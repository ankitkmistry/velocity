
// Generated from H:/Programming (Ankit)/Projects/spade/1.0/velocity/assembler\SpadeAssembly.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "SpadeAssemblyParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by SpadeAssemblyParser.
 */
class  SpadeAssemblyListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterAssembly(SpadeAssemblyParser::AssemblyContext *ctx) = 0;
  virtual void exitAssembly(SpadeAssemblyParser::AssemblyContext *ctx) = 0;

  virtual void enterMetadata(SpadeAssemblyParser::MetadataContext *ctx) = 0;
  virtual void exitMetadata(SpadeAssemblyParser::MetadataContext *ctx) = 0;

  virtual void enterGlobals(SpadeAssemblyParser::GlobalsContext *ctx) = 0;
  virtual void exitGlobals(SpadeAssemblyParser::GlobalsContext *ctx) = 0;

  virtual void enterGlobal(SpadeAssemblyParser::GlobalContext *ctx) = 0;
  virtual void exitGlobal(SpadeAssemblyParser::GlobalContext *ctx) = 0;

  virtual void enterMethod(SpadeAssemblyParser::MethodContext *ctx) = 0;
  virtual void exitMethod(SpadeAssemblyParser::MethodContext *ctx) = 0;

  virtual void enterArgs(SpadeAssemblyParser::ArgsContext *ctx) = 0;
  virtual void exitArgs(SpadeAssemblyParser::ArgsContext *ctx) = 0;

  virtual void enterArg(SpadeAssemblyParser::ArgContext *ctx) = 0;
  virtual void exitArg(SpadeAssemblyParser::ArgContext *ctx) = 0;

  virtual void enterLocs(SpadeAssemblyParser::LocsContext *ctx) = 0;
  virtual void exitLocs(SpadeAssemblyParser::LocsContext *ctx) = 0;

  virtual void enterLocal(SpadeAssemblyParser::LocalContext *ctx) = 0;
  virtual void exitLocal(SpadeAssemblyParser::LocalContext *ctx) = 0;

  virtual void enterCode(SpadeAssemblyParser::CodeContext *ctx) = 0;
  virtual void exitCode(SpadeAssemblyParser::CodeContext *ctx) = 0;

  virtual void enterLine(SpadeAssemblyParser::LineContext *ctx) = 0;
  virtual void exitLine(SpadeAssemblyParser::LineContext *ctx) = 0;

  virtual void enterExceptionTable(SpadeAssemblyParser::ExceptionTableContext *ctx) = 0;
  virtual void exitExceptionTable(SpadeAssemblyParser::ExceptionTableContext *ctx) = 0;

  virtual void enterExceptionItem(SpadeAssemblyParser::ExceptionItemContext *ctx) = 0;
  virtual void exitExceptionItem(SpadeAssemblyParser::ExceptionItemContext *ctx) = 0;

  virtual void enterClass(SpadeAssemblyParser::ClassContext *ctx) = 0;
  virtual void exitClass(SpadeAssemblyParser::ClassContext *ctx) = 0;

  virtual void enterAccessor(SpadeAssemblyParser::AccessorContext *ctx) = 0;
  virtual void exitAccessor(SpadeAssemblyParser::AccessorContext *ctx) = 0;

  virtual void enterFields(SpadeAssemblyParser::FieldsContext *ctx) = 0;
  virtual void exitFields(SpadeAssemblyParser::FieldsContext *ctx) = 0;

  virtual void enterField(SpadeAssemblyParser::FieldContext *ctx) = 0;
  virtual void exitField(SpadeAssemblyParser::FieldContext *ctx) = 0;

  virtual void enterValue(SpadeAssemblyParser::ValueContext *ctx) = 0;
  virtual void exitValue(SpadeAssemblyParser::ValueContext *ctx) = 0;

  virtual void enterArray(SpadeAssemblyParser::ArrayContext *ctx) = 0;
  virtual void exitArray(SpadeAssemblyParser::ArrayContext *ctx) = 0;

  virtual void enterFloat(SpadeAssemblyParser::FloatContext *ctx) = 0;
  virtual void exitFloat(SpadeAssemblyParser::FloatContext *ctx) = 0;


};

