
for sub in {0..39} 
	do
	for fold in {0..4} 
		do 
		for foldtest in {0..4}
			do
			echo -n "${sub}:${fold}:${foldtest}->"
			awk 'a[$0]++' model_input.csvSUB${sub}_train_fold_${fold}.csv model_input.csvSUB${sub}fold${foldtest}.csv | wc -l
		done
	done
done

