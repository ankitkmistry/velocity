#ifndef SOURCE_LOADER_PARSER_HPP_
#define SOURCE_LOADER_PARSER_HPP_

#include "elfdef.hpp"
#include "../utils/common.hpp"
#include "../utils/exceptions.hpp"

class Parser {
private:
    FILE *file;
    string path;

    MetaInfo parseMetaInfo();

    ObjInfo parseObjInfo();

    ClassInfo parseClassInfo();

    FieldInfo parseFieldInfo();

    MethodInfo parseMethodInfo();

    MethodInfo::LineInfo parseLineInfo();

    MethodInfo::ExceptionTableInfo parseExceptionInfo();

    MethodInfo::LocalInfo parseLocalInfo();

    MethodInfo::ArgInfo parseArgInfo();

    GlobalInfo parseGlobalInfo();

    CpInfo parseCpInfo();

    __Lcon parseLcon();

    __UTF8 parseUTF8();

    uint8 readByte() { return fgetc(file); }

    uint16 readShort() { return readByte() << 8 | readByte(); }

    uint32 readInt() { return readByte() << 16 | readByte() << 8 | readByte(); }

    uint64 readLong() { return readShort() << 16 | readShort(); }

    [[noreturn]]void corruptFileError() {
        throw CorruptFileError(path);
    }

public:
    Parser(FILE *file, string path) : file(file), path(path) {
        if (file == null) throw FileNotFoundError(path);
    }

    ElpInfo parse();
};

#endif /* SOURCE_LOADER_PARSER_HPP_ */
