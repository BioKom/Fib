/**
 * @file tIndividualIdentifier
 * file name: tIndividualIdentifier.cpp
 * @author Betti Oesterholz
 * @date 26.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cIndividualIdentifier.
 *
 * Copyright (C) @c GPL3 2009 Betti Oesterholz
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
 * This file contains the test for the class cIndividualIdentifier,
 * which represents the type for underarea.
 *
 *
 *
 *  What's tested of class cIndividualIdentifier:
 * 	- cIndividualIdentifier( unsigned long long ulInAlgorithmIdentifier )
 * 	- bool equal( const cIndividualIdentifier &idIndividual ) const;
 * 	- bool operator==( const cIndividualIdentifier &idIndividual ) const;
 * 	- bool operator!=( const cIndividualIdentifier &idIndividual ) const;
 *
 */
/*
History:
26.02.2010  Oesterholz  created
*/

#include "version.h"

#include "cIndividualIdentifier.h"

#include <iostream>
#include <vector>


using namespace enviroment;
using namespace std;


int main(int argc,char* argv[]){

//	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cIndividualIdentifier methods"<<endl;
	cout<<      "=============================================="<<endl;
	

	vector< cIndividualIdentifier > vecIndividualId;
	
	vecIndividualId.push_back( cIndividualIdentifier( 1 ) );
	vecIndividualId.push_back( cIndividualIdentifier( 1 ) );
	vecIndividualId.push_back( cIndividualIdentifier( 1 ) );
	vecIndividualId.push_back( cIndividualIdentifier( 2 ) );
	vecIndividualId.push_back( cIndividualIdentifier( 2 ) );
	vecIndividualId.push_back( cIndividualIdentifier( 3 ) );
	
	for ( unsigned int uiElement1 = 0; uiElement1 < vecIndividualId.size();
			uiElement1++ ){
		for ( unsigned int uiElement2 = 0; uiElement2 < vecIndividualId.size();
				uiElement2++ ){
			
			if ( uiElement1 != uiElement2 ){
				//check id's are not equal
				if ( ! (vecIndividualId[ uiElement1 ] == vecIndividualId[ uiElement2 ]) ){
				
					cout<<"The id "<< uiElement1 <<" is correctly not equal (operator==()) to the id "<< uiElement2 <<" . "<<endl;
				}else{
					cerr<<"Error: The id "<< uiElement1 <<" is equal (operator==()) to the id "<< uiElement2 <<" . "<<endl;
					iReturn++;
				}
				if ( ! (vecIndividualId[ uiElement1 ].equal( vecIndividualId[ uiElement2 ] ) ) ){
				
					cout<<"The id "<< uiElement1 <<" is correctly not equal (equal()) to the id "<< uiElement2 <<" . "<<endl;
				}else{
					cerr<<"Error: The id "<< uiElement1 <<" is equal (equal()) to the id "<< uiElement2 <<" . "<<endl;
					iReturn++;
				}
				if ( vecIndividualId[ uiElement1 ] != vecIndividualId[ uiElement2 ] ){
				
					cout<<"The id "<< uiElement1 <<" is correctly not equal (operator!=()) to the id "<< uiElement2 <<" . "<<endl;
				}else{
					cerr<<"Error: The id "<< uiElement1 <<" is equal (operator!=()) to the id "<< uiElement2 <<" . "<<endl;
					iReturn++;
				}

			}else{
				//check id's are equal
				if ( vecIndividualId[ uiElement1 ] == vecIndividualId[ uiElement2 ] ){
				
					cout<<"The id "<< uiElement1 <<" is correctly equal (operator==()) to the id "<< uiElement2 <<" . "<<endl;
				}else{
					cerr<<"Error: The id "<< uiElement1 <<" is not equal (operator==()) to the id "<< uiElement2 <<" . "<<endl;
					iReturn++;
				}
				if ( vecIndividualId[ uiElement1 ].equal( vecIndividualId[ uiElement2 ] ) ){
				
					cout<<"The id "<< uiElement1 <<" is correctly equal (equal()) to the id "<< uiElement2 <<" . "<<endl;
				}else{
					cerr<<"Error: The id "<< uiElement1 <<" is not equal (equal()) to the id "<< uiElement2 <<" . "<<endl;
					iReturn++;
				}
				if ( ! ( vecIndividualId[ uiElement1 ] != vecIndividualId[ uiElement2 ] ) ){
				
					cout<<"The id "<< uiElement1 <<" is correctly equal (operator!=()) to the id "<< uiElement2 <<" . "<<endl;
				}else{
					cerr<<"Error: The id "<< uiElement1 <<" is not equal (operator!=()) to the id "<< uiElement2 <<" . "<<endl;
					iReturn++;
				}
			}
		}
	}
	
	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}




