% define bounds on variables (+-inf allowed)
%
% u: column vector of lower bounds
% v: column vector of upper bounds
% u(k)<v(k) is required
%
u =[2; 0.001; 0.0; 0.01; -inf*ones(5,1) ; 0.001];
v =[8; 0.1; 1.0; 0.4;  inf*ones(5,1); 0.5];
dimension=10

