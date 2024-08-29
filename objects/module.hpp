#ifndef VELOCITY_MODULE_HPP
#define VELOCITY_MODULE_HPP

#include <elpops/elpdef.hpp>
#include "method.hpp"

class ObjModule : public Obj {
public:
    enum class State {
        NOT_READ, READ, LOADED, INITIALIZED
    };
private:
    /// State of the module
    State state = State::NOT_READ;
    /// Path of the module
    fs::path path;
    /// The constant pool of the module
    vector<Obj *> constantPool;
    /// The dependencies of the module
    vector<string> dependencies;
    /// The information in the module
    ElpInfo elp;
    /// The module init method
    ObjMethod *init;

    ObjModule(const Sign sign, const Table<string> meta, State state,
              const fs::path path, const vector<Obj *> constantPool, const vector<string> dependencies,
              ElpInfo elp)
            : Obj(sign, null, null, meta),
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

    ObjMethod *getInit() const { return init; }

    void setInit(ObjMethod *init_) { init = init_; }

    Obj *copy() const override;

    bool truth() const override;

    string toString() const override;
};


#endif //VELOCITY_MODULE_HPP
