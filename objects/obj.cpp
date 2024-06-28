#include "obj.hpp"
#include "../memory/memory.hpp"
#include "inbuilt_types.hpp"

Obj::Obj(Sign sign, Type *type, ObjModule *module, const Table<string> &meta) :
        sign(sign), type(type), module(module), meta(meta) {
    info.space = spaces[this];
    spaces.erase(this);
}

void *Obj::operator new(size_t size, MemoryManager *manager) {
    auto &eden = manager->getEden();
    Obj *obj = (Obj *) eden.allocate(size);
    Obj::spaces[obj] = &eden;
    return obj;
}

void Obj::operator delete(void *p) {
    auto obj = (Obj *) p;
    obj->info.space->deallocate(obj);
}

ObjBool *ComparableObj::operator<(const Obj *rhs) const {
    return new(info.space->getManager()) ObjBool(compare(rhs) < 0);
}

ObjBool *ComparableObj::operator>(const Obj *rhs) const {
    return new(info.space->getManager()) ObjBool(compare(rhs) > 0);
}

ObjBool *ComparableObj::operator<=(const Obj *rhs) const {
    return new(info.space->getManager()) ObjBool(compare(rhs) <= 0);
}

ObjBool *ComparableObj::operator>=(const Obj *rhs) const {
    return new(info.space->getManager()) ObjBool(compare(rhs) >= 0);
}

ObjBool *ComparableObj::operator==(const Obj *rhs) const {
    return new(info.space->getManager()) ObjBool(compare(rhs) == 0);
}

ObjBool *ComparableObj::operator!=(const Obj *rhs) const {
    return new(info.space->getManager()) ObjBool(compare(rhs) != 0);
}
