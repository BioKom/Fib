#!/bin/bash
#
# Author: Betti Oesterholz
#
# Copyright (C) @c GPL3 2012 Betti Oesterholz
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License (GPL) as
# published by the Free Software Foundation, either version 3 of the
# License, or any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
#######################################################################
#
# This Script will switch two variable identifiers of Fib XML format files.
# All occurenc of the first variable name will be replaced with the
# second variable name and vice versa.
#
# call:
#    switch_variables.sh File Var1Number Var2Number
#
# parameter:
#   - File: the file wher to replace the variables
#   - Var1Number: the first variable number
#   - Var2Number: the second variable number
#
#
# History:
#  30.01.2013  Oesterholz  created
#

if [ $# -lt 3 ]; then
	echo " This Script will switch two variable identifiers of Fib XML format files."
	echo " All occurenc of the first variable name will be replaced with the"
	echo " second variable name and vice versa."
	echo ""
	echo " call:"
	echo "    switch_variables.sh File Var1Number: Var2Number:"
	echo ""
	echo " parameter:"
	echo "   - File: the file wher to replace the variables"
	echo "   - Var1Number: the first variable number"
	echo "   - Var2Number: the second variable number"
	echo ""
	exit 1
fi

Files=$1
Var1Number=$2
Var2Number=$3


for File in ${Files};
do
	if [ -e ${File} ]; then
		echo "File wher the variables will be switched \"${File}\""
		
		TmpVariableValue="tmp_${Var1Number}"
		echo "Setting ${Var1Number} to ${TmpVariableValue}"
		sed -e "s~<variable>${Var1Number}</variable>~<variable>${TmpVariableValue}</variable>~g" ${File} > ${File}.tmp1
		sed -e "s~define_variable=\"${Var1Number}\"~define_variable=\"${TmpVariableValue}\"~g" ${File}.tmp1 > ${File}.tmp2
		
		echo "Setting ${Var2Number} to ${Var1Number}"
		sed -e "s~<variable>${Var2Number}</variable>~<variable>${Var1Number}</variable>~g" ${File}.tmp2 > ${File}.tmp3
		sed -e "s~define_variable=\"${Var2Number}\"~define_variable=\"${Var1Number}\"~g" ${File}.tmp3 > ${File}.tmp4
		
		echo "Setting ${TmpVariableValue} to ${Var2Number}"
		sed -e "s~<variable>${TmpVariableValue}</variable>~<variable>${Var2Number}</variable>~g" ${File}.tmp4 > ${File}.tmp5
		sed -e "s~define_variable=\"${TmpVariableValue}\"~define_variable=\"${Var2Number}\"~g" ${File}.tmp5 > ${File}.tmp6
		
		
		rm -f ${File}.tmp1
		rm -f ${File}.tmp2
		rm -f ${File}.tmp3
		rm -f ${File}.tmp4
		rm -f ${File}.tmp5
		mv -f ${File}.tmp6 ${File}
		
		
	else
		echo "File \"${File}\" not found"
	fi
done



