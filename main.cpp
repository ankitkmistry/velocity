#include <iostream>

#include "ee/vm.hpp"

void runVM();

void signTest();

int main() {
    std::ios_base::sync_with_stdio(false);
    cout << std::boolalpha;
    // signTest();
    runVM();
}

void signTest() {
    Sign sign{".list.set<T>(rt!spade::lang.int, T)", 0};
    cout << "signature:  " << sign.getSignature() << "\n";
    cout << "library:    " << sign.getLibraryId() << "\n";
    cout << "package:    " << sign.getPkg() << "\n";
    cout << "name:       " << sign.getName() << "\n";
    cout << "args count: " << (int) sign.getArgsCount() << "\n";
    cout << "has args:   " << sign.isArgsPresent() << "\n";
}

void runVM() {
    try {
        VM vm;
#if defined(OS_LINUX)
        vm.start("/mnt/d/Programming (Ankit)/Projects/spade/1.0/velocity/fib.xp", {});
#elif defined(OS_WINDOWS)
        vm.start(R"(D:\Programming (Ankit)\Projects\spade\1.0\velocity\hello.xp)", {});
#endif
    } catch (const FatalError &error) {
        cout << "VM Error: " << error.what();
    }
}
