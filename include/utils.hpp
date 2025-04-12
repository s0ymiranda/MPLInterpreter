#pragma once

#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <forward_list>
#include <list>
#include <functional>
#include <limits>
#include <iomanip>
#include <string>
#include <string_view>

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

using Environment = std::forward_list<std::pair<std::string, Expression*>>;
//using Environment = std::forward_list<std::pair<std::string_view, Expression*>>;