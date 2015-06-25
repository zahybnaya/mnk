% define bounds on variables (+-inf allowed)
%
% u: column vector of lower bounds
% v: column vector of upper bounds
% u(k)<v(k) is required
%
u =[0.0; 0.01; 0.25; 0.25; 0.25; -inf*ones(7,1)];
v =[1.0; 1.0; 4.0; 4.0; 4.0;  inf*ones(7,1)];
dimension=12

