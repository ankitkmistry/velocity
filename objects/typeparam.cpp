#include "typeparam.hpp"

Type::Kind TypeParam::getKind() const {
    checkPlaceholder();
    return placeholder->getKind();
}

const vector<TypeParam *> &TypeParam::getTypeParams() const {
    checkPlaceholder();
    return placeholder->getTypeParams();
}

const Table<Type *> &TypeParam::getSupers() const {
    checkPlaceholder();
    return placeholder->getSupers();
}

const Table<Obj *> &TypeParam::getMembers() const {
    checkPlaceholder();
    return placeholder->getMembers();
}

vector<TypeParam *> &TypeParam::getTypeParams() {
    checkPlaceholder();
    return placeholder->getTypeParams();
}

Table<Type *> &TypeParam::getSupers() {
    checkPlaceholder();
    return placeholder->getSupers();
}

Table<Obj *> &TypeParam::getMembers() {
    checkPlaceholder();
    return placeholder->getMembers();
}

ObjModule *TypeParam::getModule() const {
    checkPlaceholder();
    return placeholder->getModule();
}

const Table<string> &TypeParam::getMeta() const {
    checkPlaceholder();
    return placeholder->getMeta();
}

const Sign &TypeParam::getSign() const {
    checkPlaceholder();
    return placeholder->getSign();
}

Type *TypeParam::getType() const {
    checkPlaceholder();
    return placeholder->getType();
}

Obj *TypeParam::copy() const {
    auto newTypeParam = Obj::alloc<TypeParam>(info.manager, sign, module, meta);
    newTypeParam->reify(placeholder);
    return newTypeParam;
}

void TypeParam::checkPlaceholder() const {
    if (placeholder == null)throw IllegalTypeParamAccessError(sign.toString());
}
