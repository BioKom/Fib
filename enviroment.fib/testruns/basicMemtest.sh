#!/bin/bash
#
# File Name: basicMemtest.sh
# Author: Betti Oesterholz ; Date: 06.03.2010
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
# 06.03.2010   Oesterholz   created 
# 23.10.2010   Oesterholz   work fib -object for operators added 
# 25.02.2011   Oesterholz   handling of more operator directories added
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
export TMP_OUT=${ORIGINAL_DIR}/result/out_memory_test.txt

export OPERATORS_DIR=../operators/
export TEST_ORIGINAL=../testObjects/farbe8_8.fib
export TEST_ORIGINAL_WORK=../testObjects/farbe8_8_err.fib

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

echo > ${TMP_OUT}
#evaluate testcases

echo >>${OUTPUT}
echo "Memoryleaks in tFibObjectFitnessBasic" >>${OUTPUT}
${LEAK_CHECKER} ./tFibObjectFitnessBasic >> ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibObjectFitnessBasic >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFibObjectFitnessBasicAlgorithm" >>${OUTPUT}
${LEAK_CHECKER} ./tFibObjectFitnessBasicAlgorithm ../testObjects/ >> ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibObjectFitnessBasicAlgorithm >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFibIndividual" >>${OUTPUT}
${LEAK_CHECKER} ./tFibIndividual >> ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibIndividual >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tIndividualInfo" >>${OUTPUT}
${LEAK_CHECKER} ./tIndividualInfo >> ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tIndividualInfo >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tInitFibEnviroment" >>${OUTPUT}
${LEAK_CHECKER} ./tInitFibEnviroment >> ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tInitFibEnviroment >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}


echo >>${OUTPUT}
echo "Memoryleaks in tEnviroment" >>${OUTPUT}
${LEAK_CHECKER} ./tEnviroment 64 10 >> ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tEnviroment >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tEndConditionCheck" >>${OUTPUT}
${LEAK_CHECKER} ./tEndConditionCheck >> ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tEndConditionCheck >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}


echo >>${OUTPUT}
echo "Checking the operators on memoryleaks" >>${OUTPUT}

#find all operator names
OPERATORS=$(cat ${OPERATORS_DIR}/operators.txt)
echo "Possible operators: ${OPERATORS}" >>${OUTPUT}


for OPERATOR in ${OPERATORS}
do
	echo >>${OUTPUT}
	echo "Checking Operator: ${OPERATOR}" >>${OUTPUT}
	echo >>${TMP_OUT}
	echo "Checking Operator: ${OPERATOR}" >>${TMP_OUT}
	${LEAK_CHECKER} ../bin/test_runOperation ${OPERATOR} ${TEST_ORIGINAL} ${TEST_ORIGINAL_WORK} >> ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ../bin/test_runOperation >>${OUTPUT} 2>>${ERROR_OUTPUT}
	echo >>${OUTPUT}
done

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






