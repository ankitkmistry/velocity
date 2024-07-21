#include "type.hpp"
#include "inbuilt_types.hpp"

static string kindNames[] = {
        "class",
        "interface",
        "enum",
        "annotation",
        "type_parameter",
        "unresolved"
};

Obj *Type::copy() const {
    Table<Obj *> membersCopy{};
    for (auto [key, value]: members) {
        membersCopy[key] = value->copy();
    }
    return new(info.space->getManager()) Type(sign, kind, typeParams, supers, membersCopy, module, meta);
}

bool Type::truth() const {
    return true;
}

string Type::toString() const {
    return format("<%s '%s'>", kindNames[kind].c_str(), sign.toString().c_str());
}

Obj *Type::getMember(string name) const {
    return getStaticMember(name);
}

Obj *Type::getStaticMember(string &name) const {
    Obj *obj = null;
    try { obj = getMembers().at(name); }
    catch (std::out_of_range &) {
        // Check for the members in the super classes
        for (auto [_, super]: getSupers()) {
            if ((obj = super->getStaticMember(name)) != null)break;
        }
    }
    if (obj == null)
        obj = new(info.space->getManager()) ObjNull;
    return obj;
}

Type *Type::SENTINEL_(const string &sign, MemoryManager *manager) {
    return new(manager) Type(Sign(sign), Kind::UNRESOLVED, {}, {}, {}, {});
}

Type::Type(Type &type) : Obj(type.sign, null, nullptr, type.meta) {
    kind = type.kind;
    typeParams = type.typeParams;
    supers = type.supers;
    members = type.members;
}
