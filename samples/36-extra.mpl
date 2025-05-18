log1 = LN(EULER);
display(log1);
log2 = LOG(4,2);
display(log2);

vector = [  (0,1.792),
            (5+5,1.308),
            (30, 0.801),
            (50,0.549),
            (70,0.406),
            (90,0.317),
            (100,0.284)];

val = 15 + 2;
in = INTERPOLATE([(0,1.792)], val);
in2 = INTERPOLATE(vector, COS(2));
display(in);
display(in2);