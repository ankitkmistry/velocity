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

template<class T, class V>
class ObjNumber : public Obj {
protected:
    explicit ObjNumber(Sign sign) :
            Obj(sign, null) {
    }

public:
    virtual ObjNumber *operator-() const = 0;

    virtual ObjFloat *power(T n) const = 0;

    virtual ObjNumber *operator+(T n) const = 0;

    virtual ObjNumber *operator-(T n) const = 0;

    virtual ObjNumber *operator*(T n) const = 0;

    virtual ObjNumber *operator/(T n) const = 0;

    virtual ObjBool *operator<(T n) const = 0;

    virtual ObjBool *operator<=(T n) const = 0;

    virtual ObjBool *operator==(T n) const = 0;

    virtual ObjBool *operator!=(T n) const = 0;

    virtual ObjBool *operator>=(T n) const = 0;

    virtual ObjBool *operator>(T n) const = 0;

    virtual operator const ObjFloat *() const = 0;

    virtual V value() const = 0;
};


class ObjInt final : public ObjNumber<ObjInt, int64> {
private:
    int64 val;
public:
    ObjInt(int64 val) :
            ObjNumber(Sign("int")), val(val) {
    }

    ~ObjInt() override = default;

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;

    ObjInt *operator-() const override;

    ObjFloat *power(ObjInt n) const override;

    ObjInt *operator+(ObjInt n) const override;

    ObjInt *operator-(ObjInt n) const override;

    ObjInt *operator*(ObjInt n) const override;

    ObjInt *operator/(ObjInt n) const override;

    ObjBool *operator<(ObjInt n) const override;

    ObjBool *operator<=(ObjInt n) const override;

    ObjBool *operator==(ObjInt n) const override;

    ObjBool *operator!=(ObjInt n) const override;

    ObjBool *operator>=(ObjInt n) const override;

    ObjBool *operator>(ObjInt n) const override;

    operator const ObjFloat *() const override;

    int64 value() const override {
        return val;
    }
};

class ObjFloat final : public ObjNumber<ObjFloat, double> {
private:
    double val;
public:
    ObjFloat(double val) :
            ObjNumber(Sign("int")), val(val) {
    }

    ~ObjFloat() override = default;

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;

    ObjFloat *operator-() const override;

    ObjFloat *power(ObjFloat n) const override;

    ObjFloat *operator+(ObjFloat n) const override;

    ObjFloat *operator-(ObjFloat n) const override;

    ObjFloat *operator*(ObjFloat n) const override;

    ObjFloat *operator/(ObjFloat n) const override;

    ObjBool *operator<(ObjFloat n) const override;

    ObjBool *operator<=(ObjFloat n) const override;

    ObjBool *operator==(ObjFloat n) const override;

    ObjBool *operator!=(ObjFloat n) const override;

    ObjBool *operator>=(ObjFloat n) const override;

    ObjBool *operator>(ObjFloat n) const override;

    operator const ObjFloat *() const override {
        return this;
    }

    double value() const override {
        return val;
    }
};

#endif /* OOP_OBJECTS_HPP_ */
