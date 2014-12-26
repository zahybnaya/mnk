#!/bin/bash
#PBS -l nodes=1:ppn=1
#PBS -l walltime=1:00:00
#PBS -l mem=1GB
#PBS -N loglik_agent_stateset
#PBS -M zahy.bnaya@nyu.edu
#PBS -o /home/mnk/results/loglik_agent_stateset_o
#PBS -e /home/mnk/results/loglik_agent_stateset_e
 
module purge
#module load gcc/4.9.2  (only for compilation)
BASE_DIR=$HOME/mnk
SRCDIR=$BASE_DIR/src
RESDIR=$BASE_DIR/results


RUNDIR=$SCRATCH/mnk/run-${PBS_JOBID/.*}
mkdir -p $RUNDIR
 
cd $RUNDIR
$SRCDIR 1>/loglik/home/mnk/results/loglik_agent_stateset_o 2>/home/mnk/results/loglik_agent_stateset_e
