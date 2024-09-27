#include <iostream>

#include "ee/vm.hpp"
#include "memory/basic/basic_manager.hpp"

using namespace spade;

void signTest() {
    Sign sign1{"A::B"};
    cout << sign1.toString() << '\n';
    Sign sign2{"A::B.C"};
    cout << sign2.toString() << '\n';
    Sign sign3{"A::B.C()"};
    cout << sign3.toString() << '\n';
    Sign sign4{"A::B.C<T,V>"};
    cout << sign4.toString() << '\n';
    Sign sign5{"A::B.C<T>(A.int,A.str)"};
    cout << sign5.toString() << '\n';
    Sign sign6{"A.B"};
    cout << sign6.toString() << '\n';
    Sign sign7{".B"};
    cout << sign7.toString() << '\n';
    Sign sign8{".B(B.int)"};
    cout << sign8.toString() << '\n';
}

int runVM() {
    try {
        auto manager = new spade::basic::BasicMemoryManager;
        SpadeVM vm{manager};
#if defined(OS_LINUX)
        return vm.start("../test_code/fib.elp", {});
#elif defined(OS_WINDOWS)
        return vm.start("..\\test_code\\fib.elp", {});
#endif
    } catch (const FatalError &error) {
        cout << "VM Error: " << error.what();
        return 1;
    }
}

int main() {
    std::ios_base::sync_with_stdio(true);
    cout << std::boolalpha;
    return runVM();
    //    signTest();
}
