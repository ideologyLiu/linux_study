#!/bin/bash
IP=(10.0.0.1 10.0.0.2 10.0.0.3)
for ((i=0;i<${#IP[*]}; i++));do
echo ${IP[$i]}
done

