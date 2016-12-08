#!/bin/python

#
# Splits the data file to train and test according to subject
#


from sys import argv
from random import shuffle,sample
import csv

try:
    split_folds = argv[3]
except:
    split_folds = None
try:
    data_file = argv[1]
    split_percentage = argv[2]
except:
    print ("usage: <data_file> <split_percentage> <split_folds>")
    print ("split_percentage is ignored if split_folds exist")
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
    if split_folds is not None:
        folds=[]
        small_fold_size = len(subject_data)/int(split_folds) #lower size
        num_large_folders=len(subject_data)%int(split_folds)
        to_ind=0
        print "Splitting for Subject: {0} with {1} records".format(s,len(subject_data))
        for i in range(int(split_folds)):
            if i<num_large_folders:
                fold_size=small_fold_size+1
                from_ind=to_ind
                to_ind=from_ind+fold_size
                print " Fold {0} :from {1} to {2}".format(i,from_ind,to_ind)
                fold = subject_data[from_ind:to_ind]
                folds.append(fold)
            else:
                fold_size=small_fold_size
                from_ind=to_ind
                to_ind=from_ind+fold_size
                print " Fold {0} :from {1} to {2}".format(i,from_ind,to_ind)
                fold = subject_data[from_ind:to_ind]
                folds.append(fold)
        assert(sum(len(j) for j in folds) == len(subject_data))
        fi=0
        for f in folds:
            write_data(data_file+"SUB"+s+"fold"+str(fi)+".csv",f)
            fi+=1
    else:
        print(" There are {0} folds with {1} fold_size each".format(len(folds),len(folds[0])))
        print(" length is: {0} and train_n:{1} ".format(len(subject_data),train_n))
        train_data = subject_data[:train_n]
        test_data = subject_data[train_n:]
        write_data(data_file+"SUB"+s+"train.csv",train_data)
        write_data(data_file+"SUB"+s+"test.csv",test_data)




