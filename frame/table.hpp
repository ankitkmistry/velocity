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

    virtual string toString() const { return name; }
};

class Arg : public TableNode {
    friend class ArgsTable;

    friend class VM;

public:
    Arg(string name, Obj *value, Table<string> &meta)
            : TableNode(name, value, meta) {}

    Arg &operator=(const Arg &arg) = default;
};

class Local : public TableNode {
    friend class LocalsTable;

public:
    Local(string name, Obj *value, Table<string> &meta)
            : TableNode(name, value, meta) {}

    Local &operator=(const Local &local) = default;
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

class Case {
private:
    Obj *value;
    uint32 location;
public:
    Case(Obj *value, uint32 location) : value(value), location(location) {}

    Case &operator=(const Case &exception) = default;

    Obj *getValue() const { return value; }

    uint32 getLocation() const { return location; }
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

    TableNode *getClosure(uint16 i) { return closures[i]; }

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

class MatchTable {
    friend class GarbageCollector;

private:
    vector<Case> cases;
    uint32 defaultLocation;
public:
    MatchTable(const vector<Case> &cases, uint32 defaultLocation) : cases(cases), defaultLocation(defaultLocation) {}

    const vector<Case> &getCases() const { return cases; }

    uint32 getDefaultLocation() const { return defaultLocation; }

    size_t count() { return cases.size(); }

    uint32 perform(Obj *value) {
        // Todo improve this to perform fast matching in case of integer values
        for (auto kase: cases) {
            if (kase.getValue() == value)
                return kase.getLocation();
        }
        return defaultLocation;
    }
};

#endif //VELOCITY_FRAME_TABLE_HPP
