#!/bin/bash
#
# The following format should be maintained: 
#  experiment-id :  <agent_file><state_file> 
#  job file : <experiment-id>.q
#  output file : <experiment-id>.o
#  error file : <experiment-id>.e

# Creates HPC jobs from two folders (states/agents) or files (states/agents)
# Only for the non-existent or failed jobs

AGENT_FILE=$1
STATE_FILE=$2

while read agent; do
  while read state; do
	experiment_id=${agent}_${state}
	experiment_id=${experiment_id//./_}
	experiment_id=${experiment_id//\//_}
	echo " Generating job $experiment_id for agent: $agent and state_file $state"
	exp_file=../jobs/${experiment_id}.q
	echo "#!/bin/bash" > $exp_file
	echo "#PBS -l nodes=1:ppn=1" >> $exp_file
	echo "#PBS -l walltime=04:00:00" >> $exp_file
	echo "#PBS -l mem=1GB">> $exp_file
	echo "#PBS -N $experiment_id">> $exp_file
	echo "#PBS -M zahy.bnaya@nyu.edu">> $exp_file
	echo "module purge">> $exp_file
	echo "module load gcc/4.9.2 "  >> $exp_file
	echo 'BASE_DIR=$HOME/mnk'>> $exp_file
	echo 'SRCDIR=$BASE_DIR/src'>> $exp_file
	echo 'RUNDIR=$SCRATCH/mnk/run-${PBS_JOBID/.*}' >> $exp_file
	echo 'mkdir -p $RUNDIR' >> $exp_file
	echo 'mkdir -p $RUNDIR/agents' >> $exp_file
	echo 'mkdir -p $RUNDIR/state_sets' >> $exp_file
	echo 'mkdir -p $RUNDIR/testbed' >> $exp_file
	echo 'cp $SRCDIR'/${agent} '$RUNDIR'/agents/${agent} >> $exp_file
	echo 'cp $SRCDIR'/${state} '$RUNDIR'/state_sets/${state}   >> $exp_file
	echo 'cp $SRCDIR/loglik $RUNDIR/testbed/loglik' >> $exp_file
	echo 'cd $RUNDIR/testbed ' >> $exp_file
	echo '$RUNDIR'/testbed/loglik -a ${agent} -s ${state} >> $exp_file
  done <${STATE_FILE}
done <${AGENT_FILE}

