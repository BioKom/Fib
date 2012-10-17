#
# @author Betti Oesterholz
# @date 26.02.2010
# @mail webmaster@BioKom.info
#
# System: make
#
# This makefile for the abstract genetic algorithm (C++).
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
# The environmentsystem implements an abstract genetic algorithm.
#
# call:
# 	make
# 		to create the environmentsystem library
# 	make clean
# 		to clean all files this make has created
# 	make test
# 		to create the environmentsystem test library and testfiles (testcase/)
# 	make win
# 		to create the environmentsystem windows library
# 	make win_test
# 		to create the environmentsystem windows test library and testfiles (testcase/)
#
##########################################################################
#
# History:
# 07.05.2011   Oesterholz   rules for windows compability added


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

# folder of the test executebels
DIR_TESTCASE:=testcase/

# folder for tinyxml an (tiny) XML -parser
DIR_TINYXML:=../tinyxml/
#Flags for tinyxml
TINYXML_FLAGS:=-DTIXML_USE_STL


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
CFLAG:=-O -O2 $(TINYXML_FLAGS)
CFLAG_TEST:=-g -pg -Wall -DTEST $(TINYXML_FLAGS)
INCL:=-I$(BASE_DIR) -I$(DIR_INCL) -I$(DIR_TINYXML)
LIBS:=-lstdc++
LIBS_TEST:=-lstdc++


##########################################################################
#
# source variables
#
##########################################################################

SRC_ENVIROMENT:=$(addprefix $(DIR_SRC), $(shell ls $(DIR_SRC)) )


##########################################################################
#
# include variables
#
##########################################################################

INCL_ENVIROMENT:=$(addprefix $(DIR_INCL), $(shell ls $(DIR_INCL)) )


##########################################################################
#
# include variables
#
##########################################################################

TEST_ENVIROMENT:=$(addprefix $(DIR_TEST), $(shell ls $(DIR_TEST)) )

TEST_PROGRAMS:=tIndividualIdentifier tOperationIdentifier

TEST_BIN:=$(addprefix $(DIR_TESTCASE), $(TEST_PROGRAMS) )


##########################################################################
#
# object variables
#
##########################################################################

OBJ_ENVIROMENT:=$(subst .cpp,.o,$(subst $(DIR_SRC),$(DIR_OBJ),$(SRC_ENVIROMENT) ))

OBJ_TEST_ENVIROMENT:=$(subst .cpp,.o,$(subst $(DIR_SRC),$(DIR_OBJ_TEST),$(SRC_ENVIROMENT) ))

OBJ_TINYXML:=$(addprefix $(DIR_TINYXML), tinyxml.o tinyxmlparser.o tinyxmlerror.o tinystr.o)


##########################################################################
#
# compile rules
#
##########################################################################

.PHONY: all test clean win win_test

all: $(DIR_OBJ) $(DIR_LIB) dependencies.dep $(DIR_LIB)libenviroment.a

test: $(DIR_OBJ_TEST) $(DIR_TESTCASE) $(DIR_LIB) dependencies.dep\
	$(DIR_LIB)libenviroment_test.a $(TEST_BIN)
test: CFLAG:=$(CFLAG_TEST)


$(OBJ_TINYXML): tinyxml
	 true #nothing to do for $@ , don't use standardrules

tinyxml:
	 make --directory=$(DIR_TINYXML)


##########################################################################
#
# rule for windows compatibility
#
##########################################################################

win: CFLAG:=$(CFLAG) -DWINDOWS
win: all
win_test: $(DIR_OBJ_TEST) $(DIR_TESTCASE) $(DIR_LIB) dependencies.dep\
	$(DIR_LIB)libenviroment_test.a $(TEST_BIN)
win_test: CFLAG:=$(CFLAG_TEST) -DWINDOWS



##########################################################################
#
# enviromentlibaries to produce
#
##########################################################################

$(DIR_LIB)libenviroment.a: $(OBJ_TINYXML) $(OBJ_ENVIROMENT)
	$(AR) $(ARFLAGS) $@ $?


##########################################################################
#
# enviromenttestlibaries to produce
#
##########################################################################

$(DIR_LIB)libenviroment_test.a: $(OBJ_TINYXML) $(OBJ_TEST_ENVIROMENT)
	$(AR) $(ARFLAGS) $@ $?



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
$(DIR_TESTCASE)$(1): $(DIR_OBJ_TEST)$(1).o $(TEST_TOOLS) $(DIR_LIB)libenviroment_test.a
	$(CC) $(CFLAG_TEST) $(LDFLAGS) -o $$@ $$^ $(LIBS_TEST)
endef

$(foreach TESTPROGRAM, $(TEST_PROGRAMS), $(eval $(call generat_test_bin,$(TESTPROGRAM)) ) )


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

dependencies.dep: $(SRC_ENVIROMENT) $(INCL_ENVIROMENT) $(TEST_ENVIROMENT)
	rm -f dependencies.dep_tmp
	$(foreach QUELLE,  $(SRC_ENVIROMENT) $(TEST_ENVIROMENT), \
	$(CC) -MM $(CFLAG) $(INCL) -c $(QUELLE) >> dependencies.dep_tmp; echo "	\$$(CC) \$$(CFLAG) \$$(INCL) -c \$$< -o \$$@" >> dependencies.dep_tmp; )
	cat dependencies.dep_tmp | sed -e 's,\(.*\.o\),$(DIR_OBJ)\1,g' > dependencies.dep
	cat dependencies.dep_tmp | sed -e 's,\(.*\.o\),$(DIR_OBJ_TEST)\1,g' >> dependencies.dep
	rm -f dependencies.dep_tmp




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
	make clean --directory=$(DIR_TINYXML)





