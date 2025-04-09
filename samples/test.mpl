4 + 7;
'b' = 5;
test = 'b';
7 * test - 2;

b = [2, 3, 10];
display(b);


'b' = 3;
display(test);

vec1 = [2,3];
vec2 = [4,19];
ma1 = {vec1,vec2};

vec3 = [1,100];
vec4 = [3,9];
ma2 = {vec3,vec4};

vec5 = [13,57];
vec6 = [34,74];
ma3 = {vec5,vec6};

sum2 = ma1 + ma2;

sum3 = sum2 + ma3;
display(sum3 - ma1);