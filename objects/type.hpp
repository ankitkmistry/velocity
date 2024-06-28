#ifndef VELOCITY_TYPE_HPP
#define VELOCITY_TYPE_HPP

#include "obj.hpp"

class TypeParam;

class Type : public Obj {
public:
    enum Kind {
        CLASS,
        INTERFACE,
        ENUM,
        ANNOTATION,
        TYPE_PARAM,
        UNRESOLVED
    };
private:
    Kind kind;
    vector<TypeParam *> typeParams;
    Table<Type *> supers;
    Table<Obj *> members;
public:
    Type(const Sign &sign, Kind kind, const vector<TypeParam *> &typeParams, const Table<Type *> &supers,
         const Table<Obj *> &members, ObjModule *module = null, const Table<string> &meta = {})
            : Obj(sign, null, module, meta),
              kind(kind),
              typeParams(typeParams),
              supers(supers),
              members(members) {}

    Type(Type &type);

    virtual Kind getKind() const { return kind; }

    virtual vector<TypeParam *> getTypeParams() const { return typeParams; }

    virtual Table<Type *> getSupers() const { return supers; }

    virtual Table<Obj *> getMembers() const { return members; }

    Obj *getMember(string name) const;

    Obj *getStaticMember(string &name) const;

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;

    static Type *SENTINEL_(const string &sign, MemoryManager *manager);
};

#endif //VELOCITY_TYPE_HPP
