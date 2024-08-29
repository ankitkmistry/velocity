#include "table.hpp"

Obj *ArgsTable::get(uint8 i) const {
    if (i >= args.size())
        throw IndexError("argument", i);
    return args[i].getValue();
}

void ArgsTable::set(uint8 i, Obj *val) {
    if (i >= args.size())
        throw IndexError("argument", i);
    args[i].setValue(val);
}

Obj *LocalsTable::get(uint16 i) const {
    if (i >= closureStart)
        return getClosure(i)->getValue();
    return getLocal(i).getValue();
}

void LocalsTable::set(uint16 i, Obj *val) {
    if (i >= closureStart)
        getClosure(i)->setValue(val);
    else
        getLocal(i).setValue(val);
}

const Local &LocalsTable::getLocal(uint16 i) const {
    if (i >= locals.size())
        throw IndexError("local", i);
    return locals[i];
}

Local &LocalsTable::getLocal(uint16 i) {
    if (i >= locals.size())
        throw IndexError("local", i);
    return locals[i];
}

TableNode *LocalsTable::getClosure(uint16 i) const {
    if (i - closureStart >= closures.size())
        throw IndexError("closure", i - closureStart);
    return closures[i - closureStart];
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

ArgsTable ArgsTable::copy() const {
    ArgsTable newArgs;
    for (auto arg: args) {
//        newArgs.addArg(Arg(arg.getName(), Obj::createCopy(arg.getValue()), arg.getMeta()));
        newArgs.addArg(Arg(arg.getName(), arg.getValue(), arg.getMeta()));
    }
    newArgs.args.shrink_to_fit();
    return newArgs;
}

LocalsTable LocalsTable::copy() const {
    LocalsTable newLocals{closureStart};
    for (auto local: locals) {
//        newLocals.addLocal(Local(local.getName(), Obj::createCopy(local.getValue()), local.getMeta()));
        newLocals.addLocal(Local(local.getName(), local.getValue(), local.getMeta()));
    }
    newLocals.locals.shrink_to_fit();
    for (auto closure: closures) {
        newLocals.addClosure(closure);
    }
    newLocals.closures.shrink_to_fit();
    return newLocals;
}
