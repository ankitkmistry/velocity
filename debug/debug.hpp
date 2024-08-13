#ifndef VELOCITY_DEBUG_HPP
#define VELOCITY_DEBUG_HPP

#include "../utils/common.hpp"
#include "../ee/state.hpp"

class DebugOp {
private:
    static void clearConsole();

    static void printCallStack(VMState *state);

    static void printFrame(Frame *frame);

    static void printStack(Obj **stack, uint32 count);

    static void printLines(LineNumberTable lines);

    static void printExceptions(ExceptionTable exceptions);

    static void printCode(const uint8 *code, const uint8 *ip, const unsigned int codeCount, const vector<Obj *>& pool);

    static void printLocals(LocalsTable locals);

    static void printArgs(ArgsTable args);

    static void printConstPool(const vector<Obj *>& pool);

public:
    static void printVMState(VMState *state);

//    static void printMemory(const Space &space);
};

#endif //VELOCITY_DEBUG_HPP
