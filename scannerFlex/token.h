#pragma once
typedef enum
{
    TOKEN_EOF = 0,
    TOKEN_PRINT = 258,
    TOKEN_DISPLAY = 259,
    TOKEN_LPAREN = 260,
    TOKEN_RPAREN = 261,
    TOKEN_LBRACKET = 262,
    TOKEN_RBRACKET = 263,
    TOKEN_LBRACE = 264,
    TOKEN_RBRACE = 265,
    TOKEN_COMMA = 266,
    TOKEN_SEMICOLON = 267,
    TOKEN_ASSIGN = 268,
    TOKEN_NUMBER = 269,
    TOKEN_VAR = 270,

    TOKEN_ADD = 271,
    TOKEN_SUBSTRACT = 272,
    TOKEN_MULTIPLY = 273,
    TOKEN_DIVIDE = 274,
    TOKEN_POW = 275,
    TOKEN_LOG = 276,
    TOKEN_LN = 277,
    TOKEN_SQRT = 278,
    TOKEN_ROOT = 279,
    TOKEN_SIN = 280,
    TOKEN_COS = 281,
    TOKEN_TAN = 282,
    TOKEN_CTG = 283,
    TOKEN_INVERSE = 284,
    TOKEN_MATRIXLU = 285,
    TOKEN_TRIDIAGONAL = 286,
    TOKEN_REALEIGENVALUES = 287,
    TOKEN_DETERMINANT = 288,
    TOKEN_BISECTIONROOT = 289,
    TOKEN_PI = 290,
    TOKEN_EULER = 291,

    TOKEN_PARAMS = 292,

    TOKEN_IDENTIFIER = 310,
    TOKEN_UNKNOWN = 311

}token_t;

inline const char* to_str(token_t t)
{
    switch (t)
    {
        case TOKEN_PRINT: return "PRINT";
        case TOKEN_DISPLAY: return "DISPLAY";
        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_LBRACKET: return "LBRACKET";
        case TOKEN_RBRACKET: return "RBRACKET";
        case TOKEN_LBRACE: return "LBRACE";
        case TOKEN_RBRACE: return "RBRACE";
        case TOKEN_COMMA: return "COMMA";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_ASSIGN: return "ASSIGN";
        case TOKEN_NUMBER: return "NUMBER";
        case TOKEN_VAR: return "VARIABLE";
        case TOKEN_ADD: return "ADD";
        case TOKEN_SUBSTRACT: return "SUBSTRACT";
        case TOKEN_MULTIPLY: return "MULTIPLY";
        case TOKEN_DIVIDE: return "DIVIDE";
        case TOKEN_POW: return "POW";
        case TOKEN_LOG: return "LOG";
        case TOKEN_LN: return "LN";
        case TOKEN_SQRT: return "SQRT";
        case TOKEN_ROOT: return "ROOT";
        case TOKEN_SIN: return "SIN";
        case TOKEN_COS: return "COS";
        case TOKEN_TAN: return "TAN";
        case TOKEN_CTG: return "CTG";
        case TOKEN_INVERSE: return "INVERSE";
        case TOKEN_MATRIXLU: return "MATRIXLU";
        case TOKEN_TRIDIAGONAL: return "TRIDIAGONAL";
        case TOKEN_REALEIGENVALUES: return "REALEIGENVALUES";
        case TOKEN_DETERMINANT: return "DETERMINANT";
        case TOKEN_BISECTIONROOT: return "BISECTIONROOT";
        case TOKEN_PI: return "PI";
        case TOKEN_EULER: return "EULER";
        case TOKEN_PARAMS: return "PARAMS";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_UNKNOWN: return "UNKNOWN";
    }
}