#include "callable.hpp"
#include "../ee/vm.hpp"

Obj *ObjCallable::invoke(Thread *thread, vector<Obj *> args) {
    call(thread, args);
    return thread->getState()->getVM()->run(thread);
}
