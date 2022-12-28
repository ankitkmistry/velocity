#ifndef VELOCITY_THREAD_HPP
#define VELOCITY_THREAD_HPP

#include <functional>
#include <thread>
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

    const VMState &getState() const { return state; }

    void setExitCode(int code) { exitCode = code; }

    void join() { thread.join(); }
};


#endif //VELOCITY_THREAD_HPP
