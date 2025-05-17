ma = {ve, ve2};

ve = [1,0];
ve2 = [0,9];

display(ma);

vec1 = [2,1,-3];
vec2 = [-1,3,2];
vec3 = [3,1,-3];

ma1 = {vec1,vec2,vec3};

ma1inv = INVERSE(ma1);

display(ma1inv);
