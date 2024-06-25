#ifndef UTILS_UTILS_HPP_
#define UTILS_UTILS_HPP_

#include "common.hpp"
#include "exceptions.hpp"

/**
 * Casts a value of type From to a value of type To.
 * @throws CastError if casting fails
 * @tparam To type of the value to be casted
 * @tparam From type of the casted value
 * @param val the value to be casted
 * @return the casted value
 */
template<class To, class From>
To cast(From val) {
    auto castVal = dynamic_cast<To>(val);
    if (castVal == null)
        throw CastError(typeid(From).name(), typeid(To).name());
    return castVal;
}

/**
 * Checks if the type of a value is a superclass of type V.
 * @tparam T compile time type of the value
 * @tparam V type for checking
 * @param obj the value to be checked
 * @return true if the type of a value is a superclass of type V, false otherwise
 */
template<class T, class V>
bool is(V obj) {
    return dynamic_cast<T>(obj) != null;
}

/**
 * Converts a vector<T> to a comma separated list.
 * Assumes that values have a toString() method that gives string representation of the value.
 * @tparam T type of the vectors
 * @param data
 * @return the comma separated list as a string
 */
template<class T>
string listToString(vector<T> data) {
    string str;
    const int length = data.size();
    for (uint16 i = 0; i < length; ++i)
        str += data[i].toString() + (i < length - 1 ? ", " : "");
    return str;
}

/**
 * Converts a vector<T*> to a comma separated list.
 * Assumes that values have a toString() method that gives string representation of the value.
 * @tparam T type of the vectors
 * @param data
 * @return the comma separated list as a string
 */
template<class T>
string listToString(vector<T *> data) {
    string str;
    const int length = data.size();
    for (uint16 i = 0; i < length; ++i)
        str += data[i]->toString() + (i < length - 1 ? ", " : "");
    return str;
}

/**
 * Pads a string to the left with blank spaces.
 * @param str the string to be padded
 * @param length the number of spaces
 * @return the padded string
 */
string padLeft(const string &str, size_t length);

/**
 * Pads a string to the right with blank spaces.
 * @param str the string to be padded
 * @param length the number of spaces
 * @return the padded string
 */
string padRight(const string &str, size_t length);

/**
 * Finds a the first occurrence of a character in a string in the range [start, end).
 * @param text the string to be searched
 * @param c the character to find
 * @param start starting index of the string
 * @param end ending index of the string
 * @return the index of the first occurrence if found, else returns text.length()
 */
int find(string text, char c, int start, int end);

/**
 * Finds a the first occurrence of a character in a string in the range [0, text.length()).
 * @param text the string to be searched
 * @param c the character to find
 * @return the index of the first occurrence if found, else returns text.length()
 */
int find(string text, char c);

bool isNumber(const std::string &s);

int32 longToInt(int64 num);

string getAbsolutePath(string path);

string getFilenameFromPath(string path);

template<class T>
class Table final : public map<string, T> {

};

template<class ResultType, class CompareType>
ResultType match(CompareType value,
                 map<CompareType, function<ResultType()>> matchCases) {
    try {
        return static_cast<ResultType>(matchCases.at(value)());
    } catch (std::out_of_range &) {
        throw Unreachable();
    }
}

template<class ResultType, class CompareType>
ResultType match(CompareType value,
                 map<CompareType, function<ResultType()>> matchCases,
                 function<ResultType()> defaultCase) {
    try {
        return dynamic_cast<ResultType>(matchCases.at(value)());
    } catch (std::out_of_range &) {
        return defaultCase();
    }
}

template<class T>
class Iterable {
public:
    virtual void foreach(function<void(T)> func) const = 0;
};

#endif /* UTILS_UTILS_HPP_ */
