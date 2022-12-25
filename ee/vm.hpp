#ifndef VELOCITY_VM_HPP
#define VELOCITY_VM_HPP


#include "../oop/obj.hpp"

class VM {
private:
    Table<Obj *> globals;
public:
     Table<Obj *> &getGlobals() const { return globals; }
};


#endif //VELOCITY_VM_HPP
