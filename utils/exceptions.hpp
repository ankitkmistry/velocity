#ifndef SOURCE_UTILS_EXCEPTIONS_HPP_
#define SOURCE_UTILS_EXCEPTIONS_HPP_


#include "common.hpp"
#include "format.hpp"

class FatalError : public std::runtime_error {
public:
    explicit FatalError(const string &message)
            : std::runtime_error(message) {}
};

class RuntimeError : public std::runtime_error {
public:
    explicit RuntimeError(const string &arg) : std::runtime_error(arg) {}
};

class Obj;

class ThrowSignal : public RuntimeError {
private:
    Obj *value;
public:
    explicit ThrowSignal(Obj *value) : RuntimeError("value is thrown in the vm"), value(value) {}

    Obj *getValue() const { return value; }
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

    explicit IndexError(string index_of, size_t index)
            : FatalError(format("index out of bounds: %d (%s)", index, index_of.c_str())) {}
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

class MemoryError : public FatalError {
public:
    explicit MemoryError(size_t size)
            : FatalError(format("failed to allocate memory: %d bytes", size)) {}
};

class Unreachable : public FatalError {
public:
    Unreachable() : FatalError("unreachable code reached") {}
};

class EntryPointNotFoundError : public FatalError {
public:
    explicit EntryPointNotFoundError(const string &sign)
            : FatalError(format("cannot find entry point in '%s'", sign.c_str())) {}
};

class IllegalTypeParamAccessError : public FatalError {
public:
    explicit IllegalTypeParamAccessError(const string &sign)
            : FatalError(format("tried to access empty type parameter: '%s'", sign.c_str())) {}
};

class GlobalError : public FatalError {
public:
    explicit GlobalError(const string &sign)
            : FatalError(format("cannot find global: '%s'", sign.c_str())) {}
};

class NativeLibraryError : public FatalError {
public:
    NativeLibraryError(string library, string msg)
            : FatalError(format("in '%s': %s", library.c_str(), msg.c_str())) {}

    NativeLibraryError(string library, string function, string msg)
            : FatalError(format("function %s in '%s': %s", function.c_str(), library.c_str(), msg.c_str())) {}
};

class StackOverflowError : public FatalError {
public:
    explicit StackOverflowError()
            : FatalError("bad state: stack overflow") {}
};

class ArgumentError : public FatalError {
public:
    ArgumentError(string sign, string msg)
            : FatalError(format("%s: %s", sign.c_str(), msg.c_str())) {}
};

class SignatureError : public FatalError {
public:
    SignatureError(string sign, string msg)
            : FatalError(format("invalid signature: %s: '%s'", msg.c_str(), sign.c_str())) {}

    SignatureError(string sign)
            : FatalError(format("invalid signature: '%s'", sign.c_str())) {}
};


#endif /* SOURCE_UTILS_EXCEPTIONS_HPP_ */
