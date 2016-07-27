#!/bin/bash
log | grep uct > uctloglik.csv
sed 's/.*SUB/,/g' uctloglik.csv | sed 's/fold/,/g' | sed 's/.csv//g' | sed 's/^,//g' > uctloglik_clean.csvv
