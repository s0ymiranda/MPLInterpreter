ma = {ve, ve2};

ve = [1,0];
ve2 = [0,9];

display(ma);

vec1 = [2,1,-3];
vec2 = [-1,3,2];
vec3 = [3,1,-3];

ma1 = {vec1,vec2,vec3};

ma2 = {vec,vec2,vec3};
ma1inv = INVERSE(ma2);

ma1tri = TRIDIAGONAL(ma2);

ma1eigen = REALEIGENVALUES(ma2);

ma1lu = MATRIXLU(ma2);

ma1det = DETERMINANT(ma2);


ma1inv2 = INVERSE({[2,1,-3],[-1,3,2],[3,1,-3]});
ma1tri2 = TRIDIAGONAL({[2,1,-3],[-1,3,2],[3,1,-3]});
ma1eigen2 = REALEIGENVALUES({[2,1,-3],[-1,3,2],[3,1,-3]});
ma1lu2 = MATRIXLU({[2,1,-3],[-1,3,2],[3,1,-3]});
ma1det2 = DETERMINANT({[2,1,-3],[-1,3,2],[3,1,-3]});

print(IDS);
display(ma1inv);
display(ma1tri);
display(ma1eigen);
display(ma1lu);
display(ma1det);
print(DIRECT);
display(ma1inv2);
display(ma1tri2);
display(ma1eigen2);
display(ma1lu2);
display(ma1det2);