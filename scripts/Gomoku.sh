#!/bin/bash
#PBS -N Gomoku_bfs
#PBS -l nodes=1:ppn=1
#PBS -l walltime=26:00:00
#PBS -l mem=2GB
#PBS -t 0
#PBS -M zb9@nyu.edu
#PBS -m abe
BASE_DIR=$HOME/mnk
SRCDIR=$BASE_DIR/src
player=${PBS_ARRAYID}
direc=$SCRATCH/Gomoku
module purge
module load matlab/2014a gcc/4.9.2
mkdir -p $direc/subject$player/Output
cp $direc/times.txt .
cp $SRCDIR/Gomoku_model.mexa64 $direc
cd $direc/subject$player
rm Output/out*
export MATLABPATH=$direc:$SRCDIR/matlab
export LD_PRELOAD=$GCC_LIB/libstdc++.so
echo "Gomoku_optim_mcs($player,'$BASE_DIR/agents/bfsagent', '$BASE_DIR/data/2801115.csv'); exit;" | matlab -nodisplay
echo "Done"


