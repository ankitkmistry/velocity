#ifndef VELOCITY_MEMORY_BASIC_COLLECTOR_HPP
#define VELOCITY_MEMORY_BASIC_COLLECTOR_HPP

#include "basic_manager.hpp"
#include "../../objects/obj.hpp"
#include "../../ee/thread.hpp"
#include "../../callable/frame.hpp"

namespace spade::basic {
    class BasicCollector {
    private:
        BasicMemoryManager *manager;
        vector<Collectible *> grayMaterial;

        void markRoots();

        void markTable(const Table<Obj *> &table);

        void mark(Collectible *collectible);

        void markThread(Thread *thread);

        void markFrame(Frame *frame);

        void traceReferences();

        void sweep();

    public:
        explicit BasicCollector(BasicMemoryManager *manager) : manager(manager) {}

        void gc();
    };
}

#endif //VELOCITY_MEMORY_BASIC_COLLECTOR_HPP
