#ifndef VELOCITY_TYPEPARAM_HPP
#define VELOCITY_TYPEPARAM_HPP

#include "type.hpp"

namespace spade {
    class TypeParam : public Type {
        Type *placeholder = null;

        void checkPlaceholder() const;

    public:
        TypeParam(Sign sign, ObjModule *module = null)
                : Type(sign, Kind::TYPE_PARAM, {}, {}, {}, module) {}

        /**
         * Reifies the type parameter to the specified \p type
         * @param type the final type
         */
        void reify(Type *type) { placeholder = type; }

        Kind getKind() const override;

        const vector<TypeParam *> &getTypeParams() const override;

        const Table<Type *> &getSupers() const override;

        const Table<MemberSlot> &getMemberSlots() const override;

        vector<TypeParam *> &getTypeParams() override;

        Table<Type *> &getSupers() override;

        Table<MemberSlot> &getMemberSlots() override;

        ObjModule *getModule() const override;

        const Table<string> &getMeta() const override;

        const Sign &getSign() const override;

        Type *getType() const override;

        Obj *copy() const override;
    };
}

#endif //VELOCITY_TYPEPARAM_HPP
