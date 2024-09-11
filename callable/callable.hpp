#ifndef VELOCITY_CALLABLE_HPP
#define VELOCITY_CALLABLE_HPP

#include "../utils/common.hpp"
#include "../objects/obj.hpp"
#include "../objects/type.hpp"
#include "../ee/thread.hpp"

class ObjCallable : public Obj {
public:
    enum class Kind {
        FUNCTION,
        METHOD,
        CONSTRUCTOR,
        FOREIGN
    };
protected:
    Kind kind;
public:
    ObjCallable(const Sign &sign, Kind kind, Type *type, ObjModule *module = null)
            : Obj(sign, type, module), kind(kind) {}

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

    /**
     * Calls this method with \p args on \p thread.
     * Invokes the VM, completes the execution of
     * the function and returns the return value.
     * In case the function returns void, \c ObjNull is returned
     * @param thread the thread
     * @param args the method to be called
     * @return the return value of the function
     */
    Obj *invoke(Thread *thread, vector<Obj *> args);

    Kind getKind() const { return kind; }

    bool truth() const override { return true; }
};


#endif //VELOCITY_CALLABLE_HPP
