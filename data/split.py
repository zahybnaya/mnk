#!/bin/python

#
# Splits the data file to train and test according to subject
#


from sys import argv
from random import shuffle
import csv

try:
	data_file = argv[1]
	split_percentage = argv[2]
except:
	print ("usage:")
	exit


def read_dict(data_file):
    """
    returns a dict from the file
    """
    d = []
    with open(data_file) as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            if None in row.values():
                continue
            row = dict( (k.strip(),v.strip()) for k,v in row.items() )
            d.append(row)
    return d



def write_data(outputfile,data):
    with open(outputfile, 'w') as csvfile:
	fieldnames =  ['','subject','color','gi','mi','status','bp','wp','response','rt']
	writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
	writer.writerow(dict( (_,_) for _ in fieldnames))
	for d in data:
		writer.writerow(d)


data=read_dict(data_file)
subjects=set([d['subject'] for d in data if not d['subject'].endswith('.01') ])
print "Subjects: "+ str(len(subjects))

for s in subjects:
	subject_data=[d for d in data if d['subject']==s]
	train_n = int(len(subject_data) * float(split_percentage))
	shuffle(subject_data)
	print(" length is: {0} and train_n:{1} ".format(len(subject_data),train_n))
	train_data = subject_data[:train_n]
	test_data = subject_data[train_n:]
	write_data(data_file+"SUB"+s+"train.csv",train_data)
	write_data(data_file+"SUB"+s+"test.csv",test_data)




