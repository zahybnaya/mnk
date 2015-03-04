function cross_validate(player,agent_file,data_file)
		
	data = {player, agent_file, data_file};
	filename='mcsresult.mat';
	if exist(filename,'file')
		load(filename)
		L=zeros(1,30);
		for j=1:30
			L(j)=Gomoku_wrapper(data,xbest);
		end
		result_file_name = sprintf('L%d.dat',player)
		mean_l=mean(L)
		std_l=std(L)
		save(result_file_name,'L','std_l','mean_l','-ascii')
	end
end

