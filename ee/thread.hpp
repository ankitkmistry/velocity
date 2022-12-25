#ifndef VELOCITY_THREAD_HPP
#define VELOCITY_THREAD_HPP


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
    explicit Thread(const VMState &state, std::thread thread) : state(state), thread(thread) {}

    int getExitCode() const {
        return exitCode;
    }

    std::thread getThread() const {
        return thread;
    }

    Object *getValue() const {
        return value;
    }

    const VMState &getState() const {
        return state;
    }

    void setExitCode(int code) {
        exitCode = code;
    }
};


#endif //VELOCITY_THREAD_HPP
