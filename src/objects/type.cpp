#include "type.hpp"
#include "../callable/table.hpp"
#include "typeparam.hpp"

static string kindNames[] = {"class", "interface", "enum", "annotation", "type_parameter", "unresolved"};

namespace spade
{
    Table<map<Table<Type *>, Type *>> Type::reificationTable = {};

    Obj *Type::copy() const {
        // Copy type params
        Table<NamedRef *> newTypeParams;
        for (auto [name, typeParam]: typeParams) {
            newTypeParams[name] =
                    halloc<NamedRef>(info.manager, typeParam->getName(), typeParam->getValue()->copy(), typeParam->getMeta());
        }
        // Create new type object
        Obj *newType = halloc<Type>(info.manager, sign, kind, newTypeParams, supers, memberSlots, module);
        // Reify the type params
        Obj::reify(&newType, typeParams, newTypeParams);
        return newType;
    }

    bool Type::truth() const { return true; }

    string Type::toString() const {
        return format("<%s '%s'>", kindNames[static_cast<int>(kind)].c_str(), sign.toString().c_str());
    }

    Obj *Type::getStaticMember(string name) const {
        try {
            auto slot = getMemberSlots().at(name);
            if (slot.getFlags().isStatic()) { return slot.getValue(); }
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

    void Type::setStaticMember(string name, Obj *value) {
        try {
            auto &slot = getMemberSlots().at(name);
            if (slot.getFlags().isStatic()) slot.setValue(value);
            return;
        } catch (const std::out_of_range &) {}

        // Check for the members in the super classes
        for (auto [_, super]: getSupers()) {
            try {
                super->setStaticMember(name, value);
                return;
            } catch (const IllegalAccessError &) { continue; }
        }
        throw IllegalAccessError(format("cannot find static member: %s in %s", name.c_str(), toString().c_str()));
    }

    Type *Type::SENTINEL_(const string &sign, MemoryManager *manager) {
        return halloc<Type>(manager, Sign(sign), Kind::UNRESOLVED, Table<NamedRef *>{}, Table<Type *>{}, Table<MemberSlot>{},
                            null);
    }

    Type *Type::returnReified(Table<Type *> typeParams) const {
        auto type = cast<Type *>(copy());
        auto params = type->getTypeParams();
        for (auto [name, typeparam]: params) { cast<TypeParam *>(typeparam->getValue())->setPlaceholder(typeParams[name]); }
        return type;
    }

    Type::Type(Type &type) : Obj(type.sign, null, type.module) {
        kind = type.kind;
        typeParams = type.typeParams;
        supers = type.supers;
        memberSlots = type.memberSlots;
    }

    Type *Type::getReified(Obj **args, uint8 count) const {
        if (typeParams.size() != count) {
            throw ArgumentError(sign.toString(), format("expected %d type arguments, but got %d", typeParams.size(), count));
        }

        Table<Type *> typeArgs;
        for (int i = 0; i < count; ++i) { typeArgs[getSign().getTypeParams()[i]] = (cast<Type *>(args[i])); }

        map<Table<Type *>, Type *> table;
        Type *reifiedType;

        try {
            table = reificationTable.at(getSign().toString());
        } catch (const std::out_of_range &) {
            reifiedType = returnReified(typeArgs);
            table[typeArgs] = reifiedType;
            reificationTable[getSign().toString()] = table;
            return reifiedType;
        }

        try {
            return table.at(typeArgs);
        } catch (const std::out_of_range &) {
            reifiedType = returnReified(typeArgs);
            reificationTable[getSign().toString()][typeArgs] = reifiedType;
            return reifiedType;
        }
    }

    Type *Type::getReified(vector<Type *> args) const {
        if (args.size() >= UINT8_MAX) {
            throw ArgumentError(toString(), "number of type arguments cannot be greater than 256");
        }
        auto data = args.data();
        return getReified(reinterpret_cast<Obj **>(&data), static_cast<uint8>(args.size()));
    }

    TypeParam *Type::getTypeParam(string name) const {
        try {
            return cast<TypeParam *>(typeParams.at(name)->getValue());
        } catch (const std::out_of_range &) {
            throw IllegalAccessError(format("cannot find typeparam %s in %s", name.c_str(), toString().c_str()));
        }
    }

    NamedRef *Type::captureTypeParam(string name) {
        try {
            return typeParams.at(name);
        } catch (const std::out_of_range &) {
            throw IllegalAccessError(format("cannot find typeparam %s in %s", name.c_str(), toString().c_str()));
        }
    }
} // namespace spade