#!/bin/bash
#
# Copyright (C) 2010 Betti Oesterholz
#
# Author: Betti Oesterholz 
#
#######################################################################
#
# This Script will convert the fib -xml -images in the folder
# "/testdata/todo/" into bmp -images and than copy the result and the
# original fib -file into the folder "/testdata/done/"
#
# call:
#  fibToBmp InDir OutDir MaxTimeInSec PartDir
# 
# parameter:
#   - InDir: the
#
# History:
#  06.05.2010  Oesterholz  created
#


getFirstPart()
{
	echo $1
}


DIR_SOURCE=./testdata/todo/
DIR_DESTINATION=./testdata/done/
MAX_TIME_IN_SEC=
PART_DIR=./testdata/done/

BIN_FIB_CONVERTER=./bin/convertFromFib
 

if [ $# -ge 1 ]; then
	DIR_SOURCE=$1
fi
if [ $# -ge 2 ]; then
	DIR_DESTINATION=$2
fi
if [ $# -ge 3 ]; then
	MAX_TIME_IN_SEC=$3
fi
if [ $# -ge 4 ]; then
	PART_DIR=$4
fi


Files=$(ls ${DIR_SOURCE}/*.xml)

RETURNVALUE=$?
if [ ! ${RETURNVALUE} ]; then
	echo "could not find files"
	exit 1
fi
File=$(getFirstPart ${Files})

#echo "Fib images to convert to bmp: " ${Files}

while [ true ]
do
	BmpFilname=$(echo "${File}" | sed -e "s/.xml/.bmp/g")
	date
	echo "Konverting file: ${File} to ${BmpFilname}"

	${BIN_FIB_CONVERTER} ${File} ${BmpFilname} ${MAX_TIME_IN_SEC}
	RETURNVALUE=$?
	if [ ${RETURNVALUE} -eq 0 ]; then
		mv -f ${File} ${DIR_DESTINATION}
		mv -f ${BmpFilname} ${DIR_DESTINATION}
	else
		echo "maximal evaluation time ( ${MAX_TIME_IN_SEC} s) reached"
		mv -f ${File} ${PART_DIR}
		BmpFilnamePart=$(echo "${File}" | sed -e "s/.xml/_part.bmp/g")
		mv -f ${BmpFilname} ${BmpFilnamePart}
		mv -f ${BmpFilnamePart} ${PART_DIR}
	fi
	#evalue next file to convert
	Files=$(ls ${DIR_SOURCE}/*.xml)
	RETURNVALUE=$?
	if [ ! ${RETURNVALUE} ]; then
		#no next file to convert
		break
	fi
	File=$(getFirstPart ${Files})
done

date
