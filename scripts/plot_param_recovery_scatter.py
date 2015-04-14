from sys import argv
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np
from re import match
from itertools import product
from operator import itemgetter
import csv

def read_dict(filename):
    """
    returns a dict from the file
    """
    data=[]
    with open(filename,'r') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            data.append(row)
            print row
    return data

param_file = argv[1]
data = read_dict(param_file)
params = sorted(set([x['param'].strip() for x in data ]))
models = set([x['model'].strip() for x in data ])

bounds = {'myopicagent':{},
          'uctagent':{'lapse_rate':(0.1,0.9),
                      'gamma':(0.001,0.1),
                      'exploration_constant':(0,1)
                      }
          }

for param,model in product(params,models):
    relevant_plot = [d for d in data if d['param'].strip()==param and d['model'].strip()==model]
    split_by_ds = dict((ds, [rd for rd in relevant_plot if rd['ds']==ds]) for ds in set(d['ds'] for d in relevant_plot))
    if len(split_by_ds)==0:
        continue
    print "PARAM:" + param + " MODEL:" + model
#    if model not in bounds or param not in bounds[model]:
#        read_model(mode)
    print split_by_ds
    plt.title('parameter-recovery: ' + str(param)+' '+ str(model))
    plt.xlabel('generated value')
    plt.ylabel('fitted value')
    plt.grid(True)
    ds_colors = cm.rainbow(np.linspace(0, 1, len(split_by_ds)))
    min_val_x=float('inf')
    min_val_y=float('inf')
    max_val_x=float('-inf')
    max_val_y=float('-inf')
    for ds,c in zip(split_by_ds,ds_colors):
        scatter_data = [(float(d['gen_val']), float(d['fit_val'])) for d in split_by_ds[ds]]
        plt.scatter([x[0] for x in scatter_data], [x[1] for x in scatter_data], s=215, alpha=0.8 , color=c)
        min_val_x = min(min([x[0] for x in scatter_data]),min_val_x)
        min_val_y = min(min([x[1] for x in scatter_data]),min_val_y)
        max_val_x = max(max([x[0] for x in scatter_data]),max_val_x)
        max_val_y = max(max([x[1] for x in scatter_data]),max_val_y)

    delta=(max_val_x-min_val_x)/10
    lims_x=[min_val_x-delta, max_val_x+delta]
    lims_y=[min_val_y-0.5, max_val_y+0.5]
    plt.axis(lims_x+lims_y)
    plt.plot(lims_x, lims_y, 'k--', alpha=0.85, zorder=0)
    plt.savefig('parameter_'+str(param)+str(model)+".png")
    plt.close()

