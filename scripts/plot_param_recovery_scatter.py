from sys import argv
import matplotlib.pyplot as plt
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

for param,model in product(params,models):
    print "PARAM:" + param
    print "MODEL:" + model
    data_1 = [float(d['gen_val']) for d in data if d['param'].strip()==param and d['model'].strip()==model]
    data_2 = [float(d['fit_val']) for d in data if d['param'].strip()==param and d['model'].strip()==model]
    lims=[min(data_1), max(data_1)]
    plt.axis(lims*2)
    plt.title('parameter-recovery: ' + str(param)+' '+ str(model))
    plt.xlabel('generated_value')
    plt.ylabel('fitted-value')
    plt.grid(True)
    plt.scatter(data_1, data_2, s=215,  alpha=0.8)
    plt.plot(lims, lims, 'k--', alpha=0.85, zorder=0)
    plt.savefig('par_'+str(param)+str(model)+".png")
    plt.close()

