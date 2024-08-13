#include "thread.hpp"

Thread::Thread(VMState *state, function<void(Thread *)> fun)
        : state(state), thread(fun, this) {
    threads[thread.get_id()] = this;
}

Thread *Thread::current() {
    return threads[std::this_thread::get_id()];
}
