#ifndef VELOCITY_TYPEPARAM_HPP
#define VELOCITY_TYPEPARAM_HPP

#include "type.hpp"

class TypeParam : public Type {
    Type *placeholder = null;

    void checkPlaceholder() const;
public:
    TypeParam(Sign sign, ObjModule *module = null, const Table<string> &meta = {})
            : Type(sign, TYPE_PARAM, {}, {}, {}, module, meta) {}

    void reify(Type *type) { placeholder = type; }

    Kind getKind() const override;

    vector<TypeParam *> getTypeParams() const override;

    Table<Type *> getSupers() const override;

    Table<Obj *> getMembers() const override;

    ObjModule *getModule() const override;

    const Table<string> &getMeta() const override;

    const Sign &getSign() const override;

    Type *getType() const override;

    Obj *copy() const override;
};


#endif //VELOCITY_TYPEPARAM_HPP
