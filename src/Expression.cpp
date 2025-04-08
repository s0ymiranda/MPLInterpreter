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
                auto num = dynamic_cast<Number*>(pair.second->eval(env));
                if (num != nullptr)
                {
                    return num;
                }
                return pair.second->eval(env);
            }
        }
    }
    return const_cast<Variable*>(this);
    //return new Variable(variable);
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
                //std::unique_ptr<Expression> exp(pair.second->eval(env));
                Expression* exp = pair.second->eval(env);
                auto num = dynamic_cast<Number*>(exp);
                if (num != nullptr)
                {
                    return num;
                }
                return exp;
            }
        }
    }
    return const_cast<Name*>(this);
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
    std::unique_ptr<Expression> exp1(leftExpression->eval(env));
    std::unique_ptr<Expression> exp2(rightExpression->eval(env));

    Value* element1 = dynamic_cast<Value*>(exp1.get());
    Value* element2 = dynamic_cast<Value*>(exp2.get());

    if (element1 == nullptr || element2 == nullptr)
    {
        return new Addition(exp1.release(), exp2.release());
    }

    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return new Addition(exp1.release(), exp2.release());
    }

    if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix)
    {
        auto matrix1 = dynamic_cast<Matrix*>(element1)->getMatrixExpression();
        auto matrix2 = dynamic_cast<Matrix*>(element2)->getMatrixExpression();

        if (matrix1.size() != matrix2.size())
        {
            return new Impossible();
        }

        std::vector<Expression*> newMatrix;
        for (size_t i = 0; i < matrix1.size(); ++i)
        {
            auto current_vec_mat1 = dynamic_cast<Vector*>(matrix1[i]);
            auto current_vec_mat2 = dynamic_cast<Vector*>(matrix2[i]);

            if (!current_vec_mat1 || !current_vec_mat2)
            {
                delete current_vec_mat1;
                delete current_vec_mat2;
                return nullptr;
            }

            if (current_vec_mat1->size() != current_vec_mat2->size())
            {
                delete current_vec_mat1;
                delete current_vec_mat2;
                return new Impossible();
            }

            std::vector<Expression*> newVec;
            auto row1 = current_vec_mat1->getVectorExpression();
            auto row2 = current_vec_mat2->getVectorExpression();

            for (size_t j = 0; j < current_vec_mat1->size(); ++j)
            {
                newVec.push_back(new Addition(row1[j], row2[j]));
            }

            newMatrix.push_back(new Vector(newVec));
        }

        auto result = new Matrix(newMatrix);
        return result->eval(env);
    }

    auto num1 = dynamic_cast<Number*>(exp1.get());
    auto num2 = dynamic_cast<Number*>(exp2.get());

    if (num1 == nullptr || num2 == nullptr)
    {
        return nullptr;
    }

    double resultValue = num1->getNumber() + num2->getNumber();
    return new Number(resultValue);
}

std::string Addition::toString() const noexcept
{
    return leftExpression->toString() + " + " + rightExpression->toString();
}

//Subtraction
Expression* Substraction::eval(Environment& env) const
{
    std::unique_ptr<Expression> exp1(leftExpression->eval(env));
    std::unique_ptr<Expression> exp2(rightExpression->eval(env));

    Value* element1 = dynamic_cast<Value*>(exp1.get());
    Value* element2 = dynamic_cast<Value*>(exp2.get());

    if (element1 == nullptr || element2 == nullptr)
    {
        return new Substraction(exp1.release(), exp2.release());
    }

    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return new Substraction(exp1.release(), exp2.release());
    }

    if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix)
    {
        auto matrix1 = dynamic_cast<Matrix*>(element1)->getMatrixExpression();
        auto matrix2 = dynamic_cast<Matrix*>(element2)->getMatrixExpression();

        if (matrix1.size() != matrix2.size())
        {
            return new Impossible();
        }

        std::vector<Expression*> newMatrix;
        for (size_t i = 0; i < matrix1.size(); ++i)
        {
            auto current_vec_mat1 = dynamic_cast<Vector*>(matrix1[i]);
            auto current_vec_mat2 = dynamic_cast<Vector*>(matrix2[i]);

            if (!current_vec_mat1 || !current_vec_mat2)
            {
                delete current_vec_mat1;
                delete current_vec_mat2;
                return nullptr;
            }

            if (current_vec_mat1->size() != current_vec_mat2->size())
            {
                delete current_vec_mat1;
                delete current_vec_mat2;
                return new Impossible();
            }

            std::vector<Expression*> newVec;
            auto row1 = current_vec_mat1->getVectorExpression();
            auto row2 = current_vec_mat2->getVectorExpression();

            for (size_t j = 0; j < current_vec_mat1->size(); ++j)
            {
                newVec.push_back(new Substraction(row1[j], row2[j]));
            }

            newMatrix.push_back(new Vector(newVec));
        }

        auto result = new Matrix(newMatrix);
        return result->eval(env);
    }

    auto num1 = dynamic_cast<Number*>(exp1.get());
    auto num2 = dynamic_cast<Number*>(exp2.get());

    if (num1 == nullptr || num2 == nullptr)
    {
        return nullptr;
    }

    double resultValue = num1->getNumber() - num2->getNumber();
    return new Number(resultValue);
}
std::string Substraction::toString() const noexcept
{
    return leftExpression->toString() + " - " + rightExpression->toString();
}

//Multiplication
Expression* Multiplication::eval(Environment& env) const
{
    std::unique_ptr<Expression> exp1(leftExpression->eval(env));
    std::unique_ptr<Expression> exp2(rightExpression->eval(env));
    auto element1 = dynamic_cast<Value*>(exp1.get());
    auto element2 = dynamic_cast<Value*>(exp2.get());

    if (element1 == nullptr || element2 == nullptr)
    {
        return new Multiplication(exp1.release(), exp2.release());
    }
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return new Multiplication(exp1.release(), exp2.release());
    }
    if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix)
    {
        auto matrix1 = dynamic_cast<Matrix*>(element1)->getMatrixExpression();
        auto matrix2 = dynamic_cast<Matrix*>(element2)->getMatrixExpression();
        std::vector<Expression*> newMatrix;
        auto first_row_mat1 = dynamic_cast<Vector*>(matrix1[0]);
        if (first_row_mat1 == nullptr)
        {
            return nullptr;
        }
        if (first_row_mat1->size() != matrix2.size())
        {
            // std::shared_ptr<Expression> imp = std::make_shared<Impossible>();
            // return imp;
            return new Impossible();
        }
        for (size_t i = 0; i < matrix1.size(); ++i)
        {
            std::vector<Expression*> newVec;
            auto first_row_mat2 = dynamic_cast<Vector*>(matrix2[0]);
            if (first_row_mat2 == nullptr)
            {
                return nullptr;
            }
            auto n_row_matrix1 = dynamic_cast<Vector*>(matrix1[i]);
            if (n_row_matrix1 == nullptr)
            {
                return nullptr;
            }
            for (size_t j = 0; j < first_row_mat2->size(); ++j)
            {
                std::unique_ptr<Expression> acc(new Number(0.0));
                for (size_t k = 0; k < n_row_matrix1->size(); ++k)
                {
                    auto k_row_matrix2 = dynamic_cast<Vector*>(matrix2[k]);
                    if (k_row_matrix2 == nullptr)
                    {
                        return nullptr;
                    }
                    std::unique_ptr<Vector> temp1(new Vector(newVec));
                    std::unique_ptr<Vector> temp2(new Vector(newVec));
                    std::unique_ptr<Multiplication> mul(new Multiplication(n_row_matrix1->getVectorExpression()[k], k_row_matrix2->getVectorExpression()[j]));
                    acc = std::make_unique<Addition>(acc.get(), mul.release());
                }
                newVec.push_back(acc.release());
            }
            std::unique_ptr<Vector> temp(new Vector(newVec));
            newMatrix.push_back(temp.release());
        }
        return std::make_shared<Matrix>(newMatrix)->eval(env);
    }
    if (element1->getDataType() == DataType::Number && element2->getDataType() == DataType::Matrix)
    {
        auto num = dynamic_cast<Number*>(element1);
        auto matrix1 = dynamic_cast<Matrix*>(element2)->getMatrixExpression();
        std::vector<Expression*> newMatrix;
        for (Expression* vec : matrix1)
        {
            auto v = dynamic_cast<Vector*>(vec);
            if (v == nullptr)
            {
                return nullptr;
            }
            std::vector<Expression*> new_vec{};
            for (Expression* exp : v->getVectorExpression())
            {
                std::unique_ptr<Expression> newVal = std::make_unique<Multiplication>(num,exp);
                new_vec.push_back(newVal.release());
            }
            std::unique_ptr<Vector> temp(new Vector(new_vec));
            newMatrix.push_back(temp.release());
        }
        return std::make_shared<Matrix>(newMatrix)->eval(env);
    }

    auto num1 = dynamic_cast<Number*>(exp1.get());
    auto num2 = dynamic_cast<Number*>(exp2.get());
    if (num1 == nullptr || num2 == nullptr)
    {
        return nullptr;
    }
    double result = num1->getNumber() * num2->getNumber();
    return new Number(result);
}
std::string Multiplication::toString() const noexcept
{
    return "("+ leftExpression->toString()+ ") * (" + rightExpression->toString() +")";
}

//Division
Expression* Division::eval(Environment& env) const
{
    return nullptr;
}
std::string Division::toString() const noexcept
{
    return "(" + leftExpression->toString() + ")/(" + rightExpression->toString() + ")";
}

//Power
Expression* Power::eval(Environment& env) const
{
    return nullptr;
}
std::string Power::toString() const noexcept
{
    return "("+ leftExpression->toString() + ")^(" + rightExpression->toString() + ")";
}

//NaturalLogarithm
Expression* NaturalLogarithm::eval(Environment& env) const
{
    return nullptr;
}
std::string NaturalLogarithm::toString() const noexcept
{
    return "ln(" + expression->toString() + ")";
}

//Logarithm
Expression* Logarithm::eval(Environment& env) const
{
    return nullptr;
}
std::string Logarithm::toString() const noexcept
{
    return "lg" + leftExpression->toString() + "(" + rightExpression->toString() + ")";
}

// Square Root
Expression* SquareRoot::eval(Environment& env) const
{
    return nullptr;
}
std::string SquareRoot::toString() const noexcept
{
    return "√(" + expression->toString() + ")";
}

// Root
Expression* Root::eval(Environment& env) const
{
    return nullptr;
}
std::string Root::toString() const noexcept
{
    return "(" + rightExpression->toString() + ")^√(" + leftExpression->toString() + ")";
}

//Sine
Expression* Sine::eval(Environment& env) const
{
    return nullptr;
}
std::string Sine::toString() const noexcept
{
    return "Sin(" + expression->toString() + ")";
}

//Cosine
Expression* Cosine::eval(Environment& env) const
{
    return nullptr;
}
std::string Cosine::toString() const noexcept
{
    return "cos(" + expression->toString() + ")";
}

//Tangent
Expression* Tangent::eval(Environment& env) const
{
    return nullptr;
}
std::string Tangent::toString() const noexcept
{
    return "Tag(" + expression->toString() + ")";
}

//Cotangent
Expression* Cotangent::eval(Environment& env) const
{
    return nullptr;
}
std::string Cotangent::toString() const noexcept
{
    return "Ctg(" + expression->toString() + ")";
}

//Pair
Pair::Pair(Expression* _first, Expression* _second) : Value(DataType::Pair), first{_first}, second{_second} {}
Expression* Pair::eval(Environment& env) const
{
    return nullptr;
}
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
    return nullptr;
}
std::string PairFirst::toString() const noexcept
{
    return "";
}

//PairSecond
Expression* PairSecond::eval(Environment& env) const
{
    return nullptr;
}
std::string PairSecond::toString() const noexcept
{
    return "";
}

//Vector
Vector::Vector(std::vector<Expression*> _vectorExpression) : Value(DataType::Vector), vectorExpression(_vectorExpression) {}
Expression* Vector::eval(Environment& env) const
{
    std::vector<Expression*> new_vector;
    for (auto exp : vectorExpression)
    {
        auto element = exp->eval(env);
        if (element == nullptr)
        {
            for (auto& ptr : new_vector)
            {
                delete ptr;
            }
            return nullptr;
        }
        new_vector.push_back(element);
    }
    return new Vector(new_vector);
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
Matrix::Matrix(std::vector<Expression*> _matrixExpression) : Value(DataType::Matrix), matrixExpression(_matrixExpression) {}
Expression* Matrix::eval(Environment& env) const
{
    std::vector<Expression*> new_matrix;
    std::unique_ptr<Expression> temp, element;
    Vector* first_row = dynamic_cast<Vector*>(matrixExpression[0]);
    if (first_row == nullptr)
    {
        auto is_id = dynamic_cast<Name*>(matrixExpression[0]);
        if (is_id)
        {
            first_row = dynamic_cast<Vector*>(is_id->eval(env));
        }
        if (first_row == nullptr)
        {
            return nullptr;
        }
    }
    size_t row_size = first_row->size();
    for (Expression* vec : matrixExpression)
    {
        Vector* row = dynamic_cast<Vector*>(vec);
        if (row == nullptr)
        {
            auto is_id = dynamic_cast<Name*>(vec);
            if (is_id)
            {
                auto temp = is_id->eval(env);
                row = dynamic_cast<Vector*>(temp);
            }
            if (row == nullptr)
            {
                return nullptr;
            }
        }
        if (row->size() != row_size)
        {
            return nullptr;
        }
        std::vector<Expression*> new_vector;
        for (Expression* exp : row->getVectorExpression())
        {
            auto element = exp->eval(env);
            auto num = dynamic_cast<Number*>(element);
            if (num == nullptr)
            {
                new_vector.push_back(element);
            }
            else
            {
                new_vector.push_back(num);
            }
        }
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
Expression* InverseMatrix::eval(Environment& env) const
{
    return nullptr;
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
Expression* MatrixLU::eval(Environment& env) const
{
    return nullptr;
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
Expression* TridiagonalMatrix::eval(Environment& env) const
{
    return nullptr;
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
Expression* RealEigenvalues::eval(Environment& env) const
{
    return nullptr;
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
    return nullptr;
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
    return nullptr;
}
std::string Function::toString() const noexcept
{
    return expression->toString();
}

//Integral
Integral::Integral(Expression* _interval, Expression* _function, Expression* _variable) : interval(_interval), function(_function), variable(_variable) {}
Expression* Integral::eval(Environment& env) const
{
    return nullptr;
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
    return nullptr;
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
Expression* ODEFirstOrderInitialValues::eval(Environment& env) const
{
    return nullptr;
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
Expression* FindRootBisection::eval(Environment& env) const
{
    return nullptr;
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
    std::unique_ptr<Expression> exp(expression->eval(env));
    std::cout << exp->toString();
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
    std::cout << message;
    return new Unit();
}
std::string Print::toString() const noexcept
{
    return "Print(" + message + ")";
}
void Print::destroy() noexcept {}

Expression* Assigment::eval(Environment& env) const
{
    //std::unique_ptr<Expression> exp(rightExpression->eval(env));
    Expression* exp = rightExpression->eval(env);

    Name* leftName = dynamic_cast<Name*>(leftExpression);
    if (leftName != nullptr)
    {
        env.push_front(std::make_pair(leftName->getName(), exp));
        return new Unit();
    }

    Variable* leftVar = dynamic_cast<Variable*>(leftExpression);
    if (leftVar != nullptr)
    {
        env.push_front(std::make_pair(std::string(1, leftVar->getVariable()), exp));
        return new Unit();
    }

    return nullptr;
}
std::string Assigment::toString() const noexcept
{
    return leftExpression->toString() + " = " + rightExpression->toString();
}

//Expression List
ExpressionList::ExpressionList() : expressions{}, sz{0} {}
Expression* ExpressionList::eval(Environment& env) const
{
    std::unique_ptr<ExpressionList> exp_list(new ExpressionList());

    for (auto &exp : expressions)
    {
        exp_list->addExpressionBack(exp->eval(env));
    }

    return exp_list.release();
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