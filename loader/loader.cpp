#include <cstdio>
#include "../utils/utils.hpp"
#include "loader.hpp"
#include "parser.hpp"
#include "verifier.hpp"
#include "../oop/objects.hpp"
#include "../oop/type.hpp"

ObjMethod *Loader::load(const string &path) {
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
        vm->setGlobal(obj->getSign().toString(), obj);
    }
    // Load the globals
    for (int i = 0; i < elp.globalsCount; ++i) {
        auto global = readGlobal(constPool, elp.globals[i]);
        vm->setGlobal(global->getSign().toString(), global);
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
    return dynamic_cast<ObjMethod *>(vm->getGlobal(sign));
}

bool Loader::isAlreadyLoaded(const string &path) { return loadedLibs.find(path) != loadedLibs.end(); }

Obj *Loader::readGlobal(vector<Obj *> &constPool, GlobalInfo &global) {
    Sign sign{constPool[global.thisGlobal]->toString()};
    auto type = findClass(constPool[global.type]->getSign().toString());
    auto meta = readMeta(global.meta);

    return match<Obj *>(sign.toString(), {
            {"array", [] { return new ObjArray(0); }},
            {"bool",  [] { return new ObjBool(false); }},
            {"char",  [] { return new ObjChar('\0'); }},
            {"float", [] { return new ObjFloat(0); }},
            {"int",   [] { return new ObjInt(0); }}
    }, [&] { return new Object(sign, type, meta, type->getMembers()); });
}

Obj *Loader::readObj(vector<Obj *> &constPool, ObjInfo &obj) {
    return match<Obj *>(obj.type, {
            {0x01, [&] { return readMethod(constPool, obj._method); }},
            {0x02, [&] { return readClass(obj._class); }}
    });
}

Obj *Loader::readClass(ClassInfo klass) {
    auto kind = match<Type::Kind>(klass.type, {
            {0x01, [] { return Type::CLASS; }},
            {0x02, [] { return Type::INTERFACE; }},
            {0x03, [] { return Type::ENUM; }},
            {0x04, [] { return Type::ANNOTATION; }}
    });
    auto constPool = readConstPool(klass.constantPool, klass.constantPoolCount);
    Sign sign{constPool[klass.thisClass]->toString()};
    vector<Type *> tparams;
    for (auto tparam: *dynamic_cast<ObjArray *>(constPool[klass.typeParams])) {
        auto str = tparam->toString();
        if (containsRef(str)) throw corrupt();
        auto type = Type::TYPE_PARAM_(str);
        tparams.push_back(type);
        refs[str] = type;
    }
    Table<Type *> supers;
    for (auto super: *dynamic_cast<ObjArray *>(constPool[klass.supers])) {
        auto str = super->toString();
        Type *type = findClass(str);
        supers[type->getSign().toString()] = type;
    }

    Table<Obj *> members;
    for (int i = 0; i < klass.methodsCount; ++i) {
        auto method = readMethod(sign.toString(), constPool, klass.methods[i]);
        members[method->getSign().toString()] = method;
    }
    for (int i = 0; i < klass.fieldsCount; ++i) {
        auto field = readField(constPool, klass.fields[i]);
        members[field->getSign().toString()] = field;
    }
    for (int i = 0; i < klass.objectsCount; ++i) {
        auto object = readObj(constPool, klass.objects[i]);
        members[object->getSign().toString()] = object;
    }

    for (auto const &key: tparams)
        refs.erase(key->getSign().toString());
    auto meta = readMeta(klass.meta);
    auto type = new Type(sign, meta, kind, constPool, tparams, supers, members);
    type = resolveObj(sign.toString(), type);
    vm->setGlobal(sign.toString(), type);
    return type;
}

bool Loader::containsRef(const string &str) { return refs.find(str) != refs.end(); }

CorruptFileError Loader::corrupt() { return CorruptFileError(pathStack.top()); }

Obj *Loader::readField(vector<Obj *> &constPool, FieldInfo &field) {
    Sign sign{constPool[field.thisField]->toString()};
    auto type = findClass(constPool[field.type]->getSign().toString());
    auto meta = readMeta(field.meta);

    return match<Obj *>(type->getSign().toString(), {
            {"array", [] { return new ObjArray(0); }},
            {"bool",  [] { return new ObjBool(false); }},
            {"char",  [] { return new ObjChar('\0'); }},
            {"float", [] { return new ObjFloat(0); }},
            {"int",   [] { return new ObjInt(0); }}
    }, [&] { return new Object(sign, type, meta, type->getMembers()); });
}

Obj *Loader::readMethod(const string &klassSign, vector<Obj *> &constPool, MethodInfo &method) {
    auto type = findClass(klassSign);
    auto met = readMethod(constPool, method);
    met->setType(type);
    return met;
}

Obj *Loader::readMethod(vector<Obj *> &constPool, MethodInfo &method) {
    auto kind = match<ObjMethod::Kind>(method.type, {
            {0x01, [] { return ObjMethod::FUNCTION; }},
            {0x02, [] { return ObjMethod::METHOD; }},
            {0x03, [] { return ObjMethod::CONSTRUCTOR; }}
    });
    Sign sign{constPool[method.thisMethod]->toString()};
    ArgsTable args{};
    for (int i = 0; i < method.argsCount; ++i) {
        args.addArg(readArg(constPool, method.args[i]));
    }
    LocalsTable locals{method.closureStart};
    for (int i = 0; i < method.localsCount; ++i) {
        locals.addLocal(readLocal(constPool, method.locals[i]));
    }
    ExceptionTable exceptions{};
    for (int i = 0; i < method.exceptionTableCount; ++i) {
        exceptions.addException(readException(constPool, method.exceptionTable[i]));
    }
    LineNumberTable lines{method.lineNumberTableCount};
    for (int i = 0; i < method.lineNumberTableCount; ++i) {
        auto lineInfo = method.lineNumberTable[i];
        lines.addLine(lineInfo.byteCode, lineInfo.sourceCode);
    }
    auto meta = readMeta(method.meta);
    auto *frame = new Frame{constPool, method.code, method.maxStack, args, locals, exceptions, lines, null};
    auto methodObj = new ObjMethod(sign, null, meta, kind, frame);
    frame->setMethod(methodObj);
    if (kind == ObjMethod::CONSTRUCTOR)
        vm->setGlobal(sign.toString(), methodObj);
    return methodObj;
}

Exception Loader::readException(vector<Obj *> &constPool, MethodInfo::ExceptionTableInfo &exception) {
    auto type = findClass(constPool[exception.exception]->toString());
    return {
            exception.startPc,
            exception.endPc,
            exception.targetPc,
            type,
            readMeta(exception.meta)
    };
}

Local Loader::readLocal(vector<Obj *> &constPool, MethodInfo::LocalInfo &local) {
    auto kind = match<Local::Kind>(local.flags, {
            {0x01, [] { return Local::VAR; }},
            {0x02, [] { return Local::CONST; }}
    });
    Sign sign{constPool[local.thisLocal]->toString()};
    auto type = findClass(constPool[local.type]->toString());
    auto meta = readMeta(local.meta);
    auto obj = match<Obj *>(type->getSign().toString(), {
            {"array", [] { return new ObjArray(0); }},
            {"bool",  [] { return new ObjBool(false); }},
            {"char",  [] { return new ObjChar('\0'); }},
            {"float", [] { return new ObjFloat(0); }},
            {"int",   [] { return new ObjInt(0); }}
    }, [&] { return new Object(sign, type, meta, type->getMembers()); });
    return {kind, sign.toString(), obj, meta};
}

Arg Loader::readArg(vector<Obj *> &constPool, MethodInfo::ArgInfo &arg) {
    auto kind = match<Arg::Kind>(arg.flags, {
            {0x01, [] { return Arg::VALUE; }},
            {0x02, [] { return Arg::REF; }}
    });
    Sign sign{constPool[arg.thisArg]->toString()};
    auto type = findClass(constPool[arg.type]->toString());
    auto meta = readMeta(arg.meta);
    auto obj = match<Obj *>(type->getSign().toString(), {
            {"array", [] { return new ObjArray(0); }},
            {"bool",  [] { return new ObjBool(false); }},
            {"char",  [] { return new ObjChar('\0'); }},
            {"float", [] { return new ObjFloat(0); }},
            {"int",   [] { return new ObjInt(0); }}
    }, [&] { return new Object(sign, type, meta, type->getMembers()); });
    return {kind, sign.toString(), obj, meta};
}

vector<Obj *> Loader::readConstPool(CpInfo *constantPool, uint16 count) {
    vector<Obj *> list;
    for (int i = 0; i < count; ++i) {
        list.push_back(readCp(constantPool[i]));
    }
    return list;
}

double rawToDouble(uint64 digits) {
    union Converter {
        uint64 digits;
        double number;
    } converter{.digits=digits};
    return converter.number;
}

int64 unsignedToSigned(uint64 number) {
    union Converter {
        uint64 number1;
        int64 number2;
    } converter{.number1=number};
    return converter.number2;
}

Obj *Loader::readCp(CpInfo &cpInfo) {
    return match<Obj *>(cpInfo.tag, {
            {0x00, [] { return new ObjNull; }},
            {0x01, [] { return new ObjBool(true); }},
            {0x02, [] { return new ObjBool(false); }},
            {0x03, [&] { return new ObjChar((char) cpInfo._char); }},
            {0x04, [&] { return new ObjInt(unsignedToSigned(cpInfo._int)); }},
            {0x05, [&] { return new ObjFloat(rawToDouble(cpInfo._float)); }},
            {0x06, [&] { return new ObjString(readUTF8(cpInfo._string)); }},
            {0x07, [&] {
                auto con = cpInfo._array;
                auto array = new ObjArray(con.len);
                for (int i = 0; i < con.len; ++i) {
                    array->set(i, readCp(con.items[i]));
                }
                return array;
            }}
    });
}

string Loader::readUTF8(__UTF8 &value) {
    return {reinterpret_cast<const char *>(value.bytes), value.len};
}

Table<string> Loader::readMeta(MetaInfo &meta) {
    Table<string> table;
    for (int i = 0; i < meta.len; ++i) {
        auto entry = meta.table[i];
        table[readUTF8(entry.key)] = readUTF8(entry.value);
    }
    return table;
}

Type *Loader::resolveObj(const string &sign, Type *type) {
    // Get the object
    auto find = refs.find(sign);
    // If not resolved
    if (find != refs.end()) {
        // Get the sentinel
        auto klass = find->second;
        // Change it
        klass->recognizeUnknown(*type);
        // Delete it
        delete type;
        return klass;
    }
    return type;
}

Type *Loader::findClass(const string &sign) {
    // Find in reference pool
    auto find1 = refs.find(sign);
    Type *type;
    // If not found
    if (find1 == refs.end()) {
        // Then find it if already loaded
        auto find2 = vm->getGlobal(sign);
        // If it is loaded
        if (find2 != null && is<Type *>(find2)) {
            // Get it
            type = dynamic_cast<Type *>(find2);
        } else {
            // Get a sentinel with the name attached to it
            type = Type::SENTINEL_(sign);
            // Put the type
            refs[sign] = type;
        }
    } else {
        // Get it if found in the reference pool
        type = find1->second;
    }
    // Return that
    return type;
}

