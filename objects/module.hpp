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
    /// Path of the module
    fs::path path;
    /// The constant pool of the module
    vector<Obj *> constantPool;
    /// The dependencies of the module
    vector<string> dependencies;
    /// The information in the module
    const ElpInfo elp;

    ObjModule(const Sign sign, const Table<string> meta, State state,
              const fs::path path, const vector<Obj *> constantPool, const vector<string> dependencies,
              ElpInfo elp)
            : Object(sign, null, null, meta),
              state(state), path(path),
              constantPool(constantPool),
              dependencies(dependencies), elp(elp) {}

public:
    ObjModule(const fs::path &path, ElpInfo &elp, const Table<string> &meta);

    string getAbsolutePath();

    string getModuleName() const;

    State getState() const { return state; }

    void setState(State state_) { state = state_; }

    const fs::path &getPath() const { return path; }

    ElpInfo getElp() const { return elp; }

    const vector<Obj *> &getConstantPool() const { return constantPool; }

    void setConstantPool(const vector<Obj *> &constantPool_);

    const vector<string> &getDependencies() const { return dependencies; }

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;
};


#endif //VELOCITY_MODULE_HPP
