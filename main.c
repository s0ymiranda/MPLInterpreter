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
        printf("%s", parser_result->toString().c_str());
    }
    else
    {
        printf("Parse failed!\n");
    }
    return 0;
}