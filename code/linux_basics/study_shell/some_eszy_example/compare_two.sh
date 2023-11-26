#!/bin/bash
echo "please input two number"
read a
read b

if [ $a -eq $b ]
	then echo "two number is equel"
elif [ $a -gt $b  ]
	then echo "No1>No2"
else
	echo "No1<No2"
fi

