#ifndef VELOCITY_VM_HPP
#define VELOCITY_VM_HPP

#include "../utils/common.hpp"
#include "thread.hpp"
#include "../oop/obj.hpp"
#include "../oop/objects.hpp"
#include "../loader/loader.hpp"
#include "../memory/memory.hpp"
#include "settings.hpp"

class VM {
    friend class GarbageCollector;

private:
    Table<Obj *> globals;
    std::set<Thread *> threads;
    vector<function<void()>> onExitList;
    Loader loader{this};
    MemoryManager memoryManager{this};
    Settings settings;

public:
    explicit VM(Settings settings = {}) : settings(std::move(settings)) {}

    void onExit(const function<void()> &fun);

    int start(const string &filename, const vector<string> &args);

    int start(ObjMethod *entry, ObjArray *args);

    ThrowSignal runtimeError(const string &str);

    Obj *getGlobal(const string &sign);

    void setGlobal(const string &sign, Obj *val);

    Settings &getSettings() { return settings; }

    MemoryManager &getMemoryManager() { return memoryManager; }

private:
    Table<Obj *> getGlobals() const { return globals; }

    void run(Thread *thread);

    static bool checkCast(const Type *type1, const Type *type2);

    static void call(Thread *thread, ObjMethod *method, Obj **args);

    ObjArray *argsRepr(const vector<string> &args);
};


#endif //VELOCITY_VM_HPP
