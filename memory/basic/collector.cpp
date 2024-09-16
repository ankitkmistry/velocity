#include "collector.hpp"
#include "../../ee/vm.hpp"

namespace spade::basic {
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
        // mark args
        for (int i = 0; i < frame->getArgs().count(); ++i) {
            const auto &arg = frame->getArgs().getArg(i);
            auto obj = arg->getValue();
            mark(obj);
        }
        // mark locals
        for (int i = 0; i < frame->getLocals().count(); ++i) {
            const auto &local = frame->getLocals().getLocal(i);
            auto obj = local->getValue();
            mark(obj);
        }
        // mark closures
        for (int i = 0; i < frame->getLocals().count(); ++i) {
            const auto &closure = frame->getLocals().getClosure(i);
            auto obj = closure->getValue();
            mark(obj);
        }
        // mark exceptions
        for (int i = 0; i < frame->getExceptions().count(); ++i) {
            const auto &exception = frame->getExceptions().get(i);
            auto obj = exception.getType();
            mark((Obj *) obj);
        }
        for (const auto &match: frame->getMatches()) {
            // mark every check
            for (const auto &kase: match.getCases()) {
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
                for (auto [name, member]: type->getMemberSlots()) {
                    // mark every member
                    mark(member.getValue());
                }
            } else {
                for (auto [name, member]: obj->getMemberSlots()) {
                    // mark every member
                    mark(member.getValue());
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
}
