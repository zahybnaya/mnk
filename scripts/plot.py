from sys import argv
import matplotlib.pyplot as plt
import numpy as np
from re import match
from operator import itemgetter


def read_dict(filename):
    """
    returns a dict from the file
    """
    d = {}
    with open(filename) as f:
        for line in f:
            if not match(r"[A-Z]{2} *", line):
                continue
            (key, val) = line.split()
            d[key] = val
    return d

x_model_file = argv[1]
y_model_file = argv[2]
x = read_dict(x_model_file)
y = read_dict(y_model_file)

N = len(x)
x=sorted(x.items(), key=itemgetter(1))
y_data = [y[n[0]] for n in x]
x_data = [n[1] for n in x]

#colors = np.random.rand(N)
#area = np.pi * (15 * np.random.rand(N))**2 # 0 to 15 point radiuses
#plt.scatter(x, y, s=area, c=colors, alpha=0.5)

lims = [
        1,
        3
]

# now plot both limits against eachother
plt.plot(lims, lims, 'k-', alpha=0.75, zorder=0)
#plt.set_aspect('equal')
#plt.set_xlim(lims)
#plt.set_ylim(lims)

plt.scatter(x_data, y_data, alpha=0.5)
plt.show()
#

