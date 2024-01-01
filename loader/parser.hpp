#ifndef SOURCE_LOADER_PARSER_HPP_
#define SOURCE_LOADER_PARSER_HPP_

#include "elpdef.hpp"
#include "../utils/common.hpp"
#include "../utils/exceptions.hpp"

class Parser {
private:
    uint32 index = 0;
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

    MethodInfo::MatchInfo parseMatchInfo();

    MethodInfo::MatchInfo::CaseInfo parseCaseInfo();

    GlobalInfo parseGlobalInfo();

    CpInfo parseCpInfo();

    __Container parseContainer();

    __UTF8 parseUTF8();

    uint8 readByte() {
        index++;
        return fgetc(file);
    }

    uint16 readShort() {
        uint8 a = readByte();
        uint8 b = readByte();
        return a << 8 | b;
    }

    uint32 readInt() {
        uint16 a = readShort();
        uint16 b = readShort();
        return a << 16 | b;
    }

    uint64 readLong() {
        uint64 a = static_cast<uint64>(readInt());
        uint32 b = readInt();
        return a << 32 | b;
    }
    [[noreturn]]void corruptFileError() {
        throw CorruptFileError(path);
    }

public:
    Parser(FILE *file, const string &path) : file(file), path(path) {
        if (file == null) throw FileNotFoundError(path);
    }

    /**
     * This function parses the file associated with this parser
     * and returns the bytecode data
     * @return The bytecode data in the form of ElpInfo
     */
    ElpInfo parse();
};

#endif /* SOURCE_LOADER_PARSER_HPP_ */
