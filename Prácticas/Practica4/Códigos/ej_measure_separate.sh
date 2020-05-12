#!/bin/bash
for i in `seq 1 15`; do
	echo $i
	./measure_separate $i
done

