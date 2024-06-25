#include "loader.hpp"
#include "elpops/reader.hpp"
#include "verifier.hpp"
#include "../ee/vm.hpp"

ObjMethod *Loader::load(const string &path) {
    auto library = readLibrary(path);
    libStack.push(library);
    while (!libStack.empty()) {
        library = libStack.top();
        library->setState(Library::State::MARKED);
        for (auto &dep: library->getDependencies()) {
            auto depLib = readLibrary(dep);
            if (depLib->getState() == Library::State::NOT_LOADED) {
                libStack.push(depLib);
                break;
            }
        }
        if (libStack.top() == library) {
            loadLibrary(library);
            libStack.pop();
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
    auto elp = library->getElp();
    // If this is an executable one, get the entry point
    if (elp.type == 0x01) {
        // Load the constant pool
        vector<Obj *> constPool = readConstPool(elp.constantPool, elp.constantPoolCount);
        // Get the sign of the entry point
        auto entrySign = constPool[elp.entry]->toString();
        // Return the entry point
        return cast<ObjMethod *>(vm->getGlobal(entrySign));
    }
    return null;
}

Library *Loader::readLibrary(const string &path) {
    vector<string> deps;
    auto absolutePath = getAbsolutePath(path);
    // If the library is already read, return it
    if (auto it = libraries.find(absolutePath); it != libraries.end()) {
        return it->second;
    }
    // Or else, start reading a new library
    ElpReader reader{path};
    // Read it...
    auto elp = reader.read();
    // Verify it...
    Verifier verifier{elp, path};
    verifier.verify();
    // Close the reader
    reader.close();
    // Load the constant pool
    vector<Obj *> constPool = readConstPool(elp.constantPool, elp.constantPoolCount);
    // Get the imports
    auto imports = cast<ObjArray *>(constPool[elp.imports]);
    // Get the import paths to a vector
    imports->foreach([&](auto obj) {
        deps.push_back(obj->toString());
    });
    auto library = new Library{getFilenameFromPath(path), absolutePath, elp, deps};
    libraries[absolutePath] = library;
    return library;
}

void Loader::loadLibrary(Library *library) {
    auto elp = library->getElp();
    // Load the constant pool
    vector<Obj *> constPool = readConstPool(elp.constantPool, elp.constantPoolCount);
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
    // Set the state to loaded
    library->setState(Library::State::LOADED);
}

Obj *Loader::readGlobal(vector<Obj *> &constPool, GlobalInfo &global) {
    auto sign = getSign(constPool, global.thisGlobal);
    auto type = findType(constPool[global.type]->toString());
    auto meta = readMeta(global.meta);

    return match<Obj *>(constPool[global.type]->toString(), {
            {"array", [&] { return new(vm) ObjArray(0); }},
            {"bool",  [&] { return new(vm) ObjBool(false); }},
            {"char",  [&] { return new(vm) ObjChar('\0'); }},
            {"float", [&] { return new(vm) ObjFloat(0); }},
            {"int",   [&] { return new(vm) ObjInt(0); }}
    }, [&] { return new(vm) Object(sign, type, meta, type->getMembers()); });
}

Obj *Loader::readObj(vector<Obj *> &constPool, ObjInfo &obj) {
    switch (obj.type) {
        case 0x01:
            return readMethod(constPool, obj._method);
        case 0x02:
            return readClass(constPool, obj._class);
        default:
            throw Unreachable();
    }
}

Obj *Loader::readClass(vector<Obj *> &constPool, ClassInfo klass) {
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
    auto sign = getSign(constPool, klass.thisClass);
    vector<Type *> typeParams;
    cast<ObjArray *>(constPool[klass.typeParams])->foreach([this, &typeParams](auto typeParam) {
        // Get the signature of the type parameter
        auto paramSign = typeParam->toString();
        // Make it an unresolved reference
        auto type = Type::TYPE_PARAM_(paramSign, vm);
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
        auto method = readMethod(constPool, sign.toString(), klass.methods[i]);
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

    auto meta = readMeta(klass.meta);

    // Resolve the type params
    for (auto const &key: typeParams) {
        // Remove the unresolved types from ref pool
        referencePool.erase(key->getSign().toString());
    }
    // Resolve the type
    auto type = resolveType(sign.toString(), {sign, kind, typeParams, supers, members, meta});
    vm->setGlobal(sign.toString(), type);
    return type;
}

Obj *Loader::readField(vector<Obj *> &constPool, FieldInfo &field) {
    auto sign = getSign(constPool, field.thisField);
    auto type = findType(constPool[field.type]->toString());
    auto meta = readMeta(field.meta);

    return match<Obj *>(constPool[field.type]->toString(), {
            {"array", [&] { return new(vm) ObjArray(0); }},
            {"bool",  [&] { return new(vm) ObjBool(false); }},
            {"char",  [&] { return new(vm) ObjChar('\0'); }},
            {"float", [&] { return new(vm) ObjFloat(0); }},
            {"int",   [&] { return new(vm) ObjInt(0); }}
    }, [&] { return new(vm) Object(sign, type, meta, type->getMembers()); });
}

Obj *Loader::readMethod(vector<Obj *> &constPool, const string &klassSign, MethodInfo &method) {
    auto type = findType(klassSign);
    auto met = readMethod(constPool, method);
    met->setType(type);
    return met;
}

Obj *Loader::readMethod(vector<Obj *> &constPool, MethodInfo &method) {
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
    auto sign = getSign(constPool, method.thisMethod);
    vector<Type *> typeParams;
    cast<ObjArray *>(constPool[method.typeParams])->foreach([this, &typeParams](auto typeParam) {
        // Get the signature of the type parameter
        auto paramSign = typeParam->toString();
        // Make it an unresolved reference
        auto type = Type::TYPE_PARAM_(paramSign, vm);
        // Remember the type params
        typeParams.push_back(type);
        // Put it in the ref pool
        referencePool[paramSign] = type;
    });
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
    vector<ObjMethod *> lambdas;
    lambdas.reserve(method.lambdaCount);
    for (int i = 0; i < method.lambdaCount; ++i) {
        lambdas.push_back(cast<ObjMethod *>(readMethod(constPool, method.lambdas[i])));
    }
    vector<MatchTable> matches;
    matches.reserve(method.matchCount);
    for (int i = 0; i < method.matchCount; ++i) {
        matches.push_back(readMatch(constPool, method.matches[i]));
    }
    auto meta = readMeta(method.meta);

    // Resolve the type params
    for (auto const &key: typeParams) {
        // Remove the unresolved types from ref pool
        referencePool.erase(key->getSign().toString());
    }
    // Create the frame
    auto *frame = new Frame{constPool,
                            method.codeCount, method.code,
                            method.maxStack,
                            args, locals, exceptions,
                            lines, null};
    auto methodObj = new(vm) ObjMethod(sign, kind, frame, null, typeParams, meta);
    frame->setMethod(methodObj);
    if (kind == ObjMethod::CONSTRUCTOR)
        vm->setGlobal(sign.toString(), methodObj);
    return methodObj;
}

MatchTable Loader::readMatch(vector<Obj *> constPool, MethodInfo::MatchInfo match) {
    vector<Case> cases;
    cases.reserve(match.caseCount);
    for (int i = 0; i < match.caseCount; ++i) {
        auto kase = match.cases[i];
        cases.push_back({constPool[kase.value]->copy(), kase.location});
    }
    return {cases, match.defaultLocation};
}

Exception Loader::readException(vector<Obj *> &constPool, MethodInfo::ExceptionTableInfo &exception) {
    auto type = findType(constPool[exception.exception]->toString());
    return {
            exception.startPc,
            exception.endPc,
            exception.targetPc,
            type,
            readMeta(exception.meta)
    };
}

Local Loader::readLocal(vector<Obj *> &constPool, MethodInfo::LocalInfo &local) {
    auto sign = getSign(constPool, local.thisLocal);
    auto type = findType(constPool[local.type]->toString());
    auto meta = readMeta(local.meta);
    auto obj = match<Obj *>(constPool[local.type]->toString(), {
            {"array", [&] { return new(vm) ObjArray(0); }},
            {"bool",  [&] { return new(vm) ObjBool(false); }},
            {"char",  [&] { return new(vm) ObjChar('\0'); }},
            {"float", [&] { return new(vm) ObjFloat(0); }},
            {"int",   [&] { return new(vm) ObjInt(0); }}
    }, [&] { return new(vm) Object(sign, type, meta, type->getMembers()); });
    return {sign.toString(), obj, meta};
}

Arg Loader::readArg(vector<Obj *> &constPool, MethodInfo::ArgInfo &arg) {
    auto sign = getSign(constPool, arg.thisArg);
    auto type = findType(constPool[arg.type]->toString());
    auto meta = readMeta(arg.meta);
    auto obj = match<Obj *>(constPool[arg.type]->toString(), {
            {"array", [&] { return new(vm) ObjArray(0); }},
            {"bool",  [&] { return new(vm) ObjBool(false); }},
            {"char",  [&] { return new(vm) ObjChar('\0'); }},
            {"float", [&] { return new(vm) ObjFloat(0); }},
            {"int",   [&] { return new(vm) ObjInt(0); }}
    }, [&] { return new(vm) Object(sign, type, meta, type->getMembers()); });
    return {sign.toString(), obj, meta};
}

vector<Obj *> Loader::readConstPool(CpInfo *constantPool, uint16 count) {
    vector<Obj *> list;
    list.reserve(count);
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
    switch (cpInfo.tag) {
        case 0x00:
            return new(vm) ObjNull();
        case 0x01:
            return new(vm) ObjBool(true);
        case 0x02:
            return new(vm) ObjBool(false);
        case 0x03:
            return new(vm) ObjChar((char) cpInfo._char);
        case 0x04:
            return new(vm) ObjInt(unsignedToSigned(cpInfo._int));
        case 0x05:
            return new(vm) ObjFloat(rawToDouble(cpInfo._float));
        case 0x06:
            return new(vm) ObjString(cpInfo._string.bytes, cpInfo._string.len);
        case 0x07: {
            auto con = cpInfo._array;
            auto array = new(vm) ObjArray(con.len);
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

CorruptFileError Loader::corrupt() { return CorruptFileError(libStack.top()->getPath()); }

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
        return new(vm) Type(type);
    }
}

Type *Loader::findType(const string &sign) {
    static const std::set<string> &internalTypes{"array", "bool", "char", "float", "int"};
    if (internalTypes.contains(sign))return null;

    Type *type;

    if (auto find1 = vm->getGlobal(sign); is<Type *>(find1)) { // Try to find in vm globals
        // Get it
        type = cast<Type *>(find1);
    } else if (auto find2 = referencePool.find(sign); find2 !=
                                                      referencePool.end()) { // Try to find the type if it is already present in the ref pool
        type = find2->second;
    } else { // Build an unresolved type in the ref pool and return it
        // Get a sentinel with the name attached to it
        type = Type::SENTINEL_(sign, vm);
        // Put the type
        referencePool[sign] = type;
    }
    return type;
}

Sign Loader::getSign(vector<Obj *> &constPool, cpidx index) {
    return Sign{constPool[index]->toString(), libStack.top()->getId()};
}

