#!/bin/bash

#定义一个变量名
name=crond
num=$(ps -ef|grep $name|grep -vc grep)
if [ $num -eq 1 ];then
	echo "$num running!"
else
	echo "$num is not running!"
fi
