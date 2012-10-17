#!/bin/bash
#
# File Name: basicMemtest.sh
# Author: Betti Oesterholz ; Date: 07.09.2010
# System: bash
#
# Copyright (C) 2010  Betti Oesterholz
#
# Description: a basic test on memoryleaks for fib system
# Time: less then 5 minutes
#
# Attention: You have to be in the direction of this file to run it.
#
#History:
# 07.09.2010   Oesterholz   
#

first(){
  echo $1
}


if ! [ -d result ]; then
	mkdir result
fi

export ORIGINAL_DIR=$(pwd)

export SUB_PROJECT_PATHS="fib/ enviroment/ enviroment.fib/ fib.algorithms/"

echo
#evaluate sub testruns

for SUB_PROJECT_PATH in ${SUB_PROJECT_PATHS}
do
	echo
	echo "Changing derection to ../${SUB_PROJECT_PATH}"
	cd ../${SUB_PROJECT_PATH}/testruns
	if [ -x ./basicMemtest.sh ]; then
		echo "starting basicTestrun.sh"
		./basicMemtest.sh 
	fi
	cd ${ORIGINAL_DIR}
	echo
done






