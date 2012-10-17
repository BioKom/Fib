/**
 * @file tOperationIdentifier
 * file name: tOperationIdentifier.cpp
 * @author Betti Oesterholz
 * @date 26.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cOperationIdentifier.
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
 * This file contains the test for the class cOperationIdentifier,
 * which represents the type for underarea.
 *
 *
 *
 *  What's tested of class cOperationIdentifier:
 * 	- cOperationIdentifier( unsigned long long ulInAlgorithmIdentifier )
 * 	- bool equal( const cOperationIdentifier &idOperation ) const;
 * 	- bool operator==( const cOperationIdentifier &idOperation ) const;
 * 	- bool operator!=( const cOperationIdentifier &idOperation ) const;
 *
 */
/*
History:
26.02.2010  Oesterholz  created
*/

#include "version.h"

#include "cOperationIdentifier.h"

#include <iostream>
#include <vector>


using namespace enviroment;
using namespace std;


int main(int argc,char* argv[]){

//	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cOperationIdentifier methods"<<endl;
	cout<<      "============================================="<<endl;
	

	vector< cOperationIdentifier > vecOperationId;
	
	vecOperationId.push_back( cOperationIdentifier( 1 ) );
	vecOperationId.push_back( cOperationIdentifier( 1 ) );
	vecOperationId.push_back( cOperationIdentifier( 1 ) );
	vecOperationId.push_back( cOperationIdentifier( 2 ) );
	vecOperationId.push_back( cOperationIdentifier( 2 ) );
	vecOperationId.push_back( cOperationIdentifier( 3 ) );
	
	for ( unsigned int uiElement1 = 0; uiElement1 < vecOperationId.size();
			uiElement1++ ){
		for ( unsigned int uiElement2 = 0; uiElement2 < vecOperationId.size();
				uiElement2++ ){
			
			if ( uiElement1 != uiElement2 ){
				//check id's are not equal
				if ( ! (vecOperationId[ uiElement1 ] == vecOperationId[ uiElement2 ]) ){
				
					cout<<"The id "<< uiElement1 <<" is correctly not equal (operator==()) to the id "<< uiElement2 <<" . "<<endl;
				}else{
					cerr<<"Error: The id "<< uiElement1 <<" is equal (operator==()) to the id "<< uiElement2 <<" . "<<endl;
					iReturn++;
				}
				if ( ! (vecOperationId[ uiElement1 ].equal( vecOperationId[ uiElement2 ] ) ) ){
				
					cout<<"The id "<< uiElement1 <<" is correctly not equal (equal()) to the id "<< uiElement2 <<" . "<<endl;
				}else{
					cerr<<"Error: The id "<< uiElement1 <<" is equal (equal()) to the id "<< uiElement2 <<" . "<<endl;
					iReturn++;
				}
				if ( vecOperationId[ uiElement1 ] != vecOperationId[ uiElement2 ] ){
				
					cout<<"The id "<< uiElement1 <<" is correctly not equal (operator!=()) to the id "<< uiElement2 <<" . "<<endl;
				}else{
					cerr<<"Error: The id "<< uiElement1 <<" is equal (operator!=()) to the id "<< uiElement2 <<" . "<<endl;
					iReturn++;
				}

			}else{
				//check id's are equal
				if ( vecOperationId[ uiElement1 ] == vecOperationId[ uiElement2 ] ){
				
					cout<<"The id "<< uiElement1 <<" is correctly equal (operator==()) to the id "<< uiElement2 <<" . "<<endl;
				}else{
					cerr<<"Error: The id "<< uiElement1 <<" is not equal (operator==()) to the id "<< uiElement2 <<" . "<<endl;
					iReturn++;
				}
				if ( vecOperationId[ uiElement1 ].equal( vecOperationId[ uiElement2 ] ) ){
				
					cout<<"The id "<< uiElement1 <<" is correctly equal (equal()) to the id "<< uiElement2 <<" . "<<endl;
				}else{
					cerr<<"Error: The id "<< uiElement1 <<" is not equal (equal()) to the id "<< uiElement2 <<" . "<<endl;
					iReturn++;
				}
				if ( ! ( vecOperationId[ uiElement1 ] != vecOperationId[ uiElement2 ] ) ){
				
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




