**Core**
INVALID: [Specific problem] (expected [requirement], got [actual])
IMPOSSIBLE: [Operation] undefined for [condition]

INVALID: Invalid Input, expected [type]

**Addition/Subtraction**
IMPOSSIBLE: Matrix addition requires equal dimensions
INVALID: Cannot add/subtract [TypeA] with [TypeB]
INVALUD: Cannot add/substract non-value expressions

**Multiplication**
IMPOSSIBLE: Matrix multiplication requires cols(A)=rows(B)
INVALID: Cannot multiply [TypeA] with [TypeB]
INVALUD: Cannot multiply non-value expressions

**Division**
IMPOSSIBLE: Division by zero
INVALID: Matrix division requires square invertible matrix
INVALID: Cannot inverse matrix for division
INVALID: Cannot resolve matrix multiplication for division
INVALUD: Cannot divide non-value expressions

**Power/Roots**
IMPOSSIBLE: Undefined operation: 0 raised to non-positive power
IMPOSSIBLE: Negative root with even index
INVALID: Power/Square/Square Root operation requires numeric or name base and exponent

**Logarithms**
IMPOSSIBLE: Logarithm of non-positive number (arg=[value])
IMPOSSIBLE: Logarithm base=1
INVALID: Logarithm arguments must be numeric or names

**Trigonometric**
IMPOSSIBLE: Tangent undefined where cos(x)=0 (x=[value])
IMPOSSIBLE: Cotangent undefined where sin(x)=0 (x=[value])
INVALID: Trigonometric functions require numeric input measured in radians

**Vector**
INVALID: One or more elements in the vector could not be evaluated

**Matrix Functions**
INVALID: Empty matrix (0×0)
INVALID: Inconsistent row sizes
INVALID: Matrix arguments must be vectors or names
INVALID: One or more elements in the matrix could not be evaluated

INVALID: Expected a Matrix
IMPOSSIBLE: Matrix is singular (determinant=0)
INVALID: Expected a numeric value Matrix
INVALID: Non-square matrix [m×n] cannot be inverted/get eIGENVALUES/LU DECOMPOSED /Tridiagonal
INVALID: Cannot compute Real Eigenvalues

**Integral**
INVALID: Expected variable 'varName' in function funcName
INVALID: Expected that elements in the function evaluate to numeric values
INVALID: Expected Pair, got [typeA]
INVALID: Expected Pair, got different type
INVALID: Expected numeric values in the interval
INVALID: Integration variable must be a Name

**ODE Solving**
INVALID:  Expected variable 'varName' in function funcName
INVALID: Expected that elements in the function evaluate to numeric values
INVALID: Invalid arguments received
INVALID: Time interval must be ordered as [t_init, t_final] where t_final > t_init
INVALID: ODE variable must be a Name

**Interpolation**
INVALID: Expected a Vector
INVALID: Expected a Number for interpolation
INVALID: Interpolation requires vector of (x, y) pairs
INVALID: Expected numeric values in the Pair

**Name/Assigment**
INVALID: Recursive assignment detected for variable '[name]'
INVALID: Expected a Name for assignment

**Pair**
INVALID: Expected Pair, got [Type]
INVALID: Expected Pair, got different type
INVALID: Pair elements must be evaluable expressions

**FindRootBisection**
INVALID: Invalid arguments received
INVALID:  Expected variable 'varName' in function funcName
INVALID: Expected that elements in the function evaluate to numeric values
INVALID: Expected Pair, got [typeA]
INVALID: Expected Pair, got different type
INVALID: Expected numeric values in the interval
INVALID: Interval must be ordered as [init, final] where final > init
INVALID: Variable must be a Name
INVALID: Iteration limit must be a Number