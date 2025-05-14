to = 0;
tf = 1;

interval = (to,tf);


part1 = 0.1 * (letter^(3));
part2 = -5 * (letter^(2));
part3 = -1 * (letter) + 4;

part4 = part3 + EULER^(-1*letter);

sum = part1 + part2 - part4;

display(sum);
bisection = BISECTIONROOT(interval,sum,letter);

display(bisection);