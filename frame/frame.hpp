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
    vector<ObjMethod *> lambdas;
    vector<MatchTable> matches;
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

    /**
     * Pushes onto the stack
     * @param val the value to be pushed
     */
    void push(Obj *val);

    /**
     * Pops the stack
     * @return the popped value
     */
    Obj *pop();

    /**
     * @return The value of the last item of the stack
     */
    Obj *peek();

    /**
     * @return The constant pool
     */
    const vector<Obj *> &getConstPool() const { return constPool; }

    /**
     * @return The arguments table
     */
    ArgsTable &getArgs() const { return const_cast<ArgsTable &>(args); }

    /**
     * @return The locals table
     */
    LocalsTable &getLocals() const { return const_cast<LocalsTable &>(locals); }

    /**
     * @return The exceptions table
     */
    ExceptionTable &getExceptions() const { return const_cast<ExceptionTable &>(exceptions); }

    /**
     * @return The line number table
     */
    LineNumberTable &getLines() const { return const_cast<LineNumberTable &>(lines); }

    /**
     * @return The array of lambda functions
     */
    const vector<ObjMethod *> &getLambdas() const { return lambdas; }

    /**
     * @return The array of match statements
     */
    const vector<MatchTable> &getMatches() const { return matches; }

    /**
     * @return The method associated with the this frame
     */
    ObjMethod *getMethod() const { return method; }

    /**
     * Sets the ip of this frame to ip
     * @param newIp the new ip value
     */
    void setIp(uint8 *newIp) { ip = newIp; }

    /**
     * Sets the method associated with this frame
     * @param met the method value
     */
    void setMethod(ObjMethod *met) { method = met; }

    /**
     * @return The number of items on the stack
     */
    uint32 getStackCount();

    /**
     * @return The size of the bytecode
     */
    uint32 getCodeCount() const;
};


#endif //VELOCITY_FRAME_HPP
