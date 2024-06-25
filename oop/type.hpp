#ifndef VELOCITY_TYPE_HPP
#define VELOCITY_TYPE_HPP

#include "../utils/utils.hpp"
#include "obj.hpp"

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
    vector<Type *> typeParams;
    Table<Type *> supers;
    Table<Obj *> members;
public:
    Type(const Sign &sign, Kind kind, const vector<Type *> &typeParams, const Table<Type *> &supers,
         const Table<Obj *> &members, const Table<string> &meta)
            : Obj(sign, null, meta),
              kind(kind),
              typeParams(typeParams),
              supers(supers),
              members(members) {}

    Type(Type &type);

    void setKind(Kind kind_) { kind = kind_; }

    Kind getKind() const { return kind; }

    vector<Type *> getTypeParams() const { return typeParams; }

    Table<Type *> getSupers() const { return supers; }

    Table<Obj *> getMembers() const { return members; }

    Obj *getMember(string name) const;

    Obj *getStaticMember(string &name) const;

    void reifyTypeParam(uint8 i, Type &type) { *typeParams[i] = type; }

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;

    static Type *TYPE_PARAM_(const string &name, VM *pVm);

    static Type *SENTINEL_(const string &sign, VM *pVm);
};

#endif //VELOCITY_TYPE_HPP
