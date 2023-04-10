#ifndef VELOCITY_MEMORY_HPP
#define VELOCITY_MEMORY_HPP

#include "../utils/common.hpp"
#include <mutex>

#ifdef OS_LINUX

#include <unistd.h>

#endif

using word_t = std::intptr_t;

struct Block {
    // Block Header
    /**
     * Block size
     */
    size_t size;

    /**
     * Whether this block is currently used
     */
    uint8 used;

    /**
     * Next block in list
     */
    Block *next;

    // User data
    /**
     * Payload pointer
     * Points to the first word of the returning to the user value
     */
    word_t data[1];
};

/**
 * Mode for searching a free block.
 */
enum class SearchMode {
    FirstFit,
    NextFit,
    BestFit,
};


/**
 * Reset the heap to the original position.
 */
void resetHeap();

/**
 * Initializes the heap, and the search mode.
 */
void init(SearchMode mode);

// Word alignment for faster access and lesser cache miss

/**
 * Aligns the size by the machine word.
 */
inline size_t align(size_t n);

/**
 * Returns total allocation size, reserving in addition the space for
 * the Block structure (object header + first data word).
 *
 * Since the `word_t data[1]` already allocates one word inside the Block
 * structure, we decrease it from the size request: if a user allocates
 * only one word, it's fully in the Block struct.
 */
inline size_t allocSize(size_t size);

/**
 * Requests (maps) memory from OS.
 */
Block *requestFromOS(size_t size);

/**
 * Allocates a block of memory of (at least) `size` bytes.
 */
word_t *allocate(size_t size);

/**
 * Frees a previously allocated block.
 */
void deallocate(word_t *data);

/**
 * First-fit algorithm.
 *
 * Returns the first free block which fits the size.
 */
Block *firstFit(size_t size);

/**
 * Next-fit algorithm.
 *
 * Returns the next free block which fits the size.
 * Updates the `searchStart` of success.
 */
Block *nextFit(size_t size);

/**
 * Best-fit algorithm.
 *
 * Returns a free block which size fits the best.
 */
Block *bestFit(size_t size);

/**
 * Tries to find a block of a needed size.
 */
Block *findBlock(size_t size);

/**
 * Returns the object header.
 */
Block *getHeader(word_t *data);

/*void *operator new(size_t size) {

}

void operator delete(void *p) noexcept {

}*/

#endif //VELOCITY_MEMORY_HPP
