function r=Gomoku_wrapper(data,x)
	[player,agent_file,data_file]=data{1:1,1:2,1:3}
	r=Gomoku_model(player,agent_file,[5;x]);
end
