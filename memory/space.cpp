#include "space.hpp"
#include "collector.hpp"

void *Space::allocate(size_t size) {
    auto settings = manager->getVM()->getSettings();
    Block *prev;
    size_t units = (size + sizeof(Block) - 1) / sizeof(Block) + 1;
    if ((prev = free) == null) { // No free list yet
        base = moreSpace(0);
        base->header.next = free = prev = base;
    }
    alloc:
    for (Block *p = prev->header.next;; prev = p, p = p->header.next) {
        if (p->header.isFree && p->header.size >= units) { // big enough
            if (p->header.size == units) // exactly
                prev->header.next = p->header.next;
            else { // allocate tail end
                p->header.size -= units; // decrease the size
                p += p->header.size; // move to the correct location
                p->header.size = units; // set the size of the block
            }
            free = prev;
            usedSpace += units * sizeof(Block);
            p->header.isFree = false;
            return (void *) (p + 1);
        }
        // wrapped around free list
        if (p == free) {
            if ((p = moreSpace(units)) != null) {
                prev->header.next = p;
                p->header.next = free;
                p = prev;
            } else
                switch (type) {
                    case SpaceType::EDEN:
                        if (mallocRequests > settings.MAX_MALLOC_REQUESTS) {
                            mallocRequests = 0;
                            if (gcCount > settings.MAX_EDEN_GC) {
                                gcCount = 0;
                                GarbageCollector collector1{this, manager->getVM()};
                                collector1.gc();
                                GarbageCollector collector2{&manager->getSurvivor(), manager->getVM()};
                                collector2.gc();
                            } else {
                                GarbageCollector collector{this, manager->getVM()};
                                collector.gc();
                                gcCount++;
                            }
                            goto alloc;
                        } else throw MemoryError(units * sizeof(Block));
                    case SpaceType::SURVIVOR:
                        throw MemoryError(units * sizeof(Block));
                }
        }
    }
}

Block *Space::moreSpace(size_t units) {
    mallocRequests++;
    auto block = (Block *) malloc(units * sizeof(Block));
    if (block)
        block->header = {true, units, null};
    return block;
}

void Space::deallocate(void *pointer) {
    // get pointer to block
    auto bp = (Block *) pointer - 1;
    Block *p;
    // iterate over the free list
    for (p = free; !(bp > p && bp < p->header.next); p = p->header.next)
        // check if the block was freed at the start or end of the arena
        if (p >= p->header.next && (bp > p || bp < p->header.next))
            break;

    Block *next = p->header.next;
    if (bp + bp->header.size == next) {
        // join current block to lower block
        bp->header.size += next->header.size;
        bp->header.next = next->header.next;
    } else
        bp->header.next = p->header.next;
    if (p + p->header.size == bp) {
        // join previous block with current block
        p->header.size += bp->header.size;
        p->header.next = bp->header.next;
    } else
        p->header.next = bp;

    p->header.isFree = true;
    free = p;
    freeSpace += p->header.size * sizeof(Block);
}

void Space::take(Block *block) {
    auto *p1 = base;
    auto *p2 = p1->header.next;
    block->header.next = p2;
    p1->header.next = block;
}
