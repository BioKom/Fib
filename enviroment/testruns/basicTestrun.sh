#!/bin/bash
#
# File Name: basicTestrun.sh
# Author: Betti Oesterholz ; Date: 26.02.2010
# System: bash
#
# Copyright (C) 2010  Betti Oesterholz
#
# Description: a basic test for the enviroment libary
# Time: less then 5 minutes
#
# Attention: You have to be in the direction of this file to run it.
#
#History:
# 26.02.2010   Oesterholz   created
#

first(){
  echo $1
}


if ! [ -d result ]; then
	mkdir result
fi

export ORIGINAL_DIR=$(pwd)
export OUTPUT=${ORIGINAL_DIR}/result/basicOut.txt
export ERROR_OUTPUT=${ORIGINAL_DIR}/result/basicOut.txt
export SUM_OUTPUT=${ORIGINAL_DIR}/result/basicSum.txt
export ERRORS=0
export ERROR_SUM=0

# empty output files
date >${OUTPUT} 
date >${ERROR_OUTPUT}
date >${SUM_OUTPUT}


cd ../testcase >>${OUTPUT} 2>>${ERROR_OUTPUT}

if [ ! -d test_output ]; then
  mkdir test_output
fi

tail -fq ${SUM_OUTPUT} &
export TAIL_PID=$(first $(ps | grep tail))

echo
#evaluate testcases

./tIndividualIdentifier >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tIndividualIdentifier : ${ERRORS}" >>${SUM_OUTPUT}

./tOperationIdentifier >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tOperationIdentifier : ${ERRORS}" >>${SUM_OUTPUT}




echo "---------------------" >>${SUM_OUTPUT}
echo "all Errors : ${ERROR_SUM}" >>${SUM_OUTPUT}
echo >>${SUM_OUTPUT}
date >>${SUM_OUTPUT}

cd ${ORIGINAL_DIR}
cat ${OUTPUT} ${SUM_OUTPUT} > ${ORIGINAL_DIR}/result/basic.txt
#cat ${SUM_OUTPUT}


#kill the tail process
sleep 1
kill ${TAIL_PID} > /dev/null 2>&1



