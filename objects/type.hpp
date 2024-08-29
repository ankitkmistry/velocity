#ifndef VELOCITY_TYPE_HPP
#define VELOCITY_TYPE_HPP

#include "obj.hpp"

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
    Table<Obj *> members;
    vector<TypeParam *> typeParams;
    map<vector<Type *>, Type *> reified;
public:
    Type(const Sign &sign, Kind kind, vector<TypeParam *> typeParams, const Table<Type *> &supers,
         const Table<Obj *> &members, ObjModule *module = null, const Table<string> &meta = {})
            : Obj(sign, null, module, meta),
              kind(kind),
              supers(supers),
              members(members),
              typeParams(typeParams) {}

    Type(Type &type);

    virtual Kind getKind() const { return kind; }

    virtual const Table<Type *> &getSupers() const { return supers; }

    virtual const vector<TypeParam *> &getTypeParams() const { return typeParams; }

    virtual Table<Type *> &getSupers() { return supers; }

    virtual vector<TypeParam *> &getTypeParams() { return typeParams; }

    Obj *getMember(string name) const override;

    Obj *getStaticMember(string &name) const;

    /**
     * @param args the type args
     * @param count count of type args
     * @return a newly reified type or previously reified type
     */
    Type *getReified(Obj **args, uint8 count);

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;

    static Type *SENTINEL_(const string &sign, MemoryManager *manager);
};

#endif //VELOCITY_TYPE_HPP
