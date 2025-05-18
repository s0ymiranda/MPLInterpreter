#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <forward_list>
#include <memory>
#include <unordered_set>
#include <Expression.hpp>

#define Function ReadlineFunctionWrapper
#include <readline/readline.h>
#include <readline/history.h>
#undef Function

extern FILE* yyin;
extern int yyparse();
extern Expression* parser_result;
extern void yyrestart(FILE* input);
extern int yylex_destroy();
extern std::unordered_set<Expression*> pointers;

const std::string GREEN = "\e[32m";
const std::string RED = "\e[31m";
const std::string GREEN_BOLD = "\e[1;92m";
const std::string RED_BOLD = "\e[1;91m";
const std::string COLOR_OFF = "\e[0m";

static Environment* current_env = nullptr;
static const std::vector<std::string> keywords = {
    "print", "display",
    "+", "-", "*", "/", "^",
    "LOG", "LN", "SQRT", "ROOT",
    "SIN", "COS", "TAN", "CTG", "INVERSE",
    "MATRIXLU", "TRIDIAGONAL", "REALEIGENVALUES", "DETERMINANT",
    "BISECTIONROOT", "INTEGRAL", "ODEFIRST", "INTERPOLATE",
    "PI", "EULER",
    "(", ")", "[", "]", "{", "}", ",", ";", "=",
    "exit"
};

char* words_generator(const char* text, int state)
{
    static int list_index, len;
    static std::vector<std::string> variables;

    if (!state)
    {
        list_index = 0;
        len = strlen(text);

        variables.clear();
        if (current_env)
        {
            for (const auto& pair : *current_env)
            {
                variables.push_back(pair.first);
            }
        }
    }

    if (list_index < keywords.size())
    {
        while (list_index < keywords.size())
        {
            const std::string& keyword = keywords[list_index];
            ++list_index;

            if (keyword.compare(0, len, text) == 0)
            {
                return strdup(keyword.c_str());
            }
        }
    }

    while ((list_index - keywords.size()) < variables.size())
    {
        const std::string& var = variables[list_index - keywords.size()];
        ++list_index;

        if (var.compare(0, len, text) == 0)
        {
            return strdup(var.c_str());
        }
    }

    return nullptr;
}

char** completion(const char* text, int start, int end)
{
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, words_generator);
}

std::string get_input_prompt(size_t i)
{
    return GREEN + std::string("Input [") + GREEN_BOLD + std::to_string(i) + GREEN + "]:" + COLOR_OFF + " ";
}

std::string get_output_prompt(size_t i)
{
    return RED + std::string("Output[") + RED_BOLD + std::to_string(i) + RED + "]:" + COLOR_OFF + " ";
}

std::string get_error_prompt(const std::string& error_type)
{
    return RED +
        std::string("-------------------------------------------------------------------------------\n") +
        error_type + COLOR_OFF + ": ";
}

std::string_view trim(std::string_view str)
{
    size_t start = 0;
    size_t end = str.size();

    while (start < end && std::isspace(str[start]))
    {
        ++start;
    }

    while (end > start && std::isspace(str[end - 1]))
    {
        --end;
    }

    return str.substr(start, end - start);
}

int main() {
    std::cout << "Interactive Interpreter for Mathematical Programming Language\n"
              << "Type 'exit' to quit or press Ctrl+D\n\n";

    rl_attempted_completion_function = completion;

    Environment env;
    current_env = &env;

    size_t counter = 1;

    while (true)
    {
        std::string prompt = get_input_prompt(counter);
        char* line = readline(prompt.c_str());

        if (line == nullptr)
        {
            break; // Ctrl+D pressed
        }

        std::string prog = line;
        free(line);

        if (trim(prog) == "exit")
        {
            break;
        }

        if (prog.empty())
        {
            continue;
        }

        yyin = fmemopen((void*)prog.c_str(), prog.size(), "r");
        if (!yyin)
        {
            std::cerr << get_error_prompt("Internal error") << "Failed to create memory stream\n\n";
            continue;
        }

        int result = yyparse();
        fclose(yyin);
        yyin = nullptr;

        if (result == 0)
        {
            try
            {
                auto exs = dynamic_cast<ExpressionList*>(parser_result);
                if (exs)
                {
                    std::unique_ptr<Expression> res(exs->eval(env));
                    std::cout << get_output_prompt(counter) << res->toString() << "\n\n";
                    res->destroy();
                }
                else
                {
                    std::cerr << get_error_prompt("Evaluation error") << "Expected ExpressionList\n\n";
                }

                add_history(prog.c_str());
                ++counter;
            }
            catch (const std::exception& e)
            {
                std::cerr << get_error_prompt("Runtime error") << e.what() << "\n\n";
            }

            if (parser_result)
            {
                parser_result->destroy();
                delete parser_result;
                parser_result = nullptr;
            }
        }
        else
        {
            std::cerr << get_error_prompt("Parse error") << "Invalid syntax\n\n";
            if (parser_result)
            {
                parser_result->destroy();
                delete parser_result;
                parser_result = nullptr;
            }

            for (Expression* expr : pointers)
            {
                if (expr != nullptr)
                {
                    delete expr;
                    expr = nullptr;
                }
            }

            yyrestart(nullptr);
            yylex_destroy();
        }

        pointers.clear();
    }

    for (auto& t : env)
    {
        if (t.second != nullptr)
        {
            t.second->destroy();
            delete t.second;
            t.second = nullptr;
        }
    }

    current_env = nullptr;

    return EXIT_SUCCESS;
}