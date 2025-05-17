#pragma once

#include "utils.hpp"

class Expression
{
public:
    virtual Expression* eval(Environment&) const = 0;
    virtual std::string toString() const noexcept = 0;
    virtual void destroy() noexcept = 0;
    virtual ~Expression();
};

class Unit : public Expression
{
public:
    Unit();
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};

class Value : public Expression
{
protected:
    DataType dataType;
public:
    Value(DataType _dataType);
    void destroy() noexcept override;
    DataType getDataType() const;
};

class UnaryExpression : public Expression
{
protected:
    Expression* expression;
public:
    UnaryExpression(Expression* exp);
    Expression* getExpression()
    {
        return expression;
    }
    void destroy() noexcept override;
};

class BinaryExpression : public Expression
{
protected:
    Expression* leftExpression;
    Expression* rightExpression;
public:
    BinaryExpression(Expression* _leftExpression, Expression* _rightExpression);
    Expression* getLeftExpression()
    {
        return leftExpression;
    }
    Expression* getRightExpression()
    {
        return leftExpression;
    }
    void destroy() noexcept override;
};

class Impossible : public Value
{
private:
    std::string message;
public:
    Impossible(std::string msg = "");
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Invalid : public Value
{
private:
    std::string message;
public:
    Invalid(const std::string& msg = "");
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Number : public Value
{
protected:
    double number;
public:
    Number(double _number);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    double getNumber() const;
};

class PI : public Value
{
public:
    PI();
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class EULER : public Value
{
public:
    EULER();
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Name : public Value
{
private:
    std::string name;
public:
    Name(std::string_view _name);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    std::string getName() const noexcept;
};

class Negation : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Addition : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Substraction : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Multiplication : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Division : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    Expression* eval(Environment& env) const;
    std::string toString() const noexcept override;
};

class Power : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class NaturalLogarithm : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Logarithm : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class SquareRoot : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Root : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Sine : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Cosine : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Tangent : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Cotangent : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Pair : public Value
{
private:
    Expression* first;
    Expression* second;
public:
    Pair(Expression* _first, Expression* _second);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    Expression* getFirst();
    Expression* getSecond();
    void destroy() noexcept override;
};

class PairFirst : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class PairSecond : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Vector : public Value
{
protected:
    std::vector<Expression*> vectorExpression;
public:
    Vector(std::vector<Expression*>& _vectorExpression);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    std::vector<Expression*> getVectorExpression() const;
    size_t size()
    {
        return vectorExpression.size();
    }
    void destroy() noexcept override;
};

class Matrix : public Value
{
protected:
    std::vector<Expression*> matrixExpression;
public:
    Matrix(std::vector<Expression*>& _matrixExpression);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    std::vector<Expression*> getMatrixExpression() const;
    size_t size()
    {
        return matrixExpression.size();
    }
    void destroy() noexcept override;
};

class InverseMatrix : public Value
{
private:
    Expression* matrix;
    Expression* gauss(std::vector<std::vector<Expression*>>) const;
public:
    InverseMatrix(Expression* _matrix);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};

class MatrixLU : public Value
{
private:
    Expression* matrix;
    Expression* lowerUpperDecomposition(std::vector<std::vector<Expression*>> matrixExpression) const;
public:
    MatrixLU(Expression* _matrix);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};

class TridiagonalMatrix : public Value
{
private:
    Expression* matrix;
    Expression* tridiagonal(std::vector<std::vector<Expression*>> matrix) const;
public:
    TridiagonalMatrix(Expression* _matrix);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};
class RealEigenvalues : public Value
{
private:
    Expression* matrix;
    void determ(std::vector<double> auxialiaryVector, std::vector<std::vector<double>> answerMatrix, double x, double& middle, size_t l) const;
    void bisec(std::vector<double> auxialiaryVector, std::vector<std::vector<double>> answerMatrix, double startInterval, double endInterval, double& middlePoint, size_t l) const;
    Expression* eigenvalues(std::vector<std::vector<Expression*>> matrix) const;
public:
    RealEigenvalues(Expression* _matrix);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};
class Determinant : public Value
{
private:
    Expression* matrix;
public:
    Determinant(Expression* _matrix);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};

class Function : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Integral : public Expression
{
private:
    Expression* interval;
    Expression* function;
    Expression* variable;
    Expression* simpsonMethod(double a, double b, int n, Expression* function, Environment& env, Name* variable) const;
public:
    Integral(Expression* _interval, Expression* _function, Expression* _variable);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    std::tuple<Expression*, Expression*, Expression*> getExpressions() const noexcept;
    void destroy() noexcept override;
};

class Interpolate : public Expression
{
private:
    Expression* vectorExpression;
    Expression* numInter;
public:
    Interpolate(Expression* _vectorExpression, Expression* _numInter);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    std::tuple<Expression*, Expression*> getExpressions() const noexcept;
    void destroy() noexcept override;
};

class ODEFirstOrderInitialValues : public Expression
{
private:
    Expression* funct;
    Expression* initialValue;
    Expression* tFinal;
    Expression* variable;
    Expression* rungekuttaMethod(double t, double x, double f, double h, Expression* function, Environment& env, Name* variable) const;
public:
    ODEFirstOrderInitialValues(Expression* _funct, Expression* _initialValue, Expression* _tFinal, Expression* _variable);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    std::tuple<Expression*, Expression*, Expression*, Expression*> getExpressions() const noexcept;
    void destroy() noexcept override;
};

class FindRootBisection : public Expression
{
private:
    Expression* interval;
    Expression* function;
    Expression* variable;
    Expression* iterationLimit;
    Expression* bisectionMethod(Number* left, Number* right, Expression* function, Environment& env, Name* _variable, Number* _iterationLimit) const;
public:
    FindRootBisection(Expression* _interval, Expression* _function, Expression* _variable, Expression* _iterationLimit = new Number(100));
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    std::tuple<Expression*, Expression*, Expression*, Expression*> getExpressions() const noexcept;
    void destroy() noexcept override;
};


class Display : public Expression
{
private:
    Expression* expression;
public:
    Display(Expression* _expression);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};

class Print : public Expression
{
private:
    std::string message;
public:
    Print(std::string _message);
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};

class Assigment : public BinaryExpression
{
private:
    bool containsName(Expression* expr, const std::string& varName, Environment& env) const noexcept;
public:
    using BinaryExpression::BinaryExpression;
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class ExpressionList : public Expression
{
private:
    std::list<Expression*> expressions;
    size_t sz;
public:
    ExpressionList();
    Expression* eval(Environment& env) const override;
    std::string toString() const noexcept override;
    void addExpressionFront(Expression* expr);
    void addExpressionBack(Expression* expr);
    std::vector<Expression*> getVectorExpression() const;
    void destroy() noexcept override;
    size_t size() const noexcept {return sz;}
};