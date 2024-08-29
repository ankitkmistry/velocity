#include "callable.hpp"
#include "../ee/vm.hpp"

Obj *ObjCallable::invoke(Thread *thread, vector<Obj *> args) {
    call(thread, args);
    return thread->getState()->getVM()->run(thread);
}

Obj *ObjCallable::getMember(const string &name) const {
    try {
        return getMembers().at(name);
    } catch (std::out_of_range &) {
        throw IllegalAccessError(format("cannot find member: %s in %s", name.c_str(), toString().c_str()));
    }
}

void ObjCallable::setMember(string name, Obj *obj) {
    getMembers()[name] = obj;
}
