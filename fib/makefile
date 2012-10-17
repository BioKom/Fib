#
# @author Betti Oesterholz
# @date 13.05.2009
# @mail webmaster@BioKom.info
#
# System: make
#
# This is the makefile for the fib -multimedialangue C++ system.
# Copyright (C) @c GPL3 2009 Betti Oesterholz
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
# 		to create the fib-multimedialange library
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
# 16.05.2010   Oesterholz   tDomainInteger included
# 25.07.2010   Oesterholz   tTypeComments included
# 01.08.2010   Oesterholz   tComment included
# 03.08.2010   Oesterholz   sizeofElements included
# 31.10.2010   Oesterholz   tGeneratePictures included
# 19.01.2011   Oesterholz   rule for windows compatibility added
# 21.02.2011   Oesterholz   countElementsAndBits included
# 01.05.2011   Oesterholz   tConditionFalse included
# 02.05.2011   Oesterholz   tConditionTrue included
# 02.05.2011   Oesterholz   tIf included
# 10.05.2011   Oesterholz   tConditionNot included
# 13.05.2011   Oesterholz   tConditionTwoValue included
# 15.05.2011   Oesterholz   tConditionComparison included
# 10.06.2011   Oesterholz   tFunctionIf included
# 14.07.2011   Oesterholz   zlib for the optional part included
# 24.07.2011   Oesterholz   tTypeExtObject included
# 24.08.2011   Oesterholz   tExtObject included
# 25.08.2011   Oesterholz   tTypeUnderArea to tTypeSubarea
# 06.11.2011   Oesterholz   tTypeExtSubobject included
# 09.11.2011   Oesterholz   tExtSubobject included
# 21.11.2011   Oesterholz   library "-lm" included
# 27.11.2011   Oesterholz   library "-lpthread" for cFibDatabase included
# 27.11.2011   Oesterholz   tFibDatabase included
# 02.12.2011   Oesterholz   extractFibDbDescriptions included
# 03.12.2011   Oesterholz   tDomainVectorOpenEnd included
# 04.12.2011   Oesterholz   tTypeFibSet included
# 05.12.2011   Oesterholz   tTypeFibMatrix included
# 15.12.2011   Oesterholz   tVectorFibSet included
# 22.12.2011   Oesterholz   tFibSet included
# 02.01.2012   Oesterholz   tTypeSubarea to tTypeArea
# 07.01.2012   Oesterholz   tVectorFibMatrix and tFibMatrix included
# 21.01.2012   Oesterholz   tTypeExtObjectInput included
# 26.01.2012   Oesterholz   tVectorExtObject included
# 04.02.2012   Oesterholz   tVectorExtSubobject included
# 14.02.2012   Oesterholz   tDomainReference included
# 24.02.2012   Oesterholz   changes for windows zlib
# 17.08.2012   Oesterholz   bash "if [ -a" is depricated using "-e"
# 14.10.2012   Oesterholz   library "-lpthread" included


##########################################################################
#
# folder variables
#
##########################################################################

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

# folder for tinyxml an (tiny) XML -parser
DIR_TINYXML:=../tinyxml/
#Flags for tinyxml
TINYXML_FLAGS:=-DTIXML_USE_STL


# folder for zlib package
DIR_ZLIB:=../other_packages/zlib/

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
CFLAG_OPTIMISE:=-O -O2 $(TINYXML_FLAGS)
CFLAG:=$(CFLAG_OPTIMISE)
CFLAG_TEST:=-g -pg -Wall -DTEST $(TINYXML_FLAGS)
INCL:=-I$(BASE_DIR) -I$(DIR_INCL) -I$(DIR_TINYXML) -I$(DIR_ZLIB)
#TODO "-lm" needed?
#TODO add "-lpthread" and FEATURE_FIB_DB_USE_TREADS when windows treads are implemented
LIBS:=-lstdc++ -lm -lpthread
LIBS_WIN:=-static -lstdc++ -lm



##########################################################################
#
# source variables
#
##########################################################################

SRC_FIB:=$(addprefix $(DIR_SRC), $(shell ls $(DIR_SRC)) )


##########################################################################
#
# include variables
#
##########################################################################

INCL_FIB:=$(addprefix $(DIR_INCL), $(shell ls $(DIR_INCL)) )


##########################################################################
#
# include variables
#
##########################################################################

TEST_FIB:=$(addprefix $(DIR_TEST), $(shell ls $(DIR_TEST)) )

TEST_PROGRAMS:=tDomainNaturalNumberBit tDomainNaturalNumber\
	tDomainIntegerBit tDomainInteger tDomainRational tDomainVector\
	tDomainVectorOpenEnd tDomainReference tDomainElement tDomains\
	tMultimediaInfo tOptionalPart tFibDatabase\
	tTypeDimension tTypeProperty tTypeInVar tTypeVariable tTypeArea\
	tTypeUnderFunction tTypeComments tTypeExtObject tTypeExtSubobject\
	tTypeFibSet tTypeFibMatrix tTypeExtObjectInput\
	tFibVariable tVectorPosition tVectorProperty tVectorChecksum tVectorArea\
	tVectorFibSet tVectorFibMatrix tVectorExtObject tVectorExtSubobject\
	tRoot tList tPoint tProperty tArea tFunction tComment tExtObject\
	tExtSubobject tFibSet tFibMatrix\
	tFunctionValue tFunctionVariable tFunctionTwoValue tFunctionOneValue\
	tFunctionIf\
	tIf tConditionFalse tConditionTrue tConditionNot tConditionTwoValue\
	tConditionComparison\
	tGenerateFibObjects tFibObjectVariable tFibElementStructur tFibObject\
	tFibObjectStore tEvalueObject\
	sizeofElements countElementsAndBits tGeneratePictures\
	extractFibDbDescriptions

TEST_TOOLS:=$(DIR_OBJ_TEST)tDomainTools.o $(DIR_OBJ_TEST)tGeneratorForFibObjects.o

TEST_BIN:=$(addprefix $(DIR_TESTCASE), $(TEST_PROGRAMS) )


##########################################################################
#
# object variables
#
##########################################################################

OBJ_FIB:=$(subst .cpp,.o,$(subst $(DIR_SRC),$(DIR_OBJ),$(SRC_FIB) ))

OBJ_TEST_FIB:=$(subst .cpp,.o,$(subst $(DIR_SRC),$(DIR_OBJ_TEST),$(SRC_FIB) ))

OBJ_TINYXML:=$(addprefix $(DIR_TINYXML), tinyxml.o tinyxmlparser.o tinyxmlerror.o tinystr.o)

OBJ_ZLIB:= $(addprefix $(DIR_ZLIB), adler32.o compress.o crc32.o deflate.o\
	gzclose.o gzlib.o gzread.o gzwrite.o infback.o inffast.o inflate.o\
	inftrees.o trees.o uncompr.o zutil.o )

##########################################################################
#
# compile rules
#
##########################################################################

.PHONY: all test clean win win_test zlib

all: $(DIR_OBJ) $(DIR_BIN) $(DIR_LIB) dependencies.dep $(DIR_LIB)libfib.a

test: $(DIR_OBJ_TEST) $(DIR_TESTCASE) $(DIR_LIB) dependencies.dep $(DIR_LIB)libfib_test.a $(TEST_BIN)
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

win: CFLAG:=$(CFLAG_OPTIMISE) -DWINDOWS
win: WINDOWS:=true
win: all
win: LIBS:=$(LIBS_WIN)
win_test: $(DIR_OBJ_TEST) $(DIR_TESTCASE) $(DIR_LIB) dependencies.dep $(DIR_LIB)libfib_test.a $(TEST_BIN)
win_test: CFLAG:=$(CFLAG_TEST) -DWINDOWS
win_test: WINDOWS:=true
win_test: LIBS:=$(LIBS_WIN)


##########################################################################
#
# rules to create the zlib object files
#
##########################################################################

$(OBJ_ZLIB): zlib
	true #nothing to do for $@ , don't use standardrules

zlib:
	if [ "$(WINDOWS)" != "true" ]; then\
	   if ! [ -e  $(DIR_ZLIB)zlib_config.flg ]; then\
	      cd $(DIR_ZLIB);\
	      ./configure --static;\
	      echo > zlib_config.flg;\
	      cd -;\
	   fi;\
	   make --directory=$(DIR_ZLIB);\
	else\
	   make --directory=$(DIR_ZLIB) -f win32/Makefile.gcc;\
	fi;




##########################################################################
#
# Fib -libaries to produce
#
##########################################################################

$(DIR_LIB)libfib.a: $(OBJ_TINYXML) $(OBJ_ZLIB) $(OBJ_FIB)
	$(AR) $(ARFLAGS) $@ $?


##########################################################################
#
# Fib -testlibaries to produce
#
##########################################################################

$(DIR_LIB)libfib_test.a: $(OBJ_TINYXML) $(OBJ_ZLIB) $(OBJ_TEST_FIB)
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
$(DIR_TESTCASE)$(1): $(DIR_OBJ_TEST)$(1).o $(TEST_TOOLS) $(DIR_LIB)libfib_test.a
	$(CC) $$(CFLAG_TEST) $$(LDFLAGS) -o $$@ $$^ $$(LIBS)
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

dependencies.dep: $(SRC_FIB) $(INCL_FIB) $(TEST_FIB)
	rm -f dependencies.dep_tmp
	$(foreach QUELLE,  $(SRC_FIB) $(TEST_FIB), \
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
	if [ -e  $(DIR_ZLIB)zlib_config.flg ]; then\
		make clean --directory=$(DIR_ZLIB);\
	fi;
	rm -f $(DIR_ZLIB)zlib_config.flg
	make clean --directory=$(DIR_ZLIB) -f win32/Makefile.gcc


