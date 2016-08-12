%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% init0.m %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% for a self-defined initialization list, the user should
% write an m-script file init0.m containing a matrix x0 with n
% rows and at least 3 columns and two n-vectors l and L 
% the ith column of x0 contains the initialization list
% values for the ith coordinate, their number is L(i), and
% x0(i,l(i)) is the ith coordinate of the initial point

% self-defined initialization list
L = 3*ones(11,1);
l = 2*ones(11,1);
prune_t=[0.002 5 10]
gamma=[0.001 0.04 0.1]
delta=[0.01 0.0009 0.3]
lapserate=[0.01 0.00002 0.3]
act_scale=[0.001 0.002 8.0]
weight0=[0.5 0.0007  2.0]
weight1=[0.5 0.0009 2.0]
weight2=[0.5 0.0002 2.0]
weight3=[0.5 0.005 2.0]
weight4=[0.5 0 2.0]
exploration_constant=[0.0100 0.5000 9.00]
x0=[prune_t; gamma; delta;lapserate;act_scale;weight0;weight1;weight2;weight3;weight4;exploration_constant]


