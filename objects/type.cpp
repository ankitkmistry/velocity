#include "type.hpp"
#include "typeparam.hpp"

static string kindNames[] = {
        "class",
        "interface",
        "enum",
        "annotation",
        "type_parameter",
        "unresolved"
};

Obj *Type::copy() const {
    // Copy type params
    vector<TypeParam *> newTypeParams;
    for (auto typeParam: typeParams) {
        newTypeParams.push_back(cast<TypeParam *>(typeParam->copy()));
    }
    // Create new type object
    Obj *newType = Obj::alloc<Type>(info.manager, sign, kind, newTypeParams, supers, members, module, meta);
    // Reify the type params
    Obj::reify(&newType, typeParams, newTypeParams);
    return newType;
}

bool Type::truth() const {
    return true;
}

string Type::toString() const {
    return format("<%s '%s'>", kindNames[static_cast<int>(kind)].c_str(), sign.toString().c_str());
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
    if (obj == null) {
        throw IllegalAccessError(format("cannot find static member: %s in %s", name.c_str(), toString().c_str()));
    }
    return obj;
}

Type *Type::SENTINEL_(const string &sign, MemoryManager *manager) {
    return Obj::alloc<Type>(manager, Sign(sign), Kind::UNRESOLVED,
                            vector<TypeParam *>{}, Table<Type *>{}, Table<Obj *>{}, null, Table<string>{});
}

Type::Type(Type &type) : Obj(type.sign, null, type.module, type.meta) {
    kind = type.kind;
    typeParams = type.typeParams;
    supers = type.supers;
    members = type.members;
}
