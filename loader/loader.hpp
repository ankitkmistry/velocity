#ifndef VELOCITY_LOADER_HPP
#define VELOCITY_LOADER_HPP

#include <set>
#include <stack>
#include "../utils/common.hpp"
#include "../ee/vm.hpp"
#include "../oop/obj.hpp"
#include "../oop/method.hpp"
#include "elfdef.hpp"
#include "../frame/table.hpp"

class Loader {
private:
    const VM *vm;
    set<string> loadedLibs = {};
    stack<string> pathStack = {};
    Table<Obj *> refs = {};
public:
    Loader(const VM *vm) : vm(vm) {}

    ObjMethod *load(string path);

private:
    Obj *readGlobal(vector<Obj*> &constPool, GlobalInfo &global);

    Obj *readObj(vector<Obj*> &constPool, ObjInfo &obj);

    Obj *readClass(ClassInfo klass);

    Obj *readField(ClassInfo klass, FieldInfo field);

    Obj *readMethod(ClassInfo klass, MethodInfo method);

    Obj *readMethod(vector<Obj*> constPool, MethodInfo method);

    Exception readException(vector<Obj*> constPool, MethodInfo::ExceptionTableInfo exception);

    Local readLocal(vector<Obj*> constPool, MethodInfo::LocalInfo local);

    Arg readArg(vector<Obj*> constPool, MethodInfo::ArgInfo arg);

    vector<Obj *> readConstPool(CpInfo* constantPool,uint16 count);

    Obj *readCp(CpInfo cpInfo);

    string *readUTF8(__UTF8 value);

    Table<string> readMeta(MetaInfo meta);

    void resolveObj(string sign, Type *type);

    Type *findClass(string sign);

    bool isAlreadyLoaded(const string &path);
};

#endif //VELOCITY_LOADER_HPP
