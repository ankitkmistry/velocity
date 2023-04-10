#ifndef VELOCITY_THREAD_HPP
#define VELOCITY_THREAD_HPP

#include <thread>
#include "../utils/common.hpp"
#include "../oop/oop.hpp"
#include "state.hpp"

class Thread {
public:
    enum Status {
        NOT_STARTED,
        RUNNING,
        TERMINATED,
    };
private:
    int exitCode = 0;
    std::thread thread;
    Object *value = null; // Program representation
    VMState &state;
    Status status = NOT_STARTED;
public:
    Thread(VMState &state, function<void(Thread *)> fun)
            : state(state), thread(fun, this) {}

    int getExitCode() const { return exitCode; }

    Object *getValue() const { return value; }

    VMState &getState() const { return state; }

    Status getStatus() const { return status; }

    void setStatus(Status status_) { status = status_; }

    void setExitCode(int code) { exitCode = code; }

    bool isRunning() { return status == RUNNING; }

    void join() { thread.join(); }
};


#endif //VELOCITY_THREAD_HPP
