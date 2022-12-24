#ifndef OOP_OBJ_HPP_
#define OOP_OBJ_HPP_

#include "../utils/sign.hpp"
#include "../utils/utils.hpp"

class Type;

class Obj {
protected:
    Sign sign;
    Type *type;
    Table<string> meta;
public:
    Obj(const Sign sign, Type *type,
        const Table<string> meta = Table<string>()) :
            sign(sign), type(type), meta(meta) {
    }

    virtual ~Obj() {
    }

    virtual Obj *copy() const = 0;

    virtual bool truth() const = 0;

    virtual string toString() const = 0;

    const Table<string> &getMeta() const {
        return meta;
    }

    const Sign &getSign() const {
        return sign;
    }

    const Type *getType() const {
        return type;
    }

    void setType(const Type *typ) {
        this->type = type;
    }
};

#endif /* OOP_OBJ_HPP_ */
