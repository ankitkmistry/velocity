
// Generated from H:/Programming (Ankit)/Projects/spade/1.0/velocity/assembler\SpadeAssembly.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "SpadeAssemblyListener.h"


/**
 * This class provides an empty implementation of SpadeAssemblyListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  SpadeAssemblyBaseListener : public SpadeAssemblyListener {
public:

  virtual void enterAssembly(SpadeAssemblyParser::AssemblyContext * /*ctx*/) override { }
  virtual void exitAssembly(SpadeAssemblyParser::AssemblyContext * /*ctx*/) override { }

  virtual void enterMetadata(SpadeAssemblyParser::MetadataContext * /*ctx*/) override { }
  virtual void exitMetadata(SpadeAssemblyParser::MetadataContext * /*ctx*/) override { }

  virtual void enterGlobals(SpadeAssemblyParser::GlobalsContext * /*ctx*/) override { }
  virtual void exitGlobals(SpadeAssemblyParser::GlobalsContext * /*ctx*/) override { }

  virtual void enterGlobal(SpadeAssemblyParser::GlobalContext * /*ctx*/) override { }
  virtual void exitGlobal(SpadeAssemblyParser::GlobalContext * /*ctx*/) override { }

  virtual void enterMethod(SpadeAssemblyParser::MethodContext * /*ctx*/) override { }
  virtual void exitMethod(SpadeAssemblyParser::MethodContext * /*ctx*/) override { }

  virtual void enterArgs(SpadeAssemblyParser::ArgsContext * /*ctx*/) override { }
  virtual void exitArgs(SpadeAssemblyParser::ArgsContext * /*ctx*/) override { }

  virtual void enterArg(SpadeAssemblyParser::ArgContext * /*ctx*/) override { }
  virtual void exitArg(SpadeAssemblyParser::ArgContext * /*ctx*/) override { }

  virtual void enterLocs(SpadeAssemblyParser::LocsContext * /*ctx*/) override { }
  virtual void exitLocs(SpadeAssemblyParser::LocsContext * /*ctx*/) override { }

  virtual void enterLocal(SpadeAssemblyParser::LocalContext * /*ctx*/) override { }
  virtual void exitLocal(SpadeAssemblyParser::LocalContext * /*ctx*/) override { }

  virtual void enterCode(SpadeAssemblyParser::CodeContext * /*ctx*/) override { }
  virtual void exitCode(SpadeAssemblyParser::CodeContext * /*ctx*/) override { }

  virtual void enterLine(SpadeAssemblyParser::LineContext * /*ctx*/) override { }
  virtual void exitLine(SpadeAssemblyParser::LineContext * /*ctx*/) override { }

  virtual void enterExceptionTable(SpadeAssemblyParser::ExceptionTableContext * /*ctx*/) override { }
  virtual void exitExceptionTable(SpadeAssemblyParser::ExceptionTableContext * /*ctx*/) override { }

  virtual void enterExceptionItem(SpadeAssemblyParser::ExceptionItemContext * /*ctx*/) override { }
  virtual void exitExceptionItem(SpadeAssemblyParser::ExceptionItemContext * /*ctx*/) override { }

  virtual void enterClass(SpadeAssemblyParser::ClassContext * /*ctx*/) override { }
  virtual void exitClass(SpadeAssemblyParser::ClassContext * /*ctx*/) override { }

  virtual void enterAccessor(SpadeAssemblyParser::AccessorContext * /*ctx*/) override { }
  virtual void exitAccessor(SpadeAssemblyParser::AccessorContext * /*ctx*/) override { }

  virtual void enterFields(SpadeAssemblyParser::FieldsContext * /*ctx*/) override { }
  virtual void exitFields(SpadeAssemblyParser::FieldsContext * /*ctx*/) override { }

  virtual void enterField(SpadeAssemblyParser::FieldContext * /*ctx*/) override { }
  virtual void exitField(SpadeAssemblyParser::FieldContext * /*ctx*/) override { }

  virtual void enterValue(SpadeAssemblyParser::ValueContext * /*ctx*/) override { }
  virtual void exitValue(SpadeAssemblyParser::ValueContext * /*ctx*/) override { }

  virtual void enterArray(SpadeAssemblyParser::ArrayContext * /*ctx*/) override { }
  virtual void exitArray(SpadeAssemblyParser::ArrayContext * /*ctx*/) override { }

  virtual void enterFloat(SpadeAssemblyParser::FloatContext * /*ctx*/) override { }
  virtual void exitFloat(SpadeAssemblyParser::FloatContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

