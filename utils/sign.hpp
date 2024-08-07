#ifndef UTILS_SIGN_HPP_
#define UTILS_SIGN_HPP_

#include "common.hpp"
#include "format.hpp"

class SignElement;

/// Represents a signature
class Sign {
    friend class SignParser;

public:
    /// Describes the kind of the signature
    enum class Kind {
        /// Signature is empty
        EMPTY,
        /// Signature refers to a module
        MODULE,
        /// Signature refers to a class
        CLASS,
        /// Signature refers to a method
        METHOD
    };
private:
    /// The signature elements
    vector<SignElement> elements;

    Sign(vector<SignElement> elements);

public:

    /**
     * Creates a signature object
     * @param text The text of the signature
     */
    explicit Sign(string text);

    ~Sign();

    /**
     * @return true if the signature is empty, false otherwise
     */
    bool empty() const;

    /**
     * @return the name of the signature
     */
    string getName() const;

    /**
     * @return the kind of the signature
     */
    Kind getKind() const;

    /**
     * @return the type params of the signature if exists, otherwise returns an empty array
     */
    vector<string> getTypeParams() const;

    /**
     * @return the params of the signature if exists, otherwise returns an empty array
     */
    vector<Sign> getParams() const;

    /**
     * @return the signature of the parent module
     */
    Sign getParentModule() const;

    /**
     * @return the signature of the parent class if exists, otherwise returns an empty sign
     */
    Sign getParentClass() const;

    /**
     * Appends a module name to this signature if possible
     * @param name the name of the module
     * @return true if it was added, false otherwise
     */
    bool appendModule(string name);

    /**
     * Appends a module name to this signature if possible
     * @param name the name of the class
     * @param typeParams the type params of the class
     * @return true if it was added, false otherwise
     */
    bool appendClass(string name, vector<string> typeParams = {});

    /**
     * Appends a module name to this signature if possible
     * @param name the name of the class
     * @param typeParams the type params of the class
     * @param params the params of the class
     * @return true if it was added, false otherwise
     */
    bool appendMethod(string name, vector<string> typeParams = {}, vector<Sign> params = {});

    /**
     * @return the string representation of the sign
     */
    string toString() const;
};

/// For internal use only
class SignElement {
    friend class Sign;

    friend class SignParser;

    string name;
    Sign::Kind kind;
    vector<string> typeParams;
    vector<Sign> params;

    SignElement(string name, Sign::Kind kind, vector<string> typeParams = {}, vector<Sign> params = {})
            : name(name), kind(kind), params(params), typeParams(typeParams) {}

public:
    ~SignElement() = default;

private:
    const string &getName() const { return name; }

    Sign::Kind getKind() const { return kind; }

    const vector<Sign> &getParams() const { return params; }

    const vector<string> &getTypeParams() const { return typeParams; }

    string toString() const;
};

#endif /* UTILS_SIGN_HPP_ */
