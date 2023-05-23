#ifndef VELOCITY_CONSTANTS_HPP
#define VELOCITY_CONSTANTS_HPP

#define FRAMES_MAX 65536

#if defined _WIN32
#define OS_WINDOWS
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
#define OS_LINUX
#elif defined (__APPLE__)
#define OS_MAC
#endif

#endif //VELOCITY_CONSTANTS_HPP
