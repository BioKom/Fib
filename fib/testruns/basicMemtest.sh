#!/bin/bash
#
# @author Betti Oesterholz
# @date 23.02.2010
# @mail webmaster@BioKom.info
# @filename: basicMemtest.sh
#
# System: bash, valgrind
#
# Description: a basic test on memoryleaks for the Fib -multimedialangeage libary
# Time: less then 60 minutes
# Attention: You have to be in the direction of this file to run it.
#    Also you have to install valgrind.
#
# Copyright (C) @c GPL3 2009 Betti Oesterholz
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
# 23.02.2010   Oesterholz   created
# 22.04.2010   Oesterholz   tTypeUnderFunction
# 23.04.2010   Oesterholz   tFunction
# 28.04.2010   Oesterholz   tFunctionValue
# 30.04.2010   Oesterholz   tFunctionVariable
# 05.05.2010   Oesterholz   tFunctionTwoValue
# 10.05.2010   Oesterholz   tFunctionOneValue
# 14.05.2010   Oesterholz   tDomainRational
# 16.05.2010   Oesterholz   tDomainInteger
# 17.05.2010   Oesterholz   tDomainIntegerBit
# 25.07.2010   Oesterholz   tTypeComments added
# 30.07.2010   Oesterholz   tComment added
# 06.05.2011   Oesterholz   tIf, tConditionTrue and tConditionFalse added
# 14.05.2011   Oesterholz   tConditionTwoValue added
# 15.05.2011   Oesterholz   tConditionComparison added
# 20.05.2011   Oesterholz   tConditionNot added
# 21.05.2011   Oesterholz   tFibElementStructur added (memory leaks fixed)
# 16.06.2011   Oesterholz   tFunctionIf added
# 24.07.2011   Oesterholz   tTypeExtObject added
# 24.08.2011   Oesterholz   tExtObject added
# 14.09.2011   Oesterholz   tTypeUnderArea to tTypeSubarea
# 06.11.2011   Oesterholz   tTypeExtSubobject added
# 09.11.2011   Oesterholz   tExtSubobject added
# 29.11.2011   Oesterholz   tFibDatabase added
# 03.12.2011   Oesterholz   tDomainVectorOpenEnd added
# 04.12.2011   Oesterholz   tTypeFibSet added
# 05.12.2011   Oesterholz   tTypeFibMatrix added
# 21.12.2011   Oesterholz   tVectorFibSet added
# 22.12.2011   Oesterholz   tFibSet added
# 02.01.2012   Oesterholz   tTypeSubarea to tTypeArea
# 07.01.2012   Oesterholz   tVectorFibMatrix and tFibMatrix added
# 21.01.2012   Oesterholz   tTypeExtObjectInput added
# 04.02.2012   Oesterholz   tVectorExtObject and tVectorExtSubobject added
# 14.02.2012   Oesterholz   tDomainReference added
# 09.03.2013   Oesterholz   tMatrix3D added
# 11.05.2013   Oesterholz   tFibDatatyps added
# 30.09.2013   Oesterholz   reworked for valgrid
#


# TODO
# can't use compiler option -pg
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
export SUM_OUTPUT=${ORIGINAL_DIR}/result/basicMemtestSum.txt
export ERRORS=0
export ERROR_SUM=0

export MEM_CHECKER="valgrind --leak-check=full --track-origins=yes --error-exitcode=1"

# empty output files
date > ${OUTPUT}
date > ${ERROR_OUTPUT}
date > ${SUM_OUTPUT}


cd ../testcase >>${OUTPUT} 2>>${ERROR_OUTPUT}

if [ ! -d test_output ]; then
	mkdir test_output
fi

tail -fq ${SUM_OUTPUT} &
export TAIL_PID=$(first $(ps | grep tail))

echo
#evaluate testcases

echo >>${OUTPUT}
${MEM_CHECKER} ./tFibDatatyps 256 >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibDatatyps (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tTypeDimension >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeDimension (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tTypeProperty >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeProperty (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tTypeInVar >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeInVar (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tTypeVariable >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeVariable (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tTypeComments >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeComments (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tTypeArea >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeArea (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tTypeUnderFunction >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeUnderFunction (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tTypeExtObject >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeExtObject (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tTypeExtObjectInput >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeExtObjectInput (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tTypeExtSubobject >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeExtSubobject (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tTypeFibSet >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeFibSet (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tTypeFibMatrix >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeFibMatrix (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}



echo >>${OUTPUT}
${MEM_CHECKER} ./tDomainNaturalNumberBit >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainNaturalNumberBit (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tDomainNaturalNumber >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainNaturalNumber (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tDomainInteger >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainInteger (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tDomainIntegerBit >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainIntegerBit (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tDomainRational >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainRational (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tDomainVector >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainVector (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tDomainVectorOpenEnd >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainVectorOpenEnd (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tDomainReference >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainReference (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tDomainElement >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainElement (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tDomains >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomains (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tMultimediaInfo >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tMultimediaInfo (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tOptionalPart >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tOptionalPart (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}



echo >>${OUTPUT}
${MEM_CHECKER} ./tFibVariable >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibVariable (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tVectorPosition >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorPosition (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tVectorProperty >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorProperty (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tVectorChecksum >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorChecksum (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tVectorArea >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorArea (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tVectorFibSet >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorFibSet (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tVectorFibMatrix >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorFibMatrix (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tVectorExtObject >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorExtObject (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tVectorExtSubobject >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorExtSubobject (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}


echo >>${OUTPUT}
${MEM_CHECKER} ./tRoot >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tRoot (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tList >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tList (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tPoint >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tPoint (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}



echo >>${OUTPUT}
${MEM_CHECKER} ./tProperty >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tProperty (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tArea >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tArea (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tFunction >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFunction (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tFunctionValue >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFunctionValue (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tFunctionVariable >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFunctionVariable (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tFunctionOneValue >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFunctionOneValue (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tFunctionTwoValue >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFunctionTwoValue (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tFunctionIf >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFunctionIf (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tComment >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tComment (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tIf >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tIf (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tConditionTrue >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tConditionTrue (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tConditionFalse >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tConditionFalse (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tConditionNot >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tConditionNot (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tConditionTwoValue >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tConditionTwoValue (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tConditionComparison >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tConditionComparison (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}


echo >>${OUTPUT}
${MEM_CHECKER} ./tExtObject >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tExtObject (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tExtSubobject >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tExtSubobject (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tFibSet >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibSet (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tFibMatrix >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibMatrix (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}


#tests which work random and can be resized

echo >>${OUTPUT}
${MEM_CHECKER} ./tGenerateFibObjects 64 1 >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tGenerateFibObjects (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tFibObjectVariable 64 1 >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibObjectVariable (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tFibObject 64 1 >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibObject (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tFibElementStructur 64 1 >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibElementStructur (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tFibObjectStore 64 1 >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibObjectStore (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tEvalueObject ../testObjects/ >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tEvalueObject (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}

echo >>${OUTPUT}
${MEM_CHECKER} ./tFibDatabase 64 ../testObjects/testFibDatabase/ >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibDatabase (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}



echo >>${OUTPUT}
${MEM_CHECKER} ./tMatrix3D 64 >> ${OUTPUT} 2>> ${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tMatrix3D (1=yes;0=no): ${ERRORS}" >> ${SUM_OUTPUT}




echo "---------------------" >> ${OUTPUT}
echo "all Errors : ${ERROR_SUM}" >> ${SUM_OUTPUT}
echo >> ${SUM_OUTPUT}
date >> ${SUM_OUTPUT}

cd ${ORIGINAL_DIR}
cat ${OUTPUT} > ${ORIGINAL_DIR}/result/basicMemtest.txt


#kill the tail process
sleep 1
kill ${TAIL_PID} > /dev/null 2>&1




