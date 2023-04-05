#ifndef UTILS_UTILS_HPP_
#define UTILS_UTILS_HPP_

#include "common.hpp"
#include "exceptions.hpp"

template<class To, class From>
To cast(From val) {
    auto castVal = dynamic_cast<To>(val);
    if (castVal == null)
        throw CastError(typeid(From).name(), typeid(To).name());
    return castVal;
}

template<class T, class V>
bool is(V obj) {
    return dynamic_cast<T>(obj) != null;
}

template<class T>
string listToString(vector <T> data) {
    string str;
    const int length = data.size();
    for (uint16 i = 0; i < length; ++i)
        str += data[i].toString() + (i < length - 1 ? ", " : "");
    return str;
}

string rpad(const string& str, size_t length);

template<class T>
class Table final : public map<string, T> {

};

template<class ResultType, class CompareType>
ResultType match(CompareType value,
                 map <CompareType, function<ResultType()>> matchCases) {
    try {
        return static_cast<ResultType>(matchCases.at(value)());
    } catch (std::out_of_range &) {
        throw Unreachable();
    }
}

template<class ResultType, class CompareType>
ResultType match(CompareType value,
                 map <CompareType, function<ResultType()>> matchCases,
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
