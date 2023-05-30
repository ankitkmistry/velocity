#ifndef VELOCITY_FRAME_TABLE_HPP
#define VELOCITY_FRAME_TABLE_HPP

#include <utility>

#include "../utils/utils.hpp"
#include "../oop/obj.hpp"

class TableNode {
protected:
    string name;
    Obj *value;
    Table<string> meta;
public:
    TableNode(const string &name, Obj *value, const Table<string> &meta) : name(name), value(value), meta(meta) {}

    TableNode &operator=(const TableNode &arg) = default;

    void setValue(Obj *val) { value = val; }

    const string &getName() const { return name; }

    Obj *getValue() const { return value; }

    const Table<string> &getMeta() const { return meta; }

    virtual string toString() const = 0;
};

class Arg : public TableNode {
    friend class ArgsTable;

    friend class VM;

public:
    enum Kind {
        VALUE,
        REF
    };
private:
    Kind kind;
public:
    Arg(Kind kind, string name, Obj *value, Table<string> &meta)
            : TableNode(name, value, meta), kind(kind) {}

    Arg &operator=(const Arg &arg) = default;

    Kind getKind() const { return kind; }

    string toString() const override;
};

class Local : public TableNode {
    friend class LocalsTable;

public:
    enum Kind {
        VAR,
        CONST
    };
private:
    Kind kind;
public:
    Local(Kind kind, string name, Obj *value, Table<string> &meta)
            : TableNode(name, value, meta), kind(kind) {}

    Local &operator=(const Local &local) = default;

    Kind getKind() const { return kind; }

    string toString() const override;
};

class Exception {
private:
    uint32 from, to, target;
    Type *type;
    Table<string> meta;
public:
    Exception(uint32 from, uint32 to, uint32 target, Type *type, Table<string> meta)
            : from(from), to(to),
              target(target),
              type(type),
              meta(std::move(meta)) {}

    Exception &operator=(const Exception &exception) = default;

    uint32 getFrom() const { return from; }

    uint32 getTo() const { return to; }

    uint32 getTarget() const { return target; }

    Type *getType() const { return type; }

    Table<string> getMeta() const { return meta; }

    static Exception NO_EXCEPTION() { return Exception(0, 0, 0, null, {}); }

    static bool IS_NO_EXCEPTION(const Exception &exception) { return exception.type == null; }
};

class LineNumberTable {
private:
    vector<uint32> bytecode;
    vector<uint64> sourcecode;
public:
    explicit LineNumberTable(size_t count) : bytecode(count), sourcecode(count) {}

    LineNumberTable(const LineNumberTable &table) = default;

    LineNumberTable &operator=(const LineNumberTable &lines) = default;

    void addLine(uint32 byteLine, uint64 sourceLine);

    uint64 getSourceLine(uint32 byteLine);

    const vector<uint32> &getBytecode() const { return bytecode; }

    const vector<uint64> &getSourcecode() const { return sourcecode; }

    size_t count() { return bytecode.capacity(); }
};

class ArgsTable {
    friend class GarbageCollector;

private:
    vector<Arg> args;
public:
    ArgsTable() : args() {}

    ArgsTable(const ArgsTable &table) = default;

    ArgsTable &operator=(const ArgsTable &argsTable) = default;

    void set(uint8 i, Obj *val) { args[i].value = val; }

    Obj *get(uint8 i) { return args[i].value; }

    void addArg(const Arg &arg) { args.push_back(arg); }

    Arg &getArg(uint8 i) { return args[i]; }

    uint8 count() { return args.size(); }

    string toString() const { return "(" + listToString(args) + ")"; }
};

class LocalsTable {
    friend class GarbageCollector;

private:
    uint16 closureStart;
    vector<Local> locals;
    vector<TableNode *> closures;

public:
    explicit LocalsTable(uint16 closureStart) : closureStart(closureStart), locals() {}

    LocalsTable(const LocalsTable &table) = default;

    LocalsTable &operator=(const LocalsTable &localsTable) = default;

    uint16 getClosureStart() const { return closureStart; }

    void set(uint16 i, Obj *val);

    Obj *get(uint16 i);

    void addLocal(const Local &local) { locals.push_back(local); }

    void addClosure(TableNode *local) { closures.push_back(local); }

    Local &getLocal(uint16 i) { return locals[i]; }

    TableNode* getClosure(uint16 i){ return closures[i]; }

    uint16 count() { return locals.size(); }

    string toString() const { return "(" + listToString(locals) + ")"; }
};

class ExceptionTable {
    friend class GarbageCollector;

private:
    vector<Exception> exceptions;
public:
    ExceptionTable() : exceptions() {}

    ExceptionTable(const ExceptionTable &table) = default;

    ExceptionTable &operator=(const ExceptionTable &table) = default;

    void addException(const Exception &exception) { exceptions.push_back(exception); }

    Exception &get(int i) { return exceptions[i]; }

    uint8 count() { return exceptions.size(); }

    Exception getTarget(uint32 pc, Type *type);
};

class KindStringInfo {
public:
    static string ofArg(Arg::Kind kind);

    static string ofLocal(Local::Kind kind);
};

#endif //VELOCITY_FRAME_TABLE_HPP
