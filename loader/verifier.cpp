#include "verifier.hpp"

void Verifier::check() {
    auto magic = elp.magic;
    switch (elp.type) {
        case 0x01: {
            if (magic != 0xc0ffeede)
                throw corrupt();
            break;
        }
        case 0x02: {
            if (magic != 0x6020cafe)
                throw corrupt();
            break;
        }
        default:
            throw corrupt();
    }

    auto cpCount = elp.constantPoolCount;
    for (int i = 0; i < elp.globalsCount; i++) {
        checkGlobal(elp.globals[i], cpCount);
    }
    for (int i = 0; i < elp.objectsCount; i++) {
        checkObj(elp.objects[i], cpCount);
    }
}

void Verifier::checkObj(ObjInfo object, uint16 count) {
    switch (object.type) {
        case 0x01:
            checkMethod(object._method, count);
            break;
        case 0x02:
            checkClass(object._class);
            break;
        default:
            throw corrupt();
    }
}

void Verifier::checkClass(ClassInfo klass) {
    uint8 cpCount = klass.constantPoolCount;
    if (klass.type < 0x01 || klass.type > 0x04)
        throw corrupt();
    checkRange(klass.thisClass, cpCount);
    checkRange(klass.supers, cpCount);

    for (int i = 0; i < klass.fieldsCount; i++) {
        checkField(klass.fields[i], cpCount);
    }
    for (int i = 0; i < klass.methodsCount; i++) {
        checkMethod(klass.methods[i], cpCount);
    }
    for (int i = 0; i < klass.objectsCount; i++) {
        checkObj(klass.objects[i], cpCount);
    }
}

void Verifier::checkField(FieldInfo field, uint16 count) {
    checkRange(field.thisField, count);
    checkRange(field.type, count);
}

void Verifier::checkMethod(MethodInfo method, uint16 cpCount) {
    if (method.type != 0x01 && method.type != 0x02) {
        throw corrupt();
    }
    checkRange(method.thisMethod, cpCount);
    for (int i = 0; i < method.argsCount; i++) {
        checkArg(method.args[i], cpCount);
    }
    for (int i = 0; i < method.localsCount; i++) {
        checkLocal(method.locals[i], cpCount);
    }
    for (int i = 0; i < method.exceptionTableCount; i++) {
        checkException(method.exceptionTable[i], cpCount);
    }
    uint32 codeCount = method.codeCount;
    for (int i = 0; i < method.lineNumberTableCount; i++) {
        checkLine(method.lineNumberTable[i], codeCount);
    }
}

void Verifier::checkLocal(MethodInfo::LocalInfo local, uint16 cpCount) {
    if (local.flags != 0x01 && local.flags != 0x02) {
        throw corrupt();
    }
    checkRange(local.thisLocal, cpCount);
    checkRange(local.type, cpCount);
}

void Verifier::checkLine(MethodInfo::LineInfo line, uint16 codeCount) {
    checkRange(line.byteCode, codeCount);
}

void Verifier::checkException(MethodInfo::ExceptionTableInfo exception,
                              uint16 count) {
    checkRange(exception.exception, count);
}

void Verifier::checkArg(MethodInfo::ArgInfo arg, uint16 cpCount) {
    if (arg.flags != 0x01 && arg.flags != 0x02 && arg.flags != 0x03) {
        throw corrupt();
    }
    checkRange(arg.thisArg, cpCount);
    checkRange(arg.type, cpCount);
}

void Verifier::checkGlobal(GlobalInfo global, uint16 cpCount) {
    if (global.flags != 0x01 && global.flags != 0x02)
        throw corrupt();
    checkRange(global.thisGlobal, cpCount);
    checkRange(global.type, cpCount);
}

void Verifier::checkRange(ui4 i, ui4 count) {
    if (i >= count) {
        throw corrupt();
    }
}

