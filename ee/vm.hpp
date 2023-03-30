#ifndef VELOCITY_VM_HPP
#define VELOCITY_VM_HPP

#include "../utils/common.hpp"
#include "../oop/obj.hpp"
#include "thread.hpp"
#include "../loader/loader.hpp"
#include "../oop/objects.hpp"

class VM {
private:
    Table<Obj *> globals;
    set<Thread*> threads;
    vector<function<void()>> onExitList;
    Loader loader = Loader(this);
public:
    VM() = default;

    void onExit(function<void()> fun);

    int start(const string &filename, vector<string> args);

    int start(ObjMethod *entry, ObjArray *args);

    static runtime_error runtimeError(string str);

    Obj *getGlobal(string sign);

    void setGlobal(string sign, Obj *val);

private:
    Table<Obj *> getGlobals() const { return globals; }

    void run(Thread *thread);

    static bool checkCast(const Type *type1, const Type *type2);

    void call(Thread *thread, ObjMethod *method, Obj **args);

    static ObjArray *argsRepr(const vector<string> &args);
};


#endif //VELOCITY_VM_HPP
