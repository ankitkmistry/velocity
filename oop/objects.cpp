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

ObjFloat *ObjFloat::power(const ObjFloat& n) const {
    return new ObjFloat(pow(val, n.value()));
}

ObjFloat *ObjFloat::operator+(const ObjFloat& n) const {
    return new ObjFloat(val + n.value());
}

ObjFloat *ObjFloat::operator-(const ObjFloat& n) const {
    return new ObjFloat(val - n.value());
}

ObjFloat *ObjFloat::operator*(const ObjFloat& n) const {
    return new ObjFloat(val * n.value());
}

ObjFloat *ObjFloat::operator/(const ObjFloat& n) const {
    return new ObjFloat(val / n.value());
}

ObjBool *ObjFloat::operator<(const ObjFloat& n) const {
    return new ObjBool(val < n.value());
}

ObjBool *ObjFloat::operator<=(const ObjFloat& n) const {
    return new ObjBool(val <= n.value());
}

ObjBool *ObjFloat::operator==(const ObjFloat& n) const {
    return new ObjBool(val == n.value());
}

ObjBool *ObjFloat::operator!=(const ObjFloat& n) const {
    return new ObjBool(val != n.value());
}

ObjBool *ObjFloat::operator>=(const ObjFloat& n) const {
    return new ObjBool(val >= n.value());
}

ObjBool *ObjFloat::operator>(const ObjFloat& n) const {
    return new ObjBool(val > n.value());
}

ObjFloat::operator ObjNumber() const {
    return {this};
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

ObjFloat *ObjInt::power(const ObjInt& n) const {
    return new ObjFloat(pow(val, n.value()));
}

ObjInt *ObjInt::operator+(const ObjInt& n) const {
    return new ObjInt(val + n.value());
}

ObjInt *ObjInt::operator-(const ObjInt& n) const {
    return new ObjInt(val - n.value());
}

ObjInt *ObjInt::operator*(const ObjInt& n) const {
    return new ObjInt(val * n.value());
}

ObjInt *ObjInt::operator/(const ObjInt& n) const {
    return new ObjInt(val / n.value());
}

ObjBool *ObjInt::operator<(const ObjInt& n) const {
    return new ObjBool(val < n.value());
}

ObjBool *ObjInt::operator<=(const ObjInt& n) const {
    return new ObjBool(val <= n.value());
}

ObjBool *ObjInt::operator==(const ObjInt& n) const {
    return new ObjBool(val == n.value());
}

ObjBool *ObjInt::operator!=(const ObjInt& n) const {
    return new ObjBool(val != n.value());
}

ObjBool *ObjInt::operator>=(const ObjInt& n) const {
    return new ObjBool(val >= n.value());
}

ObjBool *ObjInt::operator>(const ObjInt& n) const {
    return new ObjBool(val > n.value());
}

ObjInt::operator ObjNumber() const {
    return {this};
}

ObjInt::operator ObjFloat() const {
    return {static_cast<double>(val)};
}

ObjInt *ObjInt::operator~() const {
    return new ObjInt(~val);
}

ObjInt *ObjInt::operator<<(const ObjInt& n) const {
    return new ObjInt(val << n.value());
}

ObjInt *ObjInt::operator>>(const ObjInt& n) const {
    return new ObjInt(val >> n.value());
}

ObjInt *ObjInt::unsignedRightShift(const ObjInt& n) const {
    return new ObjInt(val & 0x7fffffff >> n.value());
}

ObjInt *ObjInt::operator%(const ObjInt& n) const {
    return new ObjInt(val % n.value());
}

ObjInt *ObjInt::operator&(const ObjInt &n) const {
    return new ObjInt(val & n.value());
}

ObjInt *ObjInt::operator|(const ObjInt &n) const {
    return new ObjInt(val | n.value());
}

ObjInt *ObjInt::operator^(const ObjInt &n) const {
    return new ObjInt(val ^ n.value());
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

Obj *ObjArray::get(int64 i) const {
    if (i >= length) throw IndexError(i);
    return array[i >= 0 ? i : length + i];
}

void ObjArray::set(int64 i, Obj *value) {
    if (i >= length) throw IndexError(i);
    array[i >= 0 ? i : length + i] = value;
}

void ObjArray::foreach(function<void(Obj *)> func) const {
    for (int i = 0; i < length; ++i) {
        func(array[i]);
    }
}

Obj *ObjNumber::operator-() const {
    if (type == Type::INT) {
        return -*numberUnion._int;
    }
    return -*numberUnion._float;
}

ObjFloat *ObjNumber::power(ObjNumber n) const {
    if (type == Type::INT) {
        if (n.type == Type::INT) {
            return new ObjFloat(pow(numberUnion._int->value(), n.numberUnion._int->value()));
        } else {
            return new ObjFloat(pow(numberUnion._int->value(), n.numberUnion._float->value()));
        }
    } else {
        if (n.type == Type::INT) {
            return new ObjFloat(pow(numberUnion._float->value(), n.numberUnion._int->value()));
        } else {
            return new ObjFloat(pow(numberUnion._float->value(), n.numberUnion._float->value()));
        }
    }
}

Obj *ObjNumber::operator+(ObjNumber n) const {
    if (type == Type::INT) {
        if (n.type == Type::INT) {
            return *numberUnion._int + *n.numberUnion._int;
        } else {
            return *n.numberUnion._float + *numberUnion._int;
        }
    } else {
        if (n.type == Type::INT) {
            return *numberUnion._float + *n.numberUnion._int;
        } else {
            return *n.numberUnion._float + *numberUnion._float;
        }
    }
}

Obj *ObjNumber::operator-(ObjNumber n) const {
    if (type == Type::INT) {
        if (n.type == Type::INT) {
            return *numberUnion._int - *n.numberUnion._int;
        } else {
            return static_cast<ObjFloat>(*numberUnion._int) - *n.numberUnion._float;
        }
    } else {
        if (n.type == Type::INT) {
            return *numberUnion._float - *n.numberUnion._int;
        } else {
            return *n.numberUnion._float - *numberUnion._float;
        }
    }
}

Obj *ObjNumber::operator*(ObjNumber n) const {
    if (type == Type::INT) {
        if (n.type == Type::INT) {
            return *numberUnion._int * *n.numberUnion._int;
        } else {
            return *n.numberUnion._float * *numberUnion._int;
        }
    } else {
        if (n.type == Type::INT) {
            return *numberUnion._float * *n.numberUnion._int;
        } else {
            return *n.numberUnion._float * *numberUnion._float;
        }
    }
}

Obj *ObjNumber::operator/(ObjNumber n) const {
    if (type == Type::INT) {
        if (n.type == Type::INT) {
            return *numberUnion._int / *n.numberUnion._int;
        } else {
            return static_cast<ObjFloat>(*numberUnion._int) / *n.numberUnion._float;
        }
    } else {
        if (n.type == Type::INT) {
            return *numberUnion._float + *n.numberUnion._int;
        } else {
            return *n.numberUnion._float + *numberUnion._float;
        }
    }
}

ObjBool *ObjNumber::operator<(ObjNumber n) const {
    if (type == Type::INT) {
        if (n.type == Type::INT) {
            return *numberUnion._int < *n.numberUnion._int;
        } else {
            return static_cast<ObjFloat>(*numberUnion._int) < *n.numberUnion._float;
        }
    } else {
        if (n.type == Type::INT) {
            return *numberUnion._float < *n.numberUnion._int;
        } else {
            return *n.numberUnion._float < *numberUnion._float;
        }
    }
}

ObjBool *ObjNumber::operator<=(ObjNumber n) const {
    if (type == Type::INT) {
        if (n.type == Type::INT) {
            return *numberUnion._int <= *n.numberUnion._int;
        } else {
            return static_cast<ObjFloat>(*numberUnion._int) <= *n.numberUnion._float;
        }
    } else {
        if (n.type == Type::INT) {
            return *numberUnion._float <= *n.numberUnion._int;
        } else {
            return *n.numberUnion._float <= *numberUnion._float;
        }
    }
}

ObjBool *ObjNumber::operator==(ObjNumber n) const {
    if (type == Type::INT) {
        if (n.type == Type::INT) {
            return *numberUnion._int == *n.numberUnion._int;
        } else {
            return static_cast<ObjFloat>(*numberUnion._int) == *n.numberUnion._float;
        }
    } else {
        if (n.type == Type::INT) {
            return *numberUnion._float == *n.numberUnion._int;
        } else {
            return *n.numberUnion._float == *numberUnion._float;
        }
    }
}

ObjBool *ObjNumber::operator!=(ObjNumber n) const {
    if (type == Type::INT) {
        if (n.type == Type::INT) {
            return *numberUnion._int != *n.numberUnion._int;
        } else {
            return static_cast<ObjFloat>(*numberUnion._int) != *n.numberUnion._float;
        }
    } else {
        if (n.type == Type::INT) {
            return *numberUnion._float != *n.numberUnion._int;
        } else {
            return *n.numberUnion._float != *numberUnion._float;
        }
    }
}

ObjBool *ObjNumber::operator>=(ObjNumber n) const {
    if (type == Type::INT) {
        if (n.type == Type::INT) {
            return *numberUnion._int >= *n.numberUnion._int;
        } else {
            return static_cast<ObjFloat>(*numberUnion._int) >= *n.numberUnion._float;
        }
    } else {
        if (n.type == Type::INT) {
            return *numberUnion._float >= *n.numberUnion._int;
        } else {
            return *n.numberUnion._float >= *numberUnion._float;
        }
    }
}

ObjBool *ObjNumber::operator>(ObjNumber n) const {
    if (type == Type::INT) {
        if (n.type == Type::INT) {
            return *numberUnion._int > *n.numberUnion._int;
        } else {
            return static_cast<ObjFloat>(*numberUnion._int) > *n.numberUnion._float;
        }
    } else {
        if (n.type == Type::INT) {
            return *numberUnion._float > *n.numberUnion._int;
        } else {
            return *n.numberUnion._float > *numberUnion._float;
        }
    }
}
