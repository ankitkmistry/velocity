#ifndef VELOCITY_MODULE_HPP
#define VELOCITY_MODULE_HPP

#include <elpops/elpdef.hpp>
#include "object.hpp"

class ObjModule : public Object {
public:
    enum class State {
        /// Library has started to load but is resolving its dependencies
        MARKED,
        /// Library has already been loaded
        LOADED,
        /// Library is not yet loaded
        NOT_LOADED
    };
private:
    /// State of the module
    State state = State::NOT_LOADED;
    /// Module id
    intptr id;
    /// Path of the module
    fs::path path;
    /// The information in the module
    const ElpInfo &elp;
    /// The constant pool of the module
    const vector<Obj *> constantPool;
    /// The dependencies of the module
    vector<string> dependencies;
public:
    ObjModule(const fs::path &path, const ElpInfo &elp, const vector<Obj *> &constantPool,
              const Table<string> &meta);

    string getAbsolutePath();

    string getModuleName();

    State getState() const { return state; }

    void setState(State state_) { state = state_; }

    intptr getId() const { return id; }

    const fs::path &getPath() const { return path; }

    const ElpInfo &getElp() const { return elp; }

    const vector<Obj *> &getConstantPool() const { return constantPool; }

    const vector<string> &getDependencies() const { return dependencies; }
};


#endif //VELOCITY_MODULE_HPP
