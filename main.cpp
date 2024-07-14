#include <iostream>

#include "ee/vm.hpp"
#include "loader/native_loader.hpp"

void runVM();

int main() {
    std::ios_base::sync_with_stdio(false);
    cout << std::boolalpha;
    runVM();
}

void runVM() {
    try {
//        VM vm;
        NativeLoader nativeLoader;
        auto lib = nativeLoader.loadSimpleLibrary("libstdc++.so");
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
