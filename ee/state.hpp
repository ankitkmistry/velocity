#ifndef VELOCITY_STATE_HPP
#define VELOCITY_STATE_HPP

#include "../utils/common.hpp"
#include "../utils/utils.hpp"
#include "../frame/frame.hpp"

class VM;

class VMState {
private:
    VM *vm;
    Frame *callStack = null, *fp = null;
    std::stringstream out;
public:
    VMState(VM *vm, Frame *frame);

    ~VMState() {
        callStack = fp = null;
        while (popFrame());
    }

    VMState(const VMState &state)
            : vm(state.vm),
              callStack(state.callStack), fp(state.fp),
              out(state.out.str()) {}

    // State operations

    // Frame operations
    /**
     * Pushes a call frame on top of the call stack
     * @param frame
     */
    void pushFrame(Frame *frame);

    /**
     * Pops the active call frame and reloads the state
     * @return true if the call stack is not empty, false otherwise
     */
    bool popFrame();

    // Stack operations
    /**
     * Pushes val on top of the operand stack
     * @param val
     */
    void push(Obj *val) const { getFrame()->push(val); }

    /**
     * Pops the operand stack
     * @return the popped value
     */
    Obj *pop() const { return getFrame()->pop(); }

    /**
     * @return the value on top of the operand stack
     */
    Obj *peek() const { return getFrame()->peek(); }

    // Constant pool operations
    /**
     * Loads the constant from the constant pool at index
     * @param index
     * @return the value
     */
    Obj *loadConst(uint16 index) const { return getFrame()->getConstPool()[index]->copy(); }

    // Code operations
    /**
     * Advances ip by 1 byte and returns the byte read
     * @return the byte
     */
    uint8 readByte() { return *getFrame()->ip++; }

    /**
     * Advances ip by 2 bytes and returns the bytes read
     * @return the short
     */
    uint16 readShort() {
        getFrame()->ip += 2;
        return (getFrame()->ip[-2] << 8) | getFrame()->ip[-1];
    }

    /**
     * Adjusts the ip by offset
     * @param offset
     */
    void adjust(ptrdiff_t offset) { getFrame()->ip += offset; }

    // Getters
    VM *getVM() const { return vm; }

    Frame *getCallStack() const { return callStack; }

    Frame *getFrame() const { return fp - 1; }

    void write(const string &str) { out << str; }

    string getOutput() { return out.str(); }

    uint16 getCallStackSize() { return fp - callStack; }

    uint32 getPc() { return getFrame()->ip - getFrame()->code; }

    void setPc(uint32 pc) { getFrame()->ip = getFrame()->code + pc; }
};

#endif //VELOCITY_STATE_HPP
