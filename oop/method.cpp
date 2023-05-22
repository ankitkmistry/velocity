#include "method.hpp"
#include "../frame/frame.hpp"
#include "../memory/memory.hpp"

static string kindNames[] = {
        "function",
        "method",
        "constructor"
};

Obj *ObjMethod::copy() const {
    return new (info.space->getManager()->getVM()) ObjMethod(sign, type, meta, kind, new Frame(*frame));
}

bool ObjMethod::truth() const {
    return true;
}

string ObjMethod::toString() const {
    return format("<%s '%s'>", kindNames[kind].c_str(), sign.toString().c_str());
}
