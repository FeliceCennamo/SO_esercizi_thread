#!/bin/bash

source $(dirname "$0")/../../.test/test.sh

BINARY=stack
OUTPUT=/tmp/output.txt
TIMEOUT=60
SKIPPED=0


init_feedback "Esercizio struttura dati thread-safe"

compile_and_run $BINARY $OUTPUT $TIMEOUT


perl -n -e 'if(/Inserimento:\s(\d+)/) { push @elementi, $1; $elementi++; } if(/Prelievo:\s(\d+)/) { $prod = pop @elementi; if($prod!=$1) { print "PRELIEVO $prod - $1\n"; exit(1); } $elementi--; } if($elementi<0 || $elementi>4) { exit(1); } END { if($#elementi>=0) { exit(1); } }' $OUTPUT

if [ $? -ne 0 ]
then
    failure "L'esecuzione non rispetta l'ordine corretto delle produzioni e delle consumazioni"
fi


static_analysis


success


