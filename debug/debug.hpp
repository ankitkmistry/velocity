#ifndef VELOCITY_DEBUG_HPP
#define VELOCITY_DEBUG_HPP

#include "../utils/common.hpp"
#include "../ee/state.hpp"

class DebugOp {
private:
    static void clearConsole();

    static void printCallStack(Frame *callStack, uint16 i);

    static void printFrame(Frame *frame, VMState state);

    static void printStack(Obj **pObj, uint32 i);

    static void printLines(LineNumberTable table);

    static void printExceptions(ExceptionTable table);

    static void printCode(uint8 *string1, uint8 *string2, const vector<Obj *> vector1);

    static void printLocals(LocalsTable table);

    static void printArgs(ArgsTable table);

    static void printConstPool(const vector<Obj *> vector1);

public:
    static void printVMState(VMState state);
};

#endif //VELOCITY_DEBUG_HPP
