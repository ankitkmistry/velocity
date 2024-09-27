#ifndef VELOCITY_TYPE_HPP
#define VELOCITY_TYPE_HPP

#include "obj.hpp"

namespace spade {
    class TypeParam;

    class Type : public Obj {
    public:
        enum class Kind {
            /// Represents a class
            CLASS,
            /// Represents an interface
            INTERFACE,
            /// Represents an enumeration class
            ENUM,
            /// Represents an annotation
            ANNOTATION,
            /// Represents an type param
            TYPE_PARAM,
            /// Represents an unresolved type
            UNRESOLVED
        };

    protected:
        Kind kind;
        Table<Type *> supers;
        Table<NamedRef *> typeParams;
        map<vector<Type *>, Type *> reified;

    public:
        Type(const Sign &sign, Kind kind, const Table<NamedRef *> &typeParams, const Table<Type *> &supers,
             const Table<MemberSlot> &memberSlots, ObjModule *module = null)
            : Obj(sign, null, module),
              kind(kind),
              supers(supers),
              typeParams(typeParams) {
            this->memberSlots = memberSlots;
        }

        Type(Type &type);

        virtual Kind getKind() const { return kind; }

        virtual const Table<Type *> &getSupers() const { return supers; }

        virtual const Table<NamedRef *> &getTypeParams() const { return typeParams; }

        virtual Table<Type *> &getSupers() { return supers; }

        virtual Table<NamedRef *> &getTypeParams() { return typeParams; }

        virtual Obj *getStaticMember(string name) const;

        virtual void setStaticMember(string name, Obj *value);

        /**
         * @param args the type args
         * @param count count of type args
         * @return a newly reified type or previously reified type
         */
        virtual Type *getReified(Obj **args, uint8 count);

        virtual TypeParam *getTypeParam(string name) const;

        virtual NamedRef *captureTypeParam(string name);

        Obj *copy() const override;

        bool truth() const override;

        string toString() const override;

        static Type *SENTINEL_(const string &sign, MemoryManager *manager);
    };
}// namespace spade

#endif//VELOCITY_TYPE_HPP
