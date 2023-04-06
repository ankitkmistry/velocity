#include "utils.hpp"

string rpad(const string &str, size_t length) {
    return str.size() < length
           ? std::string(length - str.size(), ' ') + str
           : str;
}

string lpad(const string &str, size_t length) {
    return str.size() < length
           ? str + std::string(length - str.size(), ' ')
           : str;
}

bool isNumber(const string &s) {
    return !s.empty()
           && std::find_if(s.begin(), s.end(),
                           [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
