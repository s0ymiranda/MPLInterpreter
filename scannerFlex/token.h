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
    TOKEN_POWER = 275,
    TOKEN_LOGARITHM = 276,
    TOKEN_NATURAL_LOGARITHM = 277,
    TOKEN_SQUARE_ROOT = 278,
    TOKEN_ROOT = 279,
    TOKEN_SINE = 280,
    TOKEN_COSINE = 281,
    TOKEN_TANGENT = 282,
    TOKEN_COTANGENT = 283,
    TOKEN_INVERSE = 284,
    TOKEN_MATRIX_LU = 285,
    TOKEN_TRIDIAGONAL = 286,
    TOKEN_REAL_EIGENVALUES = 287,
    TOKEN_DETERMINANT = 288,
    TOKEN_BISECTION_ROOT = 289,
    TOKEN_PI = 290,
    TOKEN_EULER = 291,
    TOKEN_PARAMS = 292,
    TOKEN_IDENTIFIER = 310

} token_t;

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
        case TOKEN_POWER: return "POWER";
        case TOKEN_LOGARITHM: return "LOGARITHM";
        case TOKEN_NATURAL_LOGARITHM: return "NATURAL_LOGARITHM";
        case TOKEN_SQUARE_ROOT: return "SQUARE_ROOT";
        case TOKEN_ROOT: return "ROOT";
        case TOKEN_SINE: return "SINE";
        case TOKEN_COSINE: return "COSINE";
        case TOKEN_TANGENT: return "TANGENT";
        case TOKEN_COTANGENT: return "COTANGENT";
        case TOKEN_INVERSE: return "INVERSE";
        case TOKEN_MATRIX_LU: return "MATRIX_LU";
        case TOKEN_TRIDIAGONAL: return "TRIDIAGONAL";
        case TOKEN_REAL_EIGENVALUES: return "REAL_EIGENVALUES";
        case TOKEN_DETERMINANT: return "DETERMINANT";
        case TOKEN_BISECTION_ROOT: return "BISECTION_ROOT";
        case TOKEN_PI: return "PI";
        case TOKEN_EULER: return "EULER";
        case TOKEN_PARAMS: return "PARAMS";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
    }
}