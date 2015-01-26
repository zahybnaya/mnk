#!/bin/bash
#PBS -N Gomoku_bfs
#PBS -l nodes=1:ppn=20
#PBS -l walltime=12:00:00
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

cd $direc
mkdir subject$player
cd subject$player
cp $direc/times.txt .
mkdir Output
rm Output/out*

echo "Gomoku_optim_mcs($player); exit;" | matlab -nodisplay

echo "Done"

