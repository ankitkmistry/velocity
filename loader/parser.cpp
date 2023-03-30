#include "parser.hpp"

ElpInfo Parser::parse() {
    ElpInfo elp{};
    elp.magic = readInt();
    elp.minorVersion = readInt();
    elp.majorVersion = readInt();
    elp.compiledFrom = readShort();
    elp.type = readByte();
    elp.entry = readShort();
    elp.imports = readShort();
    elp.constantPoolCount = readShort();
    elp.constantPool = new CpInfo[elp.constantPoolCount];
    for (int i = 0; i < elp.constantPoolCount; ++i) {
        elp.constantPool[i] = parseCpInfo();
    }
    elp.globalsCount = readShort();
    elp.globals = new GlobalInfo[elp.globalsCount];
    for (int i = 0; i < elp.globalsCount; ++i) {
        elp.globals[i] = parseGlobalInfo();
    }
    elp.objectsCount = readShort();
    elp.objects = new ObjInfo[elp.objectsCount];
    for (int i = 0; i < elp.objectsCount; ++i) {
        elp.objects[i] = parseObjInfo();
    }
    elp.meta = parseMetaInfo();
    return elp;
}

MetaInfo Parser::parseMetaInfo() {
    MetaInfo meta{};
    meta.len = readShort();
    meta.table = new MetaInfo::__meta[meta.len];
    for (int i = 0; i < meta.len; ++i) {
        MetaInfo::__meta entry{};
        entry.key = parseUTF8();
        entry.value = parseUTF8();
        meta.table[i] = entry;
    }
    return meta;
}

ObjInfo Parser::parseObjInfo() {
    ObjInfo obj{};
    obj.type = readByte();
    switch (obj.type) {
        case 0x01:
            obj._method = parseMethodInfo();
            break;
        case 0x02:
            obj._class = parseClassInfo();
            break;
        default:
            corruptFileError();
    }
    return obj;
}

ClassInfo Parser::parseClassInfo() {
    ClassInfo klass{};
    klass.constantPoolCount = readShort();
    klass.constantPool = new CpInfo[klass.constantPoolCount];
    for (int i = 0; i < klass.constantPoolCount; ++i) {
        klass.constantPool[i] = parseCpInfo();
    }
    klass.type = readByte();
    klass.accessFlags = readShort();
    klass.thisClass = readShort();
    klass.typeParams = readShort();
    klass.supers = readShort();
    klass.fieldsCount = readShort();
    klass.fields = new FieldInfo[klass.constantPoolCount];
    for (int i = 0; i < klass.constantPoolCount; ++i) {
        klass.fields[i] = parseFieldInfo();
    }
    klass.methodsCount = readShort();
    klass.methods = new MethodInfo[klass.constantPoolCount];
    for (int i = 0; i < klass.constantPoolCount; ++i) {
        klass.methods[i] = parseMethodInfo();
    }
    klass.objectsCount = readShort();
    klass.objects = new ObjInfo[klass.constantPoolCount];
    for (int i = 0; i < klass.constantPoolCount; ++i) {
        klass.objects[i] = parseObjInfo();
    }
    klass.meta = parseMetaInfo();
    return klass;
}

FieldInfo Parser::parseFieldInfo() {
    FieldInfo field{};
    field.accessFlags = readByte();
    field.thisField = readShort();
    field.type = readShort();
    field.meta = parseMetaInfo();
    return field;
}

MethodInfo Parser::parseMethodInfo() {
    MethodInfo method{};
    method.accessFlags = readShort();
    method.type = readByte();
    method.thisMethod = readShort();
    method.argsCount = readByte();
    method.args = new MethodInfo::ArgInfo[method.argsCount];
    for (int i = 0; i < method.argsCount; i++) {
        method.args[i] = parseArgInfo();
    }
    method.localsCount = readShort();
    method.closureStart = readShort();
    method.locals = new MethodInfo::LocalInfo[method.localsCount];
    for (int i = 0; i < method.localsCount; i++) {
        method.locals[i] = parseLocalInfo();
    }
    method.maxStack = readInt();
    method.codeCount = readInt();
    method.code = new uint8[method.codeCount];
    for (int i = 0; i < method.codeCount; i++) {
        method.code[i] = readByte();
    }
    method.exceptionTableCount = readShort();
    method.exceptionTable =
            new MethodInfo::ExceptionTableInfo[method.exceptionTableCount];
    for (int i = 0; i < method.exceptionTableCount; i++) {
        method.exceptionTable[i] = parseExceptionInfo();
    }
    method.lineNumberTableCount = readInt();
    method.lineNumberTable =
            new MethodInfo::LineInfo[method.lineNumberTableCount];
    for (int i = 0; i < method.lineNumberTableCount; i++) {
        method.lineNumberTable[i] = parseLineInfo();
    }
    method.meta = parseMetaInfo();
    return method;
}

MethodInfo::LineInfo Parser::parseLineInfo() {
    MethodInfo::LineInfo line{};
    line.byteCode = readInt();
    line.sourceCode = readLong();
    return line;
}

MethodInfo::ExceptionTableInfo Parser::parseExceptionInfo() {
    MethodInfo::ExceptionTableInfo exception{};
    exception.startPc = readInt();
    exception.endPc = readInt();
    exception.targetPc = readInt();
    exception.exception = readShort();
    exception.meta = parseMetaInfo();
    return exception;
}

MethodInfo::LocalInfo Parser::parseLocalInfo() {
    MethodInfo::LocalInfo local{};
    local.flags = readByte();
    local.thisLocal = readShort();
    local.type = readShort();
    local.meta = parseMetaInfo();
    return local;
}

MethodInfo::ArgInfo Parser::parseArgInfo() {
    MethodInfo::ArgInfo arg{};
    arg.flags = readByte();
    arg.thisArg = readShort();
    arg.type = readShort();
    arg.meta = parseMetaInfo();
    return arg;
}

GlobalInfo Parser::parseGlobalInfo() {
    GlobalInfo global{};
    global.flags = readByte();
    global.thisGlobal = readShort();
    global.type = readShort();
    global.meta = parseMetaInfo();
    return global;
}

CpInfo Parser::parseCpInfo() {
    CpInfo cp{};
    cp.tag = readByte();
    switch (cp.tag) {
        case 0x03:
            cp._char = readInt();
            break;
        case 0x04:
            cp._int = readLong();
            break;
        case 0x05:
            cp._float = readLong();
            break;
        case 0x06:
            cp._string = parseUTF8();
            break;
        case 0x07:
            cp._array = parseLcon();
            break;
        default:
            corruptFileError();
    }
    return cp;
}

__Lcon Parser::parseLcon() {
    __Lcon lcon{};
    lcon.len = readShort();
    lcon.items = new CpInfo[lcon.len];
    for (int i = 0; i < lcon.len; ++i) {
        lcon.items[i] = parseCpInfo();
    }
    return lcon;
}

__UTF8 Parser::parseUTF8() {
    __UTF8 utf8{};
    utf8.len = readShort();
    utf8.bytes = new uint8[utf8.len];
    for (int i = 0; i < utf8.len; ++i) {
        utf8.bytes[i] = readByte();
    }
    return utf8;
}
