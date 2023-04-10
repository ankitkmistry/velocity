#ifndef VELOCITY_STATE_HPP
#define VELOCITY_STATE_HPP

#include "../utils/common.hpp"
#include "../utils/utils.hpp"
#include "../frame/frame.hpp"

class VM;

class VMState {
private:
    const VM *vm;
    uint8 *code = null;
    uint8 *ip = null;
    Frame *callStack = null, *fp = null;
    std::stringstream out;
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
    void push(Obj *val) const { getFrame()->push(val); }

    Obj *pop() const { return getFrame()->pop(); }

    Obj *peek() const { return getFrame()->peek(); }

    // Constant pool operations
    Obj *loadConst(uint16 index) const { return getFrame()->getConstPool()[index]->copy(); }

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

    void write(const string& str) { out << str; }

    string getOutput() { return out.str(); }

    uint16 getCallStackSize() { return fp - callStack; }

    uint32 getPc();
};

#endif //VELOCITY_STATE_HPP
