#include <iostream>

#include "ee/vm.hpp"
#include "memory/basic/manager.hpp"

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
        auto manager = new BasicMemoryManager;
        SpadeVM vm{manager};
#if defined(OS_LINUX)
        return vm.start("/mnt/d/Programming (Ankit)/Projects/spade/1.0/velocity/test_code/hello.elp", {});
#elif defined(OS_WINDOWS)
        return vm.start(R"(D:\Programming (Ankit)\Projects\spade\1.0\velocity\test_code\hello.elp)", {});
#endif
    } catch (const FatalError &error) {
        cout << "VM Error: " << error.what();
    }
}

int main() {
    std::ios_base::sync_with_stdio(true);
    cout << std::boolalpha;
    return runVM();
//    signTest();
}
