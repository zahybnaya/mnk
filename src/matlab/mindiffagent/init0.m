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
L = 3*ones(17,1);
l = 2*ones(17,1);
load x0.mat -mat
x0=x0(2:15,:)
stop_ratio =[0.01 1.0 3.0]
decrease_rate  =[0.1 0.4 1.0]
consecutive_times =[10 100 1000]
x0=[x0;stop_ratio;decrease_rate;consecutive_times] 
%x0 = [-10*ones(n,1) zeros(n,1) 10*ones(n,1)];

