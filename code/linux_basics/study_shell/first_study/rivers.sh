#!/bin/bash

Network=$1
for Host in $(seq 1 254)
do
ping -c 1 $Network.$Host > /dev/null && result=0 || result=1

if [ "result" ==0 ];then
	echo -e "\003"
