#include "Statement.hpp"

Display::Display(Expression* _exp) : exp(_exp) {}

void Display::execute() const
{
    if(exp == nullptr)
    {
        std::cout << "NULLPTR" << std::endl;
    }
    else
    {
        std::cout << exp->toString() << std::endl;
    }
}

void Display::destroy() noexcept
{
    if (exp == nullptr)
    {
        exp->destroy();
        delete exp;
    }
}

Print::Print(std::string _str) : str(_str) {}

void Print::execute() const
{
    std::cout << str;
}

NameDeclaration::NameDeclaration(std::string_view _name, Expression* _expression) : name(_name), expression(_expression) {}

void NameDeclaration::destroy() noexcept
{
    if (expression)
    {
        expression->destroy();
        delete expression;
    }
}