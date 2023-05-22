#include "frame.hpp"

void Frame::push(Obj *val) { *sp++ = val; }

Obj *Frame::pop() { return *--sp; }

Obj *Frame::peek() { return sp[-1]; }

uint32 Frame::getStackCount() { return sp - stack; }

uint32 Frame::getCodeCount() const { return codeCount; }

