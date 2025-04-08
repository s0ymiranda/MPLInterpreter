#include <stdio.h>
#include <stdlib.h>
#include <Expression.hpp>

extern FILE* yyin;
extern int yyparse();
extern Expression* parser_result;

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
        printf("Parse successful! AST: \n");
        printf("====================== \n");
        auto env = Environment();
        auto exs = dynamic_cast<ExpressionList*>(parser_result);
        printf("List size: %lu\n", exs->size());

        // auto t = new Number(2);
        // auto t2 = new Number(5);

        // std::cout << t->eval(env)->toString() << std::endl;
        // std::cout << t2->eval(env)->toString() << std::endl;

        // auto add = new Addition(t, t2);
        // std::cout << add->eval(env)->toString() << std::endl;
        //exs->eval(env);
        auto test = exs->eval(env);
        printf("%s", test->toString().c_str());
        //printf("%s", exs->eval(env)->toString().c_str());
        test->destroy();
        exs->destroy();
        parser_result->destroy();
    }
    else
    {
        printf("Parse failed!\n");
    }
    return 0;
}