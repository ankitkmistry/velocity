#ifndef UTILS_UTILS_HPP_
#define UTILS_UTILS_HPP_

#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include "common.hpp"
#include "exceptions.hpp"

template<class To, class From>
To *cast(From *val) {
    auto castVal = dynamic_cast<To *>(val);
    if (castVal == null) {
        throw CastError(typeid(From).name(), typeid(To).name());
    }
    return castVal;
}

template<class T, class V>
bool is(V obj) {
    return dynamic_cast<T *>(obj) != null;
}

/*
template<class T>
concept ToStringAble=requires(T t){
    t.toString();
};
*/

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

#endif /* UTILS_UTILS_HPP_ */
