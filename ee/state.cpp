#include "state.hpp"

VMState::VMState(const VM *vm, Frame *frame) : vm(vm) {
    callStack = new Frame[FRAMES_MAX];
    fp = callStack;
    pushFrame(frame);
}

void VMState::loadState() {
    // Load the code for the current frame
    code = ip = getFrame()->getCode();
}

void VMState::storeState() {
    // Set frame pointer
    if (fp == null) {
        fp = callStack;
        return;
    }
    // Store the ip for the frame
    getFrame()->setIp(ip);
}

void VMState::pushFrame(Frame *frame) {
    if (fp > callStack)storeState();
    if (fp - callStack + 1 >= FRAMES_MAX) {
        // TODO: throw runtime error: stack overflow
        throw runtime_error("bad state: stack overflow");
    }
    *fp++ = *frame;
    loadState();
}

bool VMState::popFrame() {
    if (fp > callStack) {
        fp--;
        loadState();
        return true;
    }
    fp = null;
    return false;
}