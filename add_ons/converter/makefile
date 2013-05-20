#
# make [clean]
#
# options:
#	clean: cleans the project
#
#
# @author Betti Oesterholz
# @date 23.02.2010
# @mail webmaster@BioKom.info
#
# System: make
#
# This makefile for the fib -converter (C++).
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
# The convertersystem is for converting multimediaobjects in not fib
# -multimediaformats, more or less directly, into a fib -multimediaobjects.
#
##########################################################################
#
# History:
# 18.06.2010   Oesterholz   convertFibToFib added
# 30.03.2011   Oesterholz   evalueDerivate added
# 14.05.2011   Oesterholz   rules for windows compability added
# 18.05.2011   Oesterholz   own FreeImage wraper fipImage (for windows) added
# 14.07.2011   Oesterholz   actual solution for FreeImage in windows:
# 		copy the FreeImage.dll into the binary path (wher the executebels are)
# 15.08.2011   Oesterholz   lib -lpthread for linux added
# 21.11.2011   Oesterholz   library "-lm" included
# 14.04.2012   Oesterholz   FreeImage wraper cFreeImageData added
# 11.09.2012   Oesterholz   standard libaries to the end
# 14.07.2012   Oesterholz   glpk included for FEATURE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING
# 14.10.2012   Oesterholz   library "-lpthread" included
# 21.12.2012   Oesterholz   FreeImage needs libm
# 21.01.2013   Oesterholz   convertFibToFibPointList added
# 27.04.2013   Oesterholz   convertFromImageStructure and
#		cEvalueSimpleRGBA255Sec added



##########################################################################
#
# folder variables
#
##########################################################################


# relativ path to the fib -multimediasystem base directory
BASE_DIR:=../../


# folders of the converter source code
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
INCL_FIB_ALGORITHMS:=$(addprefix -I$(PATH_FIB_ALGORITHMS), $(addsuffix /incl/, $(NAMESPACES) ) )


# folder for FreeImage system, a library to read write image formats
DIR_FREE_IMAGE_PLUS:=FreeImage/
# the folder which contains the FreeImage files to link to
DIR_FREE_IMAGE_PLUS_DIST:=$(DIR_FREE_IMAGE_PLUS)Dist/
# the windows dll file for FreeImage
FREE_IMAGE_DLL:=FreeImageWin/Dist/FreeImage.dll
DIR_FREE_IMAGE_DLL:=FreeImageWin/Dist/


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
CFLAG:=-O -O2 $(TINYXML_FLAGS)
CFLAG_TEST:=-g -pg -Wall -DTEST $(TINYXML_FLAGS)
INCL:=-I$(BASE_DIR) -I$(DIR_INCL) -I$(DIR_FREE_IMAGE_PLUS_DIST) -I$(DIR_FIB_INCL)\
	-I$(DIR_TINYXML) $(INCL_FIB_ALGORITHMS) -I./FreeImage/Source/\
	-I$(DIR_GLPK_INCLUDE)
LIBS:=-L$(DIR_FIB_LIB) -lfib -L$(PATH_FIB_ALGORITHMS_LIB) -lfib_algorithms\
	-L$(DIR_GLPK_LIBS) -lglpk -lstdc++ -lm -lpthread
#TODO remove -static ???
LIBS_TEST:=-L$(DIR_FIB_LIB) -lfib_test -L$(PATH_FIB_ALGORITHMS_LIB) -lfib_algorithms_test\
	-L$(DIR_GLPK_LIBS) -lglpk -lstdc++ -lm -lpthread
LIBS_FREEIMAGE_PLUS:=-L$(DIR_FREE_IMAGE_PLUS_DIST) -lfreeimageplus -lm
LIBS_WIN:=-L$(DIR_FIB_LIB) -lfib -L$(PATH_FIB_ALGORITHMS_LIB) -lfib_algorithms\
	-L$(DIR_FREE_IMAGE_DLL) -lFreeImage -L$(DIR_GLPK_LIBS) -lglpk\
	-static -lstdc++ -lm
LIBS_WIN_TEST:=-L$(DIR_FIB_LIB) -lfib_test\
	-L$(PATH_FIB_ALGORITHMS_LIB) -lfib_algorithms_test\
	-L$(DIR_FREE_IMAGE_DLL) -lFreeImage -L$(DIR_GLPK_LIBS) -lglpk\
	-static -lstdc++ -lm
#TODO: link freeimageplus static ?
#	-L$(DIR_FREE_IMAGE_PLUS_DIST) -static -lfreeimageplus -lstdc++


##########################################################################
#
# source variables
#
##########################################################################

SRC_CONVERTER:=$(addprefix $(DIR_SRC), nConvertToFib.cpp nConvertFromFib.cpp\
	fipImage.cpp cFreeImageData.cpp cEvalueSimpleRGBA255Sec.cpp)


##########################################################################
#
# include variables
#
##########################################################################

INCL_CONVERTER:=$(addprefix $(DIR_INCL), $(shell ls $(DIR_INCL)) )


##########################################################################
#
# include variables
#
##########################################################################

TEST_CONVERTER:=$(addprefix $(DIR_TEST), $(shell ls $(DIR_TEST)) )

TEST_PROGRAMS:=

TEST_BIN:=$(addprefix $(DIR_TESTCASE), $(TEST_PROGRAMS) )


##########################################################################
#
# object variables
#
##########################################################################

OBJ_CONVERTER:=$(subst .cpp,.o,$(subst $(DIR_SRC),$(DIR_OBJ),$(SRC_CONVERTER) ))

OBJ_TEST_CONVERTER:=$(subst .cpp,.o,$(subst $(DIR_SRC),$(DIR_OBJ_TEST),$(SRC_CONVERTER) ))

##########################################################################
#
# executebel variables
#
##########################################################################

# the to create executebels
EXE_FILES:=convertToFib convertFromFib convertFibToFib evalueDerivate\
	convertFibToFibPointList convertFromImageStructure

SRC_EXE_FILES:=$(addprefix $(DIR_SRC), $(addsuffix .cpp, $(EXE_FILES) ) )

##########################################################################
#
# compile rules
#
##########################################################################

.PHONY: all test freeImage freeImageWin clean fib fib_algorithms\
	fib_test fib_algorithms_test win win_test

MAKEFILE_FLAG:=

all: $(DIR_OBJ) $(DIR_BIN) $(DIR_LIB)\
	 dependencies.dep fib fib_algorithms freeImage\
	$(addprefix $(DIR_BIN), $(EXE_FILES) ) $(DIR_LIB)libconverter.a
all: LIBS:=$(LIBS) -lpthread $(LIBS_FREEIMAGE_PLUS)

test: $(DIR_OBJ_TEST) $(DIR_TESTCASE) $(DIR_LIB) $(TEST_BIN) $(DIR_BIN)\
	dependencies.dep fib fib_algorithms  freeImage\
	$(addprefix $(DIR_BIN)test_, $(EXE_FILES) ) $(DIR_LIB)libconverter_test.a
test: CFLAG:=$(CFLAG_TEST)
test: LIBS_TEST:=$(LIBS_TEST) -lpthread $(LIBS_FREEIMAGE_PLUS)
test: MAKEFILE_FLAG:=test



freeImage:
	make --directory=$(DIR_FREE_IMAGE_PLUS) -f Makefile.fip

freeImage_mingw:
	make --directory=$(DIR_FREE_IMAGE) -f Makefile.mingw

freeImageWin:$(DIR_BIN)
	cp -u $(FREE_IMAGE_DLL) $(DIR_BIN)


fib:
	make --directory=$(DIR_FIB) $(MAKEFILE_FLAG)

fib_algorithms:
	make --directory=$(PATH_FIB_ALGORITHMS) $(MAKEFILE_FLAG)



##########################################################################
#
# rule for windows compatibility
#
##########################################################################

win: $(DIR_OBJ) $(DIR_BIN) $(DIR_LIB)\
	dependencies.dep fib fib_algorithms freeImageWin\
	$(addprefix $(DIR_BIN), $(EXE_FILES) ) $(DIR_LIB)libconverter.a
#TODO	freeImage_mingw
win: CFLAG:=$(CFLAG) -DWINDOWS
win: MAKEFILE_FLAG:=win
win: LIBS:=$(LIBS_WIN)


win_test: $(DIR_OBJ_TEST) $(DIR_TESTCASE) $(DIR_LIB) dependencies.dep\
	$(TEST_BIN) fib fib_algorithms freeImageWin $(DIR_BIN)\
	$(addprefix $(DIR_BIN)test_, $(EXE_FILES) ) $(DIR_LIB)libconverter_test.a
#TODO	freeImage_mingw
win_test: CFLAG:=$(CFLAG_TEST) -DWINDOWS
win_test: MAKEFILE_FLAG:=win_test
win_test: LIBS_TEST:=$(LIBS_WIN_TEST)



##########################################################################
#
# converterlibaries to produce
#
##########################################################################

$(DIR_LIB)libconverter.a: $(OBJ_CONVERTER)
	$(AR) $(ARFLAGS) $@ $?


##########################################################################
#
# convertertestlibaries to produce
#
##########################################################################

$(DIR_LIB)libconverter_test.a: $(OBJ_TEST_CONVERTER)
	$(AR) $(ARFLAGS) $@ $?


##########################################################################
#
# rules for the fib -libary
#
##########################################################################

$(DIR_FIB_LIB)libfib.a: fib


$(PATH_FIB_ALGORITHMS_LIB)libfib_algorithms.a: fib_algorithms


$(DIR_FIB_LIB)libfib_test.a: fib_test

$(PATH_FIB_ALGORITHMS_LIB)libfib_algorithms_test.a: fib_algorithms_test


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
# rules to create the testprograms
#
##########################################################################


#$(call generat_bins, Programname)
#
# @param Programname (file-)name of the program to generate
#
define generat_bins
$(DIR_BIN)$(1):$(DIR_OBJ)$(1).o $(DIR_LIB)libconverter.a $(DIR_FIB_LIB)libfib.a\
		$(PATH_FIB_ALGORITHMS_LIB)libfib_algorithms.a
	$(CC) $$(CFLAG) $(LDFLAGS) -o $$@ $$^ -L$(DIR_LIB) -lconverter $$(LIBS)
endef

$(foreach PROGRAM, $(EXE_FILES), $(eval $(call generat_bins,$(PROGRAM)) ) )


#$(call generat_test_bin, Testprogramname)
#
# @param Testprogramname (file-)name of the testprogram to generate
#
define generat_test_bin
$(DIR_TESTCASE)$(1): $(DIR_OBJ_TEST)$(1).o $(TEST_TOOLS) $(DIR_FIB_LIB)libfib_test.a\
		$(PATH_FIB_ALGORITHMS_LIB)libfib_algorithms_test.a
	$(CC) $$(CFLAG_TEST) $(LDFLAGS) -o $$@ $$^ $$(LIBS_TEST)
endef

$(foreach TESTPROGRAM, $(TEST_PROGRAMS), $(eval $(call generat_test_bin,$(TESTPROGRAM)) ) )

#$(call generat_bins, Programname)
#
# @param Programname (file-)name of the program to generate
#
define generat_test_bins
$(DIR_BIN)test_$(1):$(DIR_OBJ_TEST)$(1).o $(DIR_LIB)libconverter_test.a\
		$(DIR_FIB_LIB)libfib_test.a $(PATH_FIB_ALGORITHMS_LIB)libfib_algorithms_test.a
	$(CC) $$(CFLAG_TEST) $(LDFLAGS) -o $$@ $$^ -L$(DIR_LIB) -lconverter_test $$(LIBS_TEST)
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

dependencies.dep: $(SRC_CONVERTER) $(SRC_EXE_FILES) $(INCL_CONVERTER) $(TEST_CONVERTER)
	rm -f dependencies.dep_tmp
	$(foreach QUELLE,  $(SRC_CONVERTER) $(TEST_CONVERTER) $(SRC_EXE_FILES), \
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
#	make --directory=$(DIR_FREE_IMAGE_PLUS) -f Makefile.fip clean





