#ifndef VELOCITY_LOADER_HPP
#define VELOCITY_LOADER_HPP

#include "elpops/elpdef.hpp"
#include "../utils/common.hpp"
#include "../objects/obj.hpp"
#include "../objects/method.hpp"
#include "../objects/module.hpp"
#include "../frame/table.hpp"

class VM;

/**
 * Represents the loader of the vm
 */
class Loader {
private:
    /// Reference to the vm
    VM *vm;
    /// The memory manager
    MemoryManager *manager;
    /// List of all modules in the form of [path, module]
    std::map<string, ObjModule *> modules = {};
    /// The module stack used for resolving dependencies
    std::vector<ObjModule *> modStack = {};
    /// Pool of unresolved references
    Table<Type *> referencePool = {};
public:
    explicit Loader(VM *vm);

    /**
     * This function loads the bytecode file at <i>path</i> and
     * returns the function object which is the entry point of the bytecode file
     * @param path the path to the file
     * @return the entry point if present, null otherwise
     */
    ObjMethod *load(const string &path);

private:
    Obj *readGlobal(GlobalInfo &global);

    Obj *readObj(ObjInfo &obj);

    Obj *readClass(ClassInfo klass);

    Obj *readField(FieldInfo &field);

    Obj *readMethod(const string &klassSign, MethodInfo &method);

    Obj *readMethod(MethodInfo &method);

    Exception readException(MethodInfo::ExceptionTableInfo &exception);

    MatchTable readMatch(MethodInfo::MatchInfo match);

    Local readLocal(MethodInfo::LocalInfo &local);

    Arg readArg(MethodInfo::ArgInfo &arg);

    vector<Obj *> readConstPool(CpInfo *constantPool, uint16 count);

    Obj *readCp(CpInfo &cpInfo);

    static string readUTF8(__UTF8 &value);

    static Table<string> readMeta(MetaInfo &meta);

    Sign getSign(cpidx index);

    Type *resolveType(const string &sign, Type type);

    Type *findType(const string &sign);

    ObjModule *readModule(const string &path);

    void loadModule(ObjModule *library);

    ObjModule *getCurrentModule();

    const vector<Obj *> &getConstantPool();

    CorruptFileError corrupt();
};

#endif //VELOCITY_LOADER_HPP
