#pragma once

#include "Expression.hpp"

class Statement : public ASTNodeInterface
{
public:
    virtual void execute() const = 0;
    virtual ~Statement() {}
};

class Display : public Statement
{
public:
    Display(Expression*);
    void execute() const override;
    void destroy() noexcept override;
private:
    Expression* exp;
};

class Print :public Statement
{
public:
    Print(std::string);
    void execute() const override;
private:
    std::string str;
};

class NameDeclaration : public ASTNodeInterface
{
public:
    NameDeclaration(std::string_view _name, Expression* _expression);
    void destroy() noexcept;

private:
    std::string name;
    Expression* expression;
};