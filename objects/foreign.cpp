#include "foreign.hpp"

void ObjForeign::call(Thread *thread, vector<Obj *> args) {

}

void ObjForeign::call(Thread *thread, Obj **args) {

}

Obj *ObjForeign::copy() const {
    return null;
}

string ObjForeign::toString() const {
    static string kindNames[] = {
            "function",
            "method",
            "constructor"
    };
    return format("<foreign %s '%s'>", kindNames[kind].c_str(), sign.toString().c_str());
}
