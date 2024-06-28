#include "method.hpp"
#include "../frame/frame.hpp"
#include "../memory/memory.hpp"

static string kindNames[] = {
        "function",
        "method",
        "constructor"
};

Obj *ObjMethod::copy() const {
    return new(info.space->getManager()) ObjMethod(sign, kind, new Frame(*frame), type, typeParams, module, meta);
}

bool ObjMethod::truth() const {
    return true;
}

string ObjMethod::toString() const {
    return format("<%s '%s'>", kindNames[kind].c_str(), sign.toString().c_str());
}
