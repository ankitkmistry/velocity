#ifndef VELOCITY_METHOD_HPP
#define VELOCITY_METHOD_HPP

#include "../utils/common.hpp"
#include "obj.hpp"
#include "type.hpp"

class Frame;

class ObjMethod : public Obj {
public:
    enum Kind {
        FUNCTION,
        METHOD,
        CONSTRUCTOR
    };
private:
    Kind kind;
    vector<TypeParam *> typeParams;
    Frame *frame;
public:
    ObjMethod(const Sign &sign, Kind kind, Frame *frame, Type *type, const vector<TypeParam *> &typeParams,
              ObjModule *module = null, const Table<string> &meta = {})
            : Obj(sign, type, module, meta), kind(kind), frame(frame), typeParams(typeParams) {}

    Kind getKind() const { return kind; }

    Frame *getFrame() const { return frame; }

    const vector<TypeParam *> &getTypeParams() const { return typeParams; }

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;
};


#endif //VELOCITY_METHOD_HPP
