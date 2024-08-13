#ifndef VELOCITY_OBJECT_HPP
#define VELOCITY_OBJECT_HPP

#include "../utils/utils.hpp"
#include "obj.hpp"

class Type;

class Object : public Obj {
    friend class Obj;

protected:
    Table<Obj *> members = {};

    Object(Sign sign, Type *type, Table<Obj *> members, ObjModule *module = null, Table<string> meta = {});

public:

    Object(Sign sign, Type *type, ObjModule *module = null, Table<string> meta = {});

    Table<Obj *> getMembers() { return members; }

    Obj *getMember(const string &name) const;

    void setMember(const string &name, Obj *obj);

    Obj *copy() const;

    bool truth() const;

    string toString() const;
};

#endif //VELOCITY_OBJECT_HPP
