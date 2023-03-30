#ifndef SOURCE_LOADER_PARSER_HPP_
#define SOURCE_LOADER_PARSER_HPP_

#include "elfdef.hpp"
#include "../utils/common.hpp"
#include "../utils/exceptions.hpp"

class Parser {
private:
    uint32 index=0;
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

    uint8 readByte() { index++;return fgetc(file); }

    uint16 readShort() { return readByte() << 8 | readByte(); }

    uint32 readInt() { return readShort() << 16 | readShort(); }

    uint64 readLong() { return static_cast<uint64>(readInt()) << 32 | readInt(); }

    [[noreturn]]void corruptFileError() {
        throw CorruptFileError(path);
    }

public:
    Parser(FILE *file, const string& path) : file(file), path(path) {
        if (file == null) throw FileNotFoundError(path);
    }

    ElpInfo parse();
};

#endif /* SOURCE_LOADER_PARSER_HPP_ */
