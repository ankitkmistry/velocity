#include "memory.hpp"
#include "../ee/vm.hpp"

MemoryManager *MemoryManager::current() {
    return SpadeVM::current()->getMemoryManager();
}
