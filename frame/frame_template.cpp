#include "frame_template.hpp"

Frame *FrameTemplate::initialize() {
    auto frame = new Frame;
    frame->codeCount = codeCount;
    frame->ip = frame->code = code;
    frame->stack = new Obj *[maxStack];
    frame->sp = frame->stack;
    frame->args = args.copy();
    frame->locals = locals.copy();
    frame->exceptions = exceptions;
    frame->lines = lines;
    frame->lambdas = lambdas;
    frame->matches = matches;
    frame->method = method;
    frame->frameTemplate = this;
    return nullptr;
}

FrameTemplate *FrameTemplate::copy() {
    return new FrameTemplate(codeCount, code, maxStack, args, locals, exceptions, lines, vector<ObjMethod *>(),
                             vector<MatchTable>(), method);
}
