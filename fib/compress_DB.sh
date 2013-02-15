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
# This Script converts all database Fib XML objects into compressed Fib
# objects
#
# History:
#  01.03.2012  Oesterholz  created
#

# the path to the original Fib database
DIR_FIB_DATABASE_ORIGINAL=./fibDatabase/
# the path to the to create compressed Fib database
DIR_FIB_DATABASE_COMPRESSED=./fibDatabaseCompr/

# executebel to convert from one Fib representation into an other
CONVERTER=../add_ons/converter/bin/convertFibToFib


if ! [ -d ${DIR_FIB_DATABASE_COMPRESSED} ]; then
	
	mkdir -p ${DIR_FIB_DATABASE_COMPRESSED}
fi


for FILE in $(ls ${DIR_FIB_DATABASE_ORIGINAL}*.xml ${DIR_FIB_DATABASE_ORIGINAL}*.fib 2>/dev/null)
do
	NEW_FILENAME=$(echo "${FILE}" | sed -e "s#.xml#.fib#g" -e "s#.XML#.fib#g"\
		-e "s#${DIR_FIB_DATABASE_ORIGINAL}#${DIR_FIB_DATABASE_COMPRESSED}#g")
	
	echo "Konverting file: ${FILE} to ${NEW_FILENAME}"
	${CONVERTER} "${FILE}" "${NEW_FILENAME}"
done

