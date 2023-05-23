#ifndef UTILS_SIGN_HPP_
#define UTILS_SIGN_HPP_

#include "common.hpp"

class Sign {
private:
    string library;
    string pkg;
    string name;
    string signature;
    uint8 argsCount;
public:
    Sign(string signature) : signature(signature) { set(); }

    void set() {
        // Todo: Set the fields of the sign
    }

    string getLibrary() const { return library; }

    string getName() const { return name; }

    string getPkg() const { return pkg; }

    string getSignature() const { return signature; }

    string toString() const { return signature; }

    uint8 getArgsCount() { return argsCount; }
};

#endif /* UTILS_SIGN_HPP_ */
