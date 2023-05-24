#ifndef VELOCITY_COLLECTOR_HPP
#define VELOCITY_COLLECTOR_HPP

#include "memory.hpp"
#include "../ee/vm.hpp"

class GarbageCollector {
private:
    VM *vm;
    Space *space;
    vector<Obj *> grayMaterial;
    size_t collected = 0;

    void markRoots();

    void markTable(const Table<Obj *> &table);

    void mark(Obj *obj);

    void markThread(Thread *thread);

    void markFrame(Frame *frame);

    void traceReferences();

    void sweep();

public:
    explicit GarbageCollector(Space *space) : space(space), vm(space->getManager()->getVM()) {}

    void gc() {
        markRoots();
        traceReferences();
        sweep();
    }

    size_t getCollectedMemory() { return collected; }
};

#endif //VELOCITY_COLLECTOR_HPP
