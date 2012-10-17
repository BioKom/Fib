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
# 06.03.2010   Oesterholz   
#

first(){
  echo $1
}


if ! [ -d result ]; then
	mkdir result
fi

export ORIGINAL_DIR=$(pwd)

#export OUTPUT=${ORIGINAL_DIR}/result/basicMemtestOut.txt
#export ERROR_OUTPUT=${ORIGINAL_DIR}/result/basicMemtestOut.txt

export OUTPUT=1
export ERROR_OUTPUT=2

export ERRORS=0
export ERROR_SUM=0
export TMP_OUT=out_memory_test.txt

export OPERATORS_DIR=../operators/
export TEST_ORIGINAL=../testObjects/farbe8_8.fib

export LEAK_CHECKER=~/tools/LeakTracer/LeakCheck
export LEAK_ANALYZE=~/tools/LeakTracer/leak-analyze

# empty output files
date >${OUTPUT} 
date >${ERROR_OUTPUT}


cd ../testcase  

if [ ! -d test_output ]; then
  mkdir test_output
fi

#tail -fq ${OUTPUT} &
#export TAIL_PID=$(first $(ps | grep tail))

echo
#evaluate testcases

echo 
echo "Memoryleaks in tFibObjectFitnessBasic" 
${LEAK_CHECKER} ./tFibObjectFitnessBasic > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibObjectFitnessBasic  
echo 

echo 
echo "Memoryleaks in tFibObjectFitnessBasicAlgorithm" 
${LEAK_CHECKER} ./tFibObjectFitnessBasicAlgorithm ../testObjects/ > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibObjectFitnessBasicAlgorithm  
echo 

echo 
echo "Memoryleaks in tFibIndividual" 
${LEAK_CHECKER} ./tFibIndividual > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibIndividual  
echo 

echo 
echo "Memoryleaks in tIndividualInfo" 
${LEAK_CHECKER} ./tIndividualInfo > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tIndividualInfo  
echo 

echo 
echo "Memoryleaks in tInitFibEnviroment" 
${LEAK_CHECKER} ./tInitFibEnviroment > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tInitFibEnviroment  
echo 


echo 
#echo "Memoryleaks in tEnviroment" 
#${LEAK_CHECKER} ./tEnviroment 64 10 > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tEnviroment  
echo 

echo 
#echo "Memoryleaks in tEndConditionCheck" 
#${LEAK_CHECKER} ./tEndConditionCheck > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tEndConditionCheck  
echo 


echo 
echo "Checking the operators on memoryleaks" 

#find all operator names
OPERATOR_FILES=$(cd ${OPERATORS_DIR}incl/; ls *.h)

OPERATORS=$(echo "${OPERATOR_FILES}" | sed -e "s/.h//g")
echo "Possible operators: ${OPERATORS}" 


for OPERATOR in ${OPERATORS}
do
	echo 
	echo "Checking Operator: ${OPERATOR}" 
	${LEAK_CHECKER} ../bin/test_runOperation ${OPERATOR} ${TEST_ORIGINAL} > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ../bin/test_runOperation 
	echo 
done

echo 


echo "---------------------"
echo "done" 
echo 
date

cd ${ORIGINAL_DIR}
cat ${OUTPUT} > ${ORIGINAL_DIR}/result/basicMemtest.txt


#kill the tail process
#sleep 1
#kill ${TAIL_PID} > /dev/null 2>&1






