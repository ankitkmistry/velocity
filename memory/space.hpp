#ifndef VELOCITY_SPACE_HPP
#define VELOCITY_SPACE_HPP

#include "../utils/common.hpp"

union Block {
    struct Header {
        int64 size;
        Block *next;

        bool isFree() { return size < 0; }

        void setFree(bool b) {
            /*
             * if size is -ve then free = true
             * if size is +ve then free = false
             */
            if (b == (size < 0))return;
            size = b ? -size : size;
        }

        int64 getSize() { return std::abs(size); }
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

    uint32 gcCount = 0;

    Block *base = null;

    size_t totalSpace = 0;
    size_t usedSpace = 0;
public:
    explicit Space(SpaceType type, MemoryManager *manager) : manager(manager), type(type) {}

    void *allocate(size_t size);

    void deallocate(void *pointer);

    void take(Block *block);

    Block *moreSpace(size_t units);

    MemoryManager *getManager() const { return manager; }

    SpaceType getType() const { return type; }

    uint32 getGcCount() const { return gcCount; }

    size_t getUsedSpace() const { return usedSpace; }

    size_t getFreeSpace() const { return totalSpace - usedSpace; }

    size_t getTotalSpace() const { return totalSpace; }

    bool init(size_t units);

    Block *getLargestFreeBlock();
};

#endif //VELOCITY_SPACE_HPP
