#include "module.hpp"

string ObjModule::getAbsolutePath() {
    if (!path.is_absolute()) path = std::filesystem::current_path() / path;
    return path.string();
}

string ObjModule::getModuleName() const {
    return path.filename().string();
}

ObjModule::ObjModule(Sign sign, const fs::path &path, vector<Obj *> constantPool, vector<string> dependencies,
                     ElpInfo &elp)
        : Obj(sign, null, null), path(path), constantPool(constantPool), elp(elp) {
}

Obj *ObjModule::copy() const {
    return (Obj *) this;
}

bool ObjModule::truth() const {
    return true;
}

string ObjModule::toString() const {
    return format("<module %s>", sign.toString().c_str());
}

ObjModule *ObjModule::current() {
    if (auto thread = Thread::current();thread != null) {
        auto state = thread->getState();
        if (auto frame = state->getFrame();frame > state->getCallStack()) {
            return frame->getMethod()->getModule();
        }
    }
    return null;
}
