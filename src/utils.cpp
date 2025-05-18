#include <utils.hpp>
#include <Expression.hpp>

std::string dataTypeToString(DataType d)
{
    switch (d)
    {
    case DataType::Pair:
        return "Pair";
    case DataType::Vector:
        return "Vector";
    case DataType::Matrix:
        return "Matrix";
    case DataType::Number:
        return "Number";
    case DataType::Name:
        return "Name";
    default:
        return "DataType Undefined";
    }
}

bool containsName(Expression* expr, const std::string& varName, Environment& env) noexcept
{
    if (expr == nullptr)
    {
        return false;
    }

    if (auto name = dynamic_cast<Name*>(expr))
    {
        return name->getName() == varName;
    }

    if (auto binary = dynamic_cast<BinaryExpression*>(expr))
    {
        return containsName(binary->getLeftExpression(), varName, env) || containsName(binary->getRightExpression(), varName, env);
    }

    if (auto unary = dynamic_cast<UnaryExpression*>(expr))
    {
        return containsName(unary->getExpression(), varName, env);
    }

    if (auto vec = dynamic_cast<Vector*>(expr))
    {
        for (auto e : vec->getVectorExpression())
        {
            if (containsName(e, varName, env))
            {
                return true;
            }
        }
    }

    if (auto mat = dynamic_cast<Matrix*>(expr))
    {
        for (auto e : mat->getMatrixExpression())
        {
            if (containsName(e, varName, env))
            {
                return true;
            }
        }
    }

    if (auto pair = dynamic_cast<Pair*>(expr))
    {
        return containsName(pair->getFirst(), varName, env) || containsName(pair->getSecond(), varName, env);
    }

    if (auto func = dynamic_cast<Function*>(expr))
    {
        return containsName(func->getExpression(), varName, env);
    }

    if (auto integral = dynamic_cast<Integral*>(expr))
    {
        auto exprs = integral->getExpressions();
        return containsName(std::get<0>(exprs), varName, env) ||
               containsName(std::get<1>(exprs), varName, env) ||
               containsName(std::get<2>(exprs), varName, env);
    }

    if (auto interp = dynamic_cast<Interpolate*>(expr))
    {
        auto exprs = interp->getExpressions();
        return containsName(std::get<0>(exprs), varName, env) ||
               containsName(std::get<1>(exprs), varName, env);
    }

    if (auto ode = dynamic_cast<ODEFirstOrderInitialValues*>(expr))
    {
        auto exprs = ode->getExpressions();
        return containsName(std::get<0>(exprs), varName, env) ||
               containsName(std::get<1>(exprs), varName, env) ||
               containsName(std::get<2>(exprs), varName, env) ||
               containsName(std::get<3>(exprs), varName, env);
    }

    if (auto root = dynamic_cast<FindRootBisection*>(expr))
    {
        auto exprs = root->getExpressions();
        return containsName(std::get<0>(exprs), varName, env) ||
               containsName(std::get<1>(exprs), varName, env) ||
               containsName(std::get<2>(exprs), varName, env) ||
               containsName(std::get<3>(exprs), varName, env);
    }

    if (auto list = dynamic_cast<ExpressionList*>(expr))
    {
        for (auto e : list->getVectorExpression())
        {
            if (containsName(e, varName, env))
            {
                return true;
            }
        }
    }

    return false;
}