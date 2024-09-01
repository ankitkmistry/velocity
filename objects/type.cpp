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
    Obj *newType = Obj::alloc<Type>(info.manager, sign, kind, newTypeParams, supers, memberSlots, module);
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

Obj *Type::getStaticMember(string name) const {
    try {
        auto slot = getMemberSlots().at(name);
        if (slot.getFlags().isStatic()) {
            return slot.getValue();
        }
    } catch (const std::out_of_range &) {}

    Obj *obj = null;
    // Check for the members in the super classes
    for (auto [_, super]: getSupers()) {
        try {
            obj = super->getStaticMember(name);
        } catch (const IllegalAccessError &) {
            obj = null;
            continue;
        }
    }
    if (obj == null) {
        throw IllegalAccessError(format("cannot find static member: %s in %s", name.c_str(), toString().c_str()));
    }
    return obj;
}

Type *Type::SENTINEL_(const string &sign, MemoryManager *manager) {
    return Obj::alloc<Type>(manager, Sign(sign), Kind::UNRESOLVED,
                            vector<TypeParam *>{}, Table<Type *>{}, Table<MemberSlot>{}, null);
}

Type::Type(Type &type) : Obj(type.sign, null, type.module) {
    kind = type.kind;
    typeParams = type.typeParams;
    supers = type.supers;
    memberSlots = type.memberSlots;
}

Type *Type::getReified(Obj **args, uint8 count) {
    if (typeParams.size() != count) {
        throw ArgumentError(sign.toString(),
                            format("expected %d type arguments, but got %d", typeParams.size(), count));
    }

    vector<Type *> typeArgs;
    for (int i = 0; i < count; ++i) {
        typeArgs.push_back(cast<Type *>(args[i]));
    }
    typeArgs.shrink_to_fit();

    try {
        return reified.at(typeArgs);
    } catch (const std::out_of_range &) {
        // Always make a copy of the object when reifying
        auto type = cast<Type *>(copy());
        auto &params = type->getTypeParams();
        for (int i = 0; i < count; i++) {
            params[i]->reify(typeArgs[i]);
        }
        reified[typeArgs] = type;
        return type;
    }
}
