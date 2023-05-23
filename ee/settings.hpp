#ifndef VELOCITY_SETTINGS_HPP
#define VELOCITY_SETTINGS_HPP

#include "../utils/common.hpp"

struct Settings {
    const string VERSION = "1.0";
    const string LANG_NAME = "spade";
    const string VM_NAME = "velocity";
    const string INFO_STRING = VERSION + " " + LANG_NAME + " " + VM_NAME;
    uint16 MAX_LIFE_IN_EDEN = 10;
    uint16 MAX_MALLOC_REQUESTS = 5;
    /// MAX_EDEN_GC must be > MAX_LIFE_IN_EDEN
    uint16 MAX_EDEN_GC = 20;
};

#endif //VELOCITY_SETTINGS_HPP
