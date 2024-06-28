#include "module.hpp"

string ObjModule::getAbsolutePath() {
    if (!path.is_absolute()) path = std::filesystem::current_path() / path;
    return path.string();
}

string ObjModule::getModuleName() {
    return path.filename().string();
}

ObjModule::ObjModule(const fs::path &path, const ElpInfo &elp, const vector<Obj *> &constantPool,
                     const Table<string> &meta)
        : Object(constantPool[elp.thisModule]->toString(), null, {}, null, meta), path(path), elp(elp),
          constantPool(constantPool), id((intptr) &elp) {
    // Get the imports
    auto imports = cast<ObjArray *>(constantPool[elp.imports]);
    // Get the import paths to dependencies vector
    imports->foreach([&](auto obj) {
        dependencies.push_back(obj->toString());
    });
}
