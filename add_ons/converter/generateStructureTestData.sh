#!/bin/bash
#
# Copyright (C) 2013 Betti Oesterholz
#
# Author: Betti Oesterholz
#
#######################################################################
#
# This script repeats the a test in an endless loop.
#
# History:
#

FOLDER_WITH_DATA=tmp/

FILE_GENERATED_FILE=${FOLDER_WITH_DATA}Wikitanface.bmp.xml

if [ -e ${FILE_GENERATED_FILE} ]; then
	bin/test_convertFromFib ${FILE_GENERATED_FILE} ${FILE_GENERATED_FILE}.bmp
	bin/test_convertFibToFib ${FILE_GENERATED_FILE} ${FILE_GENERATED_FILE}.fib
	../../fib/testcase/countElementsAndBits ${FILE_GENERATED_FILE}.fib > ${FOLDER_WITH_DATA}/elementCount.txt 2>&1
fi


if [ -e ${FOLDER_WITH_DATA}borderData.xml ]; then
	bin/test_convertFromImageStructure ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureData.bmp
	bin/test_convertFromImageStructure -bg=green ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataGreen.bmp &

	bin/test_convertFromImageStructure -bg=green -justAA ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataAA.bmp
	bin/test_convertFromImageStructure -bg=green -justNotAA ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataAANot.bmp &

	bin/test_convertFromImageStructure -bg=green -last=10 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0010.bmp
	bin/test_convertFromImageStructure -bg=green -last=20 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0020.bmp &
	bin/test_convertFromImageStructure -bg=green -last=30 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0030.bmp
	bin/test_convertFromImageStructure -bg=green -last=40 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0040.bmp &
	bin/test_convertFromImageStructure -bg=green -last=50 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0050.bmp &

	bin/test_convertFromImageStructure -bg=green -last=100 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0100.bmp
	bin/test_convertFromImageStructure -bg=green -last=200 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0200.bmp &
	bin/test_convertFromImageStructure -bg=green -last=300 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0300.bmp &
	bin/test_convertFromImageStructure -bg=green -last=400 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0400.bmp
	bin/test_convertFromImageStructure -bg=green -last=500 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0500.bmp &
	bin/test_convertFromImageStructure -bg=green -last=600 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0600.bmp &
	bin/test_convertFromImageStructure -bg=green -last=700 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0700.bmp
	bin/test_convertFromImageStructure -bg=green -last=800 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0800.bmp &
	bin/test_convertFromImageStructure -bg=green -last=900 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast0900.bmp &

	bin/test_convertFromImageStructure -bg=green -last=1000 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast1000.bmp
	bin/test_convertFromImageStructure -bg=green -last=2000 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast2000.bmp &
	bin/test_convertFromImageStructure -bg=green -last=3000 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast3000.bmp
	bin/test_convertFromImageStructure -bg=green -last=4000 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast4000.bmp &
	bin/test_convertFromImageStructure -bg=green -last=5000 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast5000.bmp
	bin/test_convertFromImageStructure -bg=green -last=6000 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast6000.bmp &
	bin/test_convertFromImageStructure -bg=green -last=7000 ${FOLDER_WITH_DATA}structureData.xml ${FOLDER_WITH_DATA}structureDataLast7000.bmp
fi

#border data
if [ -e ${FOLDER_WITH_DATA}borderData.xml ]; then
	bin/test_convertFromImageStructure ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData.bmp

	bin/test_convertFromImageStructure -last=10 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0010.bmp &
	bin/test_convertFromImageStructure -last=20 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0020.bmp &
	bin/test_convertFromImageStructure -last=30 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0030.bmp
	bin/test_convertFromImageStructure -last=40 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0040.bmp &
	bin/test_convertFromImageStructure -last=50 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0050.bmp &

	bin/test_convertFromImageStructure -last=100 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0100.bmp
	bin/test_convertFromImageStructure -last=200 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0200.bmp &
	bin/test_convertFromImageStructure -last=300 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0300.bmp &
	bin/test_convertFromImageStructure -last=400 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0400.bmp
	bin/test_convertFromImageStructure -last=500 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0500.bmp &
	bin/test_convertFromImageStructure -last=600 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0600.bmp &
	bin/test_convertFromImageStructure -last=700 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0700.bmp
	bin/test_convertFromImageStructure -last=800 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0800.bmp &
	bin/test_convertFromImageStructure -last=900 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast0900.bmp &

	bin/test_convertFromImageStructure -last=1000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast1000.bmp
	bin/test_convertFromImageStructure -last=2000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast2000.bmp &
	bin/test_convertFromImageStructure -last=3000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast3000.bmp
	bin/test_convertFromImageStructure -last=4000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast4000.bmp &
	bin/test_convertFromImageStructure -last=5000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast5000.bmp
	bin/test_convertFromImageStructure -last=6000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast6000.bmp
	bin/test_convertFromImageStructure -last=7000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderDataLast7000.bmp


	bin/test_convertFromImageStructure -first=0 -last=10 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0000T0010.bmp &
	bin/test_convertFromImageStructure -first=10 -last=20 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0010T0020.bmp &
	bin/test_convertFromImageStructure -first=20 -last=30 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0020T0030.bmp
	bin/test_convertFromImageStructure -first=30 -last=40 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0030T0040.bmp &
	bin/test_convertFromImageStructure -first=40 -last=50 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0040T0050.bmp &
	bin/test_convertFromImageStructure -first=50 -last=100 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0050T0100.bmp
	bin/test_convertFromImageStructure -first=100 -last=200 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0100T0200.bmp &
	bin/test_convertFromImageStructure -first=200 -last=300 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0200T0300.bmp &
	bin/test_convertFromImageStructure -first=300 -last=400 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0300T0400.bmp
	bin/test_convertFromImageStructure -first=400 -last=500 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0400T0500.bmp &
	bin/test_convertFromImageStructure -first=500 -last=600 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0500T0600.bmp &
	bin/test_convertFromImageStructure -first=600 -last=700 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0600T0700.bmp
	bin/test_convertFromImageStructure -first=700 -last=800 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0700T0800.bmp &
	bin/test_convertFromImageStructure -first=800 -last=900 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0800T0900.bmp &
	bin/test_convertFromImageStructure -first=900 -last=1000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData0900T1000.bmp
	bin/test_convertFromImageStructure -first=1000 -last=2000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData1000T2000.bmp &
	bin/test_convertFromImageStructure -first=2000 -last=3000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData2000T3000.bmp
	bin/test_convertFromImageStructure -first=3000 -last=4000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData3000T4000.bmp &
	bin/test_convertFromImageStructure -first=4000 -last=5000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData4000T5000.bmp
	bin/test_convertFromImageStructure -first=5000 -last=6000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData5000T6000.bmp
	bin/test_convertFromImageStructure -first=6000 -last=7000 ${FOLDER_WITH_DATA}borderData.xml ${FOLDER_WITH_DATA}borderData6000T7000.bmp
fi

#border border data
if [ -e ${FOLDER_WITH_DATA}structureBorderData.xml ]; then
	bin/test_convertFromImageStructure ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData.bmp

	bin/test_convertFromImageStructure -last=10 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0010.bmp
	bin/test_convertFromImageStructure -last=20 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0020.bmp &
	bin/test_convertFromImageStructure -last=30 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0030.bmp &
	bin/test_convertFromImageStructure -last=40 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0040.bmp
	bin/test_convertFromImageStructure -last=50 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0050.bmp &

	bin/test_convertFromImageStructure -last=100 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0100.bmp
	bin/test_convertFromImageStructure -last=200 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0200.bmp &
	bin/test_convertFromImageStructure -last=300 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0300.bmp &
	bin/test_convertFromImageStructure -last=400 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0400.bmp
	bin/test_convertFromImageStructure -last=500 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0500.bmp &
	bin/test_convertFromImageStructure -last=600 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0600.bmp &
	bin/test_convertFromImageStructure -last=700 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0700.bmp
	bin/test_convertFromImageStructure -last=800 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0800.bmp &
	bin/test_convertFromImageStructure -last=900 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast0900.bmp &

	bin/test_convertFromImageStructure -last=1000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast1000.bmp
	bin/test_convertFromImageStructure -last=2000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast2000.bmp &
	bin/test_convertFromImageStructure -last=3000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast3000.bmp
	bin/test_convertFromImageStructure -last=4000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast4000.bmp &
	bin/test_convertFromImageStructure -last=5000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast5000.bmp
	bin/test_convertFromImageStructure -last=6000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast6000.bmp
	bin/test_convertFromImageStructure -last=7000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderDataLast7000.bmp


	bin/test_convertFromImageStructure -first=0 -last=10 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0000T0010.bmp &
	bin/test_convertFromImageStructure -first=10 -last=20 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0010T0020.bmp &
	bin/test_convertFromImageStructure -first=20 -last=30 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0020T0030.bmp
	bin/test_convertFromImageStructure -first=30 -last=40 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0030T0040.bmp &
	bin/test_convertFromImageStructure -first=40 -last=50 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0040T0050.bmp &
	bin/test_convertFromImageStructure -first=50 -last=100 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0050T0100.bmp
	bin/test_convertFromImageStructure -first=100 -last=200 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0100T0200.bmp &
	bin/test_convertFromImageStructure -first=200 -last=300 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0200T0300.bmp &
	bin/test_convertFromImageStructure -first=300 -last=400 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0300T0400.bmp
	bin/test_convertFromImageStructure -first=400 -last=500 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0400T0500.bmp &
	bin/test_convertFromImageStructure -first=500 -last=600 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0500T0600.bmp &
	bin/test_convertFromImageStructure -first=600 -last=700 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0600T0700.bmp
	bin/test_convertFromImageStructure -first=700 -last=800 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0700T0800.bmp &
	bin/test_convertFromImageStructure -first=800 -last=900 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0800T0900.bmp &
	bin/test_convertFromImageStructure -first=900 -last=1000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData0900T1000.bmp
	bin/test_convertFromImageStructure -first=1000 -last=2000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData1000T2000.bmp &
	bin/test_convertFromImageStructure -first=2000 -last=3000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData2000T3000.bmp
	bin/test_convertFromImageStructure -first=3000 -last=4000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData3000T4000.bmp &
	bin/test_convertFromImageStructure -first=4000 -last=5000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData4000T5000.bmp
	bin/test_convertFromImageStructure -first=5000 -last=6000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData5000T6000.bmp
	bin/test_convertFromImageStructure -first=6000 -last=7000 ${FOLDER_WITH_DATA}structureBorderData.xml ${FOLDER_WITH_DATA}structureBorderData6000T7000.bmp
fi


if [ -e ${FOLDER_WITH_DATA}structureOverlappedData.xml ]; then
	bin/test_convertFromImageStructure -last=1 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0001.bmp
	
	bin/test_convertFromImageStructure -first=0 -last=1 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0000T0001.bmp &
	bin/test_convertFromImageStructure -first=1 -last=2 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0001T0002.bmp &
	bin/test_convertFromImageStructure -first=2 -last=3 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0002T0003.bmp
	bin/test_convertFromImageStructure -first=3 -last=4 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0003T0004.bmp &
	bin/test_convertFromImageStructure -first=4 -last=5 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0004T0005.bmp &
	
	bin/test_convertFromImageStructure -last=10 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0010.bmp
	bin/test_convertFromImageStructure -last=20 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0020.bmp &
	bin/test_convertFromImageStructure -last=30 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0030.bmp &
	bin/test_convertFromImageStructure -last=40 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0040.bmp
	bin/test_convertFromImageStructure -last=50 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0050.bmp &

	bin/test_convertFromImageStructure -first=0 -last=10 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0000T0010.bmp &
	bin/test_convertFromImageStructure -first=10 -last=20 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0010T0020.bmp &
	bin/test_convertFromImageStructure -first=20 -last=30 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0020T0030.bmp
	bin/test_convertFromImageStructure -first=30 -last=40 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0030T0040.bmp &
	bin/test_convertFromImageStructure -first=40 -last=50 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0040T0050.bmp &
	bin/test_convertFromImageStructure -first=50 -last=100 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0050T0100.bmp
	
	bin/test_convertFromImageStructure -last=100 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0100.bmp
	bin/test_convertFromImageStructure -last=200 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0200.bmp &
	bin/test_convertFromImageStructure -last=300 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0300.bmp
	bin/test_convertFromImageStructure -last=400 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0400.bmp
	bin/test_convertFromImageStructure -last=500 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0500.bmp
	bin/test_convertFromImageStructure -last=600 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0600.bmp
	bin/test_convertFromImageStructure -last=700 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0700.bmp
	bin/test_convertFromImageStructure -last=800 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0800.bmp
	bin/test_convertFromImageStructure -last=900 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast0900.bmp

	bin/test_convertFromImageStructure -last=1000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast1000.bmp
	bin/test_convertFromImageStructure -last=2000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast2000.bmp
	bin/test_convertFromImageStructure -last=3000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast3000.bmp
	bin/test_convertFromImageStructure -last=4000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast4000.bmp
	bin/test_convertFromImageStructure -last=5000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast5000.bmp
	bin/test_convertFromImageStructure -last=6000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast6000.bmp
	bin/test_convertFromImageStructure -last=7000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedDataLast7000.bmp

	bin/test_convertFromImageStructure ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData.bmp
	
	bin/test_convertFromImageStructure -first=100 -last=200 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0100T0200.bmp &
	bin/test_convertFromImageStructure -first=200 -last=300 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0200T0300.bmp
	bin/test_convertFromImageStructure -first=300 -last=400 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0300T0400.bmp
	bin/test_convertFromImageStructure -first=400 -last=500 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0400T0500.bmp
	bin/test_convertFromImageStructure -first=500 -last=600 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0500T0600.bmp
	bin/test_convertFromImageStructure -first=600 -last=700 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0600T0700.bmp
	bin/test_convertFromImageStructure -first=700 -last=800 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0700T0800.bmp
	bin/test_convertFromImageStructure -first=800 -last=900 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0800T0900.bmp
	bin/test_convertFromImageStructure -first=900 -last=1000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData0900T1000.bmp
	bin/test_convertFromImageStructure -first=1000 -last=2000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData1000T2000.bmp
	bin/test_convertFromImageStructure -first=2000 -last=3000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData2000T3000.bmp
	bin/test_convertFromImageStructure -first=3000 -last=4000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData3000T4000.bmp
	bin/test_convertFromImageStructure -first=4000 -last=5000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData4000T5000.bmp
	bin/test_convertFromImageStructure -first=5000 -last=6000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData5000T6000.bmp
	bin/test_convertFromImageStructure -first=6000 -last=7000 ${FOLDER_WITH_DATA}structureOverlappedData.xml ${FOLDER_WITH_DATA}structureOverlappedData6000T7000.bmp
fi


if [ -e ${FOLDER_WITH_DATA}genAreaData.xml ]; then
	
	bin/test_convertFromImageStructure ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData.bmp &
	
	for (( NUMBER=0; NUMBER <= 20; NUMBER++ ))
	do
		NUMBER_L5=`printf "%05d" $NUMBER`
		bin/test_convertFromImageStructure -first=${NUMBER} -last=${NUMBER} ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataNR${NUMBER_L5}.bmp
	done
	
	for (( NUMBER=100; NUMBER <= 120; NUMBER++ ))
	do
		NUMBER_L5=`printf "%05d" $NUMBER`
		bin/test_convertFromImageStructure -first=${NUMBER} -last=${NUMBER} ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataNR${NUMBER_L5}.bmp
	done
	
	for (( NUMBER=1000; NUMBER <= 1020; NUMBER++ ))
	do
		NUMBER_L5=`printf "%05d" $NUMBER`
		bin/test_convertFromImageStructure -first=${NUMBER} -last=${NUMBER} ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataNR${NUMBER_L5}.bmp
	done
	
	bin/test_convertFromImageStructure -last=10 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0010.bmp
	bin/test_convertFromImageStructure -last=20 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0020.bmp &
	bin/test_convertFromImageStructure -last=30 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0030.bmp &
	bin/test_convertFromImageStructure -last=40 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0040.bmp
	bin/test_convertFromImageStructure -last=50 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0050.bmp &

	bin/test_convertFromImageStructure -first=0 -last=10 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0000T0010.bmp &
	bin/test_convertFromImageStructure -first=10 -last=20 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0010T0020.bmp &
	bin/test_convertFromImageStructure -first=20 -last=30 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0020T0030.bmp
	bin/test_convertFromImageStructure -first=30 -last=40 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0030T0040.bmp &
	bin/test_convertFromImageStructure -first=40 -last=50 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0040T0050.bmp &
	bin/test_convertFromImageStructure -first=50 -last=100 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0050T0100.bmp
	
	bin/test_convertFromImageStructure -last=100 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0100.bmp
	bin/test_convertFromImageStructure -last=200 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0200.bmp &
	bin/test_convertFromImageStructure -last=300 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0300.bmp
	bin/test_convertFromImageStructure -last=400 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0400.bmp
	bin/test_convertFromImageStructure -last=500 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0500.bmp
	bin/test_convertFromImageStructure -last=600 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0600.bmp
	bin/test_convertFromImageStructure -last=700 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0700.bmp
	bin/test_convertFromImageStructure -last=800 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0800.bmp
	bin/test_convertFromImageStructure -last=900 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast0900.bmp

	bin/test_convertFromImageStructure -last=1000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast1000.bmp
	bin/test_convertFromImageStructure -last=2000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast2000.bmp
	bin/test_convertFromImageStructure -last=3000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast3000.bmp
	bin/test_convertFromImageStructure -last=4000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast4000.bmp
	bin/test_convertFromImageStructure -last=5000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast5000.bmp
	bin/test_convertFromImageStructure -last=6000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast6000.bmp
	bin/test_convertFromImageStructure -last=7000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaDataLast7000.bmp
	
	
	bin/test_convertFromImageStructure -first=100 -last=200 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0100T0200.bmp &
	bin/test_convertFromImageStructure -first=200 -last=300 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0200T0300.bmp
	bin/test_convertFromImageStructure -first=300 -last=400 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0300T0400.bmp
	bin/test_convertFromImageStructure -first=400 -last=500 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0400T0500.bmp
	bin/test_convertFromImageStructure -first=500 -last=600 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0500T0600.bmp
	bin/test_convertFromImageStructure -first=600 -last=700 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0600T0700.bmp
	bin/test_convertFromImageStructure -first=700 -last=800 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0700T0800.bmp
	bin/test_convertFromImageStructure -first=800 -last=900 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0800T0900.bmp
	bin/test_convertFromImageStructure -first=900 -last=1000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData0900T1000.bmp
	bin/test_convertFromImageStructure -first=1000 -last=2000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData1000T2000.bmp
	bin/test_convertFromImageStructure -first=2000 -last=3000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData2000T3000.bmp
	bin/test_convertFromImageStructure -first=3000 -last=4000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData3000T4000.bmp
	bin/test_convertFromImageStructure -first=4000 -last=5000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData4000T5000.bmp
	bin/test_convertFromImageStructure -first=5000 -last=6000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData5000T6000.bmp
	bin/test_convertFromImageStructure -first=6000 -last=7000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData6000T7000.bmp
	bin/test_convertFromImageStructure -first=7000 -last=8000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData7000T8000.bmp
	bin/test_convertFromImageStructure -first=8000 -last=9000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData8000T9000.bmp
	bin/test_convertFromImageStructure -first=9000 -last=10000 ${FOLDER_WITH_DATA}genAreaData.xml ${FOLDER_WITH_DATA}genAreaData9000T10000.bmp
fi


