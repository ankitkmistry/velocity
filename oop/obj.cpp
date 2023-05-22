#include "obj.hpp"
#include "../ee/vm.hpp"

void *Obj::operator new(size_t size, VM *vm) {
    Obj *obj = (Obj *) vm->getMemoryManager().getEden().allocate(size);
    obj->getInfo().space = &vm->getMemoryManager().getEden();
    return obj;
}

void Obj::operator delete(void *p, VM *vm) {
    auto obj = (Obj *) p;
    obj->info.space->deallocate(obj);
}