#ifndef VELOCITY_FRAME_TABLE_HPP
#define VELOCITY_FRAME_TABLE_HPP

#include <utility>

#include "../utils/utils.hpp"
#include "../objects/obj.hpp"
#include "../objects/inbuilt_types.hpp"

/**
 * Represents the base class for nodes used in arg tables, local tables, etc.
 */
class TableNode {
protected:
    string name;
    Obj *value;
    Table<string> meta;
public:
    TableNode(const string &name, Obj *value, const Table<string> &meta) : name(name), value(value), meta(meta) {}

    TableNode &operator=(const TableNode &arg) = default;

    /**
     * Sets the value of the node
     * @param val
     */
    void setValue(Obj *val) { value = val; }

    /**
     * @return The name attached to the node
     */
    const string &getName() const { return name; }

    /**
     * @return The value of the node
     */
    Obj *getValue() const { return value; }

    /**
     * @return The meta data associated to the node
     */
    const Table<string> &getMeta() const { return meta; }

    /**
     * @return The string representation of the node
     */
    virtual string toString() const { return name; }
};

/**
 * Represents a function argument
 */
class Arg : public TableNode {
    friend class VM;

public:
    Arg(string name, Obj *value, Table<string> meta)
            : TableNode(name, value, meta) {}

    Arg &operator=(const Arg &arg) = default;
};

/**
 * Represents a local
 */
class Local : public TableNode {
public:
    Local(string name, Obj *value, Table<string> meta)
            : TableNode(name, value, meta) {}

    Local &operator=(const Local &local) = default;
};

/**
 * Represents an exception in the exception table
 */
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

    /**
     * @return The starting point <i>(of the try statement in code)</i>
     */
    uint32 getFrom() const { return from; }

    /**
     * @return The ending point <i>(of the try statement in code)</i>
     */
    uint32 getTo() const { return to; }

    /**
     * @return The target point <i>(or the starting of the catch block)</i>
     */
    uint32 getTarget() const { return target; }

    /**
     * @return The object representing the type of the exception
     */
    Type *getType() const { return type; }

    /**
     * Sets the exception object of the exception handle
     * @param type_ the exception type object
     */
    void setType(Type *type_) { type = type_; }

    /**
     * @return The meta data associated to the node
     */
    Table<string> getMeta() const { return meta; }

    static Exception NO_EXCEPTION() { return Exception(0, 0, 0, null, {}); }

    static bool IS_NO_EXCEPTION(const Exception &exception) { return exception.type == null; }
};

/**
 * Represents a case in a check statement
 */
class Case {
private:
    Obj *value;
    uint32 location;
public:
    Case(Obj *value, uint32 location) : value(value), location(location) {}

    Case &operator=(const Case &exception) = default;

    /**
     * @return The value to be matched
     */
    Obj *getValue() const { return value; }

    /**
     * @return The destination location in the code
     */
    uint32 getLocation() const { return location; }
};

/**
 * Represents the argument table
 */
class ArgsTable {
    friend class GarbageCollector;

    friend class FrameTemplate;

private:
    vector<Arg> args;
public:
    ArgsTable() : args() {}

    ArgsTable(const ArgsTable &table) = default;

    ArgsTable &operator=(const ArgsTable &argsTable) = default;

    /**
     * Sets the value of the argument at index i to val
     * @param i the argument index
     * @param val value to be changed
     */
    void set(uint8 i, Obj *val);

    /**
     * @return The value of the argument at index i
     * @param i the argument index
     */
    Obj *get(uint8 i) const;

    /**
     * Adds a new argument at the end of the table
     * @param arg the argument to be added
     */
    void addArg(const Arg &arg) { args.push_back(arg); }

    /**
     * @return The argument at index i
     * @param i the argument index
     */
    const Arg &getArg(uint8 i) const { return args[i]; }

    ArgsTable copy() const;

    /**
     * @return The total number of arguments present
     */
    uint8 count() const { return args.size(); }

    /**
     * @return The string representation of the table
     */
    string toString() const { return "(" + listToString(args) + ")"; }
};

/**
 * Represents the locals table
 */
class LocalsTable {
    friend class GarbageCollector;

    friend class FrameTemplate;

private:
    uint16 closureStart;
    vector<Local> locals;
    vector<TableNode *> closures;

public:
    explicit LocalsTable(uint16 closureStart) : closureStart(closureStart), locals() {}

    LocalsTable(const LocalsTable &table) = default;

    LocalsTable &operator=(const LocalsTable &localsTable) = default;

    /**
     * @return The index of the locals table starting from which closures are stored up to the end of the table
     */
    uint16 getClosureStart() const { return closureStart; }

    /**
     * Sets the value of the local at index i to val
     * @param i the local index
     * @param val value to be changed
     */
    void set(uint16 i, Obj *val);

    /**
     * @return The value of the local at index i
     * @param i the local index
     */
    Obj *get(uint16 i) const;

    /**
     * Adds a new local at the end of the table
     * @param local the local to be added
     */
    void addLocal(const Local &local) { locals.push_back(local); }

    /**
     * Adds a new closure at the end of the table
     * @param closure the closure to be added
     */
    void addClosure(TableNode *closure) { closures.push_back(closure); }

    /**
     * @return The local at index i
     * @param i the local index
     */
    const Local &getLocal(uint16 i) const;

    /**
     * @return The local at index i
     * @param i the local index
     */
    Local &getLocal(uint16 i);

    /**
     * @return The closure at index i
     * @param i the closure index
     */
    TableNode *getClosure(uint16 i) const;

    LocalsTable copy() const;

    /**
     * @return The total number of locals and closures present
     */
    uint16 count() const { return locals.size() + closures.size(); }

    /**
     * @return The string representation of the table
     */
    string toString() const { return "(" + listToString(locals) + ")"; }
};

class ExceptionTable {
    friend class GarbageCollector;

    friend class FrameTemplate;

private:
    vector<Exception> exceptions;
public:
    ExceptionTable() : exceptions() {}

    ExceptionTable(const ExceptionTable &table) = default;

    ExceptionTable &operator=(const ExceptionTable &table) = default;

    /**
     * Adds a new exception at the end of the table
     * @param exception the exception to be added
     */
    void addException(const Exception &exception) { exceptions.push_back(exception); }

    /**
     * @return The exception at index i
     * @param i the exception index
     */
    const Exception &get(int i) const { return exceptions[i]; }

    /**
     * @return The total number of exceptions
     */
    uint8 count() const { return exceptions.size(); }

    /**
     * @return The exception that catches the program execution at pc and a throwable of type
     * @param pc the program counter
     * @param type the type of the throwable
     */
    Exception getTarget(uint32 pc, Type *type) const;
};

/**
 * Represents a table which stores the corresponding line numbers
 * of the source code and byte code. It is used for printing stack trace and debugging purposes
 */
class LineNumberTable {
private:
    vector<uint32> bytecode;
    vector<uint64> sourcecode;
public:
    explicit LineNumberTable(size_t count) : bytecode(count), sourcecode(count) {
        bytecode.reserve(count);
        sourcecode.reserve(count);
    }

    LineNumberTable(const LineNumberTable &table) = default;

    LineNumberTable &operator=(const LineNumberTable &lines) = default;

    /**
     * Adds a line info at the end of the table
     * @param byteLine the line number in the bytecode
     * @param sourceLine the line number in the source code
     */
    void addLine(uint32 byteLine, uint64 sourceLine);

    /**
     * @return The corresponding line number in the source code
     * @param byteLine the line number in the bytecode
     */
    uint64 getSourceLine(uint32 byteLine) const;

    /**
     * @return The bytecode line numbers
     */
    const vector<uint32> &getBytecode() const { return bytecode; }

    /**
     * @return The source code line numbers
     */
    const vector<uint64> &getSourcecode() const { return sourcecode; }

    /**
     * @return The count of the bytecode and source code line number pairs
     */
    size_t count() { return bytecode.capacity(); }
};

/**
 * Represents a check table
 */
class MatchTable {
    friend class GarbageCollector;

private:
    vector<Case> cases;
    uint32 defaultLocation;
public:
    MatchTable(const vector<Case> &cases, uint32 defaultLocation) : cases(cases), defaultLocation(defaultLocation) {}

    /**
     * @return The array of check cases
     */
    const vector<Case> &getCases() const { return cases; }

    /**
     * @return The default location of the check table <i>(starting of the default block)</i>
     */
    uint32 getDefaultLocation() const { return defaultLocation; }

    /**
     * @return The number of the check cases
     */
    size_t count() const { return cases.size(); }

    /**
     * This function takes value and serially checks all the cases
     * and finds the case which matches with the value. Then the function returns
     * the destination location of the the matched case.<br>
     * The time complexity of this operation is O(n)
     * <br><br>
     * This function is optimized for integers and performs index search
     * on the cases array. The optimized operation takes only O(1) time.
     * @param value value to be matched
     * @return The destination location
     */
    uint32 perform(Obj *value);
};

#endif //VELOCITY_FRAME_TABLE_HPP
