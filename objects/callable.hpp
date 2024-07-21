#ifndef VELOCITY_CALLABLE_HPP
#define VELOCITY_CALLABLE_HPP

#include "../utils/common.hpp"
#include "obj.hpp"
#include "type.hpp"
#include "../ee/thread.hpp"

class ObjCallable : public Obj {
public :
    enum Kind {
        FUNCTION,
        METHOD,
        CONSTRUCTOR,
        FOREIGN
    };
protected:
    Kind kind;
public:
    ObjCallable(const Sign &sign, Kind kind, Type *type, ObjModule *module = null,
                const Table<string> &meta = {}) : Obj(sign, type, module, meta), kind(kind) {}

    /**
     * Calls this method with \p args on \p thread
     * @param thread the thread
     * @param method the method to be called
     * @param args arguments of the method
     */
    virtual void call(Thread *thread, vector<Obj *> args) = 0;

    /**
     * Calls this method with \p args on \p thread
     * @param thread the thread
     * @param method the method to be called
     * @param args pointer to the args on the stack
     */
    virtual void call(Thread *thread, Obj **args) = 0;

    Kind getKind() const { return kind; }

    bool truth() const override { return true; }

    string toString() const override;
};


#endif //VELOCITY_CALLABLE_HPP
