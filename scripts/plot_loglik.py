#
# Assumes the following format: model subject loglik
#
from sys import argv
import matplotlib.pyplot as plt
import numpy as np
from re import match
from itertools import product
from operator import itemgetter

def read_tuples(filename):
    """
    returns a dict from the file
    """
    d = []
    with open(filename) as f:
        for line in f:
            if line.isspace():
                continue
            tup = line.split()
            d.append(tup)
    return d


def read_dict(filename):
    """
    returns a dict from the file
    """
    d = {}
    with open(filename) as f:
        for line in f:
           # if not match(r"[A-Z]{2} *", line):
            #    continue
            (key, val) = line.split()
            d[key] = val
    return d

model_file = argv[1]
data = read_tuples(model_file)
subjects = sorted(set([x[1] for x in data ]))
models = set([x[0] for x in data ])
print "models:",
print models
print "subjects",
print subjects
lims = [
        1,
        3.2
]

for compare in product(models,models):
    if compare[0] == compare[1]:
        continue;
    sub_1 = set([d[1] for s in subjects for d in data if d[1] == s and d[0]==compare[0]])
    sub_2 = set([d[1] for s in subjects for d in data if d[1] == s and d[0]==compare[1]])
    subs_both = sub_1 & sub_2

    data_1 = [d[2] for s in subjects for d in data if d[1] == s and d[0]==compare[0] and s in subs_both]
    data_2 = [d[2] for s in subjects for d in data if d[1] == s and d[0]==compare[1] and s in subs_both]
#colors = np.random.rand(N)
#area = np.pi * (15 * np.random.rand(N))**2 # 0 to 15 point radiuses
#plt.scatter(x, y, s=area, c=colors, alpha=0.5)
    plt.title('Log-Likelihood')
    plt.xlabel(compare[0])
    plt.ylabel(compare[1])
    plt.grid(True)
    plt.axis([1,3.2,1,3.2])
    try:
        plt.scatter(data_1, data_2, s=215,  alpha=0.8)
        plt.plot(lims, lims, 'k--', alpha=0.85, zorder=0)
        #plt.show()
        plt.savefig(compare[0]+"_vs_"+compare[1]+"png")
        plt.close()
    except Exception as inst:
        print type(inst)
        print inst
        print "problem with "+str(compare[0]) + " and "+ str(compare[1])
        print "data_1:" + str(data_1) 
        print "data_2:" + str(data_2) 
#

