#ifndef VELOCITY_FOREIGN_HPP
#define VELOCITY_FOREIGN_HPP

#include "callable.hpp"
#include "../loader/foreign_loader.hpp"

namespace spade {
    class ObjForeign final : public ObjCallable {
        Library *library;
        string name;
        Obj *self;
    public:
        ObjForeign(const Sign &sign, Kind kind, Type *type, ObjModule *module)
                : ObjCallable(sign, kind, type, module) {}

        void linkLibrary();

        void setSelf(Obj *selfObj) override;

        void call(vector<Obj *> args) override;

        void call(Obj **args) override;

        Obj *copy() const override { return (Obj *) this; }

        string toString() const override;
    };
}

#endif //VELOCITY_FOREIGN_HPP
