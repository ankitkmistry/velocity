#include "type.hpp"
#include "../memory/memory.hpp"
#include "objects.hpp"

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
    constPool = type.constPool;
    typeParams = type.typeParams;
    supers = type.supers;
    members = type.members;
}

Obj *Type::copy() const {
    Table<Obj *> mems{};
    for (auto [key, value]: members) {
        mems[key] = value->copy();
    }
    return new(info.space->getManager()->getVM()) Type(sign, meta, kind, constPool, typeParams, supers, mems);
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
        throw runtime_error(format("can't find static member %s::%s", sign.toString().c_str(), name.c_str()));
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
    return new(vm) Type(Sign(name), {}, Kind::TYPE_PARAM, {}, {}, {}, {});
}

Type *Type::SENTINEL_(const string &sign, VM *vm) {
    return new(vm) Type(Sign(sign), {}, Kind::UNKNOWN, {}, {}, {}, {});
}
