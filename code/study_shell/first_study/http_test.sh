while true
do

read -p "请输入你的选择 start|stop|restart|status|quit:" char
case $char in 
start)
	systemctl start httpd && echo "httpd 服务已开启" || echo "http 服务开启失败"
;;
stop)
	systemctl stop httpd && echo "httpd 服务已关闭" || echo "httpd 服务关闭失败"
;;
restart)
	systemctl restart httpd && echo "httpd 服务已重启 " || echo "httpd 服务重启失败"
;;
status)
	systemctl status httpd && echo -e "httpd 的服务状态"
;;
quit)
	exit
;;
esac
done
