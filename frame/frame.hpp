#ifndef VELOCITY_FRAME_HPP
#define VELOCITY_FRAME_HPP

#include "../utils/common.hpp"
#include "../objects/obj.hpp"
#include "table.hpp"

class ObjMethod;

class Frame {
    friend class VMState;

private:
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
            : codeCount(0), code(null), ip(null),
              stack(null), sp(null),
              args(), locals(0), exceptions(),
              lines(0),
              method(null) {}

public:
    Frame(uint32 codeCount,
          uint8 *code,
          uint32 maxStack,
          ArgsTable &args,
          LocalsTable &locals,
          ExceptionTable &exceptions,
          LineNumberTable &lines,
          ObjMethod *method)
            : codeCount(codeCount), code(code), ip(null),
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
    const vector<Obj *> &getConstPool() const;

    /**
     * @return The arguments table
     */
    ArgsTable &getArgs() { return args;}

    /**
     * @return The locals table
     */
    LocalsTable &getLocals() { return locals; }

    /**
     * @return The exceptions table
     */
    ExceptionTable &getExceptions() { return exceptions; }

    /**
     * @return The arguments table
     */
    const ArgsTable &getArgs() const { return args;}

    /**
     * @return The locals table
     */
    const LocalsTable &getLocals() const { return locals; }

    /**
     * @return The exceptions table
     */
    const ExceptionTable &getExceptions() const { return exceptions; }

    /**
     * @return The line number table
     */
    const LineNumberTable &getLines() const { return lines; }

    /**
     * @return The array of lambda functions
     */
    const vector<ObjMethod *> &getLambdas() const { return lambdas; }

    /**
     * @return The array of check statements
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
