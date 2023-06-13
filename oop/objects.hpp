#ifndef OOP_OBJECTS_HPP_
#define OOP_OBJECTS_HPP_

#include "../utils/common.hpp"
#include "../utils/exceptions.hpp"
#include "../oop/obj.hpp"
#include "../memory/memory.hpp"

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
        return (Obj *) this;
    }

    ObjBool *operator!() const {
        return new(info.space->getManager()->getVM()) ObjBool(!value);
    }
};

class ObjChar : public Obj {
private:
    const char c;

public:
    ObjChar(char c);

    bool truth() const override {
        return c != '\0';
    }

    string toString() const override {
        return string({c});
    }

    Obj *copy() const override {
        return (Obj *) this;
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
        return (Obj *) this;
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
        return str;
    }

    Obj *copy() const override {
        return (Obj *) this;
    }

    ObjString(uint8 *bytes, uint16 len);
};

class ObjArray final : public Obj, public Iterable<Obj *> {
private:
    Obj **array;
    uint16 length;
public:
    explicit ObjArray(uint16 length)
            : Obj(Sign("array"), null),
              array(new(info.space->getManager()->getVM()) Obj *[length]), length(length) {
        for (int i = 0; i < length; ++i)
            array[i] = new(info.space->getManager()->getVM()) ObjNull;
    }

    void foreach(function<void(Obj *)> func) const override;

    Obj *get(int64 i) const;

    void set(int64 i, Obj *value);

    uint16 count() const { return length; }

    bool truth() const override { return length != 0; }

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
        ObjInt *_int;
        ObjFloat *_float;
    } numberUnion;
public:
    ObjNumber(Obj *obj) {
        if (is<ObjInt *>(obj)) {
            type = Type::INT;
            numberUnion = {._int=cast<ObjInt *>(obj)};
        } else if (is<ObjFloat *>(obj)) {
            type = Type::FLOAT;
            numberUnion = {._float=cast<ObjFloat *>(obj)};
        } else {
            throw FatalError(format("can't convert '%s' to a number", obj->toString().c_str()));
        }
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

class ObjInt final : public Obj {
private:
    int64 val;
public:
    ObjInt(int64 val) : Obj(Sign("int"), null), val(val) {}

    Obj *copy() const;

    bool truth() const;

    string toString() const;

    ObjInt *operator-() const;

    ObjFloat *power(const ObjInt &n) const;

    ObjInt *operator+(const ObjInt &n) const;

    ObjInt *operator-(const ObjInt &n) const;

    ObjInt *operator*(const ObjInt &n) const;

    ObjInt *operator/(const ObjInt &n) const;

    ObjBool *operator<(const ObjInt &n) const;

    ObjBool *operator<=(const ObjInt &n) const;

    ObjBool *operator==(const ObjInt &n) const;

    ObjBool *operator!=(const ObjInt &n) const;

    ObjBool *operator>=(const ObjInt &n) const;

    ObjBool *operator>(const ObjInt &n) const;

    ObjInt *operator~() const;

    ObjInt *operator%(const ObjInt &n) const;

    ObjInt *operator<<(const ObjInt &n) const;

    ObjInt *operator>>(const ObjInt &n) const;

    ObjInt *operator&(const ObjInt &n) const;

    ObjInt *operator|(const ObjInt &n) const;

    ObjInt *operator^(const ObjInt &n) const;

    ObjInt *unsignedRightShift(const ObjInt &n) const;

    operator ObjFloat() const;

    int64 value() const { return val; }
};

class ObjFloat final : public Obj {
private:
    double val;
public:
    ObjFloat(double val) : Obj(Sign("int"), null), val(val) {}

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;

    ObjFloat *operator-() const;

    ObjFloat *power(const ObjFloat &n) const;

    ObjFloat *operator+(const ObjFloat &n) const;

    ObjFloat *operator-(const ObjFloat &n) const;

    ObjFloat *operator*(const ObjFloat &n) const;

    ObjFloat *operator/(const ObjFloat &n) const;

    ObjBool *operator<(const ObjFloat &n) const;

    ObjBool *operator<=(const ObjFloat &n) const;

    ObjBool *operator==(const ObjFloat &n) const;

    ObjBool *operator!=(const ObjFloat &n) const;

    ObjBool *operator>=(const ObjFloat &n) const;

    ObjBool *operator>(const ObjFloat &n) const;

    double value() const { return val; }
};

#endif /* OOP_OBJECTS_HPP_ */
