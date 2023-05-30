#include "debug.hpp"
#include "table.hpp"
#include "../ee/opcode.hpp"
#include "../ee/vm.hpp"

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
    // Print eden space
    printMemory(state->getVM()->getMemoryManager().getEden());
    cout << "\n";
    // Print survivor space
    printMemory(state->getVM()->getMemoryManager().getSurvivor());
    cout << "\n";
    // Print the call stack
    printCallStack(state);
    // Print the current frame
    printFrame(state->getFrame(), state);
    // Print the output
    cout << "Output\n" << state->getOutput() << "\n";
    // Wait for input
    std::getline(cin, dummy);
}

void DebugOp::printCallStack(VMState *state) {
    CallStackTable table;
    auto callStack = state->getCallStack();
    for (int i = state->getCallStackSize() - 1; i >= 0; i--) {
        auto frame = &callStack[i];
        table.add(i,
                  frame->getMethod(),
                  frame->getArgs(),
                  state->getPc());
    }
    cout << table;
}

void DebugOp::printFrame(Frame *frame, const VMState *state) {
    cout << "Method: " << frame->getMethod()->toString() << "\n";
    printConstPool(frame->getConstPool());
    cout << "\n";
    printArgs(frame->getArgs());
    printLocals(frame->getLocals());
    printStack(frame->getStack(), frame->getStackCount());
    cout << "\n";
    printCode(frame->getCode(), state->getIp(), frame->getCodeCount(), frame->getConstPool());
    cout << "\n";
    printExceptions(frame->getExceptions());
    printLines(frame->getLines());
}

void DebugOp::printStack(Obj **stack, uint32 count) {
    vector<Obj *> items;
    items.reserve(count);
    for (int i = 0; i < count; ++i) {
        items.push_back(stack[i]);
    }
    cout << "Stack [" << listToString(items) << "]\n";
}

void DebugOp::printLines(LineNumberTable lines) {
    if (lines.count() == 0)return;
    auto byteLines = lines.getBytecode();
    auto sourceLines = lines.getSourcecode();
    LineDataTable table;
    for (int i = 0; i < lines.count(); ++i) {
        table.add(byteLines[i], sourceLines[i]);
    }
    cout << table;
}

void DebugOp::printExceptions(ExceptionTable exceptions) {
    if (exceptions.count() == 0)return;
    ExcTable table;
    for (int i = 0; i < exceptions.count(); ++i) {
        auto exception = exceptions.get(i);
        table.add(exception.getFrom(), exception.getTo(), exception.getTarget(), exception.getType());
    }
    cout << table;
}

void DebugOp::printCode(const uint8 *code, const uint8 *ip, const uint32 codeCount, const vector<Obj *> &pool) {
    if (codeCount == 0)return;
    auto max = std::to_string(codeCount - 1).length();
    for (uint32 i = 0; i < codeCount;) {
        // Get the index
        auto index = i;
        // Get the opcode
        auto opcode = static_cast<Opcode>(code[i++]);
        // The parameters of the opcode, if any
        string param;
        switch (OpcodeInfo::getParams(opcode)) {
            case 1: {
                auto num = code[i++];
                string valStr = OpcodeInfo::takeFromConstPool(opcode)
                                ? format("(%s)", pool[num]->toString().c_str())
                                : "";
                param = format("%d %s", num, valStr.c_str());
                break;
            }
            case 2: {
                auto num1 = code[i++];
                auto num2 = code[i++];
                auto num = (num1 << 8) | num2;
                string valStr = OpcodeInfo::takeFromConstPool(opcode)
                                ? format("(%s)", pool[num]->toString().c_str())
                                : "";
                param = format("%d %s", num, valStr.c_str());
                break;
            }
            default:
                param = "";
                break;
        }
        cout << format(" %s %s: %s %s\n",
                       (index == ip - code - 1 ? ">" : " "),
                       padRight(std::to_string(index), max).c_str(),
                       OpcodeInfo::toString(opcode).c_str(),
                       param.c_str());
    }
}

void DebugOp::printLocals(LocalsTable locals) {
    if (locals.count() == 0)return;
    LocalVarTable table{locals.getClosureStart()};
    ClosureTable closure;
    int i;
    for (i = 0; i < locals.getClosureStart(); ++i) {
        auto local = locals.getLocal(i);
        table.add(i, local.getKind(), local.getName(), local.getValue());
    }
    for (int j = 0; i < locals.count(); i++, j++) {
        auto node = locals.getClosure(i);
        if (is<Local *>(node)) {
            auto local = cast<Local *>(node);
            closure.add(i, true, local->getKind(), local->getName(), local->getValue());
        } else {
            auto arg = cast<Arg *>(node);
            closure.add(i, false, arg->getKind(), arg->getName(), arg->getValue());
        }
    }
    cout << table;
    if (locals.getClosureStart() < locals.count())
        cout << closure;
}

void DebugOp::printArgs(ArgsTable args) {
    if (args.count() == 0)return;
    ArgumentTable table;
    for (int i = 0; i < args.count(); ++i) {
        auto arg = args.getArg(i);
        table.add(i, arg.getKind(), arg.getName(), arg.getValue());
    }
    cout << table;
}

void DebugOp::printConstPool(const vector<Obj *> &pool) {
    if (pool.empty())return;
    auto max = std::to_string(pool.size() - 1).length();
    cout << "Constant Pool\n";
    cout << "-------------\n";
    for (int i = 0; i < pool.size(); ++i) {
        cout << format(" %s: %s\n",
                       padRight(std::to_string(i), max).c_str(),
                       pool.at(i)->toString().c_str());
    }
}

void DebugOp::printMemory(Space &space) {
    if (space.getTotalSpace() == 0)return;
    switch (space.getType()) {
        case SpaceType::EDEN:
            cout << "Eden Space\n";
            cout << "----------\n";
            break;
        case SpaceType::SURVIVOR:
            cout << "Survivor Space\n";
            cout << "--------------\n";
            break;
    }
    cout << "gc count:        " << space.getGcCount() << "\n";
    cout << "used space:      " << space.getUsedSpace() << " bytes\n";
    cout << "free space:      " << space.getFreeSpace() << " bytes\n";
    cout << "total space:     " << space.getTotalSpace() << " bytes\n";
}






