#ifndef VELOCITY_METHOD_HPP
#define VELOCITY_METHOD_HPP

#include "callable.hpp"

class Frame;

class ObjMethod : public ObjCallable {
    friend class VM;

    friend class Object;

private:
    vector<TypeParam *> typeParams;
    Frame frame;

    Frame &getFrame() { return frame; }

public:
    ObjMethod(const Sign &sign, Kind kind, Frame frame, Type *type, const vector<TypeParam *> &typeParams,
              ObjModule *module = null, const Table<string> &meta = {});

    const vector<TypeParam *> &getTypeParams() const { return typeParams; }

    const Frame &getFrame() const { return frame; }

    void call(Thread *thread, vector<Obj *> args) override;

    void call(Thread *thread, Obj **args) override;

    Obj *copy() const override;
};


#endif //VELOCITY_METHOD_HPP
