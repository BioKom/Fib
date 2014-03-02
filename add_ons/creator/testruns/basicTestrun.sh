#!/bin/bash
#
#
# @author Betti Oesterholz
# @date 30.09.2013
# @mail webmaster@BioKom.info
#
# System: bash
#
# Description: a basic test for the Fib -multimedialangeage libary
# Time: less then 5 minutes
# Attention: You have to be in the direction of this file to run it.
#
#
# Copyright (C) @c GPL3 2013 Betti Oesterholz
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#
# call:
# 	basicTestrun
#
#
#History:
# 30.09.2013   Oesterholz   created
# 17.10.2013   Oesterholz   tFibObjectInfo added
# 27.02.2014   Oesterholz   tFibNodeHandler_integrateFibObjectIntoNode added
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
date > ${OUTPUT}
date > ${ERROR_OUTPUT}
date > ${SUM_OUTPUT}


cd .. >>${OUTPUT} 2>>${ERROR_OUTPUT}

if [ ! -d test_output ]; then
	mkdir test_output
fi

tail -fq ${SUM_OUTPUT} &
export TAIL_PID=$(first $(ps | grep tail))

echo
#evaluate testcases
./mFibObjSelector/model/testcase/tFibObjectSourceFibDb >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibObjectSourceFibDb : ${ERRORS}" >> ${SUM_OUTPUT}

./mFibObjSelector/model/testcase/tFibObjectSourcePath >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibObjectSourcePath : ${ERRORS}" >> ${SUM_OUTPUT}

./mFibObjSelector/model/testcase/tFibObjectInfo >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibObjectInfo : ${ERRORS}" >> ${SUM_OUTPUT}

./control/testcase/tFibNodeHandler_integrateFibObjectIntoNode >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibNodeHandler_integrateFibObjectIntoNode  : ${ERRORS}" >> ${SUM_OUTPUT}

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



