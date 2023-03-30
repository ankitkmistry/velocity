grammar SpadeAssembly;

options {
    language=Cpp;
}

assembly: metadata
          globals?
          method*
          class*
         ;
metadata: 'magic' ':' NUMBER
          'minorVersion' ':' NUMBER
          'majorVersion' ':' NUMBER
          'type' ':' ('XP'|'SLL')
          'imports' ':' array
         ;

globals: 'globals' ':' global* ';';
global: ('VAR'|'CONST') ID ':' STRING;

method: 'entry'? 'method' STRING ':'
            (args)?
            (locs)?
            'maxstack' ':' NUMBER
            (code)?
            (exceptionTable)? ';';
args: 'args' ':' arg* ';';
arg: ('VALUE'|'REF') ID ':' STRING;
locs: 'locals' ('[' 'closureStart' ':' NUMBER ']')? ':' local* ';';
local: ('VAR'|'CONST') ID ':' STRING;
code: 'code' ':' line* ';';
line: (ID ':')? ID value?;
exceptionTable: 'exceptionTable' ':' exceptionItem* ';';
exceptionItem: ID '-' ID '->' ID ':' STRING;

class: 'class' STRING ':'
            'type' ':' ('CLASS' | 'INTERFACE' | 'ENUM' | 'ANNOTATION') ';'
            'accessors' ':' accessor*
            fields?
            method*
            class* ';';
accessor: 'PRIVATE'
        | 'INTERNAL'
        | 'PACKAGE_PRIVATE'
        | 'PROTECTED'
        | 'PUBLIC'
        | 'ABSTRACT'
        | 'FINAL'
        | 'STATIC'
        | 'INLINE';
fields: 'fields' ':' field* ';';
field: ('VAR'|'CONST') STRING ':' STRING;

value: NUMBER | STRING | CSTRING | array | float;
array: '[' (value (',' value)*)? ']';
float: NUMBER '.' NUMBER
     | NUMBER '.'
     | '.' NUMBER
     ;

NUMBER: [0-9]+;
STRING: '"'.*?'"';
CSTRING: '\''.'\'';
ID: [a-zA-Z][a-zA-Z0-9]+;
WS: [ \t\r\n]+ -> skip;
