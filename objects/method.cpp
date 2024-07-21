#include "method.hpp"
#include "../frame/frame.hpp"
#include "../memory/memory.hpp"


ObjMethod::ObjMethod(const Sign &sign, ObjMethod::Kind kind, Frame frame, Type *type,
                     const vector<TypeParam *> &typeParams, ObjModule *module, const Table<string> &meta)
        : ObjCallable(sign, kind, type, module, meta), frame(frame), typeParams(typeParams) {
    frame.setMethod(this);
}

Obj *ObjMethod::copy() const {
    // TODO: Improve the copying
    return new(info.space->getManager()) ObjMethod(sign, kind, frame, type, typeParams, module, meta);
}

void ObjMethod::call(Thread *thread, vector<Obj *> args) {
    auto newFrame = new Frame(frame);
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
        thread->getState().pushFrame(newFrame);
    }
}

void ObjMethod::call(Thread *thread, Obj **args) {
    auto newFrame = new Frame(frame);
    for (int i = 0; i < newFrame->getArgs().count(); i++) {
        newFrame->getArgs().set(i, args[i]);
    }
    thread->getState().pushFrame(newFrame);
}
