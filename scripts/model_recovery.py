#!/bin/python
#	
# mode: fixed (e.g., go on the entire range of values)

from sys import argv
from copy import copy
from itertools import product
from decimal import Decimal


def get_fit_params(model_file):  
	other_lines=[]
	params = {}
	with open(model_file) as f:
		for line in f:
			if line.startswith('#'):
				continue
			vals=line.split('?')
			if len(vals)==2:
				pname=line.split('=')[0].strip()
				u,v,step=line[line.find('{')+1:line.find('}')].split(',')
				params[pname]={'u':float(u), 'v':float(v), 'step':float(step)}
			else:
				other_lines+=line
	return other_lines,params
		
		

def print_usage():
	print 'usage: {0} <model_file> <stimuli> <number-of-datasets>'.format(argv[0])
	exit(-1)


def val_gen(u,v,step):
	round_dig = -Decimal(str(step)).as_tuple().exponent
	val = u
	while val < v:
		val+=step
		yield round(val,round_dig)



def create_points(parameters):
	sorted_params = sorted(parameters)
	param_list= [val_gen(parameters[p]['u'],parameters[p]['v'],parameters[p]['step']) for p in sorted_params]
	for p_data in product(*param_list):
		point = dict((sorted_params[i],p_data[i]) for i in range(len(sorted_params)))
		yield point

def create_generating_model_file(model_file,point,point_ind, otherlines):
	fake_name = model_file+'___fake_'+str(point_ind)
	with open(fake_name,'w') as f:
		for l in otherlines:
			f.write(l)
		for p in point:
			f.write(p)
			f.write('=')
			f.write(str(point[p])+'\n')
	return fake_name


def execute_fake_data(stimuli,gen_model_file,point_ind,num_of_data_sets):
	"""
	Execute the following:
		./states -a gen_model_file -s stimuli > data_file_agent  
	"""
	agent_desc=gen_model_file.replace('/','').replace('.','')
	for ds in range(int(num_of_data_sets)):
		line='../src/states -a '+gen_model_file+' -s '+stimuli+' > ../data/'+agent_desc+'_DS'+str(ds)+'\n'
		with open('generate_fake_data_.sh', 'a') as f:
			f.write(line)

def create_fitting_job_script(model_file,point_ind,num_of_ds):
	"""
	Writes the job script
	"""
	content = '''
#!/bin/bash
#PBS -N @AGENT_fitting
#PBS -l nodes=1:ppn=10
#PBS -l walltime=26:00:00
#PBS -l mem=4GB
#PBS -t 1-9
#PBS -M zb9@nyu.edu
#PBS -m abe
BASE_DIR=$HOME/mnk
SRCDIR=$BASE_DIR/src
DIREC=$SCRATCH/Gomoku
AGENT=@AGENT
POINT=${PBS_ARRAYID}
AGENT_FILE=$BASE_DIR/agents/${AGENT}  
module purge
module load matlab/2014a gcc/4.9.2
export MATLABPATH=$DIREC:$SRCDIR/matlab
export LD_PRELOAD=$GCC_LIB/libstdc++.so
cp $SRCDIR/Gomoku_model.mexa64 $DIREC
for DS in {0..@DS}; do 
	DATA_FILE=$BASE_DIR'/data/agents'${AGENT}'___fake_'${POINT}'0000_DS'${DS}
	RESULT_PATH=$DIREC/fake_${AGENT}_${POINT}0000_DS${DS}
	mkdir -p ${RESULT_PATH}/Output
	cd ${RESULT_PATH}
	rm Output/out*
	echo "Gomoku_optim_mcs(-1,'$AGENT_FILE', '$DATA_FILE'); exit;" | matlab -nodisplay
	echo "Done"
done;
'''
	agent_desc=model_file.split('/')[-1].replace('.','')
	content = content.replace('@AGENT',agent_desc).replace('@DS',str(num_of_ds))
	job_name='Gomoku_fake_fitting_'+agent_desc+'.pbs'
	print " Job name:" + job_name
	with open(job_name, 'w') as f:
		f.write(content)
		



try:
	model_file=argv[1]
	stimuli=argv[2]
	num_of_data_sets=argv[3]
except:
	print_usage()

otherlines,parameters=get_fit_params(model_file)  #e.g., p1=?1{u,v} p2=?2{u,v}
point_ind=0
for point in create_points(parameters):
	print "Creates point:"+str(point)
	gen_model_file=create_generating_model_file(model_file,point,point_ind,otherlines) 
	execute_fake_data(stimuli,gen_model_file,point_ind,num_of_data_sets)
	point_ind+=1

create_fitting_job_script(model_file,point_ind,num_of_data_sets) # for fitting this model with the relevant data_file[s]


