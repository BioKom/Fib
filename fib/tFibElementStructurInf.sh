#!/bin/bash
#
# Copyright (C) 2011 Betti Oesterholz
#
# Author: Betti Oesterholz
#
#######################################################################
#
# This script repeats the tFibElementStructur test in an endless loop.
#
# History:
#

OUT_INF_LOG=outInf.txt
OUT_INF_ERR_LOG=outInfError.txt

date > ${OUT_INF_LOG}
date
STEP_SIZE=100
TEST_SIZE=500

#create the test output directory
if [ ! -d test_output ]; then
  mkdir test_output
fi

#run test in infinite loop
while [ true ];
do
	echo "./testcase/tFibElementStructur ${TEST_SIZE} > ${OUT_INF_LOG} 2>&1"
	nice ./testcase/tFibElementStructur ${TEST_SIZE} > ${OUT_INF_LOG} 2>&1
	ERRORS=$?
	tail -n4 ${OUT_INF_LOG}
	date
	if [ "${ERRORS}" != 0 ]; then
		#error occured: store log text
		date >> ${OUT_INF_ERR_LOG}
		cat ${OUT_INF_LOG} >> ${OUT_INF_ERR_LOG}
		echo "\n\n\n\n\n\n\n\n\n\n" >> ${OUT_INF_ERR_LOG}
	fi
	rm -f ${OUT_INF_LOG} > /dev/null
	TEST_SIZE=$((${TEST_SIZE} + ${STEP_SIZE}))
done




