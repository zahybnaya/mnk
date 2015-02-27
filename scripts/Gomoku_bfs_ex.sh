#!/bin/bash
#PBS -N Gomokubfsexp7
#PBS -l nodes=1:ppn=8
#PBS -l walltime=26:00:00
#PBS -l mem=4GB
#PBS -t 0-7
#PBS -M zb9@nyu.edu
#PBS -m abe
BASE_DIR=$HOME/mnk
SRCDIR=$BASE_DIR/src
player=${PBS_ARRAYID}
direc=$SCRATCH/Gomoku
agent=bfsagent_exp
data=playing_only.csv
agent_file=$BASE_DIR/agents/$agent
data_file=$BASE_DIR/data/${data}SUB${player}.0train.csv
result_path=$direc/${agent}_${data}_subject$player

module purge
module load matlab/2014a gcc/4.9.2
mkdir -p ${result_path}/Output
#cp $direc/times.txt .
cp $SRCDIR/Gomoku_model.mexa64 $direc
cd ${result_path}
rm Output/out*
export MATLABPATH=$direc:$SRCDIR/matlab
export LD_PRELOAD=$GCC_LIB/libstdc++.so
echo "Gomoku_optim_mcs($player,'$agent_file', '$data_file'); exit;" | matlab -nodisplay
echo "Done"


