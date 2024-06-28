#include "sign.hpp"
#include "utils.hpp"

/*
 * THIS IS A NON-ROBUST ERROR-IGNORING ALGO FOR PARSING SIGNATURES
 * BUT THIS IS EXTREMELY TIME EFFICIENT
 */
void Sign::set() {
#define advance() (i<signature.length()?signature[i++]:-1)
#define peek() (i<signature.length()?signature[i]:-1)
#define peekPrev() (i-1<signature.length()?signature[i-1]:-1)
#define set(var) do {\
            var = signature.substr(start, i-1-start);\
            start = i;\
        } while (false)
#define setLast(var) do {\
            var = signature.substr(start, i-start);\
            start = i;\
        } while (false)
    int start = 0;
    int i = 0;
    /*if (find(signature, '!', 0, find(signature, '(')) != signature.length()) {
        i = signature.find('!') + 1;
        set(library);
    }*/
    if (find(signature, '.') != signature.length()) {
        i = signature.find('.') + 1;
        set(pkg);
    }
    while (advance() != '(' && peek() != -1);
    if (peek() == -1)
        setLast(name);
    else
        set(name);
    if (peekPrev() == '(') {
        argsPresent = true;
        if (peek() == ')')
            argsCount = 0;
        else {
            argsCount = 1;
            while (true) {
                if (advance() == ',')argsCount++;
                else if (peek() == -1) break;
            }
        }
    }
}

string Sign::toString() const {
//    return format("%ld!%s", (int64) libraryId, signature.c_str());
    return signature;
}
