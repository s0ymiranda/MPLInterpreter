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
        std::unique_ptr<Expression> test(exs->eval(env));
        printf("%s", test->toString().c_str());
        // for (auto &t : env)
        // {
        //     if (t.second != nullptr)
        //     {
        //         std::cout << t.second->toString() << std::endl;
        //     }
        //     // if (t.first == "vec1" || t.first == "vec2")
        //     //     std::cout << t.second->toString() << std::endl;
        // }


        // auto it = env.begin();
        // std::cout << (*it).first <<": "<< (*it).second->toString() << std::endl;
        // ++it;
        // std::cout << (*it).first <<": " << (dynamic_cast<Vector*>((*it).second))->toString() << std::endl;
        // ++it;
        // std::cout << (*it).first <<": " <<(*it).second->toString() << std::endl;
        // ++it;
        // std::cout << (*it).first <<": " <<(*it).second->toString() << std::endl;
        // ++it;
        // std::cout << (*it).first <<": " <<(*it).second->toString() << std::endl;

        test->destroy();
        exs->destroy();
        for (auto& t : env)
        {
            t.second->destroy();
            delete t.second;
            t.second = nullptr;
        }


        // std::vector<Expression*> vt1;
        // vt1.push_back(new Addition(new Number(2), new Number(3)));
        // vt1.push_back(new Number(4));

        // std::vector<Expression*> vt2;
        // vt2.push_back(new Number(6));
        // vt2.push_back(new Number(8));
        // auto v1 = new Vector(vt1);
        // auto v2 = new Vector(vt2);

        // std::vector<Expression*> vt3;
        // vt3.push_back(v1);
        // vt3.push_back(v2);
        // auto m = new Matrix(vt3);

        // auto m2 = m->eval(env);

        // std::cout << m2->toString() << std::endl;
    }
    else
    {
        printf("Parse failed!\n");
    }
    return 0;
}