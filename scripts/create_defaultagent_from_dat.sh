#!/bin/bash

dat_file=$1
echo "implementation=DEFAULT"
echo 'K0=0'
echo 'vert_scale=1'
echo 'diag_scale=1'
echo 'opp_scale=1'
echo 'weights_4=0'
echo 'triangle_weight=0'
tmpfile=$(mktemp /tmp/abc-script.XXXXXX)
tail -n11 ${dat_file} | head -n10 > ${tmpfile}
paste ../agents/defaultagent_fields ${tmpfile}
rm ${tmpfile}

