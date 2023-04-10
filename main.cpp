#include <iostream>
#include <cassert>
#include "ee/vm.hpp"
#include "ee/memory.hpp"

void runVM();

int main() {
    std::ios_base::sync_with_stdio(false);
//    runVM();
    // --------------------------------------
    // Test case 1: Alignment
    //
    // A request for 3 bytes is aligned to 8.
    //

    auto p1 = allocate(3);
    auto p1b = getHeader(p1);
    assert(p1b->size == sizeof(word_t));

    // --------------------------------------
    // Test case 2: Exact amount of aligned bytes
    //

    auto p2 = allocate(8);
    auto p2b = getHeader(p2);
    assert(p2b->size == 8);

    // --------------------------------------
    // Test case 3: Free the object
    //

    deallocate(p2);
    assert(p2b->used == false);

    // --------------------------------------
    // Test case 4: The block is reused
    //
    // A consequent allocation of the same size reuses
    // the previously freed block.
    //

    auto p3 = allocate(8);
    auto p3b = getHeader(p3);
    assert(p3b->size == 8);
    assert(p3b == p2b);  // Reused!

    puts("\nAll assertions passed!\n");
}

void runVM() {
    try {
        VM vm;
#if defined(OS_LINUX)
        vm.start("/mnt/d/Programming (Ankit)/Projects/spade/1.0/velocity/fact.xp", {});
#elif defined(OS_WINDOWS)
        vm.start(R"(D:\Programming (Ankit)\Projects\spade\1.0\velocity\fact.xp)", {});
#endif
    } catch (const FatalError &error) {
        cout << "VM Error: " << error.what();
    }
}
