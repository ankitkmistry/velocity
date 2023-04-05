#include <iostream>
#include "ee/vm.hpp"

int main() {
//    std::ios_base::sync_with_stdio(false);
    try {
        VM vm;
        vm.start("H:\\Programming (Ankit)\\Projects\\spade\\1.0\\velocity\\fact.xp", {});
    } catch (const FatalError &error) {
        cout << "VM Error: " << error.what();
    }
}
