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

    const VM *getVM() const { return vm; }

    const Space &getEden() const { return eden; }

    const Space &getSurvivor() const { return survivor; }

    VM *getVM() { return vm; }

    Space &getEden() { return eden; }

    Space &getSurvivor() { return survivor; }
};

#endif //VELOCITY_MEMORY_HPP
