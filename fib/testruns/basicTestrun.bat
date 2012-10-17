@REM  File Name: basicTestrun.bat
@REM  Author: Betti Oesterholz ; Date: 20.03.2012
@REM  System: batch
@REM 
@REM  Copyright (C) 2012  Betti Oesterholz
@REM 
@REM  Description: a basic test for the Fib multimedia langeage libary
@REM  Time: less then 5 minutes
@REM 
@REM  Attention: You have to be in the direction of this file to run it.
@REM 
@REM History:
@REM  20.03.2012   Oesterholz   created


@echo OFF


IF NOT exist result (
	md result
)

prompt -

set ORIGINAL_DIR=%cd%
set OUTPUT=%ORIGINAL_DIR%\result\basicOut.txt
set SUM_OUTPUT=%ORIGINAL_DIR%\result\basicSum.txt
set ERRORS=0
set ERROR_SUM=0

@REM  empty output files
date /t >%OUTPUT%
time /t >%OUTPUT%
date /t >%SUM_OUTPUT%
time /t >%SUM_OUTPUT%


cd ..\testcase >> %OUTPUT% 2>&1

IF NOT exist test_output (
	md test_output
)


@REM tail -fq %SUM_OUTPUT% &
@REM set TAIL_PID=$(first $(ps | grep tail))

echo
@REM evaluate testcases


tTypeDimension >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tTypeDimension : %ERRORS% >>%SUM_OUTPUT%

tTypeProperty >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tTypeProperty : %ERRORS% >>%SUM_OUTPUT%

tTypeInVar >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tTypeInVar : %ERRORS% >>%SUM_OUTPUT%

tTypeVariable >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tTypeVariable : %ERRORS% >>%SUM_OUTPUT%

tTypeComments >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tTypeComments : %ERRORS% >>%SUM_OUTPUT%

tTypeArea >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tTypeArea : %ERRORS% >>%SUM_OUTPUT%

tTypeUnderFunction >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tTypeUnderFunction : %ERRORS% >>%SUM_OUTPUT%

tTypeExtObject >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tTypeExtObject : %ERRORS% >>%SUM_OUTPUT%

tTypeExtObjectInput >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tTypeExtObjectInput : %ERRORS% >>%SUM_OUTPUT%

tTypeExtSubobject >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tTypeExtSubobject : %ERRORS% >>%SUM_OUTPUT%

tTypeFibSet >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tTypeFibSet : %ERRORS% >>%SUM_OUTPUT%

tTypeFibMatrix >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tTypeFibMatrix : %ERRORS% >>%SUM_OUTPUT%


tDomainNaturalNumberBit >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tDomainNaturalNumberBit : %ERRORS% >>%SUM_OUTPUT%

tDomainNaturalNumber >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tDomainNaturalNumber : %ERRORS% >>%SUM_OUTPUT%

tDomainInteger >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tDomainInteger : %ERRORS% >>%SUM_OUTPUT%

tDomainIntegerBit >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tDomainIntegerBit : %ERRORS% >>%SUM_OUTPUT%

tDomainRational >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tDomainRational : %ERRORS% >>%SUM_OUTPUT%

tDomainVector >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tDomainVector : %ERRORS% >>%SUM_OUTPUT%

tDomainVectorOpenEnd >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tDomainVectorOpenEnd : %ERRORS% >>%SUM_OUTPUT%

tDomainReference >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tDomainReference : %ERRORS% >>%SUM_OUTPUT%


tDomainElement >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tDomainElement : %ERRORS% >>%SUM_OUTPUT%

tDomains >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tDomains : %ERRORS% >>%SUM_OUTPUT%


tMultimediaInfo >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tMultimediaInfo : %ERRORS% >>%SUM_OUTPUT%

tOptionalPart >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tOptionalPart : %ERRORS% >>%SUM_OUTPUT%


tFibVariable >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFibVariable : %ERRORS% >>%SUM_OUTPUT%

tVectorPosition >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tVectorPosition : %ERRORS% >>%SUM_OUTPUT%

tVectorProperty >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tVectorProperty : %ERRORS% >>%SUM_OUTPUT%

tVectorChecksum >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tVectorChecksum : %ERRORS% >>%SUM_OUTPUT%

tVectorArea >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tVectorArea : %ERRORS% >>%SUM_OUTPUT%

tVectorFibSet >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tVectorFibSet : %ERRORS% >>%SUM_OUTPUT%

tVectorFibMatrix >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tVectorFibMatrix : %ERRORS% >>%SUM_OUTPUT%

tVectorExtObject >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tVectorExtObject : %ERRORS% >>%SUM_OUTPUT%

tVectorExtSubobject >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tVectorExtSubobject : %ERRORS% >>%SUM_OUTPUT%


tRoot >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tRoot : %ERRORS% >>%SUM_OUTPUT%

tList >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tList : %ERRORS% >>%SUM_OUTPUT%

tPoint >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tPoint : %ERRORS% >>%SUM_OUTPUT%

tProperty >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tProperty : %ERRORS% >>%SUM_OUTPUT%

tArea >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tArea : %ERRORS% >>%SUM_OUTPUT%

tFunction >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFunction : %ERRORS% >>%SUM_OUTPUT%

tFunctionValue >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFunctionValue : %ERRORS% >>%SUM_OUTPUT%

tFunctionVariable >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFunctionVariable : %ERRORS% >>%SUM_OUTPUT%

tFunctionOneValue >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFunctionOneValue : %ERRORS% >>%SUM_OUTPUT%

tFunctionTwoValue >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFunctionTwoValue : %ERRORS% >>%SUM_OUTPUT%

tFunctionIf >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFunctionIf : %ERRORS% >>%SUM_OUTPUT%

tComment >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tComment : %ERRORS% >>%SUM_OUTPUT%

tIf >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tIf : %ERRORS% >>%SUM_OUTPUT%

tConditionTrue >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tConditionTrue : %ERRORS% >>%SUM_OUTPUT%

tConditionFalse >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tConditionFalse : %ERRORS% >>%SUM_OUTPUT%

tConditionNot >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tConditionNot : %ERRORS% >>%SUM_OUTPUT%

tConditionTwoValue >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tConditionTwoValue : %ERRORS% >>%SUM_OUTPUT%

tConditionComparison >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tConditionComparison : %ERRORS% >>%SUM_OUTPUT%

tExtObject >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tExtObject : %ERRORS% >>%SUM_OUTPUT%

tExtSubobject >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tExtSubobject : %ERRORS% >>%SUM_OUTPUT%

tFibSet >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFibSet : %ERRORS% >>%SUM_OUTPUT%

tFibMatrix >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFibMatrix : %ERRORS% >>%SUM_OUTPUT%




REM tests which work random and can be resized

tGenerateFibObjects 8 1 >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tGenerateFibObjects : %ERRORS% >>%SUM_OUTPUT%

tFibObjectVariable 16 1 >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFibObjectVariable : %ERRORS% >>%SUM_OUTPUT%

tFibObject 34 1 >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFibObject : %ERRORS% >>%SUM_OUTPUT%

tFibElementStructur 16 1 >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFibElementStructur : %ERRORS% >>%SUM_OUTPUT%

tFibObjectStore 34 1 >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFibObjectStore : %ERRORS% >>%SUM_OUTPUT%

tEvalueObject ..\testObjects\ >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tEvalueObject : %ERRORS% >>%SUM_OUTPUT%

tFibDatabase 64 ..\testObjects\testFibDatabase\ >> %OUTPUT% 2>&1
set ERRORS=%errorlevel%
set /a ERROR_SUM = %ERROR_SUM% + %ERRORS%
echo Errors in tFibDatabase : %ERRORS% >>%SUM_OUTPUT%



echo --------------------- >>%SUM_OUTPUT%
echo all Errors : %ERROR_SUM% >>%SUM_OUTPUT%
echo >>%SUM_OUTPUT%
date /t >>%SUM_OUTPUT%
time /t  >>%SUM_OUTPUT%

type %SUM_OUTPUT%
cd %ORIGINAL_DIR%
type %OUTPUT% %SUM_OUTPUT% > %ORIGINAL_DIR%\result\basic.txt


@REM kill the tail process
@REM sleep 1
@REM kill %TAIL_PID% > /dev/null 2>&1



