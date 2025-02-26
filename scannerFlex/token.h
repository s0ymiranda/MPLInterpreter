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
    TOKEN_PARAMS = 277,

    TOKEN_IDENTIFIER = 310,

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
        case TOKEN_PARAMS: return "PARAMS";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
    }
}