grade=$1
if [ $grade -gt 90 ];then
	echo "is's very good"
elif [ $grade -gt 70 ];then
	echo "is's good"
elif [ $grade -ge 60 ];then
	echo "pass"
else
	echo "not pass"
fi

