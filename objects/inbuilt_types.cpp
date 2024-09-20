#include "inbuilt_types.hpp"
#include "cmath"

namespace spade {
    int32 ObjBool::compare(const Obj *rhs) const {
        if (!is<const ObjBool *>(rhs))return 0;
        return (value ? 1 : 0) - (cast<const ObjBool *>(rhs)->value ? 1 : 0);
    }

    int32 ObjChar::compare(const Obj *rhs) const {
        if (!is<const ObjChar *>(rhs))return 0;
        return c - cast<const ObjChar *>(rhs)->c;
    }

    int32 ObjNull::compare(const Obj *rhs) const {
        if (!is<const ObjNull *>(rhs))return -1;
        return 0;
    }

    ObjNull *ObjNull::value() {
        static thread_local ObjNull *nullRef = halloc<ObjNull>(MemoryManager::current());
        return nullRef;
    }

    ObjString::ObjString(uint8 *bytes, uint16 len, ObjModule *module) :
            ComparableObj(Sign("string"), null, module), str() {
        str = string(bytes, bytes + len);
    }

    int32 ObjString::compare(const Obj *rhs) const {
        if (!is<const ObjString *>(rhs))return -1;
        return str.compare(cast<const ObjString *>(rhs)->str);
    }

    Obj *ObjArray::copy() const {
        auto arr = halloc<ObjArray>(info.manager, length);
        for (uint16 i = 0; i < length; ++i)
            arr->set(i, Obj::createCopy(array[i]));
        return arr;
    }

    string ObjArray::toString() const {
        string str;
        for (uint16 i = 0; i < length; ++i)
            str += array[i]->toString() + (i < length - 1 ? ", " : "");
        return "[" + str + "]";
    }

    Obj *ObjArray::get(int64 i) const {
        if (i >= length) throw IndexError("array", i);
        if (array == null)return halloc<ObjNull>(info.manager, module);
        return array[i >= 0 ? i : length + i];
    }

    void ObjArray::set(int64 i, Obj *value) {
        // Initialize the array if it is not initialized yet
        if (array == null) {
            array = new Obj *[length]{halloc<ObjNull>(info.manager)};
        }
        if (i >= length) throw IndexError("array", i);
        array[i >= 0 ? i : length + i] = value;
    }

    void ObjArray::foreach(function<void(Obj *)> func) const {
        for (int i = 0; i < length; ++i) func(array[i]);
    }

    int32 ObjArray::compare(const Obj *rhs) const {
        if (!is<const ObjArray *>(rhs))return -1;
        return toString().compare(cast<const ObjArray *>(rhs)->toString());
    }
}