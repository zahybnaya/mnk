% define bounds on variables (+-inf allowed)
%
% u: column vector of lower bounds
% v: column vector of upper bounds
% u(k)<v(k) is required
%
u =[0.1; 0.001; 0.0; 0.01; 0.25 ;  -inf*ones(5,1) ;  0.01];
v =[10 ; 0.1  ; 1.0; 1.0;  4 ;inf*ones(5,1); 10];

dimension=10

