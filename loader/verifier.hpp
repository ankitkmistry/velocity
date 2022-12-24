#ifndef SOURCE_LOADER_VERIFIER_HPP_
#define SOURCE_LOADER_VERIFIER_HPP_

#include "elfdef.hpp"
#include "../utils/common.hpp"
#include "../utils/exceptions.hpp"

class Verifier {
private:
    const ElpInfo elp;
    const string path;

    void checkObj(ObjInfo object, uint16 count);

    void checkClass(ClassInfo klass);

    void checkField(FieldInfo field, uint16 count);

    void checkMethod(MethodInfo method, uint16 count);

    void checkLocal(MethodInfo::LocalInfo local, uint16 count);

    void checkLine(MethodInfo::LineInfo line, uint16 codeCount);

    void checkException(MethodInfo::ExceptionTableInfo exception, uint16 count);

    void checkArg(MethodInfo::ArgInfo arg, uint16 count);

    void checkGlobal(GlobalInfo global, uint16 count);

    void checkRange(ui4 i, ui4 count);

    CorruptFileError corrupt() {
        return CorruptFileError(path);
    }

public:
    Verifier(const ElpInfo elp, const string path) : elp(elp), path(path) {}

    void check();
};

#endif /* SOURCE_LOADER_VERIFIER_HPP_ */
