function generate_times(filename)
    c=50;
    %this controls the expected total computational time
    
    out=load(filename);
    N=out(1,5)+1;
    %Number of trials
    
    L=[0 cumsum(1./(1:1e6))];
    x=linspace(1e-6,1-1e-6,1e6);
    dilog=pi^2/6+cumsum(log(x)./(1-x))/length(x);

    l=accumarray(out(:,1)+1,L(out(:,2)))./histc(out(:,1)+1,1:N);
    %negative loglik estimate for each trial
    
    p=exp(-l);
    %convert to probability estimate
    
    lambda=c/mean(interp1(x,sqrt(dilog./x),p,'spline','extrap'));
    %lagrange multiplier to enforce computational time 
    n=lambda*interp1(x,sqrt(x.*dilog),p,'spline','extrap');
    %times for each trial
    dlmwrite([filename '.times'],max(1,uint8(n)),'\n')
end
