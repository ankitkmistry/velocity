#include "utils.hpp"

string rpad(const string& str, size_t length) {
    return str.size() < length
           ? std::string(length - str.size(), ' ') + str
           : str;
}
