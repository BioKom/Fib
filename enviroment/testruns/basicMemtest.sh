#!/bin/bash
#
# File Name: basicMemtest.sh
# Author: Betti Oesterholz ; Date: 26.02.2010
# System: bash
#
# Copyright (C) 2010  Betti Oesterholz
#
# Description: a basic test on memoryleaks for the enviroment libary
# Time: less then 5 minutes
#
# Attention: You have to be in the direction of this file to run it.
#
#History:
# 26.02.2010   Oesterholz   
#

first(){
  echo $1
}


if ! [ -d result ]; then
	mkdir result
fi

export ORIGINAL_DIR=$(pwd)
export OUTPUT=${ORIGINAL_DIR}/result/basicMemtestOut.txt
export ERROR_OUTPUT=${ORIGINAL_DIR}/result/basicMemtestOut.txt
export ERRORS=0
export ERROR_SUM=0
export TMP_OUT=out_memory_test.txt

export LEAK_CHECKER=~/tools/LeakTracer/LeakCheck
export LEAK_ANALYZE=~/tools/LeakTracer/leak-analyze

# empty output files
date >${OUTPUT} 
date >${ERROR_OUTPUT}


cd ../testcase >>${OUTPUT} 2>>${ERROR_OUTPUT}

if [ ! -d test_output ]; then
  mkdir test_output
fi

tail -fq ${OUTPUT} &
export TAIL_PID=$(first $(ps | grep tail))

echo
#evaluate testcases

echo >>${OUTPUT}
echo "Memoryleaks in tIndividualIdentifier" >>${OUTPUT}
${LEAK_CHECKER} ./tIndividualIdentifier > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tIndividualIdentifier >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tOperationIdentifier" >>${OUTPUT}
${LEAK_CHECKER} ./tOperationIdentifier > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tIndividualIdentifier >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}



echo "---------------------" >>${OUTPUT}
echo "done" >>${OUTPUT}
echo >>${OUTPUT}
date >>${OUTPUT}

cd ${ORIGINAL_DIR}
cat ${OUTPUT} > ${ORIGINAL_DIR}/result/basicMemtest.txt


#kill the tail process
sleep 1
kill ${TAIL_PID} > /dev/null 2>&1




