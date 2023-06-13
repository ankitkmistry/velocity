#include "utils.hpp"

string padRight(const string &str, size_t length) {
    return str.size() < length
           ? std::string(length - str.size(), ' ') + str
           : str;
}

string padLeft(const string &str, size_t length) {
    return str.size() < length
           ? str + std::string(length - str.size(), ' ')
           : str;
}

bool isNumber(const string &s) {
    return !s.empty()
           && std::find_if(s.begin(), s.end(),
                           [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int32 longToInt(int64 num) {
    int sign = num >> 63 == 0 ? 1 : -1;
    return static_cast<int32>(sign * (sign * num & 0xffffffff));
}

int find(string text, char c, int start, int end) {
    for (int i = start; i < end; ++i) {
        if (text[i] == c)return i;
    }
    return text.length();
}

int find(string text, char c) {
    return find(text, c, 0, text.length());
}
