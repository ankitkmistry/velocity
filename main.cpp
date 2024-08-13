#include <iostream>

#include "ee/vm.hpp"
#include "loader/foreign_loader.hpp"
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

void runVM() {
    try {
        VM vm{new BasicMemoryManager};
        ForeignLoader foreignLoader;
        auto lib = foreignLoader.loadSimpleLibrary("mscvrt.dll");
        cout << (intptr) lib->call<void *>("malloc", 64) << '\n';
#if defined(OS_LINUX)
        //        vm.start("/mnt/d/Programming (Ankit)/Projects/spade/1.0/velocity/hello.xp", {});
#elif defined(OS_WINDOWS)
        //        vm.start(R"(D:\Programming (Ankit)\Projects\spade\1.0\velocity\hello.xp)", {});
#endif
    } catch (const FatalError &error) {
        cout << "VM Error: " << error.what();
    }
}

int main() {
    std::ios_base::sync_with_stdio(true);
    cout << std::boolalpha;
    runVM();
//    signTest();
}
