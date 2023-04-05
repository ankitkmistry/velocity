#include "debug.hpp"
#include "table.hpp"

void DebugOp::clearConsole() {
#if defined(OS_WINDOWS)
    system("cls");
#elif defined(OS_LINUX) || defined(OS_MAC)
    system("clear");
#endif
}

void DebugOp::printVMState(VMState state) {
    string dummy;
    // Clear the console
    clearConsole();
    // Print the call stack
    printCallStack(state.getCallStack(), state.getCallStackSize())
    // Print the frame
    printFrame(state.getFrame(), state);
    // Print the output
    cout << "Output\n" << state.getOut().str();
    // Wait for input
    cin >> dummy;
}

void DebugOp::printCallStack(Frame *callStack, uint16 count) {
    CallStackTable table;
    for (int i = count - 1; i >= 0; i--) {
        auto frame = &callStack[i];
        table.add(i,
                  frame->getMethod(),
                  frame->getArgs(),
                  frame->getPc());
    }
    cout << table;
}

void DebugOp::printFrame(Frame *frame, VMState state) {
    cout << "Method: " << frame->getMethod()->toString() << "\n";
    printConstPool(frame->getConstPool());
    cout << "\n";
    printArgs(frame->getArgs());
    printLocals(frame->getLocals());
    printStack(frame->getStack(), frame->getStackCount());
    cout << "\n";
    printCode(frame->getCode(), state.getIp(), frame->getConstPool());
    cout << "\n";
    printExceptions(frame->getExceptions());
    printLines(frame->getLines());
}


