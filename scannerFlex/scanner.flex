%{
#include "token.h"
int num_column = 1;
%}

%option yylineno

SPACE      [ \t\n\r]+
DIGIT      [0-9]
LETTER     [A-Za-z]
IDENTIFIER (_|{LETTER})({DIGIT}|{LETTER}|_)*
NUMBER     -?[0-9]+(\.[0-9]+)?([eE]-?[0-9]+)?
VARIABLE   '{LETTER}'

%%
{SPACE}             {
                        if (yytext[0] == '\n')
                        {
                            num_column = 1;
                        }
                        else
                        {
                            num_column += yyleng;
                        }
                    }
"print"             {
                        num_column += yyleng;
                        return TOKEN_PRINT;
                    }
"display"           {
                        num_column += yyleng;
                        return TOKEN_DISPLAY;
                    }
"("                 {
                        num_column += yyleng;
                        return TOKEN_LPAREN;
                    }
")"                 {
                        num_column += yyleng;
                        return TOKEN_RPAREN;
                    }
"["                 {
                        num_column += yyleng;
                        return TOKEN_LBRACKET;
                    }
"]"                 {
                        num_column += yyleng;
                        return TOKEN_RBRACKET;
                    }
"{"                 {
                        num_column += yyleng;
                        return TOKEN_LBRACE;
                    }
"}"                 {
                        num_column += yyleng;
                        return TOKEN_RBRACE;
                    }
","                 {
                        num_column += yyleng;
                        return TOKEN_COMMA;
                    }
";"                 {
                        num_column += yyleng;
                        return TOKEN_SEMICOLON;
                    }
"="                 {
                        num_column += yyleng;
                        return TOKEN_ASSIGN;
                    }
{NUMBER}            {
                        num_column += yyleng;
                        return TOKEN_NUMBER;
                    }
{VARIABLE}          {
                        num_column += yyleng;
                        return TOKEN_VAR;
                    }

"+"                 {
                        num_column += yyleng;
                        return TOKEN_ADD;
                    }
"-"                 {
                        num_column += yyleng;
                        return TOKEN_SUBSTRACT;
                    }
"*"                 {
                        num_column += yyleng;
                        return TOKEN_MULTIPLY;
                    }
"/"                 {
                        num_column += yyleng;
                        return TOKEN_DIVIDE;
                    }
"^"                 {
                        num_column += yyleng;
                        return TOKEN_POWER;
                    }

"LOG"               {
                        num_column += yyleng;
                        return TOKEN_LOG;
                    }
"LN"                {
                        num_column += yyleng;
                        return TOKEN_LN;
                    }
"SQRT"              {
                        num_column += yyleng;
                        return TOKEN_SQRT;
                    }
"ROOT"              {
                        num_column += yyleng;
                        return TOKEN_ROOT;
                    }
"SIN"               {
                        num_column += yyleng;
                        return TOKEN_SIN;
                    }
"COS"               {
                        num_column += yyleng;
                        return TOKEN_COS;
                    }
"TAN"               {
                        num_column += yyleng;
                        return TOKEN_TAN;
                    }
"CTG"               {
                        num_column += yyleng;
                        return TOKEN_CTG;
                    }
"INVERSE"           {
                        num_column += yyleng;
                        return TOKEN_INVERSE;
                    }
"MATRIXLU"          {
                        num_column += yyleng;
                        return TOKEN_MATRIXLU;
                    }
"TRIDIAGONAL"       {
                        num_column += yyleng;
                        return TOKEN_TRIDIAGONAL;
                    }
"REALEIGENVALUES"   {
                        num_column += yyleng;
                        return TOKEN_REALEIGENVALUES;
                    }
"DETERMINANT"       {
                        num_column += yyleng;
                        return TOKEN_DETERMINANT;
                    }
"BISECTIONROOT"     {
                        num_column += yyleng;
                        return TOKEN_BISECTIONROOT;
                    }
"PI"                {
                        num_column += yyleng;
                        return TOKEN_PI;
                    }
"EULER"             {
                        num_column += yyleng;
                        return TOKEN_EULER;
                    }

"params"            {
                        num_column += yyleng;
                        return TOKEN_PARAMS;
                    }
{IDENTIFIER}        {
                        num_column += yyleng;
                        return TOKEN_IDENTIFIER;
                    }

.                   {
                        const int TAM = 256;
                        char buffer[TAM];
                        snprintf(buffer, TAM, "\nERROR:\n\tLine: %d\n\tColumn: %d\n\tUnknown Token: '%s'\n", yylineno, num_column, yytext);
                        yy_fatal_error(buffer);
                    }
%%

int yywrap() { return 1; }