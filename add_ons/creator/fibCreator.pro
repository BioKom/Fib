#
# @author Betti Oesterholz
# @date 09.06.2013
# @mail webmaster@BioKom.info
#
# System: qmake
#
# This is the makefile for the Fib creator C++ system.
#
# Copyright (C) @c GPL3 2013 Betti Oesterholz
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#
# This is the makefile for the Fib creator C++ system.
# It implements an application, with a grapical user interface, for creating
# and changing Fib objects.
#
#
# call:
# 	qmake fibCreator.pro
# 		to create the Fib creator make file
# Then call:
#TODO
# 	qmake fibCreator.pro
# 		to create the Fib creator application
# 	make clean
# 		to clean all files this make has created
# 	make test
# 		to create the fib-multimedialange test library and testfiles (testcase/)
# 	make win
# 		to create the fib-multimedialange windows library
# 	make win_test
# 		to create the fib-multimedialange windows test library and testfiles (testcase/)
#
##########################################################################
#
# History:
# 09.06.2013   Oesterholz   created


##########################################################################
#
# cofig variable
#
##########################################################################

# comment in for debug mode
CONFIG += qt warn_on debug


##########################################################################
#
# folder variables
#
##########################################################################


# folders of the Fib creator code
DIR_SRC=src/
DIR_INCL=incl/

# Folder of the testcases
DIR_TEST=test/

# Folder of the translation/localization files
DIR_TRANSLATIONS=translations/


# Folder of the objects
DIR_OBJ=obj/

# Folder of the test objects
DIR_OBJ_TEST=obj_test/

# Folder of the executebels
DIR_BIN=bin/

# Folder of the test executebels
DIR_TESTCASE=testcase/


# Path to the project base directory
DIR_PROJECT_BASE=../../

# Path to the Fib language module
DIR_FIB_LANGUAGE=$${DIR_PROJECT_BASE}fib/
DIR_FIB_LANGUAGE_INCL=$${DIR_FIB_LANGUAGE}incl/
DIR_FIB_LANGUAGE_LIB=$${DIR_FIB_LANGUAGE}lib/

# Path to the tinyxml module
DIR_TINY_XML=$${DIR_PROJECT_BASE}tinyxml/


##########################################################################
#
# qmake variables
#
##########################################################################


TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += $${DIR_INCL} model/$${DIR_INCL} view/$${DIR_INCL} control/$${DIR_INCL}\
	$${DIR_PROJECT_BASE} $${DIR_FIB_LANGUAGE_INCL} $${DIR_TINY_XML}

TARGET = $${DIR_BIN}fibCreator
OBJECTS_DIR = $${DIR_OBJ}obj
MOC_DIR = $${DIR_OBJ}moc
RCC_DIR = $${DIR_OBJ}rcc
UI_DIR = $${DIR_OBJ}ui
LIBS_ADDITIONAL = -L$${DIR_FIB_LANGUAGE_LIB} -lfib

debug {
	TARGET = $${DIR_TESTCASE}test_fibCreator
	OBJECTS_DIR = $${DIR_OBJ_TEST}obj
	MOC_DIR = $${DIR_OBJ_TEST}moc
	RCC_DIR = $${DIR_OBJ_TEST}rcc
	UI_DIR = $${DIR_OBJ_TEST}ui
	LIBS_ADDITIONAL = -L$${DIR_FIB_LANGUAGE_LIB} -lfib_test
}

LIBS += $${LIBS_ADDITIONAL}

# Input
SOURCES += $${DIR_SRC}*.cpp model/$${DIR_SRC}*.cpp view/$${DIR_SRC}*.cpp\
	control/$${DIR_SRC}*.cpp
HEADERS +=  model/$${DIR_INCL}*.h view/$${DIR_INCL}*.h\
	control/$${DIR_INCL}*.h


##########################################################################
#
# qmake QT Linguist variables
#
##########################################################################


TRANSLATIONS = $${DIR_TRANSLATIONS}fibCreator_de.ts \
	$${DIR_TRANSLATIONS}fibCreator_fr.ts








