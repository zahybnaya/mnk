
#!/bin/python 

from sys import argv
from numpy import std


def get_rts(rt_values_file):
    rts = {}
    with open(rt_values_file, 'r') as f:
        for line in f:
            if line[1].isalpha():
                continue
            fields=line.split(',')
            key=(fields[6],fields[7])
            val=fields[9].strip()
            rts[key]=val
    return rts

try:
    switch_values_file = argv[1]
    rt_values_file = argv[2]
except:
    print "<time_values> <rt_values>"
    exit(-1)

rts=get_rts(rt_values_file)
12.3683,0.319881,3,0,10.8121,1.94098,0,0,0
12.3683,0.319881,3,0,10.8121,1.94098,0,0,0
measures=['black','white','player','best_diff','entropy','tree_switch','count_evals','max_val', 'norm_best_diff', 'num_consecutive', 'num_nodes' ,  'num_pieces', 'num_patterns']
boards={}
with open(switch_values_file, 'r') as f:
    for line in f:
        if line[1].isalpha():
            continue
        fields=line.split(',')
        board=(fields[0],fields[1])
        color=fields[2].strip()
        measures_lists = boards.get(board,{})

        bd = measures_lists.get('best_diff',[])
        bd.append(float(fields[3].strip()))
        measures_lists['best_diff']=bd

        en = measures_lists.get('entropy',[])
        en.append(float(fields[4].strip()))
        measures_lists['entropy']=en

        ts = measures_lists.get('tree_switch',[])
        ts.append(float(fields[5].strip()))
        measures_lists['tree_switch']=ts

        mv = measures_lists.get('max_val',[])
        mv.append(float(fields[7].strip()))
        measures_lists['max_val']=mv

        rbd = measures_lists.get('norm_best_diff',[])
        rbd.append(float(fields[8].strip()))
        measures_lists['norm_best_diff']=rbd

        nc = measures_lists.get('num_consecutive',[])
        nc.append(float(fields[9].strip()))
        measures_lists['num_consecutive']=nc

        np = measures_lists.get('num_nodes',[])
        np.append(float(fields[10].strip()))
        measures_lists['num_nodes']=np

        npp = measures_lists.get('num_patterns',[])
        npp.append(float(fields[11].strip()))
        measures_lists['num_pieces']=npp


        boards[board]=measures_lists

print "best_diff,entropy,tree_switch,max_val,norm_best_diff,num_consecutive,num_nodes,rt"
bd_std=[]
bd_means=[]
en_std=[]
en_means=[]
ts_std=[]
ts_means=[]
for b in boards:
    bd=sum(boards[b]['best_diff'])/len(boards[b]['best_diff'])

    bd_std.append(std(boards[b]['best_diff']))
    bd_means.append(bd)

    en=sum(boards[b]['entropy'])/len(boards[b]['entropy'])
    en_std.append(std(boards[b]['entropy']))
    en_means.append(en)


    ts=sum(boards[b]['tree_switch'])/len(boards[b]['tree_switch'])
    ts_std.append(std(boards[b]['tree_switch']))
    ts_means.append(ts)

    mvv=sum(boards[b]['max_val'])/len(boards[b]['max_val'])

    nbd=sum(boards[b]['norm_best_diff'])/len(boards[b]['norm_best_diff'])

    noc=sum(boards[b]['num_consecutive'])/len(boards[b]['num_consecutive'])

    non=sum(boards[b]['num_nodes'])/len(boards[b]['num_nodes'])

    print str(bd)+","+ str(en) +"," + str(ts) + "," + str(mvv) +  " ," + str(nbd) + ',' + str(noc) +',' + str(non) +',' + rts[b]

#print zip(bd_means,bd_std)
#print zip(en_means, en_std)
#print zip(ts_means ,ts_std)


