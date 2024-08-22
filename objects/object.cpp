#include "object.hpp"
#include "module.hpp"
#include "type.hpp"
#include "inbuilt_types.hpp"
#include "method.hpp"

Object::Object(Sign sign, Type *type, Table<Obj *> members, ObjModule *module, Table<string> meta)
        : Obj(sign, type, module, meta), members(members) {}

Object::Object(Sign sign, Type *type, ObjModule *module, Table<string> meta)
        : Obj(sign, type, module, meta) {
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

Obj *Object::getMember(const string &name) const {
    try {
        return members.at(name);
    } catch (std::out_of_range &) {
        throw IllegalAccessError(format("cannot find member: %s in %s", name.c_str(), toString().c_str()));
    }
}

void Object::setMember(const string &name, Obj *obj) {
    members[name] = obj;
}

Obj *Object::copy() const {
    Table<Obj *> mems{};
    for (auto [key, value]: members) {
        mems[key] = value;
    }
    return Obj::alloc<Object>(info.manager, sign, type, mems, module, meta);
}

bool Object::truth() const {
    return true;
}

string Object::toString() const {
    return format("<object %s : '%s'>", type->getSign().toString().c_str(), sign.toString().c_str());
}
