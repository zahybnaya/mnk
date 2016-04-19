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
L = 3*ones(10,1);
l = 2*ones(10,1);
load x0.mat -mat
consistent_times = [2 4 20]
prune_threshold = [0.1 3 10]
x0=x0([3:5 9:12 14],:)
x0 = [x0;consistent_times; prune_threshold ]

