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
	  echo $agent $state
  done <${STATE_FILE}
done <${AGENT_FILE}
#
##!/bin/bash
##PBS -l nodes=1:ppn=1
##PBS -l walltime=1:00:00
##PBS -l mem=1GB
##PBS -N loglik_agent_stateset
##PBS -M zahy.bnaya@nyu.edu
##PBS -o /home/mnk/results/loglik_agent_stateset_o
##PBS -e /home/mnk/results/loglik_agent_stateset_e
# 
#module purge
##module load gcc/4.9.2  (only for compilation)
#BASE_DIR=$HOME/mnk
#SRCDIR=$BASE_DIR/src
#RESDIR=$BASE_DIR/results
#
#
#RUNDIR=$SCRATCH/mnk/run-${PBS_JOBID/.*}
#mkdir -p $RUNDIR
# 
#cd $RUNDIR
#$SRCDIR 1>/loglik/home/mnk/results/loglik_agent_stateset_o 2>/home/mnk/results/loglik_agent_stateset_e
#
