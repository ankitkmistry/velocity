#include "method.hpp"
#include "typeparam.hpp"


ObjMethod::ObjMethod(const Sign &sign, Kind kind, FrameTemplate *frame, Type *type,
                     vector<TypeParam *> typeParams, ObjModule *module, const Table<string> &meta)
        : ObjCallable(sign, kind, type, module, meta), typeParams(typeParams),
          frameTemplate(frame) {
    frameTemplate->setMethod(this);
}

Obj *ObjMethod::copy() const {
    vector<TypeParam *> newTypeParams;
    for (auto typeParam: typeParams) {
        newTypeParams.push_back(cast<TypeParam *>(typeParam->copy()));
    }
    Obj *newMethod = Obj::alloc<ObjMethod>(info.manager,
                                           sign, kind, frameTemplate->copy(),
                                           type, newTypeParams, module, meta);
    Obj::reify(&newMethod, typeParams, newTypeParams);
    return newMethod;
}

void ObjMethod::call(Thread *thread, vector<Obj *> args) {
    auto newFrame = frameTemplate->initialize();
    if (newFrame->getArgs().count() < args.size()) {
        throw ArgumentError(sign.toString(),
                            format("too less arguments, expected %d got %d", newFrame->getArgs().count(), args.size()));
    } else if (newFrame->getArgs().count() > args.size()) {
        throw ArgumentError(sign.toString(),
                            format("too many arguments, expected %d got %d", newFrame->getArgs().count(), args.size()));
    } else {
        for (int i = 0; i < newFrame->getArgs().count(); i++) {
            newFrame->getArgs().set(i, args[i]);
        }
        thread->getState()->pushFrame(newFrame);
    }
}

void ObjMethod::call(Thread *thread, Obj **args) {
    auto newFrame = frameTemplate->initialize();
    for (int i = 0; i < newFrame->getArgs().count(); i++) {
        newFrame->getArgs().set(i, args[i]);
    }
    thread->getState()->pushFrame(newFrame);
}

string ObjMethod::toString() const {
    static string kindNames[] = {
            "function",
            "method",
            "constructor"
    };
    return format("<%s '%s'>", kindNames[kind].c_str(), sign.toString().c_str());
}
