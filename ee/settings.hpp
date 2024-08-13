#ifndef VELOCITY_SETTINGS_HPP
#define VELOCITY_SETTINGS_HPP

#include "../utils/common.hpp"

/**
 * Represents VM settings
 */
struct Settings {
    const string VERSION = "1.0";
    const string LANG_NAME = "spade";
    const string VM_NAME = "velocity";
    const string INFO_STRING = VERSION + " " + LANG_NAME + " " + VM_NAME;

    std::set<string> inbuiltTypes = {
            "array",
            "bool",
            "char",
            "float",
            "int",
            "string",
    };

    string libPath;
    string modPath;

    uint16 MAX_LIFE_IN_EDEN = 10;
    /// MAX_EDEN_GC must be > MAX_LIFE_IN_EDEN
    uint16 MAX_EDEN_GC = 20;
    double HEAP_GROWTH_FACTOR = 1.5;
    size_t EDEN_THRESHOLD = 1 * 1024 * 1024;
};

#endif //VELOCITY_SETTINGS_HPP
