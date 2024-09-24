#ifndef OOP_OBJECTS_HPP_
#define OOP_OBJECTS_HPP_

#include "../utils/common.hpp"
#include "../objects/obj.hpp"
#include "../memory/manager.hpp"

namespace spade {
    class ObjBool : public ComparableObj {
    private:
        bool value;

    public:
        ObjBool(bool value, ObjModule *module = null)
                : ComparableObj(Sign("bool"), null, module), value(value) {}

        bool truth() const override {
            return value;
        }

        string toString() const override {
            return value ? "true" : "false";
        }

        Obj *copy() const override {
            return (Obj *) this;
        }

        int32 compare(const Obj *rhs) const override;

        ObjBool *operator!() const {
            return halloc<ObjBool>(info.manager, !value, module);
        }
    };

    class ObjChar : public ComparableObj {
    private:
        char c;

    public:
        ObjChar(const char c, ObjModule *module = null)
                : ComparableObj(Sign("char"), null, module), c(c) {}

        bool truth() const override {
            return c != '\0';
        }

        string toString() const override {
            return string({c});
        }

        Obj *copy() const override {
            return (Obj *) this;
        }

        int32 compare(const Obj *rhs) const override;
    };

    class ObjNull : public ComparableObj {
    public:
        ObjNull(ObjModule *module = null)
                : ComparableObj(Sign("null"), null, module) {}

        static ObjNull *value(MemoryManager *manager = null);

        bool truth() const override {
            return false;
        }

        string toString() const override {
            return "null";
        }

        Obj *copy() const override {
            return (Obj *) this;
        }

        int32 compare(const Obj *rhs) const override;
    };

    class ObjString : public ComparableObj {
    private:
        string str;
    public:
        ObjString(string str, ObjModule *module = null)
                : ComparableObj(Sign("string"), null, module), str(str) {}

        ObjString(uint8 *bytes, uint16 len, ObjModule *module = null);

        bool truth() const override {
            return !str.empty();
        }

        string toString() const override {
            return str;
        }

        Obj *copy() const override {
            return (Obj *) this;
        }

        int32 compare(const Obj *rhs) const override;
    };

    class ObjArray final : public ComparableObj {
    private:
        Obj **array;
        uint16 length;
    public:
        explicit ObjArray(uint16 length, ObjModule *module = null)
                : ComparableObj(Sign("array"), null, module), length(length) {}

        void foreach(function<void(Obj *)> func) const;

        Obj *get(int64 i) const;

        void set(int64 i, Obj *value);

        uint16 count() const { return length; }

        bool truth() const override { return length != 0; }

        string toString() const override;

        Obj *copy() const override;

        /// Does lexicographical comparison
        int32 compare(const Obj *rhs) const override;
    };

    class ObjNumber : public ComparableObj {
    public:
        ObjNumber(Sign sign, ObjModule *module = null)
                : ComparableObj(sign, null, module) {}

        virtual Obj *operator-() const = 0;

        virtual Obj *power(const ObjNumber *n) const = 0;

        virtual Obj *operator+(const ObjNumber *n) const = 0;

        virtual Obj *operator-(const ObjNumber *n) const = 0;

        virtual Obj *operator*(const ObjNumber *n) const = 0;

        virtual Obj *operator/(const ObjNumber *n) const = 0;
    };
}
#endif /* OOP_OBJECTS_HPP_ */
