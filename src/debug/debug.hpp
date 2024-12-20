#ifndef VELOCITY_DEBUG_HPP
#define VELOCITY_DEBUG_HPP

#include "../callable/frame.hpp"
#include "../ee/state.hpp"
#include "../utils/common.hpp"

namespace spade
{
    class DebugOp {
      private:
        static void clearConsole();

        static void printCallStack(VMState *state);

        static void printFrame(Frame *frame);

        static void printStack(Obj **stack, uint32 count);

        static void printExceptions(ExceptionTable exceptions);

        static void printCode(const uint8 *code, const uint8 *ip, const uint32 codeCount, const vector<Obj *> &pool,
                              LineNumberTable lineInfos);

        static void printLocals(const LocalsTable &locals);

        static void printArgs(const ArgsTable &args);

        static void printConstPool(const vector<Obj *> &pool);

      public:
        static void printVMState(VMState *state);

        //    static void printMemory(const Space &space);
    };
}    // namespace spade

#endif    // VELOCITY_DEBUG_HPP
