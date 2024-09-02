#ifndef VELOCITY_LOADER_HPP
#define VELOCITY_LOADER_HPP

#include "elpops/elpdef.hpp"
#include "../utils/common.hpp"
#include "../objects/obj.hpp"
#include "../objects/method.hpp"
#include "../objects/module.hpp"
#include "../frame/table.hpp"

class SpadeVM;

/**
 * Represents the loader of the vm
 */
class Loader {
private:
    /// Reference to the vm
    SpadeVM *vm;
    /// The memory manager
    MemoryManager *manager;
    /// List of all modules in the form of [path, module]
    std::map<string, ObjModule *> modules = {};
    /// Pool of unresolved references
    Table<Type *> referencePool = {};
    ObjModule *current;
public:
    explicit Loader(SpadeVM *vm);

    /**
     * This function loads the bytecode file at \p path and
     * returns the function object which is the entry point of the bytecode file
     * @param path the path to the file
     * @return the entry point if present, null otherwise
     */
    ObjMethod *load(string path);


private:
    /**
     * Loads a module into the vm
     * @param module the module
     */
    void loadModule(ObjModule *module);

    /**
     * Reads a module specified by \p path
     * @param path the path of the module
     * @return the module as an ObjModule
     */
    ObjModule *readModule(const string &path);

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

    /**
     * Reads the constant pool
     * @param constantPool the constant pool info
     * @param count the size of the constant pool
     * @return the constant pool as a vector
     */
    vector<Obj *> readConstPool(CpInfo *constantPool, uint16 count);


    /**
     * Reads a constant
     * @param cpInfo the info of the constant
     * @return the constant as an Obj
     */
    Obj *readCp(CpInfo &cpInfo);

    static string readUTF8(__UTF8 &value);

    /**
     * Reads the meta info of the object
     * @param meta the meta info
     * @return the meta info as a table of strings
     */
    static Table<string> readMeta(MetaInfo &meta);

    /**
     * @param index index of the signature
     * @return the signature specified by the \p index from the constant pool
     *         of the current module
     */
    Sign getSign(cpidx index);

    /**
     * Searches the type specified by \p param in the globals table.
     * If found it returns that type otherwise it checks the unresolved references pool.
     * If it is found in referencePool it returns that type otherwise it creates
     * a unresolved type of param and returns it.
     * @param sign the param of the type
     * @return the type associated with \p param
     */
    Type *findType(const string &sign);

    /**
     * Resolves the type associated with \p param .
     * Searches for the type in the reference pool.
     * If found then it copies the info from \p type to the unresolved type
     * and returns the unresolved type as resolved. Otherwise it returns a
     * new Kind with its contents copied from \p type .
     * @param sign the signature of the type
     * @param type type info
     * @return the associated type
     */
    Type *resolveType(const string &sign, Type type);

    ObjModule *getCurrentModule();

    const vector<Obj *> &getConstantPool();

    CorruptFileError corrupt();

    Obj *makeObj(string typeSign, Sign objSign, Type *type);

    Obj *makeObj(string typeSign, Type *type);
};

#endif //VELOCITY_LOADER_HPP
