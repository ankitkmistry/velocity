#include "table.hpp"

static const string argKindNames[] = {
        "VALUE",
        "REF"
};

static const string localKindNames[] = {
        "VAR",
        "CONST"
};

string Arg::toString() const {
    return format("%s %s", argKindNames[kind].c_str(), name.c_str());
}


string Local::toString() const {
    return format("%s %s", localKindNames[kind].c_str(), name.c_str());
}

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

string KindStringInfo::ofArg(Arg::Kind kind) {
    return argKindNames[kind];
}

string KindStringInfo::ofLocal(Local::Kind kind) {
    return localKindNames[kind];
}
