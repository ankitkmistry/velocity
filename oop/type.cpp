#include "type.hpp"
#include "../memory/memory.hpp"
#include "objects.hpp"

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
    for (auto [key, value]: membersCopy) {
        membersCopy[key] = value->copy();
    }
    return new(info.space->getManager()->getVM()) Type(sign, kind, typeParams, supers, membersCopy, meta);
}

bool Type::truth() const {
    return true;
}

string Type::toString() const {
    return format("<%s '%s'>", kindNames[kind].c_str(), sign.toString().c_str());
}

Obj *Type::getMember(string name) const {
    Obj *member = getStaticMember(name);
    if (member == null)
        throw FatalError(format("can't find static member %s::%s", sign.toString().c_str(), name.c_str()));
    return member;
}

Obj *Type::getStaticMember(string &name) const {
    Obj *obj = null;
    try { obj = members.at(name); }
    catch (std::out_of_range &) {
        // Check for the members in the super classes
        for (auto [_, super]: supers) {
            if ((obj = super->getStaticMember(name)) != null)break;
        }
    }
    if (obj == null)
        obj = new(info.space->getManager()->getVM()) ObjNull;
    return obj;
}

Type *Type::TYPE_PARAM_(const string &name, VM *vm) {
    return new(vm) Type(Sign(name), Kind::TYPE_PARAM, {}, {}, {}, {});
}

Type *Type::SENTINEL_(const string &sign, VM *vm) {
    return new(vm) Type(Sign(sign), Kind::UNRESOLVED, {}, {}, {}, {});
}

Type::Type(Type &type) : Obj(type.sign, null, type.meta) {
    kind = type.kind;
    typeParams = type.typeParams;
    supers = type.supers;
    members = type.members;
}

/*Type::Type(Type &&type) : Obj(std::move(type.sign), null, std::move(type.meta)) {
    kind = std::move(type.kind);
    typeParams = std::move(type.typeParams);
    supers = std::move(type.supers);
    members = std::move(type.members);
}*/
