#!/bin/bash
#PBS -N Gomoku_cross_validate
#PBS -l nodes=1:ppn=8
#PBS -l walltime=00:30:00
#PBS -l mem=1GB 
#PBS -t 0-7 
#PBS -j oe
#PBS -M zb9@nyu.edu
#PBS -m abe

player=${PBS_ARRAYID}
direc=$SCRATCH/Gomoku
BASE_DIR=$HOME/mnk
SRCDIR=$BASE_DIR/src
player=${PBS_ARRAYID}
agent=bfsagent_exp
data=playing_only.csv
agent_file=$BASE_DIR/agents/$agent
data_file=$BASE_DIR/data/${data}SUB${player}.0test.csv
result_path=$direc/${agent}_${data}_subject$player

module purge
module load matlab/2014a gcc/4.9.2
export MATLABPATH=$MATLABPATH:$SRCDIR/matlab:$direc
export LD_PRELOAD=$GCC_LIB/libstdc++.so

cd $result_path
echo "cross_validate($player,'$agent_file','$data_file'); exit;" | matlab -nodisplay
echo "Done"

