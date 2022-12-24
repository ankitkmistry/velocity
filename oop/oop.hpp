#ifndef VELOCITY_OOP_HPP
#define VELOCITY_OOP_HPP

#include "../utils/utils.hpp"
#include "obj.hpp"

class Type;

class Object final : public Obj {
private:
    Table<Obj *> members;
public:
    Object(Sign sign, const Type *type, Table<string> meta, Table<Obj *> members)
            : Obj(sign, type, meta), members(members) {}

    Table<Obj *> getMembers() { return members; }

    Obj *getMember(string name) const;

    [[nodiscard]] Obj *copy() const;

    [[nodiscard]] bool truth() const;

    [[nodiscard]] string toString() const;

};

#endif //VELOCITY_OOP_HPP
