#include "frame.hpp"

void Frame::push(Obj *val) {
    *sp++ = val;
}

Obj *Frame::pop() {
    return *--sp;
}

Obj *Frame::peek() {
    return sp[-1];
}
