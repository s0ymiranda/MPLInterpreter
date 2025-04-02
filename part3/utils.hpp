#pragma once

#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <forward_list>
#include <functional>
#include <limits>
#include <iomanip>
#include <string>

enum class DataType
{
    Pair,
    Vector,
    Matrix,
    Number,
    Variable,
    Impossible,
    Name
};

class Expression;
class Statement;

using Environment = std::forward_list<std::pair<char, Expression*>>;

class ASTNodeInterface
{
public:
    virtual ~ASTNodeInterface() noexcept {};
    virtual void destroy() noexcept = 0;
};