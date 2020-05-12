#!/bin/bash

for i in $(seq 1 $2); do for j in $(seq 1 100); do $1 $((2**$i)); done done
