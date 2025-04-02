%{
#include <stdio.h>

extern int yylex();
int yyerror(const char*);
ASTNodeInterface* parser_result{nullptr};
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
%token TOKEN_INTEGRAL
%token TOKEN_ODEFIRST
%token TOKEN_INTERPOLATE

%%

program : statement_list                                              { parser_result = $1; }
        ;

statement_list : statement statement_list
               | statement
               ;

statement : print_statement
          | display_statement
          | assignment_statement
          | expression
          | expression TOKEN_SEMICOLON
          ;

print_statement : TOKEN_PRINT TOKEN_LPAREN expression TOKEN_RPAREN TOKEN_SEMICOLON;

display_statement : TOKEN_DISPLAY TOKEN_LPAREN expression TOKEN_RPAREN TOKEN_SEMICOLON;

assignment_statement : TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON
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

matrix_func_param : TOKEN_IDENTIFIER
                  | TOKEN_LBRACE vector_list TOKEN_RBRACE
                  ;

pair_or_id_param : pair_expression
                 | TOKEN_IDENTIFIER
                 ;

var_or_id_param : TOKEN_VAR
                | TOKEN_IDENTIFIER
                ;

integral_or_bisectionroot : TOKEN_BISECTIONROOT
                          | TOKEN_INTEGRAL
                          ;

vector_or_id_param : vector_expression
                   | TOKEN_IDENTIFIER
                   ;

number_or_id_param : TOKEN_NUMBER
                   | TOKEN_IDENTIFIER
                   ;

matrix_function_call : TOKEN_INVERSE TOKEN_LPAREN matrix_func_param TOKEN_RPAREN
                     | TOKEN_MATRIXLU TOKEN_LPAREN matrix_func_param TOKEN_RPAREN
                     | TOKEN_TRIDIAGONAL TOKEN_LPAREN matrix_func_param TOKEN_RPAREN
                     | TOKEN_REALEIGENVALUES TOKEN_LPAREN matrix_func_param TOKEN_RPAREN
                     | TOKEN_DETERMINANT TOKEN_LPAREN matrix_func_param TOKEN_RPAREN
                     ;

operations_function_call : integral_or_bisectionroot TOKEN_LPAREN pair_or_id_param TOKEN_COMMA expression TOKEN_COMMA var_or_id_param TOKEN_RPAREN
                         | TOKEN_INTERPOLATE TOKEN_LPAREN vector_or_id_param TOKEN_COMMA number_or_id_param TOKEN_RPAREN
                         | TOKEN_ODEFIRST TOKEN_LPAREN expression TOKEN_COMMA pair_or_id_param TOKEN_COMMA number_or_id_param TOKEN_COMMA var_or_id_param TOKEN_RPAREN
                         ;

function_call : logarithmic_function_call
              | root_function_call
              | trigonometric_function_call
              | matrix_function_call
              | operations_function_call
              ;

%%


int yyerror(const char* s)
{
    printf("Syntax error: %s\n", s);
    return 1;
}
