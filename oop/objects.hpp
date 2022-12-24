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

    [[nodiscard]] bool truth() const override {
        return value;
    }

    [[nodiscard]] string toString() const override {
        return value ? "true" : "false";
    }

    [[nodiscard]] Obj *copy() const override {
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

    [[nodiscard]] bool truth() const override {
        return c != '\0';
    }

    [[nodiscard]] string toString() const override {
        return string({c});
    }

    [[nodiscard]] Obj *copy() const override {
        return new ObjChar(c);
    }
};

class ObjNull : public Obj {
public:
    ObjNull();

    [[nodiscard]] bool truth() const override {
        return false;
    }

    [[nodiscard]] string toString() const override {
        return "null";
    }

    [[nodiscard]] Obj *copy() const override {
        return new ObjNull();
    }
};

class ObjString : public Obj {
private:
    string str;
public:
    ObjString(string str);

    [[nodiscard]] bool truth() const override {
        return !str.empty();
    }

    [[nodiscard]] string toString() const override {
        return str;
    }

    [[nodiscard]] Obj *copy() const override {
        return new ObjString(str);
    }
};

class ObjArray final : public Obj {
private:
    Obj **array;
    uint16 length;
public:
    ObjArray(int length) : Obj(Sign("array"), null), array(new Obj *[length]), length(length) {
        for (int i = 0; i < length; ++i)
            array[i] = new ObjNull();
    }

    Obj **begin() const { return &array[0]; }

    Obj **end() const { return &array[length - 1]; }

    Obj *get(size_t i) {
        if (i >= length) throw new IndexError(i);
        return array[i];
    }

    void set(size_t i, Obj *value) {
        if (i >= length) throw new IndexError(i);
        array[i] = value;
    }

    uint16 count() { return length; }

    [[nodiscard]] bool truth() const override {
        return length != 0;
    }

    [[nodiscard]] string toString() const override;

    [[nodiscard]] Obj *copy() const override;
};

class ObjFloat;

template<class T>
class ObjNumber : public Obj {
protected:
    explicit ObjNumber(Sign sign) :
            Obj(sign, null) {
    }

public:
    virtual ObjNumber *operator-() const = 0;

    virtual ObjFloat *power(ObjNumber<T> n) const = 0;

    virtual ObjNumber *operator+(ObjNumber<T> n) const = 0;

    virtual ObjNumber *operator-(ObjNumber<T> n) const = 0;

    virtual ObjNumber *operator*(ObjNumber<T> n) const = 0;

    virtual ObjNumber *operator/(ObjNumber<T> n) const = 0;

    virtual ObjBool *operator<(ObjNumber<T> n) const = 0;

    virtual ObjBool *operator<=(ObjNumber<T> n) const = 0;

    virtual ObjBool *operator==(ObjNumber<T> n) const = 0;

    virtual ObjBool *operator!=(ObjNumber<T> n) const = 0;

    virtual ObjBool *operator>=(ObjNumber<T> n) const = 0;

    virtual ObjBool *operator>(ObjNumber<T> n) const = 0;

    virtual operator const ObjFloat *() const = 0;

    [[nodiscard]] virtual T value() const = 0;
};


class ObjInt final : public ObjNumber<long> {
private:
    long val;
public:
    explicit ObjInt(long val) :
            ObjNumber(Sign("int")), val(val) {
    }

    ~ObjInt() override = default;

    [[nodiscard]] Obj *copy() const override;

    [[nodiscard]] bool truth() const override;

    [[nodiscard]] string toString() const override;

    ObjNumber<long> *operator-() const override;

    ObjFloat *power(ObjNumber<long> n) const override;

    ObjNumber<long> *operator+(ObjNumber<long> n) const override;

    ObjNumber<long> *operator-(ObjNumber<long> n) const override;

    ObjNumber<long> *operator*(ObjNumber<long> n) const override;

    ObjNumber<long> *operator/(ObjNumber<long> n) const override;

    ObjBool *operator<(ObjNumber<long> n) const override;

    ObjBool *operator<=(ObjNumber<long> n) const override;

    ObjBool *operator==(ObjNumber<long> n) const override;

    ObjBool *operator!=(ObjNumber<long> n) const override;

    ObjBool *operator>=(ObjNumber<long> n) const override;

    ObjBool *operator>(ObjNumber<long> n) const override;

    operator const ObjFloat *() const override;

    [[nodiscard]] long value() const override {
        return val;
    }
};

class ObjFloat final : public ObjNumber<double> {
private:
    double val;
public:
    explicit ObjFloat(double val) :
            ObjNumber(Sign("int")), val(val) {
    }

    ~ObjFloat() override = default;

    [[nodiscard]] Obj *copy() const override;

    [[nodiscard]] bool truth() const override;

    [[nodiscard]] string toString() const override;

    ObjNumber<double> *operator-() const override;

    ObjFloat *power(ObjNumber<double> n) const override;

    ObjNumber<double> *operator+(ObjNumber<double> n) const override;

    ObjNumber<double> *operator-(ObjNumber<double> n) const override;

    ObjNumber<double> *operator*(ObjNumber<double> n) const override;

    ObjNumber<double> *operator/(ObjNumber<double> n) const override;

    ObjBool *operator<(ObjNumber<double> n) const override;

    ObjBool *operator<=(ObjNumber<double> n) const override;

    ObjBool *operator==(ObjNumber<double> n) const override;

    ObjBool *operator!=(ObjNumber<double> n) const override;

    ObjBool *operator>=(ObjNumber<double> n) const override;

    ObjBool *operator>(ObjNumber<double> n) const override;

    operator const ObjFloat *() const override {
        return this;
    }

    [[nodiscard]] double value() const override {
        return val;
    }
};

#endif /* OOP_OBJECTS_HPP_ */
