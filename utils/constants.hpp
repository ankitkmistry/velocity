#ifndef VELOCITY_CONSTANTS_HPP
#define VELOCITY_CONSTANTS_HPP

#define FRAMES_MAX 65536

/*
 * MAX_EDEN_GC must be > MAX_LIFE_IN_EDEN
 */

#define MAX_LIFE_IN_EDEN 10 // 10 in gcs
#define MAX_MALLOC_REQUESTS 5
#define MAX_EDEN_GC 20

#define VERSION "1.0"
#define LANG_NAME "spade"
#define VM_NAME "velocity"
#define INFO_STRING LANG_NAME VM_NAME VERSION

#if defined _WIN32
#define OS_WINDOWS
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
#define OS_LINUX
#elif defined (__APPLE__)
#define OS_MAC
#endif

#endif //VELOCITY_CONSTANTS_HPP
