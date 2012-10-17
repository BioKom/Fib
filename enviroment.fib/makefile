#
# @author Betti Oesterholz
# @date 28.02.2010
# @mail webmaster@BioKom.info
#
# System: make
#
# This makefile for the fib -genetic algorithm (C++).
# Copyright (C) @c GPL3 2010 Betti Oesterholz
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
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
# The environmentsystem implements an fib-genetic algorithm.
#
# call:
# 	make
# 		to create the fib-environmentsystem
# 	make clean
# 		to clean all files this make has created
# 	make test
# 		to create the fib-environmentsystem testfiles (testcase/)
# 	make win
# 		to create the fib-environmentsystem windows
# 	make win_test
# 		to create the fib-environmentsystem windows testfiles (testcase/)
#
##########################################################################
#
# History:
# 28.02.2010   Oesterholz   created
# 15.06.2010   Oesterholz   fib.algorithms added
# 16.06.2010   Oesterholz   runEnviroment added
# 25.02.2011   Oesterholz   handling of more operator directories added
# 07.05.2011   Oesterholz   rules for windows compability added
# 21.11.2011   Oesterholz   library "-lm" included
# 11.09.2012   Oesterholz   standard libaries to the end
# 14.07.2011   Oesterholz   glpk included for FEATURE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING


##########################################################################
#
# folder variables
#
##########################################################################


# relativ path to the fib -multimediasystem base directory
BASE_DIR:=../


# folders of the enviroment source code
DIR_SRC:=src/
DIR_INCL:=incl/

# folder of the testcases
DIR_TEST:=test/

# folder of the objects
DIR_OBJ:=obj/

# folder of the test objects
DIR_OBJ_TEST:=obj_test/

# folder of the library
DIR_LIB:=lib/

# folder of the executebels
DIR_BIN:=bin/

# folder of the test executebels
DIR_TESTCASE:=testcase/

# folder of the operatores
DIR_OPERATORS:=operators/

#this file defines the DIRS_OPERATORS variable with the operator base directories
ifneq "$(MAKECMDGOALS)" "clean"
-include $(DIR_OPERATORS)/operators.mk
endif
DIRS_OPERATORS:=$(addprefix $(DIR_OPERATORS),$(DIRS_OPERATORS))


# path to the abstract genetic algorithm
DIR_ENVIROMENT:=$(BASE_DIR)enviroment/
# path to the abstract genetic algorithm library
DIR_ENVIROMENT_LIB:=$(DIR_ENVIROMENT)lib/
# path to the abstract genetic algorithm includefiles
DIR_ENVIROMENT_INCL:=$(DIR_ENVIROMENT)incl/


# path to the fib -multimedialanguage
DIR_FIB:=$(BASE_DIR)fib/
# path to the fib -multimedialanguage library
DIR_FIB_LIB:=$(DIR_FIB)lib/
# path to the fib -multimedialanguage includefiles
DIR_FIB_INCL:=$(DIR_FIB)incl/


# path to the algorithm includefiles
PATH_FIB_ALGORITHMS:=$(BASE_DIR)fib.algorithms/
PATH_FIB_ALGORITHMS_LIB:=$(PATH_FIB_ALGORITHMS)lib/

#this file defines the NAMESPACES variable with the fib.algorithms sub -namespaces
include $(PATH_FIB_ALGORITHMS)namespaces.mk

#the includes for the fib -algorithms
INCL_FIB_ALGORITHMS:=$(addprefix -I$(PATH_FIB_ALGORITHMS),$(addsuffix /incl/,$(NAMESPACES) ) )


# folder for tinyxml an (tiny) XML -parser
DIR_TINYXML:=$(BASE_DIR)tinyxml/

# folder for glpk package
DIR_GLPK:=$(BASE_DIR)other_packages/glpk/
DIR_GLPK_INCLUDE:=$(BASE_DIR)other_packages/glpk/include/
DIR_GLPK_LIBS:=$(DIR_GLPK)src/.libs/


##########################################################################
#
# compile variables
#
##########################################################################

SHELL:=/bin/sh
CC:=gcc
#debugg flags
#CFLAG:=-g -Wall
#optimize compile flags
CFLAG:=-O -O2
CFLAG_TEST:=-g -pg -Wall -DTEST
INCL:=-I$(BASE_DIR) -I$(DIR_INCL) -I$(DIR_ENVIROMENT_INCL) -I$(DIR_FIB_INCL)\
	-I$(DIR_TINYXML) -I$(DIR_OPERATORS) $(INCL_FIB_ALGORITHMS)\
	-I$(DIR_GLPK_INCLUDE)
LIBS:=-L$(DIR_FIB_LIB) -lfib\
	-L$(DIR_ENVIROMENT_LIB) -lenviroment  -L$(DIR_LIB) -lfibEnviroment\
	-L$(PATH_FIB_ALGORITHMS_LIB) -lfib_algorithms\
	-L$(DIR_GLPK)src/.libs/ -lglpk -lstdc++ -lm -lpthread
LIBS_TEST:=-L$(DIR_FIB_LIB) -lfib_test\
	-L$(DIR_ENVIROMENT_LIB) -lenviroment_test -L$(DIR_LIB) -lfibEnviroment_test\
	-L$(PATH_FIB_ALGORITHMS_LIB) -lfib_algorithms_test\
	-L$(DIR_GLPK)src/.libs/ -lglpk -lstdc++ -lm -lpthread
	
LIBS_WIN:=-L$(DIR_FIB_LIB) -lfib -static -lstdc++\
	-L$(DIR_ENVIROMENT_LIB) -lenviroment -L$(DIR_LIB) -lfibEnviroment\
	-L$(PATH_FIB_ALGORITHMS_LIB) -lfib_algorithms\
	-L$(DIR_GLPK)src/.libs/ -lglpk -static -lstdc++ -lm
LIBS_WIN_TEST:=-L$(DIR_FIB_LIB) -lfib_test -static -lstdc++\
	-L$(DIR_ENVIROMENT_LIB) -lenviroment_test -L$(DIR_LIB) -lfibEnviroment_test\
	-L$(PATH_FIB_ALGORITHMS_LIB) -lfib_algorithms_test\
	-L$(DIR_GLPK)src/.libs/ -lglpk -static -lstdc++ -lm


##########################################################################
#
# source variables
#
##########################################################################

SRC_ENVIROMENT:=$(addprefix $(DIR_SRC),$(shell ls $(DIR_SRC)) )


#$(call generat_src_files, Subfolder)
#
# @param Subfolder the (namespace) subfolder which contains the src/ folder
#    with the source files
#
define generat_src_files
SRC_OPERATORS:=$(SRC_OPERATORS) $(addprefix $(1)/$(DIR_SRC), $(shell ls $(1)/$(DIR_SRC)) )
endef

$(foreach SUBFOLDER, $(DIRS_OPERATORS), $(eval $(call generat_src_files,$(SUBFOLDER)) ) )


##########################################################################
#
# include variables
#
##########################################################################

INCL_ENVIROMENT:=$(addprefix $(DIR_INCL), $(shell ls $(DIR_INCL)) )


#$(call generat_incl_files, Subfolder)
#
# @param Subfolder the (namespace) subfolder which contains the incl/ folder
#    with the header files
#
define generat_incl_files
INCL_OPERATORS:=$(INCL_OPERATORS) $(addprefix $(1)/$(DIR_INCL), $(shell ls $(1)/$(DIR_INCL)) )
INCL:=$(INCL) -I$(1)/$(DIR_INCL)
endef

$(foreach SUBFOLDER, $(DIRS_OPERATORS), $(eval $(call generat_incl_files,$(SUBFOLDER)) ) )


##########################################################################
#
# test variables
#
##########################################################################

TEST_ENVIROMENT:=$(addprefix $(DIR_TEST), $(shell ls $(DIR_TEST)) )

TEST_PROGRAMS:=tFibObjectFitnessBasic tFibObjectFitnessBasicAlgorithm\
	tFibIndividual tIndividualInfo tEnviroment tInitFibEnviroment\
	tEndConditionCheck

TEST_TOOLS:=$(DIR_FIB)obj_test/tGeneratorForFibObjects.o

TEST_BIN:=$(addprefix $(DIR_TESTCASE), $(TEST_PROGRAMS) )


##########################################################################
#
# object variables
#
##########################################################################

OBJ_ENVIROMENT:=$(subst .cpp,.o,$(subst $(DIR_SRC),$(DIR_OBJ),$(SRC_ENVIROMENT) ))

OBJ_TEST_ENVIROMENT:=$(subst .cpp,.o,$(subst $(DIR_SRC),$(DIR_OBJ_TEST),$(SRC_ENVIROMENT) ))


#$(call generat_obj_files, Subfolder)
#
# @param Subfolder the (namespace) subfolder which contains the incl/ folder
#    with the header files
#
define generat_obj_files
OBJ_OPERATORS:=$(OBJ_OPERATORS) $(subst .cpp,.o,$(addprefix $(DIR_OBJ), $(notdir $(SRC_OPERATORS)) ))
OBJ_TEST_OPERATORS:=$(OBJ_TEST_OPERATORS) $(subst .cpp,.o,$(addprefix $(DIR_OBJ_TEST), $(notdir $(SRC_OPERATORS)) ))
endef

$(foreach SUBFOLDER, $(DIRS_OPERATORS), $(eval $(call generat_obj_files,$(SUBFOLDER)) ) )



##########################################################################
#
# executebel variables
#
##########################################################################

# the to create executebels
EXE_FILES:=runEnviroment runOperation

SRC_EXE_FILES:=$(addprefix $(DIR_SRC), $(addsuffix .cpp, $(EXE_FILES) ) )


##########################################################################
#
# compile rules
#
##########################################################################

.PHONY: all test clean enviroment fib fib_algorithms win win_test\
	dependencies_dep

MAKEFILE_FLAG:=


all: $(DIR_OBJ) $(DIR_LIB) $(DIR_BIN) dependencies.dep fib enviroment\
	fib_algorithms $(DIR_LIB)libfibEnviroment.a  $(DIR_GLPK_LIBS)libglpk.a\
	$(addprefix $(DIR_BIN), $(EXE_FILES) )

test: $(DIR_OBJ_TEST) $(DIR_TESTCASE) $(DIR_LIB) $(DIR_BIN) dependencies.dep\
	fib enviroment fib_algorithms\
	$(DIR_LIB)libfibEnviroment_test.a $(TEST_BIN)\
	$(DIR_GLPK_LIBS)libglpk.a\
	$(addprefix $(DIR_BIN)test_, $(EXE_FILES) )

test: CFLAG:=$(CFLAG_TEST)
test: MAKEFILE_FLAG:=test


##########################################################################
#
# rules for windows compatibility
#
##########################################################################

win: CFLAG:=$(CFLAG) -DWINDOWS
win: all
win: MAKEFILE_FLAG:=win
win: LIBS:=$(LIBS_WIN)
win_test: $(DIR_OBJ_TEST) $(DIR_TESTCASE) $(DIR_LIB) $(DIR_BIN) dependencies.dep\
	fib enviroment fib_algorithms\
	$(DIR_GLPK_LIBS)libglpk.a\
	$(DIR_LIB)libfibEnviroment_test.a $(TEST_BIN)\
	$(addprefix $(DIR_BIN)test_, $(EXE_FILES) )
win_test: CFLAG:=$(CFLAG_TEST) -DWINDOWS
win_test: MAKEFILE_FLAG:=win_test
win_test: LIBS_TEST:=$(LIBS_WIN_TEST)


##########################################################################
#
# rules for other fib-system parts
#
##########################################################################


enviroment:
	make --directory=$(DIR_ENVIROMENT) $(MAKEFILE_FLAG)

fib:
	make --directory=$(DIR_FIB) $(MAKEFILE_FLAG)

fib_algorithms:
	make --directory=$(PATH_FIB_ALGORITHMS) $(MAKEFILE_FLAG)



##########################################################################
#
# fib -enviroment libaries to produce
#
##########################################################################

$(DIR_LIB)libfibEnviroment.a: $(OBJ_ENVIROMENT) $(OBJ_OPERATORS)
	$(AR) $(ARFLAGS) $@ $?


##########################################################################
#
# fib -enviroment test libaries to produce
#
##########################################################################

$(DIR_LIB)libfibEnviroment_test.a: $(OBJ_TEST_ENVIROMENT) $(OBJ_TEST_OPERATORS)
	$(AR) $(ARFLAGS) $@ $?


##########################################################################
#
# rules for the fib libary
#
##########################################################################

$(DIR_FIB_LIB)libfib.a: fib

$(DIR_FIB_LIB)libfib_test.a: fib


$(DIR_FIB_LIB)libfib_algorithms.a: fib_algorithms

$(DIR_FIB_LIB)libfib_algorithms_test.a: fib_algorithms


##########################################################################
#
# rules to create the glpk object files
#
##########################################################################

$(DIR_GLPK_LIBS)libglpk.a:
	if [ "$(WINDOWS)" != "true" ]; then\
	   if ! [ -e  $(DIR_GLPK)glpk_config.flg ]; then\
	      cd $(DIR_GLPK);\
	      ./configure --disable-shared;\
	      echo > glpk_config.flg;\
	      cd -;\
	   fi;\
	   make CFLAGS=-O2 --directory=$(DIR_GLPK);\
	else\
	   make CFLAGS=-O2 --directory=$(DIR_GLPK) -f win32/Makefile.gcc;\
	fi;

	
##########################################################################
#
# rules for the operators
#
##########################################################################


$(DIR_OPERATORS)includeOperators: $(DIR_OPERATORS)includeOperators.cpp $(DIR_FIB_LIB)libfib.a
	$(CC) $(CFLAG) $(LDFLAGS) $(INCL) -o $(DIR_OPERATORS)includeOperators\
	 $(DIR_OPERATORS)includeOperators.cpp -lstdc++ -L$(DIR_FIB_LIB) -lfib

$(DIR_OPERATORS)operators.h: $(DIR_OPERATORS)includeOperators $(INCL_OPERATORS)\
		$(DIR_OPERATORS)operator_dirs.txt
	cd $(DIR_OPERATORS); ./includeOperators

$(DIR_OPERATORS)/operators.mk: $(DIR_OPERATORS)includeOperators $(INCL_OPERATORS)\
		$(DIR_OPERATORS)operator_dirs.txt
	cd $(DIR_OPERATORS); ./includeOperators
	make dependencies_dep


##########################################################################
#
# rules to create the testprograms
#
##########################################################################


#$(call generat_test_bin, Testprogramname)
#
# @param Testprogramname (file-)name of the testprogram to generate
#
define generat_test_bin
$(DIR_TESTCASE)$(1): $(DIR_OBJ_TEST)$(1).o enviroment\
		$(DIR_LIB)libfibEnviroment_test.a  $(TEST_TOOLS)
	$(CC) $$(CFLAG_TEST) $$(LDFLAGS) -o $$@ $(DIR_OBJ_TEST)$(1).o\
	 $(DIR_LIB)libfibEnviroment_test.a  $(TEST_TOOLS) $$(LIBS_TEST)
endef

$(foreach TESTPROGRAM, $(TEST_PROGRAMS), $(eval $(call generat_test_bin,$(TESTPROGRAM)) ) )


$(TEST_TOOLS):
	make --directory=$(DIR_FIB) test



#$(call generat_bins, Programname)
#
# @param Programname (file-)name of the program to generate
#
define generat_bins
$(DIR_BIN)$(1):$(DIR_OBJ)$(1).o enviroment $(DIR_LIB)libfibEnviroment.a
	$(CC) $$(CFLAG) $(LDFLAGS) -o $$@ $(DIR_OBJ)$(1).o -L$(DIR_LIB) -lfibEnviroment $$(LIBS)
endef

$(foreach PROGRAM, $(EXE_FILES), $(eval $(call generat_bins,$(PROGRAM)) ) )

#$(call generat_bins, Programname)
#
# @param Programname (file-)name of the program to generate
#
define generat_test_bins
$(DIR_BIN)test_$(1):$(DIR_OBJ_TEST)$(1).o enviroment $(DIR_LIB)libfibEnviroment_test.a
	$(CC) $$(CFLAG_TEST) $(LDFLAGS) -o $$@ $(DIR_OBJ_TEST)$(1).o -L$(DIR_LIB) -lfibEnviroment_test $$(LIBS_TEST)
endef

$(foreach TESTPROGRAM, $(EXE_FILES), $(eval $(call generat_test_bins,$(TESTPROGRAM)) ) )


##########################################################################
#
# creat folders
#
##########################################################################

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)

$(DIR_OBJ_TEST):
	mkdir -p $(DIR_OBJ_TEST)

$(DIR_BIN):
	mkdir -p $(DIR_BIN)

$(DIR_TESTCASE):
	mkdir -p $(DIR_TESTCASE)

$(DIR_LIB):
	mkdir -p $(DIR_LIB)


##########################################################################
#
# creat dependencies
#
##########################################################################


ifeq "$(MAKECMDGOALS)" "dependencies_dep"

dependencies_dep:dependencies.dep

dependencies.dep: $(SRC_ENVIROMENT) $(INCL_ENVIROMENT)\
		$(DIR_OPERATORS)operators.h $(DIR_OPERATORS)/operators.mk $(SRC_OPERATORS)
	rm -f dependencies.dep_tmp
	$(foreach QUELLE,  $(SRC_ENVIROMENT) $(TEST_ENVIROMENT) $(SRC_OPERATORS), \
	$(CC) -MM $(CFLAG) $(INCL) -c $(QUELLE) >> dependencies.dep_tmp; echo "	\$$(CC) \$$(CFLAG) \$$(INCL) -c \$$< -o \$$@" >> dependencies.dep_tmp; )
	cat dependencies.dep_tmp | sed -e 's,\(.*\.o\),$(DIR_OBJ)\1,g' > dependencies.dep
	cat dependencies.dep_tmp | sed -e 's,\(.*\.o\),$(DIR_OBJ_TEST)\1,g' >> dependencies.dep
	rm -f dependencies.dep_tmp

else

dependencies.dep: $(SRC_ENVIROMENT) $(INCL_ENVIROMENT)\
		$(DIR_OPERATORS)operators.h $(DIR_OPERATORS)/operators.mk $(SRC_OPERATORS)
	make dependencies_dep

endif




ifneq "$(MAKECMDGOALS)" "clean"
-include dependencies.dep
endif

##########################################################################
#
# clean rules
#
##########################################################################

clean:
	rm -rf $(DIR_OBJ) $(DIR_LIB) $(DIR_OBJ_TEST) $(DIR_BIN) $(DIR_TESTCASE)
	rm -f dependencies.dep dependencies.dep_tmp
	rm -f $(DIR_OPERATORS)operators.h $(DIR_OPERATORS)includeOperators $(DIR_OPERATORS)operators.mk




