
// Generated from H:/Programming (Ankit)/Projects/spade/1.0/velocity/assembler\SpadeAssembly.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "SpadeAssemblyVisitor.h"


/**
 * This class provides an empty implementation of SpadeAssemblyVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  SpadeAssemblyBaseVisitor : public SpadeAssemblyVisitor {
public:

  virtual std::any visitAssembly(SpadeAssemblyParser::AssemblyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata(SpadeAssemblyParser::MetadataContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobals(SpadeAssemblyParser::GlobalsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobal(SpadeAssemblyParser::GlobalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMethod(SpadeAssemblyParser::MethodContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgs(SpadeAssemblyParser::ArgsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArg(SpadeAssemblyParser::ArgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLocs(SpadeAssemblyParser::LocsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLocal(SpadeAssemblyParser::LocalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCode(SpadeAssemblyParser::CodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLine(SpadeAssemblyParser::LineContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExceptionTable(SpadeAssemblyParser::ExceptionTableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExceptionItem(SpadeAssemblyParser::ExceptionItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClass(SpadeAssemblyParser::ClassContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAccessor(SpadeAssemblyParser::AccessorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFields(SpadeAssemblyParser::FieldsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitField(SpadeAssemblyParser::FieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValue(SpadeAssemblyParser::ValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray(SpadeAssemblyParser::ArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloat(SpadeAssemblyParser::FloatContext *ctx) override {
    return visitChildren(ctx);
  }


};

