#include "vm.hpp"

SpadeVM::SpadeVM(MemoryManager *manager_, Settings settings)
        : settings(std::move(settings)) {
    manager = manager_;
    manager->setVM(this);
}

void SpadeVM::onExit(const function<void()> &fun) { onExitList.push_back(fun); }

int SpadeVM::start(const string &filename, const vector<string> &args) {
    // Load the file and get the entry point
    auto entry = loader.load(filename);
    // Complain if there is no entry point
    if (entry == null) throw IllegalAccessError(format("cannot find entry point in '%s'", filename.c_str()));
    if (entry->getFrameTemplate()->getArgs().count() != 1)
        throw runtimeError("entry point must have one argument (string[]): " + entry->getSign().toString());
    // Execute from the entry
    return start(entry, argsRepr(args));
}

ObjArray *SpadeVM::argsRepr(const vector<string> &args) {
    auto array = Obj::alloc<ObjArray>(manager, args.size());
    for (int i = 0; i < args.size(); ++i) {
        array->set(i, Obj::alloc<ObjString>(manager, args[i]));
    }
    return array;
}

int SpadeVM::start(ObjMethod *entry, ObjArray *args) {
    auto state = new VMState(this);
    Thread thread{state, [&](auto thr) {
        thr->setStatus(Thread::RUNNING);
        entry->call(&thread, {args});
        run(thr);
    }};
    threads.insert(&thread);
    thread.join();

    threads.erase(&thread);
    if (threads.empty()) {
        for (auto &item: onExitList)
            item();
        // Clean the globals
        // Clean the heap
    }
    return thread.getExitCode();
}

ThrowSignal SpadeVM::runtimeError(const string &str) {
    return ThrowSignal{Obj::alloc<ObjString>(manager, str)};
}

Obj *SpadeVM::getSymbol(const string &sign) const {
    Sign symbolSign{sign};
    vector<SignElement> elements = symbolSign.getElements();
    if (elements.empty())return Obj::alloc<ObjNull>(manager);
    Obj *acc;
    try {
        acc = modules.at(elements[0].getName());
        for (int i = 1; i < elements.size(); ++i) {
            if (is<Object *>(acc)) {
                auto object = cast<Object *>(acc);
                acc = object->getMember(elements[i].getName());
            } else if (is<Type *>(acc)) {
                auto type = cast<Type *>(acc);
                acc = type->getMember(elements[i].getName());
            } else if (i < elements.size() - 1) {
                throw IllegalAccessError(format("cannot find symbol: %s", sign.c_str()));
            }
        }
    } catch (const std::out_of_range &) {
        throw IllegalAccessError(format("cannot find symbol: %s", sign.c_str()));
    }
    return acc;
}

void SpadeVM::setSymbol(const string &sign, Obj *val) {
    Sign symbolSign{sign};
    vector<SignElement> elements = symbolSign.getElements();
    if (elements.empty())return;
    Obj *acc;
    try {
        acc = modules.at(elements[0].getName());
        for (int i = 1; i < elements.size(); ++i) {
            if (is<Object *>(acc)) {
                auto object = cast<Object *>(acc);
                if (i == elements.size() - 1) {
                    object->getMembers()[elements.back().getName()] = val;
                } else {
                    acc = object->getMember(elements[i].getName());
                }
            } else if (is<Type *>(acc)) {
                auto type = cast<Type *>(acc);
                if (i == elements.size() - 1) {
                    type->getMembers()[elements.back().getName()] = val;
                } else {
                    acc = type->getMember(elements[i].getName());
                }
            } else if (i < elements.size() - 1) {
                throw IllegalAccessError(format("cannot find symbol: %s", sign.c_str()));
            }
        }
    } catch (const std::out_of_range &) {
        throw IllegalAccessError(format("cannot find symbol: %s", sign.c_str()));
    }
}

bool SpadeVM::checkCast(const Type *type1, const Type *type2) {
    // TODO implement this
    return false;
}

SpadeVM *SpadeVM::current() {
    return Thread::current()->getState()->getVM();
}
