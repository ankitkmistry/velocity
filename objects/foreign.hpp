#ifndef VELOCITY_FOREIGN_HPP
#define VELOCITY_FOREIGN_HPP

#include "callable.hpp"
#include "../loader/foreign_loader.hpp"

class ObjForeign final : public ObjCallable {
    Library *library;
    string name;
public:
    ObjForeign(const Sign &sign, Kind kind, Type *type, ObjModule *module, const Table<string> &meta = {})
            : ObjCallable(sign, kind, type, module, meta) {}

    void call(Thread *thread, vector<Obj *> args) override;

    void call(Thread *thread, Obj **args) override;

    Obj *copy() const override;

    string toString() const override;
};

#endif //VELOCITY_FOREIGN_HPP
