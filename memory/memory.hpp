#ifndef VELOCITY_MEMORY_HPP
#define VELOCITY_MEMORY_HPP

#include "../utils/common.hpp"
#include "space.hpp"

class VM;

class MemoryManager {
private:
    VM *vm;
    Space eden{SpaceType::EDEN, this};
    Space survivor{SpaceType::SURVIVOR, this};
public:
    explicit MemoryManager(VM *vm) : vm(vm) {}

    VM *getVM() { return vm; }

    Space &getEden() { return eden; }

    Space &getSurvivor() { return survivor; }
};

void *operator new(size_t size, VM *vm);

void operator delete(void *p, VM *vm);

#endif //VELOCITY_MEMORY_HPP
