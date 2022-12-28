#include "objects.hpp"

ObjBool::ObjBool(bool value) :
        Obj(Sign("bool"), null), value(value) {
}

ObjChar::ObjChar(const char c) :
        Obj(Sign("char"), null), c(c) {
}

ObjNull::ObjNull() :
        Obj(Sign("null"), null) {
}

ObjString::ObjString(string str) :
        Obj(Sign("string"), null), str(str) {
}

Obj *ObjFloat::copy() const {
    return new ObjFloat(val);
}

bool ObjFloat::truth() const {
    return val != 0.0;
}

string ObjFloat::toString() const {
    return to_string(val);
}

ObjFloat *ObjFloat::operator-() const {
    return new ObjFloat(-val);
}

ObjFloat *ObjFloat::power(ObjFloat n) const {
    return new ObjFloat(pow(val, n.value()));
}

ObjFloat *ObjFloat::operator+(ObjFloat n) const {
    return new ObjFloat(val + n.value());
}

ObjFloat *ObjFloat::operator-(ObjFloat n) const {
    return new ObjFloat(val - n.value());
}

ObjFloat *ObjFloat::operator*(ObjFloat n) const {
    return new ObjFloat(val * n.value());
}

ObjFloat *ObjFloat::operator/(ObjFloat n) const {
    return new ObjFloat(val / n.value());
}

ObjBool *ObjFloat::operator<(ObjFloat n) const {
    return new ObjBool(val < n.value());
}

ObjBool *ObjFloat::operator<=(ObjFloat n) const {
    return new ObjBool(val <= n.value());
}

ObjBool *ObjFloat::operator==(ObjFloat n) const {
    return new ObjBool(val == n.value());
}

ObjBool *ObjFloat::operator!=(ObjFloat n) const {
    return new ObjBool(val != n.value());
}

ObjBool *ObjFloat::operator>=(ObjFloat n) const {
    return new ObjBool(val >= n.value());
}

ObjBool *ObjFloat::operator>(ObjFloat n) const {
    return new ObjBool(val > n.value());
}

Obj *ObjInt::copy() const {
    return new ObjInt(val);
}

bool ObjInt::truth() const {
    return val != 0;
}

string ObjInt::toString() const {
    return to_string(val);
}

ObjInt *ObjInt::operator-() const {
    return new ObjInt(-val);
}

ObjFloat *ObjInt::power(ObjInt n) const {
    return new ObjFloat(pow(val, n.value()));
}

ObjInt *ObjInt::operator+(ObjInt n) const {
    return new ObjInt(val + n.value());
}

ObjInt *ObjInt::operator-(ObjInt n) const {
    return new ObjInt(val - n.value());
}

ObjInt *ObjInt::operator*(ObjInt n) const {
    return new ObjInt(val * n.value());
}

ObjInt *ObjInt::operator/(ObjInt n) const {
    return new ObjInt(val / n.value());
}

ObjBool *ObjInt::operator<(ObjInt n) const {
    return new ObjBool(val < n.value());
}

ObjBool *ObjInt::operator<=(ObjInt n) const {
    return new ObjBool(val <= n.value());
}

ObjBool *ObjInt::operator==(ObjInt n) const {
    return new ObjBool(val == n.value());
}

ObjBool *ObjInt::operator!=(ObjInt n) const {
    return new ObjBool(val != n.value());
}

ObjBool *ObjInt::operator>=(ObjInt n) const {
    return new ObjBool(val >= n.value());
}

ObjBool *ObjInt::operator>(ObjInt n) const {
    return new ObjBool(val > n.value());
}

ObjInt::operator const ObjFloat *() const {
    return new ObjFloat(val);
}

Obj *ObjArray::copy() const {
    auto arr = new ObjArray(length);
    for (uint16 i = 0; i < length; ++i)
        arr->set(i, array[i]);
    return arr;
}

string ObjArray::toString() const {
    string str;
    for (uint16 i = 0; i < length; ++i)
        str += array[i]->toString() + (i < length - 1 ? ", " : "");
    return "[" + str + "]";
}

Obj *ObjArray::get(int64 i) {
    if (i >= length) throw IndexError(i);
    return array[i >= 0 ? i : length + i];
}

void ObjArray::set(int64 i, Obj *value) {
    if (i >= length) throw IndexError(i);
    array[i >= 0 ? i : length + i] = value;
}
