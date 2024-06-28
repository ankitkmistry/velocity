#ifndef VELOCITY_OBJECT_HPP
#define VELOCITY_OBJECT_HPP

#include "../utils/utils.hpp"
#include "obj.hpp"

class Type;

class Object : public Obj {
private:
    Table<Obj *> members;
public:
    Object(Sign sign, Type *type, Table<Obj *> members, ObjModule *module = null, Table<string> meta = {})
            : Obj(sign, type, module, meta), members(members) {}

    Table<Obj *> getMembers() { return members; }

    Obj *getMember(const string &name) const;

    Obj *copy() const;

    bool truth() const;

    string toString() const;
};

#endif //VELOCITY_OBJECT_HPP
