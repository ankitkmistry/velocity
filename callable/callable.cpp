#include "callable.hpp"
#include "../ee/vm.hpp"

namespace spade {
    Obj *ObjCallable::invoke(vector<Obj *> args) {
        Thread *thread = Thread::current();
        call(args);
        return thread->getState()->getVM()->run(thread);
    }

    void ObjCallable::validateCallSite() {
        if (MemoryManager::current() == null || MemoryManager::current() != info.manager) {
            throw IllegalAccessError(format("invalid call site, cannot call %s", toString().c_str()));
        }
    }
}
