#include "obj.hpp"
#include "module.hpp"
#include "type.hpp"
#include "object.hpp"
#include "inbuilt_types.hpp"
#include "method.hpp"

Obj::Obj(Sign sign, Type *type, ObjModule *module, const Table<string> &meta) :
        sign(sign), type(type), module(module), meta(meta) {
    if (type != null) {
        for (auto [key, value]: type->getMembers()) {
            Obj *valueCopy = Obj::createCopy(value);
            if (is<ObjMethod *>(valueCopy)) {
                // Set this argument in every method
                const_cast<LocalsTable &>(cast<ObjMethod *>(valueCopy)->getFrameTemplate()->getLocals()).set(0, this);
            }
            this->members[key] = valueCopy;
        }
    }
}

void Obj::reify(Obj **pObj, vector<TypeParam *> old_, vector<TypeParam *> new_) {
#define REIFY(pObj) reify(pObj, old_, new_)
    if (*pObj == null) return;
    if (old_.empty() || new_.empty()) return;

    if (auto array = dynamic_cast<ObjArray *>(*pObj); array != null) {
        // Reify array items
        for (int i = 0; i < array->count(); ++i) {
            auto item = array->get(i);
            REIFY(&item);
            array->set(i, item);
        }
    } else if (auto method = dynamic_cast<ObjMethod *>(*pObj); method != null) {
        auto frameTemplate = method->getFrameTemplate();
        // Reify args
        auto &args = frameTemplate->getArgs();
        for (int i = 0; i < args.count(); ++i) {
            auto arg = args.get(i);
            REIFY(&arg);
        }
        // Reify locals
        auto &locals = frameTemplate->getLocals();
        for (int i = 0; i < locals.count(); ++i) {
            auto local = locals.get(i);
            REIFY(&local);
        }
        // Reify lambdas
        auto &lambdas = frameTemplate->getLambdas();
        for (int i = 0; i < lambdas.size(); ++i) {
            auto lambda = cast<Obj *>(lambdas[i]);
            REIFY(&lambda);
        }
        // Reify matches
        auto &matches = frameTemplate->getMatches();
        for (auto match: matches) {
            auto cases = match.getCases();
            for (int i = 0; i < cases.size(); ++i) {
                auto caseValue = cases[i].getValue();
                REIFY(&caseValue);
            }
        }
        // Reify exceptions
        auto &exceptions = frameTemplate->getExceptions();
        for (int i = 0; i < exceptions.count(); ++i) {
            auto excType = cast<Obj *>(exceptions.get(i).getType());
            REIFY(&excType);
        }
    } else if (auto tp = dynamic_cast<TypeParam *>(*pObj); tp != null) {
        // Change type params accordingly
        for (int i = 0; i < old_.size(); ++i) {
            if (*pObj == old_[i]) {
                *pObj = new_[i];
                break;
            }
        }
        return;
    }

    auto object = *pObj;
    // Reify object type
    Obj *type = object->type;
    if (type != null) {
        REIFY(&type);
        object->type = cast<Type *>(type);
    }
    // Reify members
    for (auto [_, member]: object->getMembers()) {
        REIFY(&member);
    }
#undef REIFY
}

Obj *Obj::createCopy(Obj *obj) {
    return is<Type *>(obj) || is<ObjCallable *>(obj) || is<ObjModule *>(obj)
           ? obj : obj->copy();
}

Obj *Obj::getMember(string name) const {
    try {
        return getMembers().at(name);
    } catch (std::out_of_range &) {
        throw IllegalAccessError(format("cannot find member: %s in %s", name.c_str(), toString().c_str()));
    }
}

void Obj::setMember(string name, Obj *value) {
    getMembers()[name] = value;
}

Obj *Obj::copy() const {
    auto copyObj = Obj::alloc<Obj>(info.manager, sign, type, module, meta);
    for (auto [key, value]: members) {
        copyObj->setMember(key, Obj::createCopy(value));
    }
    return copyObj;
}

string Obj::toString() const {
    return format("<object %s : '%s'>", type->getSign().toString().c_str(), sign.toString().c_str());
}

ObjBool *ComparableObj::operator<(const Obj *rhs) const {
    return Obj::alloc<ObjBool>(info.manager, compare(rhs) < 0);
}

ObjBool *ComparableObj::operator>(const Obj *rhs) const {
    return Obj::alloc<ObjBool>(info.manager, compare(rhs) > 0);
}

ObjBool *ComparableObj::operator<=(const Obj *rhs) const {
    return Obj::alloc<ObjBool>(info.manager, compare(rhs) <= 0);
}

ObjBool *ComparableObj::operator>=(const Obj *rhs) const {
    return Obj::alloc<ObjBool>(info.manager, compare(rhs) >= 0);
}

ObjBool *ComparableObj::operator==(const Obj *rhs) const {
    return Obj::alloc<ObjBool>(info.manager, compare(rhs) == 0);
}

ObjBool *ComparableObj::operator!=(const Obj *rhs) const {
    return Obj::alloc<ObjBool>(info.manager, compare(rhs) != 0);
}
