to = 0;
xo = 0;

num1 = 3;
num2 = 125;


div = num1/num2;
mul = div * var;

num3 = 0.6;

sum = num3 - mul;

tFinal = 30;

ode = ODEFIRST(sum,(to,xo),tFinal,var);

display(ode);