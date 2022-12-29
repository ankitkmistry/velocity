#include "vm.hpp"
#include "../oop/objects.hpp"
#include "opcode.hpp"
#include "../oop/type.hpp"

void VM::onExit(function<void()> fun) {
    onExitList.push_back(fun);
}

int VM::start(const string &filename, vector<string> args) {
    // Load the file and get the entry point
    auto entry = loader.load(filename);
    // Complain if there is no entry point
    if (entry == null)throw new EntryPointNotFoundError(filename);
    if (entry->getFrame()->getArgs().count() != 1)
        runtimeError("entry point must have one argument (string[]): " + entry->getSign().toString());
    // Execute from the entry
    return start(entry, argsRepr(args));
}

ObjArray *VM::argsRepr(const vector<string> &args) {
    auto array = new ObjArray(args.size());
    for (int i = 0; i < args.size(); ++i) {
        array->set(i, new ObjString(args[i]));
    }
    return array;
}

int VM::start(ObjMethod *entry, ObjArray *args) {
    entry->getFrame()->getLocals().set(0, args);
    Thread thread{VMState(this, entry->getFrame()), [&](auto thr) { run(thr); }};
    threads.insert(&thread);
    thread.join();

    threads.erase(&thread);
    if (threads.empty()) {
        for (auto &item: onExitList)
            item();
        // Clean the globals
        // Clean the heap
    }
    return thread.getExitCode();
}

runtime_error VM::runtimeError(string str) {
    return runtime_error{str};
}

Obj *VM::getGlobal(string sign) {
    auto it = globals.find(sign);
    if (it == globals.end())
        return null;
    return it->second;
}

void VM::setGlobal(string sign, Obj *val) {
    globals[sign] = val;
}

void VM::run(Thread *thread) {
    auto state = thread->getState();
    for (;;) {
        auto opcode = static_cast<Opcode>(state.readByte());
        auto frame = state.getFp();
//        DebugOP.printVMState(state);
        switch (opcode) {
            case Opcode::NOP:
                // Do nothing
                break;
            case Opcode::CONSTANT:
                state.push(state.loadConst(state.readByte()));
                break;
            case Opcode::LONG_CONSTANT:
                state.push(state.loadConst(state.readShort()));
                break;
            case Opcode::POP:
                state.pop();
                break;
            case Opcode::DUP:
                state.push(state.peek());
                break;
            case Opcode::LOAD_GLOBAL:
                state.push(getGlobal(state.loadConst(state.readShort())->toString()));
                break;
            case Opcode::STORE_GLOBAL:
                setGlobal(state.loadConst(state.readShort())->toString(), state.peek());
                break;
            case Opcode::LOAD_LOCAL:
                state.push(frame->getLocals().get(state.readShort()));
                break;
            case Opcode::STORE_LOCAL:
                frame->getLocals().set(state.readShort(), state.peek());
                break;
            case Opcode::LOAD_GLOBAL_FAST:
                state.push(getGlobal(state.loadConst(state.readByte())->toString()));
                break;
            case Opcode::STORE_GLOBAL_FAST:
                setGlobal(state.loadConst(state.readByte())->toString(), state.peek());
                break;
            case Opcode::LOAD_LOCAL_FAST:
                state.push(frame->getLocals().get(state.readByte()));
                break;
            case Opcode::STORE_LOCAL_FAST:
                frame->getLocals().set(state.readByte(), state.peek());
                break;
            case Opcode::POP_STORE_GLOBAL:
                setGlobal(state.loadConst(state.readShort())->toString(), state.pop());
                break;
            case Opcode::POP_STORE_LOCAL:
                frame->getLocals().set(state.readShort(), state.pop());
                break;
            case Opcode::POP_STORE_GLOBAL_FAST:
                setGlobal(state.loadConst(state.readByte())->toString(), state.pop());
                break;
            case Opcode::POP_STORE_LOCAL_FAST:
                frame->getLocals().set(state.readByte(), state.pop());
                break;
            case Opcode::LOAD_ARG:
                state.push(frame->getArgs().get(state.readByte()));
                break;
            case Opcode::STORE_ARG:
                frame->getArgs().set(state.readByte(), state.peek());
                break;
            case Opcode::POP_STORE_ARG:
                frame->getArgs().set(state.readByte(), state.pop());
                break;
            case Opcode::LOAD_MEMBER: {
                auto object = cast<Object *>(state.pop());
                auto name = Sign(state.loadConst(state.readShort())->toString()).getName();
                Obj *member = object->getMember(name);
                if (is<ObjMethod *>(member)) {
                    auto method = cast<ObjMethod *>(member);
                    method->getFrame()->getLocals().set(0, object);
                }
                state.push(member);
                break;
            }
            case Opcode::STORE_MEMBER: {
                auto object = cast<Object *>(state.pop());
                auto value = state.peek();
                auto name = Sign(state.loadConst(state.readShort())->toString()).getName();
                object->getMembers()[name] = value;
                break;
            }
            case Opcode::LOAD_STATIC: {
                auto type = cast<Type *>(state.pop());
                auto name = Sign(state.loadConst(state.readShort())->toString()).getName();
                state.push(type->getMember(name));
                break;
            }
            case Opcode::STORE_STATIC: {
                auto type = cast<Type *>(state.pop());
                auto value = state.peek();
                auto name = Sign(state.loadConst(state.readShort())->toString()).getName();
                type->getMembers()[name] = value;
                break;
            }
            case Opcode::LOAD_MEMBER_FAST: {
                auto object = cast<Object *>(state.pop());
                auto name = Sign(state.loadConst(state.readByte())->toString()).getName();
                Obj *member = object->getMember(name);
                if (is<ObjMethod *>(member)) {
                    auto method = dynamic_cast<ObjMethod *>(member);
                    method->getFrame()->getLocals().set(0, object);
                }
                state.push(member);
                break;
            }
            case Opcode::STORE_MEMBER_FAST: {
                auto object = cast<Object *>(state.pop());
                auto value = state.peek();
                auto name = Sign(state.loadConst(state.readByte())->toString()).getName();
                object->getMembers()[name] = value;
                break;
            }
            case Opcode::LOAD_STATIC_FAST: {
                auto type = cast<Type *>(state.pop());
                auto name = Sign(state.loadConst(state.readByte())->toString()).getName();
                state.push(type->getMember(name));
                break;
            }
            case Opcode::STORE_STATIC_FAST: {
                auto type = cast<Type *>(state.pop());
                auto value = state.peek();
                auto name = Sign(state.loadConst(state.readByte())->toString()).getName();
                type->getMembers()[name] = value;
                break;
            }
            case Opcode::POP_STORE_MEMBER: {
                auto object = cast<Object *>(state.pop());
                auto value = state.pop();
                auto name = Sign(state.loadConst(state.readShort())->toString()).getName();
                object->getMembers()[name] = value;
                break;
            }
            case Opcode::POP_STORE_STATIC: {
                auto type = cast<Type *>(state.pop());
                auto value = state.pop();
                auto name = Sign(state.loadConst(state.readShort())->toString()).getName();
                type->getMembers()[name] = value;
                break;
            }
            case Opcode::POP_STORE_MEMBER_FAST: {
                auto object = cast<Object *>(state.pop());
                auto value = state.pop();
                auto name = Sign(state.loadConst(state.readByte())->toString()).getName();
                object->getMembers()[name] = value;
                break;
            }
            case Opcode::POP_STORE_STATIC_FAST: {
                auto type = cast<Type *>(state.pop());
                auto value = state.pop();
                auto name = Sign(state.loadConst(state.readByte())->toString()).getName();
                type->getMembers()[name] = value;
                break;
            }
            case Opcode::LOAD_OBJECT: {
                // Get the sign
                auto sign = state.loadConst(state.readShort())->toString();
                // Retrieve the method
                auto method = cast<ObjMethod *>(getGlobal(sign));
                // Check if it is a constructor
                if (method->getKind() != ObjMethod::CONSTRUCTOR) {
                    throw runtimeError(format("'%s' not a constructor", sign.c_str()));
                }
                // Get the count
                auto count = method->getFrame()->getArgs().count();
                // Pop the arguments
                for (int i = 0; i < count; i++) state.pop();
                // Call the method
                call(thread, method, frame->getSp());
                break;
            }
            case Opcode::LOAD_OBJECT_FAST: {
                // Get the sign
                auto sign = state.loadConst(state.readByte())->toString();
                // Retrieve the method
                auto method = cast<ObjMethod *>(getGlobal(sign));
                // Check if it is a constructor
                if (method->getKind() != ObjMethod::CONSTRUCTOR) {
                    throw runtimeError(format("'%s' not a constructor", sign.c_str()));
                }
                // Get the count
                auto count = method->getFrame()->getArgs().count();
                // Pop the arguments
                for (int i = 0; i < count; i++) state.pop();
                // Call the method
                call(thread, method, frame->getSp());
                break;
            }
            case Opcode::UNPACK_ARRAY: {
                auto array = cast<ObjArray *>(state.pop());
                for (auto item: *array) {
                    state.push(item);
                }
                break;
            }
            case Opcode::BUILD_ARRAY: {
                auto count = state.readShort();
                auto array = new ObjArray(count);
                state.push(array);
                break;
            }
            case Opcode::BUILD_ARRAY_FAST: {
                auto count = state.readByte();
                auto array = new ObjArray(count);
                state.push(array);
                break;
            }
            case Opcode::LOAD_INDEX: {
                auto array = cast<ObjArray *>(state.pop());
                auto index = cast<ObjInt *>(state.pop());
                state.push(array->get(index->value()));
                break;
            }
            case Opcode::STORE_INDEX: {
                auto array = cast<ObjArray *>(state.pop());
                auto index = cast<ObjInt *>(state.pop());
                auto value = state.peek();
                array->set(index->value(), value);
                break;
            }
            case Opcode::POP_STORE_INDEX: {
                auto array = cast<ObjArray *>(state.pop());
                auto index = cast<ObjInt *>(state.pop());
                auto value = state.pop();
                array->set(index->value(), value);
                break;
            }
            case Opcode::LOAD_LENGTH: {
                auto array = cast<ObjArray *>(state.pop());
                state.push(new ObjInt(array->count()));
                break;
            }
            case Opcode::INVOKE: {
                // Get the count
                auto count = state.readByte();
                // Pop the arguments
                for (int i = 0; i < count; i++) state.pop();
                // Get the method
                auto method = cast<ObjMethod *>(state.pop());
                // Call it
                call(thread, method, frame->getSp());
                break;
            }
            case Opcode::INVOKE_VIRTUAL: {
                // Get the sign
                Sign sign{state.loadConst(state.readShort())->toString()};
                // Get name of the method
                auto name = sign.getName();
                // Get the arg count
                auto count = sign.getArgsCount();

                // Pop the arguments
                for (int i = 0; i < count; i++) state.pop();
                // Get the object
                auto object = cast<Object *>(state.pop());
                // Get the method
                auto method = cast<ObjMethod *>(object->getMember(name));
                // Call it
                call(thread, method, frame->getSp());
                // Set 'this' (by convention slot 0 of locals)
                state.getFp()->getLocals().set(0, object);
                break;
            }
            case Opcode::INVOKE_STATIC: {
                // Get the sign
                Sign sign{state.loadConst(state.readShort())->toString()};
                // Get name of the method
                auto name = sign.getName();
                // Get the arg count
                auto count = sign.getArgsCount();

                // Pop the arguments
                for (int i = 0; i < count; i++) state.pop();
                // Get the type
                auto type = cast<Type *>(state.pop());
                // Get the method
                auto method = cast<ObjMethod *>(type->getMember(name));
                // Call it
                call(thread, method, frame->getSp());
                break;
            }
            case Opcode::INVOKE_LOCAL: {
                // Get the method
                auto method = cast<ObjMethod *>(frame->getLocals().get(state.readShort()));
                // Get the arg count
                auto count = method->getFrame()->getArgs().count();
                // Pop the arguments
                for (int i = 0; i < count; i++) state.pop();
                // Call it
                call(thread, method, frame->getSp());
                break;
            }
            case Opcode::INVOKE_GLOBAL: {
                // Get the method
                auto method = cast<ObjMethod *>(getGlobal(state.loadConst(state.readShort())->toString()));
                // Get the arg count
                auto count = method->getFrame()->getArgs().count();
                // Pop the arguments
                for (int i = 0; i < count; i++) state.pop();
                // Call it
                call(thread, method, frame->getSp());
                break;
            }
            case Opcode::INVOKE_VIRTUAL_FAST: {
                // Get the sign
                Sign sign{state.loadConst(state.readByte())->toString()};
                // Get name of the method
                auto name = sign.getName();
                // Get the arg count
                auto count = sign.getArgsCount();

                // Pop the arguments
                for (int i = 0; i < count; i++) state.pop();
                // Get the object
                auto object = cast<Object *>(state.pop());
                // Get the method
                auto method = cast<ObjMethod *>(object->getMember(name));
                // Call it
                call(thread, method, frame->getSp());
                // Set 'this' (by convention slot 0 of locals)
                state.getFp()->getLocals().set(0, object);
                break;
            }
            case Opcode::INVOKE_STATIC_FAST: {
                // Get the sign
                Sign sign{state.loadConst(state.readByte())->toString()};
                // Get name of the method
                auto name = sign.getName();
                // Get the arg count
                auto count = sign.getArgsCount();

                // Pop the arguments
                for (int i = 0; i < count; i++) state.pop();
                // Get the type
                auto type = cast<Type *>(state.pop());
                // Get the method
                auto method = cast<ObjMethod *>(type->getMember(name));
                // Call it
                call(thread, method, frame->getSp());
                break;
            }
            case Opcode::INVOKE_LOCAL_FAST: {
                // Get the method
                auto method = cast<ObjMethod *>(frame->getLocals().get(state.readByte()));
                // Get the arg count
                auto count = method->getFrame()->getArgs().count();
                // Pop the arguments
                for (int i = 0; i < count; i++) state.pop();
                // Call it
                call(thread, method, frame->getSp());
                break;
            }
            case Opcode::INVOKE_GLOBAL_FAST: {
                // Get the method
                auto method = cast<ObjMethod *>(getGlobal(state.loadConst(state.readByte())->toString()));
                // Get the arg count
                auto count = method->getFrame()->getArgs().count();
                // Pop the arguments
                for (int i = 0; i < count; i++) state.pop();
                // Call it
                call(thread, method, frame->getSp());
                break;
            }
            case Opcode::INVOKE_ARG: {
                // Get the method
                auto method = cast<ObjMethod *>(frame->getArgs().get(state.readByte()));
                // Get the arg count
                auto count = method->getFrame()->getArgs().count();
                // Pop the arguments
                for (int i = 0; i < count; i++) state.pop();
                // Call it
                call(thread, method, frame->getSp());
                break;
            }
            case Opcode::SUB_CALL: {
                auto address = new ObjInt(frame->getIp() - frame->getCode());
                state.push(address);
                auto offset = state.readShort();
                state.adjust(offset);
                break;
            }
            case Opcode::SUB_RETURN: {
                auto address = cast<ObjInt *>(state.pop());
                frame->setIp(frame->getCode() + address->value());
                break;
            }
            case Opcode::JUMP_FORWARD: {
                auto offset = state.readShort();
                state.adjust(offset);
                break;
            }
            case Opcode::JUMP_BACKWARD: {
                auto offset = state.readShort();
                state.adjust(-offset);
                break;
            }
            case Opcode::JUMP_IF_TRUE: {
                auto obj = state.peek();
                auto offset = state.readShort();
                if (obj->truth())state.adjust(offset);
                break;
            }
            case Opcode::JUMP_IF_FALSE: {
                auto obj = state.peek();
                auto offset = state.readShort();
                if (!obj->truth())state.adjust(offset);
                break;
            }
            case Opcode::POP_JUMP_IF_TRUE: {
                auto obj = state.pop();
                auto offset = state.readShort();
                if (obj->truth())state.adjust(offset);
                break;
            }
            case Opcode::POP_JUMP_IF_FALSE: {
                auto obj = state.pop();
                auto offset = state.readShort();
                if (!obj->truth())state.adjust(offset);
                break;
            }
            case Opcode::POP_JUMP_IF_LT: {
                auto b = cast<ObjNumber *>(state.pop());
                auto a = cast<ObjNumber *>(state.pop());
                auto offset = state.readShort();
                if ((*a < *b)->truth())state.adjust(offset);
                break;
            }
            case Opcode::POP_JUMP_IF_LE: {
                auto b = cast<ObjNumber *>(state.pop());
                auto a = cast<ObjNumber *>(state.pop());
                auto offset = state.readShort();
                if ((*a <= *b)->truth())state.adjust(offset);
                break;
            }
            case Opcode::POP_JUMP_IF_EQ: {
                auto b = cast<ObjNumber *>(state.pop());
                auto a = cast<ObjNumber *>(state.pop());
                auto offset = state.readShort();
                if ((*a == *b)->truth())state.adjust(offset);
                break;
            }
            case Opcode::POP_JUMP_IF_NE: {
                auto b = cast<ObjNumber *>(state.pop());
                auto a = cast<ObjNumber *>(state.pop());
                auto offset = state.readShort();
                if ((*a != *b)->truth())state.adjust(offset);
                break;
            }
            case Opcode::POP_JUMP_IF_GE: {
                auto b = cast<ObjNumber *>(state.pop());
                auto a = cast<ObjNumber *>(state.pop());
                auto offset = state.readShort();
                if ((*a >= *b)->truth())state.adjust(offset);
                break;
            }
            case Opcode::POP_JUMP_IF_GT: {
                auto b = cast<ObjNumber *>(state.pop());
                auto a = cast<ObjNumber *>(state.pop());
                auto offset = state.readShort();
                if ((*a > *b)->truth())state.adjust(offset);
                break;
            }
            case Opcode::NOT:
                state.push(!*cast<ObjBool *>(state.pop()));
                break;
            case Opcode::INVERT:
                state.push(~*cast<ObjInt *>(state.pop()));
                break;
            case Opcode::NEGATE:
                state.push(-*cast<ObjInt *>(state.pop()));
                break;
            case Opcode::GET_TYPE:
                state.push((Obj *) state.pop()->getType());
                break;
            case Opcode::SAFE_CAST: {
                auto type = cast<Type *>(state.pop());
                auto obj = cast<Object *>(state.pop());
                if (checkCast(obj->getType(), type)) {
                    obj->setType(type);
                    state.push(obj);
                } else
                    state.push(new ObjNull);
                break;
            }
            case Opcode::CHECKED_CAST: {
                auto type = cast<Type *>(state.pop());
                auto obj = cast<Object *>(state.pop());
                if (checkCast(obj->getType(), type)) {
                    obj->setType(type);
                    state.push(obj);
                } else
                    runtimeError(format("object of type '%s' cannot be cast to object of type '%s'",
                                        obj->getType()->getSign().toString().c_str(),
                                        type->getSign().toString().c_str()));
                break;
            }
            case Opcode::POWER: {
                auto b = static_cast<ObjNumber>(*cast<ObjNumberConvertible *>(state.pop()));
                auto a = static_cast<ObjNumber>(*cast<ObjNumberConvertible *>(state.pop()));
                state.push(a.power(b));
                break;
            }
            case Opcode::MULTIPLY: {
                auto b = static_cast<ObjNumber>(*cast<ObjNumberConvertible *>(state.pop()));
                auto a = static_cast<ObjNumber>(*cast<ObjNumberConvertible *>(state.pop()));
                state.push(a * b);
                break;
            }
            case Opcode::DIVIDE: {
                auto b = static_cast<ObjNumber>(*cast<ObjNumberConvertible *>(state.pop()));
                auto a = static_cast<ObjNumber>(*cast<ObjNumberConvertible *>(state.pop()));
                state.push(a / b);
                break;
            }
            case Opcode::REMAINDER: {
                auto b = cast<ObjInt *>(state.pop());
                auto a = cast<ObjInt *>(state.pop());
                state.push(*a % *b);
                break;
            }
            case Opcode::ADD: {
                auto b = static_cast<ObjNumber>(*cast<ObjNumberConvertible *>(state.pop()));
                auto a = static_cast<ObjNumber>(*cast<ObjNumberConvertible *>(state.pop()));
                state.push(a + b);
                break;
            }
            case Opcode::SUBTRACT: {
                auto b = static_cast<ObjNumber>(*cast<ObjNumberConvertible *>(state.pop()));
                auto a = static_cast<ObjNumber>(*cast<ObjNumberConvertible *>(state.pop()));
                state.push(a - b);
                break;
            }
            case Opcode::LSHIFT:
                break;
            case Opcode::RSHIFT:
                break;
            case Opcode::URSHIFT:
                break;
            case Opcode::AND:
                break;
            case Opcode::OR:
                break;
            case Opcode::XOR:
                break;
            case Opcode::LT:
                break;
            case Opcode::LE:
                break;
            case Opcode::EQ:
                break;
            case Opcode::NE:
                break;
            case Opcode::GE:
                break;
            case Opcode::GT:
                break;
            case Opcode::IS:
                break;
            case Opcode::IS_NULL:
                break;
            case Opcode::IS_NON_NULL:
                break;
            case Opcode::MONITOR_ENTER:
                break;
            case Opcode::MONITOR_EXIT:
                break;
            case Opcode::LOAD_CLOSURE:
                break;
            case Opcode::LOAD_CLOSURE_FAST:
                break;
            case Opcode::LOAD_REIFIED:
                break;
            case Opcode::LOAD_REIFIED_FAST:
                break;
            case Opcode::THROW:
                break;
            case Opcode::RETURN:
                break;
            case Opcode::RETURN_VOID:
                break;
            case Opcode::PRINTLN:
                break;
            case Opcode::NUM_OPCODES:
                break;
        }
    }
}

bool VM::checkCast(const Type *type1, const Type *type2) {
    return false;
}

void VM::call(Thread *thread, ObjMethod *method, Obj **args) {

}
