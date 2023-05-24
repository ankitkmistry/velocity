#ifndef VELOCITY_LOADER_HPP
#define VELOCITY_LOADER_HPP

#include "../utils/common.hpp"
#include "../oop/obj.hpp"
#include "../oop/method.hpp"
#include "elpdef.hpp"
#include "../frame/table.hpp"

class VM;

class Loader {
private:
    VM *vm;
    std::set <string> loadedLibs = {};
    std::stack <string> pathStack = {};
    Table<Type *> refs = {};
public:
    explicit Loader(VM *vm) : vm(vm) {}

    ObjMethod *load(const string &path);

private:
    Obj *readGlobal(vector<Obj *> &constPool, GlobalInfo &global);

    Obj *readObj(vector<Obj *> &constPool, ObjInfo &obj);

    Obj *readClass(vector<Obj *> &constPool, ClassInfo klass);

    Obj *readField(vector<Obj *> &constPool, FieldInfo &field);

    Obj *readMethod(const string &klassSign, vector<Obj *> &constPool, MethodInfo &method);

    Obj *readMethod(vector<Obj *> &constPool, MethodInfo &method);

    Exception readException(vector<Obj *> &constPool, MethodInfo::ExceptionTableInfo &exception);

    Local readLocal(vector<Obj *> &constPool, MethodInfo::LocalInfo &local);

    Arg readArg(vector<Obj *> &constPool, MethodInfo::ArgInfo &arg);

    vector<Obj *> readConstPool(CpInfo *constantPool, uint16 count);

    Obj *readCp(CpInfo &cpInfo);

    static string readUTF8(__UTF8 &value);

    static Table<string> readMeta(MetaInfo &meta);

    Type *resolveObj(const string &sign, Type *type);

    Type *findClass(const string &sign);

    bool isAlreadyLoaded(const string &path);

    CorruptFileError corrupt();

    bool containsRef(const string &str);
};

#endif //VELOCITY_LOADER_HPP
