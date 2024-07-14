#include "inbuilt_types.hpp"
#include "cmath"

int32 ObjBool::compare(const Obj *rhs) const {
    if (!is<const ObjBool *>(rhs))return 0;
    return (value ? 1 : 0) - (cast<const ObjBool *>(rhs)->value ? 1 : 0);
}

int32 ObjChar::compare(const Obj *rhs) const {
    if (!is<const ObjChar *>(rhs))return 0;
    return c - cast<const ObjChar *>(rhs)->c;
}

int32 ObjNull::compare(const Obj *rhs) const {
    if (!is<const ObjNull *>(rhs))return -1;
    return 0;
}

ObjString::ObjString(uint8 *bytes, uint16 len, ObjModule *module, const Table<string> &meta) :
        ComparableObj(Sign("string"), null, module, meta), str() {
    str = string(bytes, bytes + len);
}

int32 ObjString::compare(const Obj *rhs) const {
    if (!is<const ObjString *>(rhs))return -1;
    return str.compare(cast<const ObjString *>(rhs)->str);
}

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
    return new(info.space->getManager()) ObjFloat(-val);
}

Obj *ObjFloat::power(const ObjNumber *n) const {
    return new(info.space->getManager()) ObjFloat(pow(val, cast<const ObjFloat *>(n)->val));
}

Obj *ObjFloat::operator+(const ObjNumber *n) const {
    return new(info.space->getManager()) ObjFloat(val + cast<const ObjFloat *>(n)->val);
}

Obj *ObjFloat::operator-(const ObjNumber *n) const {
    return new(info.space->getManager()) ObjFloat(val - cast<const ObjFloat *>(n)->val);
}

Obj *ObjFloat::operator*(const ObjNumber *n) const {
    return new(info.space->getManager()) ObjFloat(val * cast<const ObjFloat *>(n)->val);
}

Obj *ObjFloat::operator/(const ObjNumber *n) const {
    return new(info.space->getManager()) ObjFloat(val / cast<const ObjFloat *>(n)->val);
}

Obj *ObjInt::copy() const {
    return (Obj *) this;
}

bool ObjInt::truth() const {
    return val != 0;
}

string ObjInt::toString() const {
    return std::to_string(val);
}

ObjInt *ObjInt::operator~() const {
    return new(info.space->getManager()) ObjInt(~val);
}

ObjInt *ObjInt::operator<<(const ObjInt &n) const {
    return new(info.space->getManager()) ObjInt(val << n.val);
}

ObjInt *ObjInt::operator>>(const ObjInt &n) const {
    return new(info.space->getManager()) ObjInt(val >> n.val);
}

ObjInt *ObjInt::unsignedRightShift(const ObjInt &n) const {
    return new(info.space->getManager()) ObjInt(val & 0x7fffffff >> n.val);
}

ObjInt *ObjInt::operator%(const ObjInt &n) const {
    return new(info.space->getManager()) ObjInt(val % n.val);
}

ObjInt *ObjInt::operator&(const ObjInt &n) const {
    return new(info.space->getManager()) ObjInt(val & n.val);
}

ObjInt *ObjInt::operator|(const ObjInt &n) const {
    return new(info.space->getManager()) ObjInt(val | n.val);
}

ObjInt *ObjInt::operator^(const ObjInt &n) const {
    return new(info.space->getManager()) ObjInt(val ^ n.val);
}

int32 ObjInt::compare(const Obj *rhs) const {
    if (!is<const ObjInt *>(rhs))return 0;
    return val - cast<const ObjInt *>(rhs)->val;
}

Obj *ObjInt::operator-() const {
    return new(info.space->getManager()) ObjInt(-val);
}

Obj *ObjInt::power(const ObjNumber *n) const {
    return new(info.space->getManager()) ObjFloat(pow(val, cast<const ObjInt *>(n)->val));
}

Obj *ObjInt::operator+(const ObjNumber *n) const {
    return new(info.space->getManager()) ObjInt(val + cast<const ObjInt *>(n)->val);
}

Obj *ObjInt::operator-(const ObjNumber *n) const {
    return new(info.space->getManager()) ObjInt(val - cast<const ObjInt *>(n)->val);
}

Obj *ObjInt::operator*(const ObjNumber *n) const {
    return new(info.space->getManager()) ObjInt(val * cast<const ObjInt *>(n)->val);
}

Obj *ObjInt::operator/(const ObjNumber *n) const {
    return new(info.space->getManager()) ObjInt(val / cast<const ObjInt *>(n)->val);
}

Obj *ObjArray::copy() const {
    auto arr = new(info.space->getManager()) ObjArray(length);
    for (uint16 i = 0; i < length; ++i)
        arr->set(i, array[i]->copy());
    return arr;
}

string ObjArray::toString() const {
    string str;
    for (uint16 i = 0; i < length; ++i)
        str += array[i]->toString() + (i < length - 1 ? ", " : "");
    return "[" + str + "]";
}

Obj *ObjArray::get(int64 i) const {
    if (i >= length) throw IndexError(i);
    if (array == null)return new(info.space->getManager()) ObjNull(module);
    return array[i >= 0 ? i : length + i];
}

void ObjArray::set(int64 i, Obj *value) {
    // Initialize the array if it is not initialized yet
    if (array == null) {
        array = new(info.space->getManager()) Obj *[length]{new(info.space->getManager()) ObjNull};
    }
    if (i >= length) throw IndexError(i);
    array[i >= 0 ? i : length + i] = value;
}

void ObjArray::foreach(function<void(Obj *)> func) const {
    for (int i = 0; i < length; ++i) func(array[i]);
}

int32 ObjArray::compare(const Obj *rhs) const {
    if (!is<const ObjArray *>(rhs))return -1;
    return toString().compare(cast<const ObjArray *>(rhs)->toString());
}
