/**
 * @file tDomainTools
 * file name: tDomainTools.cpp
 * @author Betti Oesterholz
 * @date 13.05.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains testfunctions for domains of the class cDomain.
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
 * This file contains the test for the class cDomainNaturalNumberBit,
 * which represents a domain for natural numbers.
 *
 */
/*
History:
12.05.2010  Oesterholz  scalingfactor moved from cDomainSingle to cDomainIntegerBasis
*/

#include "version.h"

#include "fibDatatyps.h"
#include "cDomainSingle.h"
#include "cDomainIntegerBasis.h"

#include <iostream>


using namespace fib;
using namespace std;


int checkScalingFactor( cDomainIntegerBasis *domainToTest, doubleFib dScalingFactor );
int checkBounderiesOfIntegerDomain( cDomainIntegerBasis *domainToTest,
		longFib lMinNumber, longFib lMaxNumber, doubleFib dScalingFactor );
int testIntegerDomainElements( cDomainIntegerBasis *domainToTest,
		longFib lMinNumber, longFib lMaxNumber, doubleFib dScalingFactor, longFib lStepwidth );



/**
 * This function performs a simple/ quick test of the given integer domain.
 *
 * The following tests are performed:
 * 	- the returnvalue of all methods, except the getType() method, of
 * 		the domain are tested
 * 	- is*Element() and round*() methods are tested for 100 possible
 * 		correct values with equal distance in the domain
 * 	- isUnscaledElement() and roundUnscaled() methods are tested for
 * 		values outside the domain:
 * 		-- the unscaled (minimum-1) and (maximum+1) values
 * 	- isElement() and round() methods are tested for 
 * 		values outside the domain:
 * 		-- the (minimum-1)*dScalingFactor value
 * 		-- the (maximum+1)*dScalingFactor value
 * 		-- the (minimum+0.5)*dScalingFactor value
 * 		-- the (maximum-0.5)*dScalingFactor value
 * 		-- the (nullvalue+0.5)*dScalingFactor value
 * 		-- the (nullvalue-0.5)*dScalingFactor value
 *
 * @param domainToTest the integer domain to test
 * @param lMinNumber the minimal unscaled number in the given domain domainToTest
 * @param lMaxNumber the maximal unscaled number in the given domain domainToTest
 * @param dScalingFactor the scaling factor of the domain
 * @return the number of errors occured in the test
 */
int testIntegerDomainShort( cDomainIntegerBasis *domainToTest, longFib lMinNumber, longFib lMaxNumber, doubleFib dScalingFactor ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( lMaxNumber < lMinNumber ){
		const longFib lTmpMaxNumber = lMaxNumber;
		lMinNumber = lMaxNumber;
		lMaxNumber = lTmpMaxNumber;
	}
	
	//test scaling factor
	iReturn += checkScalingFactor( domainToTest, dScalingFactor );

	//test the bounderies of the domain
	iReturn += checkBounderiesOfIntegerDomain( domainToTest, lMinNumber, lMaxNumber,
		dScalingFactor );

	//stepwidth for testing the elements in the domain
	longFib lStepwidth = (lMaxNumber - lMinNumber) / (longFib)(101);
	if ( lStepwidth == 0 ){
		lStepwidth = 1;
	}

	//test the domain elements
	iReturn += testIntegerDomainElements( domainToTest, lMinNumber, lMaxNumber, dScalingFactor, lStepwidth );

	return iReturn;
}


/**
 * This function performs a intensive test of the given integer domain.
 *
 * The following tests are performed:
 * 	- the returnvalue of all methods, except the getType() method, of
 * 		the domain are tested
 * 	- is*Element() and round*() methods are tested for all possible
 * 		correct values in the domain
 * 	- isUnscaledElement() and roundUnscaled() methods are tested for
 * 		values outside the domain:
 * 		-- the unscaled (minimum-1) and (maximum+1) values
 * 	- isElement() and round() methods are tested for 
 * 		values outside the domain:
 * 		-- the (minimum-1)*dScalingFactor value
 * 		-- the (maximum+1)*dScalingFactor value
 * 		-- the (minimum+0.5)*dScalingFactor value
 * 		-- the (maximum-0.5)*dScalingFactor value
 * 		-- the (nullvalue+0.5)*dScalingFactor value
 * 		-- the (nullvalue-0.5)*dScalingFactor value
 *
 * @param domainToTest the integer domain to test
 * @param lMinNumber the minimal unscaled number in the given domain domainToTest
 * @param lMaxNumber the maximal unscaled number in the given domain domainToTest
 * @param dScalingFactor the scaling factor of the domain
 * @return the number of errors occured in the test
 */
int testIntegerDomainLong( cDomainIntegerBasis *domainToTest,
		longFib lMinNumber, longFib lMaxNumber, doubleFib dScalingFactor ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	if ( lMaxNumber < lMinNumber ){
		const longFib lTmpMaxNumber = lMaxNumber;
		lMinNumber = lMaxNumber;
		lMaxNumber = lTmpMaxNumber;
	}

	//test scaling factor
	iReturn += checkScalingFactor( domainToTest, dScalingFactor );

	//test the bounderies of the domain
	iReturn += checkBounderiesOfIntegerDomain( domainToTest, lMinNumber, lMaxNumber,
		dScalingFactor );

	//test the domain elements
	iReturn += testIntegerDomainElements( domainToTest, lMinNumber, lMaxNumber, dScalingFactor, (longFib)(1)  );

	return iReturn;
}



/**
 * This function test of the given domain.
 *
 *
 * @param domainToTest the domain to test
 * @param dScalingFactor the scaling factor of the domain
 * @return the number of errors occured in the test
 */
int checkScalingFactor( cDomainIntegerBasis *domainToTest,
		doubleFib dScalingFactor ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors

	//test scaling factor
	if ( domainToTest->getScalingFactor() == dScalingFactor ){
		cout<<"the domain has the correct scalingfactor: "<<
			domainToTest->getScalingFactor()<<endl;
	}else{
		cerr<<"Error: the scalingfactor of the domain isn't correct, it is: "<<
			domainToTest->getScalingFactor()<<" but should be "<<dScalingFactor<<
			endl;
		iReturn++;
	}
	return iReturn;
}


/**
 * This function checks the bounderies of the given integer domain.
 * checkt bounderies are: minimal, maximal and nullvalue
 *
 * @param domainToTest the integer domain to test
 * @param lMinNumber the minimal unscaled number in the given domain domainToTest
 * @param lMaxNumber the maximal unscaled number in the given domain domainToTest
 * @param dScalingFactor the scaling factor of the domain
 * @return the number of errors occured in the test
 */
int checkBounderiesOfIntegerDomain( cDomainIntegerBasis *domainToTest,
		longFib lMinNumber, longFib lMaxNumber, doubleFib dScalingFactor ){

	int iReturn=0;
	
	if ( lMaxNumber < lMinNumber ){
		const longFib lTmpMaxNumber = lMaxNumber;
		lMinNumber = lMaxNumber;
		lMaxNumber = lTmpMaxNumber;
	}

	//test unscaled minimum
	if ( domainToTest->getMinimumUnscaled()==lMinNumber ){
		cout<<"the domain has the correct unscaled minimum: "<<
			domainToTest->getMinimumUnscaled()<<endl;
	}else{
		cerr<<"Error: the unscaled minimum of the domain isn't correct, it is: "<<
			domainToTest->getMinimumUnscaled()<<" but should be "<<lMinNumber<<
			endl;
		iReturn++;
	}


	//test scaled minimum
	if ( domainToTest->getMinimum()==(lMinNumber * dScalingFactor) ){
		cout<<"the domain has the correct scaled minimum: "<<
			domainToTest->getMinimum()<<endl;
	}else{
		cerr<<"Error: the scaled minimum of the domain isn't correct, it is: "<<
			domainToTest->getMinimum()<<" but should be "<<(lMinNumber * dScalingFactor)<<
			endl;
		iReturn++;
	}


	//test unscaled maximum
	if ( domainToTest->getMaximumUnscaled()==lMaxNumber ){
		cout<<"the domain has the correct unscaled maximum: "<<
			domainToTest->getMaximumUnscaled()<<endl;
	}else{
		cerr<<"Error: the unscaled maximum of the domain isn't correct, it is: "<<
			domainToTest->getMaximumUnscaled()<<" but should be "<<lMaxNumber<<
			endl;
		iReturn++;
	}

	//test scaled maximum
	if ( domainToTest->getMaximum()==(lMaxNumber * dScalingFactor) ){
		cout<<"the domain has the correct scaled maximum: "<<
			domainToTest->getMaximum()<<endl;
	}else{
		cerr<<"Error: the scaled maximum of the domain isn't correct, it is: "<<
			domainToTest->getMaximum()<<" but should be "<<(lMaxNumber * dScalingFactor)<<
			endl;
		iReturn++;
	}

	//evalue the unscaled nullvalue the domain should have
	longFib lUnscaledNull=(longFib)(0);
	
	if ( 0<lMinNumber ){
		lUnscaledNull = lMinNumber;
	}
	if ( lMaxNumber<0 ){
		lUnscaledNull = lMaxNumber;
	}

	//test unscaled nullvale
	if ( domainToTest->getNullUnscaled() == lUnscaledNull ){
		cout<<"the domain has the correct unscaled nullvalue: "<<
			domainToTest->getNullUnscaled()<<endl;
	}else{
		cerr<<"Error: the unscaled nullvalue of the domain isn't correct, it is: "<<
			domainToTest->getNullUnscaled()<<" but should be "<<lUnscaledNull<<
			endl;
		iReturn++;
	}

	//test scaled nullvale
	if ( domainToTest->getNull()==(lUnscaledNull * dScalingFactor) ){
		cout<<"the domain has the correct scaled nullvalue: "<<
			domainToTest->getNull()<<endl;
	}else{
		cerr<<"Error: the scaled nullvalue of the domain isn't correct, it is: "<<
			domainToTest->getNull()<<" but should be "<<(lUnscaledNull * dScalingFactor)<<
			endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This function performs a test of the elements in the given integer domain.
 *
 * The following tests are performed:
 * 	- is*Element() and round*() methods are tested for correct values
 * 		in the domain with the (unscaled) distance lStepwidth
 * 	- isUnscaledElement() and roundUnscaled() methods are tested for
 * 		values outside the domain:
 * 		-- the unscaled (minimum-1) and (maximum+1) values
 * 	- isElement() and round() methods are tested for 
 * 		values outside the domain:
 * 		-- the (minimum-1)*dScalingFactor value
 * 		-- the (maximum+1)*dScalingFactor value
 * 		-- the (minimum+0.5)*dScalingFactor value
 * 		-- the (maximum-0.5)*dScalingFactor value
 * 		-- the (nullvalue+0.5)*dScalingFactor value
 * 		-- the (nullvalue-0.5)*dScalingFactor value
 *
 * @param domainToTest the integer domain to test
 * @param lMinNumber the minimal unscaled number in the given domain domainToTest
 * @param lMaxNumber the maximal unscaled number in the given domain domainToTest
 * @param dScalingFactor the scaling factor of the domain
 * @param lStepwidth every which steps the elements of the integer domain
 * 	should be tested
 * @return the number of errors occured in the test
 */
int testIntegerDomainElements( cDomainIntegerBasis *domainToTest,
		longFib lMinNumber, longFib lMaxNumber, doubleFib dScalingFactor, longFib lStepwidth ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	//evalue the unscaled nullvalue the domain should have
	longFib lUnscaledNull = (longFib)(0);
	
	if ( lMaxNumber < lMinNumber ){
		const longFib lTmpMaxNumber = lMaxNumber;
		lMinNumber = lMaxNumber;
		lMaxNumber = lTmpMaxNumber;
	}
	
	if ( 0 < lMinNumber ){
		lUnscaledNull = lMinNumber;
	}
	if ( lMaxNumber < 0 ){
		lUnscaledNull = lMaxNumber;
	}
	if ( lStepwidth == 0 ){
		lStepwidth = 1;
	}


	/*test the method isUnscaledElement() for values in the domain*/
	cout<<"numbers in the unscaled domain: ";
	for ( longFib lTestNumber = lMinNumber; lTestNumber <= lMaxNumber;
			lTestNumber = lTestNumber + lStepwidth ){
		
		if ( domainToTest->isUnscaledElement( lTestNumber ) ){
			cout<<lTestNumber<<" ;";
		}else{
			cerr<<endl<<"Error: The number: "<<lTestNumber<<
				" is not in the unscaled domain but should be "<<endl;
			cout<<"numbers in the unscaled domain: ";
			iReturn++;
		}
	}
	cout<<endl;
 
	//test if (minimum-1) is not in the unscaled domain
	if ( !domainToTest->isUnscaledElement( lMinNumber-1 ) ){
		cout<<"The (minimal-1) number "<<(lMinNumber-1)<<
			" is correctly not in the domain"<<endl;
	}else{
		cerr<<"Error: The (minimal-1) number "<<(lMinNumber-1)<<
			" is in the domain"<<endl;
		iReturn++;
	}
	
	//test if (maximum+1) is not in the unscaled domain
	if ( !domainToTest->isUnscaledElement( lMaxNumber+1 ) ){
		cout<<"The (maximum+1) number "<<(lMaxNumber+1)<<
			" is correctly not in the domain"<<endl;
	}else{
		cerr<<"Error: The (maximum+1) number "<<(lMaxNumber+1)<<
			" is in the domain"<<endl;
		iReturn++;
	}


	/*test the method isElement() for values in the domain*/
	cout<<"numbers in the scaled domain: ";
	for ( longFib lTestNumber = lMinNumber; lTestNumber <= lMaxNumber; lTestNumber = lTestNumber+lStepwidth ){
		
		if ( domainToTest->isElement( lTestNumber*dScalingFactor ) ){
			cout<<(lTestNumber*dScalingFactor)<<" ;";
		}else{
			cerr<<endl<<"Error: The number: "<<lTestNumber*dScalingFactor<<
				" is not in the scaled domain but should be "<<endl;
			cout<<"numbers in the scaled domain: ";
			iReturn++;
		}
	}
	cout<<endl;
 
	//test if (minimum-1)*dScalingFactor is not in the unscaled domain
	if ( !domainToTest->isElement( (lMinNumber-1)*dScalingFactor ) ){
		cout<<"The (minimal-1)*dScalingFactor number "<<
			(lMinNumber-1)*dScalingFactor<<" is correctly not in the domain"<<endl;
	}else{
		cerr<<"Error: The (minimal-1)*dScalingFactor number "<<
			(lMinNumber-1)*dScalingFactor<<" is in the domain"<<endl;
		iReturn++;
	}
	
	//test if (maximum+1)*dScalingFactor is not in the unscaled domain
	if ( !domainToTest->isElement( (lMaxNumber+1 )*dScalingFactor ) ){
		cout<<"The (maximum+1)*dScalingFactor number "<<
			(lMaxNumber+1)*dScalingFactor<<" is correctly not in the domain"<<endl;
	}else{
		cerr<<"Error: The (maximum+1)*dScalingFactor number "<<
			(lMaxNumber+1)*dScalingFactor<<" is in the domain"<<endl;
		iReturn++;
	}

	//test if (minimum+0.5)*dScalingFactor is not in the unscaled domain
	if ( !domainToTest->isElement( ((doubleFib)(lMinNumber)+0.5)*dScalingFactor ) ){
		cout<<"The (minimal+0.5)*dScalingFactor number "<<
			((doubleFib)(lMinNumber)+0.5)*dScalingFactor<<
			" is correctly not in the domain"<<endl;
	}else{
		cerr<<"Error: The (minimal+0.5)*dScalingFactor number "<<
			((doubleFib)(lMinNumber)+0.5)*dScalingFactor<<
			" is in the domain"<<endl;
		iReturn++;
	}
	
	//test if (maximum-0.5)*dScalingFactor is not in the unscaled domain
	if ( !domainToTest->isElement( ((doubleFib)(lMaxNumber)-0.5)*dScalingFactor ) ){
		cout<<"The (maximum-0.5)*dScalingFactor number "<<
			((doubleFib)(lMaxNumber)-0.5)*dScalingFactor<<
			" is correctly not in the domain"<<endl;
	}else{
		cerr<<"Error: The (maximum-0.5)*dScalingFactor number "<<
			((doubleFib)(lMaxNumber)-0.5)*dScalingFactor<<
			" is in the domain"<<endl;
		iReturn++;
	}

	//test if (nullvalue+0.5)*dScalingFactor is not in the unscaled domain
	if ( !domainToTest->isElement( ((doubleFib)(lUnscaledNull)+0.5)*dScalingFactor ) ){
		cout<<"The (nullvalue+0.5)*dScalingFactor number "<<
			((doubleFib)(lUnscaledNull)+0.5)*dScalingFactor<<
			" is correctly not in the domain"<<endl;
	}else{
		cerr<<"Error: tThe (nullvalue+0.5)*dScalingFactor number "<<
			((doubleFib)(lUnscaledNull)+0.5)*dScalingFactor<<
			" is in the domain"<<endl;
		iReturn++;
	}
	
	//test if (nullvalue-0.5)*dScalingFactor is not in the unscaled domain
	if ( !domainToTest->isElement( ((doubleFib)(lUnscaledNull)-0.5)*dScalingFactor ) ){
		cout<<"The (nullvalue-0.5)*dScalingFactor number "<<
			((doubleFib)(lUnscaledNull)-0.5)*dScalingFactor<<
			" is correctly not in the domain"<<endl;
	}else{
		cerr<<"Error: The (nullvalue-0.5)*dScalingFactor number "<<
			((doubleFib)(lUnscaledNull)-0.5)*dScalingFactor<<
			" is in the domain"<<endl;
		iReturn++;
	}


	/*test the method roundUnscaled() for values in the domain*/
	cout<<"numbers in the unscaled domain rounded correct: ";
	for ( longFib lTestNumber = lMinNumber; lTestNumber <= lMaxNumber; lTestNumber = lTestNumber+lStepwidth ){
		
		if ( domainToTest->roundUnscaled( lTestNumber ) == lTestNumber ){
			cout<<lTestNumber<<" ;";
		}else{
			cerr<<endl<<"Error: The number: "<<lTestNumber<<
				" is rounded wrong to: "<<
				domainToTest->roundUnscaled( lTestNumber )<<endl;
			cout<<"numbers in the unscaled domain rounded correct: ";
			iReturn++;
		}
	}
	cout<<endl;

	//test if (minimum-1) of the unscaled domain is rounded correct to minimum
	if ( domainToTest->roundUnscaled( lMinNumber-1 )==lMinNumber ){
		cout<<"The (minimal-1) number "<<(lMinNumber-1)<<
			" is correctly rounded to the minimal "<<lMinNumber<<endl;
	}else{
		cerr<<"Error: The (minimal-1) number "<<(lMinNumber-1)<<
			" is not correctly rounded to the minimal "<<lMinNumber<<
			" but to the number :"<<
			domainToTest->roundUnscaled( lMinNumber-1 )<<endl;
		iReturn++;
	}
	
	//test if (maximum+1) of the unscaled domain is rounded correct to maximum
	if ( domainToTest->roundUnscaled( lMaxNumber+1 )==lMaxNumber ){
		cout<<"The (maximum+1) number "<<(lMaxNumber+1)<<
			" is correctly rounded to the maximal "<<lMaxNumber<<endl;
	}else{
		cerr<<"Error: The (maximum+1) number "<<(lMaxNumber+1)<<
			" is not correctly rounded to the maximal "<<lMaxNumber<<
			" but to the number :"<<
			domainToTest->roundUnscaled( lMaxNumber+1 )<<endl;
		iReturn++;
	}

	/*test the method round() for values in the domain*/
	const doubleFib dDeltaValue = dScalingFactor / 1000000000.0;
	const doubleFib dDiffValue = dScalingFactor / 3.0;
	cout<<"numbers in the scaled domain rounded correct: ";
	for ( longFib lTestNumber = lMinNumber; lTestNumber <= lMaxNumber;
			lTestNumber = lTestNumber+lStepwidth ){
		
		const doubleFib dTestNumber = ((doubleFib)lTestNumber) * dScalingFactor;
		doubleFib dRoundedValue =
			domainToTest->round( dTestNumber );
		if ( domainToTest->isElement( dRoundedValue ) ){
			cout<< dRoundedValue <<" ;";
		}else{
			cerr<<endl<<"Error: The rounded number: "<< dRoundedValue <<
				" is not in the scaled domain but should be "<<endl;
			cout<<"numbers in the scaled domain rounded correct: ";
			iReturn++;
		}
		if ( ( dRoundedValue < (dTestNumber - dDeltaValue)) ||
				((dTestNumber + dDeltaValue) < dRoundedValue ) ){
			cerr<<endl<<"Error: The number: "<<dTestNumber<<
				" is rounded wrong to: "<< dRoundedValue <<
				" (diff="<< dRoundedValue - dTestNumber <<" )"<<endl;
			cout<<"numbers in the scaled domain rounded correct: ";
			iReturn++;
		}
		dRoundedValue = domainToTest->round( dTestNumber + dDiffValue );
		if ( ! domainToTest->isElement( dRoundedValue ) ){
			cerr<<endl<<"Error: The rounded number: "<< dRoundedValue <<
				" is not in the scaled domain but should be "<<endl;
			cout<<"numbers in the scaled domain rounded correct: ";
			iReturn++;
		}
		if ( ( dRoundedValue < (dTestNumber - dDeltaValue)) ||
				((dTestNumber + dDeltaValue) < dRoundedValue ) ){
			cerr<<endl<<"Error: The number: "<<dTestNumber + dDiffValue<<
				" is rounded wrong to: "<< dRoundedValue <<
				" (diff="<< dRoundedValue - (dTestNumber + dDiffValue) <<" )"<<endl;
			cout<<"numbers in the scaled domain rounded correct: ";
			iReturn++;
		}
		dRoundedValue = domainToTest->round( dTestNumber - dDiffValue );
		if ( ! domainToTest->isElement( dRoundedValue ) ){
			cerr<<endl<<"Error: The rounded number: "<< dRoundedValue <<
				" is not in the scaled domain but should be "<<endl;
			cout<<"numbers in the scaled domain rounded correct: ";
			iReturn++;
		}
		if ( ( dRoundedValue < (dTestNumber - dDeltaValue)) ||
				((dTestNumber + dDeltaValue) < dRoundedValue ) ){
			cerr<<endl<<"Error: The number: "<<dTestNumber - dDiffValue<<
				" is rounded wrong to: "<< dRoundedValue <<
				" (diff="<< dRoundedValue - (dTestNumber - dDiffValue) <<" )"<<endl;
			cout<<"numbers in the scaled domain rounded correct: ";
			iReturn++;
		}
	}
	cout<<endl;

	/*test if (minimum-1)*dScalingFactor of the scaled domain is rounded
	 correct to minimum*/
	doubleFib dRoundedMinValue =
		  domainToTest->round( (lMinNumber-1)*dScalingFactor );
	if ( domainToTest->isElement( dRoundedMinValue ) &&
			((lMinNumber * dScalingFactor - dDeltaValue) <= dRoundedMinValue) &&
			(dRoundedMinValue <= (lMinNumber * dScalingFactor + dDeltaValue)) ){
			
		cout<<"The (minimal-1)*dScalingFactor number "<<
			(lMinNumber-1)*dScalingFactor<<
			" is correctly rounded to the minimal "<<
			lMinNumber*dScalingFactor<<endl;
	}else{
		cerr<<"Error: The (minimal-1)*dScalingFactor number "<<
			(lMinNumber-1)*dScalingFactor<<
			" is not correctly rounded to the minimal "<<
			lMinNumber*dScalingFactor<<
			" but to the number :"<<
			domainToTest->round( (lMinNumber-1)*dScalingFactor )<<endl;
		iReturn++;
	}
	
	/*test if (maximum+1)*dScalingFactor of the scaled domain is rounded
	 correct to maximum*/
	doubleFib dRoundedMaxValue =
		  domainToTest->round( (lMaxNumber+1)*dScalingFactor );
	if ( domainToTest->isElement( dRoundedMinValue ) &&
			((lMaxNumber * dScalingFactor - dDeltaValue) <= dRoundedMaxValue) &&
			(dRoundedMaxValue <= (lMaxNumber * dScalingFactor + dDeltaValue)) ){
			
		cout<<"The (maximum+1)*dScalingFactor number "<<
			(lMaxNumber+1)*dScalingFactor<<
			" is correctly rounded to the maximal*dScalingFactor "<<
			lMaxNumber*dScalingFactor<<endl;
	}else{
		cerr<<"Error: The (maximum+1)*dScalingFactor number "<<
			(lMaxNumber+1)*dScalingFactor<<
			" is not correctly rounded to the maximal*dScalingFactor "<<
			lMaxNumber*dScalingFactor<<
			" but to the number :"<<
			domainToTest->round( (lMaxNumber+1)*dScalingFactor )<<endl;
		iReturn++;
	}

	/*test if (minimum+0.499)*dScalingFactor  of the scaled domain is rounded
	 correct to minimum*/
	dRoundedMinValue = domainToTest->round(
		((doubleFib)(lMinNumber) + 0.499) * dScalingFactor );
	if ( domainToTest->isElement( dRoundedMinValue ) &&
			((lMinNumber * dScalingFactor - dDeltaValue) <= dRoundedMinValue) &&
			(dRoundedMinValue <= (lMinNumber * dScalingFactor + dDeltaValue)) ){

		cout<<"The (minimal+0.499)*dScalingFactor number "<<
			((doubleFib)(lMinNumber)+0.499)*dScalingFactor<<
			" is correctly rounded to the minimal "<<
			lMinNumber*dScalingFactor<<endl;
	}else{
		cerr<<"Error: The (minimal+0.499)*dScalingFactor number "<<
			(lMinNumber+0.499)*dScalingFactor<<
			" is not correctly rounded to the minimal "<<
			lMinNumber*dScalingFactor<<
			" but to the number :"<< dRoundedMinValue <<endl;
		iReturn++;
	}

	/*test if (maximum-0.499)*dScalingFactor of the scaled domain is rounded
	 correct to maximum*/
	dRoundedMaxValue = domainToTest->round(
		((doubleFib)(lMaxNumber)-0.499)*dScalingFactor );
	if ( domainToTest->isElement( dRoundedMinValue ) &&
			((lMaxNumber * dScalingFactor - dDeltaValue) <= dRoundedMaxValue) &&
			(dRoundedMaxValue <= (lMaxNumber * dScalingFactor + dDeltaValue)) ){
			
		cout<<"the (maximum-0.499)*dScalingFactor number "<<
			((doubleFib)(lMaxNumber)-0.499)*dScalingFactor<<
			" is correctly rounded to the maximum "<<
			lMaxNumber*dScalingFactor<<endl;
	}else{
		cerr<<"Error: the (maximum-0.499)*dScalingFactor number "<<
			(lMaxNumber-0.499)*dScalingFactor<<
			" is not correctly rounded to the maximum "<<
			lMaxNumber*dScalingFactor<<
			" but to the number :"<< dRoundedMaxValue <<endl;
		iReturn++;
	}


	/*test if (nullvalue+0.499)*dScalingFactor  of the scaled domain is rounded
	 correct to nullvalue*/
	if ( domainToTest->round( ((doubleFib)(lUnscaledNull)+0.499)*dScalingFactor )==
			lUnscaledNull*dScalingFactor ){

		cout<<"the (nullvalue+0.499)*dScalingFactor number "<<
			((doubleFib)(lUnscaledNull)+0.499)*dScalingFactor<<
			" is correctly rounded to the nullvalue "<<
			lUnscaledNull*dScalingFactor<<endl;
	}else{
		cerr<<"Error: the (nullvalue+0.499)*dScalingFactor number "<<
			(lUnscaledNull+0.499)*dScalingFactor<<
			" is not correctly rounded to the nullvalue "<<
			lUnscaledNull*dScalingFactor<<
			" but to the number :"<<
			domainToTest->round( (lUnscaledNull+0.499)*dScalingFactor )<<endl;
		iReturn++;
	}

	/*test if (nullvalue-0.499)*dScalingFactor of the scaled domain is rounded
	 correct to nullvalue*/
	if ( domainToTest->round( ((doubleFib)(lUnscaledNull)-0.499)*dScalingFactor )==
			lUnscaledNull*dScalingFactor ){

		cout<<"the (nullvalue-0.499)*dScalingFactor number "<<
			((doubleFib)(lUnscaledNull)-0.499)*dScalingFactor<<
			" is correctly rounded to the nullvalue "<<
			lUnscaledNull*dScalingFactor<<endl;
	}else{
		cerr<<"Error: the (nullvalue-0.499)*dScalingFactor number "<<
			(lUnscaledNull-0.499)*dScalingFactor<<
			" is not correctly rounded to the nullvalue "<<
			lUnscaledNull*dScalingFactor<<
			" but to the number :"<<
			domainToTest->round( (lUnscaledNull-0.499)*dScalingFactor )<<endl;
		iReturn++;
	}

	return iReturn;
}












