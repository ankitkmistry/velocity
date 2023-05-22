#ifndef VELOCITY_MEMORY_HPP
#define VELOCITY_MEMORY_HPP

#include "../utils/common.hpp"
#include "../utils/exceptions.hpp"
#include "../debug/table.hpp"
#include "../ee/thread.hpp"

class VM;

union Block {
    struct Header {
        bool isFree = true;
        size_t size;
        Block *next;
    } header;
    intptr_t align;
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

class GarbageCollector {
private:
    VM *vm;
    Space *space;
    vector<Obj *> grayMaterial;
public:
    GarbageCollector(Space *space, VM *vm) : space(space), vm(vm) {}

    void markRoots();

    void markTable(const Table<Obj *> &table);

    void mark(Obj *obj);

    void markThread(Thread *thread);

    void markFrame(Frame *frame);

    void traceReferences();

    void sweep();

    void gc() {
        markRoots();
        traceReferences();
        sweep();
    }
};

void *operator new(size_t size, VM *vm);

void operator delete(void *p, VM *vm);

#endif //VELOCITY_MEMORY_HPP
