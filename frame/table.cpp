#include "table.hpp"

void LineNumberTable::addLine(uint32 byteLine, uint64 sourceLine) {
    bytecode.push_back(byteLine);
    sourcecode.push_back(sourceLine);
}

uint64 LineNumberTable::getSourceLine(uint32 byteLine) {
    int i, j;
    i = j = 0;
    for (int line: bytecode) {
        i = j;
        j = line;
        if (i <= byteLine && byteLine < j)
            break;
    }
    return i;
}

Exception ExceptionTable::getTarget(uint32 pc, Type *type) {
    for (auto &exception: exceptions) {
        if (exception.getFrom() <= pc && pc < exception.getTo()
            && exception.getType() == type) {
            return exception;
        }
    }
    return Exception::NO_EXCEPTION();
}

void LocalsTable::set(uint16 i, Obj *val) {
    if (i >= closureStart)
        closures[i - closureStart]->setValue(val);
    else
        locals[i].value = val;
}

Obj *LocalsTable::get(uint16 i) {
    if (i >= closureStart)
        return closures[i - closureStart]->getValue();
    return locals[i].value;
}
