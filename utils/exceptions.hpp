#ifndef SOURCE_UTILS_EXCEPTIONS_HPP_
#define SOURCE_UTILS_EXCEPTIONS_HPP_


#include "common.hpp"
#include "format.hpp"

class FatalError : public std::runtime_error {
public:
    explicit FatalError(const string &message)
            : std::runtime_error(message) {}
};

class CorruptFileError : public FatalError {
private:
    string path;

public:
    explicit CorruptFileError(const string &path)
            : FatalError(format("'%s' is corrupted", path.c_str())), path(path) {}

    string getPath() const { return path; }
};

class CastError : public FatalError {
private:
    const string from, to;

public:
    CastError(const string &from, const string &to)
            : FatalError(format("cannot cast type '%s' to type '%s'", from.c_str(), to.c_str())),
              from(from), to(to) {}

    const string &getFrom() const { return from; }

    const string &getTo() const { return to; }
};

class IndexError : public FatalError {
public:
    explicit IndexError(size_t index)
            : FatalError(format("index out of bounds: %d", index)) {}
};

class FileNotFoundError : public FatalError {
    string path;
public:
    explicit FileNotFoundError(const string &path)
            : FatalError(format("file not found: '%s'", path.c_str())), path(path) {}

    const string &getPath() const { return path; }
};

class ReferenceNotFoundError : public FatalError {
public:
    explicit ReferenceNotFoundError(const string &sign)
            : FatalError(format("reference not found: '%s'", sign.c_str())) {}
};

class Unreachable : public FatalError {
public:
    explicit Unreachable() : FatalError("unreachable code reached") {}
};

class EntryPointNotFoundError : public FatalError {
public:
    explicit EntryPointNotFoundError(const string &sign)
            : FatalError(format("cannot find entry point in '%s'", sign.c_str())) {}
};


#endif /* SOURCE_UTILS_EXCEPTIONS_HPP_ */
