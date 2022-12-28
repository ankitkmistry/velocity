#ifndef UTILS_UTILS_HPP_
#define UTILS_UTILS_HPP_

#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdio>
#include <functional>
#include <any>
#include "common.hpp"
#include "exceptions.hpp"

template<class To, class From>
To cast(From val) {
    auto castVal = dynamic_cast<To>(val);
    if (castVal == null) {
        throw CastError(typeid(From).name(), typeid(To).name());
    }
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

template<class T>
class Iterator {
private:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

    pointer ptr;
public:
    Iterator() : ptr(null) {}

    Iterator(T *t) : ptr(t) {}

    ~Iterator() = default;

    /*postfix*/
    Iterator operator++(int)/*postfix*/{
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    /*prefix*/
    Iterator &operator++()/*prefix*/
    {
        ptr++;
        return *this;
    }

    reference operator*() const { return *ptr; }

    pointer operator->() const { return ptr; }

    Iterator operator+(difference_type diff) const { return ptr + diff; }

    bool operator==(const Iterator &rhs) const { return ptr == rhs.ptr; }

    bool operator!=(const Iterator &rhs) const { return ptr != rhs.ptr; }
};

template<class T>
class Table final : public map<string, T> {

};

template<class T, class V>
struct MatchCase {
    T __case;
    function <V> __action;
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

#endif /* UTILS_UTILS_HPP_ */
