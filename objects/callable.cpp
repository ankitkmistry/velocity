#include "callable.hpp"

static string kindNames[] = {
        "function",
        "method",
        "constructor"
};

string ObjCallable::toString() const {
    return format("<%s '%s'>", kindNames[kind].c_str(), sign.toString().c_str());
}
