#!/bin/bash
#
# Copyright (C) 2011 Betti Oesterholz
#
# Author: Betti Oesterholz
#
#######################################################################
#
# This script creats an extract of the fib-system.
# The extract will contain all files needed for the fib-system.
#
# History:
#  07.05.2011  Oesterholz  created
#  14.07.2011  Oesterholz  zlib added
#  08.08.2011  Oesterholz  copy_folder_recursive() implemented
#  23.02.2012  Oesterholz  copy FreeImage windows files
#  29.02.2012  Oesterholz  copy database files
#  18.03.2012  Oesterholz  file liesmich.txt added
#  26.09.2012  Oesterholz  glpk added
#  26.09.2012  Oesterholz  FreeImage version changed to 3.15.3
#  18.10.2012  Oesterholz  operators directory splineMax4ParamBorder added;
#  	fib.algorithms/nConvertToFib/ added
#  02.12.2012  Oesterholz  HowTo_Fib_objekte_schreiben.txt added
#



# the folder for the extracted Fib-system
export FOLDER_EXTRACT="extract/fib/"

# variables for the subfolders of an code base directory
export DIR_SORCE="src/"
export DIR_INCLUDE="incl/"
export DIR_TEST="test/"
export DIR_TESTRUNS="testruns/"
export DIR_OBJECTS="testObjects/"


# paths to the subprojects
export SUB_PROJECT_PATHS="fib/ enviroment/ enviroment.fib/ add_ons/converter/
   fib.algorithms/"

# the folder for the Fib database
export DIR_FIB_DATABASE="fib/fibDatabase/"

# paths to the algorithm namespace folders
export ALGORITHM_FOLDERS="fib.algorithms/
	fib.algorithms/nD1/ fib.algorithms/nD2/ fib.algorithms/nDn/
	fib.algorithms/nLinearEquation/ fib.algorithms/nLinearInequation/
	fib.algorithms/nReduceFibObject/ fib.algorithms/nTidyFibObjects/
	fib.algorithms/nCorrectFibObject/
	fib.algorithms/nEvalueFibObject/nNeededUnderobjects/
	fib.algorithms/nAnalyse/nFibObject/ fib.algorithms/nCluster/
	fib.algorithms/nConvertToFib/"

# paths to the folders for the directories
export OPERATORS_FOLDERS="enviroment.fib/operators/
	enviroment.fib/operators/findLine/even/
	enviroment.fib/operators/findLine/similar/
	enviroment.fib/operators/findArea/even/goodPolynomBorder/
	enviroment.fib/operators/findArea/similar/goodPolynomBorder/
	enviroment.fib/operators/findArea/even/splineMax4ParamBorderItrFast/
	enviroment.fib/operators/findArea/similar/splineMax4ParamBorderItrFast/
	enviroment.fib/operators/findArea/even/splineMax4ParamBorder/
	enviroment.fib/operators/findArea/similar/splineMax4ParamBorder/"

# extra folders which should be created in te extract (needed for EXTRA_FILES)
export EXTRA_FOLDERS_TO_CREATE="testruns/
	gpl/ other_packages/
	fib/test_output"

# files wich should be copied seperated
export EXTRA_FILES="readme.txt liesmich.txt makefile version.h
	HowTo_Fib_objekte_schreiben.txt
	add_ons/converter/readme.txt
	testruns/basicTestrun.sh testruns/basicMemtest.sh
	fib.algorithms/namespaces.mk
	enviroment.fib/operators/includeOperators.cpp
	enviroment.fib/operators/operator_dirs.txt
	enviroment.fib/operators/operators.txt
	gpl/gpl-3_0.tex gpl/gpl.txt gpl/lgpl.txt
	fib/databaseDes.txt"


# file typs for the latex documentation
export DOCU_TYPS="tex bib"
# folders for the latex documentation
export DOCU_FOLDERS="docu/docu_V1_ger/ docu/docu_V1_ger/algorithm/
	docu/docu_V1_en/ docu/handzettel/ docu/handzettel_en/"
# file typs of the latex documentation pictures
export DOCU_PICTURE_TYPS="eps dia png xcf jpg bmp"
# folders for the latex documentation pictures
export DOCU_PICTURE_FOLDERS="docu/docu_V1_ger/beispiele/
	docu/docu_V1_ger/klassendiagramme/
	docu/docu_V1_ger/material_algorithmen/
	docu/docu_V1_ger/material_enviroment/
	docu/docu_V1_ger/material_enviroment_implementation/
	docu/docu_V1_ger/material_grundlagen/
	docu/docu_V1_ger/material_sprachbeschreibung/
	docu/docu_V1_ger/material_sprachimplementation/
	docu/docu_V1_ger/sonstiges/
	docu/docu_V1_en/stock_language_description/
	docu/docu_V1_en/stock_environment/
	docu/docu_V1_en/sonstiges/
	docu/handzettel/bilder/
	docu/handzettel_en/pictures/"


# path of all directories with to copy code in them
export CODE_PATHS_TO_COPY="${SUB_PROJECT_PATHS} ${ALGORITHM_FOLDERS}
	${OPERATORS_FOLDERS}"






##########################################################################
#
# This function copies the given filetype from the FOLDER_SRC to the
# FOLDER_DEST, if files of the type exists.
# If files should be copied but the FOLDER_DEST dos not exists it will be
# created.
#
# call:
# 	copy_folder_with_filetype FOLDER_SRC FILE_TYPE FOLDER_DEST
#
# Parameters:
# 	FOLDER_SRC the folder wher to look for the file type
# 	FILE_TYPE the file type to copy
# 	FOLDER_DEST the folder to copy the file type to
#
##########################################################################
copy_folder_with_filetype(){
	
	for FILE in ${1}*${2}; do
		if [ -e ${FILE} ]; then
			echo "copy *${2} files from ${1} to ${3}"
			if [ ! -d ${3} ]; then
				mkdir -p ${3};
			fi
			cp -f ${1}*${2} ${3};
			break;
		fi;
	done
}


##########################################################################
#
# This function copies the given FOLDER_SRC to the FOLDER_DEST.
# If files should be copied but the FOLDER_DEST dos not exists it will be
# created.
# It won't copy hidden files or directories
#
# call:
# 	copy_folder_recursive FOLDER_SRC FOLDER_DEST
#
# Parameters:
# 	FOLDER_SRC the folder (absolute path) wher copy the files from
# 	FOLDER_DEST the folder (absolute path) to copy the files to
#
##########################################################################
copy_folder_recursive(){
	
	FOLDER_SRC_CP_RECURSIVE=${1}
	FOLDER_DEST_CP_RECURSIVE=${2}
	if [ ! -d ${FOLDER_SRC_CP_RECURSIVE} ]; then
		return
	fi;
	if [ ! -d ${FOLDER_DEST_CP_RECURSIVE} ]; then
		mkdir -p ${FOLDER_DEST_CP_RECURSIVE};
	fi;
	echo "copy recursive from ${FOLDER_SRC_CP_RECURSIVE} to ${FOLDER_DEST_CP_RECURSIVE}"
	
	cd ${FOLDER_SRC_CP_RECURSIVE}
	FOLDER_ENTRIES=$(ls)
	# echo "entries in folder ${FOLDER_SRC_CP_RECURSIVE}: ${FOLDER_ENTRIES}"
	
	for ENTRY in ${FOLDER_ENTRIES}; do
		
		# echo "checking entry \"${ENTRY}\""
		
		if [ -f ${ENTRY} ]; then
			# copy file
			# echo "copy file from ${FOLDER_SRC_CP_RECURSIVE}/${ENTRY} to ${FOLDER_DEST_CP_RECURSIVE}/"
			cp -f ${ENTRY} ${FOLDER_DEST_CP_RECURSIVE}/;
		else
			if [ -d ${ENTRY} ]; then
				if [[ ${ENTRY} != "" && ${ENTRY} != "\." && ${ENTRY} != "\.\." ]]; then
					
					# copy directory
					copy_folder_recursive ${FOLDER_SRC_CP_RECURSIVE}/${ENTRY} ${FOLDER_DEST_CP_RECURSIVE}/${ENTRY};
					
					# echo "changing back to folder: ${FOLDER_SRC_CP_RECURSIVE}/.."
					cd ${FOLDER_DEST_CP_RECURSIVE}/..
					FOLDER_DEST_CP_RECURSIVE=$(pwd)
					cd ${FOLDER_SRC_CP_RECURSIVE}/..
					FOLDER_SRC_CP_RECURSIVE=$(pwd)
					# echo "now copy recursive from ${FOLDER_SRC_CP_RECURSIVE} to ${FOLDER_DEST_CP_RECURSIVE}"
				fi;
			fi;
		fi;
	done
}


##########################################################################
#
# call: extract_code_folder FOLDER
#
# This function extracts an code directory (FOLDER).
#
# @param FOLDER the folder, in from which the code should be extracted
#
##########################################################################
extract_code_folder(){

	echo "extracting code of folder ${1}"
	#echo "mkdir -p ${FOLDER_EXTRACT}${1}"
	mkdir -p ${FOLDER_EXTRACT}${1}
	if [ -e ${1}makefile ]; then
		cp -f ${1}makefile ${FOLDER_EXTRACT}${1}makefile;
	fi;
	if [ -e ${1}version.h ]; then
		cp -f ${1}version.h ${FOLDER_EXTRACT}${1}version.h;
	fi;
	if [ -e ${1}readme.txt ]; then
		cp -f ${1}readme.txt ${FOLDER_EXTRACT}${1}readme.txt;
	fi;
	copy_folder_with_filetype "${1}${DIR_SORCE}" ".cpp" "${FOLDER_EXTRACT}${1}${DIR_SORCE}"
	
	copy_folder_with_filetype "${1}${DIR_INCLUDE}" ".h" "${FOLDER_EXTRACT}${1}${DIR_INCLUDE}"
	copy_folder_with_filetype "${1}${DIR_INCLUDE}" ".inc" "${FOLDER_EXTRACT}${1}${DIR_INCLUDE}"
	
	copy_folder_with_filetype "${1}${DIR_TEST}" ".cpp" "${FOLDER_EXTRACT}${1}${DIR_TEST}"
	copy_folder_with_filetype "${1}${DIR_TEST}" ".inc" "${FOLDER_EXTRACT}${1}${DIR_TEST}"
	
	copy_folder_with_filetype "${1}${DIR_TESTRUNS}" ".sh" "${FOLDER_EXTRACT}${1}${DIR_TESTRUNS}"
	copy_folder_with_filetype "${1}${DIR_TESTRUNS}" ".bat" "${FOLDER_EXTRACT}${1}${DIR_TESTRUNS}"
	
	# don't copy hidden files and folders
	ORIGINAL_FOLDER_CP_REC=$(pwd)
	copy_folder_recursive ${ORIGINAL_FOLDER_CP_REC}/${1}${DIR_OBJECTS}/ ${ORIGINAL_FOLDER_CP_REC}/${FOLDER_EXTRACT}${1}${DIR_OBJECTS}/
	cd ${ORIGINAL_FOLDER_CP_REC}

}


##########################################################################
# This function extracts all the sorce code in the  folders
# ${CODE_PATHS_TO_COPY}.
##########################################################################
extract_code(){
	echo "extracting code"
	echo "==============="
	for SUBFOLDER in ${CODE_PATHS_TO_COPY};
	do
		extract_code_folder ${SUBFOLDER}
	done
}


##########################################################################
# This function will extract the docu pictures.
##########################################################################
extract_docu_picturs(){
	echo "   extracting documentation pictures of folders: ${DOCU_PICTURE_FOLDERS}"
	for FOLDER in ${DOCU_PICTURE_FOLDERS};
	do
		for PICTURE_TYPE in ${DOCU_PICTURE_TYPS};
		do
			copy_folder_with_filetype "${FOLDER}" ".${PICTURE_TYPE}" "${FOLDER_EXTRACT}${FOLDER}"
		done
	done
}


##########################################################################
# This function will extract the documentation.
##########################################################################
extract_docu(){
	echo "extracting documentation of folders: ${DOCU_FOLDERS}"
	for FOLDER in ${DOCU_FOLDERS};
	do
		for DOCU_TYPE in ${DOCU_TYPS};
		do
			echo "checking docu of folder ${FOLDER} and type .${DOCU_TYPE}"
			copy_folder_with_filetype "${FOLDER}" ".${DOCU_TYPE}" "${FOLDER_EXTRACT}${FOLDER}"
		done
	done
	extract_docu_picturs
}


##########################################################################
# This function will create the extra folders.
# @see EXTRA_FOLDERS_TO_CREATE
##########################################################################
create_extra_folders(){
	echo "creating extra folders: ${EXTRA_FOLDERS_TO_CREATE}"
	for FOLDER in ${EXTRA_FOLDERS_TO_CREATE};
	do
		mkdir -p ${FOLDER_EXTRACT}${FOLDER};
	done
}

##########################################################################
# This function will copy the extra files.
# Please call create_extra_folders() befor it.
# @see EXTRA_FILES
##########################################################################
copy_extra_files(){
	echo "copy extra files: ${EXTRA_FILES}"
	for FILE in ${EXTRA_FILES};
	do
		cp -f ${FILE} ${FOLDER_EXTRACT}${FILE};
	done
}





# extract the Fib-system
extract_code
create_extra_folders
copy_extra_files
extract_docu

# copy database files
copy_folder_with_filetype "${DIR_FIB_DATABASE}" ".xml" "${FOLDER_EXTRACT}${DIR_FIB_DATABASE}"
copy_folder_with_filetype "${DIR_FIB_DATABASE}" ".fib" "${FOLDER_EXTRACT}${DIR_FIB_DATABASE}"


# unziping subsystems
# extracting tinyxml
unzip -o other_packages/tinyxml_2_5_3.zip -d ${FOLDER_EXTRACT}
# extracting FreeImage
unzip -o other_packages/FreeImage3153.zip -d ${FOLDER_EXTRACT}add_ons/converter/
# copy FreeImage windows files
mkdir -p ${FOLDER_EXTRACT}add_ons/converter/FreeImageWin
cp -f other_packages/FreeImageWin/*.txt ${FOLDER_EXTRACT}add_ons/converter/FreeImageWin/
mkdir -p ${FOLDER_EXTRACT}add_ons/converter/FreeImageWin/Dist
cp -f other_packages/FreeImageWin/Dist/*.dll ${FOLDER_EXTRACT}add_ons/converter/FreeImageWin/Dist/
cp -f other_packages/FreeImageWin/Dist/*.h ${FOLDER_EXTRACT}add_ons/converter/FreeImageWin/Dist/
cp -f other_packages/FreeImageWin/Dist/*.lib ${FOLDER_EXTRACT}add_ons/converter/FreeImageWin/Dist/

# extracting zlib
cd other_packages

if [ -d "../${FOLDER_EXTRACT}/other_packages/zlib" ]; then
	#remove old directory
	rm -fr "../${FOLDER_EXTRACT}/other_packages/zlib";
fi;
tar -xzf zlib-1.2.5.tar.gz
mv -f -T "zlib-1.2.5" "../${FOLDER_EXTRACT}/other_packages/zlib"

# extracting glpk
if [ -d "../${FOLDER_EXTRACT}/other_packages/glpk" ]; then
	#remove old directory
	rm -fr "../${FOLDER_EXTRACT}/other_packages/glpk";
fi;
tar -xzf glpk-4.35.tar.gz
mv -f -T "glpk-4.35" "../${FOLDER_EXTRACT}/other_packages/glpk"

cd ..

# TODO?? other_packages

# create zip archive of extract
cd ${FOLDER_EXTRACT}/..
zip -r fib-system fib

echo
echo "extracting done"
















