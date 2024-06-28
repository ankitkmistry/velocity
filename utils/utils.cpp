#include "utils.hpp"
#include "common.hpp"

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

double rawToDouble(uint64 digits) {
    union Converter {
        uint64 digits;
        double number;
    } converter{.digits=digits};
    return converter.number;
}

uint64 doubleToRaw(double number) {
    union Converter {
        uint64 digits;
        double number;
    } converter{.number=number};
    return converter.digits;
}

int64 unsignedToSigned(uint64 number) {
    union Converter {
        uint64 number1;
        int64 number2;
    } converter{.number1=number};
    return converter.number2;
}

uint64 signedToUnsigned(int64 number) {
    union Converter {
        uint64 number1;
        int64 number2;
    } converter{.number2=number};
    return converter.number1;
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

string getAbsolutePath(string path) {
    fs::path p(path);
    if (!p.is_absolute()) p = fs::current_path() / p;
    return p.string();
}
