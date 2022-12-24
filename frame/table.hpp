#ifndef VELOCITY_TABLE_HPP
#define VELOCITY_TABLE_HPP

#include "../utils/utils.hpp"
#include "../oop/obj.hpp"

class Arg {
public:
    enum Kind {
        VALUE,
        REF
    };
private:
    Kind kind;
    string name;
    Obj *value;
    const Table<string> meta;
public:
    Arg(Kind kind, const string &name, Obj *value, const Table<string> &meta)
            : kind(kind), name(name), value(value), meta(meta) {}

    Kind getKind() const {
        return kind;
    }

    const string &getName() const {
        return name;
    }

    Obj *getValue() const {
        return value;
    }

    void setValue(Obj *value) {
        Arg::value = value;
    }

    const Table<string> &getMeta() const {
        return meta;
    }

    string toString() const;
};

class Local {
public:
    enum Kind {
        VAR,
        CONST
    };
private:
    Kind kind;
    string name;
    Obj *value;
    const Table<string> meta;
public:
    Local(Kind kind, const string &name, Obj *value, const Table<string> &meta)
            : kind(kind), name(name), value(value), meta(meta) {}

    Kind getKind() const {
        return kind;
    }

    const string &getName() const {
        return name;
    }

    Obj *getValue() const {
        return value;
    }

    void setValue(Obj *value) {
        Local::value = value;
    }

    const Table<string> &getMeta() const {
        return meta;
    }

    string toString() const;
};

class Exception {
private:
    int from, to, target;
    const Type *exception;
    const Table<string> meta;
public:
    Exception(int from, int to, int target, const Type *exception, const Table<string> &meta)
            : from(from), to(to),
              target(target),
              exception(exception),
              meta(meta) {}

    int getFrom() const {
        return from;
    }

    int getTo() const {
        return to;
    }

    int getTarget() const {
        return target;
    }

    const Type *getException() const {
        return exception;
    }

    const Table<string> &getMeta() const {
        return meta;
    }
};

class LineNumberTable {
private:
    vector<int> bytecode;
    vector<long> sourcecode;
public:
    explicit LineNumberTable(size_t count) : bytecode(count), sourcecode(count) {}

    LineNumberTable(const LineNumberTable &table) = default;

    void addLine(int byteLine, long sourceLine);

    long getSourceLine(int byteLine);

    const vector<int> &getBytecode() const {
        return bytecode;
    }

    const vector<long> &getSourcecode() const {
        return sourcecode;
    }

    size_t count() {
        return bytecode.capacity();
    }
};

class ArgsTable {
private:
    vector<Arg> args;
public:
    ArgsTable() : args() {}

    ArgsTable(const ArgsTable &table) : args(table.args) {}

    void set(uint8 i, Obj *val) { args[i].setValue(val); }

    Obj *get(uint8 i) { return args[i].getValue(); }

    void addArg(Arg arg) { args.push_back(arg); }

    Arg getArg(uint8 i) { return args[i]; }

    uint8 count() { return args.size(); }

    string toString() const { return "(" + listToString(args) + ")"; }
};

class LocalsTable {
private:
    const int closureStart;
    vector<Local> locals;
public:
    explicit LocalsTable(int closureStart) : closureStart(closureStart), locals() {}

    LocalsTable(const LocalsTable &table) : closureStart(table.closureStart), locals(table.locals) {}

    int getClosureStart() const {
        return closureStart;
    }

    void set(uint8 i, Obj *val) { locals[i].setValue(val); }

    Obj *get(uint8 i) { return locals[i].getValue(); }

    void addArg(Local arg) { locals.push_back(arg); }

    Local getArg(uint8 i) { return locals[i]; }

    uint8 count() { return locals.size(); }

    string toString() const { return "(" + listToString(locals) + ")"; }
};

class ExceptionTable {
private:
    vector<Exception> exceptions;
public:
    ExceptionTable() : exceptions() {}

    ExceptionTable(const ExceptionTable &table) : exceptions(table.exceptions) {}
};

#endif //VELOCITY_TABLE_HPP
