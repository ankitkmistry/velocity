#include "type.hpp"

static string kindNames[] = {
        "class",
        "interface",
        "enum",
        "annotation",
        "type_parameter",
        "unknown"
};

void Type::recognizeUnknown(Type &type) {
    if (kind != Kind::UNKNOWN) {
        throw std::runtime_error("cannot change known object");
    }

    meta = type.meta;
    kind = type.kind;
    conpool = type.conpool;
    typeParams = type.typeParams;
    supers = type.supers;
    members = type.members;
}

Obj *Type::copy() const {
    Table<Obj *> mems{};
    for (auto [key, value]: members) {
        mems[key] = value->copy();
    }
    return new Type(sign, meta, kind, conpool, typeParams, supers, mems);
}

bool Type::truth() const {
    return true;
}

string Type::toString() const {
    return format("<%s '%s'>", kindNames[kind].c_str(), sign.toString().c_str());
}

Obj *Type::getMember(string name) const {
    try { return members.at(name); }
    catch (std::out_of_range &) {
        // TODO: runtime error: can't find static member $name
        return null;
    }
}

Type *Type::TYPE_PARAM_(string name) {
    return new Type(Sign(name), {}, Kind::TYPE_PARAM, {}, {}, {}, {});
}

Type *Type::SENTINEL_(string sign) {
    return new Type(Sign(sign), {}, Kind::UNKNOWN, {}, {}, {}, {});
}
