function  param_recovery( param_list, gen_values, fitting_file, ds)
% receiveds the param_list (ordered), the genereated_values (from the fitting file),
% the fitting_file (with xbest), the DS number and reports to file
load(fitting_file) %gets the xbest
for p_ind = 1:length(param_list)
    param = param_list(p_ind, :)
    gen_val = gen_values(p_ind)
    fit_val = xbest(p_ind)
    fid = fopen('params.csv', 'a+');
    %param, gen_value, fitted_value, ds
    fprintf(fid, '%s , %f , %f , %d\n', param,gen_val, fit_val, ds)
    fclose(fid);
end

