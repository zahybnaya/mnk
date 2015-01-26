%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% split.m %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% function [xbest,fbest,xmin,fmi,ipar,level,ichild,f,flag,ncall] = 
% split(fcn,data,i,s,smax,par,n0,u,v,x,y,x1,x2,z,xmin,fmi,ipar,level,
% ichild,f,xbest,fbest,stop,prt)
% splits box # par at level s in its ith coordinate into two or three
% children and inserts its children and their parameters in the list
%
% Input:
% fcn = 'fun'  	name of function fun(data,x), x an n-vector
% data		data vector
% i            	splitting index
% s            	level of the box to be split
% smax         	number of levels
% par          	label of the box
% n0(1:n)      	coordinate i has been split n0(i) times in the history
%              	of the box
% [u,v]        	original box
% x(1:n)       	base vertex of the box
% y(1:n)       	opposite vertex
% x1(1:n), x2(1:n) 'neighbors' of x such that x(i), x1(i), x2(i) are
%		pairwise distinct for i = 1,...,n
% z(1:2)       	z(1) = value of the ith coordinate of the base vertex
%              	z(2) = splitting value
%              	z(2) ~= y(i) split into 3 children
%              	z(2) = y(i)  split into 2 children
% xmin(1:n,:)  	columns are the base vertices of the boxes in the base 
%              	list
% fmi          	fmi(j) is the function value at xmin(:,j)
% ipar         	vector containing the labels of the parents of the boxes
%              	not in the `shopping basket'
% level        	vector containing their levels
% ichild       	the absolute values of this vector specify which child 
%              	they are; ichild(j) < 0 if box j was generated by 
%              	splitting according to the init. list (in the init.
%              	procedure or later) and ichild(j) > 0 otherwise
% f            	f(1,j) is the base vertex function value of box j and
%              	f(2,j) contains the function value at its splitting 
%              	value (if box j has already been split by default)
% xbest(1:n)  	current best vertex
% fbest    	current best function value
% stop          stop(1) in ]0,1[:  relative error with which the known 
%		 global minimum of a test function should be found
%		 stop(2) = fglob known global minimum of a test function
%		 stop(3) = safeguard parameter for absolutely small 
%		 fglob
%		stop(1) >= 1: the program stops if the best function
%		 value has not been improved for stop(1) sweeps
%		stop(1) = 0: the user can specify a function value that
%		 should be reached
%                stop(2) = function value that is to be achieved
% prt		print level
% Output:
% xbest(1:n) 	current best vertex
% fbest    	current best function value
% xmin(1:n,:)  	as before plus newly created boxes
% fmi          	as before plus newly created boxes 
% ipar         	as before plus newly created boxes
% level        	as before plus newly created boxes
% ichild       	as before plus newly created boxes
% f            	as before plus newly created boxes; in particular 
%              	f(2,par) and f(1,:) for the newly created boxes are
%              	defined in this program
% flag         	output flag
%              	= 0 if the known global minimum of a test function has 
%                   been found with the required relative error
%               = 1 otherwise  
% ncall		number of function evaluations
%
% Uses the following m-files:
% bounds.m
% chrelerr.m
% chvtr.m
% genbox.m
% split1.m
% updtoptl.m
% updtrec.m
%
function [xbest,fbest,xmin,fmi,ipar,level,ichild,f,flag,ncall] = split(fcn,data,i,s,smax,par,n0,u,v,x,y,x1,x2,z,xmin,fmi,ipar,level,ichild,f,xbest,fbest,stop,prt)  
global nbasket nboxes nglob nsweep nsweepbest record xglob 
% nbasket   	counter for points in the 'shopping basket'
% nboxes      	counter for boxes not in the 'shopping basket'
% nglob       	number of global minimizers of a test function in [u,v]
% nsweep      	sweep counter
% record(1:smax-1) record(i) points to the best non-split box at level i
% xglob(1:n,1:nglob)  xglob(:,i), i=1:nglob, are the global minimizers 
% 		of a test function 

ncall = 0;
n = length(x);
iopt = [];
if prt > 1
  [w1,w2] =  bounds(n,n0,x,y,u,v);
  for iglob = 1:nglob
    if w1 <= xglob(:,iglob) & xglob(:,iglob) <= w2
      iopt = [iopt, iglob];
    end
  end     
end
flag = 1;
x(i) = z(2);
f(2,par) = feval(fcn,data,x);
ncall = ncall + 1;
if f(2,par) < fbest
  fbest = f(2,par);
  xbest = x;
  nsweepbest = nsweep;
  if stop(1) > 0 & stop(1) < 1
    flag = chrelerr(fbest,stop);
  elseif stop(1) == 0
    flag = chvtr(fbest,stop(2));
  end
  if ~flag,return,end
end
splval = split1(z(1),z(2),f(1,par),f(2,par));
if s + 1 < smax 
  if f(1,par) <= f(2,par)
    nboxes = nboxes + 1;
    [ipar(nboxes),level(nboxes),ichild(nboxes),f(1,nboxes)] = genbox(par,s+1,1,f(1,par));
    updtrec(nboxes,level(nboxes),f(1,:));
    if prt > 1,
      updtoptl(i,z(1),splval,iopt,s+1,f(1,par));
    end 
    if s + 2 < smax 
      nboxes = nboxes + 1;
      [ipar(nboxes),level(nboxes),ichild(nboxes),f(1,nboxes)] = genbox(par,s+2,2,f(2,par));
      updtrec(nboxes,level(nboxes),f(1,:));
    else
      x(i) = z(2);
      nbasket = nbasket + 1;
      xmin(:,nbasket) = x;
      fmi(nbasket) = f(2,par);
    end
    if prt > 1,
      updtoptl(i,splval,z(2),iopt,s+2,f(2,par));
    end 
  else
    if s + 2 < smax
      nboxes = nboxes + 1;
      [ipar(nboxes),level(nboxes),ichild(nboxes),f(1,nboxes)] = genbox(par,s+2,1,f(1,par));
      updtrec(nboxes,level(nboxes),f(1,:));
    else
      x(i) = z(1);
      nbasket = nbasket + 1;
      xmin(:,nbasket) = x;
      fmi(nbasket) = f(1,par);
    end
    if prt > 1,
      updtoptl(i,z(1),splval,iopt,s+2,f(1,par));
    end 
    nboxes = nboxes + 1;
    [ipar(nboxes),level(nboxes),ichild(nboxes),f(1,nboxes)] = genbox(par,s+1,2,f(2,par));
    updtrec(nboxes,level(nboxes),f(1,:));
    if prt > 1,
      updtoptl(i,splval,z(2),iopt,s+1,f(2,par));
    end 
  end
  if z(2) ~= y(i)
% if the third box is larger than the smaller of the other two boxes,
% it gets level s + 1; otherwise it gets level s + 2
    if abs(z(2)-y(i)) > abs(z(2)-z(1))*(3-sqrt(5))*0.5
      nboxes = nboxes + 1;
      [ipar(nboxes),level(nboxes),ichild(nboxes),f(1,nboxes)] = genbox(par,s+1,3,f(2,par));
      updtrec(nboxes,level(nboxes),f(1,:));
      if prt > 1,
        updtoptl(i,z(2),y(i),iopt,s+1,f(2,par));
      end 
    else
      if s + 2 < smax
        nboxes = nboxes + 1;
        [ipar(nboxes),level(nboxes),ichild(nboxes),f(1,nboxes)] = genbox(par,s+2,3,f(2,par));
        updtrec(nboxes,level(nboxes),f(1,:));
      else
        x(i) = z(2);
        nbasket = nbasket + 1;
        xmin(:,nbasket) = x;
        fmi(nbasket) = f(2,par);
      end
      if prt > 1,
        updtoptl(i,z(2),y(i),iopt,s+2,f(2,par));
      end 
    end
  end
else
  x(i) = z(1);
  nbasket = nbasket + 1;
  xmin(:,nbasket) = x;
  fmi(nbasket) = f(1,par);
  x(i) = z(2);
  nbasket = nbasket + 1;
  xmin(:,nbasket) = x;
  fmi(nbasket) = f(2,par);
  if prt > 1,
    updtoptl(i,z(1),splval,iopt,smax,f(1,par));
    updtoptl(i,splval,z(2),iopt,smax,f(2,par));
    if z(2) ~= y(i)
      updtoptl(i,z(2),y(i),iopt,smax,f(2,par));
    end
  end
end
