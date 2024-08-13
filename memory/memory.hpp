#ifndef VELOCITY_MEMORY_HPP
#define VELOCITY_MEMORY_HPP

#include "../utils/common.hpp"

class VM;
class Obj;

class MemoryManager {
protected:
    VM *vm;

public:
    MemoryManager() {}

    /**
     * Allocates a block of memory
     * @param size size in bytes
     * @return the pointer to the memory block
     */
    virtual void *allocate(size_t size) = 0;

    /**
     * This function performs post allocation tasks on the object.
     * This function is automatically just after allocation and initialization
     * @param obj
     */
    virtual void postAllocation(Obj *obj) = 0;

    /**
     * Frees the pointer and returns it to the operating system for further use
     * @param pointer pointer to the memory block
     */
    virtual void deallocate(void *pointer) = 0;

    /**
     * Initiates garbage collection. Frees up unnecessary space.
     */
    virtual void collectGarbage() = 0;

    void setVM(VM *vm_) { vm = vm_; }

    const VM *getVM() const { return vm; }

    VM *getVM() { return vm; }

    /**
     * @return the current memory manager respective to the current vm
     */
    static MemoryManager *current();
};

#endif //VELOCITY_MEMORY_HPP
