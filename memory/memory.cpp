#include "memory.hpp"
#include "../ee/vm.hpp"

MemoryManager *MemoryManager::current() {
    if (auto vm = SpadeVM::current();vm != null)
        return vm->getMemoryManager();
    return null;
}
