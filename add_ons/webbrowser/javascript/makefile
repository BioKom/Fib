#
# @author Betti Oesterholz
# @date 09.04.2013
# @mail webmaster@BioKom.info
#
# System: make
#
# This is the makefile for the fib -multimedialangue C++ system.
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
# 09.04.2013   Oesterholz   created


INTERFACE_FUNCTIONS_TO_CPP:= -s EXPORTED_FUNCTIONS="['_convertFibToImageData','_printPoint','_getBitmapData',\
	'_printGivenData','_setDatabasePath']"


##########################################################################
#
# folder variables
#
##########################################################################



# relativ path to the fib -multimediasystem base directory
BASE_DIR:=../../../

# folders of this part
DIR_SRC:=src/
DIR_INCL:=incl/
FILE_FOR_FIB_DATABASE_FILES:=$(DIR_INCL)fibDatabaseFiles.h

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

# path of the Fib element module
DIR_FIB:=$(BASE_DIR)fib/
DIR_FIB_INCL:=$(DIR_FIB)incl/
DIR_FIB_SRC:=$(DIR_FIB)src/
DIR_FIB_DB:=$(DIR_FIB)fibDatabase/


# folder for tinyxml an (tiny) XML -parser
DIR_TINYXML:=$(BASE_DIR)/tinyxml/
#Flags for tinyxml
TINYXML_FLAGS:=-DTIXML_USE_STL

# path of emscripten
EMSCRIPTEN_PATH:=/home/biokom/Sprachen/emscripten/

# folder for zlib package
DIR_ZLIB:=$(BASE_DIR)/other_packages/zlib/

# flag if windows is the operating system passible values: true, false
WINDOWS:=false

##########################################################################
#
# compile variables
#
##########################################################################

SHELL:=/bin/sh
CC:=gcc
EMSCRIPTEN:=emcc
#TODO implement "--preload-file"
#EMSCRIPTEN_FLAG:=-s WARN_ON_UNDEFINED_SYMBOLS=1 --preload-file $(DIR_FIB)/fibDatabase
EMSCRIPTEN_FLAG:=-s WARN_ON_UNDEFINED_SYMBOLS=1\
   --js-library $(DIR_SRC)funJavaScriptFileHandling.js
#debugg flags
#CFLAG:=-g -Wall
#optimize compile flags
#TODO switch
DEFINES:=-DMAX_DATABASE_PATH_SEARCH_DEPTH=0
# DEFINES:=-DSWITCH_JUST_STORE_AND_EVALUE -DMAX_DATABASE_PATH_SEARCH_DEPTH=0
DEFINES_DEBUG_OUTPUT:=-DDEBUG_RESTORE_XML -DDEBUG_EVALUE

#TODO switch
CFLAG_OPTIMISE:=-O $(TINYXML_FLAGS) $(DEFINES)
#CFLAG_OPTIMISE:=-O -O2 $(TINYXML_FLAGS) $(DEFINES)
CFLAG:=$(CFLAG_OPTIMISE)
CFLAG_TEST:=-g -pg -Wall -DTEST $(TINYXML_FLAGS) $(DEFINES)
INCL:=-I$(BASE_DIR) -I. -I$(DIR_INCL) -I$(DIR_FIB_INCL) -I$(DIR_TINYXML) -I$(DIR_ZLIB)
#TODO "-lm" needed?
#TODO add "-lpthread" and FEATURE_FIB_DB_USE_TREADS when windows treads are implemented
LIBS:=-lstdc++ -lm -lpthread
LIBS_WIN:=-static -lstdc++ -lm
COMPRESS:=


##########################################################################
#
# source variables
#
##########################################################################

SRC_FIB:=$(addprefix $(DIR_FIB_SRC), $(shell ls $(DIR_FIB_SRC)) )

SRC_ZLIB_JAVASCRIPT:=$(shell ls $(DIR_SRC)*.cpp)
#TODO weg: $(DIR_SRC)jsInterface.cpp $(DIR_SRC)jsInterface.cpp


##########################################################################
#
# include variables
#
##########################################################################

INCL_FIB:=$(addprefix $(DIR_FIB_INCL), $(shell ls $(DIR_FIB_INCL)) )


##########################################################################
#
# include variables
#
##########################################################################

TEST:=$(addprefix $(DIR_TEST), $(shell ls $(DIR_TEST)) )


##########################################################################
#
# object variables
#
##########################################################################

OBJ_FIB:= $(subst .cpp,.o,$(subst $(DIR_SRC),$(DIR_OBJ),$(SRC_FIB) ))

OBJ_TEST_FIB:= $(subst .cpp,.o,$(subst $(DIR_SRC),$(DIR_OBJ_TEST),$(SRC_FIB) ))

OBJ_TINYXML:= $(addprefix $(DIR_TINYXML), tinyxml.o tinyxmlparser.o tinyxmlerror.o tinystr.o)

OBJ_ZLIB:= $(addprefix $(DIR_ZLIB), adler32.o compress.o crc32.o deflate.o\
	gzclose.o gzlib.o gzread.o gzwrite.o infback.o inffast.o inflate.o\
	inftrees.o trees.o uncompr.o zutil.o )


##########################################################################
#
# more source variables (zlib and tinyxml)
#
##########################################################################

SRC_TINYXML:= $(subst .o,.cpp, $(OBJ_TINYXML) )

SRC_ZLIB:= $(subst .o,.c, $(OBJ_ZLIB) )


##########################################################################
#
# compile rules
#
##########################################################################

.PHONY: all test clean win win_test zlib compress jsfib jsfib_dbg htmlFib db_file

all: clean $(DIR_OBJ) $(DIR_BIN) $(DIR_LIB) dependencies.dep \
	$(FILE_FOR_FIB_DATABASE_FILES) jsfib jsfib_dbg

test: clean $(DIR_OBJ_TEST) $(DIR_TESTCASE) $(DIR_LIB) dependencies.dep \
	$(FILE_FOR_FIB_DATABASE_FILES) jsfib jsfib_dbg
test: CFLAG:=$(CFLAG_TEST)


$(OBJ_TINYXML): tinyxml
	true #nothing to do for $@ , don't use standardrules

tinyxml:
	make --directory=$(DIR_TINYXML)



compress: COMPRESS:=--compression $(EMSCRIPTEN_PATH)third_party/lzma.js/lzma-native,$(EMSCRIPTEN_PATH)third_party/lzma.js/lzma-decoder.js,LZMA.decompress
compress: all

# TODO rework

jsfib: db_file $(DIR_LIB)libfib.js
$(DIR_LIB)libfib.js: $(SRC_FIB) $(SRC_TINYXML) $(SRC_ZLIB) $(SRC_ZLIB_JAVASCRIPT)
	$(EMSCRIPTEN) $(INCL) $(CFLAG) $(INTERFACE_FUNCTIONS_TO_CPP) $(EMSCRIPTEN_FLAG) -o $@ $^ $(COMPRESS)

#version with debugging information
jsfib_dbg: db_file $(DIR_LIB)libfib_dbg.js
$(DIR_LIB)libfib_dbg.js: $(SRC_FIB) $(SRC_TINYXML) $(SRC_ZLIB) $(SRC_ZLIB_JAVASCRIPT)
	$(EMSCRIPTEN) $(INCL) $(CFLAG) $(DEFINES_DEBUG_OUTPUT) $(INTERFACE_FUNCTIONS_TO_CPP) $(EMSCRIPTEN_FLAG) -o $@ $^ $(COMPRESS)

#HTML version
htmlFib: db_file $(DIR_OBJ_TEST) $(DIR_TESTCASE) $(DIR_LIB) dependencies.dep $(DIR_LIB)libfib.html

$(DIR_LIB)libfib.html: $(SRC_FIB) $(SRC_TINYXML) $(SRC_ZLIB) src/jsInterface.cpp
	$(EMSCRIPTEN) $(INCL) $(CFLAG) $(INTERFACE_FUNCTIONS_TO_CPP) $(EMSCRIPTEN_FLAG) -o $@ $^ $(COMPRESS)




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
# rules to generate a file with the fib database files
#
##########################################################################

# TODO
db_file: $(FILE_FOR_FIB_DATABASE_FILES)

$(FILE_FOR_FIB_DATABASE_FILES): $(DIR_FIB_DB)
	cd $(DIR_FIB_DB); DATABASE_FILES=$$(ls *.xml *.fib 2>/dev/null);\
	cd - ;\
	echo "//file with the list of the database files" > $@ ;\
	echo "" >> $@ ;\
	echo "#include <list>" >> $@ ;\
	echo "#include <string>" >> $@ ;\
	echo "" >> $@ ;\
	echo "static unsigned int const uiNumberArSzFilesOfFibDatabase = "$$(echo $${DATABASE_FILES} | wc -w)";" >> $@ ;\
	echo "static string const arSzFilesOfFibDatabase[] = {" >> $@ ;\
#	echo "std::list<std::string> liFilesOfFibDatabase = std::list<std::string>{" >> $@ ;\
	for FILE in $${DATABASE_FILES};\
	do\
		echo  "   \"$${FILE}\"," >>  $@ ;\
	done;\
	echo '   "" };' >>  $@
	
	

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
	rm $(FILE_FOR_FIB_DATABASE_FILES)
	rm -f dependencies.dep dependencies.dep_tmp
	make clean --directory=$(DIR_TINYXML)
	if [ -e  $(DIR_ZLIB)zlib_config.flg ]; then\
		make clean --directory=$(DIR_ZLIB);\
	fi;
	rm -f $(DIR_ZLIB)zlib_config.flg
	make clean --directory=$(DIR_ZLIB) -f win32/Makefile.gcc


