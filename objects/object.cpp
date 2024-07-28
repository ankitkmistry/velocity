#include "object.hpp"
#include "module.hpp"
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
        mems[key] = value;
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
            Obj *valueCopy = Obj::createCopy(value);
            if (is<ObjMethod *>(valueCopy)) {
                // Set this argument in every method
                const_cast<LocalsTable &>(cast<ObjMethod *>(valueCopy)->getFrameTemplate()->getLocals()).set(0, this);
            }
            this->members[key] = valueCopy;
        }
    }
}
