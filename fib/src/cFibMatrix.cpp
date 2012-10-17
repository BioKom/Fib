/**
 * @class cFibMatrix
 * file name: cFibMatrix.cpp
 * @author Betti Oesterholz
 * @date 02.01.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the Fib matrix element.
 * Copyright (C) @c LGPL3 2012 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This class represents the matrix element of the Fib multimedia language.
 * 
 * An matrix element represents a d dimensional matrix. For every dimension
 * ther is an area (Startvalue_h to Endvalue_h) for its possible index values.
 * Furthermore ther is a list ( (W_{1.1}, ..., W_{i.1}), ... ,
 * (W_{1.k}, ..., W_{i.k}) with vectors for the elements of the matrix.
 * 
 * In the evaluation of the matrix element each dimension/counter/index
 * variable (Variable_1, ..., Variable_d) goes through all integers of
 * the corresponding area (Startvalue_h to Endvalue_h). For each integer
 * value of the Variable_h all integer values of the variable Variable_{h-1}
 * will be set. For each value allocation of the dimension variables 
 * (Variable_1, ... , Variable_d) the value variables (Variable_{d+1}, ... ,
 * Variable_{d+i}) will be set to the next set of values (W_{1.b}, ... , W_{i.b}).
 * This continues until either the dimension variables (Variable_1, ... ,
 * Variable_d) have gone through all of their values or there is no next 
 * set of values (W_{1.k+1}, ... , W_{i.k+1}). If an element W_{a.b} is a 
 * variable, so the Variable_{d+a} will be assigned according to the value
 * of the variable W_{a.b}.
 * 
 * If there are no value variables (i=0), just all the values of the
 * dimension variables (Variable_1, ..., Variable_d) will be set and the
 * sets of values will be ignored.
 *
 */
/*
History:
02.01.2012  Oesterholz  created
*/


#include "cFibMatrix.h"

#include "cTypeFibMatrix.h"
#include "cTypeVariable.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainNaturalNumber.h"

#include <algorithm>



using namespace fib;



/**
 * parameterconstructor
 *
 * @param iuNumberOfDimensions the number of dimension (variables)
 * 	(minimum is 1)
 * @param uiNumberOfVectorElements the number of elements in the vectors
 * 	the elements of the matrix of this matrix element should have
 * @param pInSubobject the Fib element which is the subobject of
 * 	this Fib element (it also stands next in the order of Fib elements)
 * @param pInSuperiorElement the Fib element in which this
 * 	matrix element is a subobject
 */
cFibMatrix::cFibMatrix( unsignedIntFib iuNumberOfDimensions,
		const unsignedIntFib uiNumberOfVectorElements,
		cFibElement * pInSubobject,
		cFibElement * pInSuperiorElement ):
		cFibLimb( pInSubobject, pInSuperiorElement ),
		uiDomainNr( 0 ){
	
	if ( iuNumberOfDimensions == 0 ){
		//minimum of one dimension
		iuNumberOfDimensions = 1;
	}
	const unsignedIntFib iuNumberOfVariables =
		iuNumberOfDimensions + uiNumberOfVectorElements;
	
	for ( unsignedIntFib uiNumberOfVariable = 0;
			uiNumberOfVariable < iuNumberOfVariables; uiNumberOfVariable++ ){
		
		vecVariablesDefined.push_back( new cFibVariable( this ) );
	}
	//create the areas
	for ( unsignedIntFib uiNumberOfArea = 0;
			uiNumberOfArea < iuNumberOfDimensions; uiNumberOfArea++ ){
		
		vecMatrixDimensionAreas.push_back( new cVectorArea( this ) );
	}
	
	if ( pInSuperiorElement ){
		pInSuperiorElement->insertObjectInElement( this );
	}else{
		updateAllValues();
	}
}


/**
 * copyconstructor
 * This copyconstructor constructs a copy of the given matrix element.
 * It dosn't copy other Fib elements than the given, even if ther are
 * in the matrix element.
 *
 * @param matrixElement the matrix element to copy
 */
cFibMatrix::cFibMatrix( const cFibMatrix &matrixElement ):
		cFibLimb( matrixElement ),
		vecMatrixDimensionAreas( matrixElement.vecMatrixDimensionAreas.size(), NULL ),
		liFibMatrix( matrixElement.liFibMatrix ),
		uiDomainNr( matrixElement.uiDomainNr ){
	
	const unsignedIntFib iuNumberOfVariables =
		matrixElement.vecVariablesDefined.size();
	for ( unsignedIntFib uiNumberOfVariable = 0;
			uiNumberOfVariable < iuNumberOfVariables; uiNumberOfVariable++ ){
		
		vecVariablesDefined.push_back( new cFibVariable( this ) );
	}
	//set this matrix element as the defining element of all vectors
	const unsigned int uiNumberOfMatrixAreaVectors =
		matrixElement.vecMatrixDimensionAreas.size();
	for ( unsigned int uiActualMatrixAreaVector = 0;
			uiActualMatrixAreaVector < uiNumberOfMatrixAreaVectors;
			uiActualMatrixAreaVector++ ){
		
		vecMatrixDimensionAreas[ uiActualMatrixAreaVector ] = new cVectorArea(
			*(matrixElement.vecMatrixDimensionAreas[uiActualMatrixAreaVector]),
			this );
	}

	for ( list<cVectorFibMatrix>::iterator itrFibMatrix = liFibMatrix.begin();
			 itrFibMatrix != liFibMatrix.end(); itrFibMatrix++ ){
		
		itrFibMatrix->setDefiningFibElement( this, false );
	}
}


/**
 * The constructor for restoring a matrix element from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the Fib object is stored in
 * @param outStatus An reference to an integervalue where the errorvalue
 * 	can be stored to.
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 * @param liDefinedVariables a list with the defined variables for the
 * 	to restore Fib element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 */
cFibMatrix::cFibMatrix( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables ): uiDomainNr( 0 ){
	
	DEBUG_OUT_L2(<<"cFibMatrix() restore XML started"<<endl);
	if ( pXmlElement == NULL ){
		//noting to restore
		DEBUG_OUT_EL2(<<"Error: noting to restore"<<endl);
		outStatus = -1;
		return;
	}
	const string szElementType( pXmlElement->Value() );
	if ( szElementType != "matrix" ){
		//wrong element type to restore
		DEBUG_OUT_EL2(<<"Error: wrong element type to restore"<<endl);
		outStatus = -2;
		return;
	}
	
	//read the number of dimensions
	const char * szNumberOfDimensions = pXmlElement->Attribute( "dimensions" );
	unsigned int uiNumberOfDimensions = 0;
	if ( szNumberOfDimensions != NULL ){
		//a dimensions attribut exists
		uiNumberOfDimensions = atol( szNumberOfDimensions );
	}else{//no dimensions attribut exists
		DEBUG_OUT_EL2(<<"Warning: no dimensions attribut exists"<<endl);
		outStatus = 2;
	}

	//read the domain number
	const char * szDomainNumber = pXmlElement->Attribute( "domainNr" );
	if ( szDomainNumber != NULL ){
		//the optional attribute domainNr exists
		uiDomainNr = atol( szDomainNumber );
	}
	
	unsigned int uiNumberOfAreasRestored = 0;
	unsigned int uiNumberOfVectorElements = 0;
	for ( const TiXmlNode * pChild = pXmlElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ) {
		
		const int iType = pChild->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid Fib element xml -element, create
				the apropirate Fib element and call its restoreXml() method*/
				const TiXmlElement * pXmlElement = pChild->ToElement();
				if ( pXmlElement == NULL ){
					DEBUG_OUT_EL2(<<"Warning: can not convert child element to TiXmlElement"<<endl);
					outStatus = 2;
					continue;
				}
				const string szElementType( pXmlElement->Value() );
				
				if ( szElementType == "defined_variables" ){
					//read the defined variables
					const TiXmlElement * pXmlDefVariable = NULL;
					if ( pXmlElement->FirstChild( "variable" ) ){
						
						pXmlDefVariable = pXmlElement->FirstChild( "variable" )->ToElement();
					}
					const unsigned long lBiggestDefinedVarValue = liDefinedVariables.size();
					for( int iActualDefVariable = 1; pXmlDefVariable != NULL;
							pXmlDefVariable = pXmlDefVariable->NextSiblingElement( "variable" ),
							iActualDefVariable++ ){

						int iNumberOfDefVariable = 0;
						const char * szXmlObjectNumber = pXmlDefVariable->Attribute( "number", & iNumberOfDefVariable );
						if ( szXmlObjectNumber != NULL ){
							//defined variable number given
							if ( iActualDefVariable != iNumberOfDefVariable ){
								//Warning: no correct defined variable number
								DEBUG_OUT_EL2(<<"Warning: no correct defined variable number"<<endl);
								outStatus = 2;
							}
						}
						
						const char * pcValue = pXmlDefVariable->GetText();
						unsigned long lDefVariableValue = 0;
						if ( pcValue ){
							const int iReadValues = sscanf( pcValue, "%lu", & lDefVariableValue );
							if ( iReadValues != 1){
								//Warning: The element text is not a number.
								DEBUG_OUT_EL2(<<"Warning: The variables element text is not a number"<<endl);
								outStatus = 2;
								continue;
							}
						}
						
						if ( ( pcValue == NULL ) ||
								( lDefVariableValue < lBiggestDefinedVarValue + iActualDefVariable ) ){
							//Warning: no correct variable identifier / number
							DEBUG_OUT_EL2(<<"Warning: no correct variable identifier / number"<<endl);
							outStatus = 2;
							lDefVariableValue = lBiggestDefinedVarValue + iActualDefVariable;
						}
						vecVariablesDefined.push_back( new cFibVariable( this ) );
						vecVariablesDefined.back()->setIntegerValue( lDefVariableValue );
						liDefinedVariables.push_front( vecVariablesDefined.back() );
					}//end for all defined variables
				}else if ( szElementType == "areas" ){
					//read vectors with the dimension areas
					
					const TiXmlElement * pXmlVector = NULL;
					if ( pXmlElement->FirstChild( "vector" ) ){
						
						pXmlVector = pXmlElement->FirstChild( "vector" )->ToElement();
					}
					for( ; pXmlVector != NULL;
							pXmlVector = pXmlVector->NextSiblingElement( "vector" ) ){
					
						//check the attribute of the vector
						const char * szVectorXmlType = pXmlVector->Attribute( "type" );
						
						if ( szVectorXmlType == NULL ){
							DEBUG_OUT_EL2(<<"Warning: no type attribute for the area vector"<<endl);
							outStatus = 2;
							continue;
						}else if ( string( "area" ).compare( szVectorXmlType ) != 0 ){
							DEBUG_OUT_EL2(<<"Warning: not an area vector to restore"<<endl);
							outStatus = 2;
							continue;
						}
						//restore the areavector
						vecMatrixDimensionAreas.push_back( new cVectorArea(
							pXmlVector, outStatus, liDefinedVariables ) );
						vecMatrixDimensionAreas.back()->setDefiningFibElement( this, false );
						
						if ( outStatus < 0 ){
							return;
						}
						uiNumberOfAreasRestored++;
					}//end for all vectors
					
				}else if ( szElementType == "values" ){
					//read vectors with values to matrix
					
					const TiXmlElement * pXmlVector = NULL;
					if ( pXmlElement->FirstChild( "vector" ) ){
						
						pXmlVector = pXmlElement->FirstChild( "vector" )->ToElement();
					}
					for( ; pXmlVector != NULL;
							pXmlVector = pXmlVector->NextSiblingElement( "vector" ) ){
					
						//check the attribute of the vector
						const char * szVectorXmlType = pXmlVector->Attribute( "type" );
						
						if ( szVectorXmlType == NULL ){
							DEBUG_OUT_EL2(<<"Warning: no type attribute for the vector"<<endl);
							outStatus = 2;
							continue;
						}else if ( string( "matrix" ).compare( szVectorXmlType ) != 0 ){
							DEBUG_OUT_EL2(<<"Warning: not an matrix vector to restore"<<endl);
							outStatus = 2;
							continue;
						}
						//restore the areavector
						liFibMatrix.push_back( cVectorFibMatrix( pXmlVector, outStatus,
							liDefinedVariables ) );
						liFibMatrix.back().setDefiningFibElement( this, false );
						if ( outStatus < 0 ){
							return;
						}
						if ( liFibMatrix.size() == 1 ){
							uiNumberOfVectorElements = liFibMatrix.back().getNumberOfElements();
						}else{
							if ( uiNumberOfVectorElements !=
									liFibMatrix.back().getNumberOfElements() ){
								//Warning: the vectors have a different number of elements
								DEBUG_OUT_EL2(<<"Warning: the vectors have a different number of elements"<<endl);
								outStatus = 2;
							}
						}
						
					}//end for all vectors
					
				}else{//restore the subobject
					if ( pUnderObject == NULL ){
						pUnderObject = cFibElement::restoreXml(
							pChild, outStatus, liDefinedVariables );
						if ( pUnderObject ){
							pUnderObject->pSuperiorElement = this;
						}
						if ( outStatus < 0 ){
							//an error occured
							return;
						}
					}else{//to many subobjects -> no correct matrix element
						DEBUG_OUT_EL2(<<"Warning: to many subobjects -> no correct matrix element"<<endl);
						outStatus = 2;
						continue;
					}
				}
			}break;
			
			case TiXmlNode::DECLARATION:
			case TiXmlNode::COMMENT:{
				//ignore
				continue;
			}break;
			case TiXmlNode::DOCUMENT:
			case TiXmlNode::TEXT:
			case TiXmlNode::UNKNOWN:
			default:
				//invalid matrix element
				if ( outStatus ){
					DEBUG_OUT_EL2(<<"Warning: invalid matrix element"<<endl);
					outStatus = 2;
				}
				continue;
		}
	}//end switch restore matrix element elements
	
	if ( uiNumberOfAreasRestored != uiNumberOfDimensions ){
		//Warning: wrong number areas for the dimensions restored
		DEBUG_OUT_EL2(<<"Warning: wrong number areas for the dimensions restored (restored="<<uiNumberOfAreasRestored<<" but "<<uiNumberOfDimensions<<" dimensions"<<endl);
		outStatus = 2;
	}
	if ( vecMatrixDimensionAreas.empty() ){
		//Warning: minimum one dimension
		DEBUG_OUT_EL2(<<"Warning: minimum one dimension, but non ther"<<endl);
		outStatus = 2;
		vecMatrixDimensionAreas.push_back( new cVectorArea( this ) );
	}
	if ( ! liFibMatrix.empty() ){
		const unsignedIntFib iuNumberOfVariables =
			vecMatrixDimensionAreas.size() + uiNumberOfVectorElements;
		if ( vecVariablesDefined.size() != iuNumberOfVariables ){
			//Warning: the number defined variables restored is wrong
			DEBUG_OUT_EL2(<<"Warning: the number defined variables ("<<vecVariablesDefined.size()<<") restored is wrong (should be "<<iuNumberOfVariables<<"; dimensions="<<vecMatrixDimensionAreas.size()<<", vector elements="<<uiNumberOfVectorElements<<")"<<endl);
			outStatus = 2;
			//create missing defined variables
			for ( unsignedIntFib uiNumberOfVariable = vecVariablesDefined.size();
					uiNumberOfVariable < iuNumberOfVariables; uiNumberOfVariable++ ){
				
				vecVariablesDefined.push_back( new cFibVariable( this ) );
			}
		}
	}
	if ( pUnderObject == NULL ){
		//Error: No subobject restored
		DEBUG_OUT_EL2(<<"Error: No subobject restored"<<endl);
		outStatus = -2;
		return;
	}
}


/**
 * This constructor restores a matrix element from the stream where it is
 * stored in the compressed Fib format.
 * This constructor is for internal use only.
 *
 * @param iBitStream the stream wher the matrix element is stored in,
 * 	because this stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @param outStatus An reference to an integer value where the error value
 * 	can be stored to. If the pointer is NULL no error value will be
 * 	given back.
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 * @param liDefinedVariables a list with the defined variables for the
 * 	to restore Fib element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 * @param validDomains the domains valid for restoring the Fib elements
 * @param pNextRoot the next higher root-element for the to restore
 * 	Fib elements, or the last restored root-element
 */
cFibMatrix::cFibMatrix( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot ):
		uiDomainNr( 0 ){
	
	DEBUG_OUT_L2(<<"cFibMatrix() restore bit"<<endl);
	if ( ! iBitStream.getStream()->good() ){
		DEBUG_OUT_EL2(<<"Error: invalid bit stream"<<endl);
		outStatus = -1;
		return;
	}
	//read bit if a domain number is given
	unsigned char bReadedBit = 0;
	const unsigned int uiBitsRead = iBitStream.readBits( (char*)(&bReadedBit), 1 );
	if ( uiBitsRead != 1 ){
		//Warning: not just one bit read
		DEBUG_OUT_EL2(<<"Warning: not just one bit read"<<endl);
		outStatus = 2;
		bReadedBit = 0;
	}
	if ( bReadedBit != 0 ){
		//read domain number
		//find greatest domain number in the value domains
		unsignedIntFib uiMaxNumberOfMatrixDomain = 0;
		const unsignedIntFib uiNumberOfDomains = validDomains.getNumberOfDomains();
		for ( unsignedIntFib uiActualDomain = 1; uiActualDomain <= uiNumberOfDomains;
				uiActualDomain++ ){
			
			const cTypeElement * pTypeElement = validDomains.getType( uiActualDomain );
			if ( ( pTypeElement != NULL ) && ( pTypeElement->getType() == 15 ) ){
				//the type is a cTypeFibMatrix type
				const unsignedIntFib uiNumberOfMatrixDomain =
					((cTypeFibMatrix*)(pTypeElement))->getNumberOfDomain();
				if ( uiMaxNumberOfMatrixDomain < uiNumberOfMatrixDomain ){
					uiMaxNumberOfMatrixDomain = uiNumberOfMatrixDomain;
				}
			}
		}//end for search all domains for maximal matrix element domain
		//read domain number
		cDomainNaturalNumber domainForMatrixDomainNumber( uiMaxNumberOfMatrixDomain );
		
		uiDomainNr = domainForMatrixDomainNumber.restoreIntegerValue( iBitStream, outStatus );
		if ( outStatus < 0 ){
			//Warning: domain number not readed correctly
			DEBUG_OUT_EL2(<<"Warning: domain number not readed correctly"<<endl);
			outStatus = 2;
			uiDomainNr = 0;
		}
	}
	
	//get the matrix element domain
	cDomain * pDomainFibMatrixBase = NULL;
	for ( intFib uiActualDomain = uiDomainNr; 0 <= uiActualDomain;
			uiActualDomain-- ){
		
		const cTypeFibMatrix typeFibMatrix( uiActualDomain );
		pDomainFibMatrixBase = validDomains.getDomainForElement( typeFibMatrix );
			
		if ( pDomainFibMatrixBase != NULL ){
			break;
		}
	}
	const bool bStandardDomainFibMatrix = ( pDomainFibMatrixBase == NULL );
	if ( bStandardDomainFibMatrix ){
		const cTypeFibMatrix typeFibMatrix;
		pDomainFibMatrixBase = typeFibMatrix.getStandardDomain();
	}
	if ( ! pDomainFibMatrixBase->isVector() ){
		//Error: in domain not a vector domain -> can't load matrix object
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrixBase;
		}
		DEBUG_OUT_EL2(<<"Error: in domain not a vector domain -> can't load matrix object"<<endl);
		outStatus = -2;
		return;
	}
	const cDomainVectorBasis * pDomainFibMatrix =
		(cDomainVectorBasis*)pDomainFibMatrixBase;
	if ( pDomainFibMatrix->getNumberOfElements() < 4 ){
		/*error in domain (domain for number of defined variables and / or
		number of vectors and / or vectors missing) -> can't load matrix object*/
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		DEBUG_OUT_EL2(<<"Error: in domain (domain for number of defined variables and / or number of vectors and / or vectors missing) -> can't load matrix object"<<endl);
		outStatus = -2;
		return;
	}
	const cDomainIntegerBasis * pDomainDefVariablesCount = ((cDomainIntegerBasis*)(
		pDomainFibMatrix->getElementDomain( 1 ) ));
	if ( pDomainDefVariablesCount == NULL ){
		/*error in domain (domain for number of defined variables missing)
		-> can't load matrix object*/
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		outStatus = -2;
		return;
	}
	
	//restore the number of dimension (variables)
	const unsignedIntFib uiNumberOfDimensions =
		pDomainDefVariablesCount->restoreIntegerValue( iBitStream, outStatus );
	if ( outStatus < 0 ){
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		return;
	}
	//restore the number of vector elements (variables)
	const unsignedIntFib uiNumberOfVectorElements =
		pDomainDefVariablesCount->restoreIntegerValue( iBitStream, outStatus );
	if ( outStatus < 0 ){
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		return;
	}
	
	//restore number of vectors with the to matrix values
	const cDomainIntegerBasis * pDomainVectorsCount = ((cDomainIntegerBasis*)(
		pDomainFibMatrix->getElementDomain( 2 ) ));
	if ( pDomainVectorsCount == NULL ){
		/*error in domain (domain for number of vectors with the to matrix values missing)
		-> can't load matrix object*/
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		outStatus = -2;
		return;
	}
	//restore number of vectors with the to matrix values
	const unsignedLongFib uiNumberOfVectors =
		pDomainVectorsCount->restoreIntegerValue( iBitStream, outStatus );
	if ( outStatus < 0 ){
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		return;
	}
	//get domain for the vectors with the to matrix area values
	const cDomain * pDomainFibMatrixAreaVectorDom =
		pDomainFibMatrix->getElementDomain( 3 );
	if ( ( pDomainFibMatrixAreaVectorDom == NULL ) ||
			( ! pDomainFibMatrixAreaVectorDom->isVector() ) ){
		/*error in domain (domain for the vectors with the to matrix values
		 * missing or not a vector domain) -> can't load matrix object*/
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		outStatus = -2;
		return;
	}
	const cDomainVectorBasis * pDomainFibMatrixAreaVector = ((cDomainVectorBasis*)(
		pDomainFibMatrixAreaVectorDom ));
	//get domain for the vectors with the to matrix values
	const cDomain * pDomainFibMatrixVectorDom = pDomainFibMatrix->getElementDomain( 4 );
	if ( ( pDomainFibMatrixVectorDom == NULL ) ||
			( ! pDomainFibMatrixVectorDom->isVector() ) ){
		/*error in domain (domain for the vectors with the to matrix values
		 * missing or not a vector domain) -> can't load matrix object*/
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		outStatus = -2;
		return;
	}
	const cDomainVectorBasis * pDomainFibMatrixVector = ((cDomainVectorBasis*)(
		pDomainFibMatrixVectorDom ));
	//get the domain for the variables in this vector
	const cTypeVariable typeVariable;
	//return the variable domain
	const cDomainIntegerBasis * pDomainVariable = (cDomainIntegerBasis*)
		validDomains.getDomainForElement( typeVariable );
	const bool bStandardDomainVariable = ( pDomainVariable == NULL );
	if ( bStandardDomainVariable ){
		//use the standard domain
		pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
	}
	
	//restore the vectors with the to matrix dimension areas
	for ( unsignedLongFib uiActualAreaVector = 1;
			uiActualAreaVector <= uiNumberOfDimensions; uiActualAreaVector++ ){
		
		vecMatrixDimensionAreas.push_back( new cVectorArea( iBitStream, outStatus,
			liDefinedVariables, pDomainFibMatrixAreaVector, pDomainVariable ) );
		
		vecMatrixDimensionAreas.back()->setDefiningFibElement( this, false );
		if ( outStatus < 0 ){
			break;
		}
	}//end for restore the vectors with the matrix dimension areas
	//restore the vectors with the to matrix values
	if ( 0 < uiNumberOfVectorElements ){
		for ( unsignedLongFib uiActualVector = 1;
				uiActualVector <= uiNumberOfVectors; uiActualVector++ ){
			
			liFibMatrix.push_back( cVectorFibMatrix( iBitStream, outStatus,
				liDefinedVariables, pDomainFibMatrixVector, pDomainVariable,
				uiNumberOfVectorElements ) );
			
			liFibMatrix.back().setDefiningFibElement( this, false );
			if ( outStatus < 0 ){
				break;
			}
		}//end for restore the vectors with the to matrix values
	}else{//the set vectors have no elements
		for ( unsignedLongFib uiActualVector = 1;
				uiActualVector <= uiNumberOfVectors; uiActualVector++ ){
			
			liFibMatrix.push_back( cVectorFibMatrix( 0 ) );
			
			liFibMatrix.back().setDefiningFibElement( this, false );
		}//end for create the vectors with the to matrix values
	}
	if ( bStandardDomainFibMatrix ){
		delete pDomainFibMatrix;
	}
	if ( bStandardDomainVariable ){
		delete pDomainVariable;
	}
	//create defined variables for the subobject
	//evalue the number of defined variables
	const unsignedIntFib uiNumberDefVariables =
		uiNumberOfDimensions + uiNumberOfVectorElements;
	const unsignedIntFib uiCountDefVariablesBefor = liDefinedVariables.size();
	for ( unsignedIntFib uiNumberOfVariable = 1;
			uiNumberOfVariable <= uiNumberDefVariables; uiNumberOfVariable++ ){
		
		vecVariablesDefined.push_back( new cFibVariable( this ) );
		vecVariablesDefined.back()->setIntegerValue(
			uiCountDefVariablesBefor + uiNumberOfVariable );
		liDefinedVariables.push_front( vecVariablesDefined.back() );
	}
	if ( outStatus < 0 ){
		//an error occured -> don't restore subobject
		return;
	}

	//restore the subobject
	pUnderObject = cFibElement::restoreInternal( iBitStream, outStatus,
		liDefinedVariables, validDomains, pNextRoot );
	if ( pUnderObject ){
		pUnderObject->pSuperiorElement = this;
	}
}


/**
 * destructor
 */
cFibMatrix::~cFibMatrix(){
	
	for ( vector< cFibVariable * >::iterator
			itrDefVariable = vecVariablesDefined.begin();
			itrDefVariable != vecVariablesDefined.end(); itrDefVariable++ ){
		
		delete (*itrDefVariable);
	}
	//automatic: vecVariablesDefined.clear()
	for ( vector< cVectorArea * >::iterator
			itrMatrixAreaVector = vecMatrixDimensionAreas.begin();
			itrMatrixAreaVector != vecMatrixDimensionAreas.end(); itrMatrixAreaVector++ ){
		
		delete (*itrMatrixAreaVector);
	}
	//automatic: vecMatrixDimensionAreas.clear()
}


/**
 * @see getTypeName
 * @return a character for the typ of the Fib element
 * Types are:
 * 	- u: element of unknown typ
 * 	- p: point
 * 	- l: list-element
 * 	- y: property
 * 	- c: comment
 * 	- a: area
 * 	- f: function
 * 	- i: if-condition
 * 	- o: extern object element
 * 	- s: extern subobject element
 * 	- v: set-element
 * 	- m: matrix element
 * 	- r: root-element
 */
char cFibMatrix::getType() const{
	return 'm';
}


/**
 * This method checks, if this Fib-element is an valid Fib-element.
 *
 * @return true if this Fib-element is an valid Fib-element, else false
 */
bool cFibMatrix::isValidFibElement() const{
	
	if ( vecVariablesDefined.empty() ){
		//no defined variables -> matrix element not valid
		return false;
	}
	if ( vecMatrixDimensionAreas.empty() ){
		//no vectors with values to matrix -> matrix element not valid
		return false;
	}
	//check contained vectors
	const unsignedIntFib uiNumberVectorElements = getNumberOfVectorElements();
	for ( list< cVectorFibMatrix >::const_iterator itrActualVector = liFibMatrix.begin();
			 itrActualVector != liFibMatrix.end(); itrActualVector++ ){
	
		if ( itrActualVector->getNumberOfElements() != uiNumberVectorElements ){
			//vector has wrong number of elements
			return false;
		}
	}
	//everything is ok
	return true;
}


/**
 * This method evaluades the Fib object.
 *
 * @param evaluePosition a reference to the object with the
 * 	evaluePosition() method to evalue /store the positions and ther
 * 	properties; everytime a point (to evalue) is reached in the
 * 	evaluation, this method is called with the position and the
 * 	properties of the point; @see iEvaluePosition
 * @param objectPoint the object point in the order of true part objects
 * 	to evalue
 * @param liVecProperties a list with the property vectors which should
 * 	be global for the evalued object
 * @return if the evaluation was successfull true, else false
 */
bool cFibMatrix::evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const{
	
	if ( ( pUnderObject == NULL ) || vecMatrixDimensionAreas.empty() ){
		//nothing to evalue
		return false;
	}
	//init dimension counters
	const unsigned int uiDimensions = vecMatrixDimensionAreas.size();
	vector< longFib > vecDimCounter( uiDimensions );
	//set dimension counters to the dimension areas lower bounds
	for ( unsigned int uiActualDimension = 0;
			uiActualDimension < uiDimensions; uiActualDimension++ ){
		
		vecDimCounter[ uiActualDimension ] =
			vecMatrixDimensionAreas[ uiActualDimension ]->getLowerBound();
	}
	
	//handle the dimension 0 seperatly
	const longFib lLowerBound0 = vecMatrixDimensionAreas[ 0 ]->getLowerBound();
	const longFib lUpperBound0 = vecMatrixDimensionAreas[ 0 ]->getUpperBound();
	const bool bCountUp0 = ( lLowerBound0 < lUpperBound0 );
	
	if ( ! liFibMatrix.empty() ){
		//matrix enties exists
		const unsigned int uiNumberVectorElements = getNumberOfVectorElements();
		
		for ( list< cVectorFibMatrix >::const_iterator
				itrActualVector = liFibMatrix.begin();
				itrActualVector != liFibMatrix.end(); itrActualVector++ ){
			//set the defined variables to the values of the dimension counters
			vector< cFibVariable* >::iterator itrActualDefVariable =
				const_cast<cFibMatrix*>(this)->vecVariablesDefined.begin();
			for ( unsigned int uiActualDimension = 0;
					uiActualDimension < uiDimensions; uiActualDimension++ ){
				
				(*itrActualDefVariable)->setIntegerValue(
					vecDimCounter[ uiActualDimension ] );
				itrActualDefVariable++;
			}
			//set the remaining defined variables to the values of the vectors
			for ( unsigned int uiActualVectorElement = 1;
					uiActualVectorElement <= uiNumberVectorElements;
					uiActualVectorElement++, itrActualDefVariable++ ){
				
				(*itrActualDefVariable)->setValue(
					itrActualVector->getValue( uiActualVectorElement ) );
			}

			//call subobject with the defined variables matrix to the actual to matrix values
			list<cVectorProperty> liVecSubProperties = liVecProperties;
			
			const bool bUnderObjectEvalued = pUnderObject->evalueObject(
				evaluePosition, objectPoint, liVecSubProperties );
			if ( ! bUnderObjectEvalued ){
				//stop evaluing
				return false;
			}
			//count one up
			if ( ( bCountUp0 && ( vecDimCounter[ 0 ] < lUpperBound0 ) ) ||
					( ( ! bCountUp0 ) && ( lUpperBound0 < vecDimCounter[ 0 ] ) ) ){
				//count just counter 0
				if ( bCountUp0 ){
					//count up
					vecDimCounter[ 0 ]++;
				}else{//count down
					vecDimCounter[ 0 ]--;
				}
				
			}else{//count other dimensions up
				bool bStopEvaluation = true;
				for ( unsigned int uiActualDimension = 0;
						uiActualDimension < uiDimensions; uiActualDimension++ ){
					
					const longFib lLowerBoundActual =
						vecMatrixDimensionAreas[ uiActualDimension ]->getLowerBound();
					const longFib lUpperBoundActual =
						vecMatrixDimensionAreas[ uiActualDimension ]->getUpperBound();
					const bool bCountUpActual = ( lLowerBoundActual < lUpperBoundActual );
					
					if ( ( bCountUpActual &&
								( vecDimCounter[ uiActualDimension ] < lUpperBoundActual ) ) ||
							( ( ! bCountUpActual ) &&
								( lUpperBoundActual < vecDimCounter[ uiActualDimension ] ) ) ){
						//upper boundery not reached for actual dimension -> count one up
						if ( bCountUpActual ){
							//count up
							vecDimCounter[ uiActualDimension ]++;
						}else{//count down
							vecDimCounter[ uiActualDimension ]--;
						}
						//can evalue next set of values
						bStopEvaluation = false;
						break;
					}else{/*actual dimension counter has reached the upper bound
						-> set it to its lower bound and check next counter*/
						vecDimCounter[ uiActualDimension ] = lLowerBoundActual;
					}
				}//done count dimensions one up
				
				if ( bStopEvaluation ){
					//stop evaluation
					break;
				}
			}//end if count dimension counters one up
		}//end for all matrix entries
	}else{//liFibMatrix.empty() -> run trought all dimension areas
		
		while ( true ){
			//set the defined variables to the values of the dimension counters
			vector< cFibVariable* >::iterator itrActualDefVariable =
				const_cast<cFibMatrix*>(this)->vecVariablesDefined.begin();
			for ( unsigned int uiActualDefVariable = 0;
					uiActualDefVariable < uiDimensions;
					uiActualDefVariable++, itrActualDefVariable++ ){
				
				(*itrActualDefVariable)->setIntegerValue(
					vecDimCounter[ uiActualDefVariable ] );
			}
			//call subobject with the defined variables matrix to the actual to matrix values
			list<cVectorProperty> liVecSubProperties = liVecProperties;
			
			const bool bUnderObjectEvalued = pUnderObject->evalueObject(
				evaluePosition, objectPoint, liVecSubProperties );
			if ( ! bUnderObjectEvalued ){
				//stop evaluing
				return false;
			}
			//count one up
			if ( ( bCountUp0 && ( vecDimCounter[ 0 ] < lUpperBound0 ) ) ||
					( ! bCountUp0 && ( lUpperBound0 < vecDimCounter[ 0 ] ) ) ){
				//count just counter 0
				if ( bCountUp0 ){
					//count up
					vecDimCounter[ 0 ]++;
				}else{//count down
					vecDimCounter[ 0 ]--;
				}
				
			}else{//count other dimensions up
				bool bStopEvaluation = true;
				for ( unsigned int uiActualDimension = 0;
						uiActualDimension < uiDimensions; uiActualDimension++ ){
					
					const longFib lLowerBoundActual =
						vecMatrixDimensionAreas[ uiActualDimension ]->getLowerBound();
					const longFib lUpperBoundActual =
						vecMatrixDimensionAreas[ uiActualDimension ]->getUpperBound();
					const bool bCountUpActual = ( lLowerBoundActual < lUpperBoundActual );
					
					if ( ( bCountUpActual &&
								( vecDimCounter[ uiActualDimension ] < lUpperBoundActual ) ) ||
							( ( ! bCountUpActual ) &&
								( lUpperBoundActual < vecDimCounter[ uiActualDimension ] ) ) ){
						//upper boundery not reached for actual dimension -> count one up
						if ( bCountUpActual ){
							//count up
							vecDimCounter[ uiActualDimension ]++;
						}else{//count down
							vecDimCounter[ uiActualDimension ]--;
						}
						//can evalue next set of values
						bStopEvaluation = false;
						break;
					}else{/*actual dimension counter has reached the upper bound
						-> set it to its lower bound and check next counter*/
						vecDimCounter[ uiActualDimension ] = lLowerBoundActual;
					}
				}//done count dimensions one up
				
				if ( bStopEvaluation ){
					//stop evaluation
					break;
				}
			}//end if count dimension counters one up
		}//end while evalue matrix entries
	}//end if matrix enties exists
	
	return true;
}


/**
 * This method evaluades the Fib object.
 * Evertime a Fib elements, with a type of the given type chars in
 * liCFibElementTyps, is reached while evaluation, it is given
 * back with the properties which it has.
 * Ever point element is given back. The type chars for point elements
 * don't need to be in the list liCFibElementTyps.
 *
 * @param evalueFibElement a reference to the object with the
 * 	evalueElement() method to evalue /store the Fib elements and ther
 * 	properties; everytime a Fib element (with one of the type given
 * 	in liCFibElementTyps) is reached in the evaluation, the method
 * 	evalueElement() of this objects is called with the Fib element
 * 	and the properties of the Fib element; @see iEvalueFibElement
 * @param objectPoint the object point in the order of true part objects
 * 	to evalue
 * @param liVecProperties a list with the property vectors which should
 * 	be global for the evalued object
 * @param liCFibElementTyps a list with the type chars (@see getType() )
 * 	of the Fib elements to return
 * @return if the evaluation was successfull true, else false
 */
bool cFibMatrix::evalueObject( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties,
		const list<char> & liCFibElementTyps ){
	
	//check if this Fib element should be given back with evalueElement()
	const char cThisType = getType();
	for ( list<char>::const_iterator itrCType = liCFibElementTyps.begin();
			itrCType != liCFibElementTyps.end(); itrCType++ ){
		
		if ( (*itrCType) == cThisType ){
			//call evalueElement() with this element
			return evalueFibElement.evalueElement( *this, liVecProperties );
		}
	}//else if this element shouldn't be returned -> evalue the subobject

	if ( ( pUnderObject == NULL ) || ( vecMatrixDimensionAreas.empty() ) ){
		//nothing to evalue
		return false;
	}
	
	//init dimension counters
	const unsigned int uiDimensions = vecMatrixDimensionAreas.size();
	vector< longFib > vecDimCounter( uiDimensions );
	//set dimension counters to the dimension areas lower bounds
	for ( unsigned int uiActualDimension = 0;
			uiActualDimension < uiDimensions; uiActualDimension++ ){
		
		vecDimCounter[ uiActualDimension ] =
			vecMatrixDimensionAreas[ uiActualDimension ]->getLowerBound();
	}
	
	//handle the dimension 0 seperatly
	const longFib lLowerBound0 = vecMatrixDimensionAreas[ 0 ]->getLowerBound();
	const longFib lUpperBound0 = vecMatrixDimensionAreas[ 0 ]->getUpperBound();
	const bool bCountUp0 = ( lLowerBound0 < lUpperBound0 );
	
	if ( ! liFibMatrix.empty() ){
		//matrix enties exists
		const unsigned int uiNumberVectorElements = getNumberOfVectorElements();
		
		for ( list< cVectorFibMatrix >::const_iterator
				itrActualVector = liFibMatrix.begin();
				itrActualVector != liFibMatrix.end(); itrActualVector++ ){
			//set the defined variables to the values of the dimension counters
			vector< cFibVariable* >::iterator itrActualDefVariable =
				const_cast<cFibMatrix*>(this)->vecVariablesDefined.begin();
			for ( unsigned int uiActualDimension = 0;
					uiActualDimension < uiDimensions; uiActualDimension++ ){
				
				(*itrActualDefVariable)->setIntegerValue(
					vecDimCounter[ uiActualDimension ] );
				itrActualDefVariable++;
			}
			//set the remaining defined variables to the values of the vectors
			for ( unsigned int uiActualVectorElement = 1;
					uiActualVectorElement <= uiNumberVectorElements;
					uiActualVectorElement++, itrActualDefVariable++ ){
				
				(*itrActualDefVariable)->setValue(
					itrActualVector->getValue( uiActualVectorElement ) );
			}

			//call subobject with the defined variables matrix to the actual to matrix values
			list<cVectorProperty> liVecSubProperties = liVecProperties;
			
			const bool bUnderObjectEvalued = pUnderObject->evalueObject(
				evalueFibElement, objectPoint, liVecSubProperties, liCFibElementTyps );
			if ( ! bUnderObjectEvalued ){
				//stop evaluing
				return false;
			}
			//count one up
			if ( ( bCountUp0 && ( vecDimCounter[ 0 ] < lUpperBound0 ) ) ||
					( ( ! bCountUp0 ) && ( lUpperBound0 < vecDimCounter[ 0 ] ) ) ){
				//count just counter 0
				if ( bCountUp0 ){
					//count up
					vecDimCounter[ 0 ]++;
				}else{//count down
					vecDimCounter[ 0 ]--;
				}
				
			}else{//count other dimensions up
				bool bStopEvaluation = true;
				for ( unsigned int uiActualDimension = 0;
						uiActualDimension < uiDimensions; uiActualDimension++ ){
					
					const longFib lLowerBoundActual =
						vecMatrixDimensionAreas[ uiActualDimension ]->getLowerBound();
					const longFib lUpperBoundActual =
						vecMatrixDimensionAreas[ uiActualDimension ]->getUpperBound();
					const bool bCountUpActual = ( lLowerBoundActual < lUpperBoundActual );
					
					if ( ( bCountUpActual &&
								( vecDimCounter[ uiActualDimension ] < lUpperBoundActual ) ) ||
							( ( ! bCountUpActual ) &&
								( lUpperBoundActual < vecDimCounter[ uiActualDimension ] ) ) ){
						//upper boundery not reached for actual dimension -> count one up
						if ( bCountUpActual ){
							//count up
							vecDimCounter[ uiActualDimension ]++;
						}else{//count down
							vecDimCounter[ uiActualDimension ]--;
						}
						//can evalue next set of values
						bStopEvaluation = false;
						break;
					}else{/*actual dimension counter has reached the upper bound
						-> set it to its lower bound and check next counter*/
						vecDimCounter[ uiActualDimension ] = lLowerBoundActual;
					}
				}//done count dimensions one up
				
				if ( bStopEvaluation ){
					//stop evaluation
					break;
				}
			}//end if count dimension counters one up
		}//end for all matrix entries
	}else{//liFibMatrix.empty() -> run trought all dimension areas
		
		while ( true ){
			//set the defined variables to the values of the dimension counters
			vector< cFibVariable* >::iterator itrActualDefVariable =
				const_cast<cFibMatrix*>(this)->vecVariablesDefined.begin();
			for ( unsigned int uiActualDefVariable = 0;
					uiActualDefVariable < uiDimensions;
					uiActualDefVariable++, itrActualDefVariable++ ){
				
				(*itrActualDefVariable)->setIntegerValue(
					vecDimCounter[ uiActualDefVariable ] );
			}
			//call subobject with the defined variables matrix to the actual to matrix values
			list<cVectorProperty> liVecSubProperties = liVecProperties;
			
			const bool bUnderObjectEvalued = pUnderObject->evalueObject(
				evalueFibElement, objectPoint, liVecSubProperties, liCFibElementTyps );
			if ( ! bUnderObjectEvalued ){
				//stop evaluing
				return false;
			}
			//count one up
			if ( ( bCountUp0 && ( vecDimCounter[ 0 ] < lUpperBound0 ) ) ||
					( ( ! bCountUp0 ) && ( lUpperBound0 < vecDimCounter[ 0 ] ) ) ){
				//count just counter 0
				if ( bCountUp0 ){
					//count up
					vecDimCounter[ 0 ]++;
				}else{//count down
					vecDimCounter[ 0 ]--;
				}
				
			}else{//count other dimensions up
				bool bStopEvaluation = true;
				for ( unsigned int uiActualDimension = 0;
						uiActualDimension < uiDimensions; uiActualDimension++ ){
					
					const longFib lLowerBoundActual =
						vecMatrixDimensionAreas[ uiActualDimension ]->getLowerBound();
					const longFib lUpperBoundActual =
						vecMatrixDimensionAreas[ uiActualDimension ]->getUpperBound();
					const bool bCountUpActual = ( lLowerBoundActual < lUpperBoundActual );
					
					if ( ( bCountUpActual &&
								( vecDimCounter[ uiActualDimension ] < lUpperBoundActual ) ) ||
							( ( ! bCountUpActual ) &&
								( lUpperBoundActual < vecDimCounter[ uiActualDimension ] ) ) ){
						//upper boundery not reached for actual dimension -> count one up
						if ( bCountUpActual ){
							//count up
							vecDimCounter[ uiActualDimension ]++;
						}else{//count down
							vecDimCounter[ uiActualDimension ]--;
						}
						//can evalue next set of values
						bStopEvaluation = false;
						break;
					}else{/*actual dimension counter has reached the upper bound
						-> set it to its lower bound and check next counter*/
						vecDimCounter[ uiActualDimension ] = lLowerBoundActual;
					}
				}//done count dimensions one up
				
				if ( bStopEvaluation ){
					//stop evaluation
					break;
				}
			}//end if count dimension counters one up
		}//end while evalue matrix entries
	}//end if matrix enties exists
	
	return true;
}


/**
 * This method evaluades a value for the time needed to evalue the
 * object.
 * This value should not exceed lMaxTime, if the value for the time
 * is greater than lMaxTime the evaluation will be stopt and lMaxTime
 * returned. If lMaxTime is 0 (for infinity) the evaluation won't be
 * stoped, this is the standard case.
 *
 * @see evalueObject()
 * @param lMaxTime the maximum time for the evaluation, the returned value
 * 	will not be greater than this value; the value 0 stands for infinity,
 * 	so the evaluation won't be stoped
 * @return a value for the time needed to evalue the object
 */
unsignedLongFib cFibMatrix::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	unsignedLongFib ulTimeNeeded = 0;
	if ( ( pUnderObject == NULL ) || ( vecMatrixDimensionAreas.empty() ) ){
		return ulTimeNeeded;
	}

	//init dimension counters
	const unsigned int uiDimensions = vecMatrixDimensionAreas.size();
	vector< longFib > vecDimCounter( uiDimensions );
	//set dimension counters to the dimension areas lower bounds
	for ( unsigned int uiActualDimension = 0;
			uiActualDimension < uiDimensions; uiActualDimension++ ){
		
		vecDimCounter[ uiActualDimension ] =
			vecMatrixDimensionAreas[ uiActualDimension ]->getLowerBound();
	}
	
	//handle the dimension 0 seperatly
	const longFib lLowerBound0 = vecMatrixDimensionAreas[ 0 ]->getLowerBound();
	const longFib lUpperBound0 = vecMatrixDimensionAreas[ 0 ]->getUpperBound();
	const bool bCountUp0 = ( lLowerBound0 < lUpperBound0 );
	
	if ( ! liFibMatrix.empty() ){
		//matrix enties exists
		const unsigned int uiNumberVectorElements = getNumberOfVectorElements();
		const unsigned int uiNumberOfDefinedVariables =
			vecVariablesDefined.size();
		
		for ( list< cVectorFibMatrix >::const_iterator
				itrActualVector = liFibMatrix.begin();
				itrActualVector != liFibMatrix.end(); itrActualVector++ ){
			//set the defined variables to the values of the dimension counters
			vector< cFibVariable* >::iterator itrActualDefVariable =
				const_cast<cFibMatrix*>(this)->vecVariablesDefined.begin();
			for ( unsigned int uiActualDimension = 0;
					uiActualDimension < uiDimensions; uiActualDimension++ ){
				
				(*itrActualDefVariable)->setIntegerValue(
					vecDimCounter[ uiActualDimension ] );
				itrActualDefVariable++;
			}
			//set the remaining defined variables to the values of the vectors
			for ( unsigned int uiActualVectorElement = 1;
					uiActualVectorElement <= uiNumberVectorElements;
					uiActualVectorElement++, itrActualDefVariable++ ){
				
				(*itrActualDefVariable)->setValue(
					itrActualVector->getValue( uiActualVectorElement ) );
			}
			//call subobject with the defined variables matrix to the actual to matrix values
			if ( lMaxTime == 0 ){
				ulTimeNeeded += uiNumberOfDefinedVariables +
					pUnderObject->getTimeNeed( 0 );
			}else{
				ulTimeNeeded += uiNumberOfDefinedVariables;
				if ( lMaxTime <= ulTimeNeeded ){
					return lMaxTime;
				}
				ulTimeNeeded += pUnderObject->getTimeNeed( lMaxTime - ulTimeNeeded );
				if ( lMaxTime <= ulTimeNeeded ){
					return lMaxTime;
				}
			}
			//count one up
			if ( ( bCountUp0 && ( vecDimCounter[ 0 ] < lUpperBound0 ) ) ||
					( ( ! bCountUp0 ) && ( lUpperBound0 < vecDimCounter[ 0 ] ) ) ){
				//count just counter 0
				if ( bCountUp0 ){
					//count up
					vecDimCounter[ 0 ]++;
				}else{//count down
					vecDimCounter[ 0 ]--;
				}
				
			}else{//count other dimensions up
				bool bStopEvaluation = true;
				for ( unsigned int uiActualDimension = 0;
						uiActualDimension < uiDimensions; uiActualDimension++ ){
					
					const longFib lLowerBoundActual =
						vecMatrixDimensionAreas[ uiActualDimension ]->getLowerBound();
					const longFib lUpperBoundActual =
						vecMatrixDimensionAreas[ uiActualDimension ]->getUpperBound();
					const bool bCountUpActual = ( lLowerBoundActual < lUpperBoundActual );
					
					if ( ( bCountUpActual &&
								( vecDimCounter[ uiActualDimension ] < lUpperBoundActual ) ) ||
							( ( ! bCountUpActual ) &&
								( lUpperBoundActual < vecDimCounter[ uiActualDimension ] ) ) ){
						//upper boundery not reached for actual dimension -> count one up
						if ( bCountUpActual ){
							//count up
							vecDimCounter[ uiActualDimension ]++;
						}else{//count down
							vecDimCounter[ uiActualDimension ]--;
						}
						//can evalue next set of values
						bStopEvaluation = false;
						break;
					}else{/*actual dimension counter has reached the upper bound
						-> set it to its lower bound and check next counter*/
						vecDimCounter[ uiActualDimension ] = lLowerBoundActual;
					}
				}//done count dimensions one up
				
				if ( bStopEvaluation ){
					//stop evaluation
					break;
				}
			}//end if count dimension counters one up
		}//end for all matrix entries
	}else{//liFibMatrix.empty() -> run trought all dimension areas
		
		while ( true ){
			//set the defined variables to the values of the dimension counters
			vector< cFibVariable* >::iterator itrActualDefVariable =
				const_cast<cFibMatrix*>(this)->vecVariablesDefined.begin();
			for ( unsigned int uiActualDefVariable = 0;
					uiActualDefVariable < uiDimensions;
					uiActualDefVariable++, itrActualDefVariable++ ){
				
				(*itrActualDefVariable)->setIntegerValue(
					vecDimCounter[ uiActualDefVariable ] );
			}
			//call subobject with the defined variables matrix to the actual to matrix values
			if ( lMaxTime == 0 ){
				ulTimeNeeded += uiDimensions + pUnderObject->getTimeNeed( 0 );
			}else{
				ulTimeNeeded += uiDimensions;
				if ( lMaxTime <= ulTimeNeeded ){
					return lMaxTime;
				}
				ulTimeNeeded += pUnderObject->getTimeNeed( lMaxTime - ulTimeNeeded );
				if ( lMaxTime <= ulTimeNeeded ){
					return lMaxTime;
				}
			}
			//count one up
			if ( ( bCountUp0 && ( vecDimCounter[ 0 ] < lUpperBound0 ) ) ||
					( ( ! bCountUp0 ) && ( lUpperBound0 < vecDimCounter[ 0 ] ) ) ){
				//count just counter 0
				if ( bCountUp0 ){
					//count up
					vecDimCounter[ 0 ]++;
				}else{//count down
					vecDimCounter[ 0 ]--;
				}
				
			}else{//count other dimensions up
				bool bStopEvaluation = true;
				for ( unsigned int uiActualDimension = 0;
						uiActualDimension < uiDimensions; uiActualDimension++ ){
					
					const longFib lLowerBoundActual =
						vecMatrixDimensionAreas[ uiActualDimension ]->getLowerBound();
					const longFib lUpperBoundActual =
						vecMatrixDimensionAreas[ uiActualDimension ]->getUpperBound();
					const bool bCountUpActual = ( lLowerBoundActual < lUpperBoundActual );
					
					if ( ( bCountUpActual &&
								( vecDimCounter[ uiActualDimension ] < lUpperBoundActual ) ) ||
							( ( ! bCountUpActual ) &&
								( lUpperBoundActual < vecDimCounter[ uiActualDimension ] ) ) ){
						//upper boundery not reached for actual dimension -> count one up
						if ( bCountUpActual ){
							//count up
							vecDimCounter[ uiActualDimension ]++;
						}else{//count down
							vecDimCounter[ uiActualDimension ]--;
						}
						//can evalue next set of values
						bStopEvaluation = false;
						break;
					}else{/*actual dimension counter has reached the upper bound
						-> set it to its lower bound and check next counter*/
						vecDimCounter[ uiActualDimension ] = lLowerBoundActual;
					}
				}//done count dimensions one up
				
				if ( bStopEvaluation ){
					//stop evaluation
					break;
				}
			}//end if count dimension counters one up
		}//end while evalue matrix entries
	}//end if matrix enties exists
	
	return ulTimeNeeded;
}


/**
 * This method evaluades the size of the Fib object in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the Fib object in bits in the compressed form
 */
unsignedLongFib cFibMatrix::getCompressedSize() const{
	
	//add bits for introduction plus domain number bit
	unsignedLongFib ulCompressedSize = 16 + 1;
	//get the value domain
	const cDomains validDomains = getValidValueDomains();
	if ( uiDomainNr != 0 ){
		//if needed add bits for the domain number
		//find greatest domain number in the value domains
		unsignedIntFib uiMaxNumberOfMatrixDomain = 0;
		const unsignedIntFib uiNumberOfDomains = validDomains.getNumberOfDomains();
		for ( unsignedIntFib uiActualDomain = 1; uiActualDomain <= uiNumberOfDomains;
				uiActualDomain++ ){
			
			const cTypeElement * pTypeElement = validDomains.getType( uiActualDomain );
			if ( ( pTypeElement != NULL ) && ( pTypeElement->getType() == 15 ) ){
				//the type is a cTypeFibMatrix type
				const unsignedIntFib uiNumberOfMatrixDomain =
					((cTypeFibMatrix*)(pTypeElement))->getNumberOfDomain();
				if ( uiMaxNumberOfMatrixDomain < uiNumberOfMatrixDomain ){
					uiMaxNumberOfMatrixDomain = uiNumberOfMatrixDomain;
				}
			}
		}//end for search all domains for maximal matrix element domain
		//read domain number
		const cDomainNaturalNumber domainForMatrixDomainNumber( uiMaxNumberOfMatrixDomain );
		
		ulCompressedSize += domainForMatrixDomainNumber.getCompressedSizeForValue();
	}
	//get the matrix element domain
	cDomain * pDomainFibMatrixBase = NULL;
	for ( intFib uiActualDomain = uiDomainNr; 0 <= uiActualDomain;
			uiActualDomain-- ){
		
		const cTypeFibMatrix typeFibMatrix( uiActualDomain );
		pDomainFibMatrixBase = validDomains.getDomainForElement( typeFibMatrix );
			
		if ( pDomainFibMatrixBase != NULL ){
			break;
		}
	}
	const bool bStandardDomainFibMatrix = ( pDomainFibMatrixBase == NULL );
	if ( bStandardDomainFibMatrix ){
		const cTypeFibMatrix typeFibMatrix;
		pDomainFibMatrixBase = typeFibMatrix.getStandardDomain();
	}
	if ( ! pDomainFibMatrixBase->isVector() ){
		//Error: not a vector domain
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrixBase;
		}
		return ulCompressedSize;
	}
	const cDomainVectorBasis * pDomainFibMatrix =
		(const cDomainVectorBasis*)pDomainFibMatrixBase;
	
	const cDomainIntegerBasis * pDomainDefVariablesCount = ((const cDomainIntegerBasis*)(
		pDomainFibMatrix->getElementDomain( 1 ) ));
	if ( pDomainDefVariablesCount != NULL ){
		//add bits for defined variables count
		ulCompressedSize += 2 * pDomainDefVariablesCount->getCompressedSizeForValue();
	}
	
	//bits for number of vectors with the to matrix values
	const cDomainIntegerBasis * pDomainVectorsCount = ((const cDomainIntegerBasis*)(
		pDomainFibMatrix->getElementDomain( 2 ) ));
	if ( pDomainVectorsCount != NULL ){
		//add bits for vector with the values to matrix count
		ulCompressedSize += pDomainVectorsCount->getCompressedSizeForValue();
	}
	
	//get the domain for the variables in this vector
	const cTypeVariable typeVariable;
	//return the variable domain
	const cDomainIntegerBasis * pDomainVariable = (const cDomainIntegerBasis*)
		validDomains.getDomainForElement( typeVariable );
	const bool bStandardDomainVariable = ( pDomainVariable == NULL );
	if ( bStandardDomainVariable ){
		//use the standard domain
		pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
	}
	
	//get domain for the vectors with the to matrix area values
	const cDomain * pDomainFibMatrixAreaVectorDom = pDomainFibMatrix->getElementDomain( 3 );
	if ( ( pDomainFibMatrixAreaVectorDom != NULL ) && ( pDomainFibMatrixAreaVectorDom->isVector() ) ){
		
		const cDomainVectorBasis * pDomainFibMatrixAreaVector = ((const cDomainVectorBasis*)(
			pDomainFibMatrixAreaVectorDom ));
		
		//add compressed size for the area vector elements
		for ( vector< cVectorArea* >::const_iterator
				itrFibMatrixArea = vecMatrixDimensionAreas.begin();
				itrFibMatrixArea != vecMatrixDimensionAreas.end(); itrFibMatrixArea++ ){
			//call method with given domains for variables and values
			ulCompressedSize += (*itrFibMatrixArea)->getCompressedSize(
				*pDomainFibMatrixAreaVector, *pDomainVariable );
		}
	}
	
	//get domain for the vectors with the to matrix values
	const cDomain * pDomainFibMatrixVectorDom = pDomainFibMatrix->getElementDomain( 4 );
	if ( ( pDomainFibMatrixVectorDom != NULL ) && ( pDomainFibMatrixVectorDom->isVector() ) ){
		
		const cDomainVectorBasis * pDomainFibMatrixVector = ((const cDomainVectorBasis*)(
			pDomainFibMatrixVectorDom ));
		
		//add compressed size for the vector elements
		for ( list<cVectorFibMatrix>::const_iterator itrFibMatrix = liFibMatrix.begin();
				itrFibMatrix != liFibMatrix.end(); itrFibMatrix++ ){
			//call method with given domains for variables and values
			ulCompressedSize += itrFibMatrix->getCompressedSize(
				*pDomainFibMatrixVector, *pDomainVariable );
		}
	}
	if ( bStandardDomainFibMatrix ){
		delete pDomainFibMatrixBase;
	}
	if ( bStandardDomainVariable ){
		//delete standard domain
		delete pDomainVariable;
	}
	//add compressed size for the subobject
	if ( pUnderObject != NULL ){
		ulCompressedSize += pUnderObject->getCompressedSize();
	}
	return ulCompressedSize;
}


/**
 * This method checks if the given variable is used in the given
 * direction from this Fib element.
 *
 * @see cFibVariable
 * @see isDefinedVariable()
 * @param pVariable the variable to check if it is used
 * @param direction the direction from this Fib element, in which the
 * 	variable should be used; default value is ED_POSITION so yust
 * 	this Fib element will be checked
 * @return true if the variable is used, else false
 */
bool cFibMatrix::isUsedVariable( const cFibVariable * pVariable,
		edDirection direction ) const{
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		//check the matrix area vectors
		for ( vector< cVectorArea* >::const_iterator
				itrFibMatrixArea = vecMatrixDimensionAreas.begin();
				itrFibMatrixArea != vecMatrixDimensionAreas.end(); itrFibMatrixArea++ ){
			
			const bool bVariableUsed = (*itrFibMatrixArea)->isUsedVariable( pVariable );
			if ( bVariableUsed ){
				return true;
			}
		}
		//check the matrix vectors
		for ( list<cVectorFibMatrix>::const_iterator itrFibMatrix = liFibMatrix.begin();
				itrFibMatrix != liFibMatrix.end(); itrFibMatrix++ ){
		
			const bool bVariableUsed = itrFibMatrix->isUsedVariable( pVariable );
			if ( bVariableUsed ){
				return true;
			}
		}
	}
	return cFibLimb::isUsedVariable( pVariable, direction );
}


/**
 * This method returns all variables used in the given direction from
 * this Fib element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @see isDefinedVariable()
 * @param direction the direction from this Fib element, in which the
 * 	variable should be used; default value is ED_POSITION so yust
 * 	this Fib element will be checked
 * @return the set with all variables used in the given direction from
 * 	this Fib element
 */
set<cFibVariable*> cFibMatrix::getUsedVariables( edDirection direction ){
	
	set<cFibVariable*> matrixUsedVariables(
		cFibLimb::getUsedVariables( direction ) );
	//add the used variables in the vectors of this matrix element
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//check to matrix area vectors
		for ( vector< cVectorArea* >::iterator
				itrFibMatrixArea = vecMatrixDimensionAreas.begin();
				itrFibMatrixArea != vecMatrixDimensionAreas.end(); itrFibMatrixArea++ ){
			
			set<cFibVariable*> matrixUsedVarArea =
				(*itrFibMatrixArea)->getUsedVariables();
			
			if ( ! matrixUsedVarArea.empty() ){
				matrixUsedVariables.insert( matrixUsedVarArea.begin(),
					matrixUsedVarArea.end() );
			}
		}
		//check to matrix vectors
		for ( list<cVectorFibMatrix>::iterator itrFibMatrix = liFibMatrix.begin();
				itrFibMatrix != liFibMatrix.end(); itrFibMatrix++ ){
			
			set<cFibVariable*> matrixUsedVarVector = itrFibMatrix->getUsedVariables();
			
			if ( ! matrixUsedVarVector.empty() ){
				matrixUsedVariables.insert( matrixUsedVarVector.begin(),
					matrixUsedVarVector.end() );
			}
		}
	}
	return matrixUsedVariables;
}


/**
 * This method checks if the given variable is defined in the given
 * direction from this Fib element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @param pVariable the variable to check if it is defined
 * @param direction the direction from this Fib element, in which the
 * 	variable should be defined; default value is ED_POSITION so yust
 * 	this Fib element will be checked
 * @param pCallingFibElement the Fib element which called this method
 * @return true if the variable is used, else false
 */
bool cFibMatrix::isDefinedVariableInternal( const cFibVariable * pVariable,
		edDirection direction,
		const cFibElement * pCallingFibElement ) const{
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//check the defiened variable
		for ( vector<cFibVariable*>::const_iterator
				itrDefVariable = vecVariablesDefined.begin();
				itrDefVariable != vecVariablesDefined.end(); itrDefVariable++ ){
			
			if ( pVariable == (*itrDefVariable) ){
				return true;
			}
		}//variable not defined here
	}
	return cFibLimb::isDefinedVariableInternal(
		pVariable, direction, pCallingFibElement );
}


/**
 * This method returns all variables defined in the given direction from
 * this Fib element.
 * This is for intern use to get the correct data from
 * getDefinedVariables() without pCallingFibElement.
 *
 * @see cFibVariable
 * @see getUsedVariables()
 * @see isDefinedVariable()
 * @param direction the direction from this Fib element, in which the
 * 	variable should be used; default value is ED_POSITION so yust
 * 	this Fib element will be checked
 * @param pCallingFibElement the Fib element which called this method
 * @return the matrix with all variables used in the given direction from
 * 	this Fib element
 */
list<cFibVariable*> cFibMatrix::getDefinedVariablesInternal(
		edDirection direction,
		const cFibElement * pCallingFibElement ){

	list<cFibVariable*> liDefinedVariables;
	
	if ( (direction == ED_ALL) || ( direction == ED_BELOW ) ||
			(direction == ED_BELOW_EQUAL) ){
		//check in subobject
		liDefinedVariables = cFibLimb::getDefinedVariablesInternal(
			ED_BELOW, pCallingFibElement );
		
		if ( direction == ED_BELOW ){
			return liDefinedVariables;
		}
	}
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//insert the defined variables this matrix element defines
		liDefinedVariables.insert( liDefinedVariables.begin(),
			vecVariablesDefined.begin(), vecVariablesDefined.end() );
	}
	if ( (direction == ED_ALL) || ( direction == ED_HIGHER ) ||
			(direction == ED_HIGHER_EQUAL) ){
		//elements to check in the direction
		list<cFibVariable*> liDefinedVariablesOfSuperObject =
				cFibLimb::getDefinedVariablesInternal(
					ED_HIGHER, pCallingFibElement );
			
		liDefinedVariables.insert( liDefinedVariables.begin(),
			liDefinedVariablesOfSuperObject.begin(),
			liDefinedVariablesOfSuperObject.end() );
	}
	return liDefinedVariables;
}


/**
 * This method replace the variable pVariableOld with the variable
 * pVariableNew in the object.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @see isDefinedVariable()
 * @param pVariableOld the variable to replace
 * @param pVariableNew the variable with which the variable pVariableOld
 * 	is to be replace
 * @return true if the variable pVariableOld is replaced with pVariableNew,
 * 	else false
 */
bool cFibMatrix::replaceVariable( cFibVariable * pVariableOld,
		cFibVariable * pVariableNew ){
	
	if ( (pVariableOld == NULL) || (pVariableNew == NULL) ){
		//can't replace
		return false;
	}
	//check to matrix area vectors
	for ( vector< cVectorArea* >::iterator
			itrFibMatrixArea = vecMatrixDimensionAreas.begin();
			itrFibMatrixArea != vecMatrixDimensionAreas.end(); itrFibMatrixArea++ ){
		
		//replace variable in area vector
		if ( ! (*itrFibMatrixArea)->replaceVariable( pVariableOld, pVariableNew ) ){
			return false;
		}
	}
	//check to matrix vectors
	for ( list<cVectorFibMatrix>::iterator itrFibMatrix = liFibMatrix.begin();
			itrFibMatrix != liFibMatrix.end(); itrFibMatrix++ ){
		
		//replace variable in vector
		if ( ! itrFibMatrix->replaceVariable( pVariableOld, pVariableNew ) ){
			return false;
		}
	}
	return cFibLimb::replaceVariable( pVariableOld, pVariableNew );
}


/**
 * This method copies the Fib element on the specified position.
 * Variables which are not defined in the Fib element but used
 * don't change ther reference.
 *
 * @see getType()
 * @param cType the type of the Fib element to copy
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, to copy
 * @return the copy of the Fib element
 */
cFibElement * cFibMatrix::copyElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		//copy this element
		return new cFibMatrix( *this );
	}//else get the Fib element and copy it
	
	const cFibElement * pFibElementToCopy = getConstFibElement(
		cType, elementPoint, bAbsolute );
	
	if ( pFibElementToCopy ){
		return ( pFibElementToCopy->copyElement( 'u', 0 ) );
	}//else pFibElementToCopy == NULL
	return NULL;
}


/**
 * This method checks if the given Fib object is equal to this Fib
 * object.
 * Variables can be others, but must be defined and used in equivalent
 * Fib elements.
 *
 * @param fibObject the Fib object to which this Fib object should be
 * 	equal
 * @param mapEqualRootObjects the root objects of this object that wher
 * 	already checked as equal
 * 	map entries:
 * 		key: the root-element of this Fib object that was checked
 * 		value: the to the key correspondending root-element of the
 * 			fibObject that was checked and which is equal to the key
 * 			root-element
 * 	(it is empty if bCheckExternalObjects == false)
 * @param mapEqualDefinedVariables the Fib elements that defines
 * 	variables and are equal;
 * 	map entries:
 * 		key: the Fib element of this Fib object that was checked
 * 		value: the to the key correspondending Fib element of the
 * 			fibObject that was checked and which sets its defined
 * 			variables to the same values as the key Fib element
 * @param bCheckExternalObjects if true the external objects of
 * 	cExtObject will be compared
 * @return true if this Fib object is equal to the given Fib object,
 * 	else false
 */
bool cFibMatrix::equalInternal( const cFibElement & fibObject,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( ! equalElementInternal( fibObject, mapEqualRootObjects,
			mapEqualDefinedVariables, bCheckExternalObjects ) ){
		return false;
	}//else this and the other Fib element is equal
	//add this element to the equal defined variables
	mapEqualDefinedVariables.insert( make_pair( this, &fibObject ) );
	
	return cFibLimb::equalInternal( fibObject, mapEqualRootObjects,
		mapEqualDefinedVariables, bCheckExternalObjects );
}


/**
 * This method checks if the given Fib element is equal to this Fib
 * element.
 * The subobjects are not compared, not even ther count is compared.
 * Used variables can be others.
 *
 * @param fibElement the Fib element to which this Fib element should be
 * 	equal
 * @param mapEqualRootObjects the root objects of this object that wher
 * 	already checked as equal
 * 	map entries:
 * 		key: the root-element of this Fib object that was checked
 * 		value: the to the key correspondending root-element of the
 * 			fibObject that was checked and which is equal to the key
 * 			root-element
 * 	(it is empty if bCheckExternalObjects == false)
 * @param mapEqualDefinedVariables the Fib elements that defines
 * 	variables and are equal;
 * 	map entries:
 * 		key: the Fib element of this Fib object that was checked
 * 		value: the to the key correspondending Fib element of the
 * 			fibObject that was checked and which sets its defined
 * 			variables to the same values as the key Fib element
 * @param bCheckExternalObjects if true the external objects of
 * 	cExtObject will be compared
 * @return true if this Fib element is equal to the given Fib element,
 * 	else false
 */
bool cFibMatrix::equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	const cFibMatrix * pFibMatrixElement = (const cFibMatrix*)(&fibElement);
	if ( vecVariablesDefined.size() != pFibMatrixElement->vecVariablesDefined.size() ){
		return false;
	}
	if ( getDomainNr() != pFibMatrixElement->getDomainNr() ){
		//domain number not equal -> Fib elements not equal
		return false;
	}
	//compare to matrix vectors
	if ( vecMatrixDimensionAreas.size() != pFibMatrixElement->vecMatrixDimensionAreas.size() ){
		//number of area vectors not equal -> Fib elements not equal
		return false;
	}
	//compare area vectors with values to matrix
	vector< cVectorArea* >::const_iterator itrFibMatrixAreaVectorOther =
		pFibMatrixElement->vecMatrixDimensionAreas.begin();
	for ( vector< cVectorArea* >::const_iterator
			itrFibMatrixAreaVector = vecMatrixDimensionAreas.begin();
			itrFibMatrixAreaVector != vecMatrixDimensionAreas.end();
		itrFibMatrixAreaVector++, itrFibMatrixAreaVectorOther++ ){
		
		if ( ! (*itrFibMatrixAreaVector)->equalInternal( **itrFibMatrixAreaVectorOther,
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			return false;
		}
	}
	//compare to matrix vectors
	if ( liFibMatrix.size() != pFibMatrixElement->liFibMatrix.size() ){
		//number of vectors not equal -> Fib elements not equal
		return false;
	}
	//compare vectors with values to matrix
	list<cVectorFibMatrix>::const_iterator itrFibMatrixVectorOther =
		pFibMatrixElement->liFibMatrix.begin();
	for ( list<cVectorFibMatrix>::const_iterator
			itrFibMatrixVector = liFibMatrix.begin();
			itrFibMatrixVector != liFibMatrix.end();
			itrFibMatrixVector++, itrFibMatrixVectorOther++ ){
		
		if ( ! itrFibMatrixVector->equalInternal( *itrFibMatrixVectorOther,
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			return false;
		}
	}
	return true;
}


/**
 * This method checks if the given Fib element sets the variable to
 * the same values as this Fib element.
 *
 * @param pVariableOwn a pointer to a defined variable in this Fib element,
 * 	it is compared to the equivalent variable pVariable in the given
 * 	Fib element fibElement
 * @param fibElement the Fib element, to which this Fib element should be
 * 	compared
 * @param pVariable a pointer to a defined variable in the other
 * 	Fib element fibElement
 * @param mapEqualRootObjects the root objects of this object that wher
 * 	already checked as equal
 * 	map entries:
 * 		key: the root-element of this Fib object that was checked
 * 		value: the to the key correspondending root-element of the
 * 			fibObject that was checked and which is equal to the key
 * 			root-element
 * 	(it is empty if bCheckExternalObjects == false)
 * @param mapEqualDefinedVariables the Fib elements that defines
 * 	variables and are equal;
 * 	map entries:
 * 		key: the Fib element of this Fib object that was checked
 * 		value: the to the key correspondending Fib element of the
 * 			fibObject that was checked and which sets its defined
 * 			variables to the same values as the key Fib element
 * @param bCheckExternalObjects if true the external objects of
 * 	cExtObject will be compared
 * @return true if this Fib element sets the variable to the same
 * 	values as this Fib element
 */
bool cFibMatrix::equalValuesSetInternal( const cFibVariable * pVariableOwn,
		const cFibElement & fibElement,
		const cFibVariable * pVariable,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	if ( fibElement.getType() != getType() ){
		//not equal element type -> not equal values matrix
		return false;
	}
	const cFibMatrix * pFibMatrixElement = (const cFibMatrix*)(&fibElement);
	//check if the variables are defined on the same position
	vector<cFibVariable*>::const_iterator itrDefVarOther =
		pFibMatrixElement->vecVariablesDefined.begin();
	bool bDefVariablesOnSamePosition = false;
	for ( vector<cFibVariable*>::const_iterator itrDefVar = vecVariablesDefined.begin();
			( itrDefVar != vecVariablesDefined.end() ) &&
			( itrDefVarOther != pFibMatrixElement->vecVariablesDefined.end() );
			itrDefVar++, itrDefVarOther++ ){
		
		if ( ( (*itrDefVar) == pVariableOwn ) || ( (*itrDefVarOther) == pVariable ) ){
			//defined variable found in a Fib element
			if ( ( (*itrDefVar) == pVariableOwn ) && ( (*itrDefVarOther) == pVariable ) ){
				//the defined variables are on the same position
				bDefVariablesOnSamePosition = true;
				break;
			}else{/*the defined variables are not on the same position
				-> not equal values matrix*/
				return false;
			}
		}
	}//end for check if the variables are defined on the same position
	if ( ! bDefVariablesOnSamePosition ){
		/*the defined variables are not on the same position
		 -> not equal values matrix*/
		return false;
	}
	
	const map< const cFibElement *, const cFibElement * >::const_iterator
		itrEqualDefinedVariable = mapEqualDefinedVariables.find( this );
	if ( ( itrEqualDefinedVariable != mapEqualDefinedVariables.end() ) &&
			( itrEqualDefinedVariable->second == &fibElement ) ){
		//Fib elements compared befor as equal
		return true;
	}//else compare Fib elements
	const bool bEqualElement = equalElementInternal(
		fibElement, mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
	if ( bEqualElement ){
		mapEqualDefinedVariables.insert( make_pair( this, &fibElement ) );
		return true;
	}
	return false;
}


/**
 * This method stores this Fib object in the XML format into the
 * given stream.
 *
 * @param stream the stream where this Fib object should be stored to
 * @return true if this Fib object is stored, else false
 */
bool cFibMatrix::storeXml( ostream &stream ) const{

	bool bReturnValue = true;
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<matrix elementNr=\""<<getNumberOfElement()<<"\" dimensions=\""<<
		getNumberOfMatrixDimensions()<<"\"";
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<matrix dimensions=\""<<getNumberOfMatrixDimensions()<<"\"";
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	if ( uiDomainNr == 0 ){
		stream<<">"<<endl;
	}else{
		stream<<" domainNr=\""<< uiDomainNr <<"\">"<<endl;
	}
	
	stream<<"<defined_variables>"<<endl;
	for ( vector<cFibVariable*>::const_iterator
			itrDefVariable = vecVariablesDefined.begin();
			itrDefVariable != vecVariablesDefined.end(); itrDefVariable++ ){
		
		stream<<"<variable>"<<(*itrDefVariable)->getIntegerValue()<<"</variable>"<<endl;
	}
	stream<<"</defined_variables>"<<endl;
	
	stream<<"<areas>"<<endl;
	for ( vector<cVectorArea*>::const_iterator
			itrFibMatrixAreaVector = vecMatrixDimensionAreas.begin();
			itrFibMatrixAreaVector != vecMatrixDimensionAreas.end();
			itrFibMatrixAreaVector++ ){
		
		//store to matrix vectors
		if ( ! (*itrFibMatrixAreaVector)->storeXml( stream ) ){
			return false;
		}
	}
	stream<<"</areas>"<<endl;
	stream<<"<values>"<<endl;
	for ( list<cVectorFibMatrix>::const_iterator
			itrFibMatrixVector = liFibMatrix.begin();
			itrFibMatrixVector != liFibMatrix.end(); itrFibMatrixVector++ ){
		
		//store to matrix vectors
		if ( ! itrFibMatrixVector->storeXml( stream ) ){
			return false;
		}
	}
	stream<<"</values>"<<endl;
	if ( pUnderObject ){
		bReturnValue &= pUnderObject->storeXml( stream );
	}
	stream<<"</matrix>"<<endl;
	return bReturnValue;
}


/*
 * cFibMatrix-element methods
 */



/**
 * @return the number of dimensions (variables) the matrix of this
 * 	matrix element has
 * @see vecMatrixDimensionAreas
 */
unsignedIntFib cFibMatrix::getNumberOfMatrixDimensions() const{
	
	return vecMatrixDimensionAreas.size();
}


/**
 * @return the number of elements of the matrix entry vectors of the
 * 	matrix of this matrix element has
 * @see liFibMatrix
 */
unsignedIntFib cFibMatrix::getNumberOfVectorElements() const{
	
	return vecVariablesDefined.size() - vecMatrixDimensionAreas.size();
}


/**
 * This method returns a pointer to the uiPosition'th from this
 * matrix element defined variable.
 *
 * @param uiPosition the number of the from this matrix element defined
 * 	variable to return (counting begins with 1)
 * @return a pointer to the uiPosition'th from this matrix element defined
 * 	variable, or NULL if non such exists
 */
cFibVariable * cFibMatrix::getDefinedVariable( const unsignedLongFib uiPosition ){
	
	if ( ( uiPosition < 1 ) || ( vecVariablesDefined.size() < uiPosition ) ){
		//no such defined variables
		return NULL;
	}
	return vecVariablesDefined[ uiPosition - 1 ];
}



/**
 * @see uiDomainNr
 * @return the number of the matrix element domain for this matrix element
 */
unsignedIntFib cFibMatrix::getDomainNr() const{
	
	return uiDomainNr;
}


/**
 * This method sets the number of the matrix element domain for this
 * matrix element.
 * 
 * @see uiDomainNr
 * @param uiInDomainNumber the number of the matrix element domain for this
 * 	matrix element
 */
void cFibMatrix::setDomainNr( const unsignedLongFib uiInDomainNumber ){
	
	uiDomainNr = uiInDomainNumber;
}


/**
 * This method returns the area for the uiDimension'th dimension.
 * 
 * @see vecMatrixDimensionAreas
 * @param uiDimension the dimension for which the area is to be returned
 * 	(counting begins with 1)
 * @return the area for the uiDimension'th dimension
 */
cVectorArea * cFibMatrix::getArea( const unsignedIntFib uiDimension ){
	
	if ( ( uiDimension < 1 ) ||
			( vecMatrixDimensionAreas.size() < uiDimension ) ){
		return NULL;
	}
	return vecMatrixDimensionAreas[ uiDimension - 1 ];
}


/**
 * @see liFibMatrix
 * @return the number of vectors or sets of values this matrix element contains
 */
unsignedLongFib cFibMatrix::getNumberOfVectors() const{
	
	return liFibMatrix.size();
}


/**
 * @return a vector with all vectors / sets of values of this matrix element
 * @see liFibMatrix
 */
const vector< cVectorFibMatrix > cFibMatrix::getVectors(){
	
	return vector< cVectorFibMatrix >( liFibMatrix.begin(), liFibMatrix.end() );
}


/**
 * This method sets all vectors / sets of values of this matrix element to
 * the given vectors.
 * 
 * @see liFibMatrix
 * @param vecMatrixVectors a vector with all vectors / sets of values this
 * 	matrix element should contain
 * @return true if the vectors wher set, else false and the vectors of
 * 	this matrix element unchanged
 */
bool cFibMatrix::setVectors( const vector< cVectorFibMatrix > & vecMatrixVectors ){
	
	//check vectors
	const unsignedIntFib uiNumberOfVectorElements = getNumberOfVectorElements();
	for ( vector<cVectorFibMatrix>::const_iterator itrFibMatrix = vecMatrixVectors.begin();
			 itrFibMatrix != vecMatrixVectors.end(); itrFibMatrix++ ){
		
		if ( itrFibMatrix->getNumberOfElements() != uiNumberOfVectorElements ){
			//not correct number of vector elements -> can't change matrix vectors
			return false;
		}
	}//end for check vectors
	//set vectors
	liFibMatrix.clear();
	liFibMatrix.insert( liFibMatrix.begin(), vecMatrixVectors.begin(), vecMatrixVectors.end() );
	
	for ( list<cVectorFibMatrix>::iterator
			itrFibMatrixVector = liFibMatrix.begin();
			itrFibMatrixVector != liFibMatrix.end(); itrFibMatrixVector++ ){
		
		itrFibMatrixVector->setDefiningFibElement( this, false );
	}
	return true;
}


/**
 * This method returns a pointer to the uiPosition'th vector of this
 * matrix element.
 *
 * @see liFibMatrix
 * @param uiPosition the number of the vector to return (counting begins
 * 	with 1)
 * @return a pointer to the uiPosition'th vector, or NULL if non such exists
 */
cVectorFibMatrix * cFibMatrix::getVector( const unsignedLongFib uiPosition ){
	
	list<cVectorFibMatrix>::iterator itrFibMatrixVectorToReturn =
		getListElement( liFibMatrix, uiPosition );
	if ( itrFibMatrixVectorToReturn == liFibMatrix.end() ){
		return NULL;
	}
	return &(*itrFibMatrixVectorToReturn);
}


/**
 * This method sets the uiPosition'th vector of this matrix element to the
 * given vector.
 *
 * @see liFibMatrix
 * @param vecMatrixVector the vector to set
 * @param uiPosition the position wher the to matrix vector should stand
 * 	in this matrix element (counting begins with 1)
 * @return true if the vector was set, else false and the vectors of
 * 	this matrix element unchanged
 */
bool cFibMatrix::setVector( const cVectorFibMatrix & vecMatrixVector,
		const unsignedLongFib uiPosition ){
	
	if ( vecMatrixVector.getNumberOfElements() != getNumberOfVectorElements() ){
		//the to set vector has not the correct number of elements
		return false;
	}
	list<cVectorFibMatrix>::iterator itrFibMatrixVectorToChange =
		getListElement( liFibMatrix, uiPosition );
	if ( itrFibMatrixVectorToChange == liFibMatrix.end() ){
		return false;
	}
	(*itrFibMatrixVectorToChange) = vecMatrixVector;
	itrFibMatrixVectorToChange->setDefiningFibElement( this, false );
	return true;
}


/**
 * This method adds the given vector to the existing vectors.
 *
 * @see liFibMatrix
 * @param vecMatrixVector a reference to the to add vector
 * @param uiPosition the position wher the vecMatrixVector should be added
 * 	(counting begins with 1); if 0 the vecMatrixVector or greater than the number
 * 	of vectors the vector will be added to the end of the vector list
 * @return true if the vecMatrixVector was added, else false
 */
bool cFibMatrix::addVector( const cVectorFibMatrix & vecMatrixVector,
		const unsignedLongFib uiPosition ){
	
	if ( vecMatrixVector.getNumberOfElements() != getNumberOfVectorElements() ){
		//the to add vector has not the correct number of elements
		return false;
	}
	if ( ( uiPosition < 1 ) || ( liFibMatrix.size() < uiPosition ) ){
		liFibMatrix.push_back( vecMatrixVector );
		liFibMatrix.back().setDefiningFibElement( this, false );
		return true;
	}
	list<cVectorFibMatrix>::iterator itrFibMatrixVectorToChange =
		getListElement( liFibMatrix, uiPosition );
	if ( itrFibMatrixVectorToChange == liFibMatrix.end() ){
		return false;
	}
	itrFibMatrixVectorToChange = liFibMatrix.insert(
		itrFibMatrixVectorToChange, vecMatrixVector );
	itrFibMatrixVectorToChange->setDefiningFibElement( this, false );
	return true;
}


/**
 * This method deletes the uiPosition'th vector from the existing vectors.
 *
 * @param uiPosition the position, wher the vector should be deleted from
 * 	(counting begins with 1)
 * @return true if the vector was deleted, else false
 */
bool cFibMatrix::deleteVector( const unsignedLongFib uiPosition ){
	
	list<cVectorFibMatrix>::iterator itrFibMatrixVectorToChange =
		getListElement( liFibMatrix, uiPosition );
	if ( itrFibMatrixVectorToChange == liFibMatrix.end() ){
		return false;
	}
	liFibMatrix.erase( itrFibMatrixVectorToChange );
	return true;
}


/**
 * This method stores this Fib object in the compressed Fib format
 * into the given stream.
 * It is needed because the stream can yust store byts but the size of
 * Fib elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the Fib elements.
 *
 * @see store
 * @param stream the stream where this Fib object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if this Fib object is stored, else false
 */
bool cFibMatrix::storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{

	if ( pUnderObject == NULL ){
		return false;
	}
	
	const char szInitiation[] = { 0x2F, 0x00 };//0000 0000; 0010 1111
	const bool bInitiationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, szInitiation, 16 );
	if ( ! bInitiationStored ){
		return false;
	}
	//get the needed domains
	cDomains validDomains = getValidValueDomains();
	//write information for the domain number
	if ( uiDomainNr == 0 ){
		const char cDomainNrBit = 0x00;
		const bool bDomainNrBitStored = nBitStream::store( stream, cRestBits,
			uiRestBitPosition, cDomainNrBit, 1 );
		if ( ! bDomainNrBitStored ){
			return false;
		}
	}else{
		//store bit for domain number
		const char cDomainNrBit = 0x01;
		const bool bDomainNrBitStored = nBitStream::store( stream, cRestBits,
			uiRestBitPosition, cDomainNrBit, 1 );
		if ( ! bDomainNrBitStored ){
			return false;
		}
		//read domain number
		//find greatest domain number in the value domains
		unsignedIntFib uiMaxNumberOfMatrixDomain = 0;
		const unsignedIntFib uiNumberOfDomains = validDomains.getNumberOfDomains();
		for ( unsignedIntFib uiActualDomain = 1; uiActualDomain <= uiNumberOfDomains;
				uiActualDomain++ ){
			
			const cTypeElement * pTypeElement = validDomains.getType( uiActualDomain );
			if ( ( pTypeElement != NULL ) && ( pTypeElement->getType() == 15 ) ){
				//the type is a cTypeFibMatrix type
				const unsignedIntFib uiNumberOfMatrixDomain =
					((cTypeFibMatrix*)(pTypeElement))->getNumberOfDomain();
				if ( uiMaxNumberOfMatrixDomain < uiNumberOfMatrixDomain ){
					uiMaxNumberOfMatrixDomain = uiNumberOfMatrixDomain;
				}
			}
		}//end for search all domains for maximal matrix element domain
		//read domain number
		const cDomainNaturalNumber domainForMatrixDomainNumber( uiMaxNumberOfMatrixDomain );
		
		const bool bDomainNumberStored = domainForMatrixDomainNumber.storeUnscaledValue(
			uiDomainNr, stream, cRestBits, uiRestBitPosition );
		if ( ! bDomainNumberStored ){
			//error: domain number not stored
			return false;
		}
	}
	
	//get the matrix element domain
	cDomain * pDomainFibMatrixBase = NULL;
	for ( intFib uiActualDomain = uiDomainNr; 0 <= uiActualDomain;
			uiActualDomain-- ){
		
		const cTypeFibMatrix typeFibMatrix( uiActualDomain );
		pDomainFibMatrixBase = validDomains.getDomainForElement( typeFibMatrix );
		
		if ( pDomainFibMatrixBase != NULL ){
			break;
		}
	}
	const bool bStandardDomainFibMatrix = ( pDomainFibMatrixBase == NULL );
	if ( bStandardDomainFibMatrix ){
		const cTypeFibMatrix typeFibMatrix;
		pDomainFibMatrixBase = typeFibMatrix.getStandardDomain();
	}
	if ( ! pDomainFibMatrixBase->isVector() ){
		//Error: not a vector domain -> can't store matrix object
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrixBase;
		}
		return false;
	}
	cDomainVectorBasis * pDomainFibMatrix = (cDomainVectorBasis*)pDomainFibMatrixBase;
	
	if ( pDomainFibMatrix->getNumberOfElements() < 4 ){
		/*Error in domain (domain for number of defined variables and / or
		number of vectors and / or vectors missing) -> can't load matrix object*/
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		return false;
	}
	cDomainIntegerBasis * pDomainDefVariablesCount = ((cDomainIntegerBasis*)(
		pDomainFibMatrix->getElementDomain( 1 ) ));
	if ( pDomainDefVariablesCount == NULL ){
		/*Error: in domain (domain for number of defined variables missing)
		-> can't store matrix object*/
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		return false;
	}
	//store the number of dimension variables
	const unsignedIntFib uiNumberOfDimensions = vecMatrixDimensionAreas.size();
	const bool bNumberOfDimensions = pDomainDefVariablesCount->storeUnscaledValue(
		uiNumberOfDimensions, stream, cRestBits, uiRestBitPosition );
	if ( ! bNumberOfDimensions ){
		//Error: number of defined variables not stored
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		return false;
	}
	//store the number of vector elements (variables)
	const unsignedIntFib uiNumberOfVectorElements = getNumberOfVectorElements();
	const bool bNumberOfVectorElements = pDomainDefVariablesCount->storeUnscaledValue(
		uiNumberOfVectorElements, stream, cRestBits, uiRestBitPosition );
	if ( ! bNumberOfVectorElements ){
		//Error: number of defined variables not stored
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		return false;
	}
	//store number of vectors with the to matrix values
	cDomainIntegerBasis * pDomainVectorsCount = ((cDomainIntegerBasis*)(
		pDomainFibMatrix->getElementDomain( 2 ) ));
	if ( pDomainVectorsCount == NULL ){
		/*Error in domain (domain for number of vectors with the to matrix values missing)
		-> can't store matrix object*/
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		return false;
	}
	//store number of vectors with the to matrix values
	const unsignedLongFib ulNumberOfVectors = liFibMatrix.size();
	const bool bNumberOfVectorsStored = pDomainVectorsCount->storeUnscaledValue(
		ulNumberOfVectors, stream, cRestBits, uiRestBitPosition );
	if ( ! bNumberOfVectorsStored ){
		//Error: number of defined variables not stored
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		return false;
	}
	
	//get domain for the area vectors
	cDomain * pDomainFibMatrixAreaVectorDom = pDomainFibMatrix->getElementDomain( 3 );
	if ( ( pDomainFibMatrixAreaVectorDom == NULL ) ||
			( ! pDomainFibMatrixAreaVectorDom->isVector() ) ){
		/*Error in domain (domain for the area vectors missing or not a
		 * vector domain) -> can't load matrix object*/
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		return false;
	}
	cDomainVectorBasis * pDomainFibMatrixAreaVector = ((cDomainVectorBasis*)(
		pDomainFibMatrixAreaVectorDom ));
	
	//get the domain for the variables in this vector
	cTypeVariable typeVariable;
	//return the variable domain
	cDomainIntegerBasis * pDomainVariable = (cDomainIntegerBasis*)
		validDomains.getDomainForElement( typeVariable );
	const bool bStandardDomainVariable = ( pDomainVariable == NULL );
	if ( bStandardDomainVariable ){
		//use the standard domain
		pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
	}
	//store vectors with the dimension areas
	for ( vector<cVectorArea*>::const_iterator
			itrMatrixAreaVector = vecMatrixDimensionAreas.begin();
			itrMatrixAreaVector != vecMatrixDimensionAreas.end();
			itrMatrixAreaVector++ ){
		
		const bool bVectorStored = (*itrMatrixAreaVector)->store( stream, cRestBits,
			uiRestBitPosition, *pDomainFibMatrixAreaVector, *pDomainVariable );
		if ( ! bVectorStored ){
			if ( bStandardDomainVariable ){
				delete pDomainVariable;
			}
			if ( bStandardDomainFibMatrix ){
				delete pDomainFibMatrix;
			}
			return false;
		}
	}//end for store vectors with the dimension areas
	
	//get domain for the vectors with the to set values
	cDomain * pDomainFibMatrixVectorDom = pDomainFibMatrix->getElementDomain( 4 );
	if ( ( pDomainFibMatrixVectorDom == NULL ) || ( ! pDomainFibMatrixVectorDom->isVector() ) ){
		/*error in domain (domain for the vectors with the to matrix values
		 * missing or not a vector domain) -> can't load matrix object*/
		if ( bStandardDomainVariable ){
			delete pDomainVariable;
		}
		if ( bStandardDomainFibMatrix ){
			delete pDomainFibMatrix;
		}
		return false;
	}
	cDomainVectorBasis * pDomainFibMatrixVector = ((cDomainVectorBasis*)(
		pDomainFibMatrixVectorDom ));
	
	for ( list<cVectorFibMatrix>::const_iterator itrFibMatrix = liFibMatrix.begin();
			itrFibMatrix != liFibMatrix.end(); itrFibMatrix++ ){
		
		const bool bVectorStored = itrFibMatrix->store( stream, cRestBits,
			uiRestBitPosition, *pDomainFibMatrixVector, *pDomainVariable );
		if ( ! bVectorStored ){
			if ( bStandardDomainVariable ){
				delete pDomainVariable;
			}
			if ( bStandardDomainFibMatrix ){
				delete pDomainFibMatrix;
			}
			return false;
		}
	}//end for store vectors with values to set
	
	if ( bStandardDomainFibMatrix ){
		delete pDomainFibMatrix;
	}
	if ( bStandardDomainVariable ){
		delete pDomainVariable;
	}
	
	return pUnderObject->storeBit( stream, cRestBits, uiRestBitPosition );
}


/**
 * This method sets the each variable, which is defined above a leaf,
 * to an uniqe integer number greater than the given number
 * uiLastVariableNumber. While storing this number can be stored to
 * identify the variable.
 *
 * @param uiLastVariableNumber the number which was last use, this
 * 	means also is the greatest used, in this limb.
 * @return the number which was last use, this
 * 	means also is the greatest used, in this limb
 * 	from the method
 */
unsignedIntFib cFibMatrix::enumerateVariablesForStoring(
		unsignedIntFib uiLastVariableNumber ){
	
	for ( vector<cFibVariable*>::iterator
			itrDefVariable = vecVariablesDefined.begin();
			itrDefVariable != vecVariablesDefined.end(); itrDefVariable++ ){
		
		uiLastVariableNumber++;
		(*itrDefVariable)->setIntegerValue( uiLastVariableNumber );
	}
	
	return cFibLimb::enumerateVariablesForStoring( uiLastVariableNumber );
}


/**
 * This method copies the connected object with the given number in the
 * order of connected objects.
 * For this every Fib element, beginning from this Fib element, that
 * is part of the connected object will be copied.
 * Variables which are not defined in the connected object but used
 * don't change ther reference.
 * It is an help method for the copy method. It dosn't update the
 * structural information of the created Fib object.
 *
 * @param iObjectPoint the number of the connected object to copy;
 * 	the standart value is 0 for coping the complet actual object
 * @return the copy of the connected object or NULL if non such exists
 */
cFibElement *cFibMatrix::copyInternal( const unsignedIntFib iObjectPoint ) const{

	cFibMatrix * pFibMatrix = NULL;

	if ( pUnderObject ){
		pFibMatrix = new cFibMatrix( *this );
		//copy the subobject
		cFibElement * pCopyUnderobject = pUnderObject->copyInternal( iObjectPoint );
		if ( pCopyUnderobject == NULL ){
			//no such objectpoint
			delete pFibMatrix;
			return NULL;
		}
		vector<cFibVariable*>::iterator itrDefVarOther =
			pFibMatrix->vecVariablesDefined.begin();
		for ( vector<cFibVariable*>::const_iterator
				itrDefVar = vecVariablesDefined.begin();
				itrDefVar != vecVariablesDefined.end();
				itrDefVar++, itrDefVarOther++ ){
			
			pCopyUnderobject->replaceVariable(
				const_cast<cFibVariable*>(*itrDefVar), (*itrDefVarOther) );
		}//end for check if the variables are defined on the same position
		
		pFibMatrix->pUnderObject = pCopyUnderobject;
		if ( pFibMatrix->pUnderObject ){
			pFibMatrix->pUnderObject->pSuperiorElement = pFibMatrix;
		}
	}else{//no subobject
		if ( iObjectPoint == 0 ){
			//just copy if this is the correct objectpoint
			pFibMatrix = new cFibMatrix( *this );
		}
	}
	return pFibMatrix;
}












