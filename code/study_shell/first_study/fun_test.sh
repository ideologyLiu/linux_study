#!/bin/bash
func()
{
	VAR=$((1+1))
	return $VAR
	echo "this is a function"
}

func
echo $?
