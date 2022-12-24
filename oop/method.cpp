//
// Created by ajitkmistry on 24-12-2022.
//

#include "method.hpp"
#include "../frame/frame.hpp"

static string kindNames[] = {
        "function",
        "method",
        "constructor"
};

Obj *ObjMethod::copy() const {
    return new ObjMethod(sign, type, meta, kind, new Frame(frame));
}

bool ObjMethod::truth() const {
    return true;
}

string ObjMethod::toString() const {
    return format("<%s '%s'>", kindNames[kind].c_str(), sign.toString().c_str());
}
