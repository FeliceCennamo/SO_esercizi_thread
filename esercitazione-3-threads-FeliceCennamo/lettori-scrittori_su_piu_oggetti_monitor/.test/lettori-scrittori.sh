#!/bin/bash

source $(dirname "$0")/../../.test/test.sh

BINARY=start
OUTPUT=/tmp/output.txt
TIMEOUT=60
SKIPPED=0


init_feedback "Esercizio lettori-scrittori su più oggetti monitor"


compile_and_run $BINARY $OUTPUT $TIMEOUT


perl -n -e 'BEGIN { @val=(); }  if(/Scrittura:\sstazione=(\d+),\sid_treno=(\d+)/) { $val[$2]=$1; }  if(/Lettura:\sstazione=(\d+),\sid_treno=(\d+)/) { if($1!=$val[$2]) { exit(1); } }' $OUTPUT

if [ $? -ne 0 ]
then
    failure "L'esecuzione non accede al buffer in ordine corretto"
fi


static_analysis


success

