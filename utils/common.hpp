#ifndef SOURCE_UTILS_COMMON_HPP_
#define SOURCE_UTILS_COMMON_HPP_

#include <cstddef>
#include <cstdint>
#include <any>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <set>
#include <tuple>
#include <stdexcept>
#include <algorithm>
#include <cstdio>
#include <functional>
#include <sstream>
#include "constants.hpp"

// TODO: For debug only
#include <iostream>

#define null (nullptr)

using std::string,
        std::vector,
        std::map,
        std::function,
        std::any,
        std::runtime_error,
        std::cout, std::cin;

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

#endif /* SOURCE_UTILS_COMMON_HPP_ */
