#include "state.hpp"
#include "../objects/method.hpp"
#include "../objects/module.hpp"

VMState::VMState(VM *vm) : vm(vm) {
    callStack = new Frame[FRAMES_MAX];
    fp = callStack;
}

void VMState::pushFrame(Frame *frame) {
    if (fp - callStack >= FRAMES_MAX) {
        throw StackOverflowError();
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
