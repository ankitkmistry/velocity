#include "space.hpp"
#include "collector.hpp"

void *Space::allocate(size_t size) {
    return malloc(size);

    auto settings = manager->getVM()->getSettings();
    size_t units = (size + sizeof(Block) - 1) / sizeof(Block) + 1;
    auto requiredSize = units * sizeof(Block);
    if (base == null && !init(units))
        throw MemoryError(requiredSize);

    alloc:
    // obtain the largest free block
    auto block = getLargestFreeBlock();
    // if free block is big enough
    if (block != null && block->header.getSize() >= units) {
        // split the block and use tail end
        block->header.size -= units;
        block += block->header.size;
        block->header.size = units;
    } else
        switch (type) {
            case SpaceType::EDEN:
                // if above threshold
                if (totalSpace + requiredSize > settings.EDEN_THRESHOLD) {
                    GarbageCollector edenCollector{this};
                    // collect garbage in eden space
                    edenCollector.gc();
                    if (gcCount++ > settings.MAX_EDEN_GC) {
                        GarbageCollector survivorCollector{&manager->getSurvivor()};
                        // collect garbage in survivor space
                        survivorCollector.gc();
                        gcCount = 0;
                    }
                    // if enough memory was not collected
                    if (edenCollector.getCollectedMemory() < requiredSize) {
                        // increase the threshold
                        settings.EDEN_THRESHOLD += units;
                        // obtain from system
                        block = moreSpace(units);
                    } else // perform allocation again
                        goto alloc;
                } else // obtain from system
                    block = moreSpace(units);
                break;
            case SpaceType::SURVIVOR:
                // obtain from system
                block = moreSpace(units);
                break;
        }
    // if block was not obtained
    if (block == null) throw MemoryError(requiredSize);
    // set the block as used
    block->header.setFree(false);
    // increase the used space field
    usedSpace += requiredSize;
    return block;
}

Block *Space::moreSpace(size_t units) {
    auto size = units * sizeof(Block) * getManager()->getVM()->getSettings().HEAP_GROWTH_FACTOR;
    auto block = (Block *) malloc(size);
    if (block == null)return null;
    block->header = {-static_cast<int64>(units), null};
    take(block);
    return block;
}

bool Space::init(size_t units) {
    auto size = units * sizeof(Block) * getManager()->getVM()->getSettings().HEAP_GROWTH_FACTOR;
    base = (Block *) malloc(size);
    if (base == null)return false;
    base->header = {-static_cast<int64>(units), base};
    totalSpace = size;
    usedSpace = 0;
    return true;
}

Block *Space::getLargestFreeBlock() {
    Block *block = null;
    for (Block *p = base->header.next;; p = p->header.next) {
        if (p->header.isFree() && (block == null || p->header.size > block->header.size))
            block = p;
        if (p == base)break;
    }
    return block;
}

void Space::deallocate(void *pointer) {
    free(pointer);
    return;

    // get pointer to block
    auto bp = (Block *) pointer - 1;
    Block *p;
    // iterate over the free list
    for (p = base; !(bp > p && bp < p->header.next); p = p->header.next)
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

    p->header.setFree(true);
    usedSpace -= p->header.size * sizeof(Block);
}

void Space::take(Block *block) {
    auto *p1 = base;
    auto *p2 = p1->header.next;
    block->header.next = p2;
    p1->header.next = block;
    base = block;
    totalSpace += block->header.size;
    if (!block->header.isFree())usedSpace += block->header.size;
}
