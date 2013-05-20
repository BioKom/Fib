
//TODO check

/**
 * @file convertFromImageStructure
 * file name: convertFromImageStructure.cpp
 * @author Betti Oesterholz
 * @date 27.04.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This program is for converting image structure data into an image.
 *
 * Copyright (C) @c GPL3 2013 Betti Oesterholz
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
 * This program is for converting image structure data into an image.
 *
 *
 * call: convertFromImageStructure [PARAMETER] FILE_MULTIMEDIADATA FILE_OUTPUT
 *
 * parameters:
 * 	PATH_FIB_MULTIMEDIADATA
 * 		the path to the to load Fib multimedia data
 * 	FILE_OUTPUT
 * 		The name of the file where the converted multimedia data would be
 * 		stored to. The file ending will determine the output format.
 * 	PARAMETER
 * 		Parameters for converting into the Fib multimedia format
 * 	Possible parameters are:
 * 		-just_output_antialised or -justAA
 * 			Just output antialised image structures.
 * 		-just_output_not_antialised or -justNotAA
 * 			Just output not antialised image structures.
 * 		-background=COLOR or -bg=COLOR
 * 			Set the background property to COLOR.
 * 			Possible COLOR values are: white, black, red, green, blue
 * 		-first_to_output=NUMBER or -first=NUMBER
 * 			The NUMBER of the first image structure to output.
 * 			All image structures befor NUMBER will be ignored.
 * 		-last_to_output=NUMBER or -last=NUMBER
 * 			The NUMBER of the last image structure to output.
 * 			All image structures befor NUMBER will be ignored.
 *
 *
 * examples:
 * 	> convertFromImageStructure inputImageData.xml output.png
 * 	> convertFromImageStructure inputImageData.fib output.bmp
 */
/*
History:
27.04.2013  Oesterholz  created
*/

#include "version.h"
#include "nConvertFromFib.h"
#include "cFibElement.h"
#include "cRoot.h"
#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cTypeProperty.h"
#include "cImageStructure.h"

#include "cEvalueSimpleRGBA255Sec.h"

#include <string>
#include <iostream>
#include <fstream>


using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;
using namespace fib;
using namespace std;

void printShortHelp();





int main(int argc, char* argv[]){

	char * pFileWithOriginalData = NULL;
	/*filename wher to store the Fib object to, if NULL store in XML to
	the standartoutput*/
	char * pFileForStoringData = NULL;
	
	if ( argc < 3 ){
		//no input file -> exit
		printShortHelp();
		return 1;
	}
	cout<<endl;
	//just output antialised image structures
	bool bJustOutputAntialised = false;
	//just output not antialised image structures
	bool bJustOutputNotAntialised = false;
	
	//background property to use
	bool bUseBackgroundColor = false;
	cVectorProperty vecBackground( cTypeProperty::COLOR_RGB );
	
	//The NUMBER of the first image structure to output.
	unsigned long ulFirst = 0;
	//The NUMBER of the last image structure to output.
	unsigned long ulLast = 0;

	//read parameter
	for ( int iActualParameter = 1; iActualParameter < argc;
			iActualParameter++ ){
		
		if ( ( strncmp( argv[ iActualParameter ], "-just_output_antialised", 23 ) == 0 ) ||
				( strncmp( argv[ iActualParameter ], "-justAA", 7 ) == 0 ) ){
			bJustOutputAntialised = true;
			cout<<"Just output antialised image structures."<<endl;
			
		}else if ( ( strncmp( argv[ iActualParameter ], "-just_output_not_antialised", 27 ) == 0 ) ||
				( strncmp( argv[ iActualParameter ], "-justNotAA", 10 ) == 0 ) ){
			bJustOutputNotAntialised = true;
			cout<<"Just output not antialised image structures."<<endl;
			
		}else if ( ( strncmp( argv[ iActualParameter ], "-background=", 12 ) == 0 ) ||
				( strncmp( argv[ iActualParameter ], "-bg=", 4 ) == 0 ) ){
			
			char * pColorName = NULL;
			if ( strncmp( argv[ iActualParameter ], "-background", 11 ) == 0 ){
				pColorName = &(argv[ iActualParameter ][ 12 ]);
			}else if ( strncmp( argv[ iActualParameter ], "-bg=", 4 ) == 0 ){
				pColorName = &(argv[ iActualParameter ][ 4 ]);
			}
			if ( strncmp( pColorName, "white", 5 ) == 0 ){
				bUseBackgroundColor = true;
				vecBackground.setValue( 1, 255 );
				vecBackground.setValue( 2, 255 );
				vecBackground.setValue( 3, 255 );
				cout<<"The background color was set to white."<<endl;
			}else if ( strncmp( pColorName, "black", 5 ) == 0 ){
				bUseBackgroundColor = true;
				vecBackground.setValue( 1, 0 );
				vecBackground.setValue( 2, 0 );
				vecBackground.setValue( 3, 0 );
				cout<<"The background color was set to black."<<endl;
			}else if ( strncmp( pColorName, "red", 3 ) == 0 ){
				bUseBackgroundColor = true;
				vecBackground.setValue( 1, 255 );
				vecBackground.setValue( 2, 0 );
				vecBackground.setValue( 3, 0 );
				cout<<"The background color was set to red."<<endl;
			}else if ( strncmp( pColorName, "green", 3 ) == 0 ){
				bUseBackgroundColor = true;
				vecBackground.setValue( 1, 0 );
				vecBackground.setValue( 2, 255 );
				vecBackground.setValue( 3, 0 );
				cout<<"The background color was set to green."<<endl;
			}else if ( strncmp( pColorName, "blue", 4 ) == 0 ){
				bUseBackgroundColor = true;
				vecBackground.setValue( 1, 0 );
				vecBackground.setValue( 2, 0 );
				vecBackground.setValue( 3, 255 );
				cout<<"The background color was set to blue."<<endl;
			}//else unknown color
			
		}else if ( strncmp( argv[ iActualParameter ], "-first_to_output=", 17 ) == 0 ){
			ulFirst = atol( &(argv[ iActualParameter ][ 17 ]) );
			cout<<"Output all image structures from the "<<ulFirst<<"'th."<<endl;
			
		}else if ( strncmp( argv[ iActualParameter ], "-first=", 7 ) == 0 ){
			ulFirst = atol( &(argv[ iActualParameter ][ 7 ]) );
			cout<<"Output all image structures from the "<<ulFirst<<"'th."<<endl;
			
		}else if ( strncmp( argv[ iActualParameter ], "-last_to_output=", 16 ) == 0 ){
			ulLast = atol( &(argv[ iActualParameter ][ 16 ]) );
			cout<<"Output all image structures till the "<<ulLast<<"'th."<<endl;
			
		}else if ( strncmp( argv[ iActualParameter ], "-last=", 6 ) == 0 ){
			ulLast = atol( &(argv[ iActualParameter ][ 6 ]) );
			cout<<"Output all image structures till the "<<ulLast<<"'th."<<endl;
			
			
		}else if ( pFileWithOriginalData == NULL ){
			//read original data file
			pFileWithOriginalData = argv[ iActualParameter ];
			cout<<"Name of Fib object file to convert: "<<pFileWithOriginalData<<endl;
		}else if ( pFileForStoringData == NULL ){
			//get parameter filename where to store the Fib object to
			pFileForStoringData = argv[ iActualParameter ];
			cout<<"Name of converted output picture file: "<<pFileForStoringData<<endl;
		}else{
			cerr<<"Unknown parameter: "<<argv[ iActualParameter ]<<endl;
		}
	}
	
	if ( ( pFileWithOriginalData == NULL ) || ( pFileForStoringData == NULL ) ){
		//no input file -> exit
		printShortHelp();
		return 1;
	}
	
	
	//load the multimedia data
//	FREE_IMAGE_FORMAT imageFormat = fipImage::identifyFIF( pFileWithOriginalData );
	//evalue image size
	doubleFib dMaxX = 0;
	doubleFib dMaxY = 0;
	//restore image data
	ifstream inFile( pFileWithOriginalData );
	intFib outStatus = 0;
	
	if ( ! inFile.good() ){
		cerr<<"Error: Can't open file."<<endl;
		return 1;
	}
	
	unsigned long ulNumberOfActualImageStructure = 0;
	unsigned long ulNumberOfRestoredImageStructure = 0;
	while ( ! inFile.eof() ){
		ulNumberOfActualImageStructure++;
		if ( ( ulLast != 0 ) && ( ulLast < ulNumberOfActualImageStructure ) ){
			//don't restore more image structures
			break;
		}
		//cout<<"Restoring image structur number "<<ulNumberOfActualImageStructure<<endl<<flush;
		
		outStatus = 0;
		cImageStructure * pRestoredImageData = cImageStructure::restoreXml(
			inFile , &outStatus );
		
		if ( pRestoredImageData != NULL ){
			ulNumberOfRestoredImageStructure++;
			if ( ulFirst <= ulNumberOfActualImageStructure ){
				//evalue size of the image to create
				const set<cVectorPosition> & setStructurPoints =
					pRestoredImageData->getStructurePointsConst();
				for ( set<cVectorPosition>::const_iterator
						itrPoint = setStructurPoints.begin();
						itrPoint != setStructurPoints.end(); itrPoint++ ){
					
					dMaxX = std::max( dMaxX, itrPoint->getValue( 1 ) );
					dMaxY = std::max( dMaxY, itrPoint->getValue( 2 ) );
				}
			}
			delete pRestoredImageData;
		}
		
		/*if ( outStatus == 0 ){
			cout<<"Restoring image structure from the file \""<<
				pFileWithOriginalData <<"\" successfull."<<endl<<flush;
		}else*/
		if ( 0 < outStatus ){
			cerr<<"Warning: Restoring "<<ulNumberOfActualImageStructure<<
				"'th image structure from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl<<flush;
		}else if ( ( outStatus < 0 ) && ( ! inFile.eof() ) ){
			cerr<<"Error: Restoring "<<ulNumberOfActualImageStructure<<
				"'th image structure from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl<<flush;
		}
	}
	inFile.close();
	
	cout<<"Restoring image structure data from the file \""<<
		pFileWithOriginalData <<"\" done: "<<ulNumberOfRestoredImageStructure<<
		" structures restored (till image structure "<<
		ulNumberOfRestoredImageStructure<<")."<<endl<<flush;
	if ( ulNumberOfRestoredImageStructure == 0 ){
		cerr<<"Error: No image structures restored."<<endl;
		return 1;
	}
	unsigned int uiMaxX = dMaxX + 16;
	unsigned int uiMaxY = dMaxY + 16;
	cout<<"Image width "<<uiMaxX<<" and hight "<<uiMaxY<<
		" (evalued width "<<dMaxX<<" and hight "<<dMaxY<<")."<<endl<<flush;
	const unsigned int uiMaxPositionValue = 10000;
	if ( uiMaxPositionValue < uiMaxX ){
		cerr<<"Error: width "<<uiMaxX<<" to great reducing to "<<uiMaxPositionValue<<endl;
		uiMaxX = uiMaxPositionValue;
	}
	if ( uiMaxPositionValue < uiMaxY ){
		cerr<<"Error: hight "<<uiMaxY<<" to great reducing to "<<uiMaxPositionValue<<endl;
		uiMaxY = uiMaxPositionValue;
	}
	
	//evalue image data
	cEvalueSimpleRGBA255Sec evalueSimple( uiMaxX, uiMaxY );
	
	if ( bUseBackgroundColor ){
		//set background property
		cVectorPosition vecPositionBackground( 0 );
		list<cVectorProperty> liVecProperties;
		liVecProperties.push_back( vecBackground );
		
		evalueSimple.setPoint( vecPositionBackground, liVecProperties );
	}
	
	//restore image data
	ifstream inFileToEvalue( pFileWithOriginalData );
	
	if ( ! inFileToEvalue.good() ){
		cerr<<"Error: Can't open file."<<endl;
		return 1;
	}
	
	ulNumberOfActualImageStructure = 0;
	while ( ! inFileToEvalue.eof() ){
		ulNumberOfActualImageStructure++;
		if ( ( ulLast != 0 ) && ( ulLast < ulNumberOfActualImageStructure ) ){
			//don't restore more image structures
			break;
		}
		outStatus = 0;
		cImageStructure * pRestoredImageData = cImageStructure::restoreXml(
			inFileToEvalue , &outStatus );
		
		if ( pRestoredImageData != NULL ){
			if ( ulFirst <= ulNumberOfActualImageStructure ){
				
				if ( ( ! bJustOutputAntialised ) && ( ! bJustOutputNotAntialised ) ){
					
					pRestoredImageData->evalue( evalueSimple );
				}else if ( bJustOutputAntialised || bJustOutputNotAntialised ){
					
					if ( ( bJustOutputAntialised == pRestoredImageData->isAntialised() ) ||
							( bJustOutputNotAntialised == ( ! pRestoredImageData->isAntialised() ) ) ){
						
						pRestoredImageData->evalue( evalueSimple );
					}
				}
			}
			delete pRestoredImageData;
		}
		
		/*if ( outStatus == 0 ){
			cout<<"Restoring image structure from the file \""<<
				pFileWithOriginalData <<"\" successfull."<<endl<<flush;
		}else*/
		if ( 0 < outStatus ){
			cerr<<"Warning: Restoring "<<ulNumberOfActualImageStructure<<
				"'th image structure from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl<<flush;
		}else if ( ( outStatus < 0 ) && ( ! inFileToEvalue.eof() ) ){
			cerr<<"Error: Restoring "<<ulNumberOfActualImageStructure<<
				"'th image structure from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl<<flush;
		}
	}
	inFileToEvalue.close();
	cout<<"Image data evalued"<<endl<<flush;
	
	//convert into a multimedia object
	fipImage * pCovertedObject = evalueSimple.convertToFipImage();
	cout<<"storing image data"<<endl<<flush;
	
	int iReturnValue = 0;
	if ( pCovertedObject ){
		//output the multimedia object
		
		cout<<"Saving the converted multimedia object to the file \""<<
			pFileForStoringData <<"\" . "<<endl;
		const bool bObjectConverted = pCovertedObject->save( pFileForStoringData );
		if ( ! bObjectConverted ){
			cerr<<"Error: Couldn't save to the file \""<< pFileForStoringData <<"\" ." <<endl;
			iReturnValue = 4;
		}
		delete pCovertedObject;
	}else{
		cerr<<"Error: Could not convert the data into a multimedia object."<<endl;
		iReturnValue = 3;
	}
	
	return iReturnValue;
}


/**
 * Print short help information.
 */
void printShortHelp(){
	
	cout<<"No input file and output file specified."<<endl;
	cout<<endl;
	cout<<" This program is for converting image structure data into an image."<<endl;
	cout<<""<<endl;
	cout<<""<<endl;
	cout<<" call: convertFromImageStructure FILE_MULTIMEDIADATA FILE_OUTPUT [PARAMETER]"<<endl;
	cout<<""<<endl;
	cout<<" parameters:"<<endl;
	cout<<" 	PATH_FIB_MULTIMEDIADATA"<<endl;
	cout<<" 		the path to the to load Fib multimedia data"<<endl;
	cout<<" 	FILE_OUTPUT"<<endl;
	cout<<" 		The name of the file where the converted multimedia data would be"<<endl;
	cout<<" 		stored to. The file ending will determine the output format."<<endl;
 	cout<<""<<endl;
	cout<<""<<endl;
	cout<<" examples:"<<endl;
	cout<<" 	> convertFromImageStructure inputImageData.xml output.png"<<endl;
	cout<<" 	> convertFromImageStructure inputImageData.fib output.bmp"<<endl;
	cout<<endl;
}






