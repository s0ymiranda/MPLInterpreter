%{
#include <stdio.h>

extern int yylex();
int yyerror(const char*);
%}

%token TOKEN_PRINT
%token TOKEN_DISPLAY
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_LBRACKET
%token TOKEN_RBRACKET
%token TOKEN_LBRACE
%token TOKEN_RBRACE
%token TOKEN_COMMA
%token TOKEN_SEMICOLON
%token TOKEN_ASSIGN
%token TOKEN_NUMBER
%token TOKEN_VAR
%token TOKEN_IDENTIFIER
%token TOKEN_ADD
%token TOKEN_SUBSTRACT
%token TOKEN_MULTIPLY
%token TOKEN_DIVIDE
%token TOKEN_POW
%token TOKEN_LOG
%token TOKEN_LN
%token TOKEN_SQRT
%token TOKEN_ROOT
%token TOKEN_SIN
%token TOKEN_COS
%token TOKEN_TAN
%token TOKEN_CTG
%token TOKEN_INVERSE
%token TOKEN_MATRIXLU
%token TOKEN_TRIDIAGONAL
%token TOKEN_REALEIGENVALUES
%token TOKEN_DETERMINANT
%token TOKEN_BISECTIONROOT
%token TOKEN_PI
%token TOKEN_EULER
%token TOKEN_PARAMS

%%

program : statement_list;

statement_list : statement_list statement
               | statement
               ;

statement : print_statement
          | display_statement
          | expression
          | expression TOKEN_SEMICOLON
          ;

print_statement : TOKEN_PRINT TOKEN_LPAREN expression TOKEN_RPAREN TOKEN_SEMICOLON;

display_statement : TOKEN_DISPLAY TOKEN_LPAREN expression TOKEN_RPAREN TOKEN_SEMICOLON;

assignment_expression : TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON
                      | TOKEN_VAR TOKEN_ASSIGN numeric_expression TOKEN_SEMICOLON;

expression : expression TOKEN_ADD term
           | expression TOKEN_SUBSTRACT term
           | term
           ;

term : term TOKEN_MULTIPLY factor
     | term TOKEN_DIVIDE factor
     | term TOKEN_POW factor
     | factor
     ;

numeric_expression : TOKEN_NUMBER
                   | trigonometric_function_call
                   | logarithmic_function_call
                   | root_function_call
                   | TOKEN_PI
                   | TOKEN_EULER
                   ;

factor : TOKEN_NUMBER
       | TOKEN_PI
       | TOKEN_EULER
       | TOKEN_VAR
       | TOKEN_IDENTIFIER
       | TOKEN_LPAREN expression TOKEN_RPAREN
       | pair_expression
       | vector_expression
       | matrix_expression
       | function_call
       | assignment_expression
       ;

pair_expression : TOKEN_LPAREN expression TOKEN_COMMA expression TOKEN_RPAREN;

vector_expression : TOKEN_LBRACKET expression_list TOKEN_RBRACKET;

matrix_expression : TOKEN_LBRACE vector_list TOKEN_RBRACE;

expression_list : expression_list TOKEN_COMMA expression
                | expression
                ;

vector_list : vector_list TOKEN_COMMA vector_expression
            | vector_expression
            | vector_list TOKEN_COMMA TOKEN_IDENTIFIER
            | TOKEN_IDENTIFIER
            ;

trigonometric_function_call: TOKEN_SIN TOKEN_LPAREN expression TOKEN_RPAREN
                           | TOKEN_COS TOKEN_LPAREN expression TOKEN_RPAREN
                           | TOKEN_TAN TOKEN_LPAREN expression TOKEN_RPAREN
                           | TOKEN_CTG TOKEN_LPAREN expression TOKEN_RPAREN
                           ;

logarithmic_function_call : TOKEN_LOG TOKEN_LPAREN expression TOKEN_COMMA expression TOKEN_RPAREN
                          | TOKEN_LN TOKEN_LPAREN expression TOKEN_RPAREN
                          ;

root_function_call : TOKEN_SQRT TOKEN_LPAREN expression TOKEN_RPAREN
                   | TOKEN_ROOT TOKEN_LPAREN expression TOKEN_COMMA expression TOKEN_RPAREN
                   ;

bisection_root_first_param : pair_expression
                           | TOKEN_IDENTIFIER
                           ;

bisection_root_third_param : TOKEN_VAR
                           | TOKEN_IDENTIFIER
                           ;

matrix_func_param : TOKEN_IDENTIFIER
                  | TOKEN_LBRACE vector_list TOKEN_RBRACE
                  ;

function_call : logarithmic_function_call
              | root_function_call
              | trigonometric_function_call
              | TOKEN_INVERSE TOKEN_LPAREN matrix_func_param TOKEN_RPAREN
              | TOKEN_MATRIXLU TOKEN_LPAREN matrix_func_param TOKEN_RPAREN
              | TOKEN_TRIDIAGONAL TOKEN_LPAREN matrix_func_param TOKEN_RPAREN
              | TOKEN_REALEIGENVALUES TOKEN_LPAREN matrix_func_param TOKEN_RPAREN
              | TOKEN_DETERMINANT TOKEN_LPAREN matrix_func_param TOKEN_RPAREN
              | TOKEN_BISECTIONROOT TOKEN_LPAREN bisection_root_first_param TOKEN_COMMA expression TOKEN_COMMA bisection_root_third_param TOKEN_RPAREN
              | TOKEN_PARAMS TOKEN_LPAREN expression_list TOKEN_RPAREN
              ;

%%


int yyerror(const char* s)
{
    printf("Syntax error: %s\n", s);
    return 1;
}