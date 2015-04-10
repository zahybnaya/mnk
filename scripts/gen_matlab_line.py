
#!/bin/python 
# gets a fitted file (e.g., ...fake_uctagent_400_DS1/mcsresults.mat) finds the model file and prints the relevant values of the parameters
# returns a call of type 'param_recovery(['p1'; 'p2'; 'p3'] , [0.11 ; 0.21 ; 0.31] , '$FITTED_FILE' , '$DS')' 
from sys import argv 


def get_fit_params(model_file):  
	other_lines=[]
	params = {}
	with open(model_file) as f:
		for line in f:
			if line.startswith('#') or line.isspace() or line=='':
				continue
			vals=line.split('?')
			if len(vals)==2:
				pname=line.split('=')[0].strip()
				ind=vals[1].split('{')[0]
				u,v,step=line[line.find('{')+1:line.find('}')].split(',')
				params[pname]={'u':float(u), 'v':float(v), 'step':float(step), 'ind':int(ind)}
			else:
				other_lines.append(line)
	return other_lines,params
		
fitted_file=argv[1]
_,agent,point,ds=fitted_file.split('fake')[1].split('/')[0].split('_')
model_file='../agents/'+agent
fake_model_file='../agents/'+agent+'___fake_'+point   #../agents/uctagent___fake_10

_,params = get_fit_params(model_file)
generating_params,_= get_fit_params(fake_model_file)
print generating_params
gen_param_dict = dict([ (p.split('=')[0].strip(),p.split('=')[1].strip())  for p in generating_params if not p.startswith('#') ])

sorted_params =sorted(params, key=lambda x:params[x]['ind'])
sorted_gen_vals = [gen_param_dict[p] for p in sorted_params]
fitting_param_string= str(sorted_params).replace(',',';').replace('[','{').replace(']','}')
gen_val_string= str(sorted_gen_vals).replace(',',';').replace('\'','')


# returns a call of type 'param_recovery(['p1'; 'p2'; 'p3'] , [0.11 ; 0.21 ; 0.31] , '$FITTED_FILE' , '$DS')' 
exec_command='param_recovery('+fitting_param_string +','+ gen_val_string + ',\'' + fitted_file + '\',\'' +str(ds)+ '\',\''+agent+'\',' + point +' )'		
print exec_command
