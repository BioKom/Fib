#!/bin/bash
#
#
# @author Betti Oesterholz
# @date 13.05.2009
# @mail webmaster@BioKom.info
#
# System: bash, qmake, make
#
# This script will create all test executebels for the Fib creator module.
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
# 	makeTest
#
#
#
#######################################################################
#
# History:
# 26.09.2013   Oesterholz   created
# 21.01.2014   Oesterholz   debug to test_debug
#


# folder of the testcases
DIR_TEST=test/

# folder of the test executebels
DIR_TESTCASE=testcase/

# the folder where the output of the tests are stored
DIR_TEST_OUTPUT="test_output/"

# the file to output qmake and make output to
FILE_MAKE_OUTPUT=out_makeTest.txt

# the source files
TEST_SOURCES=$(ls mFibObjSelector/model/${DIR_TEST}*.cpp\
	control/${DIR_TEST}*.cpp)

# TODO comment in if tests exists
#		$${DIR_TEST}*.cpp model/$${DIR_TEST}*.cpp view/$${DIR_TEST}*.cpp\
#		mFibObjSelector/view/$${DIR_TEST}*.cpp\
#		mFibObjSelector/control/$${DIR_TEST}*.cpp

# the original prejct *.pro file
ORIGINALE_PRO_FILE=fibCreator.pro

# the original prejct *.pro file
TO_CREATE_PRO_FILE=test_${ORIGINALE_PRO_FILE}

echo "makeTest: creating testcases" > ${FILE_MAKE_OUTPUT} 2>&1
echo "============================" >> ${FILE_MAKE_OUTPUT} 2>&1

#create the debugging executebel
echo "create the debugging executebel"

sed -e "/^CONFIG*=*/ s/$/ warn_on test_debug/" ${ORIGINALE_PRO_FILE} > ${TO_CREATE_PRO_FILE}

echo >> ${FILE_MAKE_OUTPUT} 2>&1
echo >> ${FILE_MAKE_OUTPUT} 2>&1
echo "create the debugging executebel" >> ${FILE_MAKE_OUTPUT} 2>&1
echo >> ${FILE_MAKE_OUTPUT} 2>&1
echo "calling qmake ${TO_CREATE_PRO_FILE}" >> ${FILE_MAKE_OUTPUT} 2>&1
qmake ${TO_CREATE_PRO_FILE} >> ${FILE_MAKE_OUTPUT} 2>&1
if [ $? != 0 ]; then
	echo "Error while calling qmake (see ${FILE_MAKE_OUTPUT} for more details)"
	tail -n32 ${FILE_MAKE_OUTPUT}
fi

echo >> ${FILE_MAKE_OUTPUT} 2>&1
echo "calling make" >> ${FILE_MAKE_OUTPUT} 2>&1
make >> ${FILE_MAKE_OUTPUT} 2>&1
if [ $? != 0 ]; then
	echo "Error while calling make (see ${FILE_MAKE_OUTPUT} for more details)"
	tail -n32 ${FILE_MAKE_OUTPUT}
fi


#create directory for the test output
mkdir -p ${DIR_TEST_OUTPUT}

#create the test executebels
echo "creating tests for sources: ${TEST_SOURCES}"
echo

for TEST_SOURCE in ${TEST_SOURCES}
do
	TARGET=$( echo "${TEST_SOURCE}" |\
		sed -e "s%${DIR_TEST}%${DIR_TESTCASE}%g" -e "s%.cpp%%g" )
	
	mkdir -p $(dirname ${TARGET})
	
	echo "creating test \"${TARGET}\" from testcase source \"${TEST_SOURCE}\""
	rm ${TO_CREATE_PRO_FILE}
	
	sed -e "/^CONFIG*=*/ s/$/ qtestlib warn_on test_debug/" \
		-e "/TARGET .*=*/s%.*%TARGET = ${TARGET}%g" \
		-e "/^TARGET_SOURCE*=*/s%.*%TARGET_SOURCE = ${TEST_SOURCE}%g" \
		${ORIGINALE_PRO_FILE} > ${TO_CREATE_PRO_FILE}
	
	echo >> ${FILE_MAKE_OUTPUT} 2>&1
	echo >> ${FILE_MAKE_OUTPUT} 2>&1
	echo "creating test \"${TARGET}\" from testcase source \"${TEST_SOURCE}\"" >> ${FILE_MAKE_OUTPUT} 2>&1
	echo >> ${FILE_MAKE_OUTPUT} 2>&1
	echo "calling qmake ${TO_CREATE_PRO_FILE}" >> ${FILE_MAKE_OUTPUT} 2>&1
	qmake ${TO_CREATE_PRO_FILE} >> ${FILE_MAKE_OUTPUT} 2>&1
	if [ $? != 0 ]; then
		echo "Error while calling qmake (see ${FILE_MAKE_OUTPUT} for more details):"
		tail -n32 ${FILE_MAKE_OUTPUT}
	fi
	
	echo >> ${FILE_MAKE_OUTPUT} 2>&1
	echo "calling make" >> ${FILE_MAKE_OUTPUT} 2>&1
	make >> ${FILE_MAKE_OUTPUT} 2>&1
	if [ $? != 0 ]; then
		echo "Error while calling qmake (see ${FILE_MAKE_OUTPUT} for more details)"
		tail -n32 ${FILE_MAKE_OUTPUT}
	fi
	
done
















