#include "collector.hpp"
#include "../../ee/vm.hpp"

void BasicCollector::gc() {
    markRoots();
    traceReferences();
    sweep();
}

void BasicCollector::markRoots() {
    auto vm = manager->getVM();
    // mark the globals
    for (auto [key, object]: vm->getModules()) {
        mark(object);
    }
    // mark the threads
    for (auto thread: vm->getThreads()) markThread(thread);
}

void BasicCollector::markTable(const Table<Obj *> &table) {
    for (auto [key, object]: table) {
        // mark every value in the table
        mark(object);
    }
}

void BasicCollector::markThread(Thread *thread) {
    // mark the value of the thread
    mark((Obj *) thread->getValue());
    auto state = thread->getState();
    for (auto frame = state->getCallStack(); frame <= state->getFrame(); frame++) {
        // mark every frameTemplate
        markFrame(frame);
    }
}

void BasicCollector::markFrame(Frame *frame) {
    for (auto constant: frame->getConstPool()) {
        // mark every constant of the constant pool
        mark(constant);
    }
    for (auto obj = *frame->stack; obj < *frame->sp; obj++) {
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
    for (const auto &closure: frame->getLocals().closures) {
        // mark every value of closures
        auto obj = closure->getValue();
        mark(obj);
    }
    for (const auto &exception: frame->getExceptions().exceptions) {
        // mark every value of exceptions
        auto obj = exception.getType();
        mark((Obj *) obj);
    }
    for (const auto &match: frame->getMatches()) {
        // mark every check
        for (const auto &kase: match.cases) {
            // mark every case value
            auto obj = kase.getValue();
            mark(obj);
        }
    }
    mark((Obj *) frame->getMethod());
    for (auto typeParam: frame->getMethod()->getTypeParams()) {
        // mark every type param
        mark((Obj *) typeParam);
    }
}

void BasicCollector::mark(Obj *obj) {
    if (obj == null)return;
    if (obj->getInfo().marked)return;
    obj->getInfo().marked = true;
    grayMaterial.push_back(obj);
    mark(obj->getModule());
    mark((Obj *) obj->getType());
}

void BasicCollector::traceReferences() {
    for (auto obj: grayMaterial) {
        if (is<ObjArray *>(obj)) {
            auto array = cast<ObjArray *>(obj);
            array->foreach([&](auto val) {
                // mark every value of the array
                mark(val);
            });
        } else if (is<Type *>(obj)) {
            auto type = cast<Type *>(obj);
            for (auto typeParam: type->getTypeParams()) {
                // mark every type param
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
        } else {
            for (auto [name, member]: obj->getMembers()) {
                // mark every member
                mark(member);
            }
        }
    }
}

void BasicCollector::sweep() {
    LNode *previous = null;
    LNode *current = manager->head;
    while (current != null) {
        auto &info = current->data->getInfo();
        if (info.marked) {
            info.marked = false;
            info.life++;
            previous = current;
            current = current->next;
        } else {
            auto unreached = current;
            current = current->next;
            if (previous != null) previous->next = current;
            Obj::free(unreached->data);
            manager->deallocate(unreached);
        }
    }
}
/*auto settings = vm->settings;
Block *previous = null;
Block *current = space->base;
while (true) {
    auto &info = GET_OBJ(current)->getInfo();
    if (info.marked) {
        info.marked = false;
        switch (space->type) {
            case SpaceType::EDEN:
                // TODO Change this
                *//*if (info.life++ > settings.MAX_LIFE_IN_EDEN) {
                        auto next = current->header.next;
                        vm->getMemoryManager()->getSurvivor().take(current);
                        previous->header.next = next;
                        current = next;
                    } else {
                        previous = current;
                        current = current->header.next;
                    }*//*
                    info.life++;
                    previous = current;
                    current = current->header.next;
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
            if (previous != null) previous->header.next = current;
            collected += unreached->header.size;
            space->deallocate(unreached);
        }
        if (current == space->base) break;
    }*/
