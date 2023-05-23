#ifndef VELOCITY_OPCODE_HPP
#define VELOCITY_OPCODE_HPP

#include "../utils/common.hpp"

/**
 * Enum containing all opcodes of the bytecode language
 */
enum class Opcode {
    // Nop
    NOP,

    // Stack op
    CONSTANT,
    LONG_CONSTANT,
    POP,
    DUP,

    // Load-store op
    LOAD_GLOBAL,
    STORE_GLOBAL,
    LOAD_LOCAL,
    STORE_LOCAL,
    LOAD_GLOBAL_FAST,
    STORE_GLOBAL_FAST,
    LOAD_LOCAL_FAST,
    STORE_LOCAL_FAST,
    POP_STORE_GLOBAL,
    POP_STORE_LOCAL,
    POP_STORE_GLOBAL_FAST,
    POP_STORE_LOCAL_FAST,
    LOAD_ARG,
    STORE_ARG,
    POP_STORE_ARG,

    LOAD_MEMBER,
    STORE_MEMBER,
    LOAD_STATIC,
    STORE_STATIC,
    LOAD_MEMBER_FAST,
    STORE_MEMBER_FAST,
    LOAD_STATIC_FAST,
    STORE_STATIC_FAST,
    POP_STORE_MEMBER,
    POP_STORE_STATIC,
    POP_STORE_MEMBER_FAST,
    POP_STORE_STATIC_FAST,
    LOAD_OBJECT,
    LOAD_OBJECT_FAST,

    // Array. op
    UNPACK_ARRAY,
    BUILD_ARRAY,
    BUILD_ARRAY_FAST,
    LOAD_INDEX,
    STORE_INDEX,
    POP_STORE_INDEX,
    LOAD_LENGTH,

    // Call op
    INVOKE,
    INVOKE_VIRTUAL,
    INVOKE_STATIC,
    INVOKE_LOCAL,
    INVOKE_GLOBAL,
    INVOKE_VIRTUAL_FAST,
    INVOKE_STATIC_FAST,
    INVOKE_LOCAL_FAST,
    INVOKE_GLOBAL_FAST,
    INVOKE_ARG,
    SUB_CALL,
    SUB_RETURN,

    // Jump op
    JUMP_FORWARD,
    JUMP_BACKWARD,
    JUMP_IF_TRUE,
    JUMP_IF_FALSE,
    POP_JUMP_IF_TRUE,
    POP_JUMP_IF_FALSE,
    POP_JUMP_IF_LT,
    POP_JUMP_IF_LE,
    POP_JUMP_IF_EQ,
    POP_JUMP_IF_NE,
    POP_JUMP_IF_GE,
    POP_JUMP_IF_GT,

    // Primitive op
    NOT,
    INVERT,
    NEGATE,
    GET_TYPE,
    SAFE_CAST,
    CHECKED_CAST,
    POWER,
    MULTIPLY,
    DIVIDE,
    REMAINDER,
    ADD,
    SUBTRACT,
    LSHIFT,
    RSHIFT,
    URSHIFT,
    AND,
    OR,
    XOR,
    LT,
    LE,
    EQ,
    NE,
    GE,
    GT,
    IS,
    IS_NULL,
    IS_NON_NULL,

    // thread safety
    MONITOR_ENTER,
    MONITOR_EXIT,

    // Miscellaneous
    LOAD_CLOSURE,
    LOAD_CLOSURE_FAST,
    LOAD_REIFIED,
    LOAD_REIFIED_FAST,
    THROW,
    RETURN,
    RETURN_VOID,

    // Debug op
    PRINTLN,
    NUM_OPCODES
};

/**
 * Contains debug info for all opcodes
 */
class OpcodeInfo {
public:
    /**
     * @param opcode
     * @return string representation of the opcode
     */
    static string toString(Opcode opcode);

    /**
     * @param opcode
     * @return number of params needed for the opcode
     */
    static uint8 getParams(Opcode opcode);

    /**
     * @param opcode
     * @return whether the param of the opcode refers to the constant pool
     */
    static bool takeFromConstPool(Opcode opcode);
};

#endif //VELOCITY_OPCODE_HPP
