#ifndef VELOCITY_STATE_HPP
#define VELOCITY_STATE_HPP

#include <sstream>
#include "../utils/common.hpp"
#include "../frame/frame.hpp"

class VM;

class VMState {
private:
    const VM *vm;
    uint8 *code = null;
    uint8 *ip = null;
    Frame *callStack = null, *fp = null;
    stringstream out;
public:
    VMState(const VM *vm, Frame *frame);

    ~VMState() {
        code = ip = null;
        callStack = fp = null;
        while (popFrame());
    }

    VMState(const VMState &state)
            : vm(state.vm), code(state.code),
              ip(state.ip), callStack(state.callStack),
              fp(state.fp), out(state.out.str()) {}

    // State operations
    void loadState();

    void storeState();

    // Frame operations
    void pushFrame(Frame *frame);

    bool popFrame();

    // Stack operations
    void push(Obj *val) { getFrame()->push(val); }

    Obj *pop() { return getFrame()->pop(); }

    Obj *peek() { return getFrame()->peek(); }

    // Constant pool operations
    Obj *loadConst(uint16 index) { return getFrame()->getConstPool()[index]->copy(); }

    // Code operations
    uint8 readByte() { return *ip++; }

    uint16 readShort() { return (ip += 2, (ip[-2] << 8) | ip[-1]); }

    void adjust(ptrdiff_t offset) { ip += offset; }

    // Getters
    const VM *getVm() const { return vm; }

    uint8 *getCode() const { return code; }

    uint8 *getIp() const { return ip; }

    Frame *getCallStack() const { return callStack; }

    Frame *getFrame() const { return fp - 1; }

    stringstream &getOut() { return dynamic_cast<stringstream &>(out); }
};

#endif //VELOCITY_STATE_HPP
