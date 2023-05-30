#ifndef VELOCITY_STATE_HPP
#define VELOCITY_STATE_HPP

#include "../utils/common.hpp"
#include "../utils/utils.hpp"
#include "../frame/frame.hpp"

class VM;

class VMState {
private:
    VM *vm;
    uint8 *ip = null;
    Frame *callStack = null, *fp = null;
    std::stringstream out;
public:
    VMState(VM *vm, Frame *frame);

    ~VMState() {
        ip = null;
        callStack = fp = null;
        while (popFrame());
    }

    VMState(const VMState &state)
            : vm(state.vm), ip(state.ip),
              callStack(state.callStack), fp(state.fp),
              out(state.out.str()) {}

    // State operations
    /**
     * Sets the code and ip respectively and loads the state
     */
    void loadState();

    /**
     * Saves the code and ip to the frame
     */
    void storeState();

    // Frame operations
    /**
     * Pushes a call frame on top of the call stack
     * @param frame
     */
    void pushFrame(Frame *frame);

    /**
     * Pops the active call frame and reloads the state
     * @return the call frame
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
    uint8 readByte() { return *ip++; }

    /**
     * Advances ip by 2 bytes and returns the bytes read
     * @return the short
     */
    uint16 readShort() { return (ip += 2, (ip[-2] << 8) | ip[-1]); }

    /**
     * Adjusts the ip by offset
     * @param offset
     */
    void adjust(ptrdiff_t offset) { ip += offset; }

    // Getters
    VM *getVM() const { return vm; }

    uint8 *getIp() const { return ip; }

    Frame *getCallStack() const { return callStack; }

    Frame *getFrame() const { return fp - 1; }

    void write(const string &str) { out << str; }

    string getOutput() { return out.str(); }

    uint16 getCallStackSize() { return fp - callStack; }

    uint32 getPc() { return ip - getFrame()->code; }

    void setPc(uint32 pc){ ip = getFrame()->code + pc; }
};

#endif //VELOCITY_STATE_HPP
