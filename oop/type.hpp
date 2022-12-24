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
    vector<Obj *> conpool;
    vector<Type *> typeParams;
    Table<Type *> supers;
    Table<Obj *> members;
public:
    Type(const Sign &sign, const Table<string> &meta, Kind kind, const vector<Obj *> &conpool,
         const vector<Type *> &typeParams, const Table<Type *> &supers, const Table<Obj *> &members)
            : Obj(sign, null, meta),
              kind(kind),
              conpool(conpool),
              typeParams(typeParams),
              supers(supers),
              members(members) {}

    void recognizeUnknown(Type &type);

    Obj *getMember(string name) const;

    Kind getKind() const {
        return kind;
    }

    const vector<Obj *> &getConpool() const {
        return conpool;
    }

    const vector<Type *> &getTypeParams() const {
        return typeParams;
    }

    const Table<Type *> &getSupers() const {
        return supers;
    }

    const Table<Obj *> &getMembers() const {
        return members;
    }

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;

    static Type *TYPE_PARAM_(string name);

    static Type *SENTINEL_(string sign);
};

#endif //VELOCITY_TYPE_HPP
