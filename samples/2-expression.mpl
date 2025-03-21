num1 = 2;
var = 'A';
sum = num1 + var;
sub = num1 - sum;
mul = sub * var;
div = mul / 10;
func = div;

display(func);
var1 = 'x';
pow = var1^2;
sum1 = pow + var1 + LOG(10,var1);
fun2 = sum1;

to = 0;
tf = 10;

interval = (to,tf);

letter = 'x';
sum2 = letter + 2;

integral = INTEGRAL(interval, sum2, letter);

xo = 0;
sum3 = -3/125 * letter + 0.6;
tFinal = 30;

ode = ODEFIRST(sum3,(to,xo), tFinal,letter);

sum_test = pow + var1 + LN(var1);