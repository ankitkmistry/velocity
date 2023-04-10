#ifndef VELOCITY_METHOD_HPP
#define VELOCITY_METHOD_HPP

#include "obj.hpp"

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
    Frame *frame;
public:
    ObjMethod(const Sign &sign, Type *type, const Table<string> &meta, Kind kind, Frame *frame)
            : Obj(sign, type, meta),
              kind(kind),
              frame(frame) {}

    Kind getKind() const { return kind; }

    Frame *getFrame() const { return frame; }

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;
};


#endif //VELOCITY_METHOD_HPP
