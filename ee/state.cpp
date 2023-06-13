#include "state.hpp"

VMState::VMState(VM *vm, Frame *frame) : vm(vm) {
    callStack = new Frame[FRAMES_MAX];
    fp = callStack;
    pushFrame(frame);
}

void VMState::pushFrame(Frame *frame) {
    if (fp - callStack >= FRAMES_MAX) {
        // TODO: throw runtime error: stack overflow
        throw runtime_error("bad state: stack overflow");
    }
    *fp++ = *frame;
}

bool VMState::popFrame() {
    if (fp > callStack) {
        fp--;
        return fp != callStack;
    }
    fp = null;
    return false;
}
