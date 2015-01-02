#!/bin/bash
#PBS -l nodes=1:ppn=1
#PBS -l walltime=1:00:00
#PBS -l mem=1GB
#PBS -N loglik_agent_stateset
#PBS -M zahy.bnaya@nyu.edu
 
module purge
module load gcc/4.9.2  
#module load valgrind/gnu/3.9.0

BASE_DIR=$HOME/mnk
SRCDIR=$BASE_DIR/src
RESDIR=$BASE_DIR/results


#RUNDIR=$SCRATCH/mnk/run-${PBS_JOBID/.*}
#mkdir -p $RUNDIR
#cp -r $BASE_DIR
 
cd $BASE_DIR/jobs
$SRCDIR/loglik -a ../agents/uct1000 -s ../state_sets/empty_state.csv 
