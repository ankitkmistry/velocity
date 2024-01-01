#ifndef VELOCITY_LOADER_HPP
#define VELOCITY_LOADER_HPP

#include "../utils/common.hpp"
#include "../oop/obj.hpp"
#include "../oop/method.hpp"
#include "elpdef.hpp"
#include "../frame/table.hpp"

class VM;

/**
 * Represents the loader of the vm
 */
class Loader {
private:
    VM *vm;
    std::set<string> loadedLibs = {};
    std::stack<string> pathStack = {};
    Table<Type *> refs = {};
public:
    explicit Loader(VM *vm) : vm(vm) {}

    /**
     * This function loads the bytecode file at <i>path</i> and
     * returns the function object which is the entry point of the bytecode file
     * @param path the path to the file
     * @return the entry point if present, null otherwise
     */
    ObjMethod *load(const string &path);

private:
    Obj *readGlobal(vector<Obj *> &constPool, GlobalInfo &global);

    Obj *readObj(vector<Obj *> &constPool, ObjInfo &obj);

    Obj *readClass(vector<Obj *> &typeParam, ClassInfo klass);

    Obj *readField(vector<Obj *> &constPool, FieldInfo &field);

    Obj *readMethod(const string &klassSign, MethodInfo &method);

    Obj *readMethod(MethodInfo &method);

    Exception readException(vector<Obj *> &constPool, MethodInfo::ExceptionTableInfo &exception);

    MatchTable readMatch(vector<Obj *> constPool, MethodInfo::MatchInfo match);

    Local readLocal(vector<Obj *> &constPool, MethodInfo::LocalInfo &local);

    Arg readArg(vector<Obj *> &constPool, MethodInfo::ArgInfo &arg);

    vector<Obj *> readConstPool(CpInfo *constantPool, uint16 count);

    Obj *readCp(CpInfo &cpInfo);

    static string readUTF8(__UTF8 &value);

    static Table<string> readMeta(MetaInfo &meta);

    Type *resolveObj(const string &sign, Type *type);

    Type *findClass(const string &sign);

    bool isAlreadyLoaded(const string &path);

    bool containsRef(const string &str);

    CorruptFileError corrupt();
};

#endif //VELOCITY_LOADER_HPP
