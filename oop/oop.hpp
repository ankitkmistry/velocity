#ifndef VELOCITY_OOP_HPP
#define VELOCITY_OOP_HPP

#include "../utils/utils.hpp"
#include "obj.hpp"

class Type;

class Object final : public Obj {
private:
    Table<Obj *> members;
public:
    Object(Sign sign, Type *type, Table<string> meta, Table<Obj *> members)
            : Obj(sign, type, meta), members(members) {}

    Table<Obj *> getMembers() { return members; }

    Obj *getMember(const string& name) const;

    Obj *copy() const;

    bool truth() const;

    string toString() const;

};

#endif //VELOCITY_OOP_HPP
