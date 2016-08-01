%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% init0.m %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% for a self-defined initialization list, the user should
% write an m-script file init0.m containing a matrix x0 with n
% rows and at least 3 columns and two n-vectors l and L 
% the ith column of x0 contains the initialization list
% values for the ith coordinate, their number is L(i), and
% x0(i,l(i)) is the ith coordinate of the initial point
%
% feature-drop(delta), lapse-rate,weighs0-4, act_scale
%  
%
%
% self-defined initialization list
delta=[0.01 0.2 0.3]
lapserate=[0.01 0.1 0.3]
weight0=[0.5 1 2.0]
weight1=[0.5 1 2.0]
weight2=[0.5 1 2.0]
weight3=[0.5 1 2.0]
weight4=[0.5 1 2.0]
act_scale=[1.0 2.0 8.0]

L = 3*ones(8,1);
l = 2*ones(8,1);
x0=[delta;lapserate;weight0;weight1;weight2;weight3;weight4;act_scale]
%x0 = [-10*ones(n,1) zeros(n,1) 10*ones(n,1)];

