#!/bin/python
#	
# mode: fixed (e.g., go on the entire range of values)

from sys import argv


def get_fit_params(model_file):  
	params = {}
	with open(model_file) as f:
		for line in f:
			if line.startswith('#'):
				continue
			vals=line.split('?')
			if len(vals)==2:
				print line	
				u,v,step=line[line.find('{')+1:line.find('}')].split(',')
				params[pname]={'u':u, 'v':v, 'step':step}
	return params
		
		




model_file=argv[1]
stimuli=argv[2]
num_of_data_sets=argv[3]
#TODO check if file exists and output usage message

parameters=get_fit_params(model_file)  #e.g., p1=?1{u,v} p2=?2{u,v}
print(parameters)
exit(1)
for param in parameters:
	for point in create_points(parameters):
		gen_model_file=create_generating_model_file(model_file,param,v) #all values are concrete (param=v & all the rest are getting values from a grid or a distribution).
		fake_data_file=execute_fake_data(stimuli,agent_file,param,v)
	create_fitting_job_script(model_file) # for fitting this model with the relevant data_file[s]


