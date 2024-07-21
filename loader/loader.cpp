#include "loader.hpp"
#include "elpops/reader.hpp"
#include "verifier.hpp"
#include "../ee/vm.hpp"
#include "../objects/typeparam.hpp"

Loader::Loader(VM *vm) : vm(vm), manager(vm->getMemoryManager()) {}

ObjMethod *Loader::load(const string &path) {
    auto module = readModule(path);
    modStack.push_back(module);
    while (!modStack.empty()) {
        module = modStack.back();
        module->setState(ObjModule::State::MARKED);
        for (auto &dep: module->getDependencies()) {
            auto depLib = readModule(dep);
            if (depLib->getState() == ObjModule::State::NOT_LOADED) {
                modStack.push_back(depLib);
                break;
            }
        }
        if (modStack.back() == module) {
            loadModule(module);
            modStack.pop_back();
        }
    }

    // Complain about the unresolved types
    for (auto [sign, reference]: referencePool) {
        if (reference->getKind() == Type::Kind::UNRESOLVED) {
            throw ReferenceNotFoundError(sign);
            // TODO give a detailed error message for all the unresolved references
        }
    }

    // Finish up...
    auto elp = module->getElp();
    // If this is an executable one, get the entry point
    if (elp.type == 0x01) {
        // Load the constant pool
        vector<Obj *> constPool = module->getConstantPool();
        // Get the param of the entry point
        auto entrySign = constPool[elp.entry]->toString();
        // Return the entry point
        return cast<ObjMethod *>(vm->getGlobal(entrySign));
    }
    return null;
}

ObjModule *Loader::readModule(const string &path) {
    vector<string> deps;
    auto absolutePath = getAbsolutePath(path);
    // If the module is already read, return it
    if (auto it = modules.find(absolutePath); it != modules.end()) {
        return it->second;
    }
    // Or else, start reading a new module
    ElpReader reader{path};
    // Read it...
    auto elp = reader.read();
    // Verify it...
    Verifier verifier{elp, path};
    verifier.verify();
    // Close the reader
    reader.close();
    // Load the constant pool
    auto module = new(manager) ObjModule{path, elp, readMeta(elp.meta)};
    modStack.push_back(module);
    auto constPool = readConstPool(elp.constantPool, elp.constantPoolCount);
    module->setConstantPool(constPool);
    modStack.pop_back();
    // Insert the module to the module table
    modules[absolutePath] = module;
    return module;
}

void Loader::loadModule(ObjModule *module) {
    auto elp = module->getElp();
    // Load the objects
    for (int i = 0; i < elp.objectsCount; ++i) {
        auto obj = readObj(elp.objects[i]);
        vm->setGlobal(obj->getSign().toString(), obj);
    }
    // Load the globals
    for (int i = 0; i < elp.globalsCount; ++i) {
        auto global = readGlobal(elp.globals[i]);
        vm->setGlobal(global->getSign().toString(), global);
    }
    // Add the module to the globals
    vm->setGlobal(module->getSign().toString(), module);
    // Set the state to loaded
    module->setState(ObjModule::State::LOADED);
}

Obj *Loader::readGlobal(GlobalInfo &global) {
    auto constPool = getConstantPool();
    auto sign = getSign(global.thisGlobal);
    auto type = findType(constPool[global.type]->toString());
    auto meta = readMeta(global.meta);

    return match<Obj *>(constPool[global.type]->toString(), {
            {"array",  [&] { return new(manager) ObjArray(0, getCurrentModule()); }},
            {"bool",   [&] { return new(manager) ObjBool(false, getCurrentModule()); }},
            {"char",   [&] { return new(manager) ObjChar('\0', getCurrentModule()); }},
            {"float",  [&] { return new(manager) ObjFloat(0, getCurrentModule()); }},
            {"int",    [&] { return new(manager) ObjInt(0, getCurrentModule()); }},
            {"string", [&] { return new(manager) ObjString("", getCurrentModule()); }}
    }, [&] {
        return new(manager) Object(sign, type, getCurrentModule(), meta);
    });
}

Obj *Loader::readObj(ObjInfo &obj) {
    auto constPool = getConstantPool();
    switch (obj.type) {
        case 0x01:
            return readMethod(obj._method);
        case 0x02:
            return readClass(ClassInfo());
        default:
            throw Unreachable();
    }
}

Obj *Loader::readClass(ClassInfo klass) {
    auto constPool = getConstantPool();
    Type::Kind kind;
    switch (klass.type) {
        case 0x01:
            kind = Type::CLASS;
            break;
        case 0x02:
            kind = Type::INTERFACE;
            break;
        case 0x03:
            kind = Type::ENUM;
            break;
        case 0x04:
            kind = Type::ANNOTATION;
            break;
        default:
            throw Unreachable();
    }
    auto sign = getSign(klass.thisClass);
    vector<TypeParam *> typeParams;
    auto typeParamsObj = constPool[klass.typeParams];
    if (is<ObjArray *>(typeParamsObj))
        cast<ObjArray *>(typeParamsObj)->foreach([this, &typeParams](auto typeParam) {
            // Get the signature of the type parameter
            auto paramSign = typeParam->toString();
            // Make it an unresolved reference
            auto type = new(manager) TypeParam(Sign{paramSign}, getCurrentModule());
            // Remember the type params
            typeParams.push_back(type);
            // Put it in the ref pool
            referencePool[paramSign] = type;
        });
    Table<Type *> supers;
    cast<ObjArray *>(constPool[klass.supers])->foreach([this, &supers](auto super) {
        auto str = super->toString();
        Type *type = findType(str);
        supers[type->getSign().toString()] = type;
    });

    Table<Obj *> members;
    for (int i = 0; i < klass.methodsCount; ++i) {
        auto method = readMethod(sign.toString(), klass.methods[i]);
        members[method->getSign().toString()] = method;
    }
    for (int i = 0; i < klass.fieldsCount; ++i) {
        auto field = readField(klass.fields[i]);
        members[field->getSign().toString()] = field;
    }
    for (int i = 0; i < klass.objectsCount; ++i) {
        auto object = readObj(klass.objects[i]);
        members[object->getSign().toString()] = object;
    }

    auto meta = readMeta(klass.meta);

    // Resolve the type params
    for (auto const &key: typeParams) {
        // Remove the unresolved types from ref pool
        referencePool.erase(key->getSign().toString());
    }
    // Resolve the type
    auto type = resolveType(sign.toString(), {sign, kind, typeParams, supers, members, getCurrentModule(), meta});
    vm->setGlobal(sign.toString(), type);
    return type;
}

Obj *Loader::readField(FieldInfo &field) {
    auto constPool = getConstantPool();
    auto sign = getSign(field.thisField);
    auto type = findType(constPool[field.type]->toString());
    auto meta = readMeta(field.meta);

    return match<Obj *>(constPool[field.type]->toString(), {
            {"array",  [&] { return new(manager) ObjArray(0, getCurrentModule()); }},
            {"bool",   [&] { return new(manager) ObjBool(false, getCurrentModule()); }},
            {"char",   [&] { return new(manager) ObjChar('\0'); }},
            {"float",  [&] { return new(manager) ObjFloat(0, getCurrentModule()); }},
            {"int",    [&] { return new(manager) ObjInt(0, getCurrentModule()); }},
            {"string", [&] { return new(manager) ObjString("", getCurrentModule()); }}
    }, [&] {
        return new(manager) Object(sign, type, getCurrentModule(), meta);
    });
}

Obj *Loader::readMethod(const string &klassSign, MethodInfo &method) {
    auto constPool = getConstantPool();
    auto type = findType(klassSign);
    auto met = readMethod(method);
    met->setType(type);
    return met;
}

Obj *Loader::readMethod(MethodInfo &method) {
    auto constPool = getConstantPool();
    ObjMethod::Kind kind;
    switch (method.type) {
        case 0x01:
            kind = ObjMethod::FUNCTION;
            break;
        case 0x02:
            kind = ObjMethod::METHOD;
            break;
        case 0x03:
            kind = ObjMethod::CONSTRUCTOR;
            break;
        default:
            throw Unreachable();
    }
    auto sign = getSign(method.thisMethod);
    vector<TypeParam *> typeParams;
    auto typeParamsObj = constPool[method.typeParams];
    if (is<ObjArray *>(typeParamsObj))
        cast<ObjArray *>(typeParamsObj)->foreach([this, &typeParams](auto typeParam) {
            // Get the signature of the type parameter
            auto paramSign = typeParam->toString();
            // Make it an unresolved reference
            auto type = new(manager) TypeParam(Sign{paramSign}, getCurrentModule());
            // Remember the type params
            typeParams.push_back(type);
            // Put it in the ref pool
            referencePool[paramSign] = type;
        });
    ArgsTable args{};
    for (int i = 0; i < method.argsCount; ++i) {
        args.addArg(readArg(method.args[i]));
    }
    LocalsTable locals{method.closureStart};
    for (int i = 0; i < method.localsCount; ++i) {
        locals.addLocal(readLocal(method.locals[i]));
    }
    ExceptionTable exceptions{};
    for (int i = 0; i < method.exceptionTableCount; ++i) {
        exceptions.addException(readException(method.exceptionTable[i]));
    }
    LineNumberTable lines{method.lineNumberTableCount};
    for (int i = 0; i < method.lineNumberTableCount; ++i) {
        auto lineInfo = method.lineNumberTable[i];
        lines.addLine(lineInfo.byteCode, lineInfo.sourceCode);
    }
    vector<ObjMethod *> lambdas;
    lambdas.reserve(method.lambdaCount);
    for (int i = 0; i < method.lambdaCount; ++i) {
        lambdas.push_back(cast<ObjMethod *>(readMethod(method.lambdas[i])));
    }
    vector<MatchTable> matches;
    matches.reserve(method.matchCount);
    for (int i = 0; i < method.matchCount; ++i) {
        matches.push_back(readMatch(method.matches[i]));
    }
    auto meta = readMeta(method.meta);

    // Resolve the type params
    for (auto const &key: typeParams) {
        // Remove the unresolved types from ref pool
        referencePool.erase(key->getSign().toString());
    }
    // Create the frame
    Frame frame{method.codeCount, method.code,
                method.maxStack,
                args, locals, exceptions,
                lines, null};
    auto methodObj = new(manager) ObjMethod(sign, kind, frame, null, typeParams, getCurrentModule(), meta);
    if (kind == ObjMethod::CONSTRUCTOR)
        vm->setGlobal(sign.toString(), methodObj);
    return methodObj;
}

MatchTable Loader::readMatch(MethodInfo::MatchInfo match) {
    auto constPool = getConstantPool();
    vector<Case> cases;
    cases.reserve(match.caseCount);
    for (int i = 0; i < match.caseCount; ++i) {
        auto kase = match.cases[i];
        cases.push_back({constPool[kase.value]->copy(), kase.location});
    }
    return {cases, match.defaultLocation};
}

Exception Loader::readException(MethodInfo::ExceptionTableInfo &exception) {
    auto constPool = getConstantPool();
    auto type = findType(constPool[exception.exception]->toString());
    return {
            exception.startPc,
            exception.endPc,
            exception.targetPc,
            type,
            readMeta(exception.meta)
    };
}

Local Loader::readLocal(MethodInfo::LocalInfo &local) {
    auto constPool = getConstantPool();
    auto sign = getSign(local.thisLocal);
    auto type = findType(constPool[local.type]->toString());
    auto meta = readMeta(local.meta);
    auto obj = match<Obj *>(constPool[local.type]->toString(), {
            {"array",  [&] { return new(manager) ObjArray(0, getCurrentModule()); }},
            {"bool",   [&] { return new(manager) ObjBool(false, getCurrentModule()); }},
            {"char",   [&] { return new(manager) ObjChar('\0', getCurrentModule()); }},
            {"float",  [&] { return new(manager) ObjFloat(0, getCurrentModule()); }},
            {"int",    [&] { return new(manager) ObjInt(0, getCurrentModule()); }},
            {"string", [&] { return new(manager) ObjString("", getCurrentModule()); }}
    }, [&] {
        return new(manager) Object(sign, type, getCurrentModule(), meta);
    });
    return {sign.toString(), obj, meta};
}

Arg Loader::readArg(MethodInfo::ArgInfo &arg) {
    auto constPool = getConstantPool();
    auto sign = getSign(arg.thisArg);
    auto type = findType(constPool[arg.type]->toString());
    auto meta = readMeta(arg.meta);
    auto obj = match<Obj *>(constPool[arg.type]->toString(), {
            {"array",  [&] { return new(manager) ObjArray(0, getCurrentModule()); }},
            {"bool",   [&] { return new(manager) ObjBool(false, getCurrentModule()); }},
            {"char",   [&] { return new(manager) ObjChar('\0', getCurrentModule()); }},
            {"float",  [&] { return new(manager) ObjFloat(0, getCurrentModule()); }},
            {"int",    [&] { return new(manager) ObjInt(0, getCurrentModule()); }},
            {"string", [&] { return new(manager) ObjString("", getCurrentModule()); }}
    }, [&] {
        return new(manager) Object(sign, type, getCurrentModule(), meta);
    });
    return {sign.toString(), obj, meta};
}

vector<Obj *> Loader::readConstPool(CpInfo *constantPool, uint16 count) {
    vector<Obj *> list;
    for (int i = 0; i < count; ++i) {
        list.push_back(readCp(constantPool[i]));
    }
    list.shrink_to_fit();
    return list;
}

Obj *Loader::readCp(CpInfo &cpInfo) {
    switch (cpInfo.tag) {
        case 0x00:
            return new(manager) ObjNull(getCurrentModule());
        case 0x01:
            return new(manager) ObjBool(true, getCurrentModule());
        case 0x02:
            return new(manager) ObjBool(false, getCurrentModule());
        case 0x03:
            return new(manager) ObjChar((char) cpInfo._char, getCurrentModule());
        case 0x04:
            return new(manager) ObjInt(unsignedToSigned(cpInfo._int), getCurrentModule());
        case 0x05:
            return new(manager) ObjFloat(rawToDouble(cpInfo._float), getCurrentModule());
        case 0x06:
            return new(manager) ObjString(cpInfo._string.bytes, cpInfo._string.len, getCurrentModule());
        case 0x07: {
            auto con = cpInfo._array;
            auto array = new(manager) ObjArray(con.len, getCurrentModule());
            for (int i = 0; i < con.len; ++i) {
                array->set(i, readCp(con.items[i]));
            }
            return array;
        }
        default:
            throw Unreachable();
    }
}

string Loader::readUTF8(__UTF8 &value) {
    return string(reinterpret_cast<const char *>(value.bytes), value.len);
}

Table<string> Loader::readMeta(MetaInfo &meta) {
    Table<string> table;
    for (int i = 0; i < meta.len; ++i) {
        auto entry = meta.table[i];
        table[readUTF8(entry.key)] = readUTF8(entry.value);
    }
    return table;
}

Type *Loader::findType(const string &sign) {
    if (vm->getSettings().inbuiltTypes.contains(sign))return null;

    Type *type;

    if (auto find1 = vm->getGlobal(sign); is<Type *>(find1)) { // Try to find in vm globals
        // Get it
        type = cast<Type *>(find1);
    } else if (auto find2 = referencePool.find(sign);
            find2 != referencePool.end()) { // Try to find the type if it is already present in the ref pool
        type = find2->second;
    } else { // Build an unresolved type in the ref pool and return it
        // Get a sentinel with the name attached to it
        type = Type::SENTINEL_(sign, manager);
        // Put the type
        referencePool[sign] = type;
    }
    return type;
}

Type *Loader::resolveType(const string &sign, Type type) {
    // Get the object
    auto find = referencePool.find(sign);
    // If it was referred earlier, then resolve it
    if (find != referencePool.end()) {
        // Get the sentinel
        auto unresolved = find->second;
        // Change it
        *unresolved = type;
        return unresolved;
    } else {
        return new(manager) Type(type);
    }
}

Sign Loader::getSign(cpidx index) {
    return Sign{getConstantPool()[index]->toString()};
}

const vector<Obj *> &Loader::getConstantPool() {
    auto module = getCurrentModule();
    return module->getConstantPool();
}

ObjModule *Loader::getCurrentModule() {
    return modStack[modStack.size() - 1];
}

CorruptFileError Loader::corrupt() { return CorruptFileError(getCurrentModule()->getAbsolutePath()); }

