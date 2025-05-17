#include <stdio.h>
#include <stdlib.h>
#include <Expression.hpp>

#include <unordered_set>

extern FILE* yyin;
extern int yyparse();
extern Expression* parser_result;
extern std::unordered_set<Expression*> pointers;

void usage(char* argv[])
{
    printf("Usage: %s input_file\n", argv[0]);
    exit(1);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        usage(argv);
    }

    yyin = fopen(argv[1], "r");

    if (!yyin)
    {
        printf("Could not open %s\n", argv[1]);
        exit(1);
    }

    int result = yyparse();

    if (result == 0)
    {
        auto env = Environment();
        auto exs = dynamic_cast<ExpressionList*>(parser_result);
        std::unique_ptr<Expression> res(exs->eval(env));
        printf("%s", res->toString().c_str());
        res->destroy();
        exs->destroy();
        for (auto& t : env)
        {
            if (t.second != nullptr)
            {
                t.second->destroy();
                delete t.second;
                t.second = nullptr;
            }
        }
    }
    else
    {
        printf("Parse failed!\n");

        for (Expression* expr : pointers)
        {
            if (expr != nullptr)
            {
                delete expr;
                expr = nullptr;
            }
        }

        pointers.clear();
    }

    return 0;
}