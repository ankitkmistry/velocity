#include <iostream>
#include "ee/vm.hpp"

int main() {
    try {
        VM vm;
        vm.start("H:\\Programming (Ankit)\\Projects\\spade\\1.0\\velocity\\fact.xp", {});
    } catch (const FatalError &error) {
        cout << "VM Error: " << error.what();
    }
}
