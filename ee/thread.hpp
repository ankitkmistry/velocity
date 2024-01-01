#ifndef VELOCITY_THREAD_HPP
#define VELOCITY_THREAD_HPP

#include <thread>
#include "../utils/common.hpp"
#include "../oop/oop.hpp"
#include "state.hpp"

/**
 * Representation of a vm thread
 */
class Thread {
public:
    enum Status {
        /// The thread has not started yet
        NOT_STARTED,
        /// This thread is currently in execution
        RUNNING,
        /// The thread has terminated
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

    /**
     * @return The exitcode of the thread
     */
    int getExitCode() const { return exitCode; }

    /**
     * @return The object representation of the thread
     */
    Object *getValue() const { return value; }

    /**
     * @return The vm state
     */
    VMState &getState() const { return state; }

    /**
     * @return The status of the thread
     */
    Status getStatus() const { return status; }

    /**
     * Sets the status of the thread
     * @param status_ the new thread status
     */
    void setStatus(Status status_) { status = status_; }

    /**
     * Sets the exit code of the thread
     * @param code the new exit code value
     */
    void setExitCode(int code) { exitCode = code; }

    /**
     * @return true if the thread is running, false otherwise
     */
    bool isRunning() { return status == RUNNING; }

    /**
     * Blocks the caller thread until this thread completes.
     * Upon the completion of this thread the function returns to the caller thread
     */
    void join() { thread.join(); }
};


#endif //VELOCITY_THREAD_HPP
