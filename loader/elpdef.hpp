#ifndef LOADER_ELPDEF_HPP_
#define LOADER_ELPDEF_HPP_

#include "../utils/common.hpp"

typedef uint8_t ui1;
typedef uint16_t ui2;
typedef uint32_t ui4;
typedef uint64_t ui8;

typedef ui2 cpidx;

struct __UTF8 {
    ui2 len;
    ui1 *bytes;
};

struct CpInfo;

struct __Container {
    ui2 len;
    CpInfo *items;
};

struct CpInfo {
    ui1 tag;
    union {
        ui4 _char;
        ui8 _int;
        ui8 _float;
        __UTF8 _string;
        __Container _array;
    };
};

struct MetaInfo {
    ui2 len;
    struct __meta {
        __UTF8 key;
        __UTF8 value;
    } *table;
};

struct GlobalInfo {
    ui1 flags;
    cpidx thisGlobal;
    cpidx type;
    MetaInfo meta;
};

struct FieldInfo {
    ui2 accessFlags;
    cpidx thisField;
    cpidx type;
    MetaInfo meta;
};

struct MethodInfo {
    ui2 accessFlags;
    ui1 type;
    cpidx thisMethod;

    ui2 constantPoolCount;
    CpInfo *constantPool;

    cpidx typeParams;

    ui1 argsCount;
    struct ArgInfo {
        ui1 flags;
        cpidx thisArg;
        cpidx type;
        MetaInfo meta;
    } *args;

    ui2 localsCount;
    ui2 closureStart;
    struct LocalInfo {
        ui1 flags;
        cpidx thisLocal;
        cpidx type;
        MetaInfo meta;
    } *locals;

    ui4 maxStack;
    ui4 codeCount;
    ui1 *code;

    ui2 exceptionTableCount;
    struct ExceptionTableInfo {
        ui4 startPc;
        ui4 endPc;
        ui4 targetPc;
        cpidx exception;
        MetaInfo meta;
    } *exceptionTable;

    ui4 lineNumberTableCount;
    struct LineInfo {
        ui4 byteCode;
        ui8 sourceCode;
    } *lineNumberTable;

    MetaInfo meta;
};

struct ObjInfo;

struct ClassInfo {
    ui1 type;
    ui2 accessFlags;
    cpidx thisClass;
    cpidx typeParams;
    cpidx supers;
    ui2 fieldsCount;
    FieldInfo *fields;
    ui2 methodsCount;
    MethodInfo *methods;
    ui2 objectsCount;
    ObjInfo *objects;
    MetaInfo meta;
};

struct ObjInfo {
    ui1 type;
    union {
        MethodInfo _method;
        ClassInfo _class;
    };
};

struct ElpInfo {
    ui4 magic;
    ui4 minorVersion;
    ui4 majorVersion;
    cpidx compiledFrom;
    ui1 type;
    cpidx entry;
    cpidx imports;
    ui2 constantPoolCount;
    CpInfo *constantPool;
    ui2 globalsCount;
    GlobalInfo *globals;
    ui2 objectsCount;
    ObjInfo *objects;
    MetaInfo meta;
};

#endif /* LOADER_ELPDEF_HPP_ */
