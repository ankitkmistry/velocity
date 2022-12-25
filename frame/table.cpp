#include "table.hpp"

static const string argKindNames[] = {
        "value",
        "ref"
};

static const string localKindNames[] = {
        "var",
        "const"
};

string Arg::toString() const {
    return format("%s %s", argKindNames[kind].c_str(), name.c_str());
}


string Local::toString() const {
    return format("%s %s", localKindNames[kind].c_str(), name.c_str());
}

void LineNumberTable::addLine(int byteLine, long sourceLine) {
    bytecode.push_back(byteLine);
    sourcecode.push_back(sourceLine);
}

long LineNumberTable::getSourceLine(int byteLine) {
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

Exception ExceptionTable::getTarget(int pc, Type *type) {
    for (auto &exception: exceptions) {
        if (exception.getFrom() <= pc && pc < exception.getTo()
            && exception.getType() == type) {
            return exception;
        }
    }
    return Exception::NO_EXCEPTION();
}
