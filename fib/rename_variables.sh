#!/bin/bash
#
# Copyright (C) 2012 Betti Oesterholz
#
# Author: Betti Oesterholz 
#
#######################################################################
#
# This Script will renumbered the variable identifiers of Fib XML format files.
# To all variables from MinNumber to MaxNumber the number Delta will be added.
#
# call:
#    rename_variables File MinNumber MaxNumber Delta
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
		
		for (( ActualVariable = ${MaxNumber}; ${MinNumber} <= ActualVariable; ActualVariable-- ));
		do
			NewVariableValue=$((${ActualVariable} + ${Delta}))
			echo "Setting ${ActualVariable} to ${NewVariableValue}"
			
			sed -e "s~<variable>${ActualVariable}</variable>~<variable>${NewVariableValue}</variable>~g" ${File} > ${File}.tmp1
			sed -e "s~define_variable=\"${ActualVariable}\"~define_variable=\"${NewVariableValue}\"~g" ${File}.tmp1 > ${File}.tmp2
			
			rm -f ${File}.tmp1
			mv -f ${File}.tmp2 ${File}
		done
	else
		echo "File \"${File}\" not found"
	fi
done



