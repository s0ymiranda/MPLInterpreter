/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INCLUDE_TOKEN_H_INCLUDED
# define YY_YY_INCLUDE_TOKEN_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_PRINT = 258,             /* TOKEN_PRINT  */
    TOKEN_DISPLAY = 259,           /* TOKEN_DISPLAY  */
    TOKEN_LPAREN = 260,            /* TOKEN_LPAREN  */
    TOKEN_RPAREN = 261,            /* TOKEN_RPAREN  */
    TOKEN_LBRACKET = 262,          /* TOKEN_LBRACKET  */
    TOKEN_RBRACKET = 263,          /* TOKEN_RBRACKET  */
    TOKEN_LBRACE = 264,            /* TOKEN_LBRACE  */
    TOKEN_RBRACE = 265,            /* TOKEN_RBRACE  */
    TOKEN_COMMA = 266,             /* TOKEN_COMMA  */
    TOKEN_SEMICOLON = 267,         /* TOKEN_SEMICOLON  */
    TOKEN_ASSIGN = 268,            /* TOKEN_ASSIGN  */
    TOKEN_NUMBER = 269,            /* TOKEN_NUMBER  */
    TOKEN_VAR = 270,               /* TOKEN_VAR  */
    TOKEN_IDENTIFIER = 271,        /* TOKEN_IDENTIFIER  */
    TOKEN_ADD = 272,               /* TOKEN_ADD  */
    TOKEN_SUBSTRACT = 273,         /* TOKEN_SUBSTRACT  */
    TOKEN_MULTIPLY = 274,          /* TOKEN_MULTIPLY  */
    TOKEN_DIVIDE = 275,            /* TOKEN_DIVIDE  */
    TOKEN_POW = 276,               /* TOKEN_POW  */
    TOKEN_LOG = 277,               /* TOKEN_LOG  */
    TOKEN_LN = 278,                /* TOKEN_LN  */
    TOKEN_SQRT = 279,              /* TOKEN_SQRT  */
    TOKEN_ROOT = 280,              /* TOKEN_ROOT  */
    TOKEN_SIN = 281,               /* TOKEN_SIN  */
    TOKEN_COS = 282,               /* TOKEN_COS  */
    TOKEN_TAN = 283,               /* TOKEN_TAN  */
    TOKEN_CTG = 284,               /* TOKEN_CTG  */
    TOKEN_INVERSE = 285,           /* TOKEN_INVERSE  */
    TOKEN_MATRIXLU = 286,          /* TOKEN_MATRIXLU  */
    TOKEN_TRIDIAGONAL = 287,       /* TOKEN_TRIDIAGONAL  */
    TOKEN_REALEIGENVALUES = 288,   /* TOKEN_REALEIGENVALUES  */
    TOKEN_DETERMINANT = 289,       /* TOKEN_DETERMINANT  */
    TOKEN_BISECTIONROOT = 290,     /* TOKEN_BISECTIONROOT  */
    TOKEN_PI = 291,                /* TOKEN_PI  */
    TOKEN_EULER = 292,             /* TOKEN_EULER  */
    TOKEN_INTEGRAL = 293,          /* TOKEN_INTEGRAL  */
    TOKEN_ODEFIRST = 294,          /* TOKEN_ODEFIRST  */
    TOKEN_INTERPOLATE = 295        /* TOKEN_INTERPOLATE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INCLUDE_TOKEN_H_INCLUDED  */
