#include "memory.hpp"

static Block *heapStart;
static Block *top;

/**
 * Previously found block. Updated in `nextFit`.
 */
static Block *searchStart = heapStart;

/**
 * Current search mode.
 */
static auto searchMode = SearchMode::FirstFit;


size_t align(size_t n) {
    return (n + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
}

size_t allocSize(size_t size) {
    return size + sizeof(Block) - sizeof(std::declval<Block>().data);
}

Block *requestFromOS(size_t size) {
    // Current heap break.
    auto block = (Block *) sbrk(0);

    // OOM.
    if (sbrk(static_cast<word_t>(allocSize(size))) == (void *) -1) {
        return null;
    }

    return block;
}

word_t *allocate(size_t size) {
    // Align the size
    size = align(size);

    // ---------------------------------------------------------
    // 1. Search for an available free block:

    if (auto block = findBlock(size)) {
        return block->data;
    }

    // ---------------------------------------------------------
    // 2. If block not found in the free list, request from OS:

    auto block = requestFromOS(size);

    block->size = size;
    block->used = true;

    // Init heap.
    if (heapStart == null) {
        heapStart = block;
    }

    // Chain the blocks.
    if (top != null) {
        top->next = block;
    }

    top = block;

    // User payload:
    return block->data;
}

Block *firstFit(size_t size) {
    auto block = heapStart;

    while (block != nullptr) {
        // O(n) search.
        if (block->used || block->size < size) {
            block = block->next;
            continue;
        }

        // Found the block:
        return block;
    }

    return null;
}

Block *findBlock(size_t size) {
    switch (searchMode) {
        case SearchMode::FirstFit:
            return firstFit(size);
        case SearchMode::NextFit:
            return nextFit(size);
        case SearchMode::BestFit:
            return bestFit(size);
    }
}

Block *getHeader(word_t *data) {
    return (Block *) ((char *) data + sizeof(std::declval<Block>().data) -
                      sizeof(Block));
}

void deallocate(word_t *data) {
    auto block = getHeader(data);
    block->used = false;
}

void resetHeap() {
    // Already reset.
    if (heapStart == nullptr) {
        return;
    }

    // Roll back to the beginning.
    brk(heapStart);

    heapStart = nullptr;
    top = nullptr;
    searchStart = nullptr;
}

void init(SearchMode mode) {
    searchMode = mode;
    resetHeap();
}

Block *nextFit(size_t size) {
    // Implement here...
}

Block *bestFit(size_t size) {
    // Implement here...
}
