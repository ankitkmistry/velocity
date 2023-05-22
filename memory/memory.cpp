#define GET_OBJ(block) ((Obj *) (block + 1))

#include "memory.hpp"
#include "../ee/vm.hpp"

void *Space::allocate(size_t size) {
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
                        if (mallocRequests > MAX_MALLOC_REQUESTS) {
                            mallocRequests = 0;
                            if (gcCount > MAX_EDEN_GC) {
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

void GarbageCollector::markRoots() {
    // mark the globals
    markTable(vm->globals);
    // mark the threads
    for (auto thread: vm->threads) markThread(thread);
}

void GarbageCollector::markTable(const Table<Obj *> &table) {
    for (auto [key, object]: table) {
        // mark every value in the table
        mark(object);
    }
}

void GarbageCollector::markThread(Thread *thread) {
    // mark the value of the thread
    mark((Obj *) thread->getValue());
    auto state = thread->getState();
    for (auto frame = state.getCallStack(); frame <= state.getFrame(); frame++) {
        // mark every frame
        markFrame(frame);
    }
}

void GarbageCollector::markFrame(Frame *frame) {
    for (auto constant: frame->getConstPool()) {
        // mark every constant of the constant pool
        mark(constant);
    }
    for (auto obj = *frame->getStack(); obj < *frame->getSp(); obj++) {
        // mark every object of stack
        mark(obj);
    }
    for (const auto &arg: frame->getArgs().args) {
        // mark every value of args
        auto obj = arg.getValue();
        mark(obj);
    }
    for (const auto &local: frame->getLocals().locals) {
        // mark every value of locals
        auto obj = local.getValue();
        mark(obj);
    }
    for (const auto &exception: frame->getExceptions().exceptions) {
        // mark every value of exceptions
        auto obj = exception.getType();
        mark((Obj *) obj);
    }
    mark((Obj *) frame->getMethod());
}

void GarbageCollector::mark(Obj *obj) {
    if (obj == null)return;
    if (obj->getInfo().marked)return;
    obj->getInfo().marked = true;
    grayMaterial.push_back(obj);
    mark((Obj *) obj->getType());
}

void GarbageCollector::traceReferences() {
    for (auto obj: grayMaterial) {
        if (is<ObjArray *>(obj)) {
            auto array = cast<ObjArray *>(obj);
            array->foreach([&](auto val) {
                // mark every value of the array
                mark(val);
            });
        } else if (is<Object *>(obj)) {
            auto object = cast<Object *>(obj);
            for (auto [name, member]: object->getMembers()) {
                // mark every member
                mark(member);
            }
        } else if (is<Type *>(obj)) {
            auto type = cast<Type *>(obj);
            for (auto constant: type->getConstPool()) {
                // mark every constant of the constant pool
                mark(constant);
            }
            for (auto typeParam: type->getTypeParams()) {
                // mark every type params
                mark((Obj *) typeParam);
            }
            for (auto [name, super]: type->getSupers()) {
                // mark every super class
                mark((Obj *) super);
            }
            for (auto [name, member]: type->getMembers()) {
                // mark every member
                mark(member);
            }
        }
    }
}

void GarbageCollector::sweep() {
    Block *previous = null;
    Block *current = space->base;
    while (true) {
        auto &info = GET_OBJ(current)->getInfo();
        if (info.marked) {
            info.marked = false;
            switch (space->type) {
                case SpaceType::EDEN:
                    if (info.life++ > MAX_LIFE_IN_EDEN) {
                        auto next = current->header.next;
                        vm->getMemoryManager().getSurvivor().take(current);
                        previous->header.next = next;
                        current = next;
                    } else {
                        previous = current;
                        current = current->header.next;
                    }
                    break;
                case SpaceType::SURVIVOR:
                    info.life++;
                    previous = current;
                    current = current->header.next;
                    break;
            }
        } else {
            auto unreached = current;
            current = current->header.next;
            if (previous)
                previous->header.next = current;
            space->deallocate(unreached);
        }
        if (current == space->base) break;
    }
}

