#include "oop.hpp"
#include "type.hpp"

Obj *Object::getMember(string name) const {
    try {
        return members.at(name);
    } catch (std::out_of_range &) {
        // TODO: runtime error: can't find member $name
        return null;
    }
}

Obj *Object::copy() const {
    Table<Obj *> mems{};
    for (auto [key, value]: members) {
        mems[key] = value->copy();
    }
    return new Object(sign, type, meta, mems);
}

bool Object::truth() const {
    return true;
}

string Object::toString() const {
    return format("<object %s '%s'>", type->getSign().toString().c_str(), sign.toString().c_str());
}
