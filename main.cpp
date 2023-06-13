#include <iostream>
#include "ee/vm.hpp"

void runVM();

int main() {
    std::ios_base::sync_with_stdio(false);
    runVM();
}

void runVM() {
    try {
        VM vm;
#if defined(OS_LINUX)
        vm.start("/mnt/d/Programming (Ankit)/Projects/spade/1.0/velocity/fib.xp", {});
#elif defined(OS_WINDOWS)
        vm.start(R"(D:\Programming (Ankit)\Projects\spade\1.0\velocity\fib.xp)", {});
#endif
    } catch (const FatalError &error) {
        cout << "VM Error: " << error.what();
    }
}
