#ifndef VELOCITY_MEMORY_BASIC_MANAGER_HPP
#define VELOCITY_MEMORY_BASIC_MANAGER_HPP

#include "../memory.hpp"

namespace spade::basic {
    struct LNode {
        LNode *prev = null;
        Obj *data = null;
        LNode *next = null;
    };

    class BasicMemoryManager : public MemoryManager {
        friend class BasicCollector;

        LNode *head = null;
        LNode *last = null;
    public:
        BasicMemoryManager() : MemoryManager() {}

        void *allocate(size_t size) override;

        void postAllocation(Obj *obj) override;

        void deallocate(void *pointer) override;

        void collectGarbage() override;
    };
}

#endif //VELOCITY_MEMORY_BASIC_MANAGER_HPP
