#include "manager.hpp"
#include "collector.hpp"

void *BasicMemoryManager::allocate(size_t size) {
    return malloc(size);
}

void BasicMemoryManager::postAllocation(Obj *obj) {
    if (head == null || last == null) {
        auto node = new LNode;
        node->data = obj;
        head = node;
        last = node;
    } else {
        auto node = new LNode;
        node->data = obj;
        last->next = node;
        node->prev = last;
        last = node;
    }
}

void BasicMemoryManager::deallocate(void *pointer) {
    free(pointer);
}

void BasicMemoryManager::collectGarbage() {
    BasicCollector collector{this};
    collector.gc();
}
