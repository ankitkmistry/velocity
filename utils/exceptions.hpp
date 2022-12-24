#ifndef SOURCE_UTILS_EXCEPTIONS_HPP_
#define SOURCE_UTILS_EXCEPTIONS_HPP_

#include <stdexcept>

#include "common.hpp"
#include "format.hpp"

class FatalError : std::runtime_error {
public:
    explicit FatalError(const string &message)
            : std::runtime_error(message) {
    }
};

class CorruptFileError : FatalError {
private:
    string path;

public:
    explicit CorruptFileError(const string &path)
            : FatalError(format("'%s' is corrupted", path.c_str())), path(path) {
    }

    [[nodiscard]] string getPath() const {
        return path;
    }
};

class CastError : FatalError {
private:
    const string from, to;

public:
    CastError(const string& from, const string& to)
            : FatalError(format("cannot cast type '%s' to type '%s'", from.c_str(), to.c_str())),
              from(from), to(to) {
    }
};

class IndexError : FatalError {
public:
    explicit IndexError(size_t index)
            : FatalError(format("Index out of bounds: %d", index)) {}
};

#endif /* SOURCE_UTILS_EXCEPTIONS_HPP_ */
