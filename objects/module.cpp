#include "module.hpp"

string ObjModule::getAbsolutePath() {
    if (!path.is_absolute()) path = std::filesystem::current_path() / path;
    return path.string();
}

string ObjModule::getModuleName() const {
    return path.filename().string();
}

ObjModule::ObjModule(const fs::path &path, ElpInfo &elp, const Table<string> &meta)
        : Object(Sign(""), null, {}, null, meta), path(path), elp(elp) {
}

void ObjModule::setConstantPool(const vector<Obj *> &constantPool_) {
    constantPool = constantPool_;
    // Set the sign
    sign = Sign{constantPool[elp.thisModule]->toString()};
    // Get the imports
    auto imports = cast<ObjArray *>(constantPool[elp.imports]);
    // Get the import paths to dependencies vector
    imports->foreach([&](auto obj) {
        dependencies.push_back(obj->toString());
    });
}

Obj *ObjModule::copy() const {
    return new(info.space->getManager()) ObjModule(sign, members, meta, state, path, constantPool, dependencies, elp);
}

bool ObjModule::truth() const {
    return true;
}

string ObjModule::toString() const {
    return format("<module %s>", sign.toString().c_str());
}
