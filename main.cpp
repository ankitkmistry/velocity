#include <iostream>
#include "oop/objects.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    auto array = new ObjArray(4);
    array->set(0, new ObjString("hello, "));
    array->set(1, new ObjString("world"));
    cout << array->toString();
	return 0;
}
