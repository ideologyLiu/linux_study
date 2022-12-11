#!/bin/bash
USER="liuzheng"
while true
do
	echo "the time is `date +%F-%T`"
	sleep 10
	NUM=`who|grep "$USER"|wc -l`
	if [[ $NUM -ge 1 ]];then
		echo "The $USER is login in system "
	fi
done
