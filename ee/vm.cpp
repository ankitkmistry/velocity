#include "vm.hpp"

VM::VM(Settings settings) : settings(std::move(settings)) {
    manager = new MemoryManager{this};
}

void VM::onExit(const function<void()> &fun) { onExitList.push_back(fun); }

int VM::start(const string &filename, const vector<string> &args) {
    // Load the file and get the entry point
    auto entry = loader.load(filename);
    // Complain if there is no entry point
    if (entry == null) throw EntryPointNotFoundError(filename);
    if (entry->getFrameTemplate()->getArgs().count() != 1)
        throw runtimeError("entry point must have one argument (string[]): " + entry->getSign().toString());
    // Execute from the entry
    return start(entry, argsRepr(args));
}

ObjArray *VM::argsRepr(const vector<string> &args) {
    auto array = new(manager) ObjArray(args.size());
    for (int i = 0; i < args.size(); ++i) {
        array->set(i, new(manager) ObjString(args[i]));
    }
    return array;
}

int VM::start(ObjMethod *entry, ObjArray *args) {
    VMState state{this};
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

ThrowSignal VM::runtimeError(const string &str) {
    return ThrowSignal{new(manager) ObjString(str)};
}

Obj *VM::getGlobal(const string &sign) const {
    try {
        return globals.at(sign);
    } catch (std::out_of_range &) {
        throw GlobalError(sign);
    }
}

void VM::setGlobal(const string &sign, Obj *val) {
    globals[sign] = val;
}

bool VM::checkCast(const Type *type1, const Type *type2) {
    // TODO implement this
    return false;
}
