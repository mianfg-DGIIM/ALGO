#!/bin/bash
CONTADOR=1
for	((i=1; i<10000; i+=1000))
do
             echo El contador es $CONTADOR
	     ./lcs_dynamic $CONTADOR >> lcs_dynamic.txt 
done


