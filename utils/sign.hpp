#ifndef UTILS_SIGN_HPP_
#define UTILS_SIGN_HPP_

#include "common.hpp"

class Sign {
private:
    string library;
    string pkg;
    string name;
    const string signature;
public:
    Sign(const string& signature) : signature(signature) { set(); }

    void set() {
        // Set the fields of the sign
    }

    const string getLibrary() const { return library; }

    const string getName() const { return name; }

    const string getPkg() const { return pkg; }

    const string getSignature() const { return signature; }

    const string toString() const { return signature; }

    uint8 getArgsCount() {
        // TODO: Implement this
        return 0;
    }
};

#endif /* UTILS_SIGN_HPP_ */
