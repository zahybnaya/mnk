% define bounds on variables (+-inf allowed)
%
% u: column vector of lower bounds
% v: column vector of upper bounds
% u(k)<v(k) is required
%
u =[0.001; 0.0; 0.01; -inf*ones(5,1) ; 2 ; 0.1];
v =[0.1; 1.0; 1.0; inf*ones(5,1); 20 ; 10];
dimension=9

