#ifndef VELOCITY_FOREIGN_HPP
#define VELOCITY_FOREIGN_HPP

#include "callable.hpp"
#include "../loader/foreign_loader.hpp"

class ObjForeign final : public ObjCallable {
    Library *library;
    string name;
public:
    ObjForeign(const Sign &sign, Kind kind, Type *type, ObjModule *module)
            : ObjCallable(sign, kind, type, module) {}

    void call(vector<Obj *> args) override;

    void call(Obj **args) override;

    void linkLibrary();

    Obj *copy() const override { return (Obj *) this; }

    string toString() const override;
};

#endif //VELOCITY_FOREIGN_HPP
