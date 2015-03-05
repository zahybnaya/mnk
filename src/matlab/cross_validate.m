function cross_validate(player,agent_file,train_data_file, test_data_file)
		
	data = {player, agent_file, train_data_file};
	filename='mcsresult.mat';
	if exist(filename,'file')
		load(filename)
		L=zeros(nbasket,30);
		for j=1:30
			for i=1:nbasket
				L(i,j)=Gomoku_wrapper(data,xmin(:,i));
			end
		end
		[l,i]=min(mean(L,2))
		x=xmin(:,i)
		L
		result_file_name = sprintf('optimization_results%d.mat',player)
		save(result_file_name,'L','x','l','i','-mat')
		data = {player, agent_file, test_data_file};
		LT=zeros(1,30)
		for t=1:30
			LT(t)=Gomoku_wrapper(data,x);
		end
		mean_lt=mean(LT)
		result_file_name = sprintf('test_results%d.dat',player)
		save(result_file_name,'LT','x','mean_lt','-ascii')
	end
end

