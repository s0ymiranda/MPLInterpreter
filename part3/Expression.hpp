#pragma once

#include "utils.hpp"

class Expression : public ASTNodeInterface
{
public:
    virtual std::string toString() const noexcept = 0;
    ~Expression();
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
    void destroy() noexcept override;
};

class BinaryExpression : public Expression
{
protected:
    Expression* leftExpression;
    Expression* rigthExpression;
public:
    BinaryExpression(Expression* _leftExpression, Expression* _rigthExpression);
    void destroy() noexcept override;
};

class Impossible : public Value
{
protected:
    std::string value = "IMPOSSIBLE";
public:
    Impossible();
    std::string toString() const noexcept;
};

class Number : public Value
{
protected:
    double number;
public:
    Number(double _number);
    std::string toString() const noexcept override;
    double getNumber() const;
};

class PI : public Value
{
public:
    PI();
    std::string toString() const noexcept override;
};

class EULER : public Value
{
public:
    EULER();
    std::string toString() const noexcept override;
};

class Variable : public Value
{
protected:
    char variable;
public:
    Variable(char _variable);
    std::string toString() const noexcept override;
    char getVariable() const;
};

class Addition : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;
    std::string toString() const noexcept override;
};

class Subtraction : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;
    std::string toString() const noexcept override;
};

class Multiplication : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    std::string toString() const noexcept override;
};

class Division : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    Expression* eval(Environment& env) const;
    std::string toString() const noexcept override;
};

class Power : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;
    std::string toString() const noexcept override;
};

class NaturalLogarithm : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::string toString() const noexcept override;
};

class Logarithm : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    std::string toString() const noexcept override;
};

class SquareRoot : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::string toString() const noexcept override;
};

class Root : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    std::string toString() const noexcept override;
};

class Sine : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::string toString() const noexcept override;
};

class Cosine : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::string toString() const noexcept override;
};

class Tangent : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::string toString() const noexcept override;
};

class Cotangent : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::string toString() const noexcept override;
};

class Pair : public Value
{
private:
    Expression* first;
    Expression* second;
public:
    Pair(Expression* _first, Expression* _second);
    std::string toString() const noexcept override;
    Expression* getFirst();
    Expression* getSecond();
    void destroy() noexcept override;
};

class PairFirst : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::string toString() const noexcept override;
};

class PairSecond : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::string toString() const noexcept override;
};

class Vector : public Value
{
protected:
    std::vector<Expression*> vectorExpression;
public:
    Vector(std::vector<Expression*> _vectorExpression);
    std::string toString() const noexcept override;
    std::vector<Expression*> getVectorExpression() const;
    void destroy() noexcept override;
};

class Matrix : public Value
{
protected:
    std::vector<std::vector<Expression*>> matrixExpression;
public:
    Matrix(std::vector<std::vector<Expression*>> _matrixExpression);
    std::string toString() const noexcept override;
    std::vector<std::vector<Expression*>> getMatrixExpression() const;
    void destroy() noexcept override;
};

class InverseMatrix : public Value
{
private:
    Matrix* matrix;
    Expression* gauss(std::vector<std::vector<Expression*>> matrix) const;
public:
    InverseMatrix(Matrix* _matrix);
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};

class MatrixLU : public Value
{
private:
    Matrix* matrix;
    std::pair<std::vector<std::vector<Expression*>>, std::vector<std::vector<Expression*>>> lowerUpperDecomposition(std::vector<std::vector<Expression*>> matrix) const;
public:
    MatrixLU(Matrix* _matrix);
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};

class TridiagonalMatrix : public Value
{
private:
    Matrix* matrix;
public:
    TridiagonalMatrix(Matrix* _matrix);
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};
class RealEigenvalues : public Value
{
private:
    Matrix* matrix;
public:
    RealEigenvalues(Matrix* _matrix);
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};
class Determinant : public Value
{
private:
    Matrix* matrix;
public:
    Determinant(Matrix* _matrix);
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};

class Function : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::string toString() const noexcept override;
};

class Integral : public Expression // Resolution by Simpson Method
{
private:
    Pair* interval;
    Function* function;
    Variable* variable;
public:
    Integral(Pair* _interval, Function* _function, Variable* _variable);
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};

class Interpolate : public Vector // Resolution by Lagrange
{
private:
    Number* numInter;
public:
    Interpolate(std::vector<Expression*> _vectorExpression, Number* _numInter);
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};

class ODEFirstOrderInitialValues : public Expression
{
private:
    Function* funct;
    Pair* initialValue;
    Number* tFinal;
    Variable* variable;
public:
    ODEFirstOrderInitialValues(Function* _funct, Pair* _initialValue, Number* _tFinal, Variable* _variable);
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};

class FindRootBisection : public Expression
{
private:
    Pair* interval;
    Function* function;
    Variable* variable;
    Number* iterationLimit;
public:
    FindRootBisection(Pair* _interval, Function* _function, Variable* _variable, Number* _iterationLimit = new Number(100));
    std::string toString() const noexcept override;
    void destroy() noexcept override;
};

class Name : public Value
{
private:
    std::string name;
public:
    Name(std::string_view _name);
    std::string toString() const noexcept override;
    std::string getName() const noexcept;
};