%{
#include <stdio.h>
#include <stdlib.h>
#include <unordered_set>
#include <Expression.hpp>

#define YYSTYPE Expression*

extern int yylex();
int yyerror(const char*);
extern char* yytext;
extern char* id;
extern char* assing_id;
extern char assing_variable;
Expression* parser_result{nullptr};
std::unordered_set<Expression*> pointers;
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

program : expressions_list                                          { parser_result = $1; }
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
                                                                            pointers.emplace(newList);
                                                                            $$ = newList;
                                                                        }
                                                                    }
                 | expression                                       {
                                                                        ExpressionList* newList = new ExpressionList();
                                                                        newList->addExpressionFront($1);
                                                                        pointers.emplace(newList);
                                                                        $$ = newList;
                                                                    }
                 ;

expression : print_expression
           | display_expression
           | assignment_expression
           | math_expression TOKEN_SEMICOLON                        { $$ = $1; }
           ;

print_expression : TOKEN_PRINT TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_SEMICOLON   {
                                                                                                Expression* e = new Print(std::string(id));
                                                                                                pointers.emplace(e);
                                                                                                $$ = e;
                                                                                            }
                 ;

display_expression : TOKEN_DISPLAY TOKEN_LPAREN math_expression TOKEN_RPAREN TOKEN_SEMICOLON {
                                                                                                Expression* e = new Display($3);
                                                                                                pointers.emplace(e);
                                                                                                $$ = e;
                                                                                             }
                   ;

assignment_expression : TOKEN_IDENTIFIER TOKEN_ASSIGN math_expression TOKEN_SEMICOLON {
                                                                                        Expression* name = new Name(std::string(assing_id));
                                                                                        Expression* e = new Assigment(name, $3);
                                                                                        pointers.emplace(name);
                                                                                        pointers.emplace(e);
                                                                                        $$ = e;
                                                                                      }
                      ;

math_expression : math_expression TOKEN_ADD term {
                                                   Expression* e = new Addition($1, $3);
                                                   pointers.emplace(e);
                                                   $$ = e;
                                                 }
                | math_expression TOKEN_SUBSTRACT term {
                                                         Expression* e = new Substraction($1, $3);
                                                         pointers.emplace(e);
                                                         $$ = e;
                                                       }
                | term { $$ = $1; }
                ;

term : term TOKEN_MULTIPLY factor {
                                    Expression* e = new Multiplication($1, $3);
                                    pointers.emplace(e);
                                    $$ = e;
                                  }
     | term TOKEN_DIVIDE factor {
                                    Expression* e = new Division($1, $3);
                                    pointers.emplace(e);
                                    $$ = e;
                                }
     | factor { $$ = $1; }
     ;

factor : TOKEN_SUBSTRACT factor {
                                    Expression* e = new Negation($2);
                                    pointers.emplace(e);
                                    $$ = e;
                                }
       | power_or_primary { $$ = $1; }
       ;

power_or_primary : primary TOKEN_POW power_or_primary {
                                                        Expression* e = new Power($1, $3);
                                                        pointers.emplace(e);
                                                        $$ = e;
                                                      }
      | primary { $$ = $1; }
      ;

primary : TOKEN_NUMBER {
                            Expression* e = new Number(strtod(yytext, NULL));
                            pointers.emplace(e);
                            $$ = e;
                        }
        | TOKEN_PI {
                        Expression* e = new PI();
                        pointers.emplace(e);
                        $$ = e;
                    }
        | TOKEN_EULER {
                            Expression* e = new EULER();
                            pointers.emplace(e);
                            $$ = e;
                      }
        | TOKEN_IDENTIFIER {
                                Expression* e = new Name(std::string(id));
                                pointers.emplace(e);
                                $$ = e;
                            }
        | TOKEN_LPAREN math_expression TOKEN_RPAREN { $$ = $2; }
        | pair_expression
        | vector_expression
        | matrix_expression
        | function_call
        ;

pair_expression : TOKEN_LPAREN math_expression TOKEN_COMMA math_expression TOKEN_RPAREN {
                                                                                            Expression* e = new Pair($2, $4);
                                                                                            pointers.emplace(e);
                                                                                            $$ = e;
                                                                                        }
                ;

vector_expression : TOKEN_LBRACKET expression_list TOKEN_RBRACKET                       {
                                                                                            std::vector<Expression*> exprs{};
                                                                                            ExpressionList* list = dynamic_cast<ExpressionList*>($2);
                                                                                            if (list)
                                                                                            {
                                                                                                exprs = list->getVectorExpression();
                                                                                                if (pointers.find($2) != pointers.end())
                                                                                                {
                                                                                                    pointers.erase($2);
                                                                                                }
                                                                                                delete $2;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                exprs.push_back($2);
                                                                                            }
                                                                                            Expression* e = new Vector(exprs);
                                                                                            pointers.emplace(e);
                                                                                            $$ = e;
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
                                                                                            if (pointers.find($2) != pointers.end())
                                                                                            {
                                                                                                pointers.erase($2);
                                                                                            }
                                                                                            delete $2;
                                                                                            Expression* e = new Matrix(matrix);
                                                                                            pointers.emplace(e);
                                                                                            $$ = e;
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
                                                                                                Expression* e = newList;
                                                                                                pointers.emplace(e);
                                                                                                $$ = e;
                                                                                            }
                                                                                        }
                | math_expression                                                       {
                                                                                            ExpressionList* newList = new ExpressionList();
                                                                                            newList->addExpressionBack($1);
                                                                                            Expression* e = newList;
                                                                                            pointers.emplace(e);
                                                                                            $$ = e;
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
                                                                                                Expression* e = newList;
                                                                                                pointers.emplace(e);
                                                                                                $$ = e;
                                                                                            }
                                                                                        }
            | vector_expression                                                         {
                                                                                            ExpressionList* newList = new ExpressionList();
                                                                                            newList->addExpressionBack($1);
                                                                                            Expression* e = newList;
                                                                                            pointers.emplace(e);
                                                                                            $$ = e;
                                                                                        }
            | vector_list TOKEN_COMMA TOKEN_IDENTIFIER                                  {
                                                                                            ExpressionList* list = dynamic_cast<ExpressionList*>($1);
                                                                                            if (list)
                                                                                            {
                                                                                                Expression* name = new Name(std::string(id));
                                                                                                list->addExpressionBack(name);
                                                                                                pointers.emplace(name);
                                                                                                $$ = list;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                ExpressionList* newList = new ExpressionList();
                                                                                                newList->addExpressionBack($1);
                                                                                                Expression* name = new Name(std::string(id));
                                                                                                newList->addExpressionBack(name);
                                                                                                pointers.emplace(name);
                                                                                                pointers.emplace(newList);
                                                                                                $$ = newList;
                                                                                            }
                                                                                        }
            | TOKEN_IDENTIFIER                                                          {
                                                                                            ExpressionList* newList = new ExpressionList();
                                                                                            Expression* name = new Name(std::string(id));
                                                                                            newList->addExpressionBack(name);
                                                                                            pointers.emplace(name);
                                                                                            pointers.emplace(newList);
                                                                                            $$ = newList;
                                                                                        }
            ;

trigonometric_function_call: TOKEN_SIN TOKEN_LPAREN math_expression TOKEN_RPAREN {
                                                                                    Expression* e = new Sine($3);
                                                                                    pointers.emplace(e);
                                                                                    $$ = e;
                                                                                }
                           | TOKEN_COS TOKEN_LPAREN math_expression TOKEN_RPAREN {
                                                                                    Expression* e = new Cosine($3);
                                                                                    pointers.emplace(e);
                                                                                    $$ = e;
                                                                                 }
                           | TOKEN_TAN TOKEN_LPAREN math_expression TOKEN_RPAREN {
                                                                                    Expression* e = new Tangent($3);
                                                                                    pointers.emplace(e);
                                                                                    $$ = e;
                                                                                 }
                           | TOKEN_CTG TOKEN_LPAREN math_expression TOKEN_RPAREN {
                                                                                    Expression* e = new Cotangent($3);
                                                                                    pointers.emplace(e);
                                                                                    $$ = e;
                                                                                 }
                           ;

logarithmic_function_call : TOKEN_LOG TOKEN_LPAREN math_expression TOKEN_COMMA math_expression TOKEN_RPAREN {
                                                                                                                Expression* e = new Logarithm($3, $5);
                                                                                                                pointers.emplace(e);
                                                                                                                $$ = e;
                                                                                                            }
                          | TOKEN_LN TOKEN_LPAREN math_expression TOKEN_RPAREN {
                                                                                    Expression* e = new NaturalLogarithm($3);
                                                                                    pointers.emplace(e);
                                                                                    $$ = e;
                                                                               }
                          ;

root_function_call : TOKEN_SQRT TOKEN_LPAREN math_expression TOKEN_RPAREN {
                                                                                Expression* e = new SquareRoot($3);
                                                                                pointers.emplace(e);
                                                                                $$ = e;
                                                                          }
                   | TOKEN_ROOT TOKEN_LPAREN math_expression TOKEN_COMMA math_expression TOKEN_RPAREN {
                                                                                                            Expression* e = new Root($3, $5);
                                                                                                            pointers.emplace(e);
                                                                                                            $$ = e;
                                                                                                      }
                   ;

matrix_func_param : TOKEN_IDENTIFIER {
                                        Expression* e = new Name(std::string(id));
                                        pointers.emplace(e);
                                        $$ = e;
                                    }
                  | TOKEN_LBRACE vector_list TOKEN_RBRACE { $$ = $2; }
                  ;

pair_or_id_param : pair_expression { $$ = $1; }
                 | TOKEN_IDENTIFIER {
                                        Expression* e = new Name(std::string(id));
                                        pointers.emplace(e);
                                        $$ = e;
                                    }
                 ;

id_param :  TOKEN_IDENTIFIER {
                                Expression* e = new Name(std::string(id));
                                pointers.emplace(e);
                                $$ = e;
                             }
         ;

integral_or_bisectionroot : TOKEN_BISECTIONROOT {
                                                    Expression* e = new Name("BISECTIONROOT");
                                                    pointers.emplace(e);
                                                    $$ = e;
                                                }
                          | TOKEN_INTEGRAL {
                                                Expression* e = new Name("INTEGRAL");
                                                pointers.emplace(e);
                                                $$ = e;
                                           }
                          ;

vector_or_id_param : vector_expression { $$ = $1; }
                   | TOKEN_IDENTIFIER {
                                        Expression* e = new Name(std::string(id));
                                        pointers.emplace(e);
                                        $$ = e;
                                      }
                   ;

matrix_function_call : TOKEN_INVERSE TOKEN_LPAREN matrix_func_param TOKEN_RPAREN {
                                                                                    Expression* e = new InverseMatrix($3);
                                                                                    pointers.emplace(e);
                                                                                    $$ = e;
                                                                                 }
                     | TOKEN_MATRIXLU TOKEN_LPAREN matrix_func_param TOKEN_RPAREN {
                                                                                    Expression* e = new MatrixLU($3);
                                                                                    pointers.emplace(e);
                                                                                    $$ = e;
                                                                                  }
                     | TOKEN_TRIDIAGONAL TOKEN_LPAREN matrix_func_param TOKEN_RPAREN {
                                                                                        Expression* e = new TridiagonalMatrix($3);
                                                                                        pointers.emplace(e);
                                                                                        $$ = e;
                                                                                     }
                     | TOKEN_REALEIGENVALUES TOKEN_LPAREN matrix_func_param TOKEN_RPAREN {
                                                                                            Expression* e = new RealEigenvalues($3);
                                                                                            pointers.emplace(e);
                                                                                            $$ = e;
                                                                                         }
                     | TOKEN_DETERMINANT TOKEN_LPAREN matrix_func_param TOKEN_RPAREN {
                                                                                        Expression* e = new Determinant($3);
                                                                                        pointers.emplace(e);
                                                                                        $$ = e;
                                                                                     }
                     ;

operations_function_call : integral_or_bisectionroot TOKEN_LPAREN pair_or_id_param TOKEN_COMMA math_expression TOKEN_COMMA id_param TOKEN_RPAREN {
                                                                                                                                                            if (dynamic_cast<Name*>($1)->getName() == "BISECTIONROOT")
                                                                                                                                                            {
                                                                                                                                                                if (pointers.find($1) != pointers.end())
                                                                                                                                                                {
                                                                                                                                                                    pointers.erase($1);
                                                                                                                                                                }
                                                                                                                                                                //$1->destroy();
                                                                                                                                                                delete $1;
                                                                                                                                                                Expression* e = new FindRootBisection($3, $5, $7);
                                                                                                                                                                pointers.emplace(e);
                                                                                                                                                                $$ = e;
                                                                                                                                                            }
                                                                                                                                                            else
                                                                                                                                                            {
                                                                                                                                                                if (pointers.find($1) != pointers.end())
                                                                                                                                                                {
                                                                                                                                                                    pointers.erase($1);
                                                                                                                                                                }
                                                                                                                                                                //$1->destroy();
                                                                                                                                                                delete $1;
                                                                                                                                                                Expression* e = new Integral($3, $5, $7);
                                                                                                                                                                pointers.emplace(e);
                                                                                                                                                                $$ = e;
                                                                                                                                                            }
                                                                                                                                                        }
                         | TOKEN_INTERPOLATE TOKEN_LPAREN vector_or_id_param TOKEN_COMMA math_expression TOKEN_RPAREN {
                                                                                                                            Expression* e = new Interpolate($3, $5);
                                                                                                                            pointers.emplace(e);
                                                                                                                            $$ = e;
                                                                                                                      }
                         | TOKEN_ODEFIRST TOKEN_LPAREN math_expression TOKEN_COMMA pair_or_id_param TOKEN_COMMA math_expression TOKEN_COMMA id_param TOKEN_RPAREN {
                                                                                                                                                                        Expression* e = new ODEFirstOrderInitialValues($3, $5, $7, $9);
                                                                                                                                                                        pointers.emplace(e);
                                                                                                                                                                        $$ = e;
                                                                                                                                                                  }
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

    for (Expression* expr : pointers)
    {
        if (expr != nullptr)
        {
            delete expr;
            expr = nullptr;
        }
    }

    pointers.clear();

    return 1;
}
