#!/bin/bash
#PBS -N Gomoku_bfs
#PBS -l nodes=1:ppn=1
#PBS -l walltime=00:03:00
#PBS -l mem=1GB 
#PBS -t 0
#PBS -M zb9@nyu.edu
#PBS -m abe

BASE_DIR=$HOME/mnk
SRCDIR=$BASE_DIR/src
player=${PBS_ARRAYID}
direc=$SCRATCH/Gomoku
module purge
module load matlab/2014a gcc/4.9.2
export MATLABPATH=$MATLABPATH:$SRCDIR/matlab;$direc
export LD_PRELOAD=$GCC_LIB/libstdc++.so
mkdir -p $direc/subject$player/Output
cd $direc/subject$player
cp $direc/times.txt .
cp $SRCDIR/Gomoku_model.mexa64 $direc
rm Output/out*
echo "Gomoku_optim_mcs($player); exit;" | matlab -nodisplay
echo "Done"


