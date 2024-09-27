#ifndef VELOCITY_METHOD_HPP
#define VELOCITY_METHOD_HPP

#include "callable.hpp"
#include "frame_template.hpp"

namespace spade
{
    class ObjMethod final : public ObjCallable {
      private:
        FrameTemplate *frameTemplate;
        map<vector<Type *>, ObjMethod *> reified;
        Table<NamedRef *> typeParams;

      public:
        ObjMethod(const Sign &sign,
                  Kind kind,
                  FrameTemplate *frame,
                  Type *type,
                  Table<NamedRef *> typeParams,
                  ObjModule *module = null);

        void call(vector<Obj *> args) override;

        void call(Obj **args) override;

        void setSelf(Obj *self) override;

        /**
         * @param args the type args
         * @param count count of type args
         * @return a newly reified type or previously reified type
         */
        ObjMethod *getReified(Obj **args, uint8 count);

        TypeParam *getTypeParam(string name) const;

        Obj *copy() const override;

        string toString() const override;

        const FrameTemplate *getFrameTemplate() const { return frameTemplate; }

        const Table<NamedRef *> &getTypeParams() const { return typeParams; }

        Table<NamedRef *> &getTypeParams() { return typeParams; }

        const map<vector<Type *>, ObjMethod *> &getReifiedMethods() const { return reified; }
        NamedRef *captureTypeParam(string name);
    };
}    // namespace spade

#endif    // VELOCITY_METHOD_HPP
