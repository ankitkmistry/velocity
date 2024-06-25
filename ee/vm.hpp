#ifndef VELOCITY_VM_HPP
#define VELOCITY_VM_HPP

#include "../utils/common.hpp"
#include "thread.hpp"
#include "../oop/obj.hpp"
#include "../oop/objects.hpp"
#include "../loader/loader.hpp"
#include "../memory/memory.hpp"
#include "settings.hpp"

class VM {
    friend class GarbageCollector;

private:
    /// The globals
    Table<Obj *> globals;
    /// The threads
    std::set<Thread *> threads;
    /// The loader
    Loader loader{this};
    /// The memory manager
    MemoryManager memoryManager{this};
    /// The actions to be performed when the vm terminates
    vector<function<void()>> onExitList;
    /// The vm settings
    Settings settings;
    /// The output stream
    std::stringstream out;

public:
    explicit VM(Settings settings = {}) : settings(std::move(settings)) {}

    /**
     * This function registers the action which will be executed
     * when the virtual machine terminates
     * @param fun the action
     */
    void onExit(const function<void()> &fun);

    /**
     * This function initiates the virtual machine
     * @param filename the path to the bytecode file
     * @param args the command line args array
     * @return the exit code
     */
    int start(const string &filename, const vector<string> &args);

    /**
     * This function initiates the virtual machine
     * @warning This function is only to be used when the vm is properly loaded.
     * The loading operation is done by the loader but
     * this method does not perform the loading procedure.
     * @param entry the function object which is the entry point
     * @param args the array object which has the command line arguments
     * @return the exit code
     */
    int start(ObjMethod *entry, ObjArray *args);

    ThrowSignal runtimeError(const string &str);

    /**
     * @return The value of the global corresponding
     * to the signature <i>sign</i>, ObjNull if the global cannot be found
     * @param sign the signature of the global
     */
    Obj *getGlobal(const string &sign);

    /**
     * Set the value of the global corresponding to the signature <i>sign</i>.
     * Creates a new global and sets the value to <i>val</i> if there is no
     * existing global with signature <i>sign</i>.
     * @param sign the signature of the global
     * @param val the value
     */
    void setGlobal(const string &sign, Obj *val);

    /**
     * @return the vm settings
     */
    Settings &getSettings() { return settings; }

    /**
     * @return the memory manager
     */
    MemoryManager &getMemoryManager() { return memoryManager; }

    /**
     * @return whatever written to the output
     */
    string getOutput() { return out.str(); }

private:
    /**
     * The vm execution loop
     * @param thread the execution thread
     */
    void run(Thread *thread);

    /**
     * @return the globals table
     */
    Table<Obj *> getGlobals() const { return globals; }

    /**
     * Checks the casting compatibility between two types
     * @param type1
     * @param type2
     * @return true if casting can be done, false otherwise
     */
    static bool checkCast(const Type *type1, const Type *type2);

    /**
     * Calls the <i>method</i> with <i>args</i> on <i>thread</i>
     * @param thread the thread
     * @param method the method to be called
     * @param args the args of the method
     */
    static void call(Thread *thread, ObjMethod *method, Obj **args);

    /**
     * Converts a c++ vector to ObjArray
     * @param args the vector
     * @return an array object containing the contents of args
     */
    ObjArray *argsRepr(const vector<string> &args);

    /**
     * This function writes to the output
     * @param str
     */
    void write(const string &str) { out << str; }
};


#endif //VELOCITY_VM_HPP
