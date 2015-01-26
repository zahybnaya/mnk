#!/bin/bash
#PBS -N Gomoku_best
#PBS -l nodes=1:ppn=20
#PBS -l walltime=00:30:00
#PBS -l mem=1GB 
#PBS -t 0-37 
#PBS -j oe
#PBS -M svo213@nyu.edu
#PBS -m abe

player=${PBS_ARRAYID}
direc=$SCRATCH/Gomoku/bfs


module purge
module load matlab/2014a gcc/4.9.2
export MATLABPATH=$MATLABPATH:/scratch/svo213/Gomoku/Code:$direc
export LD_PRELOAD=$GCC_LIB/libstdc++.so

cd $direc/subject$player

echo "getbestx($player); exit;" | matlab -nodisplay

echo "Done"

