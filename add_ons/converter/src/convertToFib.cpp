/**
 * @file convertToFib
 * file name: convertToFib.cpp
 * @author Betti Oesterholz
 * @date 24.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This program is for converting multimedia objects in non fib
 * multimedia formats into Fib objects.
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
 * This program is for converting multimedia objects in non Fib
 * multimedia formats into Fib objects.
 *
 *
 * call: convertToFib [PARAMETER] FILE_MULTIMEDIADATA [FILE_OUTPUT]
 * or call: convertToFib -h[elp]
 * 	for help
 *
 * parameters:
 * 	PATH_MULTIMEDIADATA
 * 		The path to the to load non Fib multimedia data
 * 	FILE_OUTPUT
 * 		The name of the file where the Fib multimedia data would be
 * 		stored to. If the file ending is ".xml" the data will be written
 * 		in the Fib Xml format. If no parameter FILE_OUTPUT is given
 * 		the Fib object will be stored in the Fib Xml format to the
 * 		standard output.
 * 	PARAMETER
 * 		Parameters for converting into the Fib multimedia format
 * 	Possible parameters are:
 * 		-mode=VALUE
 * 			possible VALUE: simple, compress or reduce
 * 			standard VALUE: compress
 * 			(instead of the values, just the first letter of the values
 * 			can be used)
 * 			the compression mode
 * 			if simple: the picture will be converted directly, without
 * 				trying to reduce the data
 * 			if compress: the multimedia data will be compressed, by
 * 				building Fib under objects for areas with the same color
 * 				and evaluating the background color (see option "-bg=")
 * 			if reduce: the multimedia data will be compressed with
 * 				reducing the data (higher compression rate as VALUE
 * 				"compress"), by building Fib under objects for areas with
 * 				similar color and evaluating the background color;
 * 				some pixels won't have the correct color (see option "-bg="
 * 				in combination with "-max_area_dif")
 * 				possible options: 
 * 					-max_area_diff=VALUE
 * 						VALUE: a positive integer value
 * 						the maximal difference of color values in an area (as
 * 						the sum of the color vector element distances)
 * 					-min_points=VALUE1 and -max_diff=VALUE2
 * 						VALUE1 and VALUE2: positive integer value
 * 						if an area with less than VALUE1 points exists and
 * 						it layers beside an area with a color, which has a less
 * 						difference as VALUE2 to the color of the first area,
 * 						both areas will be combined with the color of the
 * 						second area (if the first area has more than one
 * 						area as a neighbor, which fulfill VALUE2, the one with
 * 						the minimum color distance is taken);
 * 						the value of max_diff should be bigger than that of
 * 						max_area_diff
 * 					-addNeighbors or -addN
 * 						add to the areas their neighbors and remove not needed areas;
 * 						basicly this is an anti anti-aliasing
 * 					-reduce_function_domains or -rfd
 * 						reduce the bits to store the function (values)
 * 					-replace_areas_with_points or -rpawp
 * 						replace areas, which need more bits to store than
 * 						their points, with their points
 * 					-min_point_for_area=VALUE or -min_pfa=VALUE
 * 						VALUE: the minimal number of points an area should
 * 						have, to create an area object for it;
 * 						if 0 the standard value will be taken
 * 					-min_point_for_neighbor_area= or -min_pfna=
 * 						all neighbor areas with less than this number of
 * 						points, will be subsumed by the area
 * 					-not_correct_missing_points or -ncmp
 * 						don't correct points, which are missing in the created area Fib objects
 * 					-max_error=VALUE
 * 						VALUE: a positive integer value
 * 						the maximal error for the area border polynomials to find
 * 		-bg=VALUE
 * 			possible VALUE: yes or no
 * 			standard VALUE: yes
 * 			if an background color should be set, if non exists;
 * 			if no: no background color will be evaluated, if non exists;
 * 		-correct-points or -cp
 * 			if wrong points should be corrected, in the last compressing step
 * 		-reduce_lists or -rl
 * 			reduce the number of lists in the Fib object
 * 		-minColDist=VALUE
 * 			VALUE: a positive integer value
 * 			The minimal color distance, to which reduce the original picture data.
 * 		-expColDistFactor=VALUE
 * 			VALUE: an floating point value, should be greater 1 (else: the
 * 				functionality is not useful)
 * 			The factor for reducing the color exponentially in the original picture data.
 * 			(This is mainly for noise reduction.)
 * 		-minFreeMemPc=VALUE (Unix only)
 * 			VALUE: an floating point value, should be between (inclusive) 0
 * 				(else: is set to 0) and 100 (else: is set to 100)
 * 			The minimum per cent of free memory from all memory.
 * 		-storeConvertedFibObjectTo=IMAGE_FILE_ENDING or -sFibTo=IMAGE_FILE_ENDING
 * 			IMAGE_FILE_ENDING: the ending for the image file to store the
 * 				created Fib object to (eg. bmp or png)
 * 			If this parameter is given the created Fib object will be
 * 			stored to an non fib image file. The type of the image file is
 * 			given by the specified IMAGE_FILE_ENDING.
 *
 * examples:
 * 	> convertToFib input.png outputFib.xml
 * 	> convertToFib input.bmp outputFib.fib
 * 	> convertToFib -mode=r -rl -max_area_diff=4 -min_points=3 -max_diff=64 -rfd -rpawp input.jpg outputFib.fib
 */
/*
History:
24.02.2010  Oesterholz  created
23.08.2010  Oesterholz  output of call info added
10.03.2011  Oesterholz  modifications to reduce the Fib data for
	compressed storege in fib
10.03.2011  Oesterholz  parameter and functionality for -minFreeMemPc added
11.03.2012  Oesterholz  parameter help added
*/

#include "version.h"
#include "nConvertToFib.h"
#include "nConvertFromFib.h"
#include "cColorDistance.h"
#include "cFibElement.h"

#include "nBalanceLists.h"
#include "nCluster.h"
#include "cClusterFunArea.h"
#include "cClusterFunExp.h"


#ifdef FEATURE_OWN_FREE_IMAGE_WARPER
	//no FreeImagePlus wraper for windows -> use own
	#include "fipImage.h"
#else //WINDOWS
	#include <FreeImagePlus.h>
#endif //WINDOWS


#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>


using namespace fib;
using namespace std;
using namespace fib::algorithms;


//comment in for debugging
//#define DEBUG

#ifndef WINDOWS
//linux only

#include <pthread.h>
#include <sys/sysinfo.h>

/**
 * This function stops the execution of the program if not enough free
 * memory is left.
 *
 * @param pMinFreeMemPc a pointer to a double with the minimum per cent of
 * 	free memory from all memory
 */
static void * stopMemFull( void * pMinFreeMemPc ){
	
	double dMinFreeMem = (*((double*)(pMinFreeMemPc))) / 100.0;
	cout<<endl<<"Minimum per cent of free memory from all memory: "<<
		(dMinFreeMem * 100.0)<<endl;
	
	struct sysinfo sysInfo;
	struct timespec remainingTime;
	struct timespec timeToWait;
	
	while ( true ){
		//wait a little
		timeToWait.tv_sec  = 0;
		timeToWait.tv_nsec = 100000000L; //= 100 ms
		
		nanosleep( &timeToWait, &remainingTime );
		
		//check memory
		sysinfo( &sysInfo );
		
		if( sysInfo.freeram < ((double)(sysInfo.totalram)) * dMinFreeMem ){
			//less than dMinFreeMem free ram
			cout<<endl<<"not enougth memory: ending program"<<endl;
			cout<<"   freeram="<<sysInfo.freeram<<
				"  totalram=" <<sysInfo.totalram<<
				"  freeram/totalram="<<( ((double)sysInfo.freeram) / ((double)sysInfo.totalram) )<<endl;
			exit( 1 );
		}
	}
}

#endif //not WINDOWS


void printDetailedHelp();


int main(int argc, char* argv[]){

	if ( ( argc == 2 ) && ( argv[ 1 ][ 0 ] == '-' ) && ( argv[ 1 ][ 1 ] == 'h' ) ){
		cout<<"Printing parameter details."<<endl;
		cout<<endl;
		
		printDetailedHelp();
		
		return 0;
	}else if ( argc < 2 ){
		//no input file -> exit
		cout<<"No inputfile with the originalmultimedia data given."<<endl;
		cout<<endl;
		cout<<"This program is for converting multimedia objects in non Fib"<<endl;
		cout<<"multimedia formats into Fib objects."<<endl;
		cout<<endl;
		cout<<" call: convertToFib [PARAMETER] FILE_MULTIMEDIADATA [FILE_OUTPUT]"<<endl;
		cout<<" or call for help: convertToFib -h[elp]"<<endl;
		cout<<endl;
		cout<<" parameters:"<<endl;
		cout<<" 	PARAMETER"<<endl;
		cout<<" 		The parameter to convert the multimedia data."<<endl;
		cout<<" 		Run \">convertToFib -help\" for more info"<<endl;
		cout<<" 	PATH_MULTIMEDIADATA"<<endl;
		cout<<" 		The path to the to load non Fib multimedia data."<<endl;
		cout<<" 	FILE_OUTPUT"<<endl;
		cout<<" 		The name of the file where the Fib multimedia data would be"<<endl;
		cout<<" 		stored to. If the file ending is \".xml\" the data will be written"<<endl;
		cout<<" 		in the Fib Xml format. If no parameter FILE_OUTPUT is given"<<endl;
		cout<<" 		the Fib object will be stored in the Fib Xml format to the"<<endl;
		cout<<" 		standard output."<<endl;
		return 1;
	}
	
	char * pFileWithOriginalData = NULL;
	/*filename where to store the Fib object to, if NULL store in XML to
	the standartoutput*/
	char * pFileForStoringData = NULL;
	
	enum typeModus { SIMPLE, COMPRESS, REDUCE };

	typeModus mode = COMPRESS;
	//parameters for the convert and reduce mode
	bool bEvalueBackground = true;
	//if wrong points should be corrected, in the last compressing step
	bool bCorrectPoints = false;
	//if the number of lists in the Fib object will be reduced
	bool bReduceList = false;
	//add to the areas their neighbors and remove not needed areas
	bool bAddNeighbours = false;
	//correct points, which are missing in the created area Fib objects
	bool bCorrectMissingPoints = true;
	//reduce the bits to store the function (values)
	bool bReduceFunctionDomains = false;
	//replace areas, which need more bits to store than their points, with their points
	bool bReplaceAreasWithPoints = true;
	//the minimal number of points an area should have, to create an area object for it
	unsigned int uiMinPointsForArea = 0;
	//parameters for the reduce mode
	unsigned long ulMaxAreaDiff = 2;
	unsigned long ulMinPoints = 1;
	unsigned long ulMaxDiff = 16;
	double maxError = 0;
	/*all neighbor areas with less than this number of points, will be
	subsumed by the area*/
	unsigned int uiMinPointsNeighbourAreas = 0;
	//parameters for reducing the colors in the original image
	unsigned int uiMinColorDistance = 0;
	double dExpColorDistanceFactor = 0.0;
	//the minimum per cent of free memory from all memory
	double dMinFreeMemPc = 0.0;
	//the ending of the image to store the converted Fib object to
	char * szStoreConvertedImage = NULL;
	
	//read parameter
	for ( int iActualParameter = 1; iActualParameter < argc;
			iActualParameter++ ){
		
		if ( strncmp( argv[ iActualParameter ], "-mode=", 6 ) == 0 ){
			if ( argv[ iActualParameter ][ 6 ] == 's' ){
				mode = SIMPLE;
				cout<<"Converting in simple mode."<<endl;
			}else if ( argv[ iActualParameter ][ 6 ] == 'c' ){
				mode = COMPRESS;
				cout<<"Converting in compressed mode."<<endl;
			}else if ( argv[ iActualParameter ][ 6 ] == 'r' ){
				mode = REDUCE;
				cout<<"Converting in reduced mode."<<endl;
			}else{
				cerr<<"unknown mode: "<<argv[ iActualParameter ]<<endl;
			}
		}else if ( strncmp( argv[ iActualParameter ], "-bg=", 4 ) == 0 ){
			if ( argv[ iActualParameter ][ 4 ] == 'n' ){
				bEvalueBackground = false;
				cout<<"Don't evaluating background."<<endl;
			}else if ( argv[ iActualParameter ][ 4 ] == 'y' ){
				bEvalueBackground = true;
				cout<<"Evaluing background."<<endl;
			}else {
				cerr<<"Unknown background mode: "<<argv[ iActualParameter ]<<endl;
			}
		}else if ( ( strncmp( argv[ iActualParameter ], "-cp", 3 ) == 0 ) ||
				( strncmp( argv[ iActualParameter ], "-correct-points", 15 ) == 0 ) ){
			bCorrectPoints = true;
			cout<<"Wrong points will be corrected."<<endl;
			
		}else if ( ( strncmp( argv[ iActualParameter ], "-rl", 3 ) == 0 ) ||
				( strncmp( argv[ iActualParameter ], "-reduce_lists", 13 ) == 0 ) ){
			bReduceList = true;
			cout<<"The number of lists in the Fib object will be reduced."<<endl;
			
		}else if ( ( strncmp( argv[ iActualParameter ], "-addN", 5 ) == 0 ) ||
				( strncmp( argv[ iActualParameter ], "-addNeighbors", 13 ) == 0 ) ){
			bAddNeighbours = true;
			cout<<"Add to the areas their neighbors and remove not needed areas."<<endl;
			
		}else if ( ( strncmp( argv[ iActualParameter ], "-ncmp", 5 ) == 0 ) ||
				( strncmp( argv[ iActualParameter ], "-not_correct_missing_points", 27 ) == 0 ) ){
			bCorrectMissingPoints = true;
			cout<<"Don't correct points, which are missing in the created area Fib objects."<<endl;
			
		}else if ( ( strncmp( argv[ iActualParameter ], "-rfd", 4 ) == 0 ) ||
				( strncmp( argv[ iActualParameter ], "-reduce_function_domains", 24 ) == 0 ) ){
			bReduceFunctionDomains = true;
			cout<<"Reduce the bits to store the function (values)."<<endl;
			
		}else if ( ( strncmp( argv[ iActualParameter ], "-rpawp", 6 ) == 0 ) ||
				( strncmp( argv[ iActualParameter ], "-replace_areas_with_points", 26 ) == 0 ) ){
			bReplaceAreasWithPoints = true;
			cout<<"Replace areas, which need more bits to store than their points, with their points."<<endl;
			
		}else if ( strncmp( argv[ iActualParameter ], "-max_area_diff=", 15 ) == 0 ){
			ulMaxAreaDiff = atol( &( argv[ iActualParameter ][ 15 ] )  );
			cout<<"The maximal difference of color values in an areas is: "<<ulMaxAreaDiff<<endl;
			
		}else if ( strncmp( argv[ iActualParameter ], "-min_points=", 12 ) == 0 ){
			ulMinPoints = atol( &( argv[ iActualParameter ][ 12 ] )  );
			cout<<"The minimum number of points for an area is: "<<ulMinPoints<<endl;
			
		}else if ( strncmp( argv[ iActualParameter ], "-max_diff=", 10 ) == 0 ){
			ulMaxDiff = atol( &( argv[ iActualParameter ][ 10 ] )  );
			cout<<"The maximal difference of color values for not areas points: "<<ulMaxDiff<<endl;
		
		}else if ( ( strncmp( argv[ iActualParameter ], "-min_point_for_area=", 20 ) == 0 ) ){
			uiMinPointsForArea = atol( &( argv[ iActualParameter ][ 20 ] )  );
			cout<<"The minimal number of points an area should have, to create an area object for it: "<<uiMinPointsForArea<<endl;
		
		}else if ( ( strncmp( argv[ iActualParameter ], "-min_pfa=", 9 ) == 0 ) ){
			uiMinPointsForArea = atol( &( argv[ iActualParameter ][ 9 ] )  );
			cout<<"The minimal number of points an area should have, to create an area object for it: "<<uiMinPointsForArea<<endl;
		
		
		}else if ( ( strncmp( argv[ iActualParameter ], "-min_point_for_neighbor_area=", 29 ) == 0 ) ){
			uiMinPointsNeighbourAreas = atol( &( argv[ iActualParameter ][ 30 ] )  );
			cout<<"The minimal number of points an neighbor area should have: "<<uiMinPointsNeighbourAreas<<endl;
		
		}else if ( ( strncmp( argv[ iActualParameter ], "-min_pfna=", 10 ) == 0 ) ){
			uiMinPointsNeighbourAreas = atol( &( argv[ iActualParameter ][ 10 ] )  );
			cout<<"The minimal number of points an neighbor area should have: "<<uiMinPointsNeighbourAreas<<endl;
		
		}else if ( ( strncmp( argv[ iActualParameter ], "-max_error=", 11 ) == 0 ) ){
			maxError = atol( &( argv[ iActualParameter ][ 11 ] )  );
			cout<<"The maximal error for the area border polynomials to find: "<<maxError<<endl;

		}else if ( ( strncmp( argv[ iActualParameter ], "-minColDist=", 12 ) == 0 ) ){
			uiMinColorDistance = atol( &( argv[ iActualParameter ][ 12 ] )  );
			cout<<"The minimal color distance, to which reduce the original picture data: "<<uiMinColorDistance<<endl;
		
		}else if ( ( strncmp( argv[ iActualParameter ], "-expColDistFactor=", 18 ) == 0 ) ){
			dExpColorDistanceFactor = atof( &( argv[ iActualParameter ][ 18 ] )  );
			cout<<"The factor for reducing the color exponentially in the original picture data: "<<dExpColorDistanceFactor<<endl;

		}else if ( ( strncmp( argv[ iActualParameter ], "-minFreeMemPc=", 14 ) == 0 ) ){
			dMinFreeMemPc = atof( &( argv[ iActualParameter ][ 14 ] )  );
			
			if ( dMinFreeMemPc <= 0.0 ){
				dMinFreeMemPc = 0.0;
			}
			if ( 100.0 < dMinFreeMemPc ){
				dMinFreeMemPc = 100.0;
			}
			cout<<"The minimum per cent of free memory from all memory: "<<dMinFreeMemPc<<endl;

		}else if ( ( strncmp( argv[ iActualParameter ], "-storeConvertedFibObjectTo=", 27 ) == 0 ) ){
			szStoreConvertedImage = &( argv[ iActualParameter ][ 27 ] );
			cout<<"The ending of the (normal) image file to store the converted Fib object to: "<<szStoreConvertedImage<<endl;

		}else if ( ( strncmp( argv[ iActualParameter ], "-sFibTo=", 8 ) == 0 ) ){
			szStoreConvertedImage = &( argv[ iActualParameter ][ 8 ] );
			cout<<"The ending of the (normal) image file to store the converted Fib object to: "<<szStoreConvertedImage<<endl;

		}else if ( argv[ iActualParameter ][ 0 ] == '-' ){
			cerr<<"Unknown parameter: "<<argv[ iActualParameter ]<<endl;
			
		}else if ( pFileWithOriginalData == NULL ){
			//read original data file
			pFileWithOriginalData = argv[ iActualParameter ];
			cout<<"Name of picture file to convert: "<<pFileWithOriginalData<<endl;
		}else if ( pFileForStoringData == NULL ){
			//get parameter filename where to store the Fib object to
			pFileForStoringData = argv[ iActualParameter ];
			cout<<"Name of converted output Fib picture file: "<<pFileForStoringData<<endl;
		}else{
			cerr<<"Unknown parameter: "<<argv[ iActualParameter ]<<endl;
		}
	}
	
#ifndef WINDOWS
	//linux only
	pthread_t threadStop;
	if ( 0.0 < dMinFreeMemPc ){
		//starting stop tread
		pthread_create( &threadStop, NULL, &stopMemFull, &dMinFreeMemPc );
		//cout<<"pthread_create returned for stop tread: "<< iReturn <<endl;
	}
#endif //not WINDOWS

	//load the multimedia data
//	FREE_IMAGE_FORMAT imageFormat = fipImage::identifyFIF( pFileWithOriginalData );
	
	fipImage orignalImage;
	bool bImagLoaded = orignalImage.load( pFileWithOriginalData );
	if ( ! bImagLoaded ){
		cerr<<"The image from file "<< pFileWithOriginalData <<" couldn't be loaded."<<endl;
#ifndef WINDOWS
		//linux only
		if ( 0.0 < dMinFreeMemPc ){
			//stop stop tread
			pthread_cancel( threadStop );
		}
#endif //not WINDOWS
		return 2;
	}
	
	//reduce colors
	if ( ( uiMinColorDistance != 0 ) ||
			( dExpColorDistanceFactor != 0.0 ) ){
		
		const map< vector< unsigned int >, unsigned long > mapColorCounts =
			nConvertToFib::countColors( orignalImage );
#ifdef DEBUG
		cout<<endl<<"Color counts befor reducing (number of colors="<<mapColorCounts.size()<<"):"<<endl;
		for (  map< vector< unsigned int >, unsigned long >::const_iterator
				itrColor = mapColorCounts.begin();
				itrColor != mapColorCounts.end(); itrColor++ ){
			
			cout<<"#col(";
			for ( vector< unsigned int >::const_iterator
					itrColElement = itrColor->first.begin();
					itrColElement != itrColor->first.end();
					itrColElement++ ){
				
				cout<<(*itrColElement)<<", ";
			}
			cout<<")="<<itrColor->second<<endl;
		}
		
#endif //DEBUG
		//cluster colors
		map< vector< unsigned int >, vector< unsigned int > > mapColorMapping;
		
		if ( uiMinColorDistance != 0 ){
			
			nCluster::cClusterFunArea< unsigned int > clusterFunArea( uiMinColorDistance );
			mapColorMapping = nCluster::cluster< vector< unsigned int > >(
				mapColorCounts, clusterFunArea );
			
			if ( dExpColorDistanceFactor != 0.0 ){
				//map color counts
				map< vector< unsigned int >, unsigned long > mapColorCountsNew;
				
				for ( map< vector< unsigned int >, vector< unsigned int > >::iterator
						itrColorMapping = mapColorMapping.begin();
						itrColorMapping != mapColorMapping.end(); itrColorMapping++ ){
					
					const map< vector< unsigned int >, unsigned long >::const_iterator
						itrColorCount = mapColorCounts.find( itrColorMapping->first );
					if ( itrColorCount == mapColorCounts.end() ){
						//no color count to add
						continue;
					}
					const unsigned long & ulColorCount = itrColorCount->second;
					
					map< vector< unsigned int >, unsigned long >::iterator
						itrNewColorCount = mapColorCountsNew.find( itrColorMapping->second );
					
					if ( itrNewColorCount == mapColorCountsNew.end() ){
						//new count -> add it
						mapColorCountsNew.insert( pair< vector< unsigned int >, unsigned long >(
							itrColorMapping->second, ulColorCount ) );
					}else{//add color count to mapped to color
						itrNewColorCount->second += ulColorCount;
					}
				}
#ifdef DEBUG
				cout<<endl<<"Created distance color mapping (size="<<mapColorMapping.size()<<"):"<<endl;
				set< vector< unsigned int > > setDestinationColors;
				for (  map< vector< unsigned int >, vector< unsigned int > >::const_iterator
						itrColorMap = mapColorMapping.begin();
						itrColorMap != mapColorMapping.end(); itrColorMap++ ){
					
					cout<<"col(";
					for ( vector< unsigned int >::const_iterator
							itrColElement = itrColorMap->first.begin();
							itrColElement != itrColorMap->first.end();
							itrColElement++ ){
						
						cout<<(*itrColElement)<<", ";
					}
					cout<<")->";
					cout<<"col(";
					for ( vector< unsigned int >::const_iterator
							itrColElement = itrColorMap->second.begin();
							itrColElement != itrColorMap->second.end();
							itrColElement++ ){
						
						cout<<(*itrColElement)<<", ";
					}
					cout<<")"<<endl;
					setDestinationColors.insert( itrColorMap->second );
				}
				cout<<"Number of destination colors: "<<setDestinationColors.size()<<endl;
				
				cout<<endl<<"New color counts (number of colors="<<mapColorCountsNew.size()<<"):"<<endl;
				for (  map< vector< unsigned int >, unsigned long >::const_iterator
						itrColor = mapColorCountsNew.begin();
						itrColor != mapColorCountsNew.end(); itrColor++ ){
					
					cout<<"#col(";
					for ( vector< unsigned int >::const_iterator
							itrColElement = itrColor->first.begin();
							itrColElement != itrColor->first.end();
							itrColElement++ ){
						
						cout<<(*itrColElement)<<", ";
					}
					cout<<")="<<itrColor->second<<endl;
				}
				cout<<"reducing colors exponential:"<<endl;
#endif //DEBUG
				//create exponential color mapping
				nConvertToFib::cColorDistance colorDistance;
				nCluster::cClusterFunExp< vector< unsigned int > >
					clusterFunExp( colorDistance, dExpColorDistanceFactor );
				const map< vector< unsigned int >, vector< unsigned int > > mapColorMappingNew =
					nCluster::cluster( mapColorCountsNew, clusterFunExp );
				
				//map old mapping to new mapping
				for (  map< vector< unsigned int >, vector< unsigned int > >::iterator
						itrColorMap = mapColorMapping.begin();
						itrColorMap != mapColorMapping.end(); itrColorMap++ ){
					
					const map< vector< unsigned int >, vector< unsigned int > >::const_iterator
						itrNewMapping = mapColorMappingNew.find( itrColorMap->second );
					
					if ( itrNewMapping != mapColorMappingNew.end() ){
						//new mapping found -> replace maped to color with new maped to color
						itrColorMap->second = itrNewMapping->second;
					}//else error: no new mapping for old mapping
				}//end for map old mapping to new mapping
				
			}//end if cluster exponential
		}else if ( dExpColorDistanceFactor != 0.0 ){
			//create exponential color mapping
			nConvertToFib::cColorDistance colorDistance;
			nCluster::cClusterFunExp< vector< unsigned int > >
				clusterFunExp( colorDistance, dExpColorDistanceFactor );
			mapColorMapping = nCluster::cluster( mapColorCounts, clusterFunExp );
		}
		
#ifdef DEBUG
		cout<<endl<<"Created color mapping (size="<<mapColorMapping.size()<<"):"<<endl<<flush;
		set< vector< unsigned int > > setDestinationColors;
		for (  map< vector< unsigned int >, vector< unsigned int > >::const_iterator
				itrColorMap = mapColorMapping.begin();
				itrColorMap != mapColorMapping.end(); itrColorMap++ ){
			
			cout<<"col(";
			for ( vector< unsigned int >::const_iterator
					itrColElement = itrColorMap->first.begin();
					itrColElement != itrColorMap->first.end();
					itrColElement++ ){
				
				cout<<(*itrColElement)<<", ";
			}
			cout<<")->";
			cout<<"col(";
			for ( vector< unsigned int >::const_iterator
					itrColElement = itrColorMap->second.begin();
					itrColElement != itrColorMap->second.end();
					itrColElement++ ){
				
				cout<<(*itrColElement)<<", ";
			}
			cout<<")"<<endl;
			
			setDestinationColors.insert( itrColorMap->second );
		}
		cout<<"Number of destination colors: "<<setDestinationColors.size()<<endl;
#endif //DEBUG
		
		//map the colors in the picture data
		nConvertToFib::mapColors( orignalImage, mapColorMapping );
		
#ifdef DEBUG
		//check number of colors
		const map< vector< unsigned int >, unsigned long > mapColorCountsTest =
			nConvertToFib::countColors( orignalImage );
		cout<<endl<<"Color counts after reducing (number of colors="<<mapColorCountsTest.size()<<"):"<<endl;
		for (  map< vector< unsigned int >, unsigned long >::const_iterator
				itrColor = mapColorCountsTest.begin();
				itrColor != mapColorCountsTest.end(); itrColor++ ){
			
			cout<<"#col(";
			for ( vector< unsigned int >::const_iterator
					itrColElement = itrColor->first.begin();
					itrColElement != itrColor->first.end();
					itrColElement++ ){
				
				cout<<(*itrColElement)<<", ";
			}
			cout<<")="<<itrColor->second<<endl;
		}
#endif //DEBUG
	}
	
	//convert into a multimedia object
	cFibElement * pFibCovertedObject = NULL;
	switch ( mode ){
		case SIMPLE:
			 pFibCovertedObject = nConvertToFib::convert( orignalImage );
		break;
		case REDUCE:
			pFibCovertedObject = nConvertToFib::convertReduced( orignalImage,
				bEvalueBackground, ulMaxAreaDiff, ulMinPoints, ulMaxDiff,
				uiMinPointsNeighbourAreas,
				bCorrectPoints, bCorrectMissingPoints, bAddNeighbours,
				bReduceFunctionDomains, bReplaceAreasWithPoints,
				uiMinPointsForArea, maxError );
		break;
		case COMPRESS:
		default:
			pFibCovertedObject = nConvertToFib::convertOptimized(
				orignalImage, bEvalueBackground, bCorrectPoints );
		break;
	}
	
	if ( pFibCovertedObject == NULL ){
		cerr<<"Error: Could not convert the data into a Fib multimedia object."<<endl;
#ifndef WINDOWS
		//linux only
		if ( 0.0 < dMinFreeMemPc ){
			//stop stop tread
			pthread_cancel( threadStop );
		}
#endif //not WINDOWS
		return 3;
	}
	
	if ( bReduceList ){
		//The number of lists in the Fib object will be reduced.
		cout<<"Reducing number of lists in the Fib object."<<endl;
		nTidyFibObjects::nBalanceLists::eliminateListTrees( pFibCovertedObject );
	}
	
	
	if ( pFileForStoringData == NULL ){
		//store to standard output in Xml format
		bool bStoreSuccesfull = pFibCovertedObject->storeXml( cout );
		
		if ( ! bStoreSuccesfull ){
	
			cerr<<"Error: Storing the data of the converted Fib object "<<
				"in the Xml format to the standard output failed."<<endl;
#ifndef WINDOWS
			//linux only
			if ( 0.0 < dMinFreeMemPc ){
				//stop stop tread
				pthread_cancel( threadStop );
			}
#endif //not WINDOWS
			return 4;
		}
	
	}else if ( strcmp( & (pFileForStoringData[
			strlen ( pFileForStoringData ) - 4 ]), ".xml") == 0 ){
		//store to file in Xml format
		ofstream outFile( pFileForStoringData );
		
		cout<<"Storing Fib object in the Xml format to the file "<< pFileForStoringData <<" . "<<endl;
		
		const bool bStoreSuccesfull = pFibCovertedObject->storeXml( outFile );
		
		if ( ! bStoreSuccesfull ){
	
			cerr<<"Error: Storing the data of the converted Fib object "<<
				"in the Xml format to the file "<< pFileForStoringData <<" failed."<<endl;
			
		}

	}else{//store to file in compressedformat
		cout<<"Storing Fib object in the compressedformat to the file "<< pFileForStoringData <<" . "<<endl;
		
		ofstream outFile( pFileForStoringData, ios_base::out | ios_base::binary );
		
		const bool bStoreSuccesfull = pFibCovertedObject->store( outFile );
		
		if ( ! bStoreSuccesfull ){
	
			cerr<<"Error: Storing the data of the converted Fib object "<<
				"in the compressed Fib format to the file "<< pFileForStoringData <<" failed."<<endl;
		}
	}
	
#ifndef WINDOWS
	//linux only
	if ( 0.0 < dMinFreeMemPc ){
		//stop stop tread
		pthread_cancel( threadStop );
	}
#endif //not WINDOWS
	
	if ( szStoreConvertedImage ){
		//convert into a multimedia object
		int iOutStatus = 0;
		fipImage * pCovertedObject = nConvertFromFib::convertToFipImage(
			*pFibCovertedObject, 0, &iOutStatus );
		
		if ( iOutStatus != 0 ){
			cout<<"The output status is: "<< iOutStatus <<endl;
		}
		
		const string szFileForStoringData =
			((string)( pFileForStoringData )) + "." + szStoreConvertedImage;
		
		if ( pCovertedObject ){
			//output the multimedia object
			
			cout<<"Saving the converted multimedia object of the created Fib object to the file \""<<
				pFileForStoringData <<"\" . "<<endl;
			bool bObjectConverted = pCovertedObject->save( szFileForStoringData.c_str() );
			if ( pCovertedObject ){
				delete pCovertedObject;
			}
			if ( ! bObjectConverted ){
				cerr<<"Error: Couldn't save to the file \""<< szFileForStoringData <<"\" ." <<endl;
				if ( pFibCovertedObject ){
					cFibElement::deleteObject( pFibCovertedObject );
				}
				return 5;
			}
		}else{
			cerr<<"Error: Could not convert the data into a multimedia object."<<endl;
			if ( pFibCovertedObject ){
				cFibElement::deleteObject( pFibCovertedObject );
			}
			return 6;
		}
	}
	if ( pFibCovertedObject ){
		cFibElement::deleteObject( pFibCovertedObject );
	}
	return 0;
}


/**
 * Print detailed help information.
 */
void printDetailedHelp(){
	
	cout<<"This program is for converting multimedia objects in non Fib"<<endl;
	cout<<"multimedia formats into Fib objects."<<endl;
	cout<<endl;
	cout<<"call: convertToFib [PARAMETER] FILE_MULTIMEDIADATA [FILE_OUTPUT]"<<endl;
	cout<<"or call: convertToFib -h[elp]"<<endl;
	cout<<"	for help"<<endl;
	cout<<""<<endl;
	cout<<"parameters:"<<endl;
	cout<<"	PATH_MULTIMEDIADATA"<<endl;
	cout<<"		The path to the to load non Fib multimedia data"<<endl;
	cout<<"	FILE_OUTPUT"<<endl;
	cout<<"		The name of the file where the Fib multimedia data would be"<<endl;
	cout<<"		stored to. If the file ending is \".xml\" the data will be written"<<endl;
	cout<<"		in the Fib Xml format. If no parameter FILE_OUTPUT is given"<<endl;
	cout<<"		the Fib object will be stored in the Fib Xml format to the"<<endl;
	cout<<"		standard output."<<endl;
	cout<<"	PARAMETER"<<endl;
	cout<<"		Parameters for converting into the Fib multimedia format"<<endl;
	cout<<"	Possible parameters are:"<<endl;
	cout<<"		-mode=VALUE"<<endl;
	cout<<"			possible VALUE: simple, compress or reduce"<<endl;
	cout<<"			standard VALUE: compress"<<endl;
	cout<<"			(instead of the values, just the first letter of the values"<<endl;
	cout<<"			can be used)"<<endl;
	cout<<"			the compression mode"<<endl;
	cout<<"			if simple: the picture will be converted directly, without"<<endl;
	cout<<"				trying to reduce the data"<<endl;
	cout<<"			if compress: the multimedia data will be compressed, by"<<endl;
	cout<<"				building Fib under objects for areas with the same color"<<endl;
	cout<<"				and evaluating the background color (see option \"-bg=\")"<<endl;
	cout<<"			if reduce: the multimedia data will be compressed with"<<endl;
	cout<<"				reducing the data (higher compression rate as VALUE"<<endl;
	cout<<"				\"compress\"), by building Fib under objects for areas with"<<endl;
	cout<<"				similar color and evaluating the background color;"<<endl;
	cout<<"				some pixels won't have the correct color (see option \"-bg=\""<<endl;
	cout<<"				in combination with \"-max_area_dif\")"<<endl;
	cout<<"				possible options:"<<endl;
	cout<<"					-max_area_diff=VALUE"<<endl;
	cout<<"						VALUE: a positive integer value"<<endl;
	cout<<"						the maximal difference of color values in an area (as"<<endl;
	cout<<"						the sum of the color vector element distances)"<<endl;
	cout<<"					-min_points=VALUE1 and -max_diff=VALUE2"<<endl;
	cout<<"						VALUE1 and VALUE2: positive integer value"<<endl;
	cout<<"						if an area with less than VALUE1 points exists and"<<endl;
	cout<<"						it layers beside an area with a color, which has a less"<<endl;
	cout<<"						difference as VALUE2 to the color of the first area,"<<endl;
	cout<<"						both areas will be combined with the color of the"<<endl;
	cout<<"						second area (if the first area has more than one"<<endl;
	cout<<"						area as a neighbor, which fulfill VALUE2, the one with"<<endl;
	cout<<"						the minimum color distance is taken);"<<endl;
	cout<<"						the value of max_diff should be bigger than that of"<<endl;
	cout<<"						max_area_diff"<<endl;
	cout<<"					-addNeighbors or -addN"<<endl;
	cout<<"						add to the areas their neighbors and remove not needed areas;"<<endl;
	cout<<"						basicly this is an anti anti-aliasing"<<endl;
	cout<<"					-reduce_function_domains or -rfd"<<endl;
	cout<<"						reduce the bits to store the function (values)"<<endl;
	cout<<"					-replace_areas_with_points or -rpawp"<<endl;
	cout<<"						replace areas, which need more bits to store than"<<endl;
	cout<<"						their points, with their points"<<endl;
	cout<<"					-min_point_for_area=VALUE or -min_pfa=VALUE"<<endl;
	cout<<"						VALUE: the minimal number of points an area should"<<endl;
	cout<<"						have, to create an area object for it;"<<endl;
	cout<<"						if 0 the standard value will be taken"<<endl;
	cout<<"					-min_point_for_neighbor_area= or -min_pfna="<<endl;
	cout<<"						all neighbor areas with less than this number of"<<endl;
	cout<<"						points, will be subsumed by the area"<<endl;
	cout<<"					-not_correct_missing_points or -ncmp"<<endl;
	cout<<"						don't correct points, which are missing in the created area Fib objects"<<endl;
	cout<<"					-max_error=VALUE"<<endl;
	cout<<"						VALUE: a positive integer value"<<endl;
	cout<<"						the maximal error for the area border polynomials to find"<<endl;
	cout<<"		-bg=VALUE"<<endl;
	cout<<"			possible VALUE: yes or no"<<endl;
	cout<<"			standard VALUE: yes"<<endl;
	cout<<"			if an background color should be set, if non exists;"<<endl;
	cout<<"			if no: no background color will be evaluated, if non exists;"<<endl;
	cout<<"		-correct-points or -cp"<<endl;
	cout<<"			if wrong points should be corrected, in the last compressing step"<<endl;
	cout<<"		-reduce_lists or -rl"<<endl;
	cout<<"			reduce the number of lists in the Fib object"<<endl;
	cout<<"		-minColDist=VALUE"<<endl;
	cout<<"			VALUE: a positive integer value"<<endl;
	cout<<"			The minimal color distance, to which reduce the original picture data."<<endl;
	cout<<"		-expColDistFactor=VALUE"<<endl;
	cout<<"			VALUE: an floating point value, should be greater 1 (else: the"<<endl;
	cout<<"				functionality is not useful)"<<endl;
	cout<<"			The factor for reducing the color exponentially in the original picture data."<<endl;
	cout<<"			(This is mainly for noise reduction.)"<<endl;
	cout<<"		-minFreeMemPc=VALUE (Unix only)"<<endl;
	cout<<"			VALUE: an floating point value, should be between (inclusive) 0"<<endl;
	cout<<"				(else: is set to 0) and 100 (else: is set to 100)"<<endl;
	cout<<"			The minimum per cent of free memory from all memory."<<endl;
	cout<<"		-storeConvertedFibObjectTo=IMAGE_FILE_ENDING or -sFibTo=IMAGE_FILE_ENDING"<<endl;
	cout<<"			IMAGE_FILE_ENDING: the ending for the image file to store the"<<endl;
	cout<<"				created Fib object to (eg. bmp or png)"<<endl;
	cout<<"			If this parameter is given the created Fib object will be"<<endl;
	cout<<"			stored to an non fib image file. The type of the image file is"<<endl;
	cout<<"			given by the specified IMAGE_FILE_ENDING."<<endl;
	cout<<endl;
	cout<<"examples:"<<endl;
	cout<<"	> convertToFib input.png outputFib.xml"<<endl;
	cout<<"	> convertToFib input.bmp outputFib.fib"<<endl;
	cout<<"	> convertToFib -mode=r -rl -max_area_diff=4 -min_points=3 -max_diff=64 -rfd -rpawp input.jpg outputFib.fib"<<endl;
	cout<<endl;
}





