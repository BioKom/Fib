#!/bin/bash
#
# File Name: basicMemtest.sh
# Author: Betti Oesterholz ; Date: 15.06.2010
# System: bash
#
# Copyright (C) 2010  Betti Oesterholz
#
# Description: a basic test on memoryleaks for the Fib -multimediaalgoritms libary
# Time: less then 5 minutes
#
# Attention: You have to be in the direction of this file to run it.
#
#History:
# 15.06.2010   Oesterholz   created
# 28.06.2010   Oesterholz   t_nD1_nPolynom added
# 22.07.2010   Oesterholz   t_nD1_createAreasForPoints added
# 27.08.2010   Oesterholz   t_nTidyFibObjects_nBalanceLists added
# 11.12.2010   Oesterholz   tCEvalueUnderObjects added
# 15.01.2011   Oesterholz   tHyperplane added
# 11.02.2011   Oesterholz   tHyperplaneBody added
# 13.02.2011   Oesterholz   t_nD1_nPolynom removed and tPolynom added
# 21.02.2011   Oesterholz   t_nD2 added
# 05.07.2011   Oesterholz   tSpline added
# 04.03.2013   Oesterholz   tImageStructureConvertToFib and
#	tImageStructureConvertToTiles added
# 05.04.2013   Oesterholz   tImageSearchData added
# 08.04.2013   Oesterholz   tFindImageStructure added
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
echo "Memory leaks in tNReduceFibObject" >>${OUTPUT}
${LEAK_CHECKER} ./tNReduceFibObject ../testObjects/ > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tNReduceFibObject >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memory leaks in t_nD1_createAreasForPoints" >>${OUTPUT}
${LEAK_CHECKER} ./t_nD1_createAreasForPoints > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./t_nD1_createAreasForPoints >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memory leaks in t_nTidyFibObjects_nBalanceLists" >>${OUTPUT}
${LEAK_CHECKER} ./t_nTidyFibObjects_nBalanceLists 64 4 > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./t_nTidyFibObjects_nBalanceLists >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}


echo >>${OUTPUT}
echo "Memory leaks in t_nD1_nPolynom_evaluePolynomHillClimbing" >>${OUTPUT}
${LEAK_CHECKER} ./t_nD1_nPolynom_evaluePolynomHillClimbing > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./t_nD1_nPolynom_evaluePolynomHillClimbing >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memory leaks in t_nD1_nPolynom_evaluePolynomRange" >>${OUTPUT}
${LEAK_CHECKER} ./t_nD1_nPolynom_evaluePolynomRange > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./t_nD1_nPolynom_evaluePolynomRange >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memory leaks in t_nD1_nPolynom_findPolynomRand" >>${OUTPUT}
${LEAK_CHECKER} ./t_nD1_nPolynom_findPolynomRand > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./t_nD1_nPolynom_findPolynomRand >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}


cd ../nEvalueFibObject/nNeededUnderobjects/testcase >>${OUTPUT} 2>>${ERROR_OUTPUT}
if [ ! -d test_output ]; then
  mkdir test_output
fi

echo >>${OUTPUT}
echo "Memory leaks in tCEvalueUnderObjects" >>${OUTPUT}
${LEAK_CHECKER} ./tCEvalueUnderObjects ../testObjects/ > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tCEvalueUnderObjects >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}


cd ${ORIGINAL_DIR}/../nDn/testcase >>${OUTPUT} 2>>${ERROR_OUTPUT}
if [ ! -d test_output ]; then
  mkdir test_output
fi

echo >>${OUTPUT}
echo "Memory leaks in tHyperplane" >>${OUTPUT}
${LEAK_CHECKER} ./tHyperplane  > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tHyperplane >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memory leaks in tHyperplaneBody" >>${OUTPUT}
${LEAK_CHECKER} ./tHyperplaneBody  > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tHyperplaneBody >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}


cd ${ORIGINAL_DIR}/../nD1/testcase >>${OUTPUT} 2>>${ERROR_OUTPUT}
if [ ! -d test_output ]; then
  mkdir test_output
fi

echo >>${OUTPUT}
echo "Memory leaks in tPolynom" >>${OUTPUT}
${LEAK_CHECKER} ./tPolynom  > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tPolynom >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memory leaks in tSpline" >>${OUTPUT}
${LEAK_CHECKER} ./tSpline  > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tSpline >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}



cd ${ORIGINAL_DIR}/../nD2/testcase >>${OUTPUT} 2>>${ERROR_OUTPUT}
if [ ! -d test_output ]; then
  mkdir test_output
fi

echo >>${OUTPUT}
echo "Memory leaks in t_nD2" >>${OUTPUT}
${LEAK_CHECKER} ./t_nD2  > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./t_nD2 >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}



# test nImage classes
cd ${ORIGINAL_DIR}/../nConvertToFib/nImage >>${OUTPUT} 2>>${ERROR_OUTPUT}

echo >>${OUTPUT}
echo "Memory leaks in tImageStructureConvertToTiles" >>${OUTPUT}
${LEAK_CHECKER} ./nStructureData/nConvertToFib/testcase/tImageStructureConvertToTiles ./testObjects/ 4  > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./nStructureData/nConvertToFib/testcase/tImageStructureConvertToTiles >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memory leaks in tImageStructureConvertToFib" >>${OUTPUT}
${LEAK_CHECKER} ./nStructureData/testcase/tImageStructureConvertToFib ./testObjects/ 64  > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./nStructureData/testcase/tImageStructureConvertToFib >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memory leaks in tImageSearchData" >>${OUTPUT}
${LEAK_CHECKER} ./nStructureData/testcase/tImageSearchData 64  > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./nStructureData/testcase/tImageSearchData >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}


echo >>${OUTPUT}
echo "Memory leaks in tFindImageStructure" >>${OUTPUT}
${LEAK_CHECKER} ./nSearchForStructure/testcase/tFindImageStructure 64  > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./nSearchForStructure/testcase/tFindImageStructure >>${OUTPUT} 2>>${ERROR_OUTPUT}
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




