#!/bin/bash

i=1
j=0

while ((i<=100))
do
	 j=`expr $i + $j`
	((i++))
done
echo $j
