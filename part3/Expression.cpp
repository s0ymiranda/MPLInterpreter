#include "Expression.hpp"

Expression::~Expression() {}
// Value
Value::Value(DataType _dataType) : dataType{_dataType} {}
DataType Value::getDataType() const
{
    return dataType;
}
void Value::destroy() noexcept {}

// Unary Expression
UnaryExpression::UnaryExpression(Expression* _expression) : expression(_expression) {}
void UnaryExpression::destroy() noexcept
{
    if (expression != nullptr)
    {
        expression->destroy();
        delete expression;
    }
}
// Binary Expression
BinaryExpression::BinaryExpression(Expression* _leftExpression, Expression* _rigthExpression) : leftExpression(_leftExpression), rigthExpression(_rigthExpression) {}
void BinaryExpression::destroy() noexcept
{
    if (leftExpression != nullptr)
    {
        leftExpression->destroy();
        delete leftExpression;
    }
    if (rigthExpression != nullptr)
    {
        rigthExpression->destroy();
        delete rigthExpression;
    }
}
//Impossible
Impossible::Impossible() : Value(DataType::Impossible) {}

std::string Impossible::toString() const noexcept
{
    return value;
}
// Number
Number::Number(double _number) : Value(DataType::Number), number{_number} {}

std::string Number::toString() const noexcept
{
    return std::to_string(number);
}
double Number::getNumber() const
{
    return number;
}

// Constants
PI::PI() : Value(DataType::Number) {}
std::string PI::toString() const noexcept
{
    return "π";
}
EULER::EULER() : Value(DataType::Number){}
std::string EULER::toString() const noexcept
{
    return "e";
}
// Variable
Variable::Variable(char _variable) : Value(DataType::Variable), variable{_variable} {}

std::string Variable::toString() const noexcept
{
    return std::string{variable};
}
char Variable::getVariable() const
{
    return variable;
}

//Name
Name::Name(std::string_view _name) : Value(DataType::Name), name(_name) {}
std::string Name::toString() const noexcept
{
    return name;
}
std::string Name::getName() const noexcept
{
    return name;
}

// Addition
std::string Addition::toString() const noexcept
{
    return leftExpression->toString() + " + " + rigthExpression->toString();
}

//Subtraction

std::string Subtraction::toString() const noexcept
{
    return leftExpression->toString() + " - " + rigthExpression->toString();
}

//Multiplication

std::string Multiplication::toString() const noexcept
{
    return "("+ leftExpression->toString()+ ") * (" + rigthExpression->toString() +")";
}

//Division

std::string Division::toString() const noexcept
{
    return "(" + leftExpression->toString() + ")/(" + rigthExpression->toString() + ")";
}

//Power

std::string Power::toString() const noexcept
{
    return "("+ leftExpression->toString() + ")^(" + rigthExpression->toString() + ")";
}

//NaturalLogarithm

std::string NaturalLogarithm::toString() const noexcept
{
    return "ln(" + expression->toString() + ")";
}

//Logarithm

std::string Logarithm::toString() const noexcept
{
    return "lg" + leftExpression->toString() + "(" + rigthExpression->toString() + ")";
}

// Square Root

std::string SquareRoot::toString() const noexcept
{
    return "√(" + expression->toString() + ")";
}

// Root

std::string Root::toString() const noexcept
{
    return "(" + rigthExpression->toString() + ")^√(" + leftExpression->toString() + ")";
}

//Sine

std::string Sine::toString() const noexcept
{
    return "Sin(" + expression->toString() + ")";
}

//Cosine

std::string Cosine::toString() const noexcept
{
    return "cos(" + expression->toString() + ")";
}

//Tangent

std::string Tangent::toString() const noexcept
{
    return "Tag(" + expression->toString() + ")";
}

//Cotangent

std::string Cotangent::toString() const noexcept
{
    return "Ctg(" + expression->toString() + ")";
}

//Pair
Pair::Pair(Expression* _first, Expression* _second) : Value(DataType::Pair), first{_first}, second{_second} {}

std::string Pair::toString() const noexcept
{
    return "[" + first->toString() + ", " + second->toString() + "]";
}

Expression* Pair::getFirst()
{
    return first;
}

Expression* Pair::getSecond()
{
    return second;
}

void Pair::destroy() noexcept
{
    if (first != nullptr)
    {
        first->destroy();
        delete first;
    }
    if (second != nullptr)
    {
        second->destroy();
        delete second;
    }
}

//PairFirst
std::string PairFirst::toString() const noexcept
{
    return "";
}

//PairSecond

std::string PairSecond::toString() const noexcept
{
    return "";
}

//Vector
Vector::Vector(std::vector<Expression*> _vectorExpression) : Value(DataType::Vector), vectorExpression(_vectorExpression) {}

std::string Vector::toString() const noexcept
{
    std::string result = "[  ";
    for (auto exp : vectorExpression)
    {
        std::string element = exp->toString();
        result += element +"  ";
    }
    result += "]";
    return result;
}

std::vector<Expression*> Vector::getVectorExpression() const
{
    return vectorExpression;
}
void Vector::destroy() noexcept
{
    for (auto exp : vectorExpression)
    {
        if (exp != nullptr)
        {
            exp->destroy();
            delete exp;
        }
    }
    vectorExpression.clear();
}

//Matrix
Matrix::Matrix(std::vector<std::vector<Expression*>> _matrixExpression) : Value(DataType::Matrix), matrixExpression(_matrixExpression) {}

std::string Matrix::toString() const noexcept
{
    std::string result;
    for (std::vector<Expression*> vec : matrixExpression)
    {
        for (Expression* exp : vec)
        {
            std::string element = exp->toString();
            result += element +" ";
        }
        result += "\n";
    }
    return result;
}
std::vector<std::vector<Expression*>> Matrix::getMatrixExpression() const
{
    return matrixExpression;
}
void Matrix::destroy() noexcept
{
    for (auto& vec : matrixExpression)
    {
        for (auto exp : vec)
        {
            if (exp != nullptr)
            {
                exp->destroy();
                delete exp;
            }
        }
        vec.clear();
    }
    matrixExpression.clear();
}

// Inverse Matrix
InverseMatrix::InverseMatrix(Expression* _matrix) : Value(DataType::Matrix), matrix(_matrix) {}

std::string InverseMatrix::toString() const noexcept
{
    return "Matrix to Inverse:\n" + matrix->toString();
}
void InverseMatrix::destroy() noexcept
{
    if (matrix != nullptr)
    {
        matrix->destroy();
        delete matrix;
    }
}
// LU Matrix
MatrixLU::MatrixLU(Expression* _matrix) : Value(DataType::Matrix), matrix(_matrix) {}

std::string MatrixLU::toString() const noexcept
{
    return "Matrix to lower Upper Decomposition: \n"+ matrix->toString();
}

void MatrixLU::destroy() noexcept
{
    if (matrix != nullptr)
    {
        matrix->destroy();
        delete matrix;
    }
}

TridiagonalMatrix::TridiagonalMatrix(Expression* _matrix) : Value(DataType::Matrix), matrix(_matrix) {}

std::string TridiagonalMatrix::toString() const noexcept
{
    return "Matrix to make tridiagonal: \n"+ matrix->toString();
}
void TridiagonalMatrix::destroy() noexcept
{
    if (matrix != nullptr)
    {
        matrix->destroy();
        delete matrix;
    }
}

// Eigenvalues
RealEigenvalues::RealEigenvalues(Expression* _matrix) : Value(DataType::Matrix), matrix(_matrix) {}

std::string RealEigenvalues::toString() const noexcept
{
    return "Matrix to calculate eigenvalues: \n"+ matrix->toString();
}
void RealEigenvalues::destroy() noexcept
{
    if (matrix != nullptr)
    {
        matrix->destroy();
        delete matrix;
    }
}
// Determinant
Determinant::Determinant(Expression* _matrix) : Value(DataType::Number), matrix(_matrix) {}

std::string Determinant::toString() const noexcept
{
    return "Matrix to calculate determinant: \n"+ matrix->toString();
}

void Determinant::destroy() noexcept
{
    if (matrix != nullptr)
    {
        matrix->destroy();
        delete matrix;
    }
}

//Function

std::string Function::toString() const noexcept
{
    return expression->toString();
}

//Integral
Integral::Integral(Expression* _interval, Expression* _function, Expression* _variable) : interval(_interval), function(_function), variable(_variable) {}

std::string Integral::toString() const noexcept
{
    std::string str = "Interval: " + interval->toString() + " | Integral = ∫(" + function->toString() + ")d" + variable->toString();
    return str;
}
void Integral::destroy() noexcept
{
    if (interval != nullptr)
    {
        interval->destroy();
        delete interval;
    }
    if (function != nullptr)
    {
        function->destroy();
        delete function;
    }
    if (variable != nullptr)
    {
        variable->destroy();
        delete variable;
    }
}
// Interpolate
Interpolate::Interpolate(Expression* _vectorExpression, Expression* _numInter) : vectorExpression(_vectorExpression), numInter(_numInter) {}
std::string Interpolate::toString() const noexcept
{
    return vectorExpression->toString() + "\nInterpolate Number: " +numInter->toString();
}
void Interpolate::destroy() noexcept
{
    if (vectorExpression != nullptr)
    {
        vectorExpression->destroy();
        delete vectorExpression;
    }
    if (numInter != nullptr)
    {
        numInter->destroy();
        delete numInter;
    }
}
//ODE First
ODEFirstOrderInitialValues::ODEFirstOrderInitialValues(Expression* _funct, Expression* _initialValue, Expression* _tFinal, Expression* _variable) : funct(_funct), initialValue(_initialValue), tFinal(_tFinal), variable(_variable) {}

std::string ODEFirstOrderInitialValues::toString() const noexcept
{
    return variable->toString() + "' = " + funct->toString() +"\n[t,"+ variable->toString()+"] = " + initialValue->toString() + "\nT_Final: " + tFinal->toString();
}

void ODEFirstOrderInitialValues::destroy() noexcept
{
    if (funct != nullptr)
    {
        funct->destroy();
        delete funct;
    }
    if (initialValue != nullptr)
    {
        initialValue->destroy();
        delete initialValue;
    }
    if (tFinal != nullptr)
    {
        tFinal->destroy();
        delete tFinal;
    }
    if (variable != nullptr)
    {
        variable->destroy();
        delete variable;
    }
}

FindRootBisection::FindRootBisection(Expression* _interval, Expression* _function, Expression* _variable, Expression* _iterationLimit) : interval(_interval), function(_function), variable(_variable), iterationLimit(_iterationLimit) {}

std::string FindRootBisection::toString() const noexcept
{
    return "Interval: " + interval->toString() + " | Function: " + function->toString();
}
void FindRootBisection::destroy() noexcept
{
    if (interval != nullptr)
    {
        interval->destroy();
        delete interval;
    }
    if (function != nullptr)
    {
        function->destroy();
        delete function;
    }
    if (variable != nullptr)
    {
        variable->destroy();
        delete variable;
    }
    if (iterationLimit != nullptr)
    {
        iterationLimit->destroy();
        delete iterationLimit;
    }
}

Display::Display(Expression* _expression) : expression(_expression) {}

std::string Display::toString() const noexcept
{
    if (expression == nullptr)
    {
        return "NULLPTR";
    }
    return expression->toString();
}

void Display::destroy() noexcept
{
    if (expression != nullptr)
    {
        expression->destroy();
        delete expression;
    }
}

Print::Print(std::string _message) : message(_message) {}

std::string Print::toString() const noexcept
{
    return message;
}

void Print::destroy() noexcept {}