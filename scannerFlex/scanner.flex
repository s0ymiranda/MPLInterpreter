%{
#include "token.h"
%}

SPACE      [ \t\n]+
DIGIT      [0-9]
LETTER     [A-Za-z]
IDENTIFIER (_|{LETTER})({DIGIT}|{LETTER}|_)*
NUMBER     -?[0-9]+(\.[0-9]+)?([eE]-?[0-9]+)?
VARIABLE   '{LETTER}'

%%
{SPACE}         { /* Ignore */ }
"print"         { return TOKEN_PRINT; }
"display"       { return TOKEN_DISPLAY; }
"("             { return TOKEN_LPAREN; }
")"             { return TOKEN_RPAREN; }
"["             { return TOKEN_LBRACKET; }
"]"             { return TOKEN_RBRACKET; }
"{"             { return TOKEN_LBRACE; }
"}"             { return TOKEN_RBRACE; }
","             { return TOKEN_COMMA; }
";"             { return TOKEN_SEMICOLON; }
"="             { return TOKEN_ASSIGN; }
{NUMBER}        { return TOKEN_NUMBER; }
{VARIABLE}      { return TOKEN_VAR; }

"+"             { return TOKEN_ADD; }
"-"             { return TOKEN_SUBSTRACT; }
"*"             { return TOKEN_MULTIPLY; }
"/"             { return TOKEN_DIVIDE; }
"^"             { return TOKEN_POW; }
"LOG"           { return TOKEN_LOG; }
"params"        { return TOKEN_PARAMS; }
{IDENTIFIER}    { return TOKEN_IDENTIFIER; }
%%

int yywrap() { return 1; }