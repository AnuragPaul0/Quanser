clc
clear
A = [0,1;0,0];
B = [0;0.418];
C = [1,0];
D = 0;
wcf_1 = 314.1593
wcf_2 = 62.8319
sys = ss(A,B,C,D);

Q = [1000000,0;0,1];
R = 1;

[K,S,e] = lqr(sys, Q, R);
sys1 =ss(A-B*K,B*K(1),C,D);
step(sys1)

