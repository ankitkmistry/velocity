#ifndef VELOCITY_TYPEPARAM_HPP
#define VELOCITY_TYPEPARAM_HPP

#include "type.hpp"

class TypeParam : public Type {
    Type *placeholder = null;

    void checkPlaceholder() const;

public:
    TypeParam(Sign sign, ObjModule *module = null, const Table<string> &meta = {})
            : Type(sign, Kind::TYPE_PARAM, {}, {}, {}, module, meta) {}

    /**
     * Reifies the type parameter to the specified \p type
     * @param type the final type
     */
    void reify(Type *type) { placeholder = type; }

    Kind getKind() const override;

    const vector<TypeParam *> &getTypeParams() const override;

    const Table<Type *> &getSupers() const override;

    const Table<Obj *> &getMembers() const override;

    vector<TypeParam *> &getTypeParams() override;

    Table<Type *> &getSupers() override;

    Table<Obj *> &getMembers() override;

    ObjModule *getModule() const override;

    const Table<string> &getMeta() const override;

    const Sign &getSign() const override;

    Type *getType() const override;

    Obj *copy() const override;
};


#endif //VELOCITY_TYPEPARAM_HPP
