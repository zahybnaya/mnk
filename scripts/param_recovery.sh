
#!/bin/bash 

model_file=$1
fake_files=[] #find the fake_files that match the model_file
param_list=`python get_param_list.py $model_file`
for fitted_file in fake_files; do 
	DS= #find the ds from file_name
	generated_values=`python get_generated_values $fitted_file`
	echo 'param_recovery(['p1'; 'p2'; 'p3'] , [0.11 ; 0.21 ; 0.31] , '$FITTED_FILE' , '$DS')' | matlab 
done

