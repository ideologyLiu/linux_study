#!/bin/bash
PS3="please enter you select install menu: "
select i in http php mysql quit
do
case $i in
	http)
		echo "test http"
	;;
	php)
		echo "test php"
	;;
	mysql)
		echo "test mysql"
	;;
	quit)
		exit &&	echo "exit"
esac
done
