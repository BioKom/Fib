#
# @author Betti Oesterholz
# @date 13.05.2009
# @mail webmaster@BioKom.info
#
# System: make
#
# This make file will compile the whool project with all subprojects.
# Copyright (C) @c GPL3 2011 Betti Oesterholz
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
# call:
# 	make
# 		to create the fib project
# 	make clean
# 		to clean all files this make has created
# 	make test
# 		to create the fib project test library and testfiles (testcase/)
# 	make win
# 		to create the fib project for windows
# 	make win_test
# 		to create the fib project test library and testfiles (testcase/) for windows
# 	make help
# 		to print help information
#
##########################################################################
#
# History:
# 16.03.2011   Oesterholz   windows included
# 20.01.2014   Oesterholz   the Fib creator application included

##########################################################################
#
# paths to the subprojects
#
##########################################################################

SUB_PROJECT_PATHS:=fib/ enviroment/ enviroment.fib/ add_ons/converter/ \
   fib.algorithms/

# Folder of the Fib creator application
DIR_CREATOR:=add_ons/creator/

##########################################################################
#
# compile rules
#
##########################################################################

.PHONY: all test clean help $(SUB_PROJECT_PATHS) creator creator_test

all: $(SUB_PROJECT_PATHS) creator

test: $(SUB_PROJECT_PATHS) creator_test

win: $(SUB_PROJECT_PATHS)

win_test: $(SUB_PROJECT_PATHS)

clean: $(SUB_PROJECT_PATHS)
	rm -fr $(FOLDER_EXTRACT)
	rm -fr $(DIR_CREATOR)/obj_test
	rm -fr $(DIR_CREATOR)/obj
	cd $(DIR_CREATOR); make clean


##########################################################################
#
# rules to compile the subprojects
#
##########################################################################


#$(call generat_sub_project, Subprojectpath)
#
# @param Subprojectpath the path to the subproject
#
define generat_sub_project
$(1):
	make --directory=$(1) $(MAKECMDGOALS)
endef

$(foreach SUB_PROJECT, $(SUB_PROJECT_PATHS), $(eval $(call generat_sub_project,$(SUB_PROJECT)) ) )


creator: fib/
	cd $(DIR_CREATOR);\
	qmake fibCreator.pro;\
	make

creator_test: fib/
	cd $(DIR_CREATOR);\
	makeTest.sh



##########################################################################
#
# rule to print the help information
#
##########################################################################

help:
	@echo ""
	@echo "This make file will compile the whool Fib-project with all subprojects."
	@echo "Copyright (C) @c GPL3 2011 Betti Oesterholz"
	@echo ""
	@echo "type:"
	@echo "   make"
	@echo "      to create the fib project"
	@echo "   make clean"
	@echo "      to clean all files this make has created"
	@echo "   make test"
	@echo "      to create the fib project test library and testfiles (testcase/)"
	@echo "   make win"
	@echo "      to create the fib project for windows"
	@echo "   make win_test"
	@echo "      to create the fib project test library and testfiles (testcase/) for windows"
	@echo "   make help"
	@echo "      to print this help information"
	@echo ""













