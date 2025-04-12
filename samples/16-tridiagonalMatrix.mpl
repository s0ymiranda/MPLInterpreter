vec1 = [2,1,-3];
vec2 = [-1,3,2];
vec3 = [3,1,-3];

ma1 = {vec1,vec2,vec3};

trid = TRIDIAGONAL(ma1);
print(Original);
display(ma1);
print(Tridiagonal);
display(trid);

print(l);
print(Prueba2);
print(l);
vec4 = [4,3,2,1];
vec5 = [3,3,2,1];
vec6 = [2,2,2,1];
vec7 = [1,1,1,1];

ma2 = {vec4,vec5,vec6,vec7};

trid2 = TRIDIAGONAL(ma2);

print(Original);
display(ma2);
print(Tridiagonal);
display(trid2);