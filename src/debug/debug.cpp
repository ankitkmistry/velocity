#include "debug.hpp"
#include "../ee/vm.hpp"
#include "table.hpp"

namespace spade
{
    void DebugOp::clearConsole() {
#if defined(OS_WINDOWS)
        system("cls");
#elif defined(OS_LINUX) || defined(OS_MAC)
        system("clear");
#endif
    }

    void DebugOp::printVMState(VMState *state) {
        string dummy;
        // Clear the console
        clearConsole();
        // TODO Print memory
        // Print the call stack
        printCallStack(state);
        // Print the current frameTemplate
        printFrame(state->getFrame());
        // Print the output
        std::cout << "Output\n" << state->getVM()->getOutput() << "\n";
        // Wait for input
        std::getline(std::cin, dummy);
    }

    void DebugOp::printCallStack(VMState *state) {
        CallStackTable table;
        auto callStack = state->getCallStack();
        for (int i = state->getCallStackSize() - 1; i >= 0; i--) {
            auto frame = &callStack[i];
            table.add(i, frame->getMethod(), frame->getArgs(), state->getPc());
        }
        std::cout << table;
    }

    void DebugOp::printFrame(Frame *frame) {
        std::cout << "Method: " << frame->getMethod()->toString() << "\n";
        printConstPool(frame->getConstPool());
        std::cout << "\n";
        printArgs(frame->getArgs());
        printLocals(frame->getLocals());
        printStack(frame->stack, frame->getStackCount());
        std::cout << "\n";
        printCode(frame->code, frame->ip, frame->getCodeCount(), frame->getConstPool(), frame->getLines());
        std::cout << "\n";
        printExceptions(frame->getExceptions());
    }

    void DebugOp::printStack(Obj **stack, uint32 count) {
        vector<Obj *> items;
        items.reserve(count);
        for (int i = 0; i < count; ++i) items.push_back(stack[i]);
        std::cout << "Stack: [" << listToString(items) << "]\n";
    }

    void DebugOp::printExceptions(ExceptionTable exceptions) {
        if (exceptions.count() == 0) return;
        ExcTable table;
        for (int i = 0; i < exceptions.count(); ++i) {
            auto const &exception = exceptions.get(i);
            table.add(exception.getFrom(), exception.getTo(), exception.getTarget(), exception.getType());
        }
        std::cout << table;
    }

    void DebugOp::printCode(const uint8 *code, const uint8 *ip, const uint32 codeCount, const vector<Obj *> &pool,
                            LineNumberTable lineTable) {
        if (codeCount == 0) return;
        auto byteLineMaxLen = std::to_string(codeCount - 1).length();
        auto sourceLineMaxLen = std::to_string(lineTable.getLineInfos().back().sourceLine).length() + 2;
        uint64 sourceLine = 0;
        for (uint32 i = 0; i < codeCount;) {
            uint64 sourceLineTemp = lineTable.getSourceLine(i);
            string sourceLineStr;
            if (sourceLine != sourceLineTemp) {
                sourceLine = sourceLineTemp;
                sourceLineStr = padRight(std::to_string(sourceLine) + " |", sourceLineMaxLen);
            } else {
                sourceLineStr = padRight(" |", sourceLineMaxLen);
            }
            // Get the start of the line
            auto start = i;
            // Get the opcode
            auto opcode = static_cast<Opcode>(code[i++]);
            // The parameters of the opcode, if any
            string param;
            switch (OpcodeInfo::getParams(opcode)) {
                case 1: {
                    auto num = code[i++];
                    string valStr = OpcodeInfo::takeFromConstPool(opcode) ? std::format("({})", pool[num]->toString()) : "";
                    param = std::format("{} {}", num, valStr);
                    break;
                }
                case 2: {
                    auto num1 = code[i++];
                    auto num2 = code[i++];
                    auto num = (num1 << 8) | num2;
                    string valStr = OpcodeInfo::takeFromConstPool(opcode) ? std::format("({})", pool[num]->toString()) : "";
                    param = std::format("{} {}", num, valStr);
                    break;
                }
                default:
                    param = "";
                    break;
            }
            string finalStr = std::format(" {} {: >{}}: {} {} {}\n", (start == ip - code - 1 ? ">" : " "), start,
                                          byteLineMaxLen, sourceLineStr, OpcodeInfo::toString(opcode), param);
            std::cout << finalStr;
        }
    }

    void DebugOp::printLocals(const LocalsTable &locals) {
        if (locals.count() == 0) return;
        LocalVarTable table{locals.getClosureStart()};
        ClosureTable closure;
        uint8 i;
        for (i = 0; i < locals.getClosureStart(); ++i) {
            auto const &local = locals.getLocal(i);
            table.add(i, local->getName(), local->getValue());
        }
        for (uint8 j = 0; i < locals.count(); i++, j++) {
            auto node = locals.getClosure(i);
            closure.add(j, node->getName(), node->getValue());
        }
        std::cout << table;
        if (locals.getClosureStart() < locals.count()) std::cout << closure;
    }

    void DebugOp::printArgs(const ArgsTable &args) {
        if (args.count() == 0) return;
        ArgumentTable table;
        for (uint8 i = 0; i < args.count(); ++i) {
            auto arg = args.getArg(i);
            table.add(i, arg->getName(), arg->getValue());
        }
        std::cout << table;
    }

    void DebugOp::printConstPool(const vector<Obj *> &pool) {
        if (pool.empty()) return;
        auto max = std::to_string(pool.size() - 1).length();
        std::cout << "Constant Pool\n";
        std::cout << "-------------\n";
        for (int i = 0; i < pool.size(); ++i) { std::cout << std::format(" {: >{}d}: {}\n", i, max, pool.at(i)->toString()); }
    }
} // namespace spade
