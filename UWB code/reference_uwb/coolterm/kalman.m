anchorA = xlsread('2_anchor_raw2.xlsx','Sheet1');
anchorB = xlsread('2_anchor_raw2.xlsx','Sheet2');
%anchorA_error = abs(anchorA - 1.944);
%anchorB_error = abs(anchorB - 1.944);
anchorA_error = abs(anchorA - mean(anchorA));
anchorB_error = abs(anchorB - mean(anchorB));
m1 = mean(anchorA_error)
m2 = mean(anchorB_error)