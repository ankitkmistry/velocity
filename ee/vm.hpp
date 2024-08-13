#ifndef VELOCITY_VM_HPP
#define VELOCITY_VM_HPP

#include "../utils/common.hpp"
#include "thread.hpp"
#include "../objects/obj.hpp"
#include "../objects/inbuilt_types.hpp"
#include "../loader/loader.hpp"
#include "../memory/memory.hpp"
#include "settings.hpp"

class VM {

private:
    /// The globals
    Table<Obj *> globals;
    /// The threads
    std::set<Thread *> threads;
    /// The loader
    Loader loader{this};
    /// The memory manager
    MemoryManager *manager;
    /// The actions to be performed when the vm terminates
    vector<function<void()>> onExitList;
    /// The vm settings
    Settings settings;
    /// The output stream
    std::stringstream out;

public:
    explicit VM(MemoryManager *manager, Settings settings = {});

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

    /**
     * The vm execution loop
     * @param thread the execution thread
     */
    Obj *run(Thread *thread);

    ThrowSignal runtimeError(const string &str);

    /**
     * @param sign the signature of the global
     * @return The value of the global corresponding
     * to the signature <i>param</i>, raises GlobalError if the global cannot be found
     */
    Obj *getGlobal(const string &sign) const;

    /**
     * Set the value of the global corresponding to the signature <i>param</i>.
     * Creates a new global and sets the value to <i>val</i> if there is no
     * existing global with signature <i>param</i>.
     * @param sign the signature of the global
     * @param val the value
     */
    void setGlobal(const string &sign, Obj *val);

    std::set<Thread *> &getThreads() { return threads; }

    const std::set<Thread *> &getThreads() const { return threads; }

    /**
     * @return the globals table
     */
    Table<Obj *> getGlobals() const { return globals; }

    /**
     * @return the vm settings
     */
    Settings &getSettings() { return settings; }

    /**
     * @return the vm settings
     */
    const Settings &getSettings() const { return settings; }

    /**
     * @return the memory manager
     */
    MemoryManager *getMemoryManager() { return manager; }

    /**
     * @return the memory manager
     */
    const MemoryManager *getMemoryManager() const { return manager; }

    /**
     * @return whatever written to the output
     */
    string getOutput() const { return out.str(); }

    /**
     * @return the current vm respective to the current thread
     */
    static VM *current();

private:

    /**
     * Checks the casting compatibility between two types
     * @param type1
     * @param type2
     * @return true if casting can be done, false otherwise
     */
    static bool checkCast(const Type *type1, const Type *type2);

    /**
     * Converts a C++ vector to ObjArray
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
