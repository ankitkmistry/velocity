#include "vm.hpp"

VM::VM(MemoryManager *manager_, Settings settings)
        : settings(std::move(settings)) {
    manager = manager_;
    manager->setVM(this);
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
    auto array = Obj::alloc<ObjArray>(manager, args.size());
    for (int i = 0; i < args.size(); ++i) {
        array->set(i, Obj::alloc<ObjString>(manager, args[i]));
    }
    return array;
}

int VM::start(ObjMethod *entry, ObjArray *args) {
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

ThrowSignal VM::runtimeError(const string &str) {
    return ThrowSignal{Obj::alloc<ObjString>(manager, str)};
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

VM *VM::current() {
    return Thread::current()->getState()->getVM();
}
