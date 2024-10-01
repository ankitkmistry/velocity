#include "method.hpp"
#include "../ee/thread.hpp"

namespace spade
{
    Table<map<Table<Type *>, ObjMethod *>> ObjMethod::reificationTable = {};

    ObjMethod::ObjMethod(const Sign &sign, Kind kind, FrameTemplate *frame, Type *type, Table<NamedRef *> typeParams,
                         ObjModule *module)
        : ObjCallable(sign, kind, type, module), typeParams(typeParams), frameTemplate(frame) {
        frameTemplate->setMethod(this);
    }

    Obj *ObjMethod::copy() const {
        Table<NamedRef *> newTypeParams;
        for (auto [name, typeParam]: typeParams) {
            newTypeParams[name] =
                    halloc<NamedRef>(info.manager, typeParam->getName(), typeParam->getValue()->copy(), typeParam->getMeta());
        }
        Obj *newMethod = halloc<ObjMethod>(info.manager, sign, kind, frameTemplate->copy(), type, newTypeParams, module);
        Obj::reify(&newMethod, typeParams, newTypeParams);
        return newMethod;
    }

    void ObjMethod::call(vector<Obj *> args) {
        validateCallSite();
        Thread *thread = Thread::current();
        auto newFrame = frameTemplate->initialize();
        if (newFrame.getArgs().count() < args.size()) {
            throw ArgumentError(sign.toString(),
                                format("too less arguments, expected %d got %d", newFrame.getArgs().count(), args.size()));
        } else if (newFrame.getArgs().count() > args.size()) {
            throw ArgumentError(sign.toString(),
                                format("too many arguments, expected %d got %d", newFrame.getArgs().count(), args.size()));
        } else {
            for (int i = 0; i < newFrame.getArgs().count(); i++) { newFrame.getArgs().set(i, args[i]); }
            thread->getState()->pushFrame(newFrame);
        }
    }

    void ObjMethod::call(Obj **args) {
        validateCallSite();
        Thread *thread = Thread::current();
        auto newFrame = frameTemplate->initialize();
        for (int i = 0; i < newFrame.getArgs().count(); i++) { newFrame.getArgs().set(i, args[i]); }
        thread->getState()->pushFrame(newFrame);
    }

    string ObjMethod::toString() const {
        static string kindNames[] = {"function", "method", "constructor"};
        return format("<%s '%s'>", kindNames[static_cast<int>(kind)].c_str(), sign.toString().c_str());
    }

    ObjMethod *ObjMethod::returnReified(Table<Type *> tParams) const {
        auto method = cast<ObjMethod *>(copy());
        auto params = method->getTypeParams();
        for (auto [name, typeparam]: params) { cast<TypeParam *>(typeparam->getValue())->setPlaceholder(tParams[name]); }
        return method;
    }

    ObjMethod *ObjMethod::getReified(Obj **args, uint8 count) {
        if (typeParams.size() != count) {
            throw ArgumentError(sign.toString(), format("expected %d type arguments, but got %d", typeParams.size(), count));
        }

        Table<Type *> typeArgs;
        for (int i = 0; i < count; ++i) { typeArgs[getSign().getTypeParams()[i]] = (cast<Type *>(args[i])); }

        map<Table<Type *>, ObjMethod *> table;
        ObjMethod *reifiedMethod;

        try {
            table = reificationTable.at(getSign().toString());
        } catch (const std::out_of_range &) {
            reifiedMethod = returnReified(typeArgs);
            table[typeArgs] = reifiedMethod;
            reificationTable[getSign().toString()] = table;
            return reifiedMethod;
        }

        try {
            return table.at(typeArgs);
        } catch (const std::out_of_range &) {
            reifiedMethod = returnReified(typeArgs);
            reificationTable[getSign().toString()][typeArgs] = reifiedMethod;
            return reifiedMethod;
        }
    }

    ObjMethod *ObjMethod::getReified(vector<Type *> args) {
        if (args.size() >= UINT8_MAX) {
            throw ArgumentError(toString(), "number of type arguments cannot be greater than 256");
        }
        auto data = args.data();
        return getReified(reinterpret_cast<Obj **>(&data), static_cast<uint8>(args.size()));
    }

    void ObjMethod::setSelf(Obj *self) {
        if (frameTemplate->getLocals().count() == 0) return;
        auto local = frameTemplate->getLocals().getLocal(0);
        local->setValue(self);
        local->setNoCopy(true);
    }

    TypeParam *ObjMethod::getTypeParam(string name) const {
        try {
            return cast<TypeParam *>(typeParams.at(name)->getValue());
        } catch (const std::out_of_range &) {
            if (type != null) { return type->getTypeParam(name); }
            throw IllegalAccessError(format("cannot find typeparam %s in %s", name.c_str(), toString().c_str()));
        }
    }

    NamedRef *ObjMethod::captureTypeParam(string name) {
        try {
            return typeParams.at(name);
        } catch (const std::out_of_range &) {
            if (type != null) { return type->captureTypeParam(name); }
            throw IllegalAccessError(format("cannot find typeparam %s in %s", name.c_str(), toString().c_str()));
        }
    }
} // namespace spade
