#include <Expression.hpp>

Expression::~Expression() {}

//Unit
Unit::Unit() {}
Expression* Unit::eval(Environment&) const
{
    return new Unit();
}
std::string Unit::toString() const noexcept
{
    return "";
}
void Unit::destroy() noexcept {}

//Invalid
Invalid::Invalid() {}
Expression* Invalid::eval(Environment& env) const
{
    return new Invalid();
}
std::string Invalid::toString() const noexcept
{
    return "INVALID OPERATION";
}

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
        expression = nullptr;
    }
}

// Binary Expression
BinaryExpression::BinaryExpression(Expression* _leftExpression, Expression* _rightExpression) : leftExpression(_leftExpression), rightExpression(_rightExpression) {}
void BinaryExpression::destroy() noexcept
{
    if (leftExpression != nullptr)
    {
        leftExpression->destroy();
        delete leftExpression;
        leftExpression = nullptr;
    }
    if (rightExpression != nullptr)
    {
        rightExpression->destroy();
        delete rightExpression;
        rightExpression = nullptr;
    }
}

//Impossible
Impossible::Impossible() : Value(DataType::Impossible) {}
Expression* Impossible::eval(Environment& env) const
{
    return new Impossible();
}
std::string Impossible::toString() const noexcept
{
    return value;
}

// Number
Number::Number(double _number) : Value(DataType::Number), number{_number} {}
Expression* Number::eval(Environment& env) const
{
    if (std::abs(number) <= 0.0000000001)
    {
        return new Number(0.0);
    }
    return new Number(number);
}
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
Expression* PI::eval(Environment& env) const
{
    return new Number(M_PI);
}
std::string PI::toString() const noexcept
{
    return "π";
}

EULER::EULER() : Value(DataType::Number){}
Expression* EULER::eval(Environment& env) const
{
    return new Number(M_E);
}
std::string EULER::toString() const noexcept
{
    return "e";
}

// Variable
Variable::Variable(char _variable) : Value(DataType::Variable), variable{_variable} {}
Expression* Variable::eval(Environment& env) const
{
    if (!env.empty())
    {
        for (auto pair : env)
        {
            if (pair.first == std::string{variable})
            {
                return pair.second->eval(env);
            }
        }
    }
    return new Variable(variable);
}
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
Expression* Name::eval(Environment& env) const
{
    if (!env.empty())
    {
        for (auto pair : env)
        {
            if (pair.first == name)
            {
                return pair.second->eval(env);
            }
        }
    }
    return new Name(name);
}
std::string Name::toString() const noexcept
{
    return name;
}
std::string Name::getName() const noexcept
{
    return name;
}

// Addition
Expression* Addition::eval(Environment& env) const
{
    Expression* exp1 = leftExpression->eval(env);
    Expression* exp2 = rightExpression->eval(env);

    Value* element1 = dynamic_cast<Value*>(exp1);
    Value* element2 = dynamic_cast<Value*>(exp2);

    if (element1 == nullptr || element2 == nullptr)
    {
        return new Addition(exp1, exp2);
    }

    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return new Addition(exp1, exp2);
    }

    if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix) {
        auto matrix1 = (dynamic_cast<Matrix*>(element1))->getMatrixExpression();
        auto matrix2 = (dynamic_cast<Matrix*>(element2))->getMatrixExpression();

        if (matrix1.size() != matrix2.size())
        {
            exp1->destroy();
            delete exp1;
            exp2->destroy();
            delete exp2;
            return new Impossible();
        }

        std::vector<Expression*> newMatrix{};
        for (size_t i = 0; i < matrix1.size(); ++i)
        {
            auto current_vec_mat1 = dynamic_cast<Vector*>(matrix1[i]);
            auto current_vec_mat2 = dynamic_cast<Vector*>(matrix2[i]);
            if (current_vec_mat1->size() != current_vec_mat2->size())
            {
                exp1->destroy();
                delete exp1;
                exp2->destroy();
                delete exp2;
                return new Impossible();
            }

            std::vector<Expression*> newVec{};
            auto row1 = current_vec_mat1->getVectorExpression();
            auto row2 = current_vec_mat2->getVectorExpression();

            for (size_t j = 0; j < current_vec_mat1->size(); ++j)
            {
                newVec.push_back(new Addition(row1[j], row2[j]));
            }

            newMatrix.push_back(new Vector(newVec));

        }
        auto res = (Matrix(newMatrix)).eval(env);

        exp1->destroy();
        delete exp1;
        exp2->destroy();
        delete exp2;

        return res;
    }

    auto num1 = dynamic_cast<Number*>(exp1);
    auto num2 = dynamic_cast<Number*>(exp2);

    if (num1 == nullptr || num2 == nullptr) {
        exp1->destroy();
        delete exp1;
        exp2->destroy();
        delete exp2;
        return new Invalid();
    }

    double resultValue = num1->getNumber() + num2->getNumber();
    exp1->destroy();
    delete exp1;
    exp2->destroy();
    delete exp2;
    return (Number(resultValue)).eval(env);
}

std::string Addition::toString() const noexcept
{
    return leftExpression->toString() + " + " + rightExpression->toString();
}

//Subtraction
Expression* Substraction::eval(Environment& env) const
{
    Expression* exp1 = leftExpression->eval(env);
    Expression* exp2 = rightExpression->eval(env);

    Value* element1 = dynamic_cast<Value*>(exp1);
    Value* element2 = dynamic_cast<Value*>(exp2);

    if (element1 == nullptr || element2 == nullptr)
    {
        return new Substraction(exp1, exp2);
    }

    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return new Substraction(exp1, exp2);
    }

    if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix) {
        auto matrix1 = (dynamic_cast<Matrix*>(element1))->getMatrixExpression();
        auto matrix2 = (dynamic_cast<Matrix*>(element2))->getMatrixExpression();

        if (matrix1.size() != matrix2.size())
        {
            exp1->destroy();
            delete exp1;
            exp2->destroy();
            delete exp2;
            return new Impossible();
        }

        std::vector<Expression*> newMatrix;
        for (size_t i = 0; i < matrix1.size(); ++i)
        {
            auto current_vec_mat1 = dynamic_cast<Vector*>(matrix1[i]);
            auto current_vec_mat2 = dynamic_cast<Vector*>(matrix2[i]);
            if (current_vec_mat1->size() != current_vec_mat2->size())
            {
                exp1->destroy();
                delete exp1;
                exp2->destroy();
                delete exp2;
                return new Impossible();
            }

            std::vector<Expression*> newVec;
            auto row1 = current_vec_mat1->getVectorExpression();
            auto row2 = current_vec_mat2->getVectorExpression();

            for (size_t j = 0; j < current_vec_mat1->size(); ++j) {
                newVec.push_back(new Substraction(row1[j], row2[j]));
            }

            newMatrix.push_back(new Vector(newVec));
        }

        return (Matrix(newMatrix)).eval(env);
    }

    auto num1 = dynamic_cast<Number*>(exp1);
    auto num2 = dynamic_cast<Number*>(exp2);

    if (num1 == nullptr || num2 == nullptr) {
        exp1->destroy();
        delete exp1;
        exp2->destroy();
        delete exp2;
        return new Invalid();
    }

    double resultValue = num1->getNumber() - num2->getNumber();
    exp1->destroy();
    delete exp1;
    exp2->destroy();
    delete exp2;
    return (Number(resultValue)).eval(env);
}
std::string Substraction::toString() const noexcept
{
    return leftExpression->toString() + " - (" + rightExpression->toString() + ")";
}

//Multiplication
Expression* Multiplication::eval(Environment& env) const
{
    Expression* exp1 = leftExpression->eval(env);
    Expression* exp2 = rightExpression->eval(env);

    Value* element1 = dynamic_cast<Value*>(exp1);
    Value* element2 = dynamic_cast<Value*>(exp2);

    if (element1 == nullptr || element2 == nullptr)
    {
        return new Multiplication(exp1, exp2);
    }

    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return new Multiplication(exp1, exp2);
    }

    if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix)
    {
        auto matrix1 = dynamic_cast<Matrix*>(element1)->getMatrixExpression();
        auto matrix2 = dynamic_cast<Matrix*>(element2)->getMatrixExpression();
        std::vector<Expression*> newMatrix;
        auto first_row_mat1 = dynamic_cast<Vector*>(matrix1[0]);

        if (first_row_mat1->size() != matrix2.size())
        {
            exp1->destroy();
            delete exp1;
            exp2->destroy();
            delete exp2;
            return new Impossible();
        }
        for (size_t i = 0; i < matrix1.size(); ++i)
        {
            std::vector<Expression*> newVec;
            auto first_row_mat2 = dynamic_cast<Vector*>(matrix2[0]);

            auto n_row_matrix1 = dynamic_cast<Vector*>(matrix1[i]);

            for (size_t j = 0; j < first_row_mat2->size(); ++j)
            {
                Expression* acc = new Number(0.0);
                for (size_t k = 0; k < n_row_matrix1->size(); ++k)
                {
                    auto k_row_matrix2 = dynamic_cast<Vector*>(matrix2[k]);
                    Expression* mul = new Multiplication(n_row_matrix1->getVectorExpression()[k], k_row_matrix2->getVectorExpression()[j]);
                    Expression* temp = new Addition(acc, mul);
                    acc = temp;
                }
                newVec.push_back(acc);
            }
            newMatrix.push_back(new Vector(newVec));
        }
        return (Matrix(newMatrix)).eval(env);
    }

    if (element1->getDataType() == DataType::Number && element2->getDataType() == DataType::Matrix)
    {
        auto num = dynamic_cast<Number*>(element1);
        auto matrix1 = dynamic_cast<Matrix*>(element2)->getMatrixExpression();
        std::vector<Expression*> newMatrix{};
        for (Expression* vec : matrix1)
        {
            auto v = dynamic_cast<Vector*>(vec);
            std::vector<Expression*> new_vec{};
            for (Expression* exp : v->getVectorExpression())
            {
                new_vec.push_back(new Multiplication(num, exp));
            }
            newMatrix.push_back(new Vector(new_vec));
        }
        return ((Matrix(newMatrix)).eval(env));
    }

    auto num1 = dynamic_cast<Number*>(exp1);
    auto num2 = dynamic_cast<Number*>(exp2);
    if (num1 == nullptr || num2 == nullptr)
    {
        exp1->destroy();
        delete exp1;
        exp2->destroy();
        delete exp2;
        return new Invalid();
    }
    double result = num1->getNumber() * num2->getNumber();
    exp1->destroy();
    delete exp1;
    exp2->destroy();
    delete exp2;
    return new Number(result);
}
std::string Multiplication::toString() const noexcept
{
    return "("+ leftExpression->toString()+ ") * (" + rightExpression->toString() +")";
}

//Division
Expression* Division::eval(Environment& env) const
{
    Expression* exp1 = leftExpression->eval(env);
    Expression* exp2 = rightExpression->eval(env);

    Value* element1 = dynamic_cast<Value*>(exp1);
    Value* element2 = dynamic_cast<Value*>(exp2);

    if (element1 == nullptr || element2 == nullptr)
    {
        return new Division(exp1, exp2);
    }

    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return new Division(exp1, exp2);
    }

    if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix)
    {
        auto matrix1 = dynamic_cast<Matrix*>(element1);
        auto matrix2 = dynamic_cast<Matrix*>(element2);

        return (Multiplication(matrix1, new InverseMatrix(matrix2))).eval(env);
    }

    if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Number)
    {
        auto matrix1 = dynamic_cast<Matrix*>(element1);
        auto num = dynamic_cast<Number*>(element2)->getNumber();
        if (num == 0)
        {
            exp1->destroy();
            delete exp1;
            exp2->destroy();
            delete exp2;
            return new Impossible();
        }
        Expression* newNum = new Number(1/num);
        return (Multiplication(newNum, matrix1)).eval(env);
    }

    auto num1 = dynamic_cast<Number*>(exp1);
    auto num2 = dynamic_cast<Number*>(exp2);
    if (num1 == nullptr || num2 == nullptr)
    {
        exp1->destroy();
        delete exp1;
        exp2->destroy();
        delete exp2;
        return new Invalid();
    }
    if (std::abs(num2->getNumber()) <= 0.00000001)
    {
        return new Impossible();
    }
    double result = num1->getNumber() / num2->getNumber();
    exp1->destroy();
    delete exp1;
    exp2->destroy();
    delete exp2;
    return (Number(result)).eval(env);
}

std::string Division::toString() const noexcept
{
    return "(" + leftExpression->toString() + ")/(" + rightExpression->toString() + ")";
}

//Power
Expression* Power::eval(Environment& env) const
{
    auto exp1 = leftExpression->eval(env);
    auto exp2 = rightExpression->eval(env);
    auto element1 = dynamic_cast<Value*>(exp1);
    auto element2 = dynamic_cast<Value*>(exp2);
    if (element1 == nullptr || element2 == nullptr)
    {
        return new Power(exp1, exp2);
    }
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return new Power(exp1, exp2);
    }
    auto num1 = dynamic_cast<Number*>(exp1);
    auto num2 = dynamic_cast<Number*>(exp2);
    if (num1 == nullptr || num2 == nullptr)
    {
        exp1->destroy();
        delete exp1;
        exp2->destroy();
        delete exp2;
        return new Invalid();
    }
    if (num2->getNumber() <= 0 && std::abs(num1->getNumber()) <= 0.00000001)
    {
        return new Impossible();
    }
    double result = std::pow(num1->getNumber(), num2->getNumber());
    exp1->destroy();
    delete exp1;
    exp2->destroy();
    delete exp2;
    return new Number(result);
}
std::string Power::toString() const noexcept
{
    return "("+ leftExpression->toString() + ")^(" + rightExpression->toString() + ")";
}

//NaturalLogarithm
Expression* NaturalLogarithm::eval(Environment& env) const
{
    Expression* exp = expression->eval(env);
    auto element = dynamic_cast<Value*>(exp);
    if (element == nullptr)
    {
        return new NaturalLogarithm(exp);
    }
    if(element->getDataType() == DataType::Variable)
    {
        return new NaturalLogarithm(exp);
    }
    auto num = dynamic_cast<Number*>(exp);
    if (num == nullptr)
    {
        exp->destroy();
        delete exp;
        return new Invalid();
    }
    if (num->getNumber() <= 0)
    {
        exp->destroy();
        delete exp;
        return new Impossible();
    }
    double result = std::log(num->getNumber());
    exp->destroy();
    delete exp;
    return new Number(result);
}
std::string NaturalLogarithm::toString() const noexcept
{
    return "ln(" + expression->toString() + ")";
}

//Logarithm
Expression* Logarithm::eval(Environment& env) const
{
    Expression* exp1 = leftExpression->eval(env);
    Expression* exp2 = rightExpression->eval(env);
    auto element1 = dynamic_cast<Value*>(exp1);
    auto element2 = dynamic_cast<Value*>(exp2);
    if (element1 == nullptr || element2 == nullptr)
    {
        return new Logarithm(exp1, exp2);
    }
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return new Logarithm(exp1, exp2);
    }
    auto num1 = dynamic_cast<Number*>(exp1);
    auto num2 = dynamic_cast<Number*>(exp2);
    if (num1 == nullptr || num2 == nullptr)
    {
        exp1->destroy();
        exp2->destroy();
        delete exp1;
        delete exp2;
        return new Invalid();
    }
    if (num1->getNumber() <= 0 || num2->getNumber() <= 0 || num2->getNumber() == 1)
    {
        exp1->destroy();
        exp2->destroy();
        delete exp1;
        delete exp2;
        return new Impossible();
    }

    double result = std::log(num1->getNumber()) / std::log(num2->getNumber());
    exp1->destroy();
    exp2->destroy();
    delete exp1;
    delete exp2;
    return new Number(result);
}
std::string Logarithm::toString() const noexcept
{
    return "lg" + leftExpression->toString() + "(" + rightExpression->toString() + ")";
}

// Square Root
Expression* SquareRoot::eval(Environment& env) const
{
    Expression* exp = expression->eval(env);
    auto element = dynamic_cast<Value*>(exp);
    if (element == nullptr)
    {
        return new SquareRoot(exp);
    }
    if(element->getDataType() == DataType::Variable)
    {
        return new SquareRoot(exp);
    }
    auto num = dynamic_cast<Number*>(exp);
    if (num == nullptr)
    {
        exp->destroy();
        delete exp;
        return new Invalid();
    }
    if (num->getNumber() < 0)
    {
        exp->destroy();
        delete exp;
        return new Impossible();
    }
    double result = std::sqrt(num->getNumber());
    exp->destroy();
    delete exp;
    return new Number(result);
}
std::string SquareRoot::toString() const noexcept
{
    return "√(" + expression->toString() + ")";
}

// Root
Expression* Root::eval(Environment& env) const
{
    Expression* exp1 = leftExpression->eval(env);
    Expression* exp2 = rightExpression->eval(env);
    auto element1 = dynamic_cast<Value*>(exp1);
    auto element2 = dynamic_cast<Value*>(exp2);
    if (element1 == nullptr || element2 == nullptr)
    {
        return new Root(exp1, exp2);
    }
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return new Root(exp1, exp2);
    }
    auto num1 = dynamic_cast<Number*>(exp1);
    auto num2 = dynamic_cast<Number*>(exp2);
    if (num1 == nullptr || num2 == nullptr)
    {
        exp1->destroy();
        exp2->destroy();
        delete exp1;
        delete exp2;
        return new Invalid();
    }
    if (num1->getNumber() <= 0 || num2->getNumber() <= 0 || num2->getNumber() == 1)
    {
        exp1->destroy();
        exp2->destroy();
        delete exp1;
        delete exp2;
        return new Impossible();
    }

    double result = std::pow(num1->getNumber(), 1.0 / num2->getNumber());
    exp1->destroy();
    exp2->destroy();
    delete exp1;
    delete exp2;
    return new Number(result);
}
std::string Root::toString() const noexcept
{
    return "(" + rightExpression->toString() + ")^√(" + leftExpression->toString() + ")";
}

//Sine
Expression* Sine::eval(Environment& env) const
{
    Expression* exp = expression->eval(env);
    auto element = dynamic_cast<Value*>(exp);
    if (element == nullptr)
    {
        return new SquareRoot(exp);
    }
    if(element->getDataType() == DataType::Variable)
    {
        return new SquareRoot(exp);
    }
    auto num = dynamic_cast<Number*>(exp);
    if (num == nullptr)
    {
        exp->destroy();
        delete exp;
        return new Invalid();
    }
    if (num->getNumber() < 0)
    {
        exp->destroy();
        delete exp;
        return new Impossible();
    }
    double result = std::sin(num->getNumber());
    exp->destroy();
    delete exp;
    return new Number(result);
}
std::string Sine::toString() const noexcept
{
    return "Sin(" + expression->toString() + ")";
}

//Cosine
Expression* Cosine::eval(Environment& env) const
{
    Expression* exp = expression->eval(env);
    auto element = dynamic_cast<Value*>(exp);
    if (element == nullptr)
    {
        return new SquareRoot(exp);
    }
    if(element->getDataType() == DataType::Variable)
    {
        return new SquareRoot(exp);
    }
    auto num = dynamic_cast<Number*>(exp);
    if (num == nullptr)
    {
        exp->destroy();
        delete exp;
        return new Invalid();
    }
    if (num->getNumber() < 0)
    {
        exp->destroy();
        delete exp;
        return new Impossible();
    }
    double result = std::cos(num->getNumber());
    exp->destroy();
    delete exp;
    return new Number(result);
}
std::string Cosine::toString() const noexcept
{
    return "cos(" + expression->toString() + ")";
}

//Tangent
Expression* Tangent::eval(Environment& env) const
{
    Expression* exp = expression->eval(env);
    auto element = dynamic_cast<Value*>(exp);
    if (element == nullptr)
    {
        return new SquareRoot(exp);
    }
    if(element->getDataType() == DataType::Variable)
    {
        return new SquareRoot(exp);
    }
    auto num = dynamic_cast<Number*>(exp);
    if (num == nullptr)
    {
        exp->destroy();
        delete exp;
        return new Invalid();
    }
    if (std::abs(std::cos(num->getNumber())) <= 0.00000001)
    {
        exp->destroy();
        delete exp;
        return new Impossible();
    }
    double result = std::tan(num->getNumber());
    exp->destroy();
    delete exp;
    return new Number(result);
}
std::string Tangent::toString() const noexcept
{
    return "Tag(" + expression->toString() + ")";
}

//Cotangent
Expression* Cotangent::eval(Environment& env) const
{
    Expression* exp = expression->eval(env);
    auto element = dynamic_cast<Value*>(exp);
    if (element == nullptr)
    {
        return new SquareRoot(exp);
    }
    if(element->getDataType() == DataType::Variable)
    {
        return new SquareRoot(exp);
    }
    auto num = dynamic_cast<Number*>(exp);
    if (num == nullptr)
    {
        exp->destroy();
        delete exp;
        return new Invalid();
    }
    if (std::abs(std::sin(num->getNumber())) <= 0.00000001)
    {
        exp->destroy();
        delete exp;
        return new Impossible();
    }
    double result = 1 / std::tan(num->getNumber());
    exp->destroy();
    delete exp;
    return new Number(result);
}
std::string Cotangent::toString() const noexcept
{
    return "Ctg(" + expression->toString() + ")";
}

//Pair
Pair::Pair(Expression* _first, Expression* _second) : Value(DataType::Pair), first{_first}, second{_second} {}
Expression* Pair::eval(Environment& env) const
{
    return new Pair(first->eval(env), second->eval(env));
}
std::string Pair::toString() const noexcept
{
    return "(" + first->toString() + ", " + second->toString() + ")";
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
        first = nullptr;
    }
    if (second != nullptr)
    {
        second->destroy();
        delete second;
        second = nullptr;
    }
}

//PairFirst
Expression* PairFirst::eval(Environment& env) const
{
    Expression* exp = expression->eval(env);
    auto pair = dynamic_cast<Pair*>(exp);
    if (pair == nullptr)
    {
        exp->destroy();
        delete exp;
        return new Invalid();
    }
    auto result = pair->getFirst()->eval(env);
    exp->destroy();
    delete exp;
    return result;
}
std::string PairFirst::toString() const noexcept
{
    return "";
}

//PairSecond
Expression* PairSecond::eval(Environment& env) const
{
    Expression* exp = expression->eval(env);
    auto pair = dynamic_cast<Pair*>(exp);
    if (pair == nullptr)
    {
        exp->destroy();
        delete exp;
        return new Invalid();
    }
    auto result = pair->getSecond()->eval(env);
    exp->destroy();
    delete exp;
    return result;
}
std::string PairSecond::toString() const noexcept
{
    return "";
}

//Vector
Vector::Vector(std::vector<Expression*>& _vectorExpression) : Value(DataType::Vector), vectorExpression(_vectorExpression) {}
Expression* Vector::eval(Environment& env) const
{
    std::vector<Expression*> newVector;
    for (auto exp : vectorExpression)
    {
        Expression* element = exp->eval(env);
        if (element == nullptr)
        {
            for (auto e : newVector)
            {
                e->destroy();
                delete e;
            }
            return new Invalid();
        }
        newVector.push_back(element);
    }
    return new Vector(newVector);
}
std::string Vector::toString() const noexcept
{
    std::string result = "[  ";
    for (const auto& exp : vectorExpression)
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
    for (auto& exp : vectorExpression)
    {
        if (exp != nullptr)
        {
            exp->destroy();
            delete exp;
            exp = nullptr;
        }
    }
    vectorExpression.clear();
}

//Matrix
Matrix::Matrix(std::vector<Expression*>& _matrixExpression) : Value(DataType::Matrix), matrixExpression(_matrixExpression) {}
Expression* Matrix::eval(Environment& env) const
{
    std::vector<Expression*> new_matrix{};
    auto first = matrixExpression[0]->eval(env);

    Vector* first_row = dynamic_cast<Vector*>(first);

    if (first_row == nullptr)
    {
        first->destroy();
        delete first;
        return new Invalid();
    }
    size_t row_size = first_row->size();

    first->destroy();
    delete first;

    for (Expression* vec : matrixExpression)
    {
        auto r = vec->eval(env);
        Vector* row = dynamic_cast<Vector*>(r);
        if (row == nullptr)
        {
            r->destroy();
            delete r;
            return new Invalid();
        }
        if (row->size() != row_size)
        {
            return new Invalid();
        }
        std::vector<Expression*> new_vector{};
        for (Expression* exp : row->getVectorExpression())
        {
            Expression* element = exp->eval(env);
            if (element == nullptr)
            {
                for (auto e : new_vector)
                {
                    e->destroy();
                    delete e;
                }
                return new Invalid();
            }
            new_vector.push_back(element);
        }

        r->destroy();
        delete r;

        new_matrix.push_back(new Vector(new_vector));
    }
    return new Matrix(new_matrix);
}
std::string Matrix::toString() const noexcept
{
    std::string result;
    for (const auto& vec : matrixExpression)
    {
        std::string element = vec->toString();
        result += element +" ";
        result += "\n";
    }
    return result;
}
std::vector<Expression*> Matrix::getMatrixExpression() const
{
    return matrixExpression;
}
void Matrix::destroy() noexcept
{
    for (auto& vec : matrixExpression)
    {
       if (vec != nullptr)
       {
            vec->destroy();
            delete vec;
            vec = nullptr;
       }
    }
    matrixExpression.clear();
}

// Inverse Matrix
InverseMatrix::InverseMatrix(Expression* _matrix) : Value(DataType::Matrix), matrix(_matrix) {}
Expression* InverseMatrix::gauss(std::vector<std::vector<Expression*>> matrixExpression) const
{
    size_t size = matrixExpression.size();

    double matrix[size][size * 2];

    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            matrix[i][j] = dynamic_cast<Number*>(matrixExpression[i][j])->getNumber();
        }
    }

    for (size_t i = size, k = 0; i < size * 2; ++i ,++k)
    {
        for (size_t j = size; j < size * 2; ++j)
        {
            if (i == j)
            {
                matrix[k][j] = 1.0;
            }
            else
            {
                matrix[k][j] = 0.0;
            }
        }
    }

    for (size_t i = 0; i < size - 1; ++i)
    {
        size_t primaryIndexPivot = i;
        for (size_t j = i + 1; j < size; ++j)
        {
            if (std::abs(matrix[primaryIndexPivot][i]) < std::abs(matrix[j][i]))
            {
                primaryIndexPivot = j;
            }
        }
        if (primaryIndexPivot != i)
        {
            for (size_t j = 0; j < size * 2; ++j)
            {
                std::swap(matrix[i][j], matrix[primaryIndexPivot][j]);
            }
        }

        if (matrix[i][i] == 0)
        {
            return new Impossible();
        }

        for (int jRow = i + 1; jRow < size; ++jRow)
        {
            if (matrix[jRow][i] != 0)
            {
                double result = matrix[jRow][i] / matrix[i][i];
                for (int jColumn = i + 1; jColumn < size * 2; ++jColumn)
                {
                    double temp = matrix[jRow][jColumn];
                    matrix[jRow][jColumn] -= result * matrix[i][jColumn];
                    if (std::abs(matrix[jRow][jColumn]) < std::numeric_limits<double>::epsilon() * temp)
                    {
                        matrix[jRow][jColumn] = 0.0;
                    }
                }
            }
        }
    }

    if (matrix[size - 1][size - 1] == 0)
    {
        return new Impossible();
    }

    for (size_t m = size; m < size * 2; ++m)
    {
        matrix[size - 1][m] /= matrix[size - 1][size - 1];
        for (int newIdx = size - 2; newIdx >= 0; --newIdx)
        {
            double temp = matrix[newIdx][m];
            for (int k = newIdx + 1; k < size; ++k)
            {
                temp -= matrix[newIdx][k] * matrix[k][m];
            }
            matrix[newIdx][m] = temp / matrix[newIdx][newIdx];
        }
    }
    std::vector<Expression*> newMatrix;

    for (size_t i = 0; i < size; ++i)
    {
        std::vector<Expression*> newVector;
        for (size_t j = size; j < size * 2; ++j)
        {
            newVector.push_back(new Number(matrix[i][j]));
        }
        newMatrix.push_back(new Vector(newVector));
    }
    return new Matrix(newMatrix);
}
Expression* InverseMatrix::eval(Environment& env) const
{
    auto evMatrix = dynamic_cast<Matrix*>(matrix->eval(env));
    if (evMatrix == nullptr)
    {
        return new Invalid();
    }
    auto mat = evMatrix->getMatrixExpression();
    std::vector<std::vector<Expression*>> matrix_to_inverse{};
    for (auto &vec : mat)
    {
        const auto& v = dynamic_cast<Vector*>(vec);
        std::vector<Expression*> row{};
        for (auto &exp : v->getVectorExpression())
        {
            row.push_back(exp);
        }
        matrix_to_inverse.push_back(row);
    }

    if (matrix_to_inverse.size() != matrix_to_inverse[0].size()) // Validation for Square Matrix
    {
        return new Impossible();
    }
    return gauss(matrix_to_inverse);
}
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
        matrix = nullptr;
    }
}

// LU Matrix
MatrixLU::MatrixLU(Expression* _matrix) : Value(DataType::Matrix), matrix(_matrix) {}

Expression* MatrixLU::lowerUpperDecomposition(std::vector<std::vector<Expression*>> matrixExpression) const
{
    size_t size = matrixExpression.size();

    double matrix[size][size];

    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            matrix[i][j] = dynamic_cast<Number*>(matrixExpression[i][j])->getNumber();
        }
    }

    auto L = std::vector<std::vector<double>>(size, std::vector<double>(size, 0.0));
    auto U = std::vector<std::vector<double>>(size, std::vector<double>(size, 0.0));
    for (int i = 0; i < size; ++i)
    {
        L[i][i] = 1.0;
        for (int j = 0; j < size; ++j)
        {
            U[i][j] = matrix[i][j];
        }
    }
    for (int k = 0; k < size - 1; ++k)
    {
        int maxIndex = k;
        double maxVal = std::abs(U[k][k]);
        for (int i = k + 1; i < size; ++i)
        {
            if (std::abs(U[i][k]) > maxVal)
            {
                maxVal = std::abs(U[i][k]);
                maxIndex = i;
            }
        }
        if (maxIndex != k)
        {
            std::swap(U[k], U[maxIndex]);
            for (int i = 0; i < k; ++i)
            {
                std::swap(L[k][i], L[maxIndex][i]);
            }
        }
        for (int i = k + 1; i < size; ++i)
        {
            L[i][k] = U[i][k] / U[k][k];
            for (int j = k; j < size; ++j)
            {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
    }
    std::vector<Expression*> newMatrixLower;
    std::vector<Expression*> newMatrixUpper;
    for (size_t i = 0; i < size; ++i)
    {
        std::vector<Expression*> newVectorLower;
        std::vector<Expression*> newVectorUpper;
        for (size_t j = 0; j < size; ++j)
        {
            newVectorLower.push_back(new Number(L[i][j]));
            newVectorUpper.push_back(new Number(U[i][j]));
        }
        newMatrixLower.push_back(new Vector(newVectorLower));
        newMatrixUpper.push_back(new Vector(newVectorUpper));
    }
    return new Pair(new Matrix(newMatrixLower), new Matrix(newMatrixUpper));
}

Expression* MatrixLU::eval(Environment& env) const
{
    auto evMatrix = dynamic_cast<Matrix*>(matrix->eval(env));
    if (evMatrix == nullptr)
    {
        return new Invalid();
    }
    auto mat = evMatrix->getMatrixExpression();
    std::vector<std::vector<Expression*>> matrix_to_lower_upper{};
    for (auto &vec : mat)
    {
        const auto& v = dynamic_cast<Vector*>(vec);
        std::vector<Expression*> row{};
        for (auto &exp : v->getVectorExpression())
        {
            row.push_back(exp);
        }
        matrix_to_lower_upper.push_back(row);
    }
    if (matrix_to_lower_upper.size() != matrix_to_lower_upper[0].size()) // Validation for Square Matrix
    {
        return new Impossible();
    }
    return lowerUpperDecomposition(matrix_to_lower_upper);
}
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
        matrix = nullptr;
    }
}

TridiagonalMatrix::TridiagonalMatrix(Expression* _matrix) : Value(DataType::Matrix), matrix(_matrix) {}
Expression* TridiagonalMatrix::tridiagonal(std::vector<std::vector<Expression*>> matrix) const
{
    size_t size = matrix.size();
    std::vector<std::vector<double>> answerMatrix(size, std::vector<double>(size)), temporalMatrix(size, std::vector<double>(size));
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            answerMatrix[i][j] = dynamic_cast<Number*>(matrix[i][j])->getNumber();
        }
    }

    std::vector<double> auxiliaryVector(size);
    for (int idx = 0; idx < size - 2; ++idx)
    {
        double sum = 0;
        for (int i = 0; i < size; ++i)
        {
            auxiliaryVector[i] = 0;
            if (i > idx + 1) auxiliaryVector[i] = answerMatrix[i][idx];
            if (i > idx) sum += answerMatrix[i][idx] * answerMatrix[i][idx];
        }
        double sign = 1;
        if (answerMatrix[idx + 1][idx] < 0) sign = -1;
        double squareRoot = sqrt(sum);
        double h = sum + std::abs(answerMatrix[idx + 1][idx]) * squareRoot;
        auxiliaryVector[idx + 1] = answerMatrix[idx + 1][idx] + squareRoot * sign;
        double quotient = 0;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                quotient += auxiliaryVector[i] * answerMatrix[i][j] * auxiliaryVector[j];
                if ((i <= idx) && (j <= idx))
                {
                    temporalMatrix[i][j] = answerMatrix[i][j];
                    continue;
                }
                if ((j == idx) && (i >= idx + 2))
                {
                    temporalMatrix[i][j] = 0;
                    continue;
                }
                double middleValue = 0;
                for (int k = 0; k < size; ++k)
                {
                    middleValue -= (auxiliaryVector[i] * answerMatrix[k][j] + answerMatrix[i][k] * auxiliaryVector[j]) * auxiliaryVector[k];
                }
                temporalMatrix[i][j] = answerMatrix[i][j] + middleValue / h;
            }
        }
        quotient /= h * h;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                answerMatrix[i][j] = temporalMatrix[i][j] + quotient * auxiliaryVector[i] * auxiliaryVector[j];
                if (std::abs(answerMatrix[i][j]) < 0.000001)
                {
                    answerMatrix[i][j] = 0;
                }
            }
        }
    }

    std::vector<Expression*> newMatrix;
    for (size_t i = 0; i < size; ++i)
    {
        std::vector<Expression*> newVector;
        for (size_t j = 0; j < size; ++j)
        {
            newVector.push_back(new Number(answerMatrix[i][j]));
        }
        newMatrix.push_back(new Vector(newVector));
    }
    return new Matrix(newMatrix);
}
Expression* TridiagonalMatrix::eval(Environment& env) const
{
    auto evMatrix = dynamic_cast<Matrix*>(matrix->eval(env));
    if (evMatrix == nullptr)
    {
        return new Invalid();
    }
    auto mat = evMatrix->getMatrixExpression();
    std::vector<std::vector<Expression*>> matrix_to_tridiagonal{};
    for (auto &vec : mat)
    {
        const auto& v = dynamic_cast<Vector*>(vec);
        std::vector<Expression*> row{};
        for (auto &exp : v->getVectorExpression())
        {
            row.push_back(exp);
        }
        matrix_to_tridiagonal.push_back(row);
    }

    if (matrix_to_tridiagonal.size() != matrix_to_tridiagonal[0].size()) // Validation for Square Matrix
    {
        return new Impossible();
    }
    return tridiagonal(matrix_to_tridiagonal);
}
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
        matrix = nullptr;
    }
}

// Eigenvalues
RealEigenvalues::RealEigenvalues(Expression* _matrix) : Value(DataType::Matrix), matrix(_matrix) {}
void RealEigenvalues::determ(std::vector<double> auxialiaryVector, std::vector<std::vector<double>> answerMatrix, double x, double& middle, size_t l) const
{
    auxialiaryVector[0] = answerMatrix[0][0] - x;
    if (l == 1) return;
    for (int k = 1; k < l; ++k)
    {
        auxialiaryVector[k] = (answerMatrix[k][k] - x) * auxialiaryVector[k - 1] - answerMatrix[k][k - 1] * answerMatrix[k][k - 1] * ((k - 2 < 0) ? 1 : auxialiaryVector[k - 2]);
    }
    middle = auxialiaryVector[l - 1];
}
void RealEigenvalues::bisec(std::vector<double> auxialiaryVector, std::vector<std::vector<double>> answerMatrix, double startInterval, double endInterval, double& middlePoint, size_t l) const
{
    int iterationsCounter = 0;
    double startValue, endValue, dx, xbValue, middleValue;
    determ(auxialiaryVector, answerMatrix, startInterval, startValue, l);
    determ(auxialiaryVector, answerMatrix, endInterval, endValue, l);
    while (true)
    {
        ++iterationsCounter;
        if (iterationsCounter > 99) return;
        dx = endInterval - startInterval;
        if (dx < 0.0000001) return;
        if (dx > 1)
        {
            middlePoint = (startInterval + endInterval) / 2;
            determ(auxialiaryVector, answerMatrix, middlePoint, middleValue, l);
            if (startValue * middleValue < 0)
            {
                endInterval = middlePoint;
                endValue = middleValue;
                continue;
            }
            startInterval = middlePoint;
            startValue = middleValue;
            continue;
        }
        xbValue = middlePoint;
        middlePoint = (startInterval * endValue - endInterval * startValue) / (endValue - startValue);
        determ(auxialiaryVector, answerMatrix, middlePoint, middleValue, l);
        if (std::abs(xbValue - middlePoint) < 0.000001) return;
        if (startValue * middleValue < 0)
        {
            endInterval = middlePoint;
            endValue = middleValue;
            continue;
        }
        startInterval = middlePoint;
        startValue = middleValue;
    }
}
Expression* RealEigenvalues::eigenvalues(std::vector<std::vector<Expression*>> matrix) const
{
    size_t size = matrix.size();
    std::vector<std::vector<double>> answerMatrix(size, std::vector<double>(size)), eigenvaluesIterations(size + 1, std::vector<double>(size + 1));
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            answerMatrix[i][j] = dynamic_cast<Number*>(matrix[i][j])->getNumber();
        }
    }

    std::vector<double> auxiliaryVector(size);

    int maxIterations = size;
    for (size_t l = 1; l <= maxIterations; ++l)
    {
        if (l == 1)
        {
            eigenvaluesIterations[1][1] = answerMatrix[0][0];
        }
        else
        {
            for (int j = 1; j <= l; ++j)
            {
                double startInterval = eigenvaluesIterations[l - 1][j - 1];
                double endInterval = eigenvaluesIterations[l - 1][j];
                double middlePoint;
                bisec(auxiliaryVector, answerMatrix, startInterval, endInterval, middlePoint, l);
                eigenvaluesIterations[l][j] = middlePoint;
            }
        }
        if (l < maxIterations)
        {
            eigenvaluesIterations[l][0] = -99;
            eigenvaluesIterations[l][l + 1] = 99;
        }
    }

    std::vector<Expression*> newVector{};
    for (size_t i = 1; i <= size; ++i)
    {
        newVector.push_back(new Number(eigenvaluesIterations[size][i]));
    }
    return new Vector(newVector);
}
Expression* RealEigenvalues::eval(Environment& env) const
{
    auto exp = matrix->eval(env);
    auto matrixExp = dynamic_cast<Matrix*>(exp);
    if (matrixExp == nullptr)
    {
        exp->destroy();
        delete exp;
        return new Invalid();
    }

    auto tridiagonalMatrix = TridiagonalMatrix(matrixExp).eval(env);
    auto mat = dynamic_cast<Matrix*>(tridiagonalMatrix)->getMatrixExpression();
    std::vector<std::vector<Expression*>> toeigen;

    for (auto& v : mat)
    {
        auto r = v->eval(env);
        auto row = dynamic_cast<Vector*>(r);
        if (row)
        {
            auto vect = row->getVectorExpression();
            toeigen.push_back(vect);
        }
    }

    return eigenvalues(toeigen);
}
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
        matrix = nullptr;
    }
}

// Determinant
Determinant::Determinant(Expression* _matrix) : Value(DataType::Number), matrix(_matrix) {}
Expression* Determinant::eval(Environment& env) const
{
    auto matrixPair = new MatrixLU(matrix);
    auto second = new PairSecond(matrixPair);
    auto upperMatrix = dynamic_cast<Matrix*>(second->eval(env));
    auto U = upperMatrix->getMatrixExpression();
    double det = 1;
    for (size_t i = 0; i < U.size(); ++i)
    {
        auto row = dynamic_cast<Vector*>(U[i]);
        det *= dynamic_cast<Number*>(row->getVectorExpression()[i])->getNumber();
    }
    delete second;
    delete matrixPair;
    return new Number(((det < 0) ? -det : det));
}
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
        matrix = nullptr;
    }
}

//Function
Expression* Function::eval(Environment& env) const
{
    Expression* exp = dynamic_cast<Value*>(expression->eval(env));
    if (exp != nullptr)
    {
        return exp;
    }
    else
    {
        delete exp;
        return expression;
    }
}
std::string Function::toString() const noexcept
{
    return expression->toString();
}

//Integral
Integral::Integral(Expression* _interval, Expression* _function, Expression* _variable) : interval(_interval), function(_function), variable(_variable) {}
Expression* Integral::simpsonMethod(double a, double b, int n, Expression* function, Environment& env, Variable* _variable) const
{
    double s = 0.0;
    double ss = 0.0;
    int ls = (n / 2 * 2 == n) ? 0 : 3;
    double h = (b - a) / n;
    if (ls == 3)
    {
        for (size_t i = 0; i <= 3; ++i)
        {
            double x = a + h * i;
            double w = (i == 0 || i == 3) ? 1 : 3;
            env.push_front(std::make_pair(std::string{_variable->getVariable()}, new Number(x)));
            auto re = function->eval(env);
            Number* funcResult = dynamic_cast<Number*>(re);
            if (funcResult == nullptr)
            {
                std::cout<<"AQUI34534"<<std::endl;
                return new Invalid();
            }
            ss = ss + w * funcResult->getNumber();
            re->destroy();
            delete re;
        }
        ss = ss * h * 3 / 8;
        if (n == 3)
        {
            return new Number(ss);
        }
    }
    for (size_t i = 0; i <= n - ls; ++i)
    {
        double x = a + h * (i + ls);
        double w = 2;
        if (int(i / 2) * 2 + 1 == i)
        {
            w = 4;
        }
        if (i == 0 || i == n - ls)
        {
            w = 1;
        }
        env.push_front(std::make_pair(std::string{_variable->getVariable()}, new Number(x)));
        auto re = function->eval(env);
        Number* funcResult = dynamic_cast<Number*>(re);
        if (funcResult == nullptr)
        {
            return new Invalid();
        }
        s = s + w * funcResult->getNumber();
        re->destroy();
        delete re;
    }
    return new Number(ss + s * h / 3);
}
Expression* Integral::eval(Environment& env) const
{
    auto inter = dynamic_cast<Pair*>(interval->eval(env));
    if (inter == nullptr)
    {
        return nullptr;
    }
    auto to = dynamic_cast<Number*>(PairFirst{inter}.eval(env));
    auto tf = dynamic_cast<Number*>(PairSecond{inter}.eval(env));
    if (to == nullptr || tf == nullptr)
    {
        return new Invalid();
    }
    double a = to->getNumber();
    double b = tf->getNumber();

    auto var = dynamic_cast<Variable*>(variable->eval(env));
    if (var == nullptr)
    {
        return new Invalid();
    }
    Environment envIntegral = std::forward_list<std::pair<std::string, Expression*>>{};
    auto result = simpsonMethod(a, b, 100, function->eval(env), envIntegral, var);

    for (auto& t : envIntegral)
    {
        if (t.second != nullptr)
        {
            t.second->destroy();
            delete t.second;
            t.second = nullptr;
        }
    }
    return result;
}
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
        interval = nullptr;
    }
    if (function != nullptr)
    {
        function->destroy();
        delete function;
        function = nullptr;
    }
    if (variable != nullptr)
    {
        variable->destroy();
        delete variable;
        variable = nullptr;
    }
}

// Interpolate
Interpolate::Interpolate(Expression* _vectorExpression, Expression* _numInter) : vectorExpression(_vectorExpression), numInter(_numInter) {}
Expression* Interpolate::eval(Environment& env) const
{
    std::vector<double> x;
    std::vector<double> f;
    auto vector = (dynamic_cast<Vector*>(vectorExpression->eval(env)));
    if (vector == nullptr)
    {
        return new Invalid();
    }
    auto vec = vector->getVectorExpression();
    int n = vec.size();

    auto number = dynamic_cast<Number*>(numInter->eval(env));
    if (number == nullptr)
    {
        return new Invalid();
    }
    double xa = number->getNumber();

    for (auto exp : vec)
    {
        auto pair = dynamic_cast<Pair*>(exp);
        if (pair == nullptr || pair->getDataType() != DataType::Pair)
        {
            return new Invalid();
        }
        auto num = dynamic_cast<Number*>(PairFirst{pair}.eval(env));
        auto num2 = dynamic_cast<Number*>(PairSecond{pair}.eval(env));
        if (num == nullptr || num2 == nullptr)
        {
            return new Invalid();
        }
        x.push_back(num->getNumber());
        f.push_back(num2->getNumber());
    }
    double y_res = 0.0;
    for (int i = 0; i < n; ++i)
    {
        double z = 1.0;
        for (int j = 0; j < n; ++j)
        {
            if (i != j)
            {
                z = z * (xa - x[j]) / (x[i] - x[j]);
            }
        }
        y_res += z * f[i];
    }
    return new Number(y_res);
}
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
        vectorExpression = nullptr;
    }
    if (numInter != nullptr)
    {
        numInter->destroy();
        delete numInter;
        numInter = nullptr;
    }
}

//ODE First
ODEFirstOrderInitialValues::ODEFirstOrderInitialValues(Expression* _funct, Expression* _initialValue, Expression* _tFinal, Expression* _variable) : funct(_funct), initialValue(_initialValue), tFinal(_tFinal), variable(_variable) {}
Expression* ODEFirstOrderInitialValues::rungekuttaMethod(double _t, double _x, double f, double h, Expression* function, Environment& env, Variable* variable) const
{
    double t = _t, x = _x, tn = f;
    while(t < tn)
    {
        env.push_front(std::make_pair(std::string{variable->getVariable()}, new Number(x)));
        auto num1 = dynamic_cast<Number*>(function->eval(env));

        if (num1 == nullptr)
        {
            return new Invalid;
        }
        double k1 = h * num1->getNumber();

        env.push_front(std::make_pair(std::string{variable->getVariable()}, new Number(x + 0.5 * k1)));
        auto num2 = dynamic_cast<Number*>(function->eval(env));

        if(num2 == nullptr)
        {
            return new Invalid();
        }

        double k2 = h * num2->getNumber();

        env.push_front(std::make_pair(std::string{variable->getVariable()}, new Number(x + 0.5 * k2)));
        auto num3 = dynamic_cast<Number*>(function->eval(env));

        if (num3 == nullptr)
        {
            return new Invalid();
        }
        double k3 = h * num3->getNumber();

        env.push_front(std::make_pair(std::string{variable->getVariable()}, new Number(x + k3)));
        auto num4 = dynamic_cast<Number*>(function->eval(env));

        if (num4 == nullptr)
        {
            return new Invalid();
        }
        double k4 = h * num4->getNumber();

        x = x + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);
        t = t + h;
    }
    return new Pair(new Number(t), new Number(x));
}
Expression* ODEFirstOrderInitialValues::eval(Environment& env) const
{
    auto initialV = dynamic_cast<Pair*>(initialValue->eval(env));
    auto to = dynamic_cast<Number*>(PairFirst{initialValue}.eval(env));
    auto xo = dynamic_cast<Number*>(PairSecond{initialValue}.eval(env));
    auto tEval = dynamic_cast<Number*>(tFinal->eval(env));
    if (initialV == nullptr || to == nullptr || xo == nullptr || tEval == nullptr)
    {
        return new Invalid();
    }
    double t = to->getNumber();
    double x = xo->getNumber();
    double f = tEval->getNumber();
    double step = 0.1;
    if (f < t)
    {
        return new Impossible();
    }
    auto var = dynamic_cast<Variable*>(variable->eval(env));
    if (var == nullptr)
    {
        new Invalid();
    }

    Environment envOde = std::forward_list<std::pair<std::string, Expression*>>{};

    auto result = rungekuttaMethod(t, x, f, step, funct->eval(env), envOde, var);
    for (auto& t : envOde)
    {
        if (t.second != nullptr)
        {
            t.second->destroy();
            delete t.second;
            t.second = nullptr;
        }
    }
    return result;
}
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
        funct = nullptr;
    }
    if (initialValue != nullptr)
    {
        initialValue->destroy();
        delete initialValue;
        initialValue = nullptr;
    }
    if (tFinal != nullptr)
    {
        tFinal->destroy();
        delete tFinal;
        tFinal = nullptr;
    }
    if (variable != nullptr)
    {
        variable->destroy();
        delete variable;
        variable = nullptr;
    }
}

FindRootBisection::FindRootBisection(Expression* _interval, Expression* _function, Expression* _variable, Expression* _iterationLimit) : interval(_interval), function(_function), variable(_variable), iterationLimit(_iterationLimit) {}
Expression* FindRootBisection::bisectionMethod(Number* left, Number* right, Expression* evFunction, Environment& env, Variable* _variable, Number* _iterationLimit) const
{
    double a = left->getNumber(), c = right->getNumber(), ep = 0.000001;
    size_t il = _iterationLimit->getNumber();

    std::string var = std::string{_variable->getVariable()};

    std::cout <<a <<std::endl;
    env.push_front(std::make_pair(var, left));
    auto _ya = dynamic_cast<Number*>(evFunction->eval(env));
    if (_ya == nullptr)
    {
        return new Invalid();
    }
    double ya = _ya->getNumber();

    env.push_front(std::make_pair(var, right));

    auto _yc = dynamic_cast<Number*>(evFunction->eval(env));
    if (_yc == nullptr)
    {
        return new Invalid();
    }
    double yc_ = _yc->getNumber();

    int it = 0;

    while (++it <= il)
    {
        double b = (a + c) / 2;
        env.push_front(std::make_pair(var, new Number(b)));
        auto _yb = dynamic_cast<Number*>(evFunction->eval(env));
        if (_yb == nullptr)
        {
            break;
        }
        double yb = _yb->getNumber();
        if (std::abs(b - a) < ep)
        {
            break;
        }
        if (ya * yb <= 0)
        {
            c = b;
            yc_ = yb;
        }
        else
        {
            a = b;
            ya = yb;
        }
    }
    return new Number((a + c) / 2);
}
Expression* FindRootBisection::eval(Environment& env) const
{
    auto evInterval = dynamic_cast<Pair*>(interval->eval(env));
    if (evInterval == nullptr)
    {
        return new Invalid();
    }
    auto left = dynamic_cast<Number*>(PairFirst{evInterval}.eval(env));
    auto right = dynamic_cast<Number*>(PairSecond{evInterval}.eval(env));

    if (left == nullptr || right == nullptr)
    {
        return new Invalid();
    }
    if (left->getDataType() != DataType::Number || right->getDataType() != DataType::Number)
    {
        return new Invalid();
    }
    if (left->getNumber() > right->getNumber())
    {
        return new Invalid();
    }
    auto var = dynamic_cast<Variable*>(variable->eval(env));

    if (var == nullptr)
    {
        return new Invalid();
    }

    auto it = dynamic_cast<Number*>(iterationLimit->eval(env));

    if (it == nullptr)
    {
        return new Invalid();
    }

    Environment envBi = std::forward_list<std::pair<std::string, Expression*>>{};
    auto result = bisectionMethod(left, right, function->eval(env), envBi, var, it);
    for (auto& t : envBi)
    {
        if (t.second != nullptr)
        {
            t.second->destroy();
            delete t.second;
            t.second = nullptr;
        }
    }
    return result;
}
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
        interval = nullptr;
    }
    if (function != nullptr)
    {
        function->destroy();
        delete function;
        function = nullptr;
    }
    if (variable != nullptr)
    {
        variable->destroy();
        delete variable;
        variable = nullptr;
    }
    if (iterationLimit != nullptr)
    {
        iterationLimit->destroy();
        delete iterationLimit;
        iterationLimit = nullptr;
    }
}

Display::Display(Expression* _expression) : expression(_expression) {}
Expression* Display::eval(Environment& env) const
{
    Expression* exp = expression->eval(env);
    std::cout << exp->toString() << std::endl;
    exp->destroy();
    delete exp;
    return new Unit();
}
std::string Display::toString() const noexcept
{
    if (expression == nullptr)
    {
        return "NULLPTR";
    }
    return "Display(" + expression->toString() + ")";
}
void Display::destroy() noexcept
{
    if (expression != nullptr)
    {
        expression->destroy();
        delete expression;
        expression = nullptr;
    }
}

Print::Print(std::string _message) : message(_message) {}
Expression* Print::eval(Environment&) const
{
    std::cout << message << std::endl;
    return new Unit();
}
std::string Print::toString() const noexcept
{
    return "Print(" + message + ")";
}
void Print::destroy() noexcept {}

Expression* Assigment::eval(Environment& env) const
{
    Name* leftName = dynamic_cast<Name*>(leftExpression);
    if (leftName != nullptr)
    {
        env.push_front(std::make_pair(leftName->getName(), rightExpression->eval(env)));
        return new Unit();
    }

    Variable* leftVar = dynamic_cast<Variable*>(leftExpression);
    if (leftVar != nullptr)
    {
        env.push_front(std::make_pair(std::string{leftVar->getVariable()}, rightExpression->eval(env)));
        return new Unit();
    }
    return new Invalid();
}
std::string Assigment::toString() const noexcept
{
    return leftExpression->toString() + " = " + rightExpression->toString();
}

//Expression List
ExpressionList::ExpressionList() : expressions{}, sz{0} {}
Expression* ExpressionList::eval(Environment& env) const
{
    ExpressionList* exp_list = new ExpressionList();

    for (auto &exp : expressions)
    {
        exp_list->addExpressionBack(exp->eval(env));
    }

    return exp_list;
}
std::string ExpressionList::toString() const noexcept
{
    std::string result;
    for (const auto& expr : expressions)
    {
        result += (dynamic_cast<Unit*>(expr)) ? "" : expr->toString() + "\n";
    }
    return result;
}
void ExpressionList::addExpressionFront(Expression* expr)
{
    ++sz;
    expressions.push_front(expr);
}
void ExpressionList::addExpressionBack(Expression* expr)
{
    ++sz;
    expressions.push_back(expr);
}
std::vector<Expression*> ExpressionList::getVectorExpression() const
{
    std::vector<Expression*> expressions_vec;
    for (const auto& expr : expressions)
    {
        expressions_vec.push_back(expr);
    }
    return expressions_vec;
}
void ExpressionList::destroy() noexcept
{
    for (auto& expr : expressions)
    {
        if (expr != nullptr)
        {
            expr->destroy();
            delete expr;
            expr = nullptr;
        }
    }
    expressions.clear();
}