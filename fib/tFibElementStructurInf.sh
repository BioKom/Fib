#!/bin/bash
#
#
# @author Betti Oesterholz
# @date 13.05.2009
# @mail webmaster@BioKom.info
#
# System: bash
#
# This script repeats the tFibElementStructur test in an endless loop.
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
# 	tFibElementStructurInf
#
#######################################################################
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




