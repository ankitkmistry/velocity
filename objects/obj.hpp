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

/**
 * The abstract description of an object in the virtual machine
 */
class Obj {
    inline static map<Obj *, Space *> spaces{};
protected:
    MemoryInfo info{};
    ObjModule *module;
    Sign sign;
    Type *type;
    Table<string> meta;

public:
    Obj(Sign sign, Type *type, ObjModule *module, const Table<string> &meta = Table<string>());

    void *operator new(size_t size, MemoryManager *manager);

    void operator delete(void *p);

    /**
     * Performs a complete deep copy on the object
     * @return a copy of the object
     */
    virtual Obj *copy() const = 0;

    /**
     * @return the corresponding truth value of the object
     */
    virtual bool truth() const = 0;

    /**
     * @return a string representation of this object for VM context only
     */
    virtual string toString() const = 0;

    /**
     * @return the memory information of the object
     */
    MemoryInfo &getInfo() { return info; }

    /**
     * @return the encapsulating module of the object
     */
    virtual ObjModule *getModule() const { return module; }

    /**
     * @return the meta information of the object
     */
    virtual const Table<string> &getMeta() const { return meta; }

    /**
     * @return the signature of the object
     */
    virtual const Sign &getSign() const { return sign; }

    /**
     * @return the type of the object
     */
    virtual Type *getType() const { return type; }

    /**
     * Sets the type of the object (generally, in case of a cast)
     * @param destType the destination type
     */
    void setType(Type *destType) { this->type = destType; }
};

class ObjBool;

/**
 * The abstract description of a comparable object in the virtual machine.
 * Simple comparison operations can be performed on this kind of object
 */
class ComparableObj : public Obj {
public:
    ComparableObj(Sign sign, Type *type, ObjModule *module, const Table<string> &meta = Table<string>())
            : Obj(sign, type, module, meta) {}

    /**
     * Performs comparison between two objects
     * @param rhs the other object to compare
     * @return < 0 if the object is less than this,
     *         = 0 if the object is equal to this,
     *         otherwise > 0 if the object is greater than this
     */
    virtual int32 compare(const Obj *rhs) const = 0;

    ObjBool *operator<(const Obj *rhs) const;

    ObjBool *operator>(const Obj *rhs) const;

    ObjBool *operator<=(const Obj *rhs) const;

    ObjBool *operator>=(const Obj *rhs) const;

    ObjBool *operator==(const Obj *rhs) const;

    ObjBool *operator!=(const Obj *rhs) const;
};

#endif /* OOP_OBJ_HPP_ */
