
#!/bin/bash 
model_file=$1
BASE_DIR=$HOME/mnk
SRCDIR=$BASE_DIR/src
direc=$SCRATCH/Gomoku
module purge
module load matlab/2014a gcc/4.9.2
export MATLABPATH=$direc:$SRCDIR/matlab
export LD_PRELOAD=$GCC_LIB/libstdc++.so
agent_name=`basename $model_file`
fake_files=`find $SCRATCH/Gomoku/ -path *fake*${agent_name}*/mcsresult.mat `
for fitted_file in ${fake_files[@]}; do 
	echo "python gen_matlab_line.py $fitted_file"
	matlab_line=`python gen_matlab_line.py $fitted_file`
	echo "$matlab_line ; exit "| matlab -nodisplay
	#echo 'param_recovery(['p1'; 'p2'; 'p3'] , [0.11 ; 0.21 ; 0.31] , '$FITTED_FILE' , '$DS')' | matlab 
done

