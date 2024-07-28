#ifndef VELOCITY_METHOD_HPP
#define VELOCITY_METHOD_HPP

#include "callable.hpp"
#include "../frame/frame_template.hpp"


class ObjMethod final : public ObjCallable {
    FrameTemplate *frameTemplate;
    vector<TypeParam *> typeParams;
public:
    ObjMethod(const Sign &sign,
              Kind kind,
              FrameTemplate *frame,
              Type *type,
              vector<TypeParam *> typeParams,
              ObjModule *module = null,
              const Table<string> &meta = {});

    const FrameTemplate *getFrameTemplate() const { return frameTemplate; }

    const vector<TypeParam *> &getTypeParams() const { return typeParams; }

    void call(Thread *thread, vector<Obj *> args) override;

    void call(Thread *thread, Obj **args) override;

    Obj *copy() const override;

    string toString() const override;
};


#endif //VELOCITY_METHOD_HPP
