from sys import argv
import matplotlib.pyplot as plt
import numpy as np
from itertools import product
import csv

filename  = argv[1]
def read_dict(filename):
    """
    returns a dict from the file
    """
    d = []
    with open(filename) as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            if None in row.values():
                continue
            row = { k.strip():v.strip() for k,v in row.items() }
            d.append(row)
    return d


data = read_dict(filename)
plt.title("UCT with a single random playout")
plt.xlabel('subject')
plt.ylabel('-logliklihood')
plt.grid(True)
width=.45
for i in range(8):
    subject_d = [float(d[str(i)]) for d in data ]
    plt.bar(i,np.mean(subject_d),width,color='grey',align='center',yerr=np.std(subject_d),ecolor='k')
#plt.plot(sorted(iterations), ucterrors, 'r-' ,iterations, cdperrors, 'g-', iterations, mmerrors, 'b^')
#plt.plot(sorted(iterations), ucterrors, 'r-' ,iterations,  mmerrors, 'b-')
# plt.savefig(title+'.png', bbox_inches='tight')
plt.show()
#plt.close()

