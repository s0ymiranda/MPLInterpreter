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

INVALID: Matrix multiplication dimension mismatch
INVALID: Matrix addition requires equal dimensions
INVALID: Expected a Matrix
IMPOSSIBLE: Matrix is singular (determinant=0)
INVALID: Non-square matrix ([m×n] cannot be inverted/get eIGENVALUES/LU DECOMPOSED)
INVALID: Matrix must be symmetric for tridiagonal form
INVALID: Matrix contains non-numeric elements
IMPOSSIBLE: Matrix is not positive definite

**Integral**
INVALID: Integral bounds must be numeric
INVALID: Integration variable must be identifier
IMPOSSIBLE: Integral diverges in interval [a,b]

**ODE Solving**
INVALID: ODE function must use the specified variable [variable_name]
INVALID: Initial condition must be pair
INCALID: ODE function not contains the variable
INVALID: time interval must be ordered as [t_init, t_final] where t_final > t_init

**Interpolation**
IMPOSSIBLE: Extrapolation beyond data range

**Recursion**
INVALID: Recursive assignment detected for variable '[name]'

**Pair**\
INVALID: Expected Pair, got [Type]
INVALID: Expected Pair, got different type
INVALID: Pair elements must be evaluable expressions