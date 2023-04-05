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

uint32 Frame::getPc() {
    return ip - code;
}

uint32 Frame::getStackCount() {
    return sp - stack + 1;
}

