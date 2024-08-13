#include "module.hpp"
#include "inbuilt_types.hpp"

string ObjModule::getAbsolutePath() {
    if (!path.is_absolute()) path = std::filesystem::current_path() / path;
    return path.string();
}

string ObjModule::getModuleName() const {
    return path.filename().string();
}

ObjModule::ObjModule(const fs::path &path, ElpInfo &elp, const Table<string> &meta)
        : Object(Sign(""), null, null, meta), path(path), elp(elp) {
}

void ObjModule::setConstantPool(const vector<Obj *> &constantPool_) {
    constantPool = constantPool_;
    sign = Sign{constantPool[elp.thisModule]->toString()};
    auto imports = cast<ObjArray *>(constantPool[elp.imports]);
    dependencies.clear();
    // Get the import paths to dependencies vector
    imports->foreach([&](auto obj) {
        dependencies.push_back(obj->toString());
    });
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
