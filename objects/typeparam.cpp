#include "typeparam.hpp"
#include "../utils/exceptions.hpp"

Type::Kind TypeParam::getKind() const {
    checkPlaceholder();
    return placeholder->getKind();
}

vector<TypeParam *> TypeParam::getTypeParams() const {
    checkPlaceholder();
    return placeholder->getTypeParams();
}

Table<Type *> TypeParam::getSupers() const {
    checkPlaceholder();
    return placeholder->getSupers();
}

Table<Obj *> TypeParam::getMembers() const {
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
    auto newTypeParam = new(info.space->getManager()) TypeParam(sign, module, meta);
    newTypeParam->reify(placeholder);
    return newTypeParam;
}

void TypeParam::checkPlaceholder() const {
    if (placeholder == null)throw IllegalTypeParamAccessError(sign.toString());
}
