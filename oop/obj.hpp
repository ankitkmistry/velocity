#ifndef OOP_OBJ_HPP_
#define OOP_OBJ_HPP_

#include <utility>

#include "../utils/common.hpp"
#include "../utils/sign.hpp"
#include "../utils/utils.hpp"

class Space;

class VM;

class Type;

struct MemoryInfo {
    bool marked = false;
    uint32 life = 0;
    Space *space = null;
};

class Obj {
    inline static map<Obj *, Space *> spaces{};
protected:
    MemoryInfo info{};
    Sign sign;
    Type *type;
    Table<string> meta;

public:
    Obj(Sign sign, Type *type,
        const Table<string> &meta = Table<string>());

    void *operator new(size_t size, VM *vm);

    void operator delete(void *p);

    virtual Obj *copy() const = 0;

    virtual bool truth() const = 0;

    virtual string toString() const = 0;

    MemoryInfo &getInfo() { return info; }

    void setInfo(const MemoryInfo &info_) { info = info_; }

    const Table<string> &getMeta() const { return meta; }

    const Sign &getSign() const { return sign; }

    Type *getType() const { return type; }

    void setType(Type *typ) { this->type = typ; }
};

#endif /* OOP_OBJ_HPP_ */
