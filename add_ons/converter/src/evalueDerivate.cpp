/**
 * @file evalueDerivate
 * file name: evalueDerivate.cpp
 * @author Betti Oesterholz
 * @date 29.03.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This programm evalues the color derivate of an pictur and stores it as
 * an new pictur.
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
 * This programm evalues the color derivate of an pictur and stores it as
 * an new pictur.
 * An negativ difference will be stored as red and an positiv as green.
 * If the absolute difference value is to big (eg. 300 when 255 is the
 * maximum value), the absolute difference part higher as the maximum
 * will be stored as blue. If the value is to big to store as blue, it is
 * set to the max blue value.
 *
 *
 * call: evalueDerivate COLOR_COMPONENT DIRECTION [MULTIPLICATOR]
 * 			FILE_PICTURE FILE_OUTPUT_DERIVATE
 *
 * parameters:
 * 	COLOR_COMPONENT
 * 		the color component for which to evalue the derivate/difference
 * 		possible values are:
 * 			-r: evalue the derivate of the red component
 * 			-g: evalue the derivate of the green component
 * 			-b: evalue the derivate of the blue component
 * 			-s: evalue the derivate of the black component (if picture is in grayscale)
 * 		Standardvalue is: -r or -s
 * 	DIRECTION
 * 		the direction in which to evalue the derivate
 * 		possible values are:
 * 			-horizontal or -h: evalue the derivate in horizontal direction
 * 			-vertical or -v: evalue the derivate in vertical direction
 * 		Standardvalue is: -h
 * 	FILE_PICTURE
 * 		The path to the to load picture to evalue the derivate from
 * 	FILE_OUTPUT_DERIVATE
 * 		The name of the file wher the derivate of the picture sould be
 * 		stored to. The fileending will determine the output format.
 * 	MULTIPLICATOR: -mult=VALUE or -m=VALUE
 * 		VALUE: the multiplicator (float) value for the derivate values,
 * 			standard value is 1
 * 		Every evalueated difference will be multiplied with this value.
 * 		With this option you can make even small differences visible
 */
/*
History:
29.03.2011  Oesterholz  created
*/

#include "version.h"


#ifdef FEATURE_OWN_FREE_IMAGE_WARPER
	//no FreeImagePlus wraper for windows -> use own
	#include "fipImage.h"
#else //WINDOWS
	#include <FreeImagePlus.h>
#endif //WINDOWS


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>



using namespace std;


fipImage *evalueDerivate( const fipImage & orignalImage,
	bool  bDirection, unsigned char iColor, double dMultiplicator );


int main(int argc, char* argv[]){

	char * pFileWithOriginalData = NULL;
	/*filename wher to store the fib -object to, if NULL store in XML to
	the standartoutput*/
	char * pFileForStoringData = NULL;
	
	/*the color component for which to evalue the derivate
	0 = red; 1 = green; 2 = blue*/
	unsigned char uiColor = 0;
	//if the derivate should be evalued in horizontal direction
	bool bDirectionHorizontal = true;
	//the multiplicator for the difference values
	double dMultiplicator = 1.0;
	//read the parameters
	for ( int iActualParameter = 1; iActualParameter < argc;
			iActualParameter++ ){
		
		if ( strncmp ( argv[ iActualParameter ], "-r", 2 ) == 0 ){
			uiColor = 0;
			cout<<"Evaluing derivate for red color."<<endl;
		}else if ( strncmp ( argv[ iActualParameter ], "-g", 2 ) == 0 ){
			uiColor = 1;
			cout<<"Evaluing derivate for green color."<<endl;
		}else if ( strncmp ( argv[ iActualParameter ], "-b", 2 ) == 0 ){
			uiColor = 2;
			cout<<"Evaluing derivate for blue color."<<endl;
		}else if ( strncmp ( argv[ iActualParameter ], "-s", 2 ) == 0 ){
			uiColor = 0;
			cout<<"Evaluing derivate for black color (of gryscale image)."<<endl;
		}else if ( strncmp ( argv[ iActualParameter ], "-h", 2 ) == 0 ){
			bDirectionHorizontal = true;
			cout<<"Evaluing derivate in horizontal direction."<<endl;
			
		}else if ( strncmp ( argv[ iActualParameter ], "-v", 2 ) == 0 ){
			bDirectionHorizontal = false;
			cout<<"Evaluing derivate in vertical direction."<<endl;
			
		}else if ( ( strncmp ( argv[ iActualParameter ], "-mult=", 6 ) == 0 ) ){
			dMultiplicator = atof( &( argv[ iActualParameter ][ 6 ] )  );
			cout<<"The multiplication factor for the differencesis: "<<dMultiplicator<<endl;

		}else if ( ( strncmp ( argv[ iActualParameter ], "-m=", 3 ) == 0 ) ){
			dMultiplicator = atof( &( argv[ iActualParameter ][ 3 ] )  );
			cout<<"The multiplication factor for the differencesis: "<<dMultiplicator<<endl;

		}else if ( argv[ iActualParameter ][ 0 ] == '-' ){
			cerr<<"Unknown parameter: "<<argv[ iActualParameter ]<<endl;
			
		}else if ( pFileWithOriginalData == NULL ){
			//read original data file
			pFileWithOriginalData = argv[ iActualParameter ];
			cout<<"Name of pictur file to convert: "<<pFileWithOriginalData<<endl;
		}else if ( pFileForStoringData == NULL ){
			//get parameter filename wher to store the fib -object to
			pFileForStoringData = argv[ iActualParameter ];
			cout<<"Name of converted output fib pictur file: "<<pFileForStoringData<<endl;
		}else{
			cerr<<"unknown parameter: "<<argv[ iActualParameter ]<<endl;
		}
	}
	
	
	if ( ( pFileWithOriginalData == NULL ) || ( pFileForStoringData == NULL ) ){
		//no input file -> exit
		cout<<"Missing parameters"<<endl;
		cout<<endl;
		cout<<" call: evalueDerivate COLOR_COMPONENT DIRECTION [MULTIPLICATOR]"<<endl;
		cout<<"  			FILE_PICTURE FILE_OUTPUT_DERIVATE"<<endl;
		cout<<" "<<endl;
		cout<<"  parameters:"<<endl;
		cout<<"  	COLOR_COMPONENT"<<endl;
		cout<<"  		the color component for which to evalue the derivate/difference"<<endl;
		cout<<"  		possible values are:"<<endl;
		cout<<"  			-r: evalue the derivate of the red component"<<endl;
		cout<<"  			-g: evalue the derivate of the green component"<<endl;
		cout<<"  			-b: evalue the derivate of the blue component"<<endl;
		cout<<"  	DIRECTION"<<endl;
		cout<<"  		the direction in which to evalue the derivate"<<endl;
		cout<<"  		possible values are:"<<endl;
		cout<<"  			-horizontal or -h: evalue the derivate in horizontal direction"<<endl;
		cout<<"  			-vertical or -v: evalue the derivate in vertical direction"<<endl;
		cout<<"  	FILE_PICTURE"<<endl;
		cout<<"  		The path to the to load picture to evalue the derivate from"<<endl;
		cout<<"  	FILE_OUTPUT_DERIVATE"<<endl;
		cout<<"  		The name of the file wher the derivate of the picture sould be"<<endl;
		cout<<"  		stored to. The fileending will determine the output format."<<endl;
		cout<<"  	MULTIPLICATOR: -mult=VALUE or -m=VALUE"<<endl;
		cout<<"  		VALUE: the multiplicator (float) value for the derivate values,"<<endl;
		cout<<"  			standard value is 1"<<endl;
		cout<<"  		Every evalueated difference will be multiplied with this value."<<endl;
		cout<<"  		With this option you can make even small differences visible"<<endl;
		return 1;
	}
	//load original image
	fipImage orignalImage;
	bool bImagLoaded = orignalImage.load( pFileWithOriginalData );
	if ( ! bImagLoaded ){
		cerr<<"The image from file "<< pFileWithOriginalData <<" couldn't be loaded."<<endl;
		return 2;
	}
	
	//convert into a multimediaobject
	fipImage * pCovertedObject = evalueDerivate(
		orignalImage, bDirectionHorizontal, uiColor, dMultiplicator );
	
	
	if ( pCovertedObject ){
		//output the multimediaobject
		
		cout<<"Saving the converted multimediaobject to the file \""<<
			pFileForStoringData <<"\" . "<<endl;
		bool bObjectConverted = pCovertedObject->save( pFileForStoringData );
		if ( ! bObjectConverted ){
			cerr<<"Error: Couldn't save to the file \""<< pFileForStoringData <<"\" ." <<endl;
			if ( pCovertedObject ){
				delete pCovertedObject;
			}
			return 4;
		}
	}else{
		cerr<<"Error: Could not convert the data into a multimediaobject."<<endl;
		if ( pCovertedObject ){
			delete pCovertedObject;
		}
		return 3;
	}
	if ( pCovertedObject ){
		delete pCovertedObject;
	}
	return 0;
}



fipImage *evalueDerivate( const fipImage & multimediaObject,
		const bool bDirection, unsigned char iColor, const double dMultiplicator ){
	
	if ( 2 < iColor ){
		//no such color
		return NULL;
	}
	
	//create image for derivate picture
	DEBUG_OUT_L1( <<"evalueDerivate() started"<<endl; );
	const unsigned long ulWidth  = multimediaObject.getWidth();
	const unsigned long ulHeight = multimediaObject.getHeight();
	const bool bIsGrayscale = multimediaObject.isGrayscale();
	DEBUG_OUT_L1( <<"image size width="<< ulWidth <<" height="<< ulHeight <<" in "<<(bIsGrayscale?"grayscale":"color")<<endl; );
	
	const unsigned long ulWidthDerivate  = bDirection ? (ulWidth - 1) : ulWidth;
	const unsigned long ulHeightDerivate = bDirection ? ulHeight : (ulHeight - 1);
	
	fipImage * pFipDerivateImage = new fipImage( FIT_BITMAP, ulWidthDerivate, ulHeightDerivate, 24 );
	
	if ( bIsGrayscale ){
		if ( 0 < iColor ){
			//no such color
			return NULL;
		}
		pFipDerivateImage->convertToGrayscale();
	}//else RGB image

	//evalue derivate of picture
	RGBQUAD * colorRGBValue1 = new RGBQUAD();
	RGBQUAD * colorRGBValue2 = new RGBQUAD();
	RGBQUAD * colorRGBValueDerivate = new RGBQUAD();
	BYTE * indexValue = new BYTE();
	
	RGBQUAD * colorPalette = multimediaObject.getPalette();
	const unsigned long ulPaletteSize = (colorPalette == NULL) ?
		0 : multimediaObject.getPaletteSize();
	
	bool bColor;
	for ( unsigned long ulX = 0; ulX < ulWidthDerivate; ulX++ ){
		
		for ( unsigned long ulY = 0; ulY < ulHeightDerivate; ulY++ ){
			//evalue the color of the point
			
			DEBUG_OUT_L1( <<"evalue point X="<< ulX <<" Y="<< ulY <<endl );
			unsigned long ulX2 = bDirection ? (ulX + 1) : ulX;
			unsigned long ulY2 = bDirection ? ulY : (ulY + 1);
			
			if ( colorPalette != NULL ){
				//till 8 bit
				bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
				
				if ( ulPaletteSize <= *indexValue ){
					continue;//skip pixel
				}
				*colorRGBValue1 = colorPalette[ *indexValue ];
				
				bColor = multimediaObject.getPixelIndex( ulX2, ulY2, indexValue );
				
				if ( ulPaletteSize <= *indexValue ){
					continue;//skip pixel
				}
				*colorRGBValue2 = colorPalette[ *indexValue ];
			}else{
				bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue1 );
				bColor = multimediaObject.getPixelColor( ulX2, ulY2, colorRGBValue2 );
			}
			
			if ( bColor ){
				//evalue derivate pixel
				const int iDiffValue = (
					(iColor == 0) ? ( colorRGBValue2->rgbRed - colorRGBValue1->rgbRed ):
					(iColor == 1) ? ( colorRGBValue2->rgbGreen - colorRGBValue1->rgbGreen ):
					(iColor == 2) ? ( colorRGBValue2->rgbBlue - colorRGBValue1->rgbBlue ):
					0 ) * dMultiplicator;//error should not happen
				
				if ( 0 <= iDiffValue ){
					colorRGBValueDerivate->rgbRed   = 0;
					if ( iDiffValue < 256 ){
						colorRGBValueDerivate->rgbGreen = iDiffValue;
						colorRGBValueDerivate->rgbBlue  = 0;
					}else{
						colorRGBValueDerivate->rgbGreen = 255;
						if ( (256 + 255) < iDiffValue ){
							colorRGBValueDerivate->rgbBlue  = iDiffValue - 255;
						}else{
							colorRGBValueDerivate->rgbBlue  = 255;
						}
					}
				}else{
					colorRGBValueDerivate->rgbGreen = 0;
					const int iDiffValueAbs = -1 * iDiffValue;
					if ( iDiffValueAbs < 256 ){
						colorRGBValueDerivate->rgbRed = iDiffValueAbs;
						colorRGBValueDerivate->rgbBlue  = 0;
					}else{
						colorRGBValueDerivate->rgbRed = 255;
						if ( (256 + 255) < iDiffValueAbs ){
							colorRGBValueDerivate->rgbBlue  = iDiffValueAbs - 255;
						}else{
							colorRGBValueDerivate->rgbBlue  = 255;
						}
					}
				}
				
				//write derivate pixel
				pFipDerivateImage->setPixelColor( ulX, ulY, colorRGBValueDerivate );
			}
		}
	}
	
	return pFipDerivateImage;
}

















