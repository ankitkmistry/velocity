#include <math.h>
#include "float.hpp"

Obj *ObjFloat::copy() const {
    return (Obj *) this;
}

bool ObjFloat::truth() const {
    return val != 0.0;
}

string ObjFloat::toString() const {
    return std::to_string(val);
}

int32 ObjFloat::compare(const Obj *rhs) const {
    if (!is<const ObjFloat *>(rhs))return 0;
    return val - cast<const ObjFloat *>(rhs)->val;
}

Obj *ObjFloat::operator-() const {
    return Obj::alloc<ObjFloat>(info.manager, -val);
}

Obj *ObjFloat::power(const ObjNumber *n) const {
    return Obj::alloc<ObjFloat>(info.manager, pow(val, cast<const ObjFloat *>(n)->val));
}

Obj *ObjFloat::operator+(const ObjNumber *n) const {
    return Obj::alloc<ObjFloat>(info.manager, val + cast<const ObjFloat *>(n)->val);
}

Obj *ObjFloat::operator-(const ObjNumber *n) const {
    return Obj::alloc<ObjFloat>(info.manager, val - cast<const ObjFloat *>(n)->val);
}

Obj *ObjFloat::operator*(const ObjNumber *n) const {
    return Obj::alloc<ObjFloat>(info.manager, val * cast<const ObjFloat *>(n)->val);
}

Obj *ObjFloat::operator/(const ObjNumber *n) const {
    return Obj::alloc<ObjFloat>(info.manager, val / cast<const ObjFloat *>(n)->val);
}
