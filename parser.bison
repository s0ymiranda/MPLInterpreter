%{
#include <stdio.h>
#include <stdlib.h>
#include <Expression.hpp>

#define YYSTYPE Expression*

extern int yylex();
int yyerror(const char*);
extern char* yytext;
extern char* id;
extern char* assing_id;
extern char assing_variable;
Expression* parser_result{nullptr};

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

program : expressions_list                                          {   parser_result = $1;}
        ;

expressions_list : expression expressions_list                      {
                                                                        ExpressionList* exprList = dynamic_cast<ExpressionList*>($2);
                                                                        if (exprList)
                                                                        {
                                                                            exprList->addExpressionFront($1);
                                                                            $$ = exprList;
                                                                        }
                                                                        else
                                                                        {
                                                                            ExpressionList* newList = new ExpressionList();
                                                                            newList->addExpressionFront($1);
                                                                            newList->addExpressionFront($2);
                                                                            $$ = newList;
                                                                        }
                                                                    }
                 | expression                                       {
                                                                        ExpressionList* newList = new ExpressionList();
                                                                        newList->addExpressionFront($1);
                                                                        $$ = newList;
                                                                    }
                 ;

expression : print_expression
           | display_expression
           | assignment_expression
           | math_expression TOKEN_SEMICOLON                        { $$ = $1; }
           ;

print_expression : TOKEN_PRINT TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_SEMICOLON   {   $$ = new Print(std::string(id));}
                 ;

display_expression : TOKEN_DISPLAY TOKEN_LPAREN math_expression TOKEN_RPAREN TOKEN_SEMICOLON {  $$ = new Display($3); }
                   ;

assignment_expression : TOKEN_IDENTIFIER TOKEN_ASSIGN math_expression TOKEN_SEMICOLON { $$ = new Assigment(new Name(std::string(assing_id)), $3);}
                      ;

math_expression : math_expression TOKEN_ADD term { $$ = new Addition($1, $3); }
                | math_expression TOKEN_SUBSTRACT term { $$ = new Substraction($1, $3); }
                | term { $$ = $1; }
                ;

term : term TOKEN_MULTIPLY factor { $$ = new Multiplication($1, $3); }
     | term TOKEN_DIVIDE factor { $$ = new Division($1, $3); }
     | term TOKEN_POW factor { $$ = new Power($1, $3); }
     | factor { $$ = $1; }
     ;

factor : TOKEN_NUMBER {  $$ = new Number(strtod(yytext, NULL)); }
       | TOKEN_PI { $$ = new PI(); }
       | TOKEN_EULER { $$ = new EULER(); }
       | TOKEN_IDENTIFIER {  $$ = new Name(std::string(id)); }
       | TOKEN_LPAREN math_expression TOKEN_RPAREN { $$ = $2; }
       | pair_expression
       | vector_expression
       | matrix_expression
       | function_call
       ;

pair_expression : TOKEN_LPAREN math_expression TOKEN_COMMA math_expression TOKEN_RPAREN {   $$ = new Pair($2, $4);}
                ;

vector_expression : TOKEN_LBRACKET expression_list TOKEN_RBRACKET                       {
                                                                                            std::vector<Expression*> exprs{};
                                                                                            ExpressionList* list = dynamic_cast<ExpressionList*>($2);
                                                                                            if (list)
                                                                                            {
                                                                                                exprs = list->getVectorExpression();
                                                                                                delete $2;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                exprs.push_back($2);
                                                                                            }
                                                                                            $$ = new Vector(exprs);
                                                                                        }
                  ;

matrix_expression : TOKEN_LBRACE vector_list TOKEN_RBRACE                               {
                                                                                            std::vector<Expression*> matrix{};
                                                                                            ExpressionList* list = dynamic_cast<ExpressionList*>($2);
                                                                                            if (list)
                                                                                            {
                                                                                                for (auto expr : list->getVectorExpression())
                                                                                                {
                                                                                                    Vector* vec = dynamic_cast<Vector*>(expr);
                                                                                                    if (vec)
                                                                                                    {
                                                                                                        matrix.push_back(vec);
                                                                                                    }
                                                                                                    else
                                                                                                    {
                                                                                                        Name* name = dynamic_cast<Name*>(expr);
                                                                                                        if (name)
                                                                                                        {
                                                                                                            matrix.push_back(name);
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                            delete $2;
                                                                                            $$ = new Matrix(matrix);
                                                                                        }
                  ;

expression_list : expression_list TOKEN_COMMA math_expression                           {
                                                                                            ExpressionList* list = dynamic_cast<ExpressionList*>($1);
                                                                                            if (list)
                                                                                            {
                                                                                                list->addExpressionBack($3);
                                                                                                $$ = list;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                ExpressionList* newList = new ExpressionList();
                                                                                                newList->addExpressionBack($1);
                                                                                                newList->addExpressionBack($3);
                                                                                                $$ = newList;
                                                                                            }
                                                                                        }
                | math_expression                                                       {
                                                                                            ExpressionList* newList = new ExpressionList();
                                                                                            newList->addExpressionBack($1);
                                                                                            $$ = newList;
                                                                                        }
                ;

vector_list : vector_list TOKEN_COMMA vector_expression                                 {
                                                                                            ExpressionList* list = dynamic_cast<ExpressionList*>($1);
                                                                                            if (list)
                                                                                            {
                                                                                                list->addExpressionBack($3);
                                                                                                $$ = list;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                ExpressionList* newList = new ExpressionList();
                                                                                                newList->addExpressionBack($1);
                                                                                                newList->addExpressionBack($3);
                                                                                                $$ = newList;
                                                                                            }
                                                                                        }
            | vector_expression                                                         {
                                                                                            ExpressionList* newList = new ExpressionList();
                                                                                            newList->addExpressionBack($1);
                                                                                            $$ = newList;
                                                                                        }
            | vector_list TOKEN_COMMA TOKEN_IDENTIFIER                                  {
                                                                                            ExpressionList* list = dynamic_cast<ExpressionList*>($1);
                                                                                            if (list)
                                                                                            {
                                                                                                list->addExpressionBack(new Name(std::string(id)));
                                                                                                $$ = list;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                ExpressionList* newList = new ExpressionList();
                                                                                                newList->addExpressionBack($1);
                                                                                                newList->addExpressionBack(new Name(std::string(id)));
                                                                                                $$ = newList;
                                                                                            }
                                                                                        }
            | TOKEN_IDENTIFIER                                                          {
                                                                                            ExpressionList* newList = new ExpressionList();
                                                                                            newList->addExpressionBack(new Name(std::string(id)));
                                                                                            $$ = newList;
                                                                                        }
            ;

trigonometric_function_call: TOKEN_SIN TOKEN_LPAREN math_expression TOKEN_RPAREN { $$ = new Sine($3); }
                           | TOKEN_COS TOKEN_LPAREN math_expression TOKEN_RPAREN { $$ = new Cosine($3); }
                           | TOKEN_TAN TOKEN_LPAREN math_expression TOKEN_RPAREN { $$ = new Tangent($3); }
                           | TOKEN_CTG TOKEN_LPAREN math_expression TOKEN_RPAREN { $$ = new Cotangent($3); }
                           ;

logarithmic_function_call : TOKEN_LOG TOKEN_LPAREN math_expression TOKEN_COMMA math_expression TOKEN_RPAREN { $$ = new Logarithm($3, $5); }
                          | TOKEN_LN TOKEN_LPAREN math_expression TOKEN_RPAREN { $$ = new NaturalLogarithm($3); }
                          ;

root_function_call : TOKEN_SQRT TOKEN_LPAREN math_expression TOKEN_RPAREN { $$ = new SquareRoot($3); }
                   | TOKEN_ROOT TOKEN_LPAREN math_expression TOKEN_COMMA math_expression TOKEN_RPAREN { $$ = new Root($3, $5); }
                   ;

matrix_func_param : TOKEN_IDENTIFIER { $$ = new Name(std::string(id)); }
                  | TOKEN_LBRACE vector_list TOKEN_RBRACE { $$ = $2; }
                  ;

pair_or_id_param : pair_expression { $$ = $1; }
                 | TOKEN_IDENTIFIER { $$ = new Name(std::string(id)); }
                 ;

id_param :  TOKEN_IDENTIFIER { $$ = new Name(std::string(id)); }
         ;

integral_or_bisectionroot : TOKEN_BISECTIONROOT { $$ = new Name("BISECTIONROOT"); }
                          | TOKEN_INTEGRAL { $$ = new Name("INTEGRAL"); }
                          ;

vector_or_id_param : vector_expression { $$ = $1; }
                   | TOKEN_IDENTIFIER { $$ = new Name(std::string(id)); }
                   ;

number_or_id_param : TOKEN_NUMBER { $$ = new Number(strtod(yytext, NULL)); }
                   | TOKEN_IDENTIFIER { $$ = new Name(std::string(id)); }
                   ;

matrix_function_call : TOKEN_INVERSE TOKEN_LPAREN matrix_func_param TOKEN_RPAREN { $$ = new InverseMatrix($3); }
                     | TOKEN_MATRIXLU TOKEN_LPAREN matrix_func_param TOKEN_RPAREN { $$ = new MatrixLU($3); }
                     | TOKEN_TRIDIAGONAL TOKEN_LPAREN matrix_func_param TOKEN_RPAREN { $$ = new TridiagonalMatrix($3); }
                     | TOKEN_REALEIGENVALUES TOKEN_LPAREN matrix_func_param TOKEN_RPAREN { $$ = new RealEigenvalues($3); }
                     | TOKEN_DETERMINANT TOKEN_LPAREN matrix_func_param TOKEN_RPAREN { $$ = new Determinant($3); }
                     ;

operations_function_call : integral_or_bisectionroot TOKEN_LPAREN pair_or_id_param TOKEN_COMMA math_expression TOKEN_COMMA id_param TOKEN_RPAREN {
                                                                                                                                                            if (dynamic_cast<Name*>($1)->getName() == "BISECTIONROOT")
                                                                                                                                                            {
                                                                                                                                                                $1->destroy();
                                                                                                                                                                delete $1;
                                                                                                                                                                $$ = new FindRootBisection($3, $5, $7);
                                                                                                                                                            }
                                                                                                                                                            else
                                                                                                                                                            {
                                                                                                                                                                $1->destroy();
                                                                                                                                                                delete $1;
                                                                                                                                                                $$ = new Integral($3, $5, $7);
                                                                                                                                                            }
                                                                                                                                                        }
                         | TOKEN_INTERPOLATE TOKEN_LPAREN vector_or_id_param TOKEN_COMMA number_or_id_param TOKEN_RPAREN { $$ = new Interpolate($3, $5); }
                         | TOKEN_ODEFIRST TOKEN_LPAREN math_expression TOKEN_COMMA pair_or_id_param TOKEN_COMMA number_or_id_param TOKEN_COMMA id_param TOKEN_RPAREN {  $$ = new ODEFirstOrderInitialValues($3, $5, $7, $9);}
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