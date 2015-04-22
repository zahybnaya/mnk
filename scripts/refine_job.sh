#!/bin/bash
#
#  Gets as an input a pbs work and creates a string of missing subjects
#
job_file=$1
agent=`cat $job_file | grep 'agent=' | cut -d= -f2`
data=`cat $job_file | grep 'data=' | cut -d= -f2`
jobs=`cat $job_file | grep 'PBS -t' | awk '{print $3}' `
echo $jobs
jobs=${jobs/-/..}
jobs={${jobs}}
echo $jobs
#myopicagent_37subjects.csv.csv_subject28/mcsresult.mat >> exits
#myopicagent_37subjects.csv.csv_subject28/mcsresult.mat
#myopicagent_37subjects.csv_subject28/mcsresult.mat
t_string='#PBS -t '
for j in `eval echo $jobs` ; do 
	#file "/scratch/zb9/Gomoku/${agent}_${data}_subject${j}/mcsresult.mat"
	if [ -f "/scratch/zb9/Gomoku/${agent}_${data}_subject${j}/mcsresult.mat" ]  ; then 
		echo "results for subject $j exists" ; 
		else  
		t_string=$t_string,$j
		echo "$j  is missing" ; 
	fi
done;
t_string=${t_string/ ,/ }
echo $t_string
#
