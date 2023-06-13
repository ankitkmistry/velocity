#include "obj.hpp"
#include "../ee/vm.hpp"

Obj::Obj(Sign sign, Type *type, const Table<string> &meta) :
        sign(sign), type(type), meta(meta) {
    info.space = spaces[this];
    spaces.erase(this);
}

void *Obj::operator new(size_t size, VM *vm) {
    auto &eden = vm->getMemoryManager().getEden();
    Obj *obj = (Obj *) eden.allocate(size);
    Obj::spaces[obj] = &eden;
    return obj;
}

void Obj::operator delete(void *p) {
    auto obj = (Obj *) p;
    obj->info.space->deallocate(obj);
}
