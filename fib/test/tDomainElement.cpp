/**
 * @file tDomainElement
 * file name: tDomainElement.cpp
 * @author Betti Oesterholz
 * @date 07.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cDomainElement.
 *
 * Copyright (C) @c GPL3 2009  Betti Oesterholz
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
 * This file contains the test for the class cDomainElement,
 * which represents an domainelement of an domain list in an root -element.
 *
 *
 *  What's tested of class cDomainElement:
 * 	- cDomainElement( const cTypeElement &typeElement, const cDomain *domain=NULL );
 * 	- cDomainElement( const cTypeElement &typeElement, const cDomain & domain );
 * 	- cDomainElement( const cDomainElement &domainElement );
 * 	- ~cDomainElement();
 * 	- cTypeElement * getElementType() const;
 * 	- cDomain * getDomain() const;
 * 	- bool setDomain( const cDomain &domain );
 * 	- bool setDomain( cDomain * domain );
 * 	- bool storeXml( ostringstream & ostream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 *
 */
/*
History:
07.06.2009  Oesterholz  created
12.11.2009  Oesterholz  store*() and getCompressedSize() tested
13.05.2010  Oesterholz  the ordering of bits for the compressed storing corrected
30.03.2011  Oesterholz  storing to binary stream
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
28.01.2013  Oesterholz  COLOR_SW changed to COLOR_GRAYSCALE
*/

#include "version.h"

#include "cDomainElement.h"
#include "cTypeDimension.h"
#include "cTypeProperty.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iomanip>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif

using namespace fib;
using namespace std;


int testCostructorSetDomain( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );

int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cDomainElement methods"<<endl;
	cout<<      "======================================="<<endl;
	
	iReturn += testCostructorSetDomain( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );

	if ( iReturn==0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * This method tests the constructors and the setDomain()
 * methods of the cDomainElement class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCostructorSetDomain( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing an simple domain element"<<endl;

	cTypeDimension testTypeDimension;

	//create vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 2 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 4 );
	cDomainVector vectorDomain1D2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	
	//check construktor
	cout<<"cDomainElement domainElement1( testTypeDimension, &vectorDomain1D2 );"<<endl;
	cDomainElement domainElement1( testTypeDimension, &vectorDomain1D2 );
	
	//check the isCompatible() methode for cDomainIntegerBasis domains
	if ( *(domainElement1.getElementType()) == testTypeDimension ){
	
		cout<<"The type is correct cTypeDimension. "<<endl;
	}else{
		cerr<<"Error: The type is not correct."<<endl;
		iReturn++;
	}

	cout<<"cDomain * domain = domainElement1.getDomain();"<<endl;
	cDomain * domain = domainElement1.getDomain();
	
	//check if the domainpointer points to the original domain
	if ( domain == &vectorDomain1D2 ){
	
		cout<<"The domain is correctly the vectorDomain1D2 . "<<endl;
	}else{
		cerr<<"Error: The domain is not the domain vectorDomain1D2  ."<<endl;
		iReturn++;
	}
	
	if ( domain == NULL ){
	
		cerr<<"Error: The domain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( domain->getType()=="DomainVector" ){
	
		cout<<"The domain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *domainVector=(cDomainVector*)domain;

		unsignedIntFib uiDomainVectorElements=2;
		
		if ( domainVector->getNumberOfElements() == uiDomainVectorElements ){
		
			cout<<"The domainvector has correctly "<<
				uiDomainVectorElements<<" element. "<<endl;
			
			unsignedIntFib actualElement=1;
			
			//test domain of first vector element
			cDomain *domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=3;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			actualElement=2;
			//test domain of secound vector element
			domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=15;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
		
		
		}else{
			cerr<<"Error: The domain has "<<
				domainVector->getNumberOfElements()<<" elements and not "<<
				uiDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The domain has the type "<<
			domain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
	}

	//test the set domain method
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setDomain() Method on an pointer"<<endl;

	//create vector domain with two elements
	vecDomains2[ 0 ]=new cDomainNaturalNumberBit( 2 );
	vecDomains2[ 1 ]=new cDomainNaturalNumberBit( 4 );
	cDomainVector vectorDomain3D2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];


	//check if getDomain() returns the standarddomain for the type
	cout<<"domainElement1.setDomain( &vectorDomain3D2 );"<<endl;
	domainElement1.setDomain( &vectorDomain3D2 );
	
	//check if getDomain() returns the standarddomain for the type
	cout<<"domain=domainElement1.getDomain();"<<endl;
	domain=domainElement1.getDomain();
	
	//check if the domainpointer points to the original domain
	if ( domain == &vectorDomain3D2 ){
	
		cout<<"The domainpointer is correctly the vectorDomain3D2 domain . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is not the domain vectorDomain3D2  ."<<endl;
		iReturn++;
	}

	if ( domain == NULL ){
	
		cerr<<"Error: The domain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( domain->getType()=="DomainVector" ){
	
		cout<<"The domain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *domainVector=(cDomainVector*)domain;

		unsignedIntFib uiDomainVectorElements=2;
		
		if ( domainVector->getNumberOfElements() == uiDomainVectorElements ){
		
			cout<<"The domainvector has correctly "<<
				uiDomainVectorElements<<" element. "<<endl;
			
			unsignedIntFib actualElement=1;
			
			//test domain of first vector element
			cDomain *domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=3;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			actualElement=2;
			//test domain of secound vector element
			domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=15;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
		
		}else{
			cerr<<"Error: The domain has "<<
				domainVector->getNumberOfElements()<<" elements and not "<<
				uiDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The domain has the type "<<
			domain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
	}
	
	//test the set domain method
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setDomain() Method on an object"<<endl;

	//create vector domain with two elements
	vecDomains2[ 0 ]=new cDomainNaturalNumberBit( 3 );
	vecDomains2[ 1 ]=new cDomainNaturalNumberBit( 1 );
	cDomainVector vectorDomain2D2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];


	//check if getDomain() returns the standarddomain for the type
	cout<<"domainElement1.setDomain( vectorDomain2D2 );"<<endl;
	domainElement1.setDomain( vectorDomain2D2 );
	
	//check if getDomain() returns the standarddomain for the type
	cout<<"domain=domainElement1.getDomain();"<<endl;
	domain=domainElement1.getDomain();
	
	//check if the domainpointer points to the original domain
	if ( domain != &vectorDomain2D2 ){
	
		cout<<"The domainpointer is correctly not the vectorDomain2D2 domain . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is the domain vectorDomain2D2  ."<<endl;
		iReturn++;
	}

	if ( domain==NULL ){
	
		cerr<<"Error: The domain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( domain->getType()=="DomainVector" ){
	
		cout<<"The domain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *domainVector=(cDomainVector*)domain;

		unsignedIntFib uiDomainVectorElements=2;
		
		if ( domainVector->getNumberOfElements() == uiDomainVectorElements ){
		
			cout<<"The domainvector has correctly "<<
				uiDomainVectorElements<<" element. "<<endl;
			
			unsignedIntFib actualElement=1;
			
			//test domain of first vector element
			cDomain *domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=7;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			actualElement=2;
			//test domain of secound vector element
			domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=1;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
		
		}else{
			cerr<<"Error: The domain has "<<
				domainVector->getNumberOfElements()<<" elements and not "<<
				uiDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The domain has the type "<<
			domain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
	}


	//check construktor with the standart value for the secound parameter
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing construktor with the standart value for the secound parameter"<<endl;

	cout<<"cDomainElement domainElement2( testTypeDimension ); "<<endl;
	cDomainElement domainElement2( testTypeDimension );
	
	//check the isCompatible() methode for cDomainIntegerBasis domains
	if ( *(domainElement2.getElementType())==testTypeDimension ){
	
		cout<<"The type is correct cTypeDimension. "<<endl;
	}else{
		cerr<<"Error: The type is not correct."<<endl;
		iReturn++;
	}

	//check if getDomain() returns the standarddomain for the type
	domain=domainElement2.getDomain();
	
	if ( domain==NULL ){
	
		cerr<<"Error: The domain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( domain->getType()=="DomainVector" ){
	
		cout<<"The domain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *domainVector=(cDomainVector*)domain;

		unsignedIntFib uiDomainVectorElements=2;
		
		if ( domainVector->getNumberOfElements() == uiDomainVectorElements ){
		
			cout<<"The domainvector has correctly "<<
				uiDomainVectorElements<<" element. "<<endl;
			
			unsignedIntFib actualElement=1;
			
			//test domain of first vector element
			cDomain *domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=65535;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			actualElement=2;
			//test domain of secound vector element
			domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=65535;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
		
		
		}else{
			cerr<<"Error: The domain has "<<
				domainVector->getNumberOfElements()<<" elements and not "<<
				uiDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The domain has the type "<<
			domain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
	}


	//check construktor with the standart value for the secound parameter
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the copyconstruktor"<<endl;

	cout<<"cDomainElement domainElement3( domainElement1 );"<<endl;
	cDomainElement domainElement3( domainElement1 );
	
	//check the isCompatible() methode for cDomainIntegerBasis domains
	if ( *(domainElement3.getElementType())==testTypeDimension ){
	
		cout<<"The type is correct cTypeDimension. "<<endl;
	}else{
		cerr<<"Error: The type is not correct."<<endl;
		iReturn++;
	}

	//check if getDomain() returns the standarddomain for the type
	cout<<"domain=domainElement3.getDomain();"<<endl;
	domain=domainElement3.getDomain();
	
	//check if the domainpointer points to the original domain
	if ( domain != &vectorDomain2D2 ){
	
		cout<<"The domainpointer is correctly not the vectorDomain2D2 domain . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is the domain vectorDomain2D2  ."<<endl;
		iReturn++;
	}
	
	if ( domain==NULL ){
	
		cerr<<"Error: The domain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( domain->getType()=="DomainVector" ){
	
		cout<<"The domain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *domainVector=(cDomainVector*)domain;

		unsignedIntFib uiDomainVectorElements=2;
		
		if ( domainVector->getNumberOfElements() == uiDomainVectorElements ){
		
			cout<<"The domainvector has correctly "<<
				uiDomainVectorElements<<" element. "<<endl;
			
			unsignedIntFib actualElement=1;
			
			//test domain of first vector element
			cDomain *domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=7;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			actualElement=2;
			//test domain of secound vector element
			domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=1;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
		
		
		}else{
			cerr<<"Error: The domain has "<<
				domainVector->getNumberOfElements()<<" elements and not "<<
				uiDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The domain has the type "<<
			domain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
	}


	//check construktor with the standart value for the secound parameter
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing construktor with the incompatible value for the domain parameter"<<endl;

	cout<<"cDomainNaturalNumberBit domainNaturalNumber13( 13 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumber13( 13 );

	cout<<"cDomainElement domainElement4( testTypeDimension, &domainNaturalNumber13 );"<<endl;
	cDomainElement domainElement4( testTypeDimension, &domainNaturalNumber13 );
	
	//check the isCompatible() methode for cDomainIntegerBasis domains
	if ( *(domainElement4.getElementType())==testTypeDimension ){
	
		cout<<"The type is correct cTypeDimension. "<<endl;
	}else{
		cerr<<"Error: The type is not correct."<<endl;
		iReturn++;
	}

	//check if getDomain() returns the standarddomain for the type
	cout<<"domain=domainElement4.getDomain();"<<endl;
	domain=domainElement4.getDomain();
	
	if ( domain==NULL ){
	
		cerr<<"Error: The domain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( domain->getType()=="DomainVector" ){
	
		cout<<"The domain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *domainVector=(cDomainVector*)domain;

		unsignedIntFib uiDomainVectorElements=2;
		
		if ( domainVector->getNumberOfElements() == uiDomainVectorElements ){
		
			cout<<"The domainvector has correctly "<<
				uiDomainVectorElements<<" element. "<<endl;
			
			unsignedIntFib actualElement=1;
			
			//test domain of first vector element
			cDomain *domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=65535;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			actualElement=2;
			//test domain of secound vector element
			domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=65535;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
		
		}else{
			cerr<<"Error: The domain has "<<
				domainVector->getNumberOfElements()<<" elements and not "<<
				uiDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The domain has the type "<<
			domain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing an simple domain element"<<endl;

	cTypeProperty testTypeProperty( cTypeProperty::COLOR_GRAYSCALE );

	//create vector domain with two elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cDomainVector vectorDomainD1N4( vecDomains1 );
	delete vecDomains1[ 0 ];
	
	//check construktor
	cout<<"cDomainElement domainElementD1N4( testTypeProperty, &vectorDomainD1N4 );"<<endl;
	cDomainElement domainElementD1N4( testTypeProperty, &vectorDomainD1N4 );
	
	//check the isCompatible() methode for cDomainIntegerBasis domains
	if ( *(domainElementD1N4.getElementType()) == testTypeProperty ){
	
		cout<<"The type is correct testTypeProperty. "<<endl;
	}else{
		cerr<<"Error: The type is not testTypeProperty."<<endl;
		iReturn++;
	}

	cout<<"cDomain * domain = domainElementD1N4.getDomain();"<<endl;
	domain = domainElementD1N4.getDomain();
	
	//check if the domainpointer points to the original domain
	if ( domain == &vectorDomainD1N4 ){
	
		cout<<"The domain is correctly the vectorDomainD1N4 . "<<endl;
	}else{
		cerr<<"Error: The domain is not the domain vectorDomainD1N4  ."<<endl;
		iReturn++;
	}
	
	if ( domain == NULL ){
	
		cerr<<"Error: The domain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( domain->getType()=="DomainVector" ){
	
		cout<<"The domain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *domainVector=(cDomainVector*)domain;

		unsignedIntFib uiDomainVectorElements=1;
		
		if ( domainVector->getNumberOfElements() == uiDomainVectorElements ){
		
			cout<<"The domainvector has correctly "<<
				uiDomainVectorElements<<" element. "<<endl;
			
			unsignedIntFib actualElement=1;
			
			//test domain of first vector element
			cDomain *domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=15;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
		
		}else{
			cerr<<"Error: The domain has "<<
				domainVector->getNumberOfElements()<<" elements and not "<<
				uiDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The domain has the type "<<
			domain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
	}


	//check construktor with the standart value for the secound parameter
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the copyconstruktor"<<endl;

	cout<<"cDomainElement domainElementCopyD1N4( domainElementD1N4 );"<<endl;
	cDomainElement domainElementCopyD1N4( domainElementD1N4 );
	
	//check the isCompatible() methode for cDomainIntegerBasis domains
	if ( *(domainElementCopyD1N4.getElementType()) == testTypeProperty ){
	
		cout<<"The type is correct testTypeProperty. "<<endl;
	}else{
		cerr<<"Error: The type is not testTypeProperty."<<endl;
		iReturn++;
	}

	//check if getDomain() returns the standarddomain for the type
	cout<<"domain=domainElementCopyD1N4.getDomain();"<<endl;
	domain=domainElementCopyD1N4.getDomain();
	
	//check if the domainpointer points to the original domain
	if ( domain == &vectorDomainD1N4 ){
	
		cout<<"The domainpointer is correctly the vectorDomainD1N4 domain . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is not the domain vectorDomainD1N4  ."<<endl;
		iReturn++;
	}
	
	if ( domain==NULL ){
	
		cerr<<"Error: The domain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( domain->getType()=="DomainVector" ){
	
		cout<<"The domain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *domainVector=(cDomainVector*)domain;

		unsignedIntFib uiDomainVectorElements=1;
		
		if ( domainVector->getNumberOfElements() == uiDomainVectorElements ){
		
			cout<<"The domainvector has correctly "<<
				uiDomainVectorElements<<" element. "<<endl;
			
			unsignedIntFib actualElement=1;
			
			//test domain of first vector element
			cDomain *domainElement=domainVector->getElementDomain( actualElement );
			if ( domainElement==NULL ){
			
				cerr<<"Error: The "<<actualElement<<"'th element of the"<<
					" standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The "<<actualElement<<"'th element of the arddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=15;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<actualElement<<" element of the domain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
		
		
		}else{
			cerr<<"Error: The domain has "<<
				domainVector->getNumberOfElements()<<" elements and not "<<
				uiDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The domain has the type "<<
			domain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests a in the xml -format stored cDomainElement with
 * cTypeProperty and cDomainNaturalNumberBit domains.
 *
 * @param szFilename the name of the file where the cDomainElement is stored
 * @param uiPropertyType the type of the property
 * @param bHasDomain true if the type was saved with his domain
 * @param uiNumberOfElements the number of elements in the vector domain;
 * 	every element is an cDomainNaturalNumberBit
 * @param vecUiBits a vector with the bits the cDomainNaturalNumberBit
 * 	domains have
 * @param vecScalingfactor a vector with the scalingfactors for the
 * 	cDomainNaturalNumberBit domains have
 * @return the number of errors occured in the test
 */
int testXmlType( const string szFilename, const unsigned int uiPropertyType,
		bool bHasDomain, const unsigned int uiNumberOfElements,
		const vector<unsigned int> vecUiBits,
		const vector<double> vecScalingfactor ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored type:"<<endl;
	
	TiXmlDocument xmlDocVectorPosition( szFilename );
	bool loadOkay = xmlDocVectorPosition.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the type was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorPosition );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlRootHandle( 0 );

	pXmlElement = xmlHandle.FirstChildElement().Element();
	
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();

		if ( szElementName == "property" ){
			cout<<"The root element is correctly named \"property\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"property\"."<<endl;
			iReturn++;
		}
		
		const char * pcAttributElements = pXmlElement->Attribute( "name" );
		
		cTypeProperty typeProperty( uiPropertyType );
		
		if ( pcAttributElements == NULL ){
			cerr<<"Error: The type has no attribute \"name\"."<<endl;
			iReturn++;
		}else if ( typeProperty.getNameOfProperty( ) == pcAttributElements ) {
			cout<<"The propertyname of the type is correctly \""<<
				typeProperty.getNameOfProperty() <<"\". "<<endl;
		}else{
			cerr<<"Error: The propertyname of the loaded type is \""<<
				pcAttributElements <<"\", but should be \""<<
				typeProperty.getNameOfProperty() <<"\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}

	//read the dimensionmappings
	xmlRootHandle = xmlHandle.FirstChildElement();

	
	if ( bHasDomain ){
	//check the domain of the type
		pXmlElement = xmlRootHandle.FirstChild( "vector" ).Element();
		
		if ( pXmlElement ) {
			string szElementName = pXmlElement->Value();
	
			if ( szElementName == "vector" ){
				cout<<"The root element is correctly named \"vector\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"vector\"."<<endl;
				iReturn++;
			}
			
			int iNumberOfElementsLoaded = 0;
			const char * pcAttributElements = pXmlElement->Attribute( "elements",
				&iNumberOfElementsLoaded );
			
			if ( pcAttributElements == NULL ){
				cerr<<"Error: The domain has no attribute \"elements\"."<<endl;
				iReturn++;
			}else if ( iNumberOfElementsLoaded == (int)uiNumberOfElements ) {
				cout<<"The number of elements of the domain are correctly \""<<
					uiNumberOfElements <<"\". "<<endl;
			}else{
				cerr<<"Error: The number of elements of the loaded domain are \""<<
					iNumberOfElementsLoaded <<"\", but should be \""<<
					uiNumberOfElements <<"\"."<<endl;
				iReturn++;
			}
	
		}else{// pXmlElement == NULL ->no root handle
			cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
			return iReturn;
		}
		
		TiXmlHandle xmlDomainHandle( 0 );
		xmlDomainHandle = xmlRootHandle.FirstChildElement( "vector" );
	
		pXmlElement = xmlDomainHandle.FirstChild().Element();
		unsigned int uiActualDimension = 0;
		//for every subdomain
		for( uiActualDimension = 0; pXmlElement; 
				pXmlElement = pXmlElement->NextSiblingElement(), uiActualDimension++ ){
	
			unsigned int uiBits = vecUiBits[ uiActualDimension ];
			double dScalingfactor = vecScalingfactor[ uiActualDimension ];
		
			// should always have a valid root but handle gracefully if it does
			string szElementName = pXmlElement->Value();
	
			if ( szElementName == "naturalNumberB" ){
				cout<<"The  element is correctly named \"naturalNumberB\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the element is \""<< szElementName <<"\" and not \"naturalNumberB\"."<<endl;
				iReturn++;
			}
			
			int iBitsLoaded = 0;
			const char * pcAttributBits = pXmlElement->Attribute( "bit", &iBitsLoaded );
			
			if ( pcAttributBits == NULL ){
				cerr<<"Error: The domain has no attribute bits."<<endl;
				iReturn++;
			}else if ( iBitsLoaded == (int)uiBits ) {
				cout<<"The number of bits of the domain are correctly \""<< uiBits <<"\". "<<endl;
			}else{
				cerr<<"Error: The number of bits of the loaded domain are \""<< iBitsLoaded
					<<"\", but should be \""<< uiBits <<"\"."<<endl;
				iReturn++;
			}
	
			const char * pcAttributeScalingfactor =
				pXmlElement->Attribute( "scalingfactor" );
			
			longFib lfMantissa;
			longFib lfExponent;
			decomposeDoubleFib( dScalingfactor, & lfMantissa, & lfExponent );
			
			long lMantissa = lfMantissa;
			long lExponent = lfExponent;
	
			char szScalingfactorBuffer[128];
			szScalingfactorBuffer[0] = 0;
			sprintf ( szScalingfactorBuffer, "%li * 2^(%li)", lMantissa, lExponent );
			
			string szScalingfactor( szScalingfactorBuffer );
			
			if ( ( dScalingfactor == 1.0 ) && ( pcAttributeScalingfactor == NULL ) ){
				//no scalingfactor needed
				cout<<"No scalingfactor attribut. This is correct because the scalingfactor is 1.0 . "<<endl;
			}else{
				if ( pcAttributeScalingfactor == NULL ){
					cerr<<"Error: The domain has no attribute scalingfactor."<<endl;
					iReturn++;
				}else if ( szScalingfactor == pcAttributeScalingfactor ) {
					cout<<"The scalingfactor of the domain is correctly \""<< pcAttributeScalingfactor <<"\". "<<endl;
				}else{
					cerr<<"Error: The scalingfactor of the loaded domain is \""<< pcAttributeScalingfactor
						<<"\", but should be \""<< dScalingfactor <<"\" (=\""<< szScalingfactor <<"\")."<<endl;
					iReturn++;
				}
			}
		}
		
		if ( uiActualDimension == uiNumberOfElements ){
			cout<<"The number of subdomains is correct. "<<endl;
		
		}else{
			cerr<<"Error: The number of subdomains is "<< uiActualDimension <<
				", but should be "<< uiNumberOfElements <<"."<<endl;
			iReturn++;
		}
	}

	return iReturn;
}


/**
 * This method storeXml() method of the class.
 *
 * methods tested:
 * 	- bool storeXml( ostringstream & ostream ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreXml( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing xml -storing a domain element with a propertytype of type 2 and an domain"<<endl;
	
	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );
	cout<<"cDomainVector domainVectorE1( vecDomains1 );"<<endl;
	cDomainVector domainVectorE1( vecDomains1 );
	delete vecDomains1[ 0 ];
	
	vector<unsigned int> vecDomainE1Bits(1);
	vecDomainE1Bits[ 0 ] = 4;
	vector<double> vecDomainE1Scalingfactor(1);
	vecDomainE1Scalingfactor[ 0 ] = 1.0;

	unsigned int uiPropertyType = 2;
	cout<<"cTypeProperty typeProperty2( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty2( uiPropertyType );

	cout<<"cDomainElement domainElement1( typeProperty2, &domainVectorE1 );"<<endl;
	cDomainElement domainElement1( typeProperty2, &domainVectorE1 );

	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainElement1.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"domainElement1.storeXml( *fileXml );"<<endl;
	bool bStoreSuccesfull = domainElement1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, uiPropertyType, true, 1,
		vecDomainE1Bits, vecDomainE1Scalingfactor );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a domain element with a property of type 1 and an domain"<<endl;
	
	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1, 1.0 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1, 1.0 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2, 0.125 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2, 0.125 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3, 3.0 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3, 3.0 );
	cout<<"cDomainVector domainVectorE3( vecDomains1 );"<<endl;
	cDomainVector domainVectorE3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	vector<unsigned int> vecDomainE3Bits( 3 );
	vecDomainE3Bits[ 0 ] = 1;
	vecDomainE3Bits[ 1 ] = 2;
	vecDomainE3Bits[ 2 ] = 3;
	vector<double> vecDomainE3Scalingfactor( 3 );
	vecDomainE3Scalingfactor[ 0 ] = 1.0;
	vecDomainE3Scalingfactor[ 1 ] = 0.125;
	vecDomainE3Scalingfactor[ 2 ] = 3.0;

	uiPropertyType = 1;
	cout<<"cTypeProperty typeProperty1Dom( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty1Dom( uiPropertyType );

	cout<<"cDomainElement domainElement2( typeProperty1Dom, &domainVectorE3 );"<<endl;
	cDomainElement domainElement2( typeProperty1Dom, &domainVectorE3 );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainElement2.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"domainElement2.storeXml( *fileXml );"<<endl;
	bStoreSuccesfull = domainElement2.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, uiPropertyType, true, 3,
		vecDomainE3Bits, vecDomainE3Scalingfactor );


	return iReturn;
}




/**
 * This method store() method of the class.
 *
 * methods tested:
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostringstream & ostream ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStore( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a domain element with the property of type 2"<<endl;

	unsigned int uiPropertyType = 2;
	cout<<"cTypeProperty typeProperty2( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty2( uiPropertyType );
	
	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector domainVectorE1( vecDomains1 );"<<endl;
	cDomainVector domainVectorE1( vecDomains1 );
	delete vecDomains1[ 0 ];

	//check construktor
	cout<<"cDomainElement domainElement1( typeProperty2, &domainVectorE1 );"<<endl;
	cDomainElement domainElement1( typeProperty2, &domainVectorE1 );

	//test get compressed size
	unsigned int uiCompressedSize = 8 + 8 + 32;
	if ( (unsigned int)(domainElement1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			domainElement1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainElement1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = domainElement1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	unsigned char ucRestBit = cRestBit;
	if ( ( ucRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainElement1[] = { (char)0x22,
		(char)0x02,   //type of the property
		(char)0xC0,   //vector domain
		(char)0x01,   //8 bit parameter for number of elements
		(char)0x00, (char)0x03, //natural number domain
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainElement1, 7 );



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing af a domain element with property of type 2003"<<endl;

	uiPropertyType = 2003;
	cout<<"cTypeProperty typeProperty2003( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty2003( uiPropertyType );


	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector domainVectorE3( vecDomains3 );"<<endl;
	cDomainVector domainVectorE3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	//check construktor
	cout<<"cDomainElement domainElement2( typeProperty2003, &domainVectorE3 );"<<endl;
	cDomainElement domainElement2( typeProperty2003, &domainVectorE3 );

	//test get compressed size
	uiCompressedSize = 8 + 64 + 16 + 3 * 16;
	if ( (unsigned int)(domainElement2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			domainElement2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainElement2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = domainElement2.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	if ( ( ucRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainElement2[] = { (char)0x24,
		(char)0xD3, (char)0x07, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,   //type of the property
		(char)0xC0,  //vector domain
		(char)0x03,  //8 bit parameter for number of elements
		(char)0x00, (char)0x01,//natural number domain 1
		(char)0x00, (char)0x02,//natural number domain 2
		(char)0x00, (char)0x03,//natural number domain 3
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainElement2, 18 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a type property of type 7 and 2 restbits"<<endl;

	uiPropertyType = 7;
	cout<<"cTypeProperty typeProperty7( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty7( uiPropertyType );

	//check construktor
	cout<<"cDomainElement domainElement3( typeProperty7, &domainVectorE1 );"<<endl;
	cDomainElement domainElement3( typeProperty7, &domainVectorE1 );

	//test get compressed size
	uiCompressedSize = 8 + 8 + 32;
	if ( (unsigned int)(domainElement3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			domainElement3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainElement3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x02;
	cNumberOfRestBit = 2 ;
	bStoreSuccesfull = domainElement3.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	if ( ( ucRestBit == (unsigned char)(char)0x00 ) && ( cNumberOfRestBit == 2 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x00 and number of restbit should be 2. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainElement3[] = { (char)0x8A,
		(char)0x1C,   //type of the property
		(char)0x00,  //vector domain
		(char)0x07,
		(char)0x00, (char)0x0C,
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainElement3, 7 );
	

	return iReturn;
}


















