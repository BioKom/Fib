/**
 * @file tVectorChecksum
 * file name: tVectorChecksum.cpp
 * @author Betti Oesterholz
 * @date 17.11.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class tVectorChecksum.
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
 * This file contains the test for the class tVectorChecksum,
 * which represents the vector for properties.
 *
 *
 *
 *  What's tested of class tVectorChecksum:
 * 	- cVectorChecksum( cFibElement & definingPointElement );
 * 	- cVectorChecksum( const cVectorChecksum & vector, cFibElement * definingFibElement = NULL );
 * 	- getElementType()
 * 	- getNumberOfElements()
 * 	- getVectorType()
 * 	- getDomain()
 * 	- getDomain(i=1..n)
 * 	- getStandardDomain()
 * 	- getDefiningFibElement()
 * 	- setDefiningFibElement()
 * 	- isVariable(i=1..n)
 * 	- setValue(i=1..n)
 * 	- getValue(i=1..n)
 * 	- setVariable(i=1..n)
 * 	- getVariable(i=1..n)
 * 	- equal()
 * 	- operator==()
 * 	- operator=( const cFibVector &vector ) 
 * 	- createInstance( unsignedIntFib iNumberOfElements=2, cFibElement *definingPropertyElement=NULL )
 * 	- storeXml()
 * 	- intFib getPropertyType() const;
 *
 */
/*
History:
17.11.2009  Oesterholz  created
27.12.2009  Oesterholz  using function (tCompareBits:)compareDoubleFib() for comparing doubles from restored xml
20.02.2011  Oesterholz  sscanf() reads long long "%lld" instead of long
29.04.2011  Oesterholz  sscanf() "%lld" for windows to "%I64d"
06.06.2011  Oesterholz  number atribute in XML-vector is now optional
*/


#include "version.h"


#include "cVectorChecksum.h"
#include "cTypeProperty.h"
#include "cVectorPosition.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cRoot.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif


using namespace fib;
using namespace std;


int testCostructor( unsigned long &ulTestphase );
int testDomain( unsigned long &ulTestphase );
int testGetSetDefiningElement( unsigned long &ulTestphase );
int testVectorElements( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testCreateInstance( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testAssignment( unsigned long &ulTestphase );



int testCompareTwoEqualVectors( const cFibVector & vector1, const string & szNameVector1,
	const cFibVector & vector2, const string & szNameVector2 );
int testCompareTwoNotEqualVectors( const cFibVector & vector1, const string & szNameVector1,
	const cFibVector & vector2, const string & szNameVector2 );


int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cVectorChecksum methods"<<endl;
	cout<<      "========================================"<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testDomain( ulTestphase );
	iReturn += testGetSetDefiningElement( ulTestphase );
	iReturn += testVectorElements( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCreateInstance( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testAssignment( ulTestphase );


	if ( iReturn==0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * This method tests the constructors and the getNumberOfDimension()
 * and getType() method of the cVectorChecksum class.
 *
 * methods tested:
 * 	- cVectorChecksum( intFib iPropertyType, cFibElement & definingPointElement );
 * 	- cVectorChecksum( intFib iPropertyType, unsignedIntFib iNumberOfElements , cFibElement *pDefiningPropertyElement=NULL );
 * 	- cVectorChecksum( const cVectorChecksum & vector, cFibElement * definingFibElement = NULL );
 * 	- getElementType()
 * 	- getNumberOfElements()
 * 	- isVariable(i=1..n)==false
 * 	- getValue(i=1..n)==0
 * 	- getDomain()
 * 	- getElementType()
 * 	- getDefiningFibElement()
 * 	- getVectorType()
 * 	- intFib getPropertyType() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

//TODO change  root element to point element

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cVectorChecksum"<<endl;

	cout<<"cTypeProperty typeChecksum( cTypeProperty::CHECKSUM );"<<endl;
	cTypeProperty typeChecksum( cTypeProperty::CHECKSUM );
	
	cout<<"cVectorChecksum vecChecksum;"<<endl;
	cVectorChecksum vecChecksum;


	//check the getVectorType() methode from cVectorChecksum
	if ( vecChecksum.getVectorType() == "property.checksum" ){
	
		cout<<"The name of the checksumvector is correctly \"property.checksum\" . "<<endl;
	}else{
		cerr<<"Error: The name of the checksumvector is "<<
			vecChecksum.getVectorType()<<" but should be \"property.checksum\" ."<<endl;
		iReturn++;
	}
	//check the getPropertyType() methode from cVectorChecksum
	if ( vecChecksum.getPropertyType() == cTypeProperty::CHECKSUM  ){
	
		cout<<"The type of the checksumvector is correctly "<<cTypeProperty::CHECKSUM <<" . "<<endl;
	}else{
		cerr<<"Error: The type of the checksumvector is "<<
			vecChecksum.getPropertyType()<<" but should be "<<cTypeProperty::CHECKSUM <<" ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorChecksum
	cTypeElement * pTypeProperty = vecChecksum.getElementType();
	if ( typeChecksum == (*pTypeProperty) ){
	
		cout<<"The type of the checksumvector is correctly equal to typeChecksum. "<<endl;
	}else{
		cerr<<"Error: The type of checksumvector not equal to typeChecksum ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorChecksum
	if ( vecChecksum.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the checksumvector is "<<
			vecChecksum.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecChecksum.getNumberOfElements(); 
			uiActualElement++ ){
		
		if ( ! vecChecksum.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecChecksum.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is "<<vecChecksum.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vecChecksum.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the checksumvector."<<endl;
		iReturn++;
	}

	//check the getDomain() methode from cVectorChecksum
	if ( vecChecksum.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the checksumvector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorChecksum with an defining element"<<endl;

	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;

	cout<<"cRoot rootChecksum;"<<flush<<endl;
	cRoot rootChecksum;
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3( 3 );
	cout<<"vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE3( vecDomainsE3 );"<<endl;
	cDomainVector vectorDomainE3( vecDomainsE3 );
	delete vecDomainsE3[ 0 ];
	delete vecDomainsE3[ 1 ];
	delete vecDomainsE3[ 2 ];

	cout<<"rootChecksum.getDomains()->addDomain( typeChecksum, &vectorDomainE3);"<<endl;
	rootChecksum.getDomains()->addDomain( typeChecksum, &vectorDomainE3);

	
	cout<<"cVectorChecksum vecChecksum1RootChecksum1( &rootChecksum );"<<endl;
	cVectorChecksum vecChecksum1RootChecksum1(  &rootChecksum );


	//check the getVectorType() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1.getVectorType() == "property.checksum" ){
	
		cout<<"The name of the checksumvector is correctly \"property.checksum\" . "<<endl;
	}else{
		cerr<<"Error: The name of the checksumvector is "<<
			vecChecksum1RootChecksum1.getVectorType()<<" but should be \"property.checksum\" ."<<endl;
		iReturn++;
	}
	if ( vecChecksum1RootChecksum1.getPropertyType() == cTypeProperty::CHECKSUM  ){
	
		cout<<"The type of the checksumvector is correctly "<<cTypeProperty::CHECKSUM <<" . "<<endl;
	}else{
		cerr<<"Error: The type of the checksumvector is "<<
			vecChecksum1RootChecksum1.getPropertyType()<<" but should be "<<cTypeProperty::CHECKSUM <<" ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorChecksum
	pTypeProperty = vecChecksum1RootChecksum1.getElementType();
	if ( typeChecksum == (*pTypeProperty) ){
	
		cout<<"The type of the checksumvector is correctly equal to typeChecksum. "<<endl;
	}else{
		cerr<<"Error: The type of checksumvector not equal to typeChecksum ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the checksumvector is "<<
			vecChecksum1RootChecksum1.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecChecksum1RootChecksum1.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecChecksum1RootChecksum1.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecChecksum1RootChecksum1.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is "<<vecChecksum1RootChecksum1.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &rootChecksum == vecChecksum1RootChecksum1.getDefiningFibElement() ){
	
		cout<<"The rootChecksum is the defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The rootChecksum is not the defining element for the checksumvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the checksumvector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3 == (*(vecChecksum1RootChecksum1.getDomain())) ){
	
		cout<<"The vectorDomainE3 is the domain for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the checksumvector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorChecksum with an empty root element"<<endl;

	cout<<"cVectorChecksum vecChecksum1RE( &emptyRoot );"<<endl;
	cVectorChecksum vecChecksum1RE( &emptyRoot );


	//check the getVectorType() methode from cVectorChecksum
	if ( vecChecksum1RE.getVectorType() == "property.checksum" ){
	
		cout<<"The name of the checksumvector is correctly \"property.checksum\" . "<<endl;
	}else{
		cerr<<"Error: The name of the checksumvector is "<<
			vecChecksum1RE.getVectorType()<<" but should be \"property.checksum\" ."<<endl;
		iReturn++;
	}
	if ( vecChecksum1RE.getPropertyType() == cTypeProperty::CHECKSUM  ){
	
		cout<<"The type of the checksumvector is correctly "<<cTypeProperty::CHECKSUM <<" . "<<endl;
	}else{
		cerr<<"Error: The type of the checksumvector is "<<
			vecChecksum1RE.getPropertyType()<<" but should be "<<cTypeProperty::CHECKSUM <<" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorChecksum
	pTypeProperty = vecChecksum1RE.getElementType();
	if ( typeChecksum == (*pTypeProperty) ){
	
		cout<<"The type of the checksumvector is correctly equal to typeChecksum. "<<endl;
	}else{
		cerr<<"Error: The type of checksumvector not equal to typeChecksum ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorChecksum
	if ( vecChecksum1RE.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the checksumvector is "<<
			vecChecksum1RE.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecChecksum1RE.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecChecksum1RE.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecChecksum1RE.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is "<<vecChecksum1RE.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vecChecksum1RE.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &emptyRoot == vecChecksum1RE.getDefiningFibElement() ){
	
		cout<<"The rootChecksum is the defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The rootChecksum is not the defining element for the checksumvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorChecksum
	if ( vecChecksum1RE.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the checksumvector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the checksumvector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorChecksum by copying vecChecksum1RootChecksum1"<<endl;
	
	cout<<"cVectorChecksum vecChecksum1RootChecksum1Copy( vecChecksum1RootChecksum1 );"<<endl;
	cVectorChecksum vecChecksum1RootChecksum1Copy( vecChecksum1RootChecksum1 );

	//check the getVectorType() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1Copy.getVectorType() == "property.checksum" ){
	
		cout<<"The name of the checksumvector is correctly \"property.checksum\" . "<<endl;
	}else{
		cerr<<"Error: The name of the checksumvector is "<<
			vecChecksum1RootChecksum1Copy.getVectorType()<<" but should be \"property.checksum\" ."<<endl;
		iReturn++;
	}
	if ( (unsignedIntFib)(vecChecksum1RootChecksum1Copy.getPropertyType()) == cTypeProperty::CHECKSUM ){
	
		cout<<"The type of the checksumvector is correctly CHECKSUM . "<<endl;
	}else{
		cerr<<"Error: The type of the checksumvector is "<<
			vecChecksum1RootChecksum1Copy.getPropertyType()<<" but should be CHECKSUM ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorChecksum
	pTypeProperty = vecChecksum1RootChecksum1Copy.getElementType();
	if ( typeChecksum == (*pTypeProperty) ){
	
		cout<<"The type of the checksumvector is correctly equal to typeChecksum. "<<endl;
	}else{
		cerr<<"Error: The type of checksumvector not equal to typeChecksum ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1Copy.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the checksumvector is "<<
			vecChecksum1RootChecksum1Copy.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecChecksum1RootChecksum1Copy.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecChecksum1RootChecksum1Copy.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecChecksum1RootChecksum1Copy.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is "<< vecChecksum1RootChecksum1Copy.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1Copy.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &rootChecksum == vecChecksum1RootChecksum1Copy.getDefiningFibElement() ){
	
		cout<<"The rootChecksum is the defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The rootChecksum is not the defining element for the checksumvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1Copy.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3 == vecChecksum1RootChecksum1Copy.getDomain() ){
	
		cout<<"The vectorDomainE3 is the domain for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the checksumvector."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorChecksum by copying vecChecksum1RootChecksum1 and givin rootChecksum as an defining element"<<endl;
	
	cout<<"cVectorChecksum vecChecksum1RootChecksum1Copy2( vecChecksum1RootChecksum1, &rootChecksum );"<<endl;
	cVectorChecksum vecChecksum1RootChecksum1Copy2( vecChecksum1RootChecksum1, &rootChecksum );

	//check the getVectorType() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1Copy2.getVectorType() == "property.checksum" ){
	
		cout<<"The name of the checksumvector is correctly \"property.checksum\" . "<<endl;
	}else{
		cerr<<"Error: The name of the checksumvector is "<<
			vecChecksum1RootChecksum1Copy2.getVectorType()<<" but should be \"property.checksum\" ."<<endl;
		iReturn++;
	}
	if ( (unsignedIntFib)( vecChecksum1RootChecksum1Copy2.getPropertyType() ) == cTypeProperty::CHECKSUM ){
	
		cout<<"The type of the checksumvector is correctly CHECKSUM . "<<endl;
	}else{
		cerr<<"Error: The type of the checksumvector is "<<
			vecChecksum1RootChecksum1Copy2.getPropertyType()<<" but should be CHECKSUM ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorChecksum
	pTypeProperty = vecChecksum1RootChecksum1Copy2.getElementType();
	if ( typeChecksum == (*pTypeProperty) ){
	
		cout<<"The type of the checksumvector is correctly equal to typeChecksum. "<<endl;
	}else{
		cerr<<"Error: The type of checksumvector not equal to typeChecksum ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1Copy2.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the checksumvector is "<<
			vecChecksum1RootChecksum1Copy2.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecChecksum1RootChecksum1Copy2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecChecksum1RootChecksum1Copy2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecChecksum1RootChecksum1Copy2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is "<< vecChecksum1RootChecksum1Copy2.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1Copy2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &rootChecksum == vecChecksum1RootChecksum1Copy2.getDefiningFibElement() ){
	
		cout<<"The rootChecksum is the defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The rootChecksum is not the defining element for the checksumvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1Copy2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3 == vecChecksum1RootChecksum1Copy2.getDomain() ){
	
		cout<<"The vectorDomainE3 is the domain for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the checksumvector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorChecksum by copying vecChecksum1RootChecksum1 with changed elements"<<endl;
	
	cout<<"vecChecksum1RootChecksum1.setValue( 1, 1 );"<<endl;
	vecChecksum1RootChecksum1.setValue( 1, 1 );
	cout<<"vecChecksum1RootChecksum1.setValue( 2, 2 );"<<endl;
	vecChecksum1RootChecksum1.setValue( 2, 2 );
	cout<<"vecChecksum1RootChecksum1.setValue( 3, 3 );"<<endl;
	vecChecksum1RootChecksum1.setValue( 3, 3 );
	
	cout<<"cVectorChecksum vecChecksum1RootChecksumCopyMod( vecChecksum1RootChecksum1 );"<<endl;
	cVectorChecksum vecChecksum1RootChecksumCopyMod( vecChecksum1RootChecksum1 );

	//check the getVectorType() methode from cVectorChecksum
	if ( vecChecksum1RootChecksumCopyMod.getVectorType() == "property.checksum" ){
	
		cout<<"The name of the checksumvector is correctly \"property.checksum\" . "<<endl;
	}else{
		cerr<<"Error: The name of the checksumvector is "<<
			vecChecksum1RootChecksumCopyMod.getVectorType()<<" but should be \"property.checksum\" ."<<endl;
		iReturn++;
	}
	if ( vecChecksum1RootChecksumCopyMod.getPropertyType() == cTypeProperty::CHECKSUM  ){
	
		cout<<"The type of the checksumvector is correctly "<<cTypeProperty::CHECKSUM <<" . "<<endl;
	}else{
		cerr<<"Error: The type of the checksumvector is "<<
			vecChecksum1RootChecksumCopyMod.getPropertyType()<<" but should be "<<cTypeProperty::CHECKSUM <<" ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorChecksum
	pTypeProperty = vecChecksum1RootChecksumCopyMod.getElementType();
	if ( typeChecksum == (*pTypeProperty) ){
	
		cout<<"The type of the checksumvector is correctly equal to typeChecksum. "<<endl;
	}else{
		cerr<<"Error: The type of checksumvector not equal to typeChecksum ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorChecksum
	if ( vecChecksum1RootChecksumCopyMod.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the checksumvector is "<<
			vecChecksum1RootChecksumCopyMod.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
		//check the first vectorelement
	if ( ! vecChecksum1RootChecksumCopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum1RootChecksumCopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"checksumvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is "<<
			vecChecksum1RootChecksumCopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( ! vecChecksum1RootChecksumCopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum1RootChecksumCopyMod.getValue( 2 ) == (doubleFib)(2) ){
	
		cout<<"The 2'th element of the "<<
			"checksumvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is "<<
			vecChecksum1RootChecksumCopyMod.getValue( 2 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the third vectorelement
	if ( ! vecChecksum1RootChecksumCopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum1RootChecksumCopyMod.getValue( 3 ) == (doubleFib)(3) ){
	
		cout<<"The 3'th element of the "<<
			"checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the checksumvector is "<<
			vecChecksum1RootChecksumCopyMod.getValue( 3 )<<" and not 3 . "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vecChecksum1RootChecksumCopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &rootChecksum == vecChecksum1RootChecksumCopyMod.getDefiningFibElement() ){
	
		cout<<"The rootChecksum is the defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The rootChecksum is not the defining element for the checksumvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorChecksum
	if ( vecChecksum1RootChecksumCopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3 == vecChecksum1RootChecksumCopyMod.getDomain() ){
	
		cout<<"The vectorDomainE3 is the domain for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the checksumvector."<<endl;
		iReturn++;
	}

	
	cout<<endl<<"Testing the original vector vecChecksum1RootChecksum:"<<endl;

	//check the getVectorType() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1.getVectorType() == "property.checksum" ){
	
		cout<<"The name of the checksumvector is correctly \"property.checksum\" . "<<endl;
	}else{
		cerr<<"Error: The name of the checksumvector is "<<
			vecChecksum1RootChecksum1.getVectorType()<<" but should be \"property.checksum\" ."<<endl;
		iReturn++;
	}
	if ( vecChecksum1RootChecksum1.getPropertyType() == cTypeProperty::CHECKSUM  ){
	
		cout<<"The type of the checksumvector is correctly "<<cTypeProperty::CHECKSUM <<" . "<<endl;
	}else{
		cerr<<"Error: The type of the checksumvector is "<<
			vecChecksum1RootChecksum1.getPropertyType()<<" but should be "<<cTypeProperty::CHECKSUM <<" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorChecksum
	pTypeProperty = vecChecksum1RootChecksum1.getElementType();
	if ( typeChecksum == (*pTypeProperty) ){
	
		cout<<"The type of the checksumvector is correctly equal to typeChecksum. "<<endl;
	}else{
		cerr<<"Error: The type of checksumvector not equal to typeChecksum ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the checksumvector is "<<
			vecChecksum1RootChecksum1.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
		//check the first vectorelement
	if ( ! vecChecksum1RootChecksum1.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum1RootChecksum1.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"checksumvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is "<<
			vecChecksum1RootChecksum1.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( ! vecChecksum1RootChecksum1.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum1RootChecksum1.getValue( 2 ) == (doubleFib)(2) ){
	
		cout<<"The 2'th element of the "<<
			"checksumvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is "<<
			vecChecksum1RootChecksum1.getValue( 2 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the third vectorelement
	if ( ! vecChecksum1RootChecksum1.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum1RootChecksum1.getValue( 3 ) == (doubleFib)(3) ){
	
		cout<<"The 3'th element of the "<<
			"checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the checksumvector is "<<
			vecChecksum1RootChecksum1.getValue( 3 )<<" and not 3 . "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &rootChecksum == vecChecksum1RootChecksum1.getDefiningFibElement() ){
	
		cout<<"The rootChecksum is the defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The rootChecksum is not the defining element for the checksumvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorChecksum
	if ( vecChecksum1RootChecksum1.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3 == vecChecksum1RootChecksum1.getDomain() ){
	
		cout<<"The vectorDomainE3 is the domain for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the checksumvector."<<endl;
		iReturn++;
	}

	cout<<endl<<"Changing vecChecksum1RootChecksum should not change the copy:"<<endl;


	cout<<"vecChecksum1RootChecksum1.setValue( 1, 7 );"<<endl;
	vecChecksum1RootChecksum1.setValue( 1, 7 );
	cout<<"vecChecksum1RootChecksum1.setValue( 2, 1 );"<<endl;
	vecChecksum1RootChecksum1.setValue( 2, 1 );
	cout<<"vecChecksum1RootChecksum1.setValue( 3, 2 );"<<endl;
	vecChecksum1RootChecksum1.setValue( 3, 2 );


	cout<<endl<<"Testing the copied vector vecChecksum1RootChecksumCopyMod for changed values:"<<endl;
	
	//check the getVectorType() methode from cVectorChecksum
	if ( vecChecksum1RootChecksumCopyMod.getVectorType() == "property.checksum" ){
	
		cout<<"The name of the checksumvector is correctly \"property.checksum\" . "<<endl;
	}else{
		cerr<<"Error: The name of the checksumvector is "<<
			vecChecksum1RootChecksumCopyMod.getVectorType()<<" but should be \"property.checksum\" ."<<endl;
		iReturn++;
	}
	if ( vecChecksum1RootChecksumCopyMod.getPropertyType() == cTypeProperty::CHECKSUM  ){
	
		cout<<"The type of the checksumvector is correctly "<<cTypeProperty::CHECKSUM <<" . "<<endl;
	}else{
		cerr<<"Error: The type of the checksumvector is "<<
			vecChecksum1RootChecksumCopyMod.getPropertyType()<<" but should be "<<cTypeProperty::CHECKSUM <<" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorChecksum
	pTypeProperty = vecChecksum1RootChecksumCopyMod.getElementType();
	if ( typeChecksum == (*pTypeProperty) ){
	
		cout<<"The type of the checksumvector is correctly equal to typeChecksum. "<<endl;
	}else{
		cerr<<"Error: The type of checksumvector not equal to typeChecksum ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorChecksum
	if ( vecChecksum1RootChecksumCopyMod.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the checksumvector is "<<
			vecChecksum1RootChecksumCopyMod.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
		//check the first vectorelement
	if ( ! vecChecksum1RootChecksumCopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum1RootChecksumCopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"checksumvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is "<<
			vecChecksum1RootChecksumCopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( ! vecChecksum1RootChecksumCopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum1RootChecksumCopyMod.getValue( 2 ) == (doubleFib)(2) ){
	
		cout<<"The 2'th element of the "<<
			"checksumvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is "<<
			vecChecksum1RootChecksumCopyMod.getValue( 2 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the third vectorelement
	if ( ! vecChecksum1RootChecksumCopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum1RootChecksumCopyMod.getValue( 3 ) == (doubleFib)(3) ){
	
		cout<<"The 3'th element of the "<<
			"checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the checksumvector is "<<
			vecChecksum1RootChecksumCopyMod.getValue( 3 )<<" and not 3 . "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vecChecksum1RootChecksumCopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &rootChecksum == vecChecksum1RootChecksum1Copy.getDefiningFibElement() ){
	
		cout<<"The rootChecksum is the defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The rootChecksum is not the defining element for the checksumvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorChecksum
	if ( vecChecksum1RootChecksumCopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3 == vecChecksum1RootChecksumCopyMod.getDomain() ){
	
		cout<<"The vectorDomainE3 is the domain for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the checksumvector."<<endl;
		iReturn++;
	}


	return iReturn;
}



/**
 * This method tests the method for the domains of the cVectorChecksum class.
 *
 * methods tested:
 * 	- getDomain()
 * 	- getDomain(i=1..n)
 * 	- getStandardDomain()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testDomain( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get Domain methods"<<endl;
	
	cout<<"cRoot rootChecksum;"<<flush<<endl;
	cRoot rootChecksum;
	
	cout<<"cTypeProperty typeChecksum( cTypeProperty::CHECKSUM );"<<endl;
	cTypeProperty typeChecksum( cTypeProperty::CHECKSUM );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3( 3 );
	cout<<"vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE3( vecDomainsE3 );"<<endl;
	cDomainVector vectorDomainE3( vecDomainsE3 );
	delete vecDomainsE3[ 0 ];
	delete vecDomainsE3[ 1 ];
	delete vecDomainsE3[ 2 ];
	
	cout<<"rootChecksum.getDomains()->addDomain( typeChecksum, &vectorDomainE3 );"<<endl;
	rootChecksum.getDomains()->addDomain( typeChecksum, &vectorDomainE3 );

	cout<<"cVectorChecksum vecChecksumRD3( &rootChecksum );"<<endl;
	cVectorChecksum vecChecksumRD3( &rootChecksum );

	
	//check the getNumberOfElements() methode from cVectorChecksum
	if ( vecChecksumRD3.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the checksumvector is "<<
			vecChecksumRD3.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the getDomain() methode from cVectorChecksum
	if ( vecChecksumRD3.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3 == vecChecksumRD3.getDomain() ){
	
		cout<<"The vectorDomainE3 is the domain for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the checksumvector."<<endl;
		iReturn++;
	}

	/*check the getDomain(i=1..n) method of the positionsvektor*/
	//test the getType() method
	cout<<"cDomain * pDomainD3 = vecChecksumRD3.getDomain();"<<endl;
	cDomain * pDomainD3 = vecChecksumRD3.getDomain();
	if ( pDomainD3->getType() == "DomainVector" ){
	
		cout<<"The type of pDomainD3 is correctly \"DomainVector\". "<<endl;

		cDomainVector * pVectorDomainD3 = (cDomainVector*)pDomainD3;
		
		//test the getNumberOfElements() method
		if ( pVectorDomainD3->getNumberOfElements() == 3 ){
		
			cout<<"The number of elements of pDomainD3 is correctly 3. "<<endl;
			
			//check domains of vector domain elements
			
			cDomainNaturalNumberBit domainNaturalNumberBit1 = cDomainNaturalNumberBit( 1 );
			if ( pVectorDomainD3->getElementDomain( 1 ) == NULL ){
				cerr<<"Error: The first element domain is NULL. "<<endl;
				iReturn++;
			}else if ( (*(pVectorDomainD3->getElementDomain( 1 ))) == domainNaturalNumberBit1 ){
			
				cout<<"The first element domain is correctly an cDomainNaturalNumberBit domain with 1 bits. "<<endl;
			}else{
				cerr<<"Error: The first element domain is not an cDomainNaturalNumberBit domain with 1 bits. "<<endl;
				iReturn++;
			}
	
			cDomainNaturalNumberBit domainNaturalNumberBit2 = cDomainNaturalNumberBit( 2 );
			if ( pVectorDomainD3->getElementDomain( 2 )==NULL ){
				cerr<<"Error: The secound element domain is NULL. "<<endl;
				iReturn++;
			}else if ( (*(pVectorDomainD3->getElementDomain( 2 ))) == domainNaturalNumberBit2 ){
			
				cout<<"The secound element domain is correctly an cDomainNaturalNumberBit domain with 2 bits. "<<endl;
			}else{
				cerr<<"Error: The secound element domain is not an cDomainNaturalNumberBit domain with 2 bits. "<<endl;
				iReturn++;
			}
	
			cDomainNaturalNumberBit domainNaturalNumberBit3 = cDomainNaturalNumberBit( 3 );
			
			if ( pVectorDomainD3->getElementDomain( 3 ) == NULL ){
				cerr<<"Error: The third element domain is NULL. "<<endl;
				iReturn++;
			}else if ( (*(pVectorDomainD3->getElementDomain( 3 ))) == domainNaturalNumberBit3 ){
			
				cout<<"The third element domain is correctly an cDomainNaturalNumberBit domain with 3 bits. "<<endl;
			}else{
				cerr<<"Error: The third element domain is not an cDomainNaturalNumberBit domain with 3 bits. "<<endl;
				iReturn++;
			}
	
			//check bounderies
			if ( pVectorDomainD3->getElementDomain( 0 ) == NULL ){
				cerr<<"The is no 0'th element domain."<<endl;
			}
	
			if ( pVectorDomainD3->getElementDomain( 4 ) == NULL ){
				cerr<<"The is no 4'th element domain."<<endl;
			}
	
	
		}else{
			cerr<<"Error: The number of elements of vectorDomain3 is "<<
				pVectorDomainD3->getNumberOfElements() <<" and not 3 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The type of pDomainD3 is "<<pDomainD3->getType() <<
			" and not \"DomainVector\""<<endl;
		iReturn++;
	}

	//check the getStandardDomain() method from cVectorChecksum
	cDomain * pDomainStandardD3 = vecChecksumRD3.getStandardDomain();
	cDomain * pTypeDomainStandardD3 = typeChecksum.getStandardDomain();
	
	if ( pDomainStandardD3 == NULL ){
		cerr<<"Error: Ther is no domain defined for the checksumvector."<<endl;
		iReturn++;	
	}else if ( *pDomainStandardD3 == *pTypeDomainStandardD3 ){
	
		cout<<"The vecChecksum1RootChecksum1 has the correct standard domain. "<<endl;
	}else{
		cerr<<"Error: The vecChecksum1RootChecksum1 has not the correct standard domain."<<endl;
		iReturn++;
	}

	delete pDomainStandardD3;
	delete pTypeDomainStandardD3;
	
	return iReturn;
}



/**
 * This method tests setDefiningFibElement() and getDefiningFibElement()
 * method of the cVectorChecksum class.
 *
 * methods tested:
 * 	- setDefiningFibElement()
 * 	- getDefiningFibElement()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testGetSetDefiningElement( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods"<<endl;

	cout<<"cRoot definingElement1;"<<endl;
	cRoot definingElement1;
	cout<<"cRoot definingElement2;"<<endl;
	cRoot definingElement2;

	cout<<"cVectorChecksum vecChecksum;"<<endl;
	cVectorChecksum vecChecksum;

	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vecChecksum.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the checksumvector."<<endl;
		iReturn++;
	}
	
	cout<<"vecChecksum.setDefiningFibElement( &definingElement1 );"<<endl;
	vecChecksum.setDefiningFibElement( &definingElement1 );

	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vecChecksum.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &definingElement1 == vecChecksum.getDefiningFibElement() ){
	
		cout<<"The definingElement1 is the defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The definingElement1 is not the defining element for the checksumvector."<<endl;
		iReturn++;
	}

	cout<<"vecChecksum.setDefiningFibElement( &definingElement2 );"<<endl;
	vecChecksum.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vecChecksum.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecChecksum.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the checksumvector."<<endl;
		iReturn++;
	}

	cout<<"vecChecksum.setDefiningFibElement( NULL );"<<endl;
	vecChecksum.setDefiningFibElement( NULL );

	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vecChecksum.getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the checksumvector."<<endl;
		iReturn++;
	}

	cout<<"vecChecksum.setDefiningFibElement( &definingElement2 );"<<endl;
	vecChecksum.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vecChecksum.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecChecksum.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the checksumvector."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests cVectorChecksum methods for manipulating the
 * vectorelements.
 *
 * methods tested:
 * 	- setValue()
 * 	- getValue()
 * 	- setVariable()
 * 	- getVariable()
 * 	- isVariable()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testVectorElements( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

//TODO test if yust values of the domain can be set

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing methods for getting the vectorelementdata"<<endl;
	
	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;
	
	cout<<"cVectorChecksum vecChecksum( &emptyRoot );"<<endl;
	cVectorChecksum vecChecksum( &emptyRoot );


	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecChecksum.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecChecksum.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecChecksum.getValue( uiActualElement ) == (doubleFib)(0.0) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is "<<vecChecksum.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
		if ( vecChecksum.getVariable( uiActualElement ) == NULL ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly no variable . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is an variable . "<<endl;
			iReturn++;
		}
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() method"<<endl;

	cout<<"vecChecksum.setValue( 2, 2.2 )"<<endl;
	if ( vecChecksum.setValue( 2, 2.2 ) ){
	
		cout<<"The 2'th element of the checksumvector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecChecksum.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"checksumvector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is "<<
			vecChecksum.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the checksumvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is an variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecChecksum.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getValue( 2 ) == (doubleFib)(2.2) ){
	
		cout<<"The 2'th element of the "<<
			"checksumvector is correctly 2.2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is "<<
			vecChecksum.getValue( 2 )<<" and not 2.2 . "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the checksumvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is an variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecChecksum.setValue( 2, 0.7 )"<<endl;
	if ( vecChecksum.setValue( 2, 0.7 ) ){
	
		cout<<"The 2'th element of the checksumvector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecChecksum.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"checksumvector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is "<<
			vecChecksum.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the checksumvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is an variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecChecksum.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"checksumvector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is "<<
			vecChecksum.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the checksumvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is an variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecChecksum.setValue( 1, 11 )"<<endl;
	if ( vecChecksum.setValue( 1, 11 ) ){
	
		cout<<"The 1'th element of the checksumvector is set. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecChecksum.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getValue( 1 ) == (doubleFib)(11) ){
	
		cout<<"The 1'th element of the "<<
			"checksumvector is correctly 11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is "<<
			vecChecksum.getValue( 1 )<<" and not 11 . "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the checksumvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is an variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecChecksum.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"checksumvector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is "<<
			vecChecksum.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the checksumvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is an variable . "<<endl;
		iReturn++;
	}

	cout<<"vecChecksum.setValue( 0, 2.2 )"<<endl;
	if ( ! vecChecksum.setValue( 0, 2.2 ) ){
	
		cout<<"The 0'th element of the checksumvector could correctly not set. "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the checksumvector is was set. "<<endl;
		iReturn++;
	}
	cout<<"vecChecksum.setValue( 4, 2.2 )"<<endl;
	if ( ! vecChecksum.setValue( 4, 2.2 ) ){
	
		cout<<"The 0'th element of the checksumvector could correctly not set. "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the checksumvector is was set. "<<endl;
		iReturn++;
	}
	if ( ! vecChecksum.isVariable( 0 ) ){
	
		cout<<"The 0'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getValue( 0 ) == (doubleFib)(0.0) ){
	
		cout<<"The 0'th element of the "<<
			"checksumvector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the checksumvector is "<<
			vecChecksum.getValue( 2 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getVariable( 0 ) == NULL ){
	
		cout<<"The 0'th element of the checksumvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the checksumvector is an variable . "<<endl;
		iReturn++;
	}
	if ( ! vecChecksum.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getValue( 4 ) == (doubleFib)(0.0) ){
	
		cout<<"The 0'th element of the "<<
			"checksumvector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the checksumvector is "<<
			vecChecksum.getValue( 4 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getVariable( 4 ) == NULL ){
	
		cout<<"The 4'th element of the checksumvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the checksumvector is an variable . "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setVariable() method"<<endl;
	
	//creat defined variables to set them later in the vector
	cout<<"emptyRoot.setNumberOfInputVariables( 6 )"<<endl;
	bool bVariableSet = emptyRoot.setNumberOfInputVariables( 6 );
	if ( bVariableSet ){
	
		cout<<"1 variables are set for the root -element. "<<endl;
	}else{
		cerr<<"Error: 1 variables are not set for the root -element. "<<endl;
		iReturn++;
	}
	//check if the variables are created
	for ( unsignedIntFib uiActualVariable = 1;
			uiActualVariable <= emptyRoot.getNumberOfInputVariables();
			uiActualVariable++ ){

		cFibVariable * pVariable = emptyRoot.getInputVariable( uiActualVariable );
		if ( pVariable ){
		
			cout<<"Could get variable "<<uiActualVariable<<
				"'th from the root -element emptyRoot. "<<endl;
		}else{
			cerr<<"Error: Couldn't get variable "<<uiActualVariable<<
				"'th from the root -element emptyRoot.  "<<endl;
			iReturn++;
		}
	}

	cout<<endl<<"pVariable1 = emptyRoot.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = emptyRoot.getInputVariable( 1 );
	cout<<endl<<"vecChecksum.setVariable( 1, pVariable1 )"<<endl;
	if ( ! vecChecksum.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the checksumvector correctly couldn't set to a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is set to a variable. "<<endl;
		iReturn++;
	}
	cout<<endl<<"vecChecksum.setVariable( 2, pVariable1 )"<<endl;
	if ( ! vecChecksum.setVariable( 2, pVariable1 ) ){
	
		cout<<"The 2'th element of the checksumvector correctly couldn't set to a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is set to a variable. "<<endl;
		iReturn++;
	}
	cout<<endl<<"vecChecksum.setVariable( 3, pVariable1 )"<<endl;
	if ( ! vecChecksum.setVariable( 3, pVariable1 ) ){
	
		cout<<"The 3'th element of the checksumvector correctly couldn't set to a variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the checksumvector is set to a variable. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecChecksum.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getValue( 1 ) == (doubleFib)(11) ){
	
		cout<<"The 1'th element of the "<<
			"checksumvector is correctly 11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is "<<
			vecChecksum.getValue( 1 )<<" and not 11 . "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the checksumvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the checksumvector is an variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecChecksum.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"checksumvector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is "<<
			vecChecksum.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the checksumvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the checksumvector is an variable . "<<endl;
		iReturn++;
	}

	cout<<"vecChecksum.setVariable( 0, pVariable1 )"<<endl;
	if ( ! vecChecksum.setVariable( 0, pVariable1 ) ){

		cout<<"The 0'th element of the checksumvector could correctly not set to a variable. "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the checksumvector is was set to a variable. "<<endl;
		iReturn++;
	}
	cout<<"vecChecksum.setVariable( 4, pVariable1 )"<<endl;
	if ( ! vecChecksum.setVariable( 4, pVariable1 ) ){

		cout<<"The 4'th element of the checksumvector could correctly not set to a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the checksumvector is was set to a variable. "<<endl;
		iReturn++;
	}
	if ( ! vecChecksum.isVariable( 0 ) ){
	
		cout<<"The 0'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getValue( 0 ) == (doubleFib)(0.0) ){
	
		cout<<"The 0'th element of the "<<
			"checksumvector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the checksumvector is "<<
			vecChecksum.getValue( 2 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getVariable( 0 ) == NULL ){
	
		cout<<"The 0'th element of the checksumvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the checksumvector is an variable . "<<endl;
		iReturn++;
	}
	if ( ! vecChecksum.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the checksumvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the checksumvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getValue( 4 ) == (doubleFib)(0.0) ){
	
		cout<<"The 0'th element of the "<<
			"checksumvector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the checksumvector is "<<
			vecChecksum.getValue( 4 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecChecksum.getVariable( 4 ) == NULL ){
	
		cout<<"The 4'th element of the checksumvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the checksumvector is an variable . "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing replaceVariable() and isUsedVariable() methods"<<endl;
	
	cout<<endl<<"pVariable2 = emptyRoot.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = emptyRoot.getInputVariable( 2 );
	
	//check vecChecksum.isUsedVariable()
	if ( ! vecChecksum.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	
	//check vecChecksum.isUsedVariable()
	if ( ! vecChecksum.isUsedVariable( NULL ) ){
	
		cout<<"The NULL is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The NULL is a used varible in the vector.  "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecChecksum.replaceVariable( pVariable1, pVariable2 )"<<endl;
	if ( vecChecksum.replaceVariable( pVariable1, pVariable2 ) ){
	
		cout<<"Can correctly replace pVariable1 of the checksumvector with pVariable2. "<<endl;
	}else{
		cerr<<"Error: Can't replace pVariable1 of the checksumvector with pVariable2. "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecChecksum.replaceVariable( NULL, pVariable2 )"<<endl;
	if ( ! vecChecksum.replaceVariable( NULL, pVariable2 ) ){
	
		cout<<"Can't correctly replace NULL of the checksumvector with pVariable2. "<<endl;
	}else{
		cerr<<"Error: Can replace NULL of the checksumvector with pVariable2. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecChecksum.replaceVariable( pVariable2, NULL )"<<endl;
	if ( ! vecChecksum.replaceVariable( pVariable2, NULL ) ){
	
		cout<<"Can't correctly replace pVariable2 of the checksumvector with NULL. "<<endl;
	}else{
		cerr<<"Error: Can replace pVariable2 of the checksumvector with NULL. "<<endl;
		iReturn++;
	}


	return iReturn;
}



/**
 * This method tests the equal() method and the operator== of two given
 * cFibVectors objects which are equal.
 *
 * @param vector1 the first vector to compare
 * @param szNameVector1 the name of the first vector to compare
 * @param vector2 the secound vector to compare to
 * @param szNameVector2 the name of the secound vector to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualVectors( const cFibVector & vector1, const string & szNameVector1,
	const cFibVector & vector2, const string & szNameVector2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( vector1.equal( vector2 ) ){
	
		cout<<"The "<<szNameVector1<<" is equal to "<<szNameVector2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVector1<<" is not equal to "<<
			szNameVector2<<"."<<endl;
		iReturn++;
	}
	if ( vector1 == vector2 ){
	
		cout<<"The "<<szNameVector1<<" is equal (operator==) to "<<
			szNameVector2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVector1<<" is not equal (operator==) to "<<
			szNameVector2<<"."<<endl;
		iReturn++;
	}
	
	if ( ! (vector1 != vector2) ){
	
		cout<<"The "<<szNameVector1<<" is not not equal (operator!=) to "<<
			szNameVector2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVector1<<" is not equal (operator!=) to "<<
			szNameVector2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}

/**
 * This method tests the equal() method and the operator== of two given
 * cFibVectors objects which are not equal.
 *
 * @param vector1 the first vector to compare
 * @param szNameVector1 the name of the first vector to compare
 * @param vector2 the secound vector to compare to
 * @param szNameVector2 the name of the secound vector to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualVectors( const cFibVector & vector1, const string & szNameVector1,
	const cFibVector & vector2, const string & szNameVector2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! vector1.equal( vector2 ) ){
	
		cout<<"The "<<szNameVector1<<" is not equal to "<<szNameVector2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVector1<<" is equal to "<<
			szNameVector2<<"."<<endl;
		iReturn++;
	}
	if ( ! (vector1 == vector2) ){
	
		cout<<"The "<<szNameVector1<<" is not equal (operator==) to "<<
			szNameVector2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVector1<<" is equal (operator==) to "<<
			szNameVector2<<"."<<endl;
		iReturn++;
	}
	
	if ( vector1 != vector2 ){
	
		cout<<"The "<<szNameVector1<<" is not equal (operator!=) to "<<
			szNameVector2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVector1<<" is equal (operator!=) to "<<
			szNameVector2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the equal() method and the operator== of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equal method and the operator== "<<endl;

	cout<<endl<<"creating vectors to compare:"<<endl<<endl;
	
	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;
	
	//creat defined variables to set them later in the vector
	cout<<"emptyRoot.setNumberOfInputVariables( 2 )"<<endl;
	emptyRoot.setNumberOfInputVariables( 2 );

	cout<<"cRoot rootChecksum;"<<flush<<endl;
	cRoot rootChecksum;
	
	cout<<"cTypeProperty typeChecksum( cTypeProperty::CHECKSUM );"<<endl;
	cTypeProperty typeChecksum( cTypeProperty::CHECKSUM );

	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3( 3 );
	cout<<"vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE3( vecDomainsE3 );"<<endl;
	cDomainVector vectorDomainE3( vecDomainsE3 );
	delete vecDomainsE3[ 0 ];
	delete vecDomainsE3[ 1 ];
	delete vecDomainsE3[ 2 ];

	cout<<"rootChecksum.getDomains()->addDomain( typeChecksum, vectorDomainE3);"<<endl;
	rootChecksum.getDomains()->addDomain( typeChecksum, vectorDomainE3);


	//create cVectorChecksums to compare
	cout<<"cVectorChecksum vectorChecksumRe( &emptyRoot );"<<endl;
	cVectorChecksum vectorChecksumRe( &emptyRoot );
	cout<<"cVectorChecksum vectorChecksumRD2( &rootChecksum );"<<endl;
	cVectorChecksum vectorChecksumRD2( &rootChecksum );
	cout<<"cVectorChecksum vectorChecksumE3;"<<endl;
	cVectorChecksum vectorChecksumE3;
	
	//vectors with changed values
	cout<<"cVectorChecksum vectorChecksumE3V2g17p2;"<<endl;
	cVectorChecksum vectorChecksumE3V2g17p2;
	vectorChecksumE3V2g17p2.setValue( 2, 17.2 );
	
	cout<<"cVectorChecksum vectorChecksumRD2V2g17p2( &rootChecksum );"<<endl;
	cVectorChecksum vectorChecksumRD2V2g17p2( &rootChecksum );
	vectorChecksumRD2V2g17p2.setValue( 2, 17.2 );

	cout<<"cVectorChecksum vectorChecksumRD2V2g17p2001( &rootChecksum );"<<endl;
	cVectorChecksum vectorChecksumRD2V2g17p2001( &rootChecksum );
	vectorChecksumRD2V2g17p2001.setValue( 2, 17.2001 );

	cout<<"cVectorChecksum vectorChecksumRD2V1g17p2( &rootChecksum );"<<endl;
	cVectorChecksum vectorChecksumRD2V1g17p2( &rootChecksum );
	vectorChecksumRD2V1g17p2.setValue( 1, 17.2 );

	cout<<"cVectorChecksum vectorChecksumRD2V1g1p1V2gm2p2;"<<endl;
	cVectorChecksum vectorChecksumRD2V1g1p1V2gm2p2;
	vectorChecksumRD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorChecksumRD2V1g1p1V2gm2p2.setValue( 2, -2.2 );

	cout<<"cVectorChecksum vectorChecksumD2RD2V1g1p1V2gm2p2( &rootChecksum );"<<endl;
	cVectorChecksum vectorChecksumD2RD2V1g1p1V2gm2p2( &rootChecksum );
	vectorChecksumD2RD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorChecksumD2RD2V1g1p1V2gm2p2.setValue( 2, -2.2 );
	
	cout<<"cVectorChecksum vectorChecksumRD2V1g1p1V2g2p2( &rootChecksum );"<<endl;
	cVectorChecksum vectorChecksumRD2V1g1p1V2g2p2( &rootChecksum );
	vectorChecksumRD2V1g1p1V2g2p2.setValue( 1, 1.1 );
	vectorChecksumRD2V1g1p1V2g2p2.setValue( 2, 2.2 );
	
	cout<<"cVectorChecksum vectorChecksumRD2V1g1p1V2g2p2V3g3p3( &rootChecksum );"<<endl;
	cVectorChecksum vectorChecksumRD2V1g1p1V2g2p2V3g3p3( &rootChecksum );
	vectorChecksumRD2V1g1p1V2g2p2V3g3p3.setValue( 1, 1.1 );
	vectorChecksumRD2V1g1p1V2g2p2V3g3p3.setValue( 2, 2.2 );
	vectorChecksumRD2V1g1p1V2g2p2V3g3p3.setValue( 2, 3.3 );

	cout<<"cVectorProperty vectorPropertyColorRgb( 1 );"<<endl;
	cVectorProperty vectorPropertyColorRgb( 1 );
	
	cout<<"cVectorProperty vectorPropertyColorRgbE4( 1, 4 );"<<endl;
	cVectorProperty vectorPropertyColorRgbE4( 1 , 4 );

	cout<<"cVectorPosition vectorPosition( 1 );"<<endl;
	cVectorPosition vectorPosition( 1 );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with vectorChecksumRe
	cFibVector * actualVector = &vectorChecksumRe;
	string szActualVectorName = "vectorChecksumRe";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorChecksumRD2
	actualVector = &vectorChecksumRD2;
	szActualVectorName = "vectorChecksumRD2";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorChecksumE3
	actualVector = &vectorChecksumE3;
	szActualVectorName = "vectorChecksumE3";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorChecksumE3V2g17p2
	actualVector = &vectorChecksumE3V2g17p2;
	szActualVectorName = "vectorChecksumE3V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorChecksumRD2V2g17p2
	actualVector = &vectorChecksumRD2V2g17p2;
	szActualVectorName = "vectorChecksumRD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorChecksumRD2V2g17p2001
	actualVector = &vectorChecksumRD2V2g17p2001;
	szActualVectorName = "vectorChecksumRD2V2g17p2001";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorChecksumRD2V1g17p2
	actualVector = &vectorChecksumRD2V1g17p2;
	szActualVectorName = "vectorChecksumRD2V1g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorChecksumRD2V1g1p1V2gm2p2
	actualVector = &vectorChecksumRD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorChecksumRD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorChecksumD2RD2V1g1p1V2gm2p2
	actualVector = &vectorChecksumD2RD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorChecksumD2RD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorChecksumRD2V1g1p1V2g2p2
	actualVector = &vectorChecksumRD2V1g1p1V2g2p2;
	szActualVectorName = "vectorChecksumRD2V1g1p1V2g2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorChecksumRD2V1g1p1V2g2p2V3g3p3
	actualVector = &vectorChecksumRD2V1g1p1V2g2p2V3g3p3;
	szActualVectorName = "vectorChecksumRD2V1g1p1V2g2p2V3g3p3";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyColorRgb
	actualVector = &vectorPropertyColorRgb;
	szActualVectorName = "vectorPropertyColorRgb";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPosition
	actualVector = &vectorPosition;
	szActualVectorName = "vectorPosition";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyColorRgbE4
	actualVector = &vectorPropertyColorRgbE4;
	szActualVectorName = "vectorPropertyColorRgbE4";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRe, "vectorChecksumRe" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2, "vectorChecksumRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3, "vectorChecksumE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumE3V2g17p2, "vectorChecksumE3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2, "vectorChecksumRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V2g17p2001, "vectorChecksumRD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g17p2, "vectorChecksumRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2gm2p2, "vectorChecksumRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumD2RD2V1g1p1V2gm2p2, "vectorChecksumD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2, "vectorChecksumRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorChecksumRD2V1g1p1V2g2p2V3g3p3, "vectorChecksumRD2V1g1p1V2g2p2V3g3p3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgb, "vectorPropertyColorRgb" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );


	return iReturn;
}



/**
 * This method tests the createInstance() method of the cVectorChecksum class.
 *
 * methods tested:
 * 	- createInstance()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCreateInstance( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a chcksumvector"<<endl;

	cout<<"cRoot rootChecksum;"<<flush<<endl;
	cRoot rootChecksum;
	
	cout<<"cTypeProperty typeChecksum( cTypeProperty::CHECKSUM );"<<endl;
	cTypeProperty typeChecksum( cTypeProperty::CHECKSUM );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3( 3 );
	cout<<"vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainD2( vecDomainsE3 );"<<endl;
	cDomainVector vectorDomainE3( vecDomainsE3 );
	delete vecDomainsE3[ 0 ];
	delete vecDomainsE3[ 1 ];
	delete vecDomainsE3[ 2 ];

	cout<<"rootChecksum.getDomains()->addDomain( typeChecksum, vectorDomainE3);"<<endl;
	rootChecksum.getDomains()->addDomain( typeChecksum, vectorDomainE3);
	
	cout<<"cVectorChecksum vecChecksum1RootChecksum1( &rootChecksum );"<<endl;
	cVectorChecksum vecChecksum1RootChecksum1( &rootChecksum );

	cout<<"cFibVector * vectorInstanceE3 = vecChecksum1RootChecksum1.createInstance( );"<<endl;
	cFibVector * vectorInstanceE3 = vecChecksum1RootChecksum1.createInstance();

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorChecksum
	if ( vectorInstanceE3->getVectorType() == "property.checksum" ){
	
		cout<<"The name of the checksumvector is correctly \"property.checksum\" . "<<endl;
	}else{
		cerr<<"Error: The name of the checksumvector is "<<
			vectorInstanceE3->getVectorType()<<" but should be \"property.checksum\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorChecksum
	cTypeElement * pTypeProperty = vectorInstanceE3->getElementType();
	if ( typeChecksum == (*pTypeProperty) ){
	
		cout<<"The type of the checksumvector is correctly equal to typeChecksum2. "<<endl;
	}else{
		cerr<<"Error: The type of checksumvector not equal to typeChecksum2 ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorChecksum
	if ( vectorInstanceE3->getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the checksumvector is "<<
			vectorInstanceE3->getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceE3->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceE3->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceE3->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is "<<vectorInstanceE3->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vectorInstanceE3->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the checksumvector."<<endl;
	}else if ( &rootChecksum == vectorInstanceE3->getDefiningFibElement() ){
	
		cerr<<"Error: The rootChecksum is the defining element for the checksumvector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is an defining element for the checksumvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorChecksum
	if ( vectorInstanceE3->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the checksumvector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the checksumvector."<<endl;
		iReturn++;
	}
	delete vectorInstanceE3;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with rootChecksum as an defining element"<<endl;

	cout<<"cFibVector * vectorInstanceE2RD2 = vecChecksum1RootChecksum1.createInstance( &rootChecksum );"<<endl;
	cFibVector * vectorInstanceE2RD2 = vecChecksum1RootChecksum1.createInstance( &rootChecksum );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorChecksum
	if ( vectorInstanceE2RD2->getVectorType() == "property.checksum" ){
	
		cout<<"The name of the checksumvector is correctly \"property.checksum\" . "<<endl;
	}else{
		cerr<<"Error: The name of the checksumvector is "<<
			vectorInstanceE2RD2->getVectorType()<<" but should be \"property.checksum\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorChecksum
	pTypeProperty = vectorInstanceE2RD2->getElementType();
	if ( typeChecksum == (*pTypeProperty) ){
	
		cout<<"The type of the checksumvector is correctly equal to typeChecksum. "<<endl;
	}else{
		cerr<<"Error: The type of checksumvector not equal to typeChecksum ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorChecksum
	if ( vectorInstanceE2RD2->getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the checksumvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the checksumvector is "<<
			vectorInstanceE2RD2->getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceE2RD2->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceE2RD2->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceE2RD2->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"checksumvector is "<<vectorInstanceE2RD2->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorChecksum
	if ( vectorInstanceE2RD2->getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the checksumvector."<<endl;
		iReturn++;	
	}else if ( &rootChecksum == vectorInstanceE2RD2->getDefiningFibElement() ){
	
		cout<<"The rootChecksum is the defining element for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The rootChecksum is not the defining element for the checksumvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorChecksum
	if ( vectorInstanceE2RD2->getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the checksumvector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3 == (*(vectorInstanceE2RD2->getDomain())) ){
	
		cout<<"The vectorDomainE3 is the domain for the checksumvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the checksumvector."<<endl;
		iReturn++;
	}
	delete vectorInstanceE2RD2;


	return iReturn;
}


/**
 * This method tests a in the xml -format stored cFibVector.
 *
 * @param szFilename the name of the file wher the cFibVector is stored
 * @param szVectorType the name of the type for the vector
 * @param uiVectorElements the number of elements in the vector
 * @param vecElementType a vector with the typs of the vectorelements
 * 	(w=value; v=variable)
 * @param vecValues the values of the vectorelements
 * @return the number of errors occured in the test
 */
int testXmlVector( const string szFilename, const string szVectorType,
		unsigned int uiVectorElements, vector<char> vecElementType,
		vector<double> vecValues ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored vector:"<<endl;
	
	TiXmlDocument xmlDocVectorChecksum( szFilename );
	bool loadOkay = xmlDocVectorChecksum.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorChecksum );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();

		if ( szElementName == "vector" ){
			cout<<"The root element is correctly named \"vector\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"vector\"."<<endl;
			iReturn++;
		}
		const char * szVectorXmlType = pXmlElement->Attribute( "type" );
		
		if ( szVectorXmlType == NULL ){
			cerr<<"Error: The vector has no type."<<endl;
			iReturn++;
		}else if ( szVectorType == szVectorXmlType ) {
			cout<<"The type of the vector is correctly \""<< szVectorType <<"\". "<<endl;
		}else{
			cerr<<"Error: The type of the vector is \""<< szVectorXmlType
				<<"\", but should be \""<< szVectorType <<"\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	xmlHandleRoot = TiXmlHandle( pXmlElement );
	pXmlElement = xmlHandleRoot.FirstChild().Element();
	
	if ( uiVectorElements != 0 ){
		if ( pXmlElement == NULL ){
			cerr<<"Error: No elements in this vector."<<endl;
			iReturn++;
			return iReturn;
		}
	}else{
		if ( pXmlElement != NULL ){
			cerr<<"Error: Ther are elements in this vector, but it shouldn't hafe some."<<endl;
			iReturn++;
		}
	}
	int iReadedNumberOfElement = 0;
	for( int iNumberOfElement = 1; pXmlElement;
			pXmlElement = pXmlElement->NextSiblingElement(), iNumberOfElement++ ){
	
		string szElementName = pXmlElement->Value();
		
		if ( pXmlElement->Attribute( "number", & iReadedNumberOfElement ) ){
			iNumberOfElement = iReadedNumberOfElement;
			
			cout<<"Reading the "<< iNumberOfElement <<"'th numbert element of the type "<<
				szElementName <<" . "<<endl;
		}else{
			cout<<"Reading the "<< iNumberOfElement <<"'th element of the type "<<
				szElementName <<" . "<<endl;
		}
		
		//the elementtype the actual element should have
		string szTargetElementType( "non" );
		
		if ( iNumberOfElement < 1 ){
			cerr<<"Error: Ther couldn't be a 0'th vectorelement."<<endl;
			iReturn++;
		}else if ( (int)(uiVectorElements) < iNumberOfElement ){
			cerr<<"Error: Ther couldn't be a "<< iNumberOfElement <<
				"'th vectorelement, because the vector has yust "<<
					uiVectorElements <<" elements."<<endl;
			iReturn++;
		}else{
			switch ( vecElementType[ iNumberOfElement-1 ] ){
				case 'w': 
					szTargetElementType = "value";
				break;
				case 'v': 
					szTargetElementType = "variable";
				break;
			}
		}
		
		if ( szTargetElementType != szElementName ){
			cerr<<"Error: The element is of type \""<< szElementName <<
				"\", but should be of the type \""<<  szTargetElementType <<"\"."<<endl;
			iReturn++;
		}
		
		if ( szElementName == "value" ){
			const char * pcValue = pXmlElement->GetText();
			cout<<"The value of the element is: "<< pcValue <<endl;
			//converting value to double
			if ( (1 <= iNumberOfElement) && ( iNumberOfElement <= (int)(uiVectorElements) ) ){
				double dValue1 = 0.0;
				int iReadValues = sscanf ( pcValue, "%lf", & dValue1 );
				
				long long lMantissa = 0;
				long long lExponent = 0;
#ifdef WINDOWS
				sscanf( pcValue, "%I64d * 2^(%I64d", & lMantissa, & lExponent );
#else //WINDOWS
				sscanf( pcValue, "%lld * 2^(%lld", & lMantissa, & lExponent );
#endif //WINDOWS
				
				//mantissa and exponent readed
				double dValue2 = ((doubleFib)lMantissa) * pow( 2.0, (doubleFib)lExponent );

				if ( iReadValues != 0){
					if ( compareDoubleFib(dValue1, vecValues[ iNumberOfElement - 1 ]) ||
							compareDoubleFib(dValue2, vecValues[ iNumberOfElement - 1 ]) ){
						cout<<"The value of the element is correct."<<endl;
					}else{
						cerr<<"Error: The value of the element should be : "<<
							vecValues[ iNumberOfElement - 1 ] <<endl;
						iReturn++;
					}
				}else{
					cerr<<"Error: The element text is not a number."<<endl;
					iReturn++;
				}
			}//else can't compare with a value
		
		}else if ( szElementName == "variable" ){
		
			const char * pcValue = pXmlElement->GetText();
			cout<<"The variablenumber of the element is: "<< pcValue <<endl;
			//converting value to integer
			if ( (1 <= iNumberOfElement) && ( iNumberOfElement <= (int)(uiVectorElements) ) ){
				long lValue;
				int iReadValues = sscanf ( pcValue, "%ld", & lValue );
				if ( iReadValues != 0){
					if ( (double)(lValue) == vecValues[ iNumberOfElement - 1 ] ){
						cout<<"The variablenumber of the element is correct."<<endl;
					}else{
						cerr<<"Error: The variablenumber of the element should be : "<<
							vecValues[ iNumberOfElement - 1 ] <<endl;
						iReturn++;
					}
				}else{
					cerr<<"Error: The element text is not a number."<<endl;
					iReturn++;
				}
			}//else can't compare with a value

		}else{
			cerr<<"Error: Unknown element type."<<endl;
			iReturn++;
		}
	}

	return iReturn;
}


/**
 * This method tests the storeXml() method of the cVectorChecksum class.
 *
 * methods tested:
 * 	- storeXml()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreXml( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an empty 3 d checksumvector"<<endl;
	
	cout<<"cRoot rootChecksum;"<<flush<<endl;
	cRoot rootChecksum;
	
	cout<<"cTypeProperty typeChecksum( cTypeProperty::CHECKSUM );"<<endl;
	cTypeProperty typeChecksum( cTypeProperty::CHECKSUM );

	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3( 3 );
	cout<<"vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE3( vecDomainsE3 );"<<endl;
	cDomainVector vectorDomainE3( vecDomainsE3 );
	delete vecDomainsE3[ 0 ];
	delete vecDomainsE3[ 1 ];
	delete vecDomainsE3[ 2 ];
	
	cout<<"rootChecksum.getDomains()->addDomain( typeChecksum, &vectorDomainE3 );"<<endl;
	rootChecksum.getDomains()->addDomain( typeChecksum, &vectorDomainE3 );

	cout<<"cVectorChecksum vecChecksum( &rootChecksum );"<<endl;
	cVectorChecksum vecChecksum( &rootChecksum );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecChecksumEmpty.xml" );
	ofstream fileVectorProperty( pFileName );
	
	bool bStoreSuccesfull = vecChecksum.storeXml( fileVectorProperty );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<char> vecElementTypePosition( 5, 'w' );
	vector<double> vecValuesPosition( 5, 0.0 );
	
	iReturn += testXmlVector( pFileName, "property.checksum",
		3, vecElementTypePosition, vecValuesPosition );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an checksumvector with one value set"<<endl;
	
	cout<<"vecChecksum.setValue( 1, 111 )"<<endl;
	vecChecksum.setValue( 1, 111 );
	vecElementTypePosition[0] = 'w';
	vecValuesPosition[0] = 111;
	
	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecChecksumV1g111.xml" );
	ofstream fileVectorPropertyRD3V1g111n( pFileName );
	
	bStoreSuccesfull = vecChecksum.storeXml( fileVectorPropertyRD3V1g111n );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( pFileName, "property.checksum",
		3, vecElementTypePosition, vecValuesPosition );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an checksumvector with all value set"<<endl;
	
	cout<<"vecChecksum.setValue( 2, 123.456 )"<<endl;
	vecChecksum.setValue( 2, 123.456  );
	vecElementTypePosition[1] = 'w';
	vecValuesPosition[1] = 123.456;
	cout<<"vecChecksum.setValue( 3, -123.456 )"<<endl;
	vecChecksum.setValue( 3, -123.456 );
	vecElementTypePosition[2] = 'w';
	vecValuesPosition[2] = -123.456;

	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorChecksumE3T3.xml" );
	ofstream fileVectorPropertyRD3T3( pFileName );
	
	bStoreSuccesfull = vecChecksum.storeXml( fileVectorPropertyRD3T3 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szFileNameBuffer, "property.checksum",
		3, vecElementTypePosition, vecValuesPosition );


	return iReturn;
}



/**
 * This method tests the assignment method of the class.
 *
 * methods tested:
 * 	-operator=( const cFibVector &vector ) 
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testAssignment( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the operator=() method on an checksumvector with values set"<<endl;

	cout<<"cVectorChecksum vecChecksumDestination;"<<endl;
	cVectorChecksum vecChecksumDestination;
	
	cout<<"cVectorChecksum vectorChecksumValue;"<<endl;
	cVectorChecksum vectorChecksumValue;
	cout<<"vectorChecksumValue.setValue( 1, 1 );"<<endl;
	vectorChecksumValue.setValue( 1, 1 );
	cout<<"vectorChecksumValue.setValue( 2, 2 );"<<endl;
	vectorChecksumValue.setValue( 2, 2 );
	cout<<"vectorChecksumValue.setValue( 3, 3 );"<<endl;
	vectorChecksumValue.setValue( 3, 3 );
	
	cout<<"vecChecksumDestination = vectorChecksumValue;"<<endl;
	vecChecksumDestination = vectorChecksumValue;
	
	if ( vecChecksumDestination == vectorChecksumValue ){
	
		cout<<"The vecChecksumDestination is equal to the vectorChecksumValue . "<<endl;
	}else{
		cerr<<"Error: The vecChecksumDestination is not equal to the vectorChecksumValue ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the operator=() method on an checksumvector with variables set"<<endl;

	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;
	
	//creat defined variables to set them later in the vector
	cout<<"emptyRoot.setNumberOfInputVariables( 3 )"<<endl;
	emptyRoot.setNumberOfInputVariables( 3 );
	cFibVariable * pVariable1 = emptyRoot.getInputVariable( 1 );
	cFibVariable * pVariable2 = emptyRoot.getInputVariable( 2 );
	cFibVariable * pVariable3 = emptyRoot.getInputVariable( 3 );

	cout<<"cVectorChecksum vectorChecksumVariables( &emptyRoot );"<<endl;
	cVectorChecksum vectorChecksumVariables( &emptyRoot );
	cout<<"vectorChecksumVariables.setVariable( 1, pVariable1 );"<<endl;
	vectorChecksumVariables.setVariable( 1, pVariable1 );
	cout<<"vectorChecksumVariables.setVariable( 2, pVariable2 );"<<endl;
	vectorChecksumVariables.setVariable( 2, pVariable2 );
	cout<<"vectorChecksumVariables.setVariable( 3, pVariable3 );"<<endl;
	vectorChecksumVariables.setVariable( 3, pVariable3 );

	cout<<"vecChecksumDestination = vectorChecksumVariables;"<<endl;
	vecChecksumDestination = vectorChecksumVariables;
	
	if ( vecChecksumDestination == vectorChecksumVariables ){
	
		cout<<"The vecChecksumDestination is equal to the vectorChecksumVariables . "<<endl;
	}else{
		cerr<<"Error: The vecChecksumDestination is not equal to the vectorChecksumVariables ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the operator=() method on an position vector with 4 elements"<<endl;

	//creat defined variables to set them later in the vector
	cout<<"cVectorPosition vectorPositionD4( 4 );"<<endl;
	cVectorPosition vectorPositionD4( 4 );
	cout<<"vectorPositionD4.setValue( 1, 5 );"<<endl;
	vectorPositionD4.setValue( 1, 5 );
	cout<<"vectorPositionD4.setValue( 2, 2 );"<<endl;
	vectorPositionD4.setValue( 2, 2 );
	cout<<"vectorPositionD4.setValue( 3, 6 );"<<endl;
	vectorPositionD4.setValue( 3, 6 );
	cout<<"vectorPositionD4.setValue( 4, 7 );"<<endl;
	vectorPositionD4.setValue( 4, 7 );

	cout<<"cVectorChecksum vectorChecksumValues2;"<<endl;
	cVectorChecksum vectorChecksumValues2;
	cout<<"vectorChecksumValues2.setValue( 1, 5 );"<<endl;
	vectorChecksumValues2.setValue( 1, 5 );
	cout<<"vectorChecksumValues2.setValue( 2, 2 );"<<endl;
	vectorChecksumValues2.setValue( 2, 2 );
	cout<<"vectorChecksumValues2.setValue( 3, 6 );"<<endl;
	vectorChecksumValues2.setValue( 3, 6 );
	
	cout<<"vecChecksumDestination = vectorPositionD4;"<<endl;
	vecChecksumDestination = vectorPositionD4;
	
	if ( vecChecksumDestination != vectorPositionD4 ){
	
		cout<<"The vecChecksumDestination is correctly not equal to the vectorPositionD4 . "<<endl;
	}else{
		cerr<<"Error: The vecChecksumDestination is equal to the vectorPositionD4 ."<<endl;
		iReturn++;
	}

	if ( vecChecksumDestination == vectorChecksumValues2 ){
	
		cout<<"The vecChecksumDestination is equal to the vectorChecksumValues2 . "<<endl;
	}else{
		cerr<<"Error: The vecChecksumDestination is not equal to the vectorChecksumValues2 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the operator=() method on an position vector with 1 element"<<endl;

	//creat defined variables to set them later in the vector
	cout<<"cVectorPosition vectorPositionD1( 1 );"<<endl;
	cVectorPosition vectorPositionD1( 1 );
	cout<<"vectorPositionD1.setValue( 1, 10 );"<<endl;
	vectorPositionD1.setValue( 1, 10 );

	cout<<"vectorChecksumValues2.setValue( 1, 10 );"<<endl;
	vectorChecksumValues2.setValue( 1, 10 );
	cout<<"vectorChecksumValues2.setValue( 2, 0 );"<<endl;
	vectorChecksumValues2.setValue( 2, 0 );
	cout<<"vectorChecksumValues2.setValue( 3, 0 );"<<endl;
	vectorChecksumValues2.setValue( 3, 0 );
	
	cout<<"vecChecksumDestination = vectorPositionD1;"<<endl;
	vecChecksumDestination = vectorPositionD1;
	
	if ( vecChecksumDestination != vectorPositionD1 ){
	
		cout<<"The vecChecksumDestination is correctly not equal to the vectorPositionD1 . "<<endl;
	}else{
		cerr<<"Error: The vecChecksumDestination is equal to the vectorPositionD1 ."<<endl;
		iReturn++;
	}

	if ( vecChecksumDestination == vectorChecksumValues2 ){
	
		cout<<"The vecChecksumDestination is equal to the vectorChecksumValues2 . "<<endl;
	}else{
		cerr<<"Error: The vecChecksumDestination is not equal to the vectorChecksumValues2 ."<<endl;
		iReturn++;
	}


	return iReturn;
}














