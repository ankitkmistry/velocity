#ifndef VELOCITY_FRAME_HPP
#define VELOCITY_FRAME_HPP

#include "../utils/common.hpp"
#include "../oop/obj.hpp"
#include "table.hpp"

class ObjMethod;

class Frame {
private:
    vector<Obj *> constPool;
    uint8 *code;
    uint8 *ip;
    Obj **stack, **sp;
    ArgsTable args;
    LocalsTable locals;
    ExceptionTable exceptions;
    LineNumberTable lines;
    ObjMethod *method;
public:
    Frame(vector<Obj *> &constPool,
          uint8 *code,
          Obj **stack,
          ArgsTable &args,
          LocalsTable &locals,
          ExceptionTable &exceptions,
          LineNumberTable &lines,
          ObjMethod *method)
            : constPool(constPool), code(code), ip(ip), stack(stack), sp(stack), args(args),
              locals(locals), exceptions(exceptions), lines(lines), method(method) {}

    Frame(const Frame &frame) = default;

    Frame &operator=(const Frame &frame) = default;

    void push(Obj *val);

    Obj *pop();

    Obj *peek();

    const vector<Obj *> &getConstPool() const { return constPool; }

    uint8 *getCode() const { return const_cast<uint8 *>(code); }

    const uint8 *getIp() const { return ip; }

    Obj **getStack() const { return stack; }

    Obj **getSp() const { return sp; }

    const ArgsTable &getArgs() const { return args; }

    const LocalsTable &getLocals() const { return locals; }

    const ExceptionTable &getExceptions() const { return exceptions; }

    const LineNumberTable &getLines() const { return lines; }

    const ObjMethod *getMethod() const { return method; }

    void setIp(uint8 *__ip) { ip = __ip; }

    void setSp(Obj **__sp) { sp = __sp; }
};


#endif //VELOCITY_FRAME_HPP
