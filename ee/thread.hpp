#ifndef VELOCITY_THREAD_HPP
#define VELOCITY_THREAD_HPP

#include <thread>
#include "../utils/common.hpp"
#include "../oop/oop.hpp"
#include "state.hpp"

class Thread {
private:
    int exitCode = 0;
    std::thread thread;
    Object *value = null; // Program representation
    const VMState state;
public:
    Thread(const VMState &state, function<void(Thread *)> fun)
            : state(state), thread(fun, this) {}

    int getExitCode() const { return exitCode; }

    Object *getValue() const { return value; }

    VMState &getState() const { return const_cast<VMState &>(state); }

    void setExitCode(int code) { exitCode = code; }

    void join() { thread.join(); }
};


#endif //VELOCITY_THREAD_HPP
