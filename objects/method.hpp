#ifndef VELOCITY_METHOD_HPP
#define VELOCITY_METHOD_HPP

#include "callable.hpp"
#include "../frame/frame_template.hpp"


class ObjMethod final : public ObjCallable {
private:
    FrameTemplate *frameTemplate;
    map<vector<Type *>, ObjMethod *> reified;
    vector<TypeParam *> typeParams;
public:
    ObjMethod(const Sign &sign,
              Kind kind,
              FrameTemplate *frame,
              Type *type,
              vector<TypeParam *> typeParams,
              ObjModule *module = null);

    const FrameTemplate *getFrameTemplate() const { return frameTemplate; }

    const vector<TypeParam *> &getTypeParams() const { return typeParams; }

    vector<TypeParam *> &getTypeParams() { return typeParams; }

    void call(Thread *thread, vector<Obj *> args) override;

    void call(Thread *thread, Obj **args) override;

    /**
     * @param args the type args
     * @param count count of type args
     * @return a newly reified type or previously reified type
     */
    ObjMethod *getReified(Obj **args, uint8 count);

    Obj *copy() const override;

    string toString() const override;
};


#endif //VELOCITY_METHOD_HPP
