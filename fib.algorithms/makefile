#
# @author Betti Oesterholz
# @date 11.06.2010
# @mail webmaster@BioKom.info
#
# System: make
#
# This is the makefile for the fib -multimedialangue C++ system.
# Copyright (C) @c GPL3 2010 Betti Oesterholz
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
# 		to create the algorithm library
# 	make clean
# 		to clean all files this make has created
# 	make test
# 		to create the algorithm test library and testfiles (testcase/)
# 	make win
# 		to create the algorithm windows library
# 	make win_test
# 		to create the algorithm windows test library and testfiles (testcase/)
#
##########################################################################
#
# History:
# 11.06.2010   Oesterholz   created
# 28.06.2010   Oesterholz   t_nD1_nPolynom added
# 25.08.2010   Oesterholz   t_nTidyFibObjects_nBalanceLists added
# 11.12.2010   Oesterholz   testfile generation in subfolders added
# 03.04.2011   Oesterholz   searching in source directories just for *.cpp files
# 07.05.2011   Oesterholz   rules for windows compability added
# 21.11.2011   Oesterholz   library "-lm" included
# 11.09.2012   Oesterholz   standard libaries to the end
# 14.07.2011   Oesterholz   glpk included for FEATURE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING


##########################################################################
#
# folder variables
#
##########################################################################

include namespaces.mk

# relativ path to the fib -multimediasystem base directory
BASE_DIR:=../

# folders of the fib -elements
DIR_SRC:=src/
DIR_INCL:=incl/

# Folder of the testcases
DIR_TEST:=test/

# Folder of the objects
DIR_OBJ:=obj/

# Folder of the test objects
DIR_OBJ_TEST:=obj_test/

# Folder of the library
DIR_LIB:=lib/

# Folder of the executebels
DIR_BIN:=bin/

# Folder of the test executebels
DIR_TESTCASE:=testcase/

# path to the fib -multimedialanguage
DIR_FIB:=$(BASE_DIR)fib/
# path to the fib -multimedialanguage library
DIR_FIB_LIB:=$(DIR_FIB)lib/
# path to the fib -multimedialanguage includefiles
DIR_FIB_INCL:=$(DIR_FIB)incl/


# folder for tinyxml an (tiny) XML -parser
DIR_TINYXML:=../tinyxml/
#Flags for tinyxml
TINYXML_FLAGS:=-DTIXML_USE_STL

# folder for glpk package
DIR_GLPK:=$(BASE_DIR)other_packages/glpk/
DIR_GLPK_INCLUDE:=$(BASE_DIR)other_packages/glpk/include/
DIR_GLPK_LIBS:=$(DIR_GLPK)src/.libs/

#TODO
# flag if windows is the operating system passible values: true, false
WINDOWS:=false


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
INCL:=-I$(BASE_DIR). -I$(DIR_TINYXML) -I$(DIR_INCL) -I$(DIR_FIB_INCL)\
	-I$(DIR_GLPK_INCLUDE)
LIBS:=-L$(DIR_FIB_LIB) -lfib -L$(DIR_GLPK_LIBS) -lglpk -lstdc++ -lm
LIBS_TEST:=-L$(DIR_FIB_LIB) -lfib_test\
	-L$(DIR_GLPK)src/.libs/ -lglpk -lstdc++ -lm
	
LIBS_WIN_TEST:=-L$(DIR_FIB_LIB) -lfib_test\
	-L$(DIR_GLPK)src/.libs/ -lglpk -lpthread -lstdc++ -lm

##########################################################################
#
# source variables
#
##########################################################################

SRC_FILES:=$(SRC_FILES) $(shell ls $(DIR_SRC)/*.cpp )

#$(call generat_src_files, Subfolder)
#
# @param Subfolder the (namespace) subfolder which contains the src/ folder
#    with the source files
#
define generat_src_files
SRC_FILES:=$(SRC_FILES) $(shell ls $(1)/$(DIR_SRC)/*.cpp )
endef

$(foreach SUBFOLDER, $(NAMESPACES), $(eval $(call generat_src_files,$(SUBFOLDER)) ) )


##########################################################################
#
# include variables
#
##########################################################################

INCL_FILES:=$(INCL_FILES) $(addprefix $(DIR_INCL), $(shell ls $(DIR_INCL)) )

#$(call generat_incl_files, Subfolder)
#
# @param Subfolder the (namespace) subfolder which contains the incl/ folder
#    with the header files
#
define generat_incl_files
INCL_FILES:=$(INCL_FILES) $(addprefix $(1)/$(DIR_INCL), $(shell ls $(1)/$(DIR_INCL)) )
INCL:=$(INCL) -I$(1)/$(DIR_INCL)
endef

$(foreach SUBFOLDER, $(NAMESPACES), $(eval $(call generat_incl_files,$(SUBFOLDER)) ) )



##########################################################################
#
# test variables
#
##########################################################################


TEST_TOOLS:=$(DIR_FIB)obj_test/tGeneratorForFibObjects.o

#$(call generat_test_files, Subfolder)
#
# @param Subfolder the (namespace) subfolder which contains the incl/ folder
#    with the header files
#
define generat_test_files
TEST_FILES:=$(TEST_FILES) $(addprefix $(1)/$(DIR_TEST), $(shell ls $(1)/$(DIR_TEST)) )
TEST_BIN:=$(TEST_BIN) $(addprefix $(1)/$(DIR_TESTCASE), $(subst .cpp,, $(shell ls $(1)/$(DIR_TEST)) ) )
endef

$(foreach SUBFOLDER, $(NAMESPACES), $(eval $(call generat_test_files,$(SUBFOLDER)) ) )


OBJ_TEST_FILES:=$(subst .cpp,.o,$(subst $(DIR_TEST),$(DIR_OBJ_TEST),$(TEST_FILES) ))


#TEST_PROGRAMS:=t_nD1_nPolynom_evaluePolynomRange t_nD1_nPolynom_findPolynomRand\
#  t_nD1_nPolynom_evaluePolynomHillClimbing tNReduceFibObject t_nD1_nPolynom\
#  t_nD1_createAreasForPoints t_nTidyFibObjects_nBalanceLists



##########################################################################
#
# object variables
#
##########################################################################

OBJ_FILES:=$(subst .cpp,.o,$(subst $(DIR_SRC),$(DIR_OBJ),$(SRC_FILES) ))

OBJ_TEST_FILES:=$(subst .cpp,.o,$(subst $(DIR_SRC),$(DIR_OBJ_TEST),$(SRC_FILES) ))

OBJ_TINYXML:=$(addprefix $(DIR_TINYXML), tinyxml.o tinyxmlparser.o tinyxmlerror.o tinystr.o)

##########################################################################
#
# compile rules
#
##########################################################################

.PHONY: all test clean create_dirs $(DIR_FIB_LIB)libfib.a $(DIR_FIB_LIB)libfib_test.a\
	win win_test

all: create_dirs dependencies.dep $(DIR_LIB)libfib_algorithms.a\
	$(DIR_FIB_LIB)libfib.a $(DIR_GLPK_LIBS)libglpk.a

test: create_dirs dependencies.dep $(DIR_LIB)libfib_algorithms_test.a $(TEST_BIN)\
	$(DIR_GLPK_LIBS)libglpk.a
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
win: WINDOWS:=true
win: all
win_test: create_dirs dependencies.dep $(DIR_LIB)libfib_algorithms_test.a\
	$(DIR_GLPK_LIBS)libglpk.a $(TEST_BIN)
win_test: CFLAG:=$(CFLAG_TEST) -DWINDOWS
win_test: WINDOWS:=true
win_test: LIBS_TEST:=$(LIBS_WIN_TEST)


##########################################################################
#
# rules to create the glpk object files
#
##########################################################################

$(DIR_GLPK_LIBS)libglpk.a:
	if ! [ -e  $(DIR_GLPK)glpk_config.flg ]; then\
	   cd $(DIR_GLPK);\
	   ./configure --disable-shared;\
	   echo > glpk_config.flg;\
	   cd -;\
	fi;\
	make CFLAGS=-O2 --directory=$(DIR_GLPK);\



##########################################################################
#
# Fib -algorithms libaries to produce
#
##########################################################################

$(DIR_LIB)libfib_algorithms.a: $(OBJ_TINYXML) $(OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $?


##########################################################################
#
# Fib -testalgorithmslibaries to produce
#
##########################################################################

$(DIR_LIB)libfib_algorithms_test.a: $(OBJ_TINYXML) $(OBJ_TEST_FILES)
	$(AR) $(ARFLAGS) $@ $?


##########################################################################
#
# rules for the fib -libary
#
##########################################################################

$(DIR_FIB_LIB)libfib.a:
	make --directory=$(DIR_FIB)

$(DIR_FIB_LIB)libfib_test.a:
	make --directory=$(DIR_FIB) test


##########################################################################
#
# rules to create the testprograms
#
##########################################################################

#$(call generat_test_rules, Subfolder)
#
# @param Subfolder the (namespace) subfolder which contains the test files
#
define generat_test_rules
$(1)/$(DIR_TESTCASE)%: $(1)/$(DIR_OBJ_TEST)%.o $(TEST_TOOLS) $(DIR_FIB_LIB)libfib_test.a\
  $(DIR_LIB)libfib_algorithms_test.a
	$(CC) $$(CFLAG_TEST) $$(LDFLAGS) -o $$@ $$^ $$(LIBS_TEST)
endef

$(foreach SUBFOLDER, $(NAMESPACES), $(eval $(call generat_test_rules,$(SUBFOLDER)) ) )


$(TEST_TOOLS):
	make --directory=$(DIR_FIB) test


##########################################################################
#
# creat folders
#
##########################################################################

DIRS_TO_DELETE:=$(DIRS_TO_DELETE) $(DIR_OBJ) $(DIR_OBJ_TEST) $(DIR_TESTCASE)


#$(call generat_folders, Subfolder)
#
# @param Subfolder the (namespace) subfolder in which the folder should be
#    created
#
define generat_folders
$(1)/$$(DIR_OBJ):
	mkdir -p $(1)/$$(DIR_OBJ)

$(1)/$$(DIR_OBJ_TEST):
	mkdir -p $(1)/$$(DIR_OBJ_TEST)

$(1)/$$(DIR_TESTCASE):
	mkdir -p $(1)/$$(DIR_TESTCASE)

DIRS_TO_DELETE:=$(DIRS_TO_DELETE) $(1)/$$(DIR_OBJ) $(1)/$$(DIR_OBJ_TEST) $(1)/$$(DIR_TESTCASE)
endef

$(foreach SUBFOLDER, $(NAMESPACES), $(eval $(call generat_folders,$(SUBFOLDER)) ) )


$(DIR_BIN):
	mkdir -p $(DIR_BIN)

$(DIR_LIB):
	mkdir -p $(DIR_LIB)

DIRS_TO_DELETE:=$(DIRS_TO_DELETE) $(DIR_BIN) $(DIR_LIB)

create_dirs:$(DIRS_TO_DELETE)

##########################################################################
#
# creat dependencies
#
##########################################################################

dependencies.dep: $(SRC_FILES) $(INCL_FILES) $(TEST_FILES)
	rm -f dependencies.dep
	$(foreach QUELLE,  $(SRC_FILES) $(TEST_FILES), \
	$(CC) -MM $(CFLAG) $(INCL) -c $(QUELLE) -MT $(subst $(DIR_TEST),$(DIR_OBJ), $(subst $(DIR_SRC),$(DIR_OBJ), $(subst .cpp,.o, $(QUELLE) ) ) ) >> dependencies.dep; \
	echo "	\$$(CC) \$$(CFLAG) \$$(INCL) -c \$$< -o \$$@" >> dependencies.dep; )
	$(foreach QUELLE,  $(SRC_FILES) $(TEST_FILES), \
	$(CC) -MM $(CFLAG_TEST) $(INCL) -c $(QUELLE) -MT $(subst $(DIR_SRC),$(DIR_OBJ_TEST), $(subst $(DIR_TEST),$(DIR_OBJ_TEST), $(subst .cpp,.o, $(QUELLE) ) ) ) >> dependencies.dep; \
	echo "	\$$(CC) \$$(CFLAG_TEST) \$$(INCL) -c \$$< -o \$$@" >> dependencies.dep; )



ifneq "$(MAKECMDGOALS)" "clean"
-include dependencies.dep
endif

##########################################################################
#
# clean rules
#
##########################################################################

clean:
	rm -rf $(DIRS_TO_DELETE)
	rm -f dependencies.dep dependencies.dep_tmp
	make clean --directory=$(DIR_TINYXML)





