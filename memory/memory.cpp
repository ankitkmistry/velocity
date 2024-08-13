#include "memory.hpp"
#include "../ee/vm.hpp"

MemoryManager *MemoryManager::current() {
    return VM::current()->getMemoryManager();
}
