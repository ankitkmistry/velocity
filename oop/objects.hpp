#ifndef OOP_OBJECTS_HPP_
#define OOP_OBJECTS_HPP_

#include "cmath"
#include "../utils/common.hpp"
#include "../utils/exceptions.hpp"
#include "../oop/obj.hpp"

class ObjBool : public Obj {
private:
    const bool value;

public:
    ObjBool(bool value);

    bool truth() const override {
        return value;
    }

    string toString() const override {
        return value ? "true" : "false";
    }

    Obj *copy() const override {
        return new ObjBool(value);
    }

    ObjBool *operator!() const {
        return new ObjBool(!value);
    }
};

class ObjChar : public Obj {
private:
    const char c;

public:
    ObjChar(const char c);

    bool truth() const override {
        return c != '\0';
    }

    string toString() const override {
        return string({c});
    }

    Obj *copy() const override {
        return new ObjChar(c);
    }
};

class ObjNull : public Obj {
public:
    ObjNull();

    bool truth() const override {
        return false;
    }

    string toString() const override {
        return "null";
    }

    Obj *copy() const override {
        return new ObjNull();
    }
};

class ObjString : public Obj {
private:
    string str;
public:
    ObjString(string str);

    bool truth() const override {
        return !str.empty();
    }

    string toString() const override {
        return "'" + str + "'";
    }

    Obj *copy() const override {
        return new ObjString(str);
    }
};

class ObjArray final : public Obj {
private:
    Obj **array;
    uint16 length;
public:
    explicit ObjArray(uint16 length) : Obj(Sign("array"), null), array(new Obj *[length]), length(length) {
        for (int i = 0; i < length; ++i)
            array[i] = new ObjNull();
    }

    Obj **begin() const { return &array[0]; }

    Obj **end() const { return &array[length - 1]; }

    Obj *get(int64 i);

    void set(int64 i, Obj *value);

    uint16 count() { return length; }

    bool truth() const override {
        return length != 0;
    }

    string toString() const override;

    Obj *copy() const override;
};

class ObjFloat;

class ObjInt;

class ObjNumber {
private:
    enum class Type {
        INT, FLOAT
    } type;
    union Number {
        const ObjInt *_int;
        const ObjFloat *_float;
    } numberUnion;
public:
    ObjNumber(const ObjInt *_int) {
        type = Type::INT;
        numberUnion = {._int=_int};
    }

    ObjNumber(const ObjFloat *_float) {
        type = Type::FLOAT;
        numberUnion = {._float=_float};
    }

    Obj *operator-() const;

    ObjFloat *power(ObjNumber n) const;

    Obj *operator+(ObjNumber n) const;

    Obj *operator-(ObjNumber n) const;

    Obj *operator*(ObjNumber n) const;

    Obj *operator/(ObjNumber n) const;

    ObjBool *operator<(ObjNumber n) const;

    ObjBool *operator<=(ObjNumber n) const;

    ObjBool *operator==(ObjNumber n) const;

    ObjBool *operator!=(ObjNumber n) const;

    ObjBool *operator>=(ObjNumber n) const;

    ObjBool *operator>(ObjNumber n) const;
};

class ObjNumberConvertible : public Obj {
public:
    ObjNumberConvertible(string sign) : Obj(Sign(sign), null) {}

    virtual operator ObjNumber() const = 0;
};

class ObjInt final : public ObjNumberConvertible {
private:
    int64 val;
public:
    ObjInt(int64 val) : ObjNumberConvertible("int"), val(val) {}

    Obj *copy() const;

    bool truth() const;

    string toString() const;

    ObjInt *operator-() const;

    ObjFloat *power(ObjInt n) const;

    ObjInt *operator+(ObjInt n) const;

    ObjInt *operator-(ObjInt n) const;

    ObjInt *operator*(ObjInt n) const;

    ObjInt *operator/(ObjInt n) const;

    ObjBool *operator<(ObjInt n) const;

    ObjBool *operator<=(ObjInt n) const;

    ObjBool *operator==(ObjInt n) const;

    ObjBool *operator!=(ObjInt n) const;

    ObjBool *operator>=(ObjInt n) const;

    ObjBool *operator>(ObjInt n) const;

    ObjInt *operator~() const;

    ObjInt *operator%(ObjInt n) const;

    ObjInt *operator<<(ObjInt n) const;

    ObjInt *operator>>(ObjInt n) const;

    ObjInt *unsignedRightShift(ObjInt n) const;

    operator ObjNumber() const override;

    operator ObjFloat() const;

    int64 value() const { return val; }
};

class ObjFloat final : public ObjNumberConvertible {
private:
    double val;
public:
    ObjFloat(double val) : ObjNumberConvertible("int"), val(val) {}

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;

    ObjFloat *operator-() const;

    ObjFloat *power(ObjFloat n) const;

    ObjFloat *operator+(ObjFloat n) const;

    ObjFloat *operator-(ObjFloat n) const;

    ObjFloat *operator*(ObjFloat n) const;

    ObjFloat *operator/(ObjFloat n) const;

    ObjBool *operator<(ObjFloat n) const;

    ObjBool *operator<=(ObjFloat n) const;

    ObjBool *operator==(ObjFloat n) const;

    ObjBool *operator!=(ObjFloat n) const;

    ObjBool *operator>=(ObjFloat n) const;

    ObjBool *operator>(ObjFloat n) const;

    operator ObjNumber() const override;

    double value() const { return val; }
};

#endif /* OOP_OBJECTS_HPP_ */
