#!/bin/bash
#
# File Name: basicMemtest.sh
# Author: Betti Oesterholz ; Date: 23.02.2010
# System: bash
#
# Copyright (C) 2009  Betti Oesterholz
#
# Description: a basic test on memoryleaks for the Fib -multimedialangeage libary
# Time: less then 5 minutes
#
# Attention: You have to be in the direction of this file to run it.
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
echo "Memoryleaks in tTypeDimension:" >>${OUTPUT}
${LEAK_CHECKER} ./tTypeDimension > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tTypeDimension >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tTypeProperty" >>${OUTPUT}
${LEAK_CHECKER} ./tTypeProperty > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tTypeProperty >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tTypeInVar" >>${OUTPUT}
${LEAK_CHECKER} ./tTypeInVar > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tTypeInVar >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tTypeVariable" >>${OUTPUT}
${LEAK_CHECKER} ./tTypeVariable > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tTypeVariable >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tTypeComments" >>${OUTPUT}
${LEAK_CHECKER} ./tTypeComments > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tTypeComments >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tTypeArea" >>${OUTPUT}
${LEAK_CHECKER} ./tTypeArea > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tTypeArea >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tTypeUnderFunction" >>${OUTPUT}
${LEAK_CHECKER} ./tTypeUnderFunction > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tTypeUnderFunction >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tTypeExtObject" >>${OUTPUT}
${LEAK_CHECKER} ./tTypeExtObject > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tTypeExtObject >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tTypeExtObjectInput" >>${OUTPUT}
${LEAK_CHECKER} ./tTypeExtObjectInput > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tTypeExtObjectInput >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tTypeExtSubobject" >>${OUTPUT}
${LEAK_CHECKER} ./tTypeExtSubobject > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tTypeExtSubobject >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tTypeFibSet" >>${OUTPUT}
${LEAK_CHECKER} ./tTypeFibSet > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tTypeFibSet >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tTypeFibMatrix" >>${OUTPUT}
${LEAK_CHECKER} ./tTypeFibMatrix > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tTypeFibMatrix >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}


echo >>${OUTPUT}
echo "Memoryleaks in tDomainNaturalNumberBit" >>${OUTPUT}
${LEAK_CHECKER} ./tDomainNaturalNumberBit > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tDomainNaturalNumberBit >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tDomainNaturalNumber" >>${OUTPUT}
${LEAK_CHECKER} ./tDomainNaturalNumber > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tDomainNaturalNumber >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tDomainInteger" >>${OUTPUT}
${LEAK_CHECKER} ./tDomainInteger > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tDomainInteger >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tDomainIntegerBit" >>${OUTPUT}
${LEAK_CHECKER} ./tDomainIntegerBit > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tDomainIntegerBit >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tDomainRational" >>${OUTPUT}
${LEAK_CHECKER} ./tDomainRational > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tDomainRational >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tDomainVector" >>${OUTPUT}
${LEAK_CHECKER} ./tDomainVector > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tDomainVector >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tDomainVectorOpenEnd" >>${OUTPUT}
${LEAK_CHECKER} ./tDomainVectorOpenEnd > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tDomainVectorOpenEnd >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tDomainReference" >>${OUTPUT}
${LEAK_CHECKER} ./tDomainReference > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tDomainReference >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}


echo >>${OUTPUT}
echo "Memoryleaks in tDomainElement" >>${OUTPUT}
${LEAK_CHECKER} ./tDomainElement > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tDomainElement >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tDomains" >>${OUTPUT}
${LEAK_CHECKER} ./tDomains > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tDomains >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tMultimediaInfo" >>${OUTPUT}
${LEAK_CHECKER} ./tMultimediaInfo > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tMultimediaInfo >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tOptionalPart" >>${OUTPUT}
${LEAK_CHECKER} ./tOptionalPart > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tOptionalPart >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFibVariable" >>${OUTPUT}
${LEAK_CHECKER} ./tFibVariable > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibVariable >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tVectorPosition" >>${OUTPUT}
${LEAK_CHECKER} ./tVectorPosition > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tVectorPosition >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tVectorProperty" >>${OUTPUT}
${LEAK_CHECKER} ./tVectorProperty > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tVectorProperty >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tVectorChecksum" >>${OUTPUT}
${LEAK_CHECKER} ./tVectorChecksum > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tVectorChecksum >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tVectorArea" >>${OUTPUT}
${LEAK_CHECKER} ./tVectorArea > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tVectorArea >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tVectorFibSet" >>${OUTPUT}
${LEAK_CHECKER} ./tVectorFibSet > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tVectorFibSet >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tVectorFibMatrix" >>${OUTPUT}
${LEAK_CHECKER} ./tVectorFibMatrix > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tVectorFibMatrix >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tVectorExtObject" >>${OUTPUT}
${LEAK_CHECKER} ./tVectorExtObject > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tVectorExtObject >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tVectorExtSubobject" >>${OUTPUT}
${LEAK_CHECKER} ./tVectorExtSubobject > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tVectorExtSubobject >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}



echo >>${OUTPUT}
echo "Memoryleaks in tRoot" >>${OUTPUT}
${LEAK_CHECKER} ./tRoot > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tRoot >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tList" >>${OUTPUT}
${LEAK_CHECKER} ./tList > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tList >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tPoint" >>${OUTPUT}
${LEAK_CHECKER} ./tPoint > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tPoint >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tProperty" >>${OUTPUT}
${LEAK_CHECKER} ./tProperty > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tProperty >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tArea" >>${OUTPUT}
${LEAK_CHECKER} ./tArea > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tArea >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFunction" >>${OUTPUT}
${LEAK_CHECKER} ./tFunction > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFunction >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFunctionValue" >>${OUTPUT}
${LEAK_CHECKER} ./tFunctionValue > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFunctionValue >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFunctionVariable" >>${OUTPUT}
${LEAK_CHECKER} ./tFunctionVariable > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFunctionVariable >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFunctionOneValue" >>${OUTPUT}
${LEAK_CHECKER} ./tFunctionOneValue > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFunctionOneValue >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFunctionTwoValue" >>${OUTPUT}
${LEAK_CHECKER} ./tFunctionTwoValue > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFunctionTwoValue >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFunctionIf" >>${OUTPUT}
${LEAK_CHECKER} ./tFunctionIf > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFunctionIf >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tComment" >>${OUTPUT}
${LEAK_CHECKER} ./tComment > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tComment >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tIf" >>${OUTPUT}
${LEAK_CHECKER} ./tIf > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tIf >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tConditionTrue" >>${OUTPUT}
${LEAK_CHECKER} ./tConditionTrue > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tConditionTrue >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tConditionFalse" >>${OUTPUT}
${LEAK_CHECKER} ./tConditionFalse > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tConditionFalse >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tConditionNot" >>${OUTPUT}
${LEAK_CHECKER} ./tConditionNot > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tConditionNot >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tConditionTwoValue" >>${OUTPUT}
${LEAK_CHECKER} ./tConditionTwoValue > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tConditionTwoValue >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tConditionComparison" >>${OUTPUT}
${LEAK_CHECKER} ./tConditionComparison > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tConditionComparison >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tExtObject" >>${OUTPUT}
${LEAK_CHECKER} ./tExtObject > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tExtObject >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tExtSubobject" >>${OUTPUT}
${LEAK_CHECKER} ./tExtSubobject > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tExtSubobject >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFibSet" >>${OUTPUT}
${LEAK_CHECKER} ./tFibSet > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibSet >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFibMatrix" >>${OUTPUT}
${LEAK_CHECKER} ./tFibMatrix > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibMatrix >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}



#tests which work random and can be resized

echo >>${OUTPUT}
echo "Memoryleaks in tGenerateFibObjects" >>${OUTPUT}
${LEAK_CHECKER} ./tGenerateFibObjects 64 1 > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tGenerateFibObjects >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFibObjectVariable" >>${OUTPUT}
${LEAK_CHECKER} ./tFibObjectVariable 64 1 > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibObjectVariable >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFibObject" >>${OUTPUT}
${LEAK_CHECKER} ./tFibObject 64 1 > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibObject >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFibElementStructur" >>${OUTPUT}
${LEAK_CHECKER} ./tFibElementStructur 64 1 > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibElementStructur >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFibObjectStore" >>${OUTPUT}
${LEAK_CHECKER} ./tFibObjectStore 64 1 > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibObjectStore >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tEvalueObject" >>${OUTPUT}
${LEAK_CHECKER} ./tEvalueObject ../testObjects/ > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tEvalueObject >>${OUTPUT} 2>>${ERROR_OUTPUT}
echo >>${OUTPUT}

echo >>${OUTPUT}
echo "Memoryleaks in tFibDatabase" >>${OUTPUT}
${LEAK_CHECKER} ./tFibDatabase 64 ../testObjects/testFibDatabase/ > ${TMP_OUT} 2>&1;${LEAK_ANALYZE} ./tFibDatabase >>${OUTPUT} 2>>${ERROR_OUTPUT}
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




