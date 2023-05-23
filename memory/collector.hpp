#ifndef VELOCITY_COLLECTOR_HPP
#define VELOCITY_COLLECTOR_HPP

#include "memory.hpp"
#include "../ee/vm.hpp"

class GarbageCollector {
private:
    VM *vm;
    Space *space;
    vector<Obj *> grayMaterial;

    void markRoots();

    void markTable(const Table<Obj *> &table);

    void mark(Obj *obj);

    void markThread(Thread *thread);

    void markFrame(Frame *frame);

    void traceReferences();

    void sweep();

public:
    GarbageCollector(Space *space, VM *vm) : space(space), vm(vm) {}

    void gc() {
        markRoots();
        traceReferences();
        sweep();
    }
};

#endif //VELOCITY_COLLECTOR_HPP
