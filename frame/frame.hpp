#ifndef VELOCITY_FRAME_HPP
#define VELOCITY_FRAME_HPP

#include "../utils/common.hpp"
#include "../oop/obj.hpp"
#include "table.hpp"

class ObjMethod;

class Frame {
    friend class VMState;

private:
    vector<Obj *> constPool;
    uint32 codeCount;
public:
    uint8 *code;
    uint8 *ip;
    Obj **stack;
    Obj **sp;
private:
    ArgsTable args;
    LocalsTable locals;
    ExceptionTable exceptions;
    LineNumberTable lines;
    ObjMethod *method;

    Frame()
            : constPool(), codeCount(0), code(null), ip(null),
              stack(null), sp(null),
              args(), locals(0), exceptions(),
              lines(0),
              method(null) {}

public:
    Frame(vector<Obj *> &constPool,
          uint32 codeCount,
          uint8 *code,
          uint32 maxStack,
          ArgsTable &args,
          LocalsTable &locals,
          ExceptionTable &exceptions,
          LineNumberTable &lines,
          ObjMethod *method)
            : constPool(constPool),
              codeCount(codeCount), code(code), ip(null),
              stack(new Obj *[maxStack]), sp(null),
              args(args), locals(locals), exceptions(exceptions),
              lines(lines),
              method(method) {
        ip = code;
        sp = stack;
    }

    Frame(const Frame &frame) = default;

    Frame &operator=(const Frame &frame) = default;

    void push(Obj *val);

    Obj *pop();

    Obj *peek();

    const vector<Obj *> &getConstPool() const { return constPool; }

    ArgsTable &getArgs() const { return const_cast<ArgsTable &>(args); }

    LocalsTable &getLocals() const { return const_cast<LocalsTable &>(locals); }

    ExceptionTable &getExceptions() const { return const_cast<ExceptionTable &>(exceptions); }

    LineNumberTable &getLines() const { return const_cast<LineNumberTable &>(lines); }

    ObjMethod *getMethod() const { return method; }

    void setIp(uint8 *ip_) { ip = ip_; }

    void setMethod(ObjMethod *met) { method = met; }

    uint32 getStackCount();

    uint32 getCodeCount() const;
};


#endif //VELOCITY_FRAME_HPP
