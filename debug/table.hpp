#ifndef VELOCITY_DEBUG_TABLE_HPP
#define VELOCITY_DEBUG_TABLE_HPP

#include "../utils/common.hpp"
#include "../utils/exceptions.hpp"
#include "../utils/utils.hpp"
#include "../oop/method.hpp"
#include "../oop/type.hpp"
#include "../frame/table.hpp"

class IntPack {
private:
    uint32 i;
public:
    IntPack(uint32 i) : i(i) {}

    string toString() const { return std::to_string(i); }
};

class DataTable {
private:
    const string title;
    // This field is done to maintain the insertion order which DataTable::data does not maintain
    vector<string> keys;
    map<string, vector<string>> data;
    int width;

protected:
    DataTable(const string &title, const vector<string> &args);

    any get(const string &str) const { return data.at(str); }

    void set(vector<string> vals) {
        if (vals.size() != data.size())
            throw FatalError("not enough vals");

        size_t i = 0;
        for (auto &[_, list]: data) {
            list.push_back(vals[i]);
            i++;
        }
        width++;
    }

public:
    string toString() const;

    friend std::ostream &operator<<(std::ostream &os, const DataTable &table);
};

class CallStackTable : public DataTable {
public:
    CallStackTable() : DataTable("Call Stack", {"i", "method", "args", "pc"}) {}

    void add(uint16 i, ObjMethod *method, const ArgsTable &args, uint32 pc) {
        set({std::to_string(i), method->toString(), args.toString(), std::to_string(pc)});
    }
};

class ArgumentTable : public DataTable {
public:
    ArgumentTable() : DataTable("Args Table", {"slot", "type", "name", "value"}) {}

    void add(uint8 slot, Arg::Kind kind, const string &name, Obj *value) {
        set({std::to_string(slot), KindStringInfo::ofArg(kind), name, value->toString()});
    }
};

class LocalVarTable : public DataTable {
public:
    explicit LocalVarTable(uint16 closureStart) : DataTable(format("Locals Table | closureStart: %d", closureStart),
                                                            {"slot", "type", "name", "value"}) {}

    void add(uint8 slot, Local::Kind kind, const string &name, Obj *value) {
        set({std::to_string(slot), KindStringInfo::ofLocal(kind), name, value->toString()});
    }
};

class ExcTable : public DataTable {
public:
    ExcTable() : DataTable("Exception Table", {"from", "to", "target", "exception"}) {}

    void add(uint32 from, uint32 to, uint32 target, Type *exception) {
        set({std::to_string(from), std::to_string(to), std::to_string(target), exception->toString()});
    }
};

class LineDataTable : public DataTable {
public:
    LineDataTable() : DataTable("Lines", {"bytecode", "source code"}) {}

    void add(uint32 b, uint64 s) {
        set({std::to_string(b), std::to_string(s)});
    }
};


#endif //VELOCITY_DEBUG_TABLE_HPP
