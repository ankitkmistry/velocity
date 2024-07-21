#include "table.hpp"

void LineNumberTable::addLine(uint32 byteLine, uint64 sourceLine) {
    bytecode.push_back(byteLine);
    sourcecode.push_back(sourceLine);
}

uint64 LineNumberTable::getSourceLine(uint32 byteLine) const {
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

Exception ExceptionTable::getTarget(uint32 pc, Type *type) const {
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

Obj *LocalsTable::get(uint16 i) const {
    if (i >= closureStart)
        return closures[i - closureStart]->getValue();
    return locals[i].value;
}

const Local & LocalsTable::getLocal(uint16 i) const {
    // TODO: FATAL ERROR
    // if (i >= closureStart) FATAL_ERROR();
    return locals[i];
}

TableNode *LocalsTable::getClosure(uint16 i) const {
    // TODO: FATAL ERROR
    // if (i-closureStart >= closures.size()) FATAL_ERROR();
    return closures[i - closureStart];
}

uint32 MatchTable::perform(Obj *value) {
    // Info: improve this to perform fast matching in case of integer values
    if (is<ObjInt *>(value)) {
        auto val = cast<ObjInt *>(value)->value();
        return cases[val].getLocation();
    }
    for (auto kase: cases) {
        if (kase.getValue() == value)
            return kase.getLocation();
    }
    return defaultLocation;
}
