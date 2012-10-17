/**
 * @file includeOperators
 * file name: includeOperators.cpp
 * @author Betti Oesterholz
 * @date 20.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This program creats a header file with the definitions for the
 * enviroment operators.
 *
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This program creats a header file with the definitions for the
 * enviroment operators.
 * The base directories for the operators will be read from the
 * operator_dirs.txt file. 
 * In it every line with an '#' as the first character will be ignored, it is an
 * comment line. Every line with no '#' as the first character, should just
 * contain the path of a directory with operators and no other characters
 * (this means also no blanks or else except the ending new line character).
 * The path should be given relativ to the fib/enviroment.fib/operators/ path.
 * The directory of the path should contain two subdirectories "incl/" and
 * "src/". The "incl/" directory should contain the header files, with
 * headers of the operators. The names of the files in the "incl/"
 * directory, without the ending ".h", will be taken as the possible operator
 * names. The "src/" directory, in the same directory as the "incl/"
 * directory, should contain the implemntations of the operators of the 
 * "incl/" directory.
 *
 * With the directory information of the operator_dirs.txt file, this 
 * program will search for the headerfiles in the incl subfolders of each
 * base operators directory.
 * Every such file should contain a operator definition. The names of the
 * headerfiles (without the ending ".h") are taken to be operatornames.
 * With this names a "operators.h" headerfile is created, which contains
 * the information for the operators, such that the enviroment can use
 * them.
 * For special "cInitOperator" an "#define INIT_OPERATOR" is created
 *
 *
 * Example:
 ** Headerfiles in the "incl" subfolder:
 ** 	- cInitOperator.h
 ** 	- cOpCreateNew.h
 **
 ** Created "operators.h" file (without comments):
 *************************************************************************
 **
 **
 ** #ifndef ___ENVIROMENT_OPERATIONS_H__
 ** #define ___ENVIROMENT_OPERATIONS_H__
 **
 ** #include "cOperationIdentifier.h"
 **
 ** #include "cInitOperator.h"
 ** #include "cOpCreateNew.h"
 **
 ** using namespace enviroment::fib;
 ** using namespace enviroment;
 **
 ** //an init operator exists
 ** #define INIT_OPERATOR
 **
 ** namespace enviroment{
 ** namespace operations{
 ** //ignore this namespace; it contains an const instance for every
 ** //operations, so the arrayOperations can contain the instances and the
 ** //instances get destroyed at the execution end
 **
 ** 	const cInitOperator InitOperator( cOperationIdentifier( 0 ) );
 ** 	const cOpCreateNew OpCreateNew( cOperationIdentifier( 0 ) );
 **
 ** };
 ** };
 **
 ** //number of existing operations
 ** //to define this variable const didn't work for the external linkage
 ** unsigned long ulNumberOfOperations = 2;
 **
 ** //array with pointers to the instances of existing operations;
 ** //call the virtual createInstance() method of theas to create
 ** //instances of operations you need
 ** const cOperation * arrayOperations[] = {
 ** 	& (enviroment::operations::InitOperator),
 ** 	& (enviroment::operations::OpCreateNew)
 ** };
 **
 ** #endif //___ENVIROMENT_OPERATIONS_H__
 **
 **
 *************************************************************************
 *
 * Ther will also be created a include file for make with a variable
 * DIRS_OPERATORS, which contains the base directories of the operators.
 */
/*
History:
20.03.2010  Oesterholz  created
25.02.2011  Oesterholz  handling of more operator directories added
*/

//TODO weg: g++ -Wall -g -I../incl -I../../enviroment/incl/ -I../../fib/incl/ -I../../ -o includeOperators includeOperators.cpp ../../fib/lib/libfib_test.a



#include "version.h"

#include "cFolder.h"

#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;


#define INIT_OPERATOR_HEADER "cInitOperator.h"

#ifndef ROOT_DIR_OPERATORS
	#define ROOT_DIR_OPERATORS "./"
#endif
#ifndef FILE_TESTOBJECTS
	#define FILE_TESTOBJECTS "operator_dirs.txt"
#endif



list< string > loadFolderList( const string szFilePath );


const char * pDirTestObjects = ROOT_DIR_OPERATORS;


int main(int argc,char* argv[]){
	
	//the name of the to generate header file
	const string szToGenerteFilePath = "./operators.h";

	//the name of the to generate make include file file
	const string szToGenerteMakeFilePath = "./operators.mk";

	//the name of the to generate make include file file
	const string szToGenerteAllOperatorsFilePath = "./operators.txt";

	
	cout<<endl<<"Generating \""<< szToGenerteFilePath <<"\" ."<<endl;
	
	
//iterate over subfolders
	
	//load the operation folder list
	string szFilePath = string( pDirTestObjects ) + FILE_TESTOBJECTS;
	
	const list< string > liOperatorDirs = loadFolderList( szFilePath );
	if ( liOperatorDirs.empty() ){
		cerr<<"Error: No testfolders to test."<<endl;
		return 1;
	}
	
	cout<<endl<<"Including operators of directories:"<<endl;
	list< string > liOperatorFiles;
	list< string > liOperatorPaths;
	for ( list< string >::const_iterator itrOperatorDir = liOperatorDirs.begin();
			itrOperatorDir != liOperatorDirs.end(); itrOperatorDir++ ){
		//the path to the file which contains the headers of the operators
		const string szOperationIncluedPath = (*itrOperatorDir) + "incl/";
		cout<<"   "<<szOperationIncluedPath<<endl;
		
		//evalue the operator names
		cFolder folderOperatorHeaders( szOperationIncluedPath );
		
		if ( ! folderOperatorHeaders.good() ){
			cerr<<"ERROR: Could not open the folder "<< szOperationIncluedPath <<endl;
			return 1;
		}
		const list< string > liActualOperatorFiles =
			folderOperatorHeaders.getFiles();
		
		for ( list< string >::const_iterator itrFile = liActualOperatorFiles.begin();
				itrFile != liActualOperatorFiles.end(); itrFile++ ){
			
			//yust use header files
			if ( itrFile->compare( itrFile->size() - 2, 2, ".h" ) != 0 ){
				//not an header file -> skip it
				continue;
			}
			liOperatorFiles.push_back( *itrFile );
			liOperatorPaths.push_back( szOperationIncluedPath + (*itrFile) );
		}
	}
	
//generate makefile include
	//open the make include file
	ofstream fileMakeToGenerate( szToGenerteMakeFilePath.c_str() );
	if ( ! fileMakeToGenerate.good() ){
		cerr<<"ERROR: Could not create the file "<< szToGenerteMakeFilePath <<endl;
		return 1;
	}
	//write the file begin
	fileMakeToGenerate<<"# This is a automatic generated file."<<endl;
	fileMakeToGenerate<<"# It was generated by includeOperators the program."<<endl;
	fileMakeToGenerate<<"# The Copyright is (C) @c GPL3 2010 Betti Oesterholz"<<endl;
	fileMakeToGenerate<<"# see includeOperators.cpp for more details"<<endl;
	fileMakeToGenerate<<"#"<<endl;
	fileMakeToGenerate<<"# This is a makefile includefile for the operator directories."<<endl;
	fileMakeToGenerate<<"#"<<endl;
	fileMakeToGenerate<<endl<<endl;
	fileMakeToGenerate<<"DIRS_OPERATORS:=";
	
	for ( list< string >::const_iterator itrOperatorDir = liOperatorDirs.begin();
			itrOperatorDir != liOperatorDirs.end(); itrOperatorDir++ ){
		fileMakeToGenerate<<"\\"<<endl<<"   "<<(*itrOperatorDir);
	}
	fileMakeToGenerate<<endl<<endl;
	fileMakeToGenerate.close();
	
	
//write the to generate header file
	//open the file
	ofstream fileHeaderToGenerate( szToGenerteFilePath.c_str() );
	if ( ! fileHeaderToGenerate.good() ){
		cerr<<"ERROR: Could not create the file "<< szToGenerteFilePath <<endl;
		return 1;
	}
	
	//write the file begin
	fileHeaderToGenerate<<"/**"<<endl;
	fileHeaderToGenerate<<" * This is a automatic generated file."<<endl;
	fileHeaderToGenerate<<" * It was generated by includeOperators the program."<<endl;
	fileHeaderToGenerate<<" * The Copyright is (C) @c GPL3 2010 Betti Oesterholz"<<endl;
	fileHeaderToGenerate<<" * see includeOperators.cpp for more details"<<endl;
	fileHeaderToGenerate<<" *"<<endl;
	fileHeaderToGenerate<<" * This files contains the declarations for the operators of the enviroment."<<endl;
	fileHeaderToGenerate<<" * The enviroment use this declarations to use the operators."<<endl;
	fileHeaderToGenerate<<" *"<<endl;
	fileHeaderToGenerate<<"**/"<<endl;
	fileHeaderToGenerate<<endl;
	fileHeaderToGenerate<<"#ifndef ___ENVIROMENT_OPERATIONS_H__"<<endl;
	fileHeaderToGenerate<<"#define ___ENVIROMENT_OPERATIONS_H__"<<endl;
	fileHeaderToGenerate<<endl;
	fileHeaderToGenerate<<"#include \"cOperationIdentifier.h\""<<endl;
	fileHeaderToGenerate<<endl;

	//write the include for the headers
	bool bInitOperatorExists = false;
	
	
	for ( list<string>::iterator itrOperator = liOperatorPaths.begin();
			itrOperator != liOperatorPaths.end(); ){
		
		fileHeaderToGenerate<<"#include \""<< *itrOperator <<"\""<<endl;
		
		if ( (*itrOperator) == INIT_OPERATOR_HEADER ){
			bInitOperatorExists = true;
		}
		itrOperator++;
	}
	fileHeaderToGenerate<<endl;
	//open namespaces
	fileHeaderToGenerate<<"using namespace enviroment::fib;"<<endl;
	fileHeaderToGenerate<<"using namespace enviroment;"<<endl;

	//write define for init operator if it exists
	if ( bInitOperatorExists ){
		fileHeaderToGenerate<<"//an init operator exists"<<endl;
		fileHeaderToGenerate<<"#define INIT_OPERATOR"<<endl;
		fileHeaderToGenerate<<endl;
	}

	//write the declaration of the const operators
	fileHeaderToGenerate<<"namespace enviroment{"<<endl;
	fileHeaderToGenerate<<"namespace operations{"<<endl;
	fileHeaderToGenerate<<"	/*ignore this namespace; it contains an const instance for every"<<endl;
	fileHeaderToGenerate<<"	operations, so the arrayOperations can contain the instances and the"<<endl;
	fileHeaderToGenerate<<"	instances get destroyed at the execution end*/"<<endl;
	
	list<string> liOperationInstanceNames;
	for ( list<string>::iterator itrOperator = liOperatorFiles.begin();
			itrOperator != liOperatorFiles.end(); itrOperator++ ){
		
		string szOperatorName = (*itrOperator);
		//remove the ".h"
		szOperatorName.resize( szOperatorName.size() - 2 );
		//szOperationInstanceNames is szOperatorName wthiout the leading character
		string szOperationInstanceName( &((szOperatorName.c_str())[1]));
		liOperationInstanceNames.push_back( szOperationInstanceName );
		
		fileHeaderToGenerate<<"	const "<< szOperatorName <<" "<<
			szOperationInstanceName <<"( cOperationIdentifier( 0 ) );"<<endl;
	}
	
	fileHeaderToGenerate<<"};"<<endl;
	fileHeaderToGenerate<<"};"<<endl;
	fileHeaderToGenerate<<endl;

	//write arrayOperations
	fileHeaderToGenerate<<"//number of existing operations"<<endl;
//TODO
	fileHeaderToGenerate<<"//to define this variable const didn't work for the external linkage"<<endl;
	fileHeaderToGenerate<<"unsigned long ulNumberOfOperations = "<<
		liOperationInstanceNames.size()<<";"<<endl;
	fileHeaderToGenerate<<endl;
	fileHeaderToGenerate<<"/*array with pointers to the instances of existing operations;"<<endl;
	fileHeaderToGenerate<<"call the virtual createInstance() method of theas to create"<<endl;
	fileHeaderToGenerate<<"instances of operations you need*/"<<endl;
	fileHeaderToGenerate<<"const cOperation * arrayOperations[] = {"<<endl;
	for ( list<string>::iterator itrOperator = liOperationInstanceNames.begin();
			itrOperator != liOperationInstanceNames.end(); itrOperator++ ){
		
		if ( itrOperator != liOperationInstanceNames.begin() ){
			fileHeaderToGenerate<<","<<endl;
		}
		fileHeaderToGenerate<<"	& (enviroment::operations::"<< *itrOperator <<")";
		
	}
	
	fileHeaderToGenerate<<endl<<"};"<<endl;
	fileHeaderToGenerate<<endl;

	//write fileend
	fileHeaderToGenerate<<"#endif //___ENVIROMENT_OPERATIONS_H__"<<endl;
	fileHeaderToGenerate<<endl;
	
	fileHeaderToGenerate.close();

//write the to generate all operators file
	//open the file
	ofstream fileToGenerteAllOperatorsFilePath( szToGenerteAllOperatorsFilePath.c_str() );
	if ( ! fileToGenerteAllOperatorsFilePath.good() ){
		cerr<<"ERROR: Could not create the file "<< fileToGenerteAllOperatorsFilePath <<endl;
		return 1;
	}
	for ( list<string>::iterator itrOperator = liOperationInstanceNames.begin();
			itrOperator != liOperationInstanceNames.end(); itrOperator++ ){
		
		fileToGenerteAllOperatorsFilePath<< (*itrOperator) <<endl;
		
	}
	fileToGenerteAllOperatorsFilePath.close();

	return 0;
}


/**
 * This function reads the given file and returns a list with its lines.
 * The lines in the files should be the subfolders to check.
 * Empty line, lines wich begin with a blank ' ' or '#' will be ignored.
 *
 * @param szFilePath the path wher the folderlist to check is stored;
 * 	each folder to check is writen in a seperate line
 * @return a list with the folders to check
 */
list< string > loadFolderList( const string szFilePath ){
	
	list< string > liFolders;
	
	ifstream ifStream( szFilePath.c_str() );
	
	if ( ! ifStream.good() ){
		
		cerr<<"Error: Couldn't read the folder list "<< szFilePath <<endl;
		return liFolders;
	}
	char szBuffer[ 1024 ];
	
	while( ifStream.good() ){
	
		ifStream.getline( szBuffer, 1024 );
		string szFolder( szBuffer );
		if ( ( szFolder != "" ) && ( szFolder[ 0 ] != ' ' ) && ( szFolder[ 0 ] != '#' ) ){
			liFolders.push_back( szFolder );
		}
	}
	return liFolders;
}








