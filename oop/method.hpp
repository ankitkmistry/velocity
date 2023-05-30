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
    vector<Type *> typeParams;
    Frame *frame;
public:
    ObjMethod(const Sign &sign, Kind kind, Frame *frame, Type *type, const vector<Type *> &typeParams,
              const Table<string> &meta)
            : Obj(sign, type, meta), kind(kind), frame(frame), typeParams(typeParams) {}

    Kind getKind() const { return kind; }

    Frame *getFrame() const { return frame; }

    const vector<Type *> &getTypeParams() const { return typeParams; }

    void reifyTypeParam(uint8 i, Type &type) { typeParams[i]->recognize(type); }

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;
};


#endif //VELOCITY_METHOD_HPP
