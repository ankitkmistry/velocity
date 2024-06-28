#include "state.hpp"
#include "../objects/method.hpp"
#include "../objects/module.hpp"

VMState::VMState(VM *vm, Frame *frame) : vm(vm) {
    callStack = new Frame[FRAMES_MAX];
    fp = callStack;
    pushFrame(frame);
}

void VMState::pushFrame(Frame *frame) {
    if (fp - callStack >= FRAMES_MAX) {
        // TODO: throw runtime error: stack overflow
        throw FatalError("bad state: stack overflow");
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
