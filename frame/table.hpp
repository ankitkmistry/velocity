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

    void setValue(Obj *val) {
        value = val;
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

    void setValue(Obj *val) {
        Local::value = val;
    }

    const Table<string> &getMeta() const {
        return meta;
    }

    string toString() const;
};

class Exception {
private:
    uint32 from, to, target;
    const Type *type;
    const Table<string> meta;
public:
    Exception(uint32 from, uint32 to, uint32 target, const Type *type, const Table<string> &meta)
            : from(from), to(to),
              target(target),
              type(type),
              meta(meta) {}

    uint32 getFrom() const {
        return from;
    }

    uint32 getTo() const {
        return to;
    }

    uint32 getTarget() const {
        return target;
    }

    const Type *getType() const {
        return type;
    }

    const Table<string> &getMeta() const {
        return meta;
    }

    static Exception NO_EXCEPTION() { return Exception(0, 0, 0, null, {}); }

    static bool IS_NO_EXCEPTION(const Exception &exception) { return exception.type == null; }
};

class LineNumberTable {
private:
    vector<int> bytecode;
    vector<long> sourcecode;
public:
    explicit LineNumberTable(size_t count) : bytecode(count), sourcecode(count) {}

    LineNumberTable(const LineNumberTable &table) = default;

    LineNumberTable &operator=(const LineNumberTable &lines) = default;

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

    ArgsTable(const ArgsTable &table) = default;

    ArgsTable &operator=(const ArgsTable &argsTable) = default;

    void set(uint8 i, Obj *val) { args[i].setValue(val); }

    Obj *get(uint8 i) { return args[i].getValue(); }

    void addArg(Arg arg) { args.push_back(arg); }

    Arg getArg(uint8 i) { return args[i]; }

    uint8 count() { return args.size(); }

    string toString() const { return "(" + listToString(args) + ")"; }
};

class LocalsTable {
private:
    int closureStart;
    vector<Local> locals;
public:
    explicit LocalsTable(int closureStart) : closureStart(closureStart), locals() {}

    LocalsTable(const LocalsTable &table) = default;

    LocalsTable &operator=(const LocalsTable &localsTable) = default;

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

    ExceptionTable(const ExceptionTable &table) = default;

    ExceptionTable &operator=(const ExceptionTable &table) = default;

    void addException(Exception &exception) { exceptions.push_back(exception); }

    Exception &get(int i) { return exceptions[i]; }

    uint8 count() { return exceptions.size(); }

    Exception getTarget(int pc, Type *exception);
};

#endif //VELOCITY_TABLE_HPP
