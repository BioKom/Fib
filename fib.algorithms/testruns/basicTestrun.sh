#!/bin/bash
#
# File Name: basicTestrun.sh
# Author: Betti Oesterholz ; Date: 15.06.2010
# System: bash
#
# Copyright (C) 2010  Betti Oesterholz
#
# Description: a basic test for the Fib -multimediaalgoritms libary
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

./tNReduceFibObject ../testObjects/ >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tNReduceFibObject : ${ERRORS}" >>${SUM_OUTPUT}

./t_nD1_createAreasForPoints >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in t_nD1_createAreasForPoints : ${ERRORS}" >>${SUM_OUTPUT}

./t_nTidyFibObjects_nBalanceLists 64 8 >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in t_nTidyFibObjects_nBalanceLists : ${ERRORS}" >>${SUM_OUTPUT}



#manuall to test, just running tested hear
echo >>${SUM_OUTPUT}
echo "Check these test manualy:" >>${SUM_OUTPUT}

./t_nD1_nPolynom_evaluePolynomHillClimbing >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in t_nD1_nPolynom_evaluePolynomHillClimbing : ${ERRORS}" >>${SUM_OUTPUT}

./t_nD1_nPolynom_evaluePolynomRange >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in t_nD1_nPolynom_evaluePolynomRange : ${ERRORS}" >>${SUM_OUTPUT}

./t_nD1_nPolynom_findPolynomRand >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in t_nD1_nPolynom_findPolynomRand : ${ERRORS}" >>${SUM_OUTPUT}


echo >>${SUM_OUTPUT}
echo "Manual checks done; next checks automatic" >>${SUM_OUTPUT}


cd ../nEvalueFibObject/nNeededUnderobjects/testcase >>${OUTPUT} 2>>${ERROR_OUTPUT}
if [ ! -d test_output ]; then
  mkdir test_output
fi

./tCEvalueUnderObjects ../testObjects/ >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tCEvalueUnderObjects : ${ERRORS}" >>${SUM_OUTPUT}


cd ${ORIGINAL_DIR}/../nDn/testcase >>${OUTPUT} 2>>${ERROR_OUTPUT}
if [ ! -d test_output ]; then
  mkdir test_output
fi

./tHyperplane >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tHyperplane : ${ERRORS}" >>${SUM_OUTPUT}

./tHyperplaneBody >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tHyperplaneBody : ${ERRORS}" >>${SUM_OUTPUT}


cd ${ORIGINAL_DIR}/../nD1/testcase >>${OUTPUT} 2>>${ERROR_OUTPUT}
if [ ! -d test_output ]; then
  mkdir test_output
fi

./tPolynom >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tPolynom : ${ERRORS}" >>${SUM_OUTPUT}

./tSpline >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tSpline : ${ERRORS}" >>${SUM_OUTPUT}


cd ${ORIGINAL_DIR}/../nD2/testcase >>${OUTPUT} 2>>${ERROR_OUTPUT}
if [ ! -d test_output ]; then
  mkdir test_output
fi

./t_nD2 >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in t_nD2 : ${ERRORS}" >>${SUM_OUTPUT}

# test nImage classes
cd ${ORIGINAL_DIR}/../nConvertToFib/nImage >>${OUTPUT} 2>>${ERROR_OUTPUT}

./nStructureData/nConvertToFib/testcase/tImageStructureConvertToTiles ./testObjects/ 4 >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tImageStructureConvertToTiles : ${ERRORS}" >>${SUM_OUTPUT}

./nStructureData/testcase/tImageStructureConvertToFib ./testObjects/ 256 >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tImageStructureConvertToFib : ${ERRORS}" >>${SUM_OUTPUT}

./nStructureData/testcase/tImageSearchData 256 >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tImageSearchData : ${ERRORS}" >>${SUM_OUTPUT}


./nSearchForStructure/testcase/tFindImageStructure ./testObjects/ 256 >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFindImageStructure : ${ERRORS}" >>${SUM_OUTPUT}



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



