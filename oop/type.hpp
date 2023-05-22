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
        UNKNOWN
    };
private:
    Kind kind;
    vector<Obj *> constPool;
    vector<Type *> typeParams;
    Table<Type *> supers;
    Table<Obj *> members;
public:
    Type(const Sign &sign, const Table<string> &meta, Kind kind, const vector<Obj *> &constPool,
         const vector<Type *> &typeParams, const Table<Type *> &supers, const Table<Obj *> &members)
            : Obj(sign, null, meta),
              kind(kind),
              constPool(constPool),
              typeParams(typeParams),
              supers(supers),
              members(members) {}

    void recognizeUnknown(Type &type);

    Obj *getMember(string name) const;

    Kind getKind() const { return kind; }

    vector<Obj *> getConstPool() const { return constPool; }

    vector<Type *> getTypeParams() const { return typeParams; }

    Table<Type *> getSupers() const { return supers; }

    Table<Obj *> getMembers() const { return members; }

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;

    static Type *TYPE_PARAM_(const string &name, VM *pVm);

    static Type *SENTINEL_(const string &sign, VM *pVm);

    Obj * getStaticMember(string &name) const;
};

#endif //VELOCITY_TYPE_HPP
