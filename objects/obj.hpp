#ifndef OOP_OBJ_HPP_
#define OOP_OBJ_HPP_

#include "../utils/common.hpp"
#include "../utils/sign.hpp"
#include "../memory/space.hpp"

class Type;

struct MemoryInfo {
    bool marked = false;
    uint32 life = 0;
    Space *space = null;
};

class ObjModule;

class Obj {
    inline static map<Obj *, Space *> spaces{};
protected:
    ObjModule *module;
    MemoryInfo info{};
    Sign sign;
    Type *type;
    Table<string> meta;

public:
    Obj(Sign sign, Type *type, ObjModule *module, const Table<string> &meta = Table<string>());

    void *operator new(size_t size, MemoryManager *manager);

    void operator delete(void *p);

    virtual Obj *copy() const = 0;

    virtual bool truth() const = 0;

    virtual string toString() const = 0;

    MemoryInfo &getInfo() { return info; }

    void setInfo(const MemoryInfo &info_) { info = info_; }

    virtual ObjModule *getModule() const { return module; }

    virtual const Table<string> &getMeta() const { return meta; }

    virtual const Sign &getSign() const { return sign; }

    virtual Type *getType() const { return type; }

    void setType(Type *typ) { this->type = typ; }
};

class ObjBool;

class ComparableObj : public Obj {
public:
    ComparableObj(Sign sign, Type *type, ObjModule *module, const Table<string> &meta = Table<string>())
            : Obj(sign, type, module, meta) {}

    virtual int32 compare(const Obj *rhs) const = 0;

    ObjBool *operator<(const Obj *rhs) const;

    ObjBool *operator>(const Obj *rhs) const;

    ObjBool *operator<=(const Obj *rhs) const;

    ObjBool *operator>=(const Obj *rhs) const;

    ObjBool *operator==(const Obj *rhs) const;

    ObjBool *operator!=(const Obj *rhs) const;
};

#endif /* OOP_OBJ_HPP_ */
