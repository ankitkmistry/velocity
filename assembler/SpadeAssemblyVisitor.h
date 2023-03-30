
// Generated from H:/Programming (Ankit)/Projects/spade/1.0/velocity/assembler\SpadeAssembly.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "SpadeAssemblyParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by SpadeAssemblyParser.
 */
class  SpadeAssemblyVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by SpadeAssemblyParser.
   */
    virtual std::any visitAssembly(SpadeAssemblyParser::AssemblyContext *context) = 0;

    virtual std::any visitMetadata(SpadeAssemblyParser::MetadataContext *context) = 0;

    virtual std::any visitGlobals(SpadeAssemblyParser::GlobalsContext *context) = 0;

    virtual std::any visitGlobal(SpadeAssemblyParser::GlobalContext *context) = 0;

    virtual std::any visitMethod(SpadeAssemblyParser::MethodContext *context) = 0;

    virtual std::any visitArgs(SpadeAssemblyParser::ArgsContext *context) = 0;

    virtual std::any visitArg(SpadeAssemblyParser::ArgContext *context) = 0;

    virtual std::any visitLocs(SpadeAssemblyParser::LocsContext *context) = 0;

    virtual std::any visitLocal(SpadeAssemblyParser::LocalContext *context) = 0;

    virtual std::any visitCode(SpadeAssemblyParser::CodeContext *context) = 0;

    virtual std::any visitLine(SpadeAssemblyParser::LineContext *context) = 0;

    virtual std::any visitExceptionTable(SpadeAssemblyParser::ExceptionTableContext *context) = 0;

    virtual std::any visitExceptionItem(SpadeAssemblyParser::ExceptionItemContext *context) = 0;

    virtual std::any visitClass(SpadeAssemblyParser::ClassContext *context) = 0;

    virtual std::any visitAccessor(SpadeAssemblyParser::AccessorContext *context) = 0;

    virtual std::any visitFields(SpadeAssemblyParser::FieldsContext *context) = 0;

    virtual std::any visitField(SpadeAssemblyParser::FieldContext *context) = 0;

    virtual std::any visitValue(SpadeAssemblyParser::ValueContext *context) = 0;

    virtual std::any visitArray(SpadeAssemblyParser::ArrayContext *context) = 0;

    virtual std::any visitFloat(SpadeAssemblyParser::FloatContext *context) = 0;


};

