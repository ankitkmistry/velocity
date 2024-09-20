#include "obj.hpp"
#include "module.hpp"
#include "type.hpp"
#include "typeparam.hpp"
#include "inbuilt_types.hpp"
#include "../ee/vm.hpp"

namespace spade {
    Obj::Obj(Sign sign, Type *type, ObjModule *module) :
            sign(sign), type(type), module(module) {
        if (this->module == null) {
            this->module = ObjModule::current();
        }
        if (type != null) {
            for (auto [name, slot]: type->getMemberSlots()) {
                if (slot.getFlags().isStatic())continue;
                Obj *value = slot.getValue();
                if (is<ObjCallable *>(value) &&
                    cast<ObjCallable *>(value)->getKind() != ObjCallable::Kind::CONSTRUCTOR) {
                    auto newMethod = cast<ObjCallable *>(value->copy());
                    newMethod->setSelf(this);
                    memberSlots[name] = newMethod;
                } else {
                    memberSlots[name] = Obj::createCopy(slot.getValue());
                }
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
        for (auto [_, member]: object->getMemberSlots()) {
            REIFY(&member.getValue());
        }
#undef REIFY
    }

    Obj *Obj::createCopy(Obj *obj) {
        return is<Type *>(obj) || is<ObjCallable *>(obj) || is<ObjModule *>(obj)
               ? obj : obj->copy();
    }

    Obj *Obj::getMember(string name) const {
        try {
            return getMemberSlots().at(name).getValue();
        } catch (std::out_of_range &) {
            if (type == null) {
                throw IllegalAccessError(format("cannot find member: %s in %s", name.c_str(), toString().c_str()));
            } else {
                try {
                    return type->getStaticMember(name);
                } catch (const IllegalAccessError &) {
                    throw IllegalAccessError(format("cannot find member: %s in %s", name.c_str(), toString().c_str()));
                }
            }
        }
    }

    void Obj::setMember(string name, Obj *value) {
        try {
            getMemberSlots().at(name).setValue(value);
        } catch (std::out_of_range &) {
            if (type == null) {
                getMemberSlots()[name] = MemberSlot{value, 0b0001000000000000};
            } else {
                try {
                    type->getStaticMember(name);
                } catch (const IllegalAccessError &) {
                    getMemberSlots()[name] = MemberSlot{value, 0b0001000000000000};
                }
            }
        }
        if (is<ObjCallable *>(value)) {
            cast<ObjCallable *>(value)->setSelf(this);
            if (is<ObjMethod *>(value)) {
                cast<ObjMethod *>(value)->setType(type);
            }
        }
    }

    const Table<string> &Obj::getMeta() const {
        static Table<string> noMeta = {};
        if (sign.empty()) return noMeta;
        try {
            return info.manager->getVM()->getMetadata(sign.toString());
        } catch (const IllegalAccessError &) {
            return noMeta;
        }
    }

    Obj *Obj::copy() const {
        auto copyObj = halloc<Obj>(info.manager, sign, type, module);
        for (auto [name, slot]: memberSlots) {
            copyObj->setMember(name, Obj::createCopy(slot.getValue()));
        }
        return copyObj;
    }

    string Obj::toString() const {
        return format("<object %s : '%s'>", type->getSign().toString().c_str(), sign.toString().c_str());
    }

    ObjBool *ComparableObj::operator<(const Obj *rhs) const {
        return halloc<ObjBool>(info.manager, compare(rhs) < 0);
    }

    ObjBool *ComparableObj::operator>(const Obj *rhs) const {
        return halloc<ObjBool>(info.manager, compare(rhs) > 0);
    }

    ObjBool *ComparableObj::operator<=(const Obj *rhs) const {
        return halloc<ObjBool>(info.manager, compare(rhs) <= 0);
    }

    ObjBool *ComparableObj::operator>=(const Obj *rhs) const {
        return halloc<ObjBool>(info.manager, compare(rhs) >= 0);
    }

    ObjBool *ComparableObj::operator==(const Obj *rhs) const {
        return halloc<ObjBool>(info.manager, compare(rhs) == 0);
    }

    ObjBool *ComparableObj::operator!=(const Obj *rhs) const {
        return halloc<ObjBool>(info.manager, compare(rhs) != 0);
    }
}