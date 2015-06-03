function  model_recovery(loglik, number_of_parameters, fitting_file, ds, model, point)
load(fitting_file) %gets the xbest and 
gofs = [AIC,BIC]
for gof in gofs:
    g=gof(loglik, number_of_parameters)
    fid = fopen('model_gofs.csv', 'a+')
    %generating_model, fitted_model, data_set , type_of_gof , value_of_gof
    fprintf(fid, '%s , %f , %f , %s, %s, %d\n', param,gen_val, fit_val, ds, model,point)
    fclose(fid);
end


function m = AIC(loglic, number_of_parameters)
    m = 2*loglic -2*number_of_parameters
end 

function m = BIC(loglic, number_of_parameters)
    m = 2*loglic -2*number_of_parameters
end
