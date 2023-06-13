#include "opcode.hpp"

struct Info {
    string name;
    uint8 params;
    bool take;
};

static const Info OPCODE_TABLE[] = {
        // Nop
        {"NOP", 0, false},

        // Stack op
        {"CONSTANT", 1, true},
        {"LONG_CONSTANT", 2, true},
        {"POP", 0, false},
        {"DUP", 0, false},

        // Load-store op
        {"LOAD_GLOBAL", 2, true},
        {"STORE_GLOBAL", 1, true},
        {"LOAD_LOCAL", 2, false},
        {"STORE_LOCAL", 2, false},
        {"LOAD_GLOBAL_FAST", 1, true},
        {"STORE_GLOBAL_FAST", 1, true},
        {"LOAD_LOCAL_FAST", 1, false},
        {"STORE_LOCAL_FAST", 1, false},
        {"POP_STORE_GLOBAL", 2, true},
        {"POP_STORE_GLOBAL_FAST", 1, true},
        {"POP_STORE_LOCAL", 2, false},
        {"POP_STORE_LOCAL_FAST", 1, false},
        {"LOAD_ARG", 1, false},
        {"STORE_ARG", 1, false},
        {"POP_STORE_ARG", 1, false},

        {"LOAD_MEMBER", 2, true},
        {"STORE_MEMBER", 2, true},
        {"LOAD_STATIC", 2, true},
        {"STORE_STATIC", 2, true},
        {"LOAD_MEMBER_FAST", 1, true},
        {"STORE_MEMBER_FAST", 1, true},
        {"LOAD_STATIC_FAST", 1, true},
        {"STORE_STATIC_FAST", 1, true},
        {"POP_STORE_MEMBER", 2, true},
        {"POP_STORE_STATIC", 2, true},
        {"POP_STORE_MEMBER_FAST", 1, true},
        {"POP_STORE_STATIC_FAST", 1, true},
        {"LOAD_OBJECT", 2, true},
        {"LOAD_OBJECT_FAST", 1, true},

        // Array. op
        {"UNPACK_ARRAY", 0, false},
        {"BUILD_ARRAY", 2, false},
        {"BUILD_ARRAY_FAST", 1, false},
        {"LOAD_INDEX", 0, false},
        {"STORE_INDEX", 0, false},
        {"POP_STORE_INDEX", 0, false},
        {"LOAD_LENGTH", 0, false},

        // Call op
        {"INVOKE", 1, false},
        {"INVOKE_VIRTUAL", 2, true},
        {"INVOKE_STATIC", 2, true},
        {"INVOKE_LOCAL", 2, false},
        {"INVOKE_GLOBAL", 2, true},
        {"INVOKE_VIRTUAL_FAST", 1, true},
        {"INVOKE_STATIC_FAST", 1, true},
        {"INVOKE_LOCAL_FAST", 1, false},
        {"INVOKE_GLOBAL_FAST", 1, true},
        {"INVOKE_ARG", 1, false},
        {"SUB_CALL", 2, false},
        {"SUB_RETURN", 0, false},

        // Jump op
        {"JUMP_FORWARD", 2, false},
        {"JUMP_BACKWARD", 2, false},
        {"JUMP_IF_TRUE", 2, false},
        {"JUMP_IF_FALSE", 2, false},
        {"POP_JUMP_IF_TRUE", 2, false},
        {"POP_JUMP_IF_FALSE", 2, false},
        {"POP_JUMP_IF_LT", 2, false},
        {"POP_JUMP_IF_LE", 2, false},
        {"POP_JUMP_IF_EQ", 2, false},
        {"POP_JUMP_IF_NE", 2, false},
        {"POP_JUMP_IF_GE", 2, false},
        {"POP_JUMP_IF_GT", 2, false},

        // Primitive op
        {"NOT", 0, false},
        {"INVERT", 0, false},
        {"NEGATE", 0, false},
        {"GET_TYPE", 0, false},
        {"SAFE_CAST", 0, false},
        {"CHECKED_CAST", 0, false},
        {"POWER", 0, false},
        {"MULTIPLY", 0, false},
        {"DIVIDE", 0, false},
        {"REMAINDER", 0, false},
        {"ADD", 0, false},
        {"SUBTRACT", 0, false},
        {"LSHIFT", 0, false},
        {"RSHIFT", 0, false},
        {"URSHIFT", 0, false},
        {"AND", 0, false},
        {"OR", 0, false},
        {"XOR", 0, false},
        {"LT", 0, false},
        {"LE", 0, false},
        {"EQ", 0, false},
        {"NE", 0, false},
        {"GE", 0, false},
        {"GT", 0, false},
        {"IS", 0, false},
        {"IS_NOT", 0, false},
        {"IS_NULL", 0, false},
        {"IS_NON_NULL", 0, false},

        // thread safety
        {"MONITOR_ENTER", 0, false/*TODO: Yet to be changed*/},
        {"MONITOR_EXIT", 0, false/*TODO: Yet to be changed*/},

        // Miscellaneous
        {"LOAD_CLOSURE", 0, false},
        {"LOAD_REIFIED", 0, false},
        {"THROW", 0, false},
        {"RETURN", 0, false},
        {"RETURN_VOID", 0, false},

        // Debug op
        {"PRINTLN", 0, false},
};

string OpcodeInfo::toString(Opcode opcode) {
    return OPCODE_TABLE[static_cast<int>(opcode)].name;
}

uint8 OpcodeInfo::getParams(Opcode opcode) {
    return OPCODE_TABLE[static_cast<int>(opcode)].params;
}

bool OpcodeInfo::takeFromConstPool(Opcode opcode) {
    return OPCODE_TABLE[static_cast<int>(opcode)].take;
}
