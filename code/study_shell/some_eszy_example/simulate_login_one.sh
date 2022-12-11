#/bin/bash
echo -n "login"
read name 
echo -n "password"
read passwd
if [ $name="liuzheng" -a $passwd="liuzheng" ];then
echo "the host and passwd is right!"
fi
