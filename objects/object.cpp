#include "object.hpp"
#include "type.hpp"
#include "inbuilt_types.hpp"
#include "method.hpp"

Obj *Object::getMember(const string &name) const {
    try {
        return members.at(name);
    } catch (std::out_of_range &) {
        return new(info.space->getManager()) ObjNull;
    }
}

Obj *Object::copy() const {
    Table<Obj *> mems{};
    for (auto [key, value]: members) {
        mems[key] = value->copy();
    }
    return new(info.space->getManager()) Object(sign, type, mems, module, meta);
}

bool Object::truth() const {
    return true;
}

string Object::toString() const {
    return format("<object %s : '%s'>", type->getSign().toString().c_str(), sign.toString().c_str());
}

Object::Object(Sign sign, Type *type, Table<Obj *> members, ObjModule *module, Table<string> meta)
        : Obj(sign, type, module, meta), members(members) {}


Object::Object(Sign sign, Type *type, ObjModule *module, Table<string> meta)
        : Obj(sign, type, module, meta) {
    if (type != null) {
        for (auto [key, value]: type->getMembers()) {
            Obj *valueCopy = value->copy();
            // Set the this argument in every method
            if (is<ObjMethod *>(valueCopy)) {
                cast<ObjMethod *>(valueCopy)->getFrame().getLocals().set(0, this);
            }
            this->members[key] = valueCopy;
        }
    }
}
