#include <cstdio>
#include "loader.hpp"
#include "parser.hpp"
#include "verifier.hpp"
#include "../oop/objects.hpp"
#include "../oop/type.hpp"

ObjMethod *Loader::load(string path) {
    // If already loaded, exit...
    if (isAlreadyLoaded(path))return null;
    // Push the current loading state to the stack
    pathStack.push(path);
    // Construct the parser
    Parser parser{fopen(path.c_str(), "rb"), path};
    // Parse it...
    ElpInfo elp = parser.parse();
    // Construct the verifier
    Verifier verifier{elp, path};
    // Verify it...
    verifier.check();

    // Load the constant pool
    vector<Obj *> constPool = readConstPool(elp.constantPool, elp.constantPoolCount);
    // Get the imports
    auto imports = dynamic_cast<ObjArray *>(constPool[elp.imports]);
    // Check each import
    for (auto obj: *imports) {
        // Get the import library path
        string libPath = obj->toString();
        // Load it if it is already not loaded
        if (!isAlreadyLoaded(libPath))
            load(libPath);
    }

    // Load the objects
    for (int i = 0; i < elp.objectsCount; ++i) {
        auto obj = readObj(constPool, elp.objects[i]);
        vm->getGlobals()[obj->getSign().toString()] = obj;
    }
    // Load the globals
    for (int i = 0; i < elp.globalsCount; ++i) {
        auto global = readGlobal(constPool, elp.globals[i]);
        vm->getGlobals()[global->getSign().toString()] = global;
    }

    if (elp.type == 0x02)return null;
    auto sign = constPool[elp.entry]->toString();

    // Cleanup
    loadedLibs.insert(path);
    pathStack.pop();
    for (auto [str, obj]: refs) {
        if (obj->getType() != null
            && (obj->getType()->getKind() == Type::Kind::TYPE_PARAM ||
                obj->getType()->getKind() == Type::Kind::UNKNOWN))
            throw ReferenceNotFoundError(str);
    }
    return dynamic_cast<ObjMethod *>(vm->getGlobals()[sign]);
}

bool Loader::isAlreadyLoaded(const string &path) { return loadedLibs.find(path) == loadedLibs.end(); }

Obj *Loader::readGlobal(vector<Obj *> &constPool, GlobalInfo &global) {
    Sign sign{constPool[global.thisGlobal]->toString()};
    auto type = findClass(constPool[global.type]->getSign().toString());
    auto meta = readMeta(global.meta);

    switch()
}

Obj *Loader::readObj(vector<Obj *> &constPool, ObjInfo &obj) {
    return nullptr;
}

Obj *Loader::readClass(ClassInfo klass) {
    return nullptr;
}

Obj *Loader::readField(ClassInfo klass, FieldInfo field) {
    return nullptr;
}

Obj *Loader::readMethod(ClassInfo klass, MethodInfo method) {
    return nullptr;
}

Obj *Loader::readMethod(vector<Obj *> constPool, MethodInfo method) {
    return nullptr;
}

Exception Loader::readException(vector<Obj *> constPool, MethodInfo::ExceptionTableInfo exception) {
    return Exception(nullptr, nullptr, nullptr, nullptr, Table());
}

Local Loader::readLocal(vector<Obj *> constPool, MethodInfo::LocalInfo local) {
    return Local(Local::CONST, __cxx11::basic_string(), nullptr, Table());
}

Arg Loader::readArg(vector<Obj *> constPool, MethodInfo::ArgInfo arg) {
    return Arg(Arg::VALUE, __cxx11::basic_string(), nullptr, Table());
}

vector<Obj *> Loader::readConstPool(CpInfo *constantPool, uint16 count) {
    return vector<Obj *>();
}

Obj *Loader::readCp(CpInfo cpInfo) {
    return nullptr;
}

string *Loader::readUTF8(__UTF8 value) {
    return nullptr;
}

Table<string> Loader::readMeta(MetaInfo meta) {
    return Table<string>();
}

void Loader::resolveObj(string sign, Type *type) {

}

Type *Loader::findClass(string sign) {
    return nullptr;
}
