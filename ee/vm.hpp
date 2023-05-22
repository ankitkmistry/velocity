#ifndef VELOCITY_VM_HPP
#define VELOCITY_VM_HPP

#include "../utils/common.hpp"
#include "../oop/obj.hpp"
#include "thread.hpp"
#include "../loader/loader.hpp"
#include "../oop/objects.hpp"
#include "../memory/memory.hpp"

class VM {
    friend class GarbageCollector;

private:
    Table<Obj *> globals;
    std::set<Thread *> threads;
    vector<function<void()>> onExitList;
    Loader loader{this};
    MemoryManager memoryManager{this};

public:
    VM() = default;

    void onExit(const function<void()> &fun);

    int start(const string &filename, const vector<string> &args);

    int start(ObjMethod *entry, ObjArray *args);

    runtime_error runtimeError(const string &str);

    Obj *getGlobal(const string &sign);

    void setGlobal(const string &sign, Obj *val);

    MemoryManager &getMemoryManager() { return memoryManager; }

private:
    Table<Obj *> getGlobals() const { return globals; }

    void run(Thread *thread);

    static bool checkCast(const Type *type1, const Type *type2);

    static void call(Thread *thread, ObjMethod *method, Obj **args);

    ObjArray *argsRepr(const vector<string> &args);
};


#endif //VELOCITY_VM_HPP
