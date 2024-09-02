#ifndef VELOCITY_MEMORY_BASIC_COLLECTOR_HPP
#define VELOCITY_MEMORY_BASIC_COLLECTOR_HPP

#include "manager.hpp"
#include "../../objects/obj.hpp"
#include "../../ee/thread.hpp"
#include "../../frame/frame.hpp"

class BasicCollector {
private:
    BasicMemoryManager *manager;
    vector<Obj *> grayMaterial;

    void markRoots();

    void markTable(const Table<Obj *> &table);

    void mark(Obj *obj);

    void markThread(Thread *thread);

    void markFrame(Frame *frame);

    void traceReferences();

    void sweep();

public:
    explicit BasicCollector(BasicMemoryManager *manager) : manager(manager) {}

    void gc();
};

#endif //VELOCITY_MEMORY_BASIC_COLLECTOR_HPP
