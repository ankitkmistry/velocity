#ifndef UTILS_SIGN_HPP_
#define UTILS_SIGN_HPP_

#include "common.hpp"
#include "format.hpp"

class Sign {
private:
    intptr libraryId;
    string pkg;
    string name;
    string signature;
    bool argsPresent = false;
    uint8 argsCount = -1;
public:
    Sign(string signature, intptr libraryId = 0) : signature(signature), libraryId(libraryId) { set(); }

    void set();

    intptr getLibraryId() const { return libraryId; }

    string getName() const { return name; }

    string getPkg() const { return pkg; }

    string getSignature() const { return signature; }

    uint8 getArgsCount() { return argsCount; }

    bool isArgsPresent() const { return argsPresent; }

    string toString() const;
};

#endif /* UTILS_SIGN_HPP_ */
