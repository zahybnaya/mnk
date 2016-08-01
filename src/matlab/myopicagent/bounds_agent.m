% define bounds on variables (+-inf allowed)
%
% u: column vector of lower bounds
% v: column vector of upper bounds
% u(k)<v(k) is required
% feature-drop(delta), lapse-rate,weighs0-4, act_scale
%
u =[0.0; 0.01; 0.25; 0.25; 0.25; 0.25; 0.25; 0.5];
v =[0.7; 0.5; 4.0; 4.0; 4.0;  4.0; 4.0; 10];
dimension=8

