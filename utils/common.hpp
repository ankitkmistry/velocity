#ifndef SOURCE_UTILS_COMMON_HPP_
#define SOURCE_UTILS_COMMON_HPP_

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <any>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <sstream>
#include "constants.hpp"

// TODO: For debug only
#include <iostream>

#define null (nullptr)

namespace fs = std::filesystem;

using std::string,
        std::vector,
        std::map,
        std::function,
        std::any,
        std::cout, std::cin;

using intptr = std::intptr_t;

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

template<class T>
using Table = map<string, T>;

/*void *operator new(size_t size);

void operator delete(void *pVoid);*/

#endif /* SOURCE_UTILS_COMMON_HPP_ */
