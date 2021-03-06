#!/bin/bash
#
# File Name: basicTestrun.sh
# Author: Betti Oesterholz ; Date: 03.07.2009
# System: bash
#
# Copyright (C) 2009  Betti Oesterholz
#
# Description: a basic test for the Fib -multimedialangeage libary
# Time: less then 5 minutes
#
# Attention: You have to be in the direction of this file to run it.
#
#History:
# 19.12.2009   Oesterholz   tList added
# 30.12.2009   Oesterholz   tGenerateFibObjects added
# 01.01.2010   Oesterholz   tDomainNaturalNumber added
# 01.01.2010   Oesterholz   tFibElementStructur and tFibObject added
# 30.01.2010   Oesterholz   tFibObjectStore added
# 19.02.2010   Oesterholz   tArea added
# 22.04.2010   Oesterholz   tTypeUnderFunction
# 22.04.2010   Oesterholz   tFunction
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
# 06.06.2011   Oesterholz   tFunctionIf added
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
# 07.01.2012   Oesterholz   tVectorExtObject added
# 21.01.2012   Oesterholz   tTypeExtObjectInput added
# 04.02.2012   Oesterholz   tTypeExtSubobject and tVectorExtSubobject added
# 14.02.2012   Oesterholz   tDomainReference added
# 09.03.2013   Oesterholz   tMatrix3D added
# 11.05.2013   Oesterholz   tFibDatatyps added
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
./tFibDatatyps 1024 >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibDatatyps : ${ERRORS}" >>${SUM_OUTPUT}


./tTypeDimension >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeDimension : ${ERRORS}" >>${SUM_OUTPUT}

./tTypeProperty >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeProperty : ${ERRORS}" >>${SUM_OUTPUT}

./tTypeInVar >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeInVar : ${ERRORS}" >>${SUM_OUTPUT}

./tTypeVariable >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeVariable : ${ERRORS}" >>${SUM_OUTPUT}

./tTypeComments >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeComments : ${ERRORS}" >>${SUM_OUTPUT}

./tTypeArea >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeArea : ${ERRORS}" >>${SUM_OUTPUT}

./tTypeUnderFunction >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeUnderFunction : ${ERRORS}" >>${SUM_OUTPUT}

./tTypeExtObject >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeExtObject : ${ERRORS}" >>${SUM_OUTPUT}

./tTypeExtObjectInput >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeExtObjectInput : ${ERRORS}" >>${SUM_OUTPUT}

./tTypeExtSubobject >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeExtSubobject : ${ERRORS}" >>${SUM_OUTPUT}

./tTypeFibSet >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeFibSet : ${ERRORS}" >>${SUM_OUTPUT}

./tTypeFibMatrix >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tTypeFibMatrix : ${ERRORS}" >>${SUM_OUTPUT}


./tDomainNaturalNumberBit >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainNaturalNumberBit : ${ERRORS}" >>${SUM_OUTPUT}

./tDomainNaturalNumber >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainNaturalNumber : ${ERRORS}" >>${SUM_OUTPUT}

./tDomainInteger >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainInteger : ${ERRORS}" >>${SUM_OUTPUT}

./tDomainIntegerBit >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainIntegerBit : ${ERRORS}" >>${SUM_OUTPUT}

./tDomainRational >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainRational : ${ERRORS}" >>${SUM_OUTPUT}

./tDomainVector >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainVector : ${ERRORS}" >>${SUM_OUTPUT}

./tDomainVectorOpenEnd >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainVectorOpenEnd : ${ERRORS}" >>${SUM_OUTPUT}

./tDomainReference >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainReference : ${ERRORS}" >>${SUM_OUTPUT}


./tDomainElement >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomainElement : ${ERRORS}" >>${SUM_OUTPUT}

./tDomains >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tDomains : ${ERRORS}" >>${SUM_OUTPUT}


./tMultimediaInfo >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tMultimediaInfo : ${ERRORS}" >>${SUM_OUTPUT}

./tOptionalPart >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tOptionalPart : ${ERRORS}" >>${SUM_OUTPUT}


./tFibVariable >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibVariable : ${ERRORS}" >>${SUM_OUTPUT}

./tVectorPosition >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorPosition : ${ERRORS}" >>${SUM_OUTPUT}

./tVectorProperty >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorProperty : ${ERRORS}" >>${SUM_OUTPUT}

./tVectorChecksum >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorChecksum : ${ERRORS}" >>${SUM_OUTPUT}

./tVectorArea >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorArea : ${ERRORS}" >>${SUM_OUTPUT}

./tVectorFibSet >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorFibSet : ${ERRORS}" >>${SUM_OUTPUT}

./tVectorFibMatrix >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorFibMatrix : ${ERRORS}" >>${SUM_OUTPUT}

./tVectorExtObject >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorExtObject : ${ERRORS}" >>${SUM_OUTPUT}

./tVectorExtSubobject >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tVectorExtSubobject : ${ERRORS}" >>${SUM_OUTPUT}


./tRoot >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tRoot : ${ERRORS}" >>${SUM_OUTPUT}

./tList >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tList : ${ERRORS}" >>${SUM_OUTPUT}

./tPoint >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tPoint : ${ERRORS}" >>${SUM_OUTPUT}

./tProperty >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tProperty : ${ERRORS}" >>${SUM_OUTPUT}

./tArea >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tArea : ${ERRORS}" >>${SUM_OUTPUT}

./tFunction >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFunction : ${ERRORS}" >>${SUM_OUTPUT}

./tFunctionValue >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFunctionValue : ${ERRORS}" >>${SUM_OUTPUT}

./tFunctionVariable >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFunctionVariable : ${ERRORS}" >>${SUM_OUTPUT}

./tFunctionOneValue >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFunctionOneValue : ${ERRORS}" >>${SUM_OUTPUT}

./tFunctionTwoValue >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFunctionTwoValue : ${ERRORS}" >>${SUM_OUTPUT}

./tFunctionIf >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFunctionIf : ${ERRORS}" >>${SUM_OUTPUT}

./tComment >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tComment : ${ERRORS}" >>${SUM_OUTPUT}

./tIf >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tIf : ${ERRORS}" >>${SUM_OUTPUT}

./tConditionTrue >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tConditionTrue : ${ERRORS}" >>${SUM_OUTPUT}

./tConditionFalse >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tConditionFalse : ${ERRORS}" >>${SUM_OUTPUT}

./tConditionNot >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tConditionNot : ${ERRORS}" >>${SUM_OUTPUT}

./tConditionTwoValue >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tConditionTwoValue : ${ERRORS}" >>${SUM_OUTPUT}

./tConditionComparison >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tConditionComparison : ${ERRORS}" >>${SUM_OUTPUT}

./tExtObject >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tExtObject : ${ERRORS}" >>${SUM_OUTPUT}

./tExtSubobject >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tExtSubobject : ${ERRORS}" >>${SUM_OUTPUT}

./tFibSet >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibSet : ${ERRORS}" >>${SUM_OUTPUT}

./tFibMatrix >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibMatrix : ${ERRORS}" >>${SUM_OUTPUT}




#tests which work random and can be resized

./tGenerateFibObjects 128 1 >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tGenerateFibObjects : ${ERRORS}" >>${SUM_OUTPUT}

./tFibObjectStore 512 1 >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibObjectStore : ${ERRORS}" >>${SUM_OUTPUT}

./tFibObjectVariable 256 1 >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibObjectVariable : ${ERRORS}" >>${SUM_OUTPUT}

./tFibObject 512 1 >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibObject : ${ERRORS}" >>${SUM_OUTPUT}

./tFibElementStructur 256 1 >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibElementStructur : ${ERRORS}" >>${SUM_OUTPUT}

./tEvalueObject ../testObjects/ >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tEvalueObject : ${ERRORS}" >>${SUM_OUTPUT}

./tFibDatabase 512 ../testObjects/testFibDatabase/ >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tFibDatabase : ${ERRORS}" >>${SUM_OUTPUT}


./tMatrix3D 64 >>${OUTPUT} 2>>${ERROR_OUTPUT}
ERRORS=$?
ERROR_SUM=$(expr ${ERROR_SUM} + ${ERRORS})
echo "Errors in tMatrix3D : ${ERRORS}" >>${SUM_OUTPUT}



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



