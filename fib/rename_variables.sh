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
# This Script will renumbered the variable identifiers of Fib XML format files.
# To all variables from MinNumber to MaxNumber the number Delta will be added.
#
# call:
#    rename_variables.sh File MinNumber MaxNumber Delta
#
# parameter:
#   - File: the file wher to replace the variables
#   - MinNumber: the minimum variable number to which to add Delta
#   - MaxNumber: the maximum variable number to which to add Delta
#   - Delta: the number to add to the variable numbers
#
#
# History:
#  18.09.2012  Oesterholz  created
#  22.10.2012  Oesterholz  Bugfix: "</variable>" part needed, else 8 could
#  	become (if rename_variables 1 30 11) 29
#  22.10.2012  Oesterholz  Bugfix: now the variables can be renamed in both
#  	directions 0 < Delta and Delta < 0
#

if [ $# -lt 4 ]; then
	echo "This Script will replace a variable identifiers of Fib XML format files."
	echo "To all variables from MinNumber to MaxNumber the number Delta will be added."
	echo ""
	echo "call:"
	echo "   rename_variables File MinNumber MaxNumber Delta"
	echo ""
	echo "parameter:"
	echo "   - File: the file wher to replace the variables"
	echo "   - MinNumber: the minimum variable number to which to add Delta"
	echo "   - MaxNumber: the maximum variable number to which to add Delta"
	echo "   - Delta: the number to add to the variable numbers"
	echo ""
	exit 1
fi

Files=$1
MinNumber=$2
MaxNumber=$3
Delta=$4


for File in ${Files};
do
	if [ -e ${File} ]; then
		echo "File wher the variables will be renumbered: \"${File}\""
		
		if [ 0 -lt ${Delta} ]; then
		
			for (( ActualVariable = ${MaxNumber}; ${MinNumber} <= ActualVariable; ActualVariable-- ));
			do
				#delta greater 0
				NewVariableValue=$((${ActualVariable} + ${Delta}))
				echo "Setting ${ActualVariable} to ${NewVariableValue}"
				
				sed -e "s~<variable>${ActualVariable}</variable>~<variable>${NewVariableValue}</variable>~g" ${File} > ${File}.tmp1
				sed -e "s~define_variable=\"${ActualVariable}\"~define_variable=\"${NewVariableValue}\"~g" ${File}.tmp1 > ${File}.tmp2
				
				rm -f ${File}.tmp1
				mv -f ${File}.tmp2 ${File}
			done
		else
			#delta lower 0
			for (( ActualVariable = ${MinNumber}; ActualVariable <= ${MaxNumber}; ActualVariable++ ));
			do
				#delta greater 0
				NewVariableValue=$((${ActualVariable} + ${Delta}))
				echo "Setting ${ActualVariable} to ${NewVariableValue}"
				
				sed -e "s~<variable>${ActualVariable}</variable>~<variable>${NewVariableValue}</variable>~g" ${File} > ${File}.tmp1
				sed -e "s~define_variable=\"${ActualVariable}\"~define_variable=\"${NewVariableValue}\"~g" ${File}.tmp1 > ${File}.tmp2
				
				rm -f ${File}.tmp1
				mv -f ${File}.tmp2 ${File}
			done
		fi
	else
		echo "File \"${File}\" not found"
	fi
done



