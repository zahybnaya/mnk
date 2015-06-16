function cross_validate(player,agent_file,train_data_file, test_data_file)
		
	data = {player, agent_file, train_data_file};
	filename='mcsresult.mat';
	if exist(filename,'file')
		load(filename)
		L=zeros(nbasket,50);
		% training 
		for j=1:50
			for i=1:nbasket
				L(i,j)=Gomoku_wrapper(data,xmin(:,i));
			end
		end
		[l,i]=min(mean(L,2))
		x=xmin(:,i) %best values are stored in x
		L
		result_file_name = sprintf('optimization_results%d.mat',player)
		save(result_file_name,'L','x','l','i','-mat')
		data = {player, agent_file, test_data_file};
		LT=zeros(1,50)
		% testing
		for t=1:50
			LT(t)=Gomoku_wrapper(data,x);
		end
		mean_lt=mean(LT)
		sd_lt=std(LT)
		result_file_name = sprintf('test_results%d.dat',player)
		save(result_file_name,'LT','x','mean_lt','-ascii')
		fid = fopen('loglik.csv', 'a+');
		fprintf(fid, '%s, %s, %d, %d\n',agent_file, test_data_file, mean_lt, sd_lt)
		fclose(fid);

	end
end

