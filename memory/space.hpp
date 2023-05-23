#ifndef VELOCITY_SPACE_HPP
#define VELOCITY_SPACE_HPP

#include "../utils/common.hpp"

union Block {
    struct Header {
        bool isFree = true;
        size_t size;
        Block *next;
    } header;
    intptr_t align = 0;
};

enum class SpaceType {
    EDEN,
    SURVIVOR,
};

class MemoryManager;

class Space {
    friend class GarbageCollector;

private:
    SpaceType type;
    MemoryManager *manager;

    uint32 mallocRequests = 0;
    uint32 gcCount = 0;

    Block *base = null;
    Block *free = null;

    size_t usedSpace = 0;
    size_t freeSpace = 0;
public:
    explicit Space(SpaceType type, MemoryManager *manager) : manager(manager), type(type) {}

    void *allocate(size_t size);

    void deallocate(void *pointer);

    void take(Block *block);

    Block *moreSpace(size_t units);

    MemoryManager *getManager() const { return manager; }

    SpaceType getType() const { return type; }

    uint32 getMallocRequests() const { return mallocRequests; }

    uint32 getGcCount() const { return gcCount; }

    size_t getUsedSpace() const { return usedSpace; }

    size_t getFreeSpace() const { return freeSpace; }

    size_t getTotalSpace() const { return freeSpace + usedSpace; }
};

#endif //VELOCITY_SPACE_HPP
