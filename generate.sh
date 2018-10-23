#!/bin/bash

read n
echo $n > input.txt 
for i in $(seq 1 $n)
do
	echo $(((RANDOM-i)%(n+1))) >> input.txt
done
