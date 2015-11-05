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
L = 3*ones(15,1);
l = 2*ones(15,1);
load x0.mat -mat
stop_threshold = [0 4 10]
prune_threshold = [0 4 10]
x0=x0(3:15,:)
x0 = [x0;stop_threshold; prune_threshold ]
