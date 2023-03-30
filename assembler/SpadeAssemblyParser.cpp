
// Generated from H:/Programming (Ankit)/Projects/spade/1.0/velocity/assembler\SpadeAssembly.g4 by ANTLR 4.11.1


#include "SpadeAssemblyListener.h"
#include "SpadeAssemblyVisitor.h"

#include "SpadeAssemblyParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct SpadeAssemblyParserStaticData final {
  SpadeAssemblyParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SpadeAssemblyParserStaticData(const SpadeAssemblyParserStaticData&) = delete;
  SpadeAssemblyParserStaticData(SpadeAssemblyParserStaticData&&) = delete;
  SpadeAssemblyParserStaticData& operator=(const SpadeAssemblyParserStaticData&) = delete;
  SpadeAssemblyParserStaticData& operator=(SpadeAssemblyParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag spadeassemblyParserOnceFlag;
SpadeAssemblyParserStaticData *spadeassemblyParserStaticData = nullptr;

void spadeassemblyParserInitialize() {
  assert(spadeassemblyParserStaticData == nullptr);
  auto staticData = std::make_unique<SpadeAssemblyParserStaticData>(
    std::vector<std::string>{
      "assembly", "metadata", "globals", "global", "method", "args", "arg", 
      "locs", "local", "code", "line", "exceptionTable", "exceptionItem", 
      "class", "accessor", "fields", "field", "value", "array", "float"
    },
    std::vector<std::string>{
      "", "'magic'", "':'", "'minorVersion'", "'majorVersion'", "'type'", 
      "'XP'", "'SLL'", "'imports'", "'globals'", "';'", "'VAR'", "'CONST'", 
      "'entry'", "'method'", "'maxstack'", "'args'", "'VALUE'", "'REF'", 
      "'locals'", "'['", "'closureStart'", "']'", "'code'", "'exceptionTable'", 
      "'-'", "'->'", "'class'", "'CLASS'", "'INTERFACE'", "'ENUM'", "'ANNOTATION'", 
      "'accessors'", "'PRIVATE'", "'INTERNAL'", "'PACKAGE_PRIVATE'", "'PROTECTED'", 
      "'PUBLIC'", "'ABSTRACT'", "'FINAL'", "'STATIC'", "'INLINE'", "'fields'", 
      "','", "'.'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "NUMBER", "STRING", "CSTRING", 
      "ID", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,49,262,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,1,0,1,0,3,0,43,8,
  	0,1,0,5,0,46,8,0,10,0,12,0,49,9,0,1,0,5,0,52,8,0,10,0,12,0,55,9,0,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,
  	2,5,2,76,8,2,10,2,12,2,79,9,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,4,3,4,89,
  	8,4,1,4,1,4,1,4,1,4,3,4,95,8,4,1,4,3,4,98,8,4,1,4,1,4,1,4,1,4,3,4,104,
  	8,4,1,4,3,4,107,8,4,1,4,1,4,1,5,1,5,1,5,5,5,114,8,5,10,5,12,5,117,9,5,
  	1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,3,7,132,8,7,1,7,1,
  	7,5,7,136,8,7,10,7,12,7,139,9,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,
  	9,5,9,151,8,9,10,9,12,9,154,9,9,1,9,1,9,1,10,1,10,3,10,160,8,10,1,10,
  	1,10,3,10,164,8,10,1,11,1,11,1,11,5,11,169,8,11,10,11,12,11,172,9,11,
  	1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,5,13,194,8,13,10,13,12,13,197,9,13,1,13,
  	3,13,200,8,13,1,13,5,13,203,8,13,10,13,12,13,206,9,13,1,13,5,13,209,8,
  	13,10,13,12,13,212,9,13,1,13,1,13,1,14,1,14,1,15,1,15,1,15,5,15,221,8,
  	15,10,15,12,15,224,9,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,17,1,17,
  	1,17,1,17,1,17,3,17,238,8,17,1,18,1,18,1,18,1,18,5,18,244,8,18,10,18,
  	12,18,247,9,18,3,18,249,8,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,3,19,260,8,19,1,19,0,0,20,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,
  	30,32,34,36,38,0,5,1,0,6,7,1,0,11,12,1,0,17,18,1,0,28,31,1,0,33,41,270,
  	0,40,1,0,0,0,2,56,1,0,0,0,4,72,1,0,0,0,6,82,1,0,0,0,8,88,1,0,0,0,10,110,
  	1,0,0,0,12,120,1,0,0,0,14,125,1,0,0,0,16,142,1,0,0,0,18,147,1,0,0,0,20,
  	159,1,0,0,0,22,165,1,0,0,0,24,175,1,0,0,0,26,183,1,0,0,0,28,215,1,0,0,
  	0,30,217,1,0,0,0,32,227,1,0,0,0,34,237,1,0,0,0,36,239,1,0,0,0,38,259,
  	1,0,0,0,40,42,3,2,1,0,41,43,3,4,2,0,42,41,1,0,0,0,42,43,1,0,0,0,43,47,
  	1,0,0,0,44,46,3,8,4,0,45,44,1,0,0,0,46,49,1,0,0,0,47,45,1,0,0,0,47,48,
  	1,0,0,0,48,53,1,0,0,0,49,47,1,0,0,0,50,52,3,26,13,0,51,50,1,0,0,0,52,
  	55,1,0,0,0,53,51,1,0,0,0,53,54,1,0,0,0,54,1,1,0,0,0,55,53,1,0,0,0,56,
  	57,5,1,0,0,57,58,5,2,0,0,58,59,5,45,0,0,59,60,5,3,0,0,60,61,5,2,0,0,61,
  	62,5,45,0,0,62,63,5,4,0,0,63,64,5,2,0,0,64,65,5,45,0,0,65,66,5,5,0,0,
  	66,67,5,2,0,0,67,68,7,0,0,0,68,69,5,8,0,0,69,70,5,2,0,0,70,71,3,36,18,
  	0,71,3,1,0,0,0,72,73,5,9,0,0,73,77,5,2,0,0,74,76,3,6,3,0,75,74,1,0,0,
  	0,76,79,1,0,0,0,77,75,1,0,0,0,77,78,1,0,0,0,78,80,1,0,0,0,79,77,1,0,0,
  	0,80,81,5,10,0,0,81,5,1,0,0,0,82,83,7,1,0,0,83,84,5,48,0,0,84,85,5,2,
  	0,0,85,86,5,46,0,0,86,7,1,0,0,0,87,89,5,13,0,0,88,87,1,0,0,0,88,89,1,
  	0,0,0,89,90,1,0,0,0,90,91,5,14,0,0,91,92,5,46,0,0,92,94,5,2,0,0,93,95,
  	3,10,5,0,94,93,1,0,0,0,94,95,1,0,0,0,95,97,1,0,0,0,96,98,3,14,7,0,97,
  	96,1,0,0,0,97,98,1,0,0,0,98,99,1,0,0,0,99,100,5,15,0,0,100,101,5,2,0,
  	0,101,103,5,45,0,0,102,104,3,18,9,0,103,102,1,0,0,0,103,104,1,0,0,0,104,
  	106,1,0,0,0,105,107,3,22,11,0,106,105,1,0,0,0,106,107,1,0,0,0,107,108,
  	1,0,0,0,108,109,5,10,0,0,109,9,1,0,0,0,110,111,5,16,0,0,111,115,5,2,0,
  	0,112,114,3,12,6,0,113,112,1,0,0,0,114,117,1,0,0,0,115,113,1,0,0,0,115,
  	116,1,0,0,0,116,118,1,0,0,0,117,115,1,0,0,0,118,119,5,10,0,0,119,11,1,
  	0,0,0,120,121,7,2,0,0,121,122,5,48,0,0,122,123,5,2,0,0,123,124,5,46,0,
  	0,124,13,1,0,0,0,125,131,5,19,0,0,126,127,5,20,0,0,127,128,5,21,0,0,128,
  	129,5,2,0,0,129,130,5,45,0,0,130,132,5,22,0,0,131,126,1,0,0,0,131,132,
  	1,0,0,0,132,133,1,0,0,0,133,137,5,2,0,0,134,136,3,16,8,0,135,134,1,0,
  	0,0,136,139,1,0,0,0,137,135,1,0,0,0,137,138,1,0,0,0,138,140,1,0,0,0,139,
  	137,1,0,0,0,140,141,5,10,0,0,141,15,1,0,0,0,142,143,7,1,0,0,143,144,5,
  	48,0,0,144,145,5,2,0,0,145,146,5,46,0,0,146,17,1,0,0,0,147,148,5,23,0,
  	0,148,152,5,2,0,0,149,151,3,20,10,0,150,149,1,0,0,0,151,154,1,0,0,0,152,
  	150,1,0,0,0,152,153,1,0,0,0,153,155,1,0,0,0,154,152,1,0,0,0,155,156,5,
  	10,0,0,156,19,1,0,0,0,157,158,5,48,0,0,158,160,5,2,0,0,159,157,1,0,0,
  	0,159,160,1,0,0,0,160,161,1,0,0,0,161,163,5,48,0,0,162,164,3,34,17,0,
  	163,162,1,0,0,0,163,164,1,0,0,0,164,21,1,0,0,0,165,166,5,24,0,0,166,170,
  	5,2,0,0,167,169,3,24,12,0,168,167,1,0,0,0,169,172,1,0,0,0,170,168,1,0,
  	0,0,170,171,1,0,0,0,171,173,1,0,0,0,172,170,1,0,0,0,173,174,5,10,0,0,
  	174,23,1,0,0,0,175,176,5,48,0,0,176,177,5,25,0,0,177,178,5,48,0,0,178,
  	179,5,26,0,0,179,180,5,48,0,0,180,181,5,2,0,0,181,182,5,46,0,0,182,25,
  	1,0,0,0,183,184,5,27,0,0,184,185,5,46,0,0,185,186,5,2,0,0,186,187,5,5,
  	0,0,187,188,5,2,0,0,188,189,7,3,0,0,189,190,5,10,0,0,190,191,5,32,0,0,
  	191,195,5,2,0,0,192,194,3,28,14,0,193,192,1,0,0,0,194,197,1,0,0,0,195,
  	193,1,0,0,0,195,196,1,0,0,0,196,199,1,0,0,0,197,195,1,0,0,0,198,200,3,
  	30,15,0,199,198,1,0,0,0,199,200,1,0,0,0,200,204,1,0,0,0,201,203,3,8,4,
  	0,202,201,1,0,0,0,203,206,1,0,0,0,204,202,1,0,0,0,204,205,1,0,0,0,205,
  	210,1,0,0,0,206,204,1,0,0,0,207,209,3,26,13,0,208,207,1,0,0,0,209,212,
  	1,0,0,0,210,208,1,0,0,0,210,211,1,0,0,0,211,213,1,0,0,0,212,210,1,0,0,
  	0,213,214,5,10,0,0,214,27,1,0,0,0,215,216,7,4,0,0,216,29,1,0,0,0,217,
  	218,5,42,0,0,218,222,5,2,0,0,219,221,3,32,16,0,220,219,1,0,0,0,221,224,
  	1,0,0,0,222,220,1,0,0,0,222,223,1,0,0,0,223,225,1,0,0,0,224,222,1,0,0,
  	0,225,226,5,10,0,0,226,31,1,0,0,0,227,228,7,1,0,0,228,229,5,46,0,0,229,
  	230,5,2,0,0,230,231,5,46,0,0,231,33,1,0,0,0,232,238,5,45,0,0,233,238,
  	5,46,0,0,234,238,5,47,0,0,235,238,3,36,18,0,236,238,3,38,19,0,237,232,
  	1,0,0,0,237,233,1,0,0,0,237,234,1,0,0,0,237,235,1,0,0,0,237,236,1,0,0,
  	0,238,35,1,0,0,0,239,248,5,20,0,0,240,245,3,34,17,0,241,242,5,43,0,0,
  	242,244,3,34,17,0,243,241,1,0,0,0,244,247,1,0,0,0,245,243,1,0,0,0,245,
  	246,1,0,0,0,246,249,1,0,0,0,247,245,1,0,0,0,248,240,1,0,0,0,248,249,1,
  	0,0,0,249,250,1,0,0,0,250,251,5,22,0,0,251,37,1,0,0,0,252,253,5,45,0,
  	0,253,254,5,44,0,0,254,260,5,45,0,0,255,256,5,45,0,0,256,260,5,44,0,0,
  	257,258,5,44,0,0,258,260,5,45,0,0,259,252,1,0,0,0,259,255,1,0,0,0,259,
  	257,1,0,0,0,260,39,1,0,0,0,25,42,47,53,77,88,94,97,103,106,115,131,137,
  	152,159,163,170,195,199,204,210,222,237,245,248,259
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  spadeassemblyParserStaticData = staticData.release();
}

}

SpadeAssemblyParser::SpadeAssemblyParser(TokenStream *input) : SpadeAssemblyParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

SpadeAssemblyParser::SpadeAssemblyParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  SpadeAssemblyParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *spadeassemblyParserStaticData->atn, spadeassemblyParserStaticData->decisionToDFA, spadeassemblyParserStaticData->sharedContextCache, options);
}

SpadeAssemblyParser::~SpadeAssemblyParser() {
  delete _interpreter;
}

const atn::ATN& SpadeAssemblyParser::getATN() const {
  return *spadeassemblyParserStaticData->atn;
}

std::string SpadeAssemblyParser::getGrammarFileName() const {
  return "SpadeAssembly.g4";
}

const std::vector<std::string>& SpadeAssemblyParser::getRuleNames() const {
  return spadeassemblyParserStaticData->ruleNames;
}

const dfa::Vocabulary& SpadeAssemblyParser::getVocabulary() const {
  return spadeassemblyParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView SpadeAssemblyParser::getSerializedATN() const {
  return spadeassemblyParserStaticData->serializedATN;
}


//----------------- AssemblyContext ------------------------------------------------------------------

SpadeAssemblyParser::AssemblyContext::AssemblyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SpadeAssemblyParser::MetadataContext* SpadeAssemblyParser::AssemblyContext::metadata() {
  return getRuleContext<SpadeAssemblyParser::MetadataContext>(0);
}

SpadeAssemblyParser::GlobalsContext* SpadeAssemblyParser::AssemblyContext::globals() {
  return getRuleContext<SpadeAssemblyParser::GlobalsContext>(0);
}

std::vector<SpadeAssemblyParser::MethodContext *> SpadeAssemblyParser::AssemblyContext::method() {
  return getRuleContexts<SpadeAssemblyParser::MethodContext>();
}

SpadeAssemblyParser::MethodContext* SpadeAssemblyParser::AssemblyContext::method(size_t i) {
  return getRuleContext<SpadeAssemblyParser::MethodContext>(i);
}

std::vector<SpadeAssemblyParser::ClassContext *> SpadeAssemblyParser::AssemblyContext::class_() {
  return getRuleContexts<SpadeAssemblyParser::ClassContext>();
}

SpadeAssemblyParser::ClassContext* SpadeAssemblyParser::AssemblyContext::class_(size_t i) {
  return getRuleContext<SpadeAssemblyParser::ClassContext>(i);
}


size_t SpadeAssemblyParser::AssemblyContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleAssembly;
}

void SpadeAssemblyParser::AssemblyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssembly(this);
}

void SpadeAssemblyParser::AssemblyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssembly(this);
}


std::any SpadeAssemblyParser::AssemblyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitAssembly(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::AssemblyContext* SpadeAssemblyParser::assembly() {
  AssemblyContext *_localctx = _tracker.createInstance<AssemblyContext>(_ctx, getState());
  enterRule(_localctx, 0, SpadeAssemblyParser::RuleAssembly);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(40);
    metadata();
    setState(42);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SpadeAssemblyParser::T__8) {
      setState(41);
      globals();
    }
    setState(47);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SpadeAssemblyParser::T__12

    || _la == SpadeAssemblyParser::T__13) {
      setState(44);
      method();
      setState(49);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(53);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SpadeAssemblyParser::T__26) {
      setState(50);
      class_();
      setState(55);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MetadataContext ------------------------------------------------------------------

SpadeAssemblyParser::MetadataContext::MetadataContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SpadeAssemblyParser::MetadataContext::NUMBER() {
  return getTokens(SpadeAssemblyParser::NUMBER);
}

tree::TerminalNode* SpadeAssemblyParser::MetadataContext::NUMBER(size_t i) {
  return getToken(SpadeAssemblyParser::NUMBER, i);
}

SpadeAssemblyParser::ArrayContext* SpadeAssemblyParser::MetadataContext::array() {
  return getRuleContext<SpadeAssemblyParser::ArrayContext>(0);
}


size_t SpadeAssemblyParser::MetadataContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleMetadata;
}

void SpadeAssemblyParser::MetadataContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMetadata(this);
}

void SpadeAssemblyParser::MetadataContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMetadata(this);
}


std::any SpadeAssemblyParser::MetadataContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitMetadata(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::MetadataContext* SpadeAssemblyParser::metadata() {
  MetadataContext *_localctx = _tracker.createInstance<MetadataContext>(_ctx, getState());
  enterRule(_localctx, 2, SpadeAssemblyParser::RuleMetadata);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    match(SpadeAssemblyParser::T__0);
    setState(57);
    match(SpadeAssemblyParser::T__1);
    setState(58);
    match(SpadeAssemblyParser::NUMBER);
    setState(59);
    match(SpadeAssemblyParser::T__2);
    setState(60);
    match(SpadeAssemblyParser::T__1);
    setState(61);
    match(SpadeAssemblyParser::NUMBER);
    setState(62);
    match(SpadeAssemblyParser::T__3);
    setState(63);
    match(SpadeAssemblyParser::T__1);
    setState(64);
    match(SpadeAssemblyParser::NUMBER);
    setState(65);
    match(SpadeAssemblyParser::T__4);
    setState(66);
    match(SpadeAssemblyParser::T__1);
    setState(67);
    _la = _input->LA(1);
    if (!(_la == SpadeAssemblyParser::T__5

    || _la == SpadeAssemblyParser::T__6)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(68);
    match(SpadeAssemblyParser::T__7);
    setState(69);
    match(SpadeAssemblyParser::T__1);
    setState(70);
    array();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GlobalsContext ------------------------------------------------------------------

SpadeAssemblyParser::GlobalsContext::GlobalsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SpadeAssemblyParser::GlobalContext *> SpadeAssemblyParser::GlobalsContext::global() {
  return getRuleContexts<SpadeAssemblyParser::GlobalContext>();
}

SpadeAssemblyParser::GlobalContext* SpadeAssemblyParser::GlobalsContext::global(size_t i) {
  return getRuleContext<SpadeAssemblyParser::GlobalContext>(i);
}


size_t SpadeAssemblyParser::GlobalsContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleGlobals;
}

void SpadeAssemblyParser::GlobalsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobals(this);
}

void SpadeAssemblyParser::GlobalsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobals(this);
}


std::any SpadeAssemblyParser::GlobalsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitGlobals(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::GlobalsContext* SpadeAssemblyParser::globals() {
  GlobalsContext *_localctx = _tracker.createInstance<GlobalsContext>(_ctx, getState());
  enterRule(_localctx, 4, SpadeAssemblyParser::RuleGlobals);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(72);
    match(SpadeAssemblyParser::T__8);
    setState(73);
    match(SpadeAssemblyParser::T__1);
    setState(77);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SpadeAssemblyParser::T__10

    || _la == SpadeAssemblyParser::T__11) {
      setState(74);
      global();
      setState(79);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(80);
    match(SpadeAssemblyParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GlobalContext ------------------------------------------------------------------

SpadeAssemblyParser::GlobalContext::GlobalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SpadeAssemblyParser::GlobalContext::ID() {
  return getToken(SpadeAssemblyParser::ID, 0);
}

tree::TerminalNode* SpadeAssemblyParser::GlobalContext::STRING() {
  return getToken(SpadeAssemblyParser::STRING, 0);
}


size_t SpadeAssemblyParser::GlobalContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleGlobal;
}

void SpadeAssemblyParser::GlobalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal(this);
}

void SpadeAssemblyParser::GlobalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal(this);
}


std::any SpadeAssemblyParser::GlobalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitGlobal(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::GlobalContext* SpadeAssemblyParser::global() {
  GlobalContext *_localctx = _tracker.createInstance<GlobalContext>(_ctx, getState());
  enterRule(_localctx, 6, SpadeAssemblyParser::RuleGlobal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    _la = _input->LA(1);
    if (!(_la == SpadeAssemblyParser::T__10

    || _la == SpadeAssemblyParser::T__11)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(83);
    match(SpadeAssemblyParser::ID);
    setState(84);
    match(SpadeAssemblyParser::T__1);
    setState(85);
    match(SpadeAssemblyParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodContext ------------------------------------------------------------------

SpadeAssemblyParser::MethodContext::MethodContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SpadeAssemblyParser::MethodContext::STRING() {
  return getToken(SpadeAssemblyParser::STRING, 0);
}

tree::TerminalNode* SpadeAssemblyParser::MethodContext::NUMBER() {
  return getToken(SpadeAssemblyParser::NUMBER, 0);
}

SpadeAssemblyParser::ArgsContext* SpadeAssemblyParser::MethodContext::args() {
  return getRuleContext<SpadeAssemblyParser::ArgsContext>(0);
}

SpadeAssemblyParser::LocsContext* SpadeAssemblyParser::MethodContext::locs() {
  return getRuleContext<SpadeAssemblyParser::LocsContext>(0);
}

SpadeAssemblyParser::CodeContext* SpadeAssemblyParser::MethodContext::code() {
  return getRuleContext<SpadeAssemblyParser::CodeContext>(0);
}

SpadeAssemblyParser::ExceptionTableContext* SpadeAssemblyParser::MethodContext::exceptionTable() {
  return getRuleContext<SpadeAssemblyParser::ExceptionTableContext>(0);
}


size_t SpadeAssemblyParser::MethodContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleMethod;
}

void SpadeAssemblyParser::MethodContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethod(this);
}

void SpadeAssemblyParser::MethodContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethod(this);
}


std::any SpadeAssemblyParser::MethodContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitMethod(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::MethodContext* SpadeAssemblyParser::method() {
  MethodContext *_localctx = _tracker.createInstance<MethodContext>(_ctx, getState());
  enterRule(_localctx, 8, SpadeAssemblyParser::RuleMethod);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SpadeAssemblyParser::T__12) {
      setState(87);
      match(SpadeAssemblyParser::T__12);
    }
    setState(90);
    match(SpadeAssemblyParser::T__13);
    setState(91);
    match(SpadeAssemblyParser::STRING);
    setState(92);
    match(SpadeAssemblyParser::T__1);
    setState(94);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SpadeAssemblyParser::T__15) {
      setState(93);
      args();
    }
    setState(97);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SpadeAssemblyParser::T__18) {
      setState(96);
      locs();
    }
    setState(99);
    match(SpadeAssemblyParser::T__14);
    setState(100);
    match(SpadeAssemblyParser::T__1);
    setState(101);
    match(SpadeAssemblyParser::NUMBER);
    setState(103);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SpadeAssemblyParser::T__22) {
      setState(102);
      code();
    }
    setState(106);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SpadeAssemblyParser::T__23) {
      setState(105);
      exceptionTable();
    }
    setState(108);
    match(SpadeAssemblyParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgsContext ------------------------------------------------------------------

SpadeAssemblyParser::ArgsContext::ArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SpadeAssemblyParser::ArgContext *> SpadeAssemblyParser::ArgsContext::arg() {
  return getRuleContexts<SpadeAssemblyParser::ArgContext>();
}

SpadeAssemblyParser::ArgContext* SpadeAssemblyParser::ArgsContext::arg(size_t i) {
  return getRuleContext<SpadeAssemblyParser::ArgContext>(i);
}


size_t SpadeAssemblyParser::ArgsContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleArgs;
}

void SpadeAssemblyParser::ArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgs(this);
}

void SpadeAssemblyParser::ArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgs(this);
}


std::any SpadeAssemblyParser::ArgsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitArgs(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::ArgsContext* SpadeAssemblyParser::args() {
  ArgsContext *_localctx = _tracker.createInstance<ArgsContext>(_ctx, getState());
  enterRule(_localctx, 10, SpadeAssemblyParser::RuleArgs);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(110);
    match(SpadeAssemblyParser::T__15);
    setState(111);
    match(SpadeAssemblyParser::T__1);
    setState(115);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SpadeAssemblyParser::T__16

    || _la == SpadeAssemblyParser::T__17) {
      setState(112);
      arg();
      setState(117);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(118);
    match(SpadeAssemblyParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgContext ------------------------------------------------------------------

SpadeAssemblyParser::ArgContext::ArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SpadeAssemblyParser::ArgContext::ID() {
  return getToken(SpadeAssemblyParser::ID, 0);
}

tree::TerminalNode* SpadeAssemblyParser::ArgContext::STRING() {
  return getToken(SpadeAssemblyParser::STRING, 0);
}


size_t SpadeAssemblyParser::ArgContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleArg;
}

void SpadeAssemblyParser::ArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArg(this);
}

void SpadeAssemblyParser::ArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArg(this);
}


std::any SpadeAssemblyParser::ArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitArg(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::ArgContext* SpadeAssemblyParser::arg() {
  ArgContext *_localctx = _tracker.createInstance<ArgContext>(_ctx, getState());
  enterRule(_localctx, 12, SpadeAssemblyParser::RuleArg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(120);
    _la = _input->LA(1);
    if (!(_la == SpadeAssemblyParser::T__16

    || _la == SpadeAssemblyParser::T__17)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(121);
    match(SpadeAssemblyParser::ID);
    setState(122);
    match(SpadeAssemblyParser::T__1);
    setState(123);
    match(SpadeAssemblyParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocsContext ------------------------------------------------------------------

SpadeAssemblyParser::LocsContext::LocsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SpadeAssemblyParser::LocsContext::NUMBER() {
  return getToken(SpadeAssemblyParser::NUMBER, 0);
}

std::vector<SpadeAssemblyParser::LocalContext *> SpadeAssemblyParser::LocsContext::local() {
  return getRuleContexts<SpadeAssemblyParser::LocalContext>();
}

SpadeAssemblyParser::LocalContext* SpadeAssemblyParser::LocsContext::local(size_t i) {
  return getRuleContext<SpadeAssemblyParser::LocalContext>(i);
}


size_t SpadeAssemblyParser::LocsContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleLocs;
}

void SpadeAssemblyParser::LocsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLocs(this);
}

void SpadeAssemblyParser::LocsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLocs(this);
}


std::any SpadeAssemblyParser::LocsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitLocs(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::LocsContext* SpadeAssemblyParser::locs() {
  LocsContext *_localctx = _tracker.createInstance<LocsContext>(_ctx, getState());
  enterRule(_localctx, 14, SpadeAssemblyParser::RuleLocs);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    match(SpadeAssemblyParser::T__18);
    setState(131);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SpadeAssemblyParser::T__19) {
      setState(126);
      match(SpadeAssemblyParser::T__19);
      setState(127);
      match(SpadeAssemblyParser::T__20);
      setState(128);
      match(SpadeAssemblyParser::T__1);
      setState(129);
      match(SpadeAssemblyParser::NUMBER);
      setState(130);
      match(SpadeAssemblyParser::T__21);
    }
    setState(133);
    match(SpadeAssemblyParser::T__1);
    setState(137);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SpadeAssemblyParser::T__10

    || _la == SpadeAssemblyParser::T__11) {
      setState(134);
      local();
      setState(139);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(140);
    match(SpadeAssemblyParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocalContext ------------------------------------------------------------------

SpadeAssemblyParser::LocalContext::LocalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SpadeAssemblyParser::LocalContext::ID() {
  return getToken(SpadeAssemblyParser::ID, 0);
}

tree::TerminalNode* SpadeAssemblyParser::LocalContext::STRING() {
  return getToken(SpadeAssemblyParser::STRING, 0);
}


size_t SpadeAssemblyParser::LocalContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleLocal;
}

void SpadeAssemblyParser::LocalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLocal(this);
}

void SpadeAssemblyParser::LocalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLocal(this);
}


std::any SpadeAssemblyParser::LocalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitLocal(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::LocalContext* SpadeAssemblyParser::local() {
  LocalContext *_localctx = _tracker.createInstance<LocalContext>(_ctx, getState());
  enterRule(_localctx, 16, SpadeAssemblyParser::RuleLocal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(142);
    _la = _input->LA(1);
    if (!(_la == SpadeAssemblyParser::T__10

    || _la == SpadeAssemblyParser::T__11)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(143);
    match(SpadeAssemblyParser::ID);
    setState(144);
    match(SpadeAssemblyParser::T__1);
    setState(145);
    match(SpadeAssemblyParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CodeContext ------------------------------------------------------------------

SpadeAssemblyParser::CodeContext::CodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SpadeAssemblyParser::LineContext *> SpadeAssemblyParser::CodeContext::line() {
  return getRuleContexts<SpadeAssemblyParser::LineContext>();
}

SpadeAssemblyParser::LineContext* SpadeAssemblyParser::CodeContext::line(size_t i) {
  return getRuleContext<SpadeAssemblyParser::LineContext>(i);
}


size_t SpadeAssemblyParser::CodeContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleCode;
}

void SpadeAssemblyParser::CodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCode(this);
}

void SpadeAssemblyParser::CodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCode(this);
}


std::any SpadeAssemblyParser::CodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitCode(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::CodeContext* SpadeAssemblyParser::code() {
  CodeContext *_localctx = _tracker.createInstance<CodeContext>(_ctx, getState());
  enterRule(_localctx, 18, SpadeAssemblyParser::RuleCode);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    match(SpadeAssemblyParser::T__22);
    setState(148);
    match(SpadeAssemblyParser::T__1);
    setState(152);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SpadeAssemblyParser::ID) {
      setState(149);
      line();
      setState(154);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(155);
    match(SpadeAssemblyParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LineContext ------------------------------------------------------------------

SpadeAssemblyParser::LineContext::LineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SpadeAssemblyParser::LineContext::ID() {
  return getTokens(SpadeAssemblyParser::ID);
}

tree::TerminalNode* SpadeAssemblyParser::LineContext::ID(size_t i) {
  return getToken(SpadeAssemblyParser::ID, i);
}

SpadeAssemblyParser::ValueContext* SpadeAssemblyParser::LineContext::value() {
  return getRuleContext<SpadeAssemblyParser::ValueContext>(0);
}


size_t SpadeAssemblyParser::LineContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleLine;
}

void SpadeAssemblyParser::LineContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLine(this);
}

void SpadeAssemblyParser::LineContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLine(this);
}


std::any SpadeAssemblyParser::LineContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitLine(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::LineContext* SpadeAssemblyParser::line() {
  LineContext *_localctx = _tracker.createInstance<LineContext>(_ctx, getState());
  enterRule(_localctx, 20, SpadeAssemblyParser::RuleLine);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(159);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      setState(157);
      match(SpadeAssemblyParser::ID);
      setState(158);
      match(SpadeAssemblyParser::T__1);
      break;
    }

    default:
      break;
    }
    setState(161);
    match(SpadeAssemblyParser::ID);
    setState(163);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 263882791714816) != 0) {
      setState(162);
      value();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExceptionTableContext ------------------------------------------------------------------

SpadeAssemblyParser::ExceptionTableContext::ExceptionTableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SpadeAssemblyParser::ExceptionItemContext *> SpadeAssemblyParser::ExceptionTableContext::exceptionItem() {
  return getRuleContexts<SpadeAssemblyParser::ExceptionItemContext>();
}

SpadeAssemblyParser::ExceptionItemContext* SpadeAssemblyParser::ExceptionTableContext::exceptionItem(size_t i) {
  return getRuleContext<SpadeAssemblyParser::ExceptionItemContext>(i);
}


size_t SpadeAssemblyParser::ExceptionTableContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleExceptionTable;
}

void SpadeAssemblyParser::ExceptionTableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExceptionTable(this);
}

void SpadeAssemblyParser::ExceptionTableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExceptionTable(this);
}


std::any SpadeAssemblyParser::ExceptionTableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitExceptionTable(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::ExceptionTableContext* SpadeAssemblyParser::exceptionTable() {
  ExceptionTableContext *_localctx = _tracker.createInstance<ExceptionTableContext>(_ctx, getState());
  enterRule(_localctx, 22, SpadeAssemblyParser::RuleExceptionTable);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(165);
    match(SpadeAssemblyParser::T__23);
    setState(166);
    match(SpadeAssemblyParser::T__1);
    setState(170);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SpadeAssemblyParser::ID) {
      setState(167);
      exceptionItem();
      setState(172);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(173);
    match(SpadeAssemblyParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExceptionItemContext ------------------------------------------------------------------

SpadeAssemblyParser::ExceptionItemContext::ExceptionItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SpadeAssemblyParser::ExceptionItemContext::ID() {
  return getTokens(SpadeAssemblyParser::ID);
}

tree::TerminalNode* SpadeAssemblyParser::ExceptionItemContext::ID(size_t i) {
  return getToken(SpadeAssemblyParser::ID, i);
}

tree::TerminalNode* SpadeAssemblyParser::ExceptionItemContext::STRING() {
  return getToken(SpadeAssemblyParser::STRING, 0);
}


size_t SpadeAssemblyParser::ExceptionItemContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleExceptionItem;
}

void SpadeAssemblyParser::ExceptionItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExceptionItem(this);
}

void SpadeAssemblyParser::ExceptionItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExceptionItem(this);
}


std::any SpadeAssemblyParser::ExceptionItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitExceptionItem(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::ExceptionItemContext* SpadeAssemblyParser::exceptionItem() {
  ExceptionItemContext *_localctx = _tracker.createInstance<ExceptionItemContext>(_ctx, getState());
  enterRule(_localctx, 24, SpadeAssemblyParser::RuleExceptionItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(175);
    match(SpadeAssemblyParser::ID);
    setState(176);
    match(SpadeAssemblyParser::T__24);
    setState(177);
    match(SpadeAssemblyParser::ID);
    setState(178);
    match(SpadeAssemblyParser::T__25);
    setState(179);
    match(SpadeAssemblyParser::ID);
    setState(180);
    match(SpadeAssemblyParser::T__1);
    setState(181);
    match(SpadeAssemblyParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassContext ------------------------------------------------------------------

SpadeAssemblyParser::ClassContext::ClassContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SpadeAssemblyParser::ClassContext::STRING() {
  return getToken(SpadeAssemblyParser::STRING, 0);
}

std::vector<SpadeAssemblyParser::AccessorContext *> SpadeAssemblyParser::ClassContext::accessor() {
  return getRuleContexts<SpadeAssemblyParser::AccessorContext>();
}

SpadeAssemblyParser::AccessorContext* SpadeAssemblyParser::ClassContext::accessor(size_t i) {
  return getRuleContext<SpadeAssemblyParser::AccessorContext>(i);
}

SpadeAssemblyParser::FieldsContext* SpadeAssemblyParser::ClassContext::fields() {
  return getRuleContext<SpadeAssemblyParser::FieldsContext>(0);
}

std::vector<SpadeAssemblyParser::MethodContext *> SpadeAssemblyParser::ClassContext::method() {
  return getRuleContexts<SpadeAssemblyParser::MethodContext>();
}

SpadeAssemblyParser::MethodContext* SpadeAssemblyParser::ClassContext::method(size_t i) {
  return getRuleContext<SpadeAssemblyParser::MethodContext>(i);
}

std::vector<SpadeAssemblyParser::ClassContext *> SpadeAssemblyParser::ClassContext::class_() {
  return getRuleContexts<SpadeAssemblyParser::ClassContext>();
}

SpadeAssemblyParser::ClassContext* SpadeAssemblyParser::ClassContext::class_(size_t i) {
  return getRuleContext<SpadeAssemblyParser::ClassContext>(i);
}


size_t SpadeAssemblyParser::ClassContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleClass;
}

void SpadeAssemblyParser::ClassContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClass(this);
}

void SpadeAssemblyParser::ClassContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClass(this);
}


std::any SpadeAssemblyParser::ClassContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitClass(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::ClassContext* SpadeAssemblyParser::class_() {
  ClassContext *_localctx = _tracker.createInstance<ClassContext>(_ctx, getState());
  enterRule(_localctx, 26, SpadeAssemblyParser::RuleClass);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(183);
    match(SpadeAssemblyParser::T__26);
    setState(184);
    match(SpadeAssemblyParser::STRING);
    setState(185);
    match(SpadeAssemblyParser::T__1);
    setState(186);
    match(SpadeAssemblyParser::T__4);
    setState(187);
    match(SpadeAssemblyParser::T__1);
    setState(188);
    _la = _input->LA(1);
    if (!(((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4026531840) != 0)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(189);
    match(SpadeAssemblyParser::T__9);
    setState(190);
    match(SpadeAssemblyParser::T__31);
    setState(191);
    match(SpadeAssemblyParser::T__1);
    setState(195);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4389456576512) != 0) {
      setState(192);
      accessor();
      setState(197);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(199);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SpadeAssemblyParser::T__41) {
      setState(198);
      fields();
    }
    setState(204);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SpadeAssemblyParser::T__12

    || _la == SpadeAssemblyParser::T__13) {
      setState(201);
      method();
      setState(206);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(210);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SpadeAssemblyParser::T__26) {
      setState(207);
      class_();
      setState(212);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(213);
    match(SpadeAssemblyParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AccessorContext ------------------------------------------------------------------

SpadeAssemblyParser::AccessorContext::AccessorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SpadeAssemblyParser::AccessorContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleAccessor;
}

void SpadeAssemblyParser::AccessorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAccessor(this);
}

void SpadeAssemblyParser::AccessorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAccessor(this);
}


std::any SpadeAssemblyParser::AccessorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitAccessor(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::AccessorContext* SpadeAssemblyParser::accessor() {
  AccessorContext *_localctx = _tracker.createInstance<AccessorContext>(_ctx, getState());
  enterRule(_localctx, 28, SpadeAssemblyParser::RuleAccessor);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(215);
    _la = _input->LA(1);
    if (!(((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4389456576512) != 0)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldsContext ------------------------------------------------------------------

SpadeAssemblyParser::FieldsContext::FieldsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SpadeAssemblyParser::FieldContext *> SpadeAssemblyParser::FieldsContext::field() {
  return getRuleContexts<SpadeAssemblyParser::FieldContext>();
}

SpadeAssemblyParser::FieldContext* SpadeAssemblyParser::FieldsContext::field(size_t i) {
  return getRuleContext<SpadeAssemblyParser::FieldContext>(i);
}


size_t SpadeAssemblyParser::FieldsContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleFields;
}

void SpadeAssemblyParser::FieldsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFields(this);
}

void SpadeAssemblyParser::FieldsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFields(this);
}


std::any SpadeAssemblyParser::FieldsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitFields(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::FieldsContext* SpadeAssemblyParser::fields() {
  FieldsContext *_localctx = _tracker.createInstance<FieldsContext>(_ctx, getState());
  enterRule(_localctx, 30, SpadeAssemblyParser::RuleFields);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(217);
    match(SpadeAssemblyParser::T__41);
    setState(218);
    match(SpadeAssemblyParser::T__1);
    setState(222);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SpadeAssemblyParser::T__10

    || _la == SpadeAssemblyParser::T__11) {
      setState(219);
      field();
      setState(224);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(225);
    match(SpadeAssemblyParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldContext ------------------------------------------------------------------

SpadeAssemblyParser::FieldContext::FieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SpadeAssemblyParser::FieldContext::STRING() {
  return getTokens(SpadeAssemblyParser::STRING);
}

tree::TerminalNode* SpadeAssemblyParser::FieldContext::STRING(size_t i) {
  return getToken(SpadeAssemblyParser::STRING, i);
}


size_t SpadeAssemblyParser::FieldContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleField;
}

void SpadeAssemblyParser::FieldContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterField(this);
}

void SpadeAssemblyParser::FieldContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitField(this);
}


std::any SpadeAssemblyParser::FieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitField(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::FieldContext* SpadeAssemblyParser::field() {
  FieldContext *_localctx = _tracker.createInstance<FieldContext>(_ctx, getState());
  enterRule(_localctx, 32, SpadeAssemblyParser::RuleField);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(227);
    _la = _input->LA(1);
    if (!(_la == SpadeAssemblyParser::T__10

    || _la == SpadeAssemblyParser::T__11)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(228);
    match(SpadeAssemblyParser::STRING);
    setState(229);
    match(SpadeAssemblyParser::T__1);
    setState(230);
    match(SpadeAssemblyParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

SpadeAssemblyParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SpadeAssemblyParser::ValueContext::NUMBER() {
  return getToken(SpadeAssemblyParser::NUMBER, 0);
}

tree::TerminalNode* SpadeAssemblyParser::ValueContext::STRING() {
  return getToken(SpadeAssemblyParser::STRING, 0);
}

tree::TerminalNode* SpadeAssemblyParser::ValueContext::CSTRING() {
  return getToken(SpadeAssemblyParser::CSTRING, 0);
}

SpadeAssemblyParser::ArrayContext* SpadeAssemblyParser::ValueContext::array() {
  return getRuleContext<SpadeAssemblyParser::ArrayContext>(0);
}

SpadeAssemblyParser::FloatContext* SpadeAssemblyParser::ValueContext::float_() {
  return getRuleContext<SpadeAssemblyParser::FloatContext>(0);
}


size_t SpadeAssemblyParser::ValueContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleValue;
}

void SpadeAssemblyParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void SpadeAssemblyParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}


std::any SpadeAssemblyParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::ValueContext* SpadeAssemblyParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 34, SpadeAssemblyParser::RuleValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(237);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(232);
      match(SpadeAssemblyParser::NUMBER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(233);
      match(SpadeAssemblyParser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(234);
      match(SpadeAssemblyParser::CSTRING);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(235);
      array();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(236);
      float_();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayContext ------------------------------------------------------------------

SpadeAssemblyParser::ArrayContext::ArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SpadeAssemblyParser::ValueContext *> SpadeAssemblyParser::ArrayContext::value() {
  return getRuleContexts<SpadeAssemblyParser::ValueContext>();
}

SpadeAssemblyParser::ValueContext* SpadeAssemblyParser::ArrayContext::value(size_t i) {
  return getRuleContext<SpadeAssemblyParser::ValueContext>(i);
}


size_t SpadeAssemblyParser::ArrayContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleArray;
}

void SpadeAssemblyParser::ArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArray(this);
}

void SpadeAssemblyParser::ArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArray(this);
}


std::any SpadeAssemblyParser::ArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitArray(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::ArrayContext* SpadeAssemblyParser::array() {
  ArrayContext *_localctx = _tracker.createInstance<ArrayContext>(_ctx, getState());
  enterRule(_localctx, 36, SpadeAssemblyParser::RuleArray);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(239);
    match(SpadeAssemblyParser::T__19);
    setState(248);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 263882791714816) != 0) {
      setState(240);
      value();
      setState(245);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SpadeAssemblyParser::T__42) {
        setState(241);
        match(SpadeAssemblyParser::T__42);
        setState(242);
        value();
        setState(247);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(250);
    match(SpadeAssemblyParser::T__21);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FloatContext ------------------------------------------------------------------

SpadeAssemblyParser::FloatContext::FloatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SpadeAssemblyParser::FloatContext::NUMBER() {
  return getTokens(SpadeAssemblyParser::NUMBER);
}

tree::TerminalNode* SpadeAssemblyParser::FloatContext::NUMBER(size_t i) {
  return getToken(SpadeAssemblyParser::NUMBER, i);
}


size_t SpadeAssemblyParser::FloatContext::getRuleIndex() const {
  return SpadeAssemblyParser::RuleFloat;
}

void SpadeAssemblyParser::FloatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloat(this);
}

void SpadeAssemblyParser::FloatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SpadeAssemblyListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloat(this);
}


std::any SpadeAssemblyParser::FloatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SpadeAssemblyVisitor*>(visitor))
    return parserVisitor->visitFloat(this);
  else
    return visitor->visitChildren(this);
}

SpadeAssemblyParser::FloatContext* SpadeAssemblyParser::float_() {
  FloatContext *_localctx = _tracker.createInstance<FloatContext>(_ctx, getState());
  enterRule(_localctx, 38, SpadeAssemblyParser::RuleFloat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(259);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(252);
      match(SpadeAssemblyParser::NUMBER);
      setState(253);
      match(SpadeAssemblyParser::T__43);
      setState(254);
      match(SpadeAssemblyParser::NUMBER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(255);
      match(SpadeAssemblyParser::NUMBER);
      setState(256);
      match(SpadeAssemblyParser::T__43);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(257);
      match(SpadeAssemblyParser::T__43);
      setState(258);
      match(SpadeAssemblyParser::NUMBER);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void SpadeAssemblyParser::initialize() {
  ::antlr4::internal::call_once(spadeassemblyParserOnceFlag, spadeassemblyParserInitialize);
}
