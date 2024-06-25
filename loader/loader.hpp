#ifndef VELOCITY_LOADER_HPP
#define VELOCITY_LOADER_HPP

#include "elpops/elpdef.hpp"
#include "../utils/common.hpp"
#include "../oop/obj.hpp"
#include "../oop/method.hpp"
#include "../frame/table.hpp"

class VM;

class Library {
public:
    enum class State {
        /// Library has started to load but is resolving its dependencies
        MARKED,
        /// Library has already been loaded
        LOADED,
        /// Library is not yet loaded
        NOT_LOADED
    };
private:
    State state = State::NOT_LOADED;
    intptr id;
    string name;
    string path;
    const ElpInfo &elp;
    vector<string> dependencies;

public:
    Library(const string &name, const string &path, const ElpInfo &elp, const vector<string> &dependencies)
            : name(name), dependencies(dependencies), path(path), elp(elp), id((intptr) &elp) {}

    const string &getName() const { return name; }

    const vector<string> &getDependencies() const { return dependencies; }

    intptr getId() const { return id; }

    const string &getPath() const { return path; }

    const ElpInfo &getElp() const { return elp; }

    State getState() const { return state; }

    void setState(State state_) { this->state = state_; }
};

/**
 * Represents the loader of the vm
 */
class Loader {
private:
    /// Reference to the vm
    VM *vm;
    /// List of all libraries in the form of [path, library]
    std::map<string, Library *> libraries;
    /// The library stack used for resolving dependencies
    std::stack<Library *> libStack = {};
    /// Pool of unresolved references
    Table<Type *> referencePool = {};
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

    Obj *readMethod(vector<Obj *> &constPool, const string &klassSign, MethodInfo &method);

    Obj *readMethod(vector<Obj *> &constPool, MethodInfo &method);

    Exception readException(vector<Obj *> &constPool, MethodInfo::ExceptionTableInfo &exception);

    MatchTable readMatch(vector<Obj *> constPool, MethodInfo::MatchInfo match);

    Local readLocal(vector<Obj *> &constPool, MethodInfo::LocalInfo &local);

    Arg readArg(vector<Obj *> &constPool, MethodInfo::ArgInfo &arg);

    vector<Obj *> readConstPool(CpInfo *constantPool, uint16 count);

    Obj *readCp(CpInfo &cpInfo);

    static string readUTF8(__UTF8 &value);

    static Table<string> readMeta(MetaInfo &meta);

    Sign getSign(vector<Obj *> &constPool, cpidx index);

    Type *resolveType(const string &sign, Type type);

    Type *findType(const string &sign);

    Library *readLibrary(const string &path);

    CorruptFileError corrupt();

    void loadLibrary(Library *library);
};

#endif //VELOCITY_LOADER_HPP
