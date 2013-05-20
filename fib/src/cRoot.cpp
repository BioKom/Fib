/**
 * @class cRoot
 * file name: cRoot.cpp
 * @author Betti Oesterholz
 * @date 02.09.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the root-Fib element.
 * Copyright (C) @c LGPL3 2009 Betti Oesterholz
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
 * This class represents the root-element of the Fib-multimedialanguage.
 * It holds the information for the enviroment of the Fib-Object, like
 * number of dimensions and domains.
 *
 */
/*
History:
02.09.2009  Oesterholz  created
13.12.2009  Oesterholz  storePropertyType() and createStorePropertyOrder() implemented
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
27.09.2010  Oesterholz  generateNeededDomains() method added
18.07.2011  Oesterholz  compressed storing for comments added
07.08.2011  Oesterholz  isDefinedVariable() and getDefinedVariables() with
	pCallingFibElement
09.08.2011  Oesterholz  changes for cExtObject: (new: liPExtObjectElm,
	setCallingFibElement(), unsetCallingFibElement(); changed generateNeededDomains() )
15.08.2011  Oesterholz  syncUnderobjects() renamed to syncSubobjects()
19.08.2011  Oesterholz  XML element name "valuedomains" changed to "valueDomains"
25.08.2011  Oesterholz  underarea to subarea
04.09.2010  Oesterholz  FEATURE_GENERATE_NEEDED_DOMAINS implemented
17.10.2011  Oesterholz  FEATURE_OUTPUT_ELEMENT_NUMBER_XML implemented
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
07.11.2011  Oesterholz  ExternUnderObjects to ExternSubobjects
09.11.2011  Oesterholz  changes for cExtSubobject: changed generateNeededDomains()
03.12.2011  Oesterholz  Bugfix: the export and import of comments; whith
	spaces didn't work (sprintf())
12.12.2011  Oesterholz  changes for cFibSet and cFibMatrix: changed
02.01.2012  Oesterholz  generateNeededDomains() cTypeSubarea to cTypeArea
23.01.2012  Oesterholz  input values changed to input vector
27.01.2012  Oesterholz  Bugfix in insertObjectInElement() if 
	(fibUnderObjects.front() == NULL) set superior of inserted element to this
29.01.2012  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR implemented:
	the input values are now a vector of values;
	getValidDomains() + getValidPureValueDomains() bInherit added
15.03.2012  Oesterholz  Bugfix: set liPExtObjectElm to NULL if not used
01.04.2012  Oesterholz  DEBUG_RESTORE_XML implemented
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
22.11.2012  Oesterholz  Bugfix: a root element can be called more than one
	time by external objects
21.12.2012  Oesterholz  debugging printf formating improved
30.12.2012  Oesterholz  DEBUG_EVALUE: debugging evalue will print first
	optional part entry
09.05.2013  Oesterholz  added debugging info: DEBUG_RESTORE_XML
12.05.2013  Oesterholz  getDigits() andling changed (now version for integers)
*/


//TODO weg
//#define DEBUG


#include "cRoot.h"

#include "cList.h"
#include "cComment.h"
#include "cFunction.h"
#include "cIf.h"
#include "cArea.h"
#include "cExtObject.h"
#include "cExtSubobject.h"
#include "cFibSet.h"
#include "cFibMatrix.h"
#include "cUnderFunction.h"
#include "cFunctionOneValue.h"
#include "cFunctionTwoValue.h"
#include "cFunctionIf.h"
#include "cCondition.h"
#include "cConditionNot.h"
#include "cConditionTwoValue.h"
#include "cConditionComparison.h"
#include "cVectorArea.h"
#include "cVectorFibSet.h"
#include "cVectorFibMatrix.h"
#include "cTypeInVar.h"
#include "cTypeDimension.h"
#include "cTypeVariable.h"
#include "cTypeComments.h"
#include "cTypeUnderFunction.h"
#include "cTypeArea.h"
#include "cTypeExtObject.h"
#include "cTypeExtObjectInput.h"
#include "cTypeExtSubobject.h"
#include "cTypeFibSet.h"
#include "cTypeFibMatrix.h"
#include "cDomainSingle.h"
#include "cDomainIntegerBasis.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainIntegerBit.h"
#include "cDomainNaturalNumber.h"
#include "cDomainVector.h"
#include "cDomainVectorOpenEnd.h"
#include "cFibDatabase.h"

#include <algorithm>


using namespace fib;

#define MAX_SUBOBJECTS (256 * 256)

/**
 * The object for the Fib database;
 */
cFibDatabase * cRoot::pFibDatabase = NULL;


#ifdef FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param pInSuperiorRootElement the root-Element in which this
 * 	root-element is an subobject
 * @param pInMainFibObject the main Fib-object of this root-element
 */
cRoot::cRoot( cFibElement * pInMainFibObject,
		cRoot * pInSuperiorRootElement ):
		cFibBranch( list<cFibElement*>(), pInSuperiorRootElement ),
		pMainFibObject( NULL ), multimediaInfo( this ), pChecksum( NULL ){
	
#ifdef FEATURE_FAST_UPDATE
	fibObjectCounts.vecNumberOfFibElements[
		cFibObjectCounts::ROOT ]++;
	fibObjectCounts.vecNumberOfFibElements[
		cFibObjectCounts::ALL ]++;
	
	fibUnderObjects.push_back( NULL );
	setMainFibObject( pInMainFibObject );
#else //FEATURE_FAST_UPDATE
	pMainFibObject = pInMainFibObject;
	
	fibUnderObjects.push_back( pInMainFibObject );
#endif //FEATURE_FAST_UPDATE
	if ( ( pInSuperiorRootElement != NULL ) &&
			( pInSuperiorRootElement->getType() == 'r' ) ){
		cRoot * pSuperiorRootElement =
			(cRoot*)pInSuperiorRootElement;
		
		//search for the next free identifier
		longFib lIdentifier = 0;
		const list<longFib> liIdentifiers =
			pSuperiorRootElement->getAllAccessibleRootObjectIdentifiers();
		
		for ( list<longFib>::const_iterator itrIdentifier = liIdentifiers.begin();
				itrIdentifier != liIdentifiers.end(); itrIdentifier++ ){
			lIdentifier = max( lIdentifier, *itrIdentifier );
		}
		lIdentifier++;
		//insert this root-object as an sub-root-object
		pSuperiorRootElement->addSubRootObject( lIdentifier, this );
		
	}
	if ( pFibDatabase == NULL ){
		//get new database instance
		pFibDatabase = cFibDatabase::getInstance();
	}
#ifndef FEATURE_FAST_UPDATE
	updateAllCounters();
#endif //FEATURE_FAST_UPDATE
}


#else //FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param pInSuperiorRootElement the root-Element in which this
 * 	root-element is an subobject
 * @param pInPreviousFibElement the Fib-Element which stands in th order
 * 	of Fib elements befor this Fib element
 * @param pInMainFibObject the main Fib-object of this root-element
 */
cRoot::cRoot( cRoot * pInSuperiorRootElement ,
		cFibElement * pInPreviousFibElement ,
		cFibElement * pInMainFibObject ):
		cFibBranch( pInSuperiorRootElement, pInPreviousFibElement, pInMainFibObject ),
		multimediaInfo( this ), pChecksum( NULL ){
	
	pMainFibObject = pInMainFibObject;
	
	fibUnderObjects.push_back( pInMainFibObject );
	
	if ( pFibDatabase == NULL ){
		//get new database instance
		pFibDatabase = cFibDatabase::getInstance();
	}
	
	updateAllValues();
}

#endif //FEATURE_SIMPLE_CONSTRUCTOR


/**
 * copyconstructor
 * This copyconstructor constructs a copy of the given root-Element.
 * It dosn't copy other root-elements than the given, even if ther are
 * in the root-element.
 *
 * @param rootElement the root-element to copy
 */
cRoot::cRoot( const cRoot & rootElement ):
		cFibBranch( rootElement ),
		pMainFibObject( NULL ),
		multimediaInfo( rootElement.multimediaInfo ),
		optionalPart( rootElement.optionalPart ),
		domains( rootElement.domains ),
		valueDomains( rootElement.valueDomains ),
		pChecksum( NULL )
#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
		,liExternSubobjects( rootElement.liExternSubobjects )
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
		{

	fibUnderObjects.push_back( NULL );
	
	setChecksum( rootElement.pChecksum );

	for( list< pair< cFibVariable *, doubleFib > >::const_iterator
			itrActualVariable = rootElement.liInputVariables.begin();
			itrActualVariable != rootElement.liInputVariables.end();
			itrActualVariable++ ){
		
		liInputVariables.push_back( make_pair ( new cFibVariable( this ),
			itrActualVariable->second ) );
		//set the standardvalue of the variable
		(liInputVariables.back().first)->setValue( itrActualVariable->second );
	}
	if ( pFibDatabase == NULL ){
		//get new database instance
		pFibDatabase = cFibDatabase::getInstance();
	}
#ifdef FEATURE_FAST_UPDATE
	updateAllCounters();
#endif //FEATURE_FAST_UPDATE
}



/**
 * The constructor for restoring a rootyelement from an TinyXml element.
 *
 * @param pXmlRootElement a pointer to the TinyXml node the Fib-object is stored in
 * @param outStatus An reference to an integervalue where the errorvalue
 * 	can be stored to.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlRootElement
 * 		- -2 loading error, invalid data in pXmlRootElement
 * 		- 1 loading warning, invalid data in pXmlRootElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlRootElement, maybe the loaded
 * 			object is wrong
 * @param liDefinedVariables a list with the defined variables for the
 * 	to restore Fib element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 */
cRoot::cRoot( const TiXmlElement * pXmlRootElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables ):
		pMainFibObject( NULL ), multimediaInfo( this ), pChecksum( NULL ){
	
	fibUnderObjects.push_back( NULL );
	
#ifdef DEBUG_RESTORE_XML
	//print debugging output
	printf("restoring root element\n" );
#endif//DEBUG_RESTORE_XML
	if ( pFibDatabase == NULL ){
		//get new database instance
#ifdef DEBUG_RESTORE_XML
		//print debugging output
		printf("get new database instance\n" );
#endif//DEBUG_RESTORE_XML
		pFibDatabase = cFibDatabase::getInstance();
	}

	if ( pXmlRootElement == NULL ){
		//nothing to restore
#ifdef DEBUG_RESTORE_XML
		//print debugging output
		printf("nothing to restore\n" );
#endif//DEBUG_RESTORE_XML
		outStatus = -1;
		return;
	}
	string szElementType( pXmlRootElement->Value() );
	if ( szElementType != "root" ){
		//wrong element type to restore
#ifdef DEBUG_RESTORE_XML
		//print debugging output
		printf("wrong element type to restore\n" );
#endif//DEBUG_RESTORE_XML
		outStatus = -2;
		return;
	}
	//restore every element just once
	bool bVectorChecksumRestored = false;
	bool bMultimediaInfoRestored = false;
	bool bOptionalPartRestored   = false;
	bool bDomainsRestored = false;
	bool bValueDomainsRestored   = false;
	bool bInputVariablesRestored = false;
	bool bSubRootObjectsRestored = false;
#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	bool bExternUnderObjectsRestored = false;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	unsignedIntFib uiVariablenCount = 0;
	//set the defined variables to their store value
#ifdef DEBUG_RESTORE_XML
	//print debugging output
	printf("set the defined variables to their store value\n" );
#endif//DEBUG_RESTORE_XML
	for ( list<cFibVariable*>::iterator itrActualVariable = liDefinedVariables.begin();
			itrActualVariable != liDefinedVariables.end();
			itrActualVariable++ ){
		
		uiVariablenCount++;
		(*itrActualVariable)->setIntegerValue( (longFib)(uiVariablenCount) );
	}

#ifdef DEBUG_RESTORE_XML
	//print debugging output
	printf("restoring sub elements\n" );
#endif//DEBUG_RESTORE_XML
	for ( const TiXmlNode * pChild = pXmlRootElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ) {
		
		int iType = pChild->Type();
		
#ifdef DEBUG_RESTORE_XML
		//print debugging output
		switch ( iType ){
			case TiXmlNode::ELEMENT:
				printf( "Element \"%s\" (outStatus now %i)\n", pChild->Value(), outStatus );
			break;
			
			case TiXmlNode::DOCUMENT:
				printf( "Document\n" );
			break;
			case TiXmlNode::COMMENT:
				printf( "Comment: \"%s\"\n", pChild->Value());
			break;
			case TiXmlNode::UNKNOWN:
				printf( "Unknown\n" );
			break;
			case TiXmlNode::TEXT:{
				const TiXmlText * pText = pChild->ToText();
				printf( "Text: [%s]\n", pText->Value() );
			}break;
			case TiXmlNode::DECLARATION:
				printf( "Declaration\n" );
			break;
			default:
				printf( "No known XML element\n" );
		}
#endif
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid Fib element xml -element, create
				the apropirate Fib element and call its restoreXml() method*/
				const TiXmlElement * pXmlElement = pChild->ToElement();
				if ( pXmlElement == NULL ){
#ifdef DEBUG_RESTORE_XML
					//print debugging output
					printf("no valid xml sub element\n" );
#endif//DEBUG_RESTORE_XML
					outStatus = 2;
					continue;
				}
				const string szElementType( pXmlElement->Value() );
				
#ifdef DEBUG_RESTORE_XML
				printf( "Restoring root subelement \"%s\" (outStatus now %i)\n", szElementType.c_str(), outStatus );
#endif
				
				if ( szElementType == "multimedia_info" ){
					//restore the multimediainformation
					if ( ! bMultimediaInfoRestored ){
						const intFib iReturnRestore = multimediaInfo.restoreXml( pXmlElement );
						if ( iReturnRestore == 0){
							bMultimediaInfoRestored = true;
						}else{//Warning: multimediainfo not restored correctly
							outStatus = 2;
						}
					}else{//Warning: can't restore two multimediainfos
						outStatus = 2;
					}
				}else if ( szElementType == "optionalpart" ){
					//restore the optionalpart
					if ( ! bOptionalPartRestored ){
						const intFib iReturnRestore = optionalPart.restoreXml( pXmlElement );
						if ( iReturnRestore == 0){
							bOptionalPartRestored = true;
						}else{//Warning: optionalpart not restored correctly
							outStatus = 2;
						}
					}else{//Warning: can't restore two optionalparts
						outStatus = 2;
					}
				}else if ( szElementType == "domains" ){
					//restore the domains
					if ( ! bDomainsRestored ){
						const intFib iReturnRestore = domains.restoreXml( pXmlElement );
						if ( iReturnRestore == 0){
							bDomainsRestored = true;
						}else{//Warning: domains not restored correctly
							outStatus = 2;
						}
					}else{//Warning: can't restore two domains
						outStatus = 2;
					}
				}else if ( ( szElementType == "valueDomains" ) ||
						( szElementType == "valuedomains" ) ){//"valuedomains" is depricated
					//restore the valuedomains
					if ( ! bValueDomainsRestored ){
						const intFib iReturnRestore = valueDomains.restoreXml( pXmlElement );
						if ( iReturnRestore == 0){
							bValueDomainsRestored = true;
						}else{//Warning: valuedomains not restored correctly
							outStatus = 2;
						}
					}else{//Warning: can't restore two valuedomains
						outStatus = 2;
					}
				}else if ( szElementType == "input_variables" ){
					//restore the inputvariables
					if ( ! bInputVariablesRestored ){
						
						const TiXmlElement * pXmlElementVariable = NULL;
						if ( pXmlElement->FirstChild("variable") ){
							
							pXmlElementVariable = pXmlElement->FirstChild("variable")->ToElement();
						}
						int iActualVariable = 1;
						for( iActualVariable = 1; pXmlElementVariable != NULL;
								pXmlElementVariable = pXmlElementVariable->NextSiblingElement("variable"),
								iActualVariable++ ){

							int iNumberOfVariable = 0;
							const char * szXmlVariableNumber = pXmlElementVariable->Attribute( "number", & iNumberOfVariable );
							double dDefaultValue = 0.0;
							const char * szXmlVariableDefault = pXmlElementVariable->Attribute( "default", & dDefaultValue );
							
							if ( szXmlVariableNumber == NULL ){
								//Warning: no correct variablenumber
								outStatus = 2;
							}
							if ( szXmlVariableDefault == NULL ){
								//Warning: no correct default
								outStatus = 2;
							}
							liInputVariables.push_back( make_pair( new cFibVariable( this ), dDefaultValue ) );
							//set the variable to it's store value
							uiVariablenCount++;
							liInputVariables.back().first->setIntegerValue( iNumberOfVariable );
							liDefinedVariables.push_back( liInputVariables.back().first );
						}
						bInputVariablesRestored = true;
					}else{//Warning: can't restore two inputvariables
						outStatus = 2;
					}
#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
				}else if ( szElementType == "output_variables" ){
					//restore the output variables
					if ( ! bExternUnderObjectsRestored ){
						
						const TiXmlElement * pXmlElementObject = NULL;
						if ( pXmlElement->FirstChild("object") ){
							
							pXmlElementObject = pXmlElement->FirstChild("object")->ToElement();
						}
						int iActualObject = 1;
						for( iActualObject = 1; pXmlElementObject != NULL;
								pXmlElementObject = pXmlElementObject->NextSiblingElement("object"),
								iActualObject++ ){

							int iNumberOfObject = 0;
							const char * szXmlObjectNumber = pXmlElementObject->Attribute( "number", & iNumberOfObject );
							int iVariableCount  = 0;
							const char * szXmlVariableCount  = pXmlElementObject->Attribute( "variable_count", & iVariableCount );
							
							if ( (szXmlObjectNumber == NULL) || (iNumberOfObject != iActualObject) ){
								//Warning: no correct externobjectnumber
								outStatus = 2;
							}
							if ( szXmlVariableCount == NULL ){
								//Warning: no correct de
								outStatus = 2;
							}
							liExternSubobjects.push_back( iVariableCount );
						}
						bExternUnderObjectsRestored = true;
					}else{//Warning: can't restore two extern subobjectlists
						outStatus = 2;
					}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
				}else if ( szElementType == "database_identifiers" ){
					//restore the identifiers of used database objects
					
					const TiXmlElement * pXmlElementObject = NULL;
					if ( pXmlElement->FirstChild("identifier") ){
						
						pXmlElementObject = pXmlElement->FirstChild("identifier")->ToElement();
					}
					for(  ; pXmlElementObject != NULL;
							pXmlElementObject = pXmlElementObject->NextSiblingElement("identifier") ){
						
						const char * pcValue = pXmlElement->GetText();
						if ( pcValue ){
							const longFib lDatabaseIdentifier = atol( pcValue );
							setDatabaseIdentifiers.insert( lDatabaseIdentifier );
#ifdef FEATURE_FIB_DB_USE_TREADS
							//set database identifier to load from database
							if ( pFibDatabase ){
								pFibDatabase->loadFibObject( lDatabaseIdentifier );
							}
#endif //FEATURE_FIB_DB_USE_TREADS
						}
					}//for all identifiers
				}else if ( szElementType == "main_fib_object" ){//load main -Fib-object
					//restore the main -Fib-object
					if ( pMainFibObject == NULL ){
						for ( const TiXmlNode * pChildMainObject = pChild->FirstChild();
								pChildMainObject != NULL;
								pChildMainObject = pChildMainObject->NextSibling() ){
							
							pMainFibObject = cFibElement::restoreXml(
								pChildMainObject, outStatus, liDefinedVariables );
							
							if ( pMainFibObject != NULL ){
								//main -Fib-object loaded
								if ( pMainFibObject->getType() == 'r' ){
									if ( outStatus == 0 ){
										//an error occured
										outStatus = 2;
									}
								}
								break;
							}
							if ( outStatus < 0 ){
								//an error occured
#ifdef DEBUG_RESTORE_XML
								//print debugging output
								printf("restoring root element: main Fib object could not be restored\n" );
#endif//DEBUG_RESTORE_XML
								return;
							}
						}
#ifdef FEATURE_FAST_UPDATE
						if ( pMainFibObject ){
							pMainFibObject->pSuperiorElement = this;
						}
#endif //FEATURE_FAST_UPDATE
						fibUnderObjects.front() = pMainFibObject;
					}else{//Warning: can't restore two main -Fib-object
						outStatus = 2;
					}
				}else if ( szElementType == "sub_roots" ){
					//restore the sub-root-objectlists
					if ( ! bSubRootObjectsRestored ){
						
						const TiXmlElement * pXmlElementSubRoot = NULL;
						if ( pXmlElement->FirstChild("sub_root") ){
							
							pXmlElementSubRoot = pXmlElement->FirstChild("sub_root")->ToElement();
						}
						for( ; pXmlElementSubRoot != NULL;
								pXmlElementSubRoot = pXmlElementSubRoot->NextSiblingElement("sub_root") ){

							const char * szXmlIdentifier = pXmlElementSubRoot->Attribute( "identifier" );
							long lIdentifier = 0;
							if ( szXmlIdentifier != NULL ){
								lIdentifier = atol( szXmlIdentifier );
							}else{
								//Warning: no correct externobjectnumber
								outStatus = 2;
							}
							//restore the sub-root object
							cRoot * pSubRootObject = NULL;
							
							const TiXmlElement * pXmlElSubRootObject = NULL;
							if ( pXmlElement->FirstChild() ){
								
								pXmlElSubRootObject = pXmlElementSubRoot->FirstChildElement();
							}
							for( ; pXmlElSubRootObject != NULL;
									pXmlElSubRootObject = pXmlElSubRootObject->NextSiblingElement() ){
	
								if ( pSubRootObject == NULL ){
									intFib iReturnStatus = 0;
									//no variable defined for a sub-root-object
									list<cFibVariable*> liDefinedVariablesSubRoot;
									
									cFibElement * pFibObject = cFibElement::restoreXml(
										pXmlElSubRootObject, iReturnStatus, liDefinedVariablesSubRoot );
									
									if ( (pFibObject != NULL) && (pFibObject->getType() == 'r') ){
										pSubRootObject = (cRoot*)pFibObject;
#ifdef FEATURE_FAST_UPDATE
										pSubRootObject->pSuperiorElement = this;
#endif //FEATURE_FAST_UPDATE
									}else{
										if (pFibObject != NULL){
											//delete restored Fib-object; it isn't usebel
#ifdef FEATURE_FAST_UPDATE
											pFibObject->deleteObject();
#else //FEATURE_FAST_UPDATE
											pFibObject->updateAllValues();
											deleteObject( pFibObject );
#endif //FEATURE_FAST_UPDATE
										}
										//Warning: no correct sub-root-object
										outStatus = 2;
									}
									if ( iReturnStatus < 0){
										if (pFibObject != NULL){
											//delete restored Fib-object; it isn't usebel
#ifdef FEATURE_FAST_UPDATE
											pFibObject->deleteObject();
#else //FEATURE_FAST_UPDATE
											pFibObject->updateAllValues();
											deleteObject( pFibObject );
#endif //FEATURE_FAST_UPDATE
										}
										outStatus = iReturnStatus;
#ifdef DEBUG_RESTORE_XML
										//print debugging output
										printf("restoring root element: sub root object could not be restored\n" );
#endif//DEBUG_RESTORE_XML
										return;
									}else if ( (outStatus == 0) && (iReturnStatus != 0) ){
										outStatus = iReturnStatus;
									}
								}else{
									//warning: can't resore two sub-root-objects
									outStatus = 2;
									break;
								}
							}
							if ( pSubRootObject != NULL ){
								liSubRootObjects.push_back( make_pair( lIdentifier, pSubRootObject ) );
								fibUnderObjects.push_back( pSubRootObject );
							}else{
								//Warning: no correct sub-root-object
								outStatus = 2;
							}
						}
						bSubRootObjectsRestored = true;
					}else{//Warning: can't restore two sub-root-objectlists
						outStatus = 2;
					}
				}else if ( szElementType == "vector" ){
					//restore the checksum vector
					//check the attribute of the vector
					const char * szVectorXmlType = pXmlElement->Attribute( "type" );
					
					if ( szVectorXmlType == NULL ){
						outStatus = 2;
						continue;
					}else if ( strncmp( "property.checksum", szVectorXmlType, 17 ) != 0 ){
						outStatus = 2;
						continue;
					}
					//restore the checksumvector
					if ( ! bVectorChecksumRestored ){
						pChecksum = new cVectorChecksum( pXmlElement, outStatus, liDefinedVariables );
						if ( outStatus < 0 ){
							outStatus = 2;
							continue;
						}
						bVectorChecksumRestored = true;
						pChecksum->setDefiningFibElement( this, false );
					}else{//Warning: can't restore to checksumvectors
						outStatus = 2;
					}
				}else{//unknown xml -element
					outStatus = 2;
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
				//invalid point object
				outStatus = 2;
		}
		if ( outStatus < 0 ){
			//an error occured
#ifdef DEBUG_RESTORE_XML
			//print debugging output
			printf("restoring root element: an error occured\n" );
#endif//DEBUG_RESTORE_XML
			return;
		}
	}
	//set liInputVariables to ther defaultvalues
	for( list< pair< cFibVariable *, doubleFib > >::iterator
			itrActualVariable = liInputVariables.begin();
			itrActualVariable != liInputVariables.end();
			itrActualVariable++ ){
		//set the standardvalue of the variable
		itrActualVariable->first->setValue( itrActualVariable->second );
	}

	if ( pMainFibObject == NULL ){
		//Warning: no main -Fib-object restored
		outStatus = 2;
	}
#ifdef DEBUG_RESTORE_XML
	//print debugging output
	printf("restoring root element done\n" );
#endif//DEBUG_RESTORE_XML
#ifdef FEATURE_FAST_UPDATE
	updateAllCounters();
#endif //FEATURE_FAST_UPDATE
}


/**
 * This method restores a rootobject from the stream where it is
 * stored in the compressed Fib-format.
 * This method is for internal use only.
 *
 * @param iBitStream the stream where this rootobject is stored to in,
 * 	because this stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @param outStatus An reference to an integervalue where the errorvalue
 * 	can be stored to. If the pointer is NULL no errorvalue will be
 * 	given back.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 * @param pNextRoot the next higher root-element for the to restore
 * 	Fib elements, or the last restored root-element;
 * 	if NULL the next Fib element restored will be an root-element
 */
cRoot::cRoot( cReadBits & iBitStream, intFib & outStatus, cRoot * pNextRoot ):
		pMainFibObject( NULL ), multimediaInfo( this ), pChecksum( NULL ){

	DEBUG_OUT_L2(<<"Running compressed restore root constructor"<<endl);
	
	if ( pFibDatabase == NULL ){
		//get new database instance
		pFibDatabase = cFibDatabase::getInstance();
	}

	if ( ! iBitStream.getStream()->good() ){
		DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
		outStatus = -1;
		return;
	}
	
	fibUnderObjects.push_back( NULL );
	
	/*befor restoring the sub-root-objects make superior connection to
	the superior root-object, so the sub-roots can evalue ther valid
	domains*/
	pSuperiorElement = pNextRoot;
	
	unsigned int uiBitsRead = 0;
	if ( pNextRoot == NULL ){
		/*this is the topmost root-element in the stream
		-> read the header*/
		char szFibHeader[ 3 ];
		uiBitsRead = iBitStream.readBits( szFibHeader, 24 );
		
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 24 ){
			DEBUG_OUT_EL2(<<"Error: 24 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}
		if ( strncmp( szFibHeader, "fib", 3 ) != 0 ){
			DEBUG_OUT_EL2(<<"Error: \"fib\" is missing, no valid Fib-stream"<<endl);
			outStatus = -2;
			return;
		}
	}

	//store the bitposition wher this root-object starts in the stream
	const unsignedLongFib ulRootStartBit = iBitStream.getBitReadedCount();

	/*read the 16 bit fild, with the bits for the optional information*/
	char cOptionalInformationBits[ 2 ];
	uiBitsRead = iBitStream.readBits( cOptionalInformationBits, 16 );
	
	if ( ! iBitStream.getStream()->good() ){
		DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
		outStatus = -2;
		return;
	}
	if ( uiBitsRead != 16 ){
		DEBUG_OUT_EL2(<<"Error: 16 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
		outStatus = -2;
		return;
	}
	//interpret the optional information bits
	bool bChecksumStored = false;
	if ( cOptionalInformationBits[0] & 0x80 ){
		bChecksumStored = true;
	}
	bool bMultimediaInfoStored = false;
	if ( cOptionalInformationBits[0] & 0x40 ){
		bMultimediaInfoStored = true;
	}
	bool bDomainsStored = false;
	if ( cOptionalInformationBits[0] & 0x20 ){
		bDomainsStored = true;
	}
	bool bInputVariablesStored = false;
	if ( cOptionalInformationBits[0] & 0x10 ){
		bInputVariablesStored = true;
	}
#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	bool bOutputVariablesStored = false;
	if ( cOptionalInformationBits[0] & 0x08 ){
		bOutputVariablesStored = true;
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	bool bSubRootsStored = false;
	if ( cOptionalInformationBits[0] & 0x04 ){
		bSubRootsStored = true;
	}
	bool bDbIdentifiersStored = false;
	if ( cOptionalInformationBits[0] & 0x02 ){
		bDbIdentifiersStored = true;
	}

	bool bOptionalPartStored = false;
	if ( cOptionalInformationBits[0] & 0x01 ){
		bOptionalPartStored = true;
	}
	
	if ( bChecksumStored ){
		//restore the checksum
		cVectorChecksum * pChecksumRestored = new cVectorChecksum( this );
		
		unsignedLongFib ulTypOfChecksum = 0;
		unsignedLongFib ulBitOfChecksumIntervall = 0;
		unsignedLongFib ulBitForChecksum = 0;
		
		uiBitsRead = iBitStream.readBits( ulTypOfChecksum, 16 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 16 ){
			DEBUG_OUT_EL2(<<"Error: 16 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}

		uiBitsRead = iBitStream.readBits( ulBitOfChecksumIntervall, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			DEBUG_OUT_EL2(<<"Error ChecksumIntervall: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}
		
		uiBitsRead = iBitStream.readBits( ulBitForChecksum, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			DEBUG_OUT_EL2(<<"Error bit for checksum: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}

		pChecksumRestored->setValue( 1, ulTypOfChecksum );
		pChecksumRestored->setValue( 2, ulBitOfChecksumIntervall );
		pChecksumRestored->setValue( 3, ulBitOfChecksumIntervall );
		
		pChecksum = pChecksumRestored;
	}
	//read offsets
	unsignedLongFib ulOffsetDomains = 0;
	if ( bDomainsStored ){
		//read offset wher the domains begin
		uiBitsRead = iBitStream.readBits( ulOffsetDomains, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			DEBUG_OUT_EL2(<<"Error offset domains: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}
	}
	unsignedLongFib ulOffsetInputVariables = 0;
	if ( bInputVariablesStored ){
		//read offset wher the inputvariables begin
		uiBitsRead = iBitStream.readBits( ulOffsetInputVariables, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			DEBUG_OUT_EL2(<<"Error offset input variables: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}
	}
#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	unsignedLongFib ulOffsetOutputVariables = 0;
	if ( bOutputVariablesStored ){
		//read offset wher the output variables begin
		uiBitsRead = iBitStream.readBits( ulOffsetOutputVariables, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			DEBUG_OUT_EL2(<<"Error offset output variables: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//read offset wher the main -Fib-object begins
	unsignedLongFib ulOffsetMainFibObject = 0;
	uiBitsRead = iBitStream.readBits( ulOffsetMainFibObject, 64 );
	if ( ! iBitStream.getStream()->good() ){
		DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
		outStatus = -2;
		return;
	}
	if ( uiBitsRead != 64 ){
		DEBUG_OUT_EL2(<<"Error offset main fib object: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
		outStatus = -2;
		return;
	}
	
	unsignedLongFib ulOffsetSubRoots = 0;
	if ( bSubRootsStored ){
		//read offset wher the sub-root-objects begin
		uiBitsRead = iBitStream.readBits( ulOffsetSubRoots, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			DEBUG_OUT_EL2(<<"Error offset sub roots: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}
	}
	
	//restore offset of used database identifiers
	unsignedLongFib ulOffsetDbIdentifiers = 0;
	if ( bDbIdentifiersStored ){
		//read offset wher the database identifiers begin
		uiBitsRead = iBitStream.readBits( ulOffsetDbIdentifiers, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			DEBUG_OUT_EL2(<<"Error offset database is: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}
	}

	unsignedLongFib ulOffsetOptionalPart = 0;
	if ( bOptionalPartStored ){
		//read offset wher the optionalpart begin
		uiBitsRead = iBitStream.readBits( ulOffsetOptionalPart, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			DEBUG_OUT_EL2(<<"Error offset optional part: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}
	}

	//read offset wher this root-object ends
	unsignedLongFib ulOffsetRootEnd = 0;
	uiBitsRead = iBitStream.readBits( ulOffsetRootEnd, 64 );
	if ( ! iBitStream.getStream()->good() ){
		DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
		outStatus = -2;
		return;
	}
	if ( uiBitsRead != 64 ){
		DEBUG_OUT_EL2(<<"Error offset root end: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
		outStatus = -2;
		return;
	}

	if ( bMultimediaInfoStored ){
		//read the multimediainfo
		DEBUG_OUT_L1(<<"Restoring multimediainfo "<<endl);
		unsignedLongFib ulFibVersion = 0;
		unsignedLongFib ulDatabaseVersion = 0;
		
		uiBitsRead = iBitStream.readBits( ulFibVersion, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			DEBUG_OUT_EL2(<<"Error Fib-version: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}
		
		uiBitsRead = iBitStream.readBits( ulDatabaseVersion, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			DEBUG_OUT_EL2(<<"Error Fib-databse -version: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}

		multimediaInfo.setFibVersion( ulFibVersion );
		multimediaInfo.setDatabaseVersion( ulDatabaseVersion );
	}
	if ( bDomainsStored ){
		iBitStream.readTillNextFullByte();
		
		DEBUG_OUT_L1(<<"Restoring domains; offset: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<<endl);
		if ( (iBitStream.getBitReadedCount() - ulRootStartBit) !=
				ulOffsetDomains * 8 ){
			DEBUG_OUT_L2(<<"Warning: offset of the domains is incorrect "<<endl);
			DEBUG_OUT_L2(<<"   is: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<< " should be: "<<ulOffsetDomains * 8<<endl);
			outStatus = 2;
		}
		//read the domains
		const intFib iDomainsRestored = domains.restore( iBitStream );
		if ( iDomainsRestored < 0 ){
			outStatus = iDomainsRestored;
			DEBUG_OUT_EL2(<<"Error: while restoring domains"<<endl);
			return;
		}else if ( (outStatus == 0) && ( iDomainsRestored != 0 ) ){
			outStatus = iDomainsRestored;
		}
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		//read the value domains
		const intFib iValueDomainsRestored = valueDomains.restore( iBitStream );
		if ( iValueDomainsRestored < 0 ){
			outStatus = iValueDomainsRestored;
			return;
		}else if ( (outStatus == 0) && ( iValueDomainsRestored != 0 ) ){
			outStatus = iValueDomainsRestored;
		}
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
	}
	cDomains validDomains = getValidValueDomains();
	
	/*create the propertytypelist, with the propertytypes in the order
	they will be counted when restored;
	create after the domains are restored and befor a subobject is restored*/
	createStorePropertyOrder();
	
	/*restore inputvariables*/
	list<cFibVariable*> liDefinedVariables;
	
	if ( bInputVariablesStored ){
		iBitStream.readTillNextFullByte();
		
		DEBUG_OUT_L1(<<"Restoring inputvariables; offset: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<<endl);
		if ( (iBitStream.getBitReadedCount() - ulRootStartBit) !=
				ulOffsetInputVariables * 8 ){
			DEBUG_OUT_L2(<<"Warning: offset of the input variables is incorrect "<<endl);
			DEBUG_OUT_L2(<<"   is: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<< " should be: "<<ulOffsetInputVariables * 8<<endl);
			//Warning: offset of the input variables is incorrect
			outStatus = 2;
		}
		//read the number of input variables
		unsignedLongFib ulCountOfInVar = 0;
		uiBitsRead = iBitStream.readBits( ulCountOfInVar, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			outStatus = -2;
			return;
		}
		
		const bool bCountInVarSet = setNumberOfInputVariables( ulCountOfInVar );
		if ( ! bCountInVarSet ){
			outStatus = -2;
			return;
		}
		//read the standardvalues of the input variables
		for ( unsignedIntFib uiActualInVar = 1;
				uiActualInVar <= ulCountOfInVar; uiActualInVar++ ){
		
			//read the inputvariable
			cTypeInVar typeInVar( uiActualInVar );
			cDomain * pDomainInVar = validDomains.getDomainForElement( typeInVar );
			bool bStandardVariableDomain = false;
			if ( pDomainInVar == NULL ){
				/*no variable domain*/
				pDomainInVar = typeInVar.getStandardDomain();
				bStandardVariableDomain = true;
			}
			if ( ! typeInVar.isCompatible( *pDomainInVar) ){
				/*if the variable domain is not compatible to variable type
				-> can't restore the standardvalue*/
				outStatus = -2;
				return;
			}
			cDomainIntegerBasis * pIntDomainInVar = (cDomainIntegerBasis*)pDomainInVar;
			
			doubleFib dStandardValue = pIntDomainInVar->restoreValue( iBitStream, outStatus );
			
			if ( bStandardVariableDomain ){
				delete pDomainInVar;
			}
			if ( outStatus < 0 ){
				return;
			}
			const bool bStandardValueInVarSet =
				setStandardValueOfInputVariable( uiActualInVar, dStandardValue );
			if ( ! bStandardValueInVarSet ){
				outStatus = 2;
			}
			//set the number under which the variable was stored
			cFibVariable * pInVar = getInputVariable( uiActualInVar );
			if ( pInVar ){
				pInVar->setValue( uiActualInVar );
			}else{
				outStatus = 2;
			}
		}
		liDefinedVariables = getInputVariables();
	}
#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	/*restore output variables*/
	if ( bOutputVariablesStored ){
		DEBUG_OUT_L1(<<"Restoring output variables; offset: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<<endl);
		iBitStream.readTillNextFullByte();
		
		if ( (iBitStream.getBitReadedCount() - ulRootStartBit) !=
				ulOffsetOutputVariables * 8 ){
			DEBUG_OUT_L2(<<"Warning: offset of the extern -objects is incorrect "<<endl);
			DEBUG_OUT_L2(<<"   is: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<< " should be: "<<ulOffsetOutputVariables * 8<<endl);
			outStatus = 2;
		}
		//read the count of extern objects
		unsignedLongFib ulCountOfExtObj = 0;
		uiBitsRead = iBitStream.readBits( ulCountOfExtObj, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			outStatus = -2;
			return;
		}
		
		const bool bCountExternObjectsSet =
			setNumberOfExternSubobjects( ulCountOfExtObj );
		if ( ! bCountExternObjectsSet ){
			outStatus = 2;
		}
		//read the bits for the counts of the output variables per extern object
		cDomainNaturalNumberBit domainNaturalNumberBit8( 8 );
		
		unsignedIntFib uiBitsPerCountOutVar = domainNaturalNumberBit8.
			restoreIntegerValue( iBitStream, outStatus );
		if ( outStatus < 0 ){
			return;
		}
		cDomainNaturalNumberBit domainNatNumOutVar( uiBitsPerCountOutVar );

		//read the counts of the output variables
		for ( unsignedIntFib uiActualExtObj = 1;
				uiActualExtObj <= ulCountOfExtObj; uiActualExtObj++ ){
		
			//read the count for ther output variables
			unsignedIntFib uiCountOutVars = domainNatNumOutVar.
				restoreIntegerValue( iBitStream, outStatus );
			if ( outStatus < 0 ){
				return;
			}
			const bool bCountOutVarsSet =
				setNumberOfOutputVariables( uiActualExtObj, uiCountOutVars );
			if ( ! bCountOutVarsSet ){
				outStatus = 2;
			}
		}
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	//restore the main -Fib-object
	iBitStream.readTillNextFullByte();
		
	if ( (iBitStream.getBitReadedCount() - ulRootStartBit) !=
			ulOffsetMainFibObject * 8 ){
		DEBUG_OUT_L2(<<"Warning: offset of the main -Fib-object is incorrect "<<endl);
		DEBUG_OUT_L2(<<"   is: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<< " should be: "<<ulOffsetMainFibObject * 8<<endl);
		outStatus = 2;
	}
	DEBUG_OUT_L1(<<"Restoring main -Fib-object; offset: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<<endl);
	
#ifdef FEATURE_FAST_UPDATE
	setMainFibObject( cFibElement::restoreInternal( iBitStream, outStatus,
		liDefinedVariables, validDomains, this ) );
#else //FEATURE_FAST_UPDATE
	pMainFibObject = cFibElement::restoreInternal( iBitStream, outStatus,
		liDefinedVariables, validDomains, this );
	fibUnderObjects.front() = pMainFibObject;
#endif //FEATURE_FAST_UPDATE
	
	if ( outStatus < 0 ){
		return;
	}
	iBitStream.readTillNextFullByte();
	
	/*restore sub-root-objects*/
	if ( bSubRootsStored ){
		DEBUG_OUT_L1(<<"Restoring sub-root-objects; offset: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<<endl);
		if ( (iBitStream.getBitReadedCount() - ulRootStartBit) !=
				ulOffsetSubRoots * 8 ){
			DEBUG_OUT_L2(<<"Warning: offset of the sub-roots is incorrect "<<endl);
			DEBUG_OUT_L2(<<"   is: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<< " should be: "<<ulOffsetSubRoots * 8<<endl);
			outStatus = 2;
		}
		//read the count of extern objects
		unsignedLongFib ulCountOfSubRoots = 0;
		uiBitsRead = iBitStream.readBits( ulCountOfSubRoots, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error count sub roots: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			DEBUG_OUT_EL2(<<"Error count sub roots: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}
		
		//read the bits for the identifiers of the sub-root-objects
		const cDomainNaturalNumberBit domainNaturalNumberBit8( 8 );
		
		const unsignedIntFib uiBytsPerIdentifier = domainNaturalNumberBit8.
			restoreIntegerValue( iBitStream, outStatus );
		if ( outStatus < 0 ){
			return;
		}
		//domain for the identifiers
		const cDomainIntegerBit domainIntegerIdentifier( uiBytsPerIdentifier * 8 );

		//read the sub-root-objects and ther identifer
		for ( unsignedIntFib uiActualSubRoot = 1;
				uiActualSubRoot <= ulCountOfSubRoots; uiActualSubRoot++ ){
			
			DEBUG_OUT_L1(<<"Restoring sub-root-object "<<uiActualSubRoot<<" ; offset: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<<endl);
		
			//read the identifier of the sub-root-object
			const longFib lIdentifier = domainIntegerIdentifier.
				restoreIntegerValue( iBitStream, outStatus );
			if ( outStatus < 0 ){
				return;
			}
			//read the sub-root object
			cRoot * pSubRootObject = cFibElement::
				restoreRootInternal( iBitStream, outStatus, this );
			
			if ( pSubRootObject ){
				//add the restored sub-root-object
#ifdef FEATURE_FAST_UPDATE
				pSubRootObject->pSuperiorElement = this;
#endif //FEATURE_FAST_UPDATE
				liSubRootObjects.push_back( make_pair( lIdentifier, pSubRootObject ) );
				fibUnderObjects.push_back( pSubRootObject );
			}
			if ( outStatus < 0 ){
				return;
			}
			iBitStream.readTillNextFullByte();
		}
	}
	//restore database identifiers
	if ( bDbIdentifiersStored ){
		//restore count of used database identifiers
		unsignedLongFib ulCountOfIdentifiers = 0;
		uiBitsRead = iBitStream.readBits( ulCountOfIdentifiers, 64 );
		if ( ! iBitStream.getStream()->good() ){
			DEBUG_OUT_EL2(<<"Error count of used database identifiers: stream not good"<<endl);
			outStatus = -2;
			return;
		}
		if ( uiBitsRead != 64 ){
			DEBUG_OUT_EL2(<<"Error count of used database identifiers: 64 bits to read, but "<<uiBitsRead<<" bits readed"<<endl);
			outStatus = -2;
			return;
		}
		//restore bits for identifiers
		const cDomainNaturalNumberBit domainNaturalNumberBit8( 8 );
		
		const unsignedIntFib uiBitsPerIdentifier = domainNaturalNumberBit8.
			restoreIntegerValue( iBitStream, outStatus );
		if ( outStatus < 0 ){
			return;
		}
		//domain for the identifiers
		const cDomainIntegerBit domainIntegerIdentifier( uiBitsPerIdentifier );
		
		//restore identifiers
		for ( unsignedLongFib ulActualIdentifier = 0;
				ulActualIdentifier < ulCountOfIdentifiers; ulActualIdentifier++ ){
			
			//read the identifier of the sub-root-object
			const longFib lIdentifier = domainIntegerIdentifier.
				restoreIntegerValue( iBitStream, outStatus );
			if ( outStatus < 0 ){
				return;
			}
			setDatabaseIdentifiers.insert( lIdentifier );
#ifdef FEATURE_FIB_DB_USE_TREADS
			//set database identifier to load from database
			if ( pFibDatabase ){
				pFibDatabase->loadFibObject( lIdentifier );
			}
#endif //FEATURE_FIB_DB_USE_TREADS
		}//end for load database identifiers
		iBitStream.readTillNextFullByte();
	}//end restore used database identifiers
	
	//restore the optional part
	if ( bOptionalPartStored ){
		iBitStream.readTillNextFullByte();
		
		DEBUG_OUT_L1(<<"Restoring optionalpart; offset: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<<endl);
		if ( (iBitStream.getBitReadedCount() - ulRootStartBit) !=
				ulOffsetOptionalPart * 8 ){
			DEBUG_OUT_L2(<<"Warning: offset of the optionalpart is incorrect "<<endl);
			DEBUG_OUT_L2(<<"   is: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<< " should be: "<<ulOffsetOptionalPart * 8<<endl);
			outStatus = 2;
		}
		//read the optional part till the end of this root-element
		const intFib iOptionalPart = optionalPart.restore( iBitStream,
			ulOffsetRootEnd - ulOffsetOptionalPart );
		//read the value domains
		if ( iOptionalPart < 0 ){
			outStatus = iOptionalPart;
			DEBUG_OUT_L2(<<"Error: Restoring optional part returned "<<iOptionalPart<<endl);
			return;
		}else if ( (outStatus == 0) && ( iOptionalPart != 0 ) ){
			outStatus = iOptionalPart;
			DEBUG_OUT_L2(<<"Warning: Restoring optional part returned "<<iOptionalPart<<endl);
		}
		extractCommentsFromOptionalPart();
	}
	//read root end
	iBitStream.readTillNextFullByte();
	
	if ( (iBitStream.getBitReadedCount() - ulRootStartBit) !=
			ulOffsetRootEnd * 8 ){
		DEBUG_OUT_L2(<<"Warning: offset of the root-object end is incorrect "<<endl);
		DEBUG_OUT_L2(<<"   is: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<< " should be: "<<ulOffsetRootEnd * 8<<endl);
		outStatus = 2;
	}

	//set liInputVariables to ther defaultvalues
	for( list< pair< cFibVariable *, doubleFib > >::iterator
			itrActualVariable = liInputVariables.begin();
			itrActualVariable != liInputVariables.end();
			itrActualVariable++ ){
		//set the standardvalue of the variable
		itrActualVariable->first->setValue( itrActualVariable->second );
	}

	if ( pMainFibObject == NULL ){
		DEBUG_OUT_L2(<<"Warning: no main-Fib-object restored"<<endl);
		outStatus = 2;
	}
#ifdef FEATURE_FAST_UPDATE
	updateAllCounters();
#endif //FEATURE_FAST_UPDATE
	DEBUG_OUT_L1(<<"End restoring root; offset: "<<(iBitStream.getBitReadedCount() - ulRootStartBit)<<endl);
}


/**
 * desstructor
 */
cRoot::~cRoot(){
	if ( pChecksum ){
		delete pChecksum;
	}
	//delete the input variables
	while( ! liInputVariables.empty() ){
		
		delete (liInputVariables.back().first);
		liInputVariables.pop_back();
	}
	//delete old backup input variable list
	while ( ! liLiStoredInputVariables.empty() ){
		
		list< cFibVariable * > & liStoredInputVariables =
			liLiStoredInputVariables.back();
		
		while ( ! liStoredInputVariables.empty() ){
			//the old values will be overwritten
			delete (liStoredInputVariables.back());
			liStoredInputVariables.pop_back();
		}
		liLiStoredInputVariables.pop_back();
	}
	//delete old backup below defined variable list
	while ( ! liLiStoredBelowVariables.empty() ){
		
		list< cFibVariable * > & liStoredBelowVariables =
			liLiStoredBelowVariables.back();
		
		while ( ! liStoredBelowVariables.empty() ){
			//the old values will be overwritten
			delete (liStoredBelowVariables.back());
			liStoredBelowVariables.pop_back();
		}
		liLiStoredBelowVariables.pop_back();
	}
	//new root instance created
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
char cRoot::getType() const{
	return 'r';
}


/**
 * This method checks, if this Fib element is an valid Fib element.
 *
 * @return true if this Fib element is an valid Fib element, else false
 */
bool cRoot::isValidFibElement() const{
	if ( ! cFibBranch::isValidFibElement() ){
		return false;
	}
	if ( pMainFibObject == NULL ){
		return false;
	}
	
	return true;
}


/**
 * This method checks if the given variable is defined in the given
 * direction from this Fib element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @param variable the variable to check if it is defined
 * @param direction the direction from this Fib element, in which the
 * 	variable should be defined; standardvalue is ED_POSITION so yust
 * 	this Fib element will be checked
 * @param pCallingFibElement the Fib-Element which called this method
 * @return true if the variable is used, else false
 */
bool cRoot::isDefinedVariableInternal( const cFibVariable *variable,
		edDirection direction,
		const cFibElement * pCallingFibElement ) const{
	
#ifdef FEATURE_NEW_ROOT_GET_DEFINED_VARIBLES
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) ){
		
		//check the input variables this root-element defines
		for( list< pair< cFibVariable *, doubleFib > >::const_iterator
				itrActualVariable = liInputVariables.begin();
				itrActualVariable != liInputVariables.end();
				itrActualVariable++ ){
		
			if ( variable == (itrActualVariable->first) ){
				return true;
			}
		}//variable not defined here
	}else if ( direction == ED_HIGHER_EQUAL ){
		
		if ( ( pCallingFibElement == pMainFibObject ) ||
				( pCallingFibElement == this ) || ( pCallingFibElement == NULL ) ){
			//check the input variables this root-element defines
			for( list< pair< cFibVariable *, doubleFib > >::const_iterator
					itrActualVariable = liInputVariables.begin();
					itrActualVariable != liInputVariables.end();
					itrActualVariable++ ){
			
				if ( variable == (itrActualVariable->first) ){
					return true;
				}
			}//variable not defined here
		}//else for other subobjects the input variables are not defined
	}

	if ( (direction == ED_ALL) || (direction == ED_BELOW) ||
			(direction == ED_BELOW_EQUAL) ){
		/*just search below for defined variables; other root-elements
		don't pass on variables*/
		if ( ! fibUnderObjects.empty() ){
			//check for all subobjects
			for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
					actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
	
				if ( (*actualUnderObject) != NULL ){
					if ( (*actualUnderObject)->isDefinedVariableInternal(
							variable, ED_BELOW_EQUAL, this ) ){
						return true;
					}
				}
			}
		}//else no elements to check in the direction
	}//else
		
#else //FEATURE_NEW_ROOT_GET_DEFINED_VARIBLES
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//check the input variables this root-element defines
		for( list< pair< cFibVariable *, doubleFib > >::const_iterator
				itrActualVariable = liInputVariables.begin();
				itrActualVariable != liInputVariables.end();
				itrActualVariable++ ){
		
			if ( variable == (itrActualVariable->first) ){
				return true;
			}
		}//variable not defined here
	}

	if ( (direction == ED_ALL) || (direction == ED_BELOW) ||
			(direction == ED_BELOW_EQUAL) ){
		/*just search below for defined variables; other root-elements
		don't pass on variables*/

		if ( pMainFibObject != NULL ){
			return pMainFibObject->isDefinedVariableInternal(
				variable, ED_BELOW_EQUAL, this );
		}
	}//else
#endif //FEATURE_NEW_ROOT_GET_DEFINED_VARIBLES
	return false;
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
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib element will be checked
 * @param pCallingFibElement the Fib-Element which called this method
 * @return the set with all variables used in the given direction from
 * 	this Fib element
 */
list<cFibVariable*> cRoot::getDefinedVariablesInternal( edDirection direction,
		const cFibElement * pCallingFibElement ){
	
	list<cFibVariable*> liDefinedVariables;
	
#ifdef FEATURE_NEW_ROOT_GET_DEFINED_VARIBLES
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) ){
		
		//insert the input variables this root-element defines
		for( list< pair< cFibVariable *, doubleFib > >::iterator
				itrActualVariable = liInputVariables.begin();
				itrActualVariable != liInputVariables.end();
				itrActualVariable++ ){
		
			liDefinedVariables.push_back( itrActualVariable->first );
		}
	}else if ( direction == ED_HIGHER_EQUAL ){
		
		if ( ( pCallingFibElement == pMainFibObject ) ||
				( pCallingFibElement == this ) || ( pCallingFibElement == NULL ) ){
			//insert the input variables this root-element defines
			for( list< pair< cFibVariable *, doubleFib > >::iterator
					itrActualVariable = liInputVariables.begin();
					itrActualVariable != liInputVariables.end();
					itrActualVariable++ ){
			
				liDefinedVariables.push_back( itrActualVariable->first );
			}
		}//else for other subobjects the input variables are not defined
	}
	if ( (direction == ED_ALL) || ( direction == ED_BELOW ) ||
			(direction == ED_BELOW_EQUAL) ){
		
		if ( ! fibUnderObjects.empty() ){
			//check for all subobjects
			for ( list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
					actualUnderObject!=fibUnderObjects.end(); actualUnderObject++ ){
	
				if ( (*actualUnderObject) != NULL ){
					list<cFibVariable*> liDefinedVariablesOfUnderObject =
						(*actualUnderObject)->getDefinedVariablesInternal( ED_BELOW_EQUAL, this );
					liDefinedVariables.insert( liDefinedVariables.end() ,
						liDefinedVariablesOfUnderObject.begin(),
						liDefinedVariablesOfUnderObject.end() );
				}
			}
		}//else no elements to check in the direction
		
	}
#else //FEATURE_NEW_ROOT_GET_DEFINED_VARIBLES
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//insert the input variables this root-element defines
		for( list< pair< cFibVariable *, doubleFib > >::iterator
				itrActualVariable = liInputVariables.begin();
				itrActualVariable != liInputVariables.end();
				itrActualVariable++ ){
		
			liDefinedVariables.push_back( itrActualVariable->first );
		}
	}

	if ( (direction == ED_ALL) || ( direction == ED_BELOW ) ||
			(direction == ED_BELOW_EQUAL) ){
		
		if ( pMainFibObject != NULL ){
			//check the main -fib object
			const list<cFibVariable*> liDefinedVariablesOfUnderObject =
				pMainFibObject->getDefinedVariablesInternal(
					ED_BELOW_EQUAL, this );
			liDefinedVariables.insert( liDefinedVariables.end() ,
				liDefinedVariablesOfUnderObject.begin(),
				liDefinedVariablesOfUnderObject.end() );

		}//else no elements to check in the direction
	}
#endif //FEATURE_NEW_ROOT_GET_DEFINED_VARIBLES

	return liDefinedVariables;
}


/**
 * This method checks, if all Fib elements of this Fib-object
 * have the subobjects they need to be correct.
 *
 * @return true if all Fib elements of this Fib-object have the
 * 	subobjects they need to be correct, else false
 */
bool cRoot::hasUnderAllObjects( ) const{

	if ( pMainFibObject == NULL ){
		//main -Fib-object is missing
		return false;
	}
	return cFibBranch::hasUnderAllObjects();
}


/**
 * This method evaluades the Fib-object.
 *
 * @param evaluePosition a reference to the object with the
 * 	evaluePosition() method to evalue /store the positions and ther
 * 	properties; everytime a point (to evalue) is reached in the
 * 	evaluation, this method is called with the position and the
 * 	properties of the point; @see iEvaluePosition
 * @param objectPoint the object point in the order of true partobjects
 * 	to evalue
 * @param liVecProperties a list with the property vectors which should
 * 	be global for the evalued object
 * @return if the evalueation was successfull true, else false
 */
bool cRoot::evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const{

	if ( pMainFibObject == NULL ){
		//nothing to evalue
		return false;
	}
#ifdef DEBUG_EVALUE
	//if exists print first optional part entry
	if ( optionalPart.getNumberOfEntries() != 0 ){
		pair< string, string > firstEntry = optionalPart.getEntry( 1 );
		printf( "cRoot::evalueObject() %s: %s\n",
			firstEntry.first.c_str(), firstEntry.second.c_str() );
	}
	
#endif //DEBUG_EVALUE
	//evalue main -Fib-object
	return pMainFibObject->evalueObject( evaluePosition, objectPoint, liVecProperties );
}


/**
 * This method evaluades the Fib-object.
 * Evertime a Fib elements, with a type of the given type chars in
 * liCFibElementTyps, is reached while evaluation, it is given
 * back with the properties which it has.
 * Ever pointelement is given back. The type chars for pointelements
 * don't need to be in the list liCFibElementTyps.
 *
 * @param evalueFibElement a reference to the object with the
 * 	evalueElement() method to evalue /store the Fib elements and ther
 * 	properties; everytime a Fib element (with one of the type given
 * 	in liCFibElementTyps) is reached in the evaluation, the method
 * 	evalueElement() of this objects is called with the Fib element
 * 	and the properties of the Fib element; @see iEvalueFibElement
 * @param objectPoint the object point in the order of true partobjects
 * 	to evalue
 * @param liVecProperties a list with the property vectors which should
 * 	be global for the evalued object
 * @param liCFibElementTyps a list with the type chars (@see getType)
 * 	of the Fib elements to return
 * @return if the evalueation was successfull true, else false
 */
bool cRoot::evalueObject( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties,
		const list<char> & liCFibElementTyps ){
	//check if this Fib element should be given back with evalueElement()
	for ( list<char>::const_iterator itrCType = liCFibElementTyps.begin();
			itrCType != liCFibElementTyps.end(); itrCType++ ){
		
		if ( *itrCType == getType() ){
			//call evalueElement() with this element
			return evalueFibElement.evalueElement( *this, liVecProperties );
		}
	}//else if this element shouldn't be returned -> evalue the main -Fib-object

	if ( pMainFibObject == NULL ){
		//nothing to evalue
		return false;
	}
	//evalue main -Fib-object
	return pMainFibObject->evalueObject( evalueFibElement, objectPoint,
		liVecProperties, liCFibElementTyps );
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
 * @param lMaxTime the maximum time for the evaluation, the returned
 * 	exceed this value; the value 0 stands for infinity, so the 
 * 	evaluation won't be stoped
 * @return a value for the time needed to evalue the object
 */
unsignedLongFib cRoot::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	if ( pMainFibObject == NULL ){
		//nothing to evalue except this root-element
		return 1;
	}
	if ( (1 <= lMaxTime) && (lMaxTime <= 3) ){
		//max time is up with evaluing this root-element
		return lMaxTime;
	}
	//decrease max time about the evalue time of this root-element
	if ( lMaxTime != 0 ){
		lMaxTime -= 3;
	}

	//evalue time for main -Fib-object
	return (pMainFibObject->getTimeNeed( lMaxTime ) + 3);
}


/**
 * This method evaluades the size of the Fib-object in bits in the
 * compressed file form.
 *
 * The optionalpart field of root-elements will not be ignored.
 *
 * @see store()
 * @return the size of the Fib-object in bits in the compressed form
 */
unsignedLongFib cRoot::getCompressedSize() const{
	
	//evalue compressed size without the optional part
	return getCompressedSize( true );
}


/**
 * This method evaluades the size of the Fib-object in bits in the
 * compressed file form.
 *
 * @see store()
 * @param bWriteOptionalPart if true the size of the optionalpart is
 * 	evalued, else it is ignored
 * @return the size of the Fib-object in bits in the compressed form
 */
unsignedLongFib cRoot::getCompressedSize( bool bWriteOptionalPart ) const{
	//the summ of the compressed size
	unsignedLongFib ulCompressedSize = 0;
	
	/*store the values of the variables, the variables will be used to
	store ther number*/
	
	//prepare the bits for storing variables
	unsignedIntFib uiVariablenCount = liInputVariables.size();
	
	//counting variables in the main -Fib-object and creating a variables domain
	if ( pMainFibObject ){
		uiVariablenCount = const_cast<cFibElement*>(pMainFibObject)->
			enumerateVariablesForStoring( uiVariablenCount );
	}
	cDomain * pOldVariableDomain = NULL;
	if ( uiVariablenCount > 0 ){//create the domain for the variables
		cTypeVariable typeVariable;
		unsigned int uiDigitsForVariables = getDigits( uiVariablenCount );
		cDomainNaturalNumberBit domainVariables( uiDigitsForVariables );
		
		//store the old variable domain
		pOldVariableDomain = const_cast<cDomains*>(&domains)->
			getDomainForElement( typeVariable );
		if ( pOldVariableDomain ){
			pOldVariableDomain = pOldVariableDomain->clone();
		}
		const_cast<cDomains*>(&domains)->addDomain( typeVariable, domainVariables );
	}
	
	/*create the propertytypelist, with the propertytypes in the order
	they will be counted when stored, for propertyelements to evalue ther size*/
	const_cast<cRoot*>(this)->createStorePropertyOrder();
	
	
	if ( pSuperiorElement == NULL ){
		//the string "fib" at the beginning of the stream
		ulCompressedSize += 3 * 8;
	}
	//16 bit for the optional information field
	ulCompressedSize += 16;
	
	//summ compressed size of all Fib element properties
	if ( pChecksum ){
		//an checksumfield exists
		ulCompressedSize += 32 + 64 * 2;
	}
	
	//add bits for the multimediainfo
	if ( pSuperiorElement != NULL ){
		/*if the multimediainfo of this root-element differs to the
		multimediainfo of the supierior root-element the multimediainfo
		have to be be written*/
		if ( ! ( multimediaInfo ==
				(((cRoot*)(pSuperiorElement))->multimediaInfo) ) ){
			ulCompressedSize += 128;
		}
	}
	
	if ( bWriteOptionalPart ){
		//add bits for the optional part
		//extract text from the main-Fib-object into the optionalpart
		/*enummerate comments and export ther strings to the optional part
		and create the needed domains*/
		cOptionalPart * optionalPartFull =
			(const_cast<cRoot*>(this))->exportCommentsIntoOptionalPart();
		
		if ( optionalPartFull ){
			if ( optionalPartFull->getNumberOfEntries() != 0 ){
				//write optional part
				
				//offset optional part
				ulCompressedSize += 64;
				
				ulCompressedSize += optionalPartFull->getCompressedSize();
			}
			delete optionalPartFull;
		}
	}

	if ( (domains.getNumberOfDomains() != 0) ||
			(valueDomains.getNumberOfDomains() != 0) ){
		//add bits for the domains
		unsignedLongFib ulCompressedDomainsSize = 64;//offset;
		//size of domains
		ulCompressedDomainsSize += domains.getCompressedSize();
		ulCompressedDomainsSize += valueDomains.getCompressedSize();
		
		//round up to a full byte
		ulCompressedDomainsSize = roundUpToFullByte( ulCompressedDomainsSize );
		
		ulCompressedSize += ulCompressedDomainsSize;
	}

	if ( ! liInputVariables.empty() ){
		//add the bits for the input variables
		unsignedLongFib ulCompressedInputVariablesSize = 64;//offset;
		ulCompressedInputVariablesSize += 64;//input variables count

		//add bits for the standardvalues
		//get valid domains
		//for every input variable
		for ( unsignedIntFib iActualInVarNumber = 1;
				iActualInVarNumber <= liInputVariables.size();
				iActualInVarNumber++ ){
			//get the domain for the i'th input variable
			
			cTypeInVar typeInVar( iActualInVarNumber );
			cDomainSingle * domain = (cDomainSingle*)(
				domains.getDomainForElement( typeInVar ) );
			
			bool bStandardInVarDomain = false;
			if ( domain == NULL ){
				//use the standard domain
				domain = (cDomainSingle*)( typeInVar.getStandardDomain() );
				bStandardInVarDomain = true;
			}
			
			//add the bits vor the i'th input variable standardvalue
			ulCompressedInputVariablesSize +=
				domain->getCompressedSizeForValue();
			
			if ( bStandardInVarDomain ){
				delete domain;
			}
		}
		//round up to a full byte
		ulCompressedInputVariablesSize = roundUpToFullByte( ulCompressedInputVariablesSize );
		
		ulCompressedSize += ulCompressedInputVariablesSize;
	}
	
#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//output variables
	if ( ! liExternSubobjects.empty() ){
		//add the bits for the output variables
		unsignedLongFib ulCompressedOutputVariablesSize = 64;//offset;
		ulCompressedOutputVariablesSize += 64;//output variables count
		ulCompressedOutputVariablesSize += 8;//bits for output variable

		//evalue the bits per output variable
		unsigned int uiBitPerOutputVariable = 0;
		
		for ( list< unsignedIntFib >::const_iterator itrActualVariable =
					liExternSubobjects.begin();
				itrActualVariable != liExternSubobjects.end();
				itrActualVariable++ ){
				
			if ( uiBitPerOutputVariable <
					getDigits( *itrActualVariable ) ){
				
				uiBitPerOutputVariable =
					getDigits( *itrActualVariable );
			}
				
		}
		//add bits for the outputvariable list
		ulCompressedOutputVariablesSize +=
			uiBitPerOutputVariable * liExternSubobjects.size();

		//round up to a full byte
		uiBitPerOutputVariable = roundUpToFullByte( uiBitPerOutputVariable );
		
		ulCompressedSize += ulCompressedOutputVariablesSize;
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	//sum compressed size of main fib object
	if ( pMainFibObject != NULL ){
	
		unsignedLongFib ulBitsForMainFibObject = 64;//offset;

		ulBitsForMainFibObject += pMainFibObject->getCompressedSize();
		
		//round up to a full byte
		ulBitsForMainFibObject = roundUpToFullByte( ulBitsForMainFibObject );
		
		ulCompressedSize += ulBitsForMainFibObject;
	}else{//error no object -> write 8 0 byts for NULL = no object
		ulCompressedSize += 64;
	}
	
	//sum compressed size of all sub-root-elements
	if ( getNumberOfSubRootObjects() != 0 ){
		//add offset + number of sub-roots + byts per identifier
		ulCompressedSize += 64 + 64 + 8;
		
		//evalue the bits per sub-root-element identifier
		unsigned int uiBitPerIdentifier = 0;
		for ( list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement =
					liSubRootObjects.begin();
				itrActualRootElement != liSubRootObjects.end();
				itrActualRootElement++ ){
			
			if ( uiBitPerIdentifier <
					getDigits( itrActualRootElement->first ) ){
				
				uiBitPerIdentifier=
					getDigits( itrActualRootElement->first );
			}
		}
		//add one bit for the sign of the identifier
		uiBitPerIdentifier = roundUpToFullByte( uiBitPerIdentifier );
		
		for ( list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement =
					liSubRootObjects.begin();
				itrActualRootElement != liSubRootObjects.end();
				itrActualRootElement++ ){

			if ( itrActualRootElement->second != NULL ){
				unsigned int ulBitsForSubRoot = uiBitPerIdentifier;
				
				ulBitsForSubRoot += itrActualRootElement->second->
					getCompressedSize( bWriteOptionalPart );
				
				//round up to a full byte
				ulBitsForSubRoot = roundUpToFullByte( ulBitsForSubRoot );
				
				ulCompressedSize += ulBitsForSubRoot;
			}else{//error no object -> write 8 0 byts for NULL = no object
				unsigned int ulBitsForSubRoot = uiBitPerIdentifier + 64;

				//round up to a full byte
				ulBitsForSubRoot = roundUpToFullByte( ulBitsForSubRoot );
				
				ulCompressedSize += ulBitsForSubRoot;
			}
		}
	}
	
	//sum compressed size for database identifiers
	if ( ! setDatabaseIdentifiers.empty() ){
		//offset databas identifiers + number of identifiers + count bit for identifer 
		ulCompressedSize += 64 + 64 + 8;
		//evalue bits for the identifiers
		unsigned int uiMaxBitsForIdentifier = 0;
		for ( set< longFib >::const_iterator itrIdentifier = setDatabaseIdentifiers.begin();
				itrIdentifier != setDatabaseIdentifiers.end(); itrIdentifier++ ){
			
			const unsigned int uiBitsForIdentifier =
				getDigits( *itrIdentifier );
			if ( uiMaxBitsForIdentifier < uiBitsForIdentifier ){
				uiMaxBitsForIdentifier = uiBitsForIdentifier;
			}
		}
		//add sign bit
		
		ulCompressedSize += setDatabaseIdentifiers.size() * uiMaxBitsForIdentifier;
	}
	
	//offset root end
	ulCompressedSize += 64;
	

	//restore the old variable domain
	if ( pOldVariableDomain != NULL ){
		cTypeVariable typeVariable;
		const_cast<cDomains*>(&domains)->addDomain( typeVariable, *pOldVariableDomain );
		delete pOldVariableDomain;
	}else{//ther wasn't an old variable domain -> delete the created variable domain
		cTypeVariable typeVariable;
		const_cast<cDomains*>(&domains)->deleteDomain( typeVariable );
	}
	
	return ulCompressedSize;
}


/**
 * @return true if this Fib element is movebel else false
 */
bool cRoot::isMovable() const{
	//root-element isn't moveble
	return false;
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
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib-object
 * @return the copy of the Fib element
 */
cFibElement *cRoot::copyElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		//copy this element
		return new cRoot( *this );
	}//else get the fib element and copy it
	
	const cFibElement * pFibElementToCopy = getConstFibElement(
		cType, elementPoint, bAbsolute );
	
	if ( pFibElementToCopy ){
		return ( pFibElementToCopy->copyElement( 'u', 0 ) );
	}//else
	return NULL;
}


#ifdef FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib-object is equal to this fib
 * -object.
 * Variables can be others, but must be defined and used in equivalent
 * Fib elements.
 *
 * @param fibObject the Fib-object to which this Fib-object should be
 * 	equal
 * @param mapEqualRootObjects the root objects of this object that wher
 * 	already checked as equal
 * 	map entries:
 * 		key: the root-element of this Fib object that was checked
 * 		value: the to the key correspondending root-element of the
 * 			fibObject that was checked and which is equal to the key
 * 		root-element
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
 * @return true if this Fib-object is equal to the given Fib-object,
 * 	else false
 */
bool cRoot::equalInternal( const cFibElement & fibObject,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibObject.getType() ){
		return false;
	}
	if ( ! equalElementInternal( fibObject,
			mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
		return false;
	}
	cRoot *pRootElement = (cRoot*)(&fibObject);
	//compare the sub-root-objects
	if ( liSubRootObjects.size() != pRootElement->liSubRootObjects.size() ){
		return false;
	}
	list< pair< longFib, cRoot * > >::const_reverse_iterator itrActualRootElement2 =
		pRootElement->liSubRootObjects.rbegin();
	
	for ( list< pair< longFib, cRoot * > >::const_reverse_iterator itrActualRootElement =
				liSubRootObjects.rbegin();
			itrActualRootElement != liSubRootObjects.rend();
			itrActualRootElement++, itrActualRootElement2++ ){
		//identifiers where already compared with equalElementInternal()
		if ( ( itrActualRootElement->second == NULL ) ||
				( itrActualRootElement2->second == NULL ) ){
			if ( itrActualRootElement->second != itrActualRootElement2->second ){
				//one subroot NULL but not the other
				return false;
			}//both subroots NULL -> check next subroots
			continue;
		}//else no subroot NULL
		if ( ! itrActualRootElement->second->equalInternal(
				*(itrActualRootElement2->second),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			return false;
		}
		if ( bCheckExternalObjects ){
			mapEqualRootObjects.insert( make_pair( itrActualRootElement->second,
				itrActualRootElement2->second ) );
		}
	}//end for compare subroots
	//compare the main Fib object
	if ( ( pMainFibObject == NULL ) || ( pRootElement->pMainFibObject == NULL ) ){
		if ( pMainFibObject != pRootElement->pMainFibObject ){
			//not both main Fib objects NULL
			return false;
		}//else both main Fib objects NULL
	}else{
		if ( ! pMainFibObject->equalInternal( *(pRootElement->pMainFibObject),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			//main Fib objects not equal
			return false;
		}
	}
	
	return true;
}


/**
 * This method checks if the given Fib element is equal to this fib
 * -element.
 * The subobjects arn't compared, not even ther count is compared.
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
 * 		root-element
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
 * @return true if this Fib element is equal to the given Fib-object,
 * 	else false
 */
bool cRoot::equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cRoot *pRootElement = (cRoot*)(&fibElement);

	/*compare identifiers of the sub-root-objects 
	(the sub-root-objects are compared in the cFibBranch)*/
	if ( liSubRootObjects.size() != pRootElement->liSubRootObjects.size() ){
		return false;
	}
	list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement2 =
		pRootElement->liSubRootObjects.begin();
	
	for ( list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement =
				liSubRootObjects.begin();
			itrActualRootElement != liSubRootObjects.end() &&
			itrActualRootElement2 != pRootElement->liSubRootObjects.end();
			itrActualRootElement++ , itrActualRootElement2++ ){
		
		if ( itrActualRootElement->first != itrActualRootElement2->first ){
			return false;
		}
	}
	//compare the multimediainfo
	if ( ! (multimediaInfo == pRootElement->multimediaInfo) ){
		return false;
	}
	
	//compare the optionalpart
	if ( ! (optionalPart == pRootElement->optionalPart) ){
		return false;
	}

	//compare the domains
	if ( ! (domains == pRootElement->domains) ){
		return false;
	}

	//compare the value domains
	if ( ! (valueDomains == pRootElement->valueDomains) ){
		return false;
	}

	//compare the checksum
	if ( ( (pChecksum == NULL) || (pRootElement->pChecksum == NULL) ) &&
			(pChecksum != pRootElement->pChecksum) ){
		return false;
	}
	if ( pChecksum != NULL ){
		if ( ! (pChecksum->equalInternal( *(pRootElement->pChecksum),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ) ){
			return false;
		}
	}

	//compare the input variables
	if ( liInputVariables.size() != pRootElement->liInputVariables.size() ){
		return false;
	}
	list< pair< cFibVariable*, doubleFib > >::const_iterator
		itrActualVariable2 = pRootElement->liInputVariables.begin();
		
	for( list< pair< cFibVariable*, doubleFib > >::const_iterator
			itrActualVariable1 = liInputVariables.begin();
			itrActualVariable1 != liInputVariables.end() &&
			itrActualVariable2 != pRootElement->liInputVariables.end() ;
			itrActualVariable1++, itrActualVariable2++ ){
		//compare default values
		if ( itrActualVariable1->second != itrActualVariable2->second ){
			return false;
		}
	}

#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//compare the extern object numbers of output variables
	if ( liExternSubobjects != pRootElement->liExternSubobjects ){
		return false;
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	return true;
}


/**
 * This method checks if the given Fib element sets the variable to
 * the same values as this Fib element.
 *
 * @param pVariableOwn a pointer to a defined variable in this Fib element,
 * 	it is compared to the equivalent variable in the given Fib element
 * 	fibElement
 * @param fibElement the Fib element to which this Fib element should be
 * 	compared
 * @param pVariable a pointer to a defined variable in the other
 * 	Fib element fibElement
 * @param mapEqualRootObjects the root objects of this object that wher
 * 	already checked as equal
 * 	map entries:
 * 		key: the root-element of this Fib object that was checked
 * 		value: the to the key correspondending root-element of the
 * 			fibObject that was checked and which is equal to the key
 * 		root-element
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
 * 	values as given Fib element
 */
bool cRoot::equalValuesSetInternal( const cFibVariable * pVariableOwn,
		const cFibElement & fibElement,
		const cFibVariable * pVariable,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	if ( pVariableOwn == pVariable ){
		//same defined variable -> same values set
		return true;
	}
	if ( getType() != fibElement.getType() ){
		//not the same element type
		return false;
	}
	
	//get the number of the variable pVariableOwn in this root-element
	list< pair< cFibVariable *, doubleFib > >::const_iterator itrActualVariable;
	unsigned int uiPositionOwnVariable = 0;
	
	for( itrActualVariable = liInputVariables.begin();
			itrActualVariable != liInputVariables.end();
			itrActualVariable++ ){
		
		uiPositionOwnVariable++;
		if ( (itrActualVariable->first) == pVariableOwn ){
			break;
		}
	}
	if ( itrActualVariable == liInputVariables.end() ){
		//no variable to compare in this root-element
		return false;
	}

	//get the number of the variable pVariable in the other root-element fibElement
	unsigned int uiPositionOtherVariable = 0;
	cRoot * pOtherRootElement = (cRoot*) & fibElement;
	
	for( itrActualVariable = pOtherRootElement->liInputVariables.begin();
			itrActualVariable != pOtherRootElement->liInputVariables.end();
			itrActualVariable++ ){
		
		uiPositionOtherVariable++;
		if ( (itrActualVariable->first) == pVariable ){
			break;
		}
	}

	if ( itrActualVariable == liInputVariables.end() ){
		//no variable to compare to in the other root-element
		return false;
	}
	
	//the input variables on the same position are set to the same values
	return ( uiPositionOwnVariable == uiPositionOtherVariable );
}


#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib-object is equal to this Fib
 * -object.
 * Variables can be others, but must be defined and used in equivalent
 * Fib elements.
 *
 * @param fibObject the Fib-object to which this Fib-object should be
 * 	equal
 * @return true if this Fib-object is equal to the given Fib-object,
 * 	else false
 */
bool cRoot::equal( const cFibElement & fibObject ) const{

	if ( ! cFibBranch::equal( fibObject ) ){
		return false;
	}
	
	cRoot *pRootElement = (cRoot*)(&fibObject);
	
	//subobjects are compared with cFibBranch::equal()
	if ( ( (pMainFibObject == NULL) || (pRootElement->pMainFibObject == NULL ) ) &&
			(pMainFibObject != pRootElement->pMainFibObject) ){
		return false;
	}
	
	return equalElement( fibObject );
}


/**
 * This method checks if the given Fib element is equal to this fib
 * -element.
 * The subobjects arn't compared, not even ther count is compared.
 * Used variables can be others.
 *
 * @param fibElement the Fib element to which this Fib element should be
 * 	equal
 * @return true if this Fib element is equal to the given Fib-object,
 * 	else false
 */
bool cRoot::equalElement( const cFibElement & fibElement ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cRoot *pRootElement = (cRoot*)(&fibElement);

	/*compare identifiers of the sub-root-objects 
	(the sub-root-objects are compared in the cFibBranch)*/
	list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement2 =
		pRootElement->liSubRootObjects.begin();
	
	if ( liSubRootObjects.size() != pRootElement->liSubRootObjects.size() ){
		return false;
	}
	
	for ( list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement =
				liSubRootObjects.begin();
			itrActualRootElement != liSubRootObjects.end() &&
			itrActualRootElement2 != pRootElement->liSubRootObjects.end();
			itrActualRootElement++ , itrActualRootElement2++ ){
		
		if ( itrActualRootElement->first != itrActualRootElement2->first ){
			return false;
		}
	}
	//compare the multimediainfo
	if ( ! (multimediaInfo == pRootElement->multimediaInfo) ){
		return false;
	}
	
	//compare the optionalpart
	if ( ! (optionalPart == pRootElement->optionalPart) ){
		return false;
	}

	//compare the domains
	if ( ! (domains == pRootElement->domains) ){
		return false;
	}

	//compare the value domains
	if ( ! (valueDomains == pRootElement->valueDomains) ){
		return false;
	}

	//compare the checksum
	if ( ( (pChecksum == NULL) || (pRootElement->pChecksum == NULL) ) &&
			(pChecksum != pRootElement->pChecksum) ){
		return false;
	}
	if ( pChecksum != NULL ){
		if ( ! ((*pChecksum) == *(pRootElement->pChecksum)) ){
			return false;
		}
	}

	//compare the input variables
	if ( liInputVariables.size() != pRootElement->liInputVariables.size() ){
		return false;
	}
	list< pair< cFibVariable*, doubleFib > >::const_iterator
		itrActualVariable2 = pRootElement->liInputVariables.begin();
		
	for( list< pair< cFibVariable*, doubleFib > >::const_iterator
			itrActualVariable1 = liInputVariables.begin();
			itrActualVariable1 != liInputVariables.end() &&
			itrActualVariable2 != pRootElement->liInputVariables.end() ;
			itrActualVariable1++, itrActualVariable2++ ){
		//compare defaultvalues
		if ( itrActualVariable1->second != itrActualVariable2->second ){
			return false;
		}
	}

#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//compare the extern object numbers of output variables
	if ( liExternSubobjects != pRootElement->liExternSubobjects ){
		return false;
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	return true;
}



/**
 * This method checks if the given Fib element sets the variable to
 * the same values as this Fib element.
 *
 * @param variableOwn a pointer to a defined variable in this Fib element,
 * 	it is compared to the equivalent variable fibElement in the given
 * 	Fib element fibElement
 * @param fibElement the Fib element to which this Fib element should be
 * 	compared
 * @param variable a pointer to a defined variable in the other 
 * 	Fib element fibElement
 * @return true if this Fib element sets the variable to the same
 * 	values as this Fib element
 */
bool cRoot::equalValuesSet( const cFibVariable * variableOwn,
		const cFibElement & fibElement,
		const cFibVariable * variable ) const{
	
	if ( getType() != fibElement.getType() ){
		//not the same element type
		return false;
	}
	
	//get the number of the variable variableOwn in this root-element
	list< pair< cFibVariable *, doubleFib > >::const_iterator itrActualVariable;
	unsigned int uiPositionOwnVariable = 0;
	
	for( itrActualVariable = liInputVariables.begin();
			itrActualVariable != liInputVariables.end();
			itrActualVariable++ ){
		
		uiPositionOwnVariable++;
		if ( (itrActualVariable->first) == variableOwn ){
			break;
		}
	}
	if ( itrActualVariable == liInputVariables.end() ){
		//no variable to compare in this root-element
		return false;
	}

	//get the number of the variable variable in the other root-element fibElement
	unsigned int uiPositionOtherVariable = 0;
	cRoot * pOtherRootElement = (cRoot*) & fibElement;
	
	for( itrActualVariable = pOtherRootElement->liInputVariables.begin();
			itrActualVariable != pOtherRootElement->liInputVariables.end();
			itrActualVariable++ ){
		
		uiPositionOtherVariable++;
		if ( (itrActualVariable->first) == variable ){
			break;
		}
	}

	if ( itrActualVariable == liInputVariables.end() ){
		//no variable to compare to in the other root-element
		return false;
	}
	
	//the input variables on the same position are set to the same values
	return ( uiPositionOwnVariable == uiPositionOtherVariable );
}

#endif //FEATURE_EQUAL_FIB_OBJECT


/**
 * This method stores this Fib-object in the XML -format into the
 * given stream.
 *
 * @param stream the stream where this Fib-object should be stored to
 * @return true if this Fib-object is stored, else false
 */
bool cRoot::storeXml( ostream & stream ) const{

	//check if the Fib-object is correct
	
	if ( pMainFibObject == NULL ){
		//no main -Fib-object -> incorrect Fib-object
		return false;
	}
	if ( pSuperiorElement == NULL ){
		//check wool Fib-object
#ifndef TEST
		if ( ! hasUnderAllObjects() ){
			return false;
		}
#endif //not TEST
		//TODO: use isValidObject() when it is implemented
	}
	
	//store the variables values
	(const_cast<cRoot*>(this))->backupVariablesValues( true );
	unsignedIntFib uiVariablenCount = 0;
	
	//set the variables values to ther number
	for ( list< pair< cFibVariable *, doubleFib > >::iterator
			itrActualVariable = (const_cast<cRoot*>(this))->liInputVariables.begin();
			itrActualVariable != (const_cast<cRoot*>(this))->liInputVariables.end();
			itrActualVariable++ ){
		
		uiVariablenCount++;
		itrActualVariable->first->setIntegerValue( (longFib)(uiVariablenCount) );
	}
	
	//counting variables in the main -Fib-object and creating a variables domain
	if ( pMainFibObject ){
		uiVariablenCount = const_cast<cFibElement*>(pMainFibObject)->
			enumerateVariablesForStoring( uiVariablenCount );
	}
	
	//store the fib object
	
	//write the stream/file header
	if ( pSuperiorElement == NULL ){
		/*this is the topmost element in the stream
		-> write the header*/
		stream<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl;
		stream<<"<fib_object"<<endl;
		stream<<"xmlns:xsd=\"http://www.w3.org/2001/XMLSchema-instance\""<<endl;
		stream<<"xmlns=\"http://www.biokom.info/\""<<endl;
		stream<<"xsd:schemaLocation=\"http://www.biokom.info/fib.xsd\">"<<endl;
	}
	//write the root object
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<root elementNr=\""<<getNumberOfElement()<<"\" >"<<endl;
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<root>"<<endl;
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	
	//write the multimediainfo
	if ( pSuperiorElement != NULL ){
		/*if the multimediainfo of this root-element differs to the
		multimediainfo of the supierior root-element the multimediainfo
		have to be be written*/
		if ( ! ( multimediaInfo ==
				(((cRoot*)(pSuperiorElement))->multimediaInfo) ) ){
			
			bool bMultimediainfoStored = multimediaInfo.storeXml( stream );
			if ( ! bMultimediainfoStored ){
				//restore the values of the variables
				(const_cast<cRoot*>(this))->backupVariablesValues( false );
				return false;
			}
		}
	}

	//write optionalpart
	if ( optionalPart.getNumberOfEntries() != 0 ){

		bool bOptionalPartStored = optionalPart.storeXml( stream );
		if ( ! bOptionalPartStored ){
			//restore the values of the variables
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			return false;
		}

	}
	//write domains
	if ( domains.getNumberOfDomains() != 0 ){
	
		bool bDomainsStored = domains.storeXml( stream );
		if ( ! bDomainsStored ){
			//restore the values of the variables
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			return false;
		}
	}
	
	//write value domains
	if  ( valueDomains.getNumberOfDomains() != 0 ){
	
		bool bValueDomainsStored = valueDomains.storeXml( stream, "valueDomains" );
		if ( ! bValueDomainsStored ){
			//restore the values of the variables
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			return false;
		}
	}
	
	//write inputvariables
	if ( getNumberOfInputVariables() > 0 ){
	
		stream<<"<input_variables>"<<endl;
		for( unsignedIntFib uiNumberOfInputVariable = 1;
			uiNumberOfInputVariable <= getNumberOfInputVariables();
			uiNumberOfInputVariable++ ){
		
			stream<<"<variable number=\""<< uiNumberOfInputVariable <<"\" ";
			stream<<"default=\""<< getStandardValueOfInputVariable(
				uiNumberOfInputVariable ) <<"\"/>"<<endl;
		}
		stream<<"</input_variables>"<<endl;
	}
	
#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//write output variables
	if ( getNumberOfExternSubobjects() > 0 ){
	
		stream<<"<output_variables>"<<endl;
		for( unsignedIntFib uiNumberOfOutputVariable = 1;
			uiNumberOfOutputVariable <= getNumberOfExternSubobjects();
			uiNumberOfOutputVariable++ ){
		
			stream<<"<object number=\""<< uiNumberOfOutputVariable <<"\" ";
			stream<<"variable_count=\""<< getNumberOfOutputVariables(
				uiNumberOfOutputVariable ) <<"\"/>"<<endl;
		}
		stream<<"</output_variables>"<<endl;
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	//write the main -Fib-object
	if ( pMainFibObject ){
		stream<<"<main_fib_object>"<<endl;
		bool bMainFibObjectStored = pMainFibObject->storeXml( stream );
		if ( ! bMainFibObjectStored ){
			//restore the values of the variables
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			return false;
		}
		stream<<"</main_fib_object>"<<endl;
	}
	
	//write the sub-root-objects if existing
	if ( getNumberOfSubRootObjects() > 0 ){
		stream<<"<sub_roots>"<<endl;
	
		for ( unsignedIntFib uiActualSubRootObject = 1;
				uiActualSubRootObject <= getNumberOfSubRootObjects();
				uiActualSubRootObject++ ){
			
			pair<longFib, cRoot*> paActualSubRootObject =
				(const_cast<cRoot*>(this))->getSubRootObject( uiActualSubRootObject );
			
			if ( paActualSubRootObject.second == NULL ){
				//no sub root object
				//restore the values of the variables
				(const_cast<cRoot*>(this))->backupVariablesValues( false );
				return false;
			}
			
			stream<<"<sub_root identifier=\""<< paActualSubRootObject.first <<"\">"<<endl;
			
			bool bSubRootObjectStored = (paActualSubRootObject.second)->storeXml( stream );
			if ( ! bSubRootObjectStored ){
				//restore the values of the variables
				(const_cast<cRoot*>(this))->backupVariablesValues( false );
				return false;
			}
			stream<<"</sub_root>"<<endl;
		}
		stream<<"</sub_roots>"<<endl;
	}
	
	//store Fib-database identifiers
	if ( ! setDatabaseIdentifiers.empty() ){
		stream<<"<database_identifiers>"<<endl;
	
		for ( set< longFib >::const_iterator
				itrDbIdentifier = setDatabaseIdentifiers.begin();
				itrDbIdentifier != setDatabaseIdentifiers.end(); itrDbIdentifier++ ){
			
			stream<<"<identifier>"<<(*itrDbIdentifier)<<"</identifier>"<<endl;
		}
		stream<<"</database_identifiers>"<<endl;
	}
	
	/*write the checksumfield if it exsists*/
	if ( pChecksum ){
		//an checksumfield exsists
		bool bChecksumStored = pChecksum->storeXml( stream );
		if ( ! bChecksumStored ){
			//restore the values of the variables
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			return false;
		}
	}
	
	stream<<"</root>"<<endl;
	
	if ( pSuperiorElement == NULL ){
		/*this is the topmost element in the stream
		-> close the header*/
		stream<<"</fib_object>"<<endl;
	}
	//restore the values of the variables
	(const_cast<cRoot*>(this))->backupVariablesValues( false );
	return true;
}



/**
 * This method inserts the given Fib element fibElement on the
 * specified position. The replaced Fib element will be the subobject
 * of the inserted Fib element fibElement.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getType()
 * @param cType the type of the Fib element insted of which the given
 * 	Fib element fibElement should be inserted
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, in which position the given
 * 	Fib element fibElement should be inserted; if 0 the given
 * 	fibElement will be inserted under this Fib element
 * @param fibElement the Fib element to insert
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib-object
 * @param bCheckVariables if true (standardvalue) it will be checked if
 * 	the variables the Fib element defines are needed, else the 
 * 	Fib element will be removed even if its variables are needed elsewher
 * @return true if the Fib element fibElement was inserted, else false
 */
bool cRoot::insertElement( cFibElement *fibElement, const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute,
		bool bCheckVariables ){
		
	const bool bObjectChanged = cFibBranch::insertElement(
		fibElement, cType, elementPoint, bAbsolute, bCheckVariables );
	
	if ( bObjectChanged ){
		syncSubobjects();
	}
	return bObjectChanged;
}


/**
 * This method inserts the given Fib-object fibObject on the
 * specified position. On the specified position a listelement will
 * be inserted, with the old Fib-object and the given Fib-object
 * fibObject as its subobjects.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see overwriteObjectWithObject()
 * @see getType()
 * @param cType the type of the Fib element, on which position the 
 * 	given Fib-object fibObject should be inserted
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, on which position the given
 * 	Fib-object fibObject should be inserted
 * @param fibObject the Fib-object to insert
 * @param first if true, the inserted object will be the first
 * 	subobject of the new listelement
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib-object
 * @return true if the Fib-object fibObject was inserted, else false
 */
bool cRoot::insertObjectInElement( cFibElement *fibObject, const char cType,
		const unsignedIntFib elementPoint, bool first,
		bool bAbsolute ){
	
	if ( fibObject == NULL ){
		//nothing to insert
		return false;
	}
	if ( fibObject->getType() == 'r' ){
		//can't insert a root-element
		return false;
	}
#ifdef FEATURE_FAST_UPDATE
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return false;
	}
#endif //FEATURE_FAST_UPDATE
	if (elementPoint == 0){
		if ( fibUnderObjects.empty() ){
			//insert in this root-element
			if ( fibObject->pSuperiorElement != NULL ){
				fibObject->pSuperiorElement->cutConnectionsTo(
					fibObject );
			}
			fibObject->pSuperiorElement = this;
			
			fibUnderObjects.push_front( fibObject );
#ifdef FEATURE_FAST_UPDATE
			cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( fibObject );
			fibObjectCountsDelta.uiNumberOfObjectpoints++;
			updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
			updateAllValues();
#endif //FEATURE_FAST_UPDATE
			syncSubobjects();
			//done with inserting
			return true;
		}//else
		if (fibUnderObjects.front() == NULL){
		
			if ( fibObject->pSuperiorElement != NULL ){
				fibObject->pSuperiorElement->cutConnectionsTo(
					fibObject );
			}
			fibObject->pSuperiorElement = this;
			
			fibUnderObjects.front() = fibObject;
			
#ifdef FEATURE_FAST_UPDATE
			cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( fibObject );
			fibObjectCountsDelta.uiNumberOfObjectpoints++;
			updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
			updateAllValues();
#endif //FEATURE_FAST_UPDATE
			syncSubobjects();
			return true;
		}//else
		return insertObjectInElement( fibObject, 'u', 2, first );
	}
	
	if ( bAbsolute ){
		bool bObjectChanged = getMasterRoot()->insertObjectInElement(
			fibObject, cType, elementPoint, first );
		if ( bObjectChanged ){
			syncSubobjects();
		}
		return bObjectChanged;
	}//else elementPoint is an relative value

	cFibElement * pFibElementPosition = getFibElement( cType, elementPoint );
	if ( (pFibElementPosition == NULL) || (pFibElementPosition->getType() == 'r') ){
		//no position to insert
		return false;
	}
	if ( fibUnderObjects.front() != NULL ){
#ifdef FEATURE_FAST_UPDATE
		if ( fibUnderObjects.front() == pFibElementPosition ){
			
			if ( fibObject->pSuperiorElement != NULL ){
				fibObject->pSuperiorElement->cutConnectionsTo(
					fibObject );
			}
			pFibElementPosition->pSuperiorElement = NULL;
#else //FEATURE_FAST_UPDATE
		if ( fibUnderObjects.front()->getNumberOfElement() ==
				pFibElementPosition->getNumberOfElement() ){
#endif //FEATURE_FAST_UPDATE
			//insert as main -Fib-object
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
			if( first ){
				fibUnderObjects.front() = new cList( fibObject, pFibElementPosition );
			}else{
				fibUnderObjects.front() = new cList( pFibElementPosition, fibObject );
			}
#else //FEATURE_SIMPLE_CONSTRUCTOR
			if( first ){
				fibUnderObjects.front() = new cList( fibObject, pFibElementPosition, this, this );
			}else{
				fibUnderObjects.front() = new cList( pFibElementPosition, fibObject, this, this );
			}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
#ifdef FEATURE_FAST_UPDATE
			//set superior Fib element
			fibUnderObjects.front()->pSuperiorElement = this;
			pFibElementPosition->pSuperiorElement = fibUnderObjects.front();
			fibObject->pSuperiorElement = fibUnderObjects.front();
			
			//update counters
			cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( fibObject );
			fibObjectCountsDelta.vecNumberOfFibElements[ cFibObjectCounts::LIST ]++;
			fibObjectCountsDelta.vecNumberOfFibElements[ cFibObjectCounts::ALL ]++;
			fibObjectCountsDelta.uiNumberOfObjectpoints += 2;
			updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
			updateAllValues();
#endif //FEATURE_FAST_UPDATE
			syncSubobjects();
			return true;
		}
	}
	
	bool bObjectChanged = cFibBranch::insertObjectInElement( fibObject, cType,
		elementPoint, first );
	
	if ( bObjectChanged ){
		syncSubobjects();
	}
	return bObjectChanged;
}


/**
 * This method overwrites the Fib-object on specified position with
 * the given Fib-object fibObject. The Fib-object on specified
 * position will be replaced with the given Fib-object fibObject.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see insertObjectInElement()
 * @see getType()
 * @param cType the type of the Fib element, on which position the 
 * 	given Fib-object fibObject should be inserted
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, on which position the given
 * 	Fib-object fibObject should be inserted
 * @param fibObject the Fib-object to insert
 * @param bDeleteOld if true, delete the old Fib-object from the memory
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib-object
 * @return true if the old Fib-object was overwritten and the given 
 * 	Fib-object fibObject was inserted, else false
 */
bool cRoot::overwriteObjectWithObject( cFibElement *fibObject, const char cType,
		const unsignedIntFib elementPoint, bool bDeleteOld,
		bool bAbsolute ){
	
	if ( fibObject == NULL ){
		//nothing to insert
		return false;
	}
	if ( fibObject->getType() == 'r' ){
		//can't insert a root-element
		return false;
	}
#ifdef FEATURE_FAST_UPDATE
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return false;
	}
#endif //FEATURE_FAST_UPDATE
	if (elementPoint == 0){
		if ( fibUnderObjects.empty() ){
			//insert in this root-element
#ifdef FEATURE_FAST_UPDATE
			if ( fibObject->pSuperiorElement != NULL ){
				fibObject->pSuperiorElement->cutConnectionsTo(
					fibObject );
			}
			fibObject->pSuperiorElement = this;
			fibUnderObjects.push_front( fibObject );
			
			cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( fibObject );
			fibObjectCountsDelta.uiNumberOfObjectpoints++;
			updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
			fibObject->pSuperiorElement = this;
			fibUnderObjects.push_front( fibObject );
			updateAllValues();
#endif //FEATURE_FAST_UPDATE
			syncSubobjects();
			//done with inserting
			return true;
		}//else
		if (fibUnderObjects.front() == NULL){
		
#ifdef FEATURE_FAST_UPDATE
			if ( fibObject->pSuperiorElement != NULL ){
				fibObject->pSuperiorElement->cutConnectionsTo(
					fibObject );
			}
#endif //FEATURE_FAST_UPDATE
			
			fibObject->pSuperiorElement = this;
			fibUnderObjects.front() = fibObject;
			
			updateAllValues();
			syncSubobjects();
			return true;
		}//else
		return overwriteObjectWithObject( fibObject, 'u', 2, bDeleteOld );
	}
	if ( bAbsolute ){
		return getMasterRoot()->overwriteObjectWithObject( fibObject, cType,
			elementPoint, bDeleteOld );
	}//else elementPoint is an relative value

	cFibElement * pFibElementPosition = getFibElement( cType, elementPoint );
	if ( (pFibElementPosition == NULL) || (pFibElementPosition->getType() == 'r') ){
		//no position to insert
		return false;
	}
	if ( fibUnderObjects.front() != NULL ){
		if ( fibUnderObjects.front()->getNumberOfElement() ==
				pFibElementPosition->getNumberOfElement() ){
			//overwrite the main -Fib-object
			//set the values of the fibObject
			fibObject->pSuperiorElement = this;
					
#ifdef FEATURE_FAST_UPDATE
			if ( fibObject->pSuperiorElement != NULL ){
				fibObject->pSuperiorElement->cutConnectionsTo(
					fibObject );
			}
			fibObject->pSuperiorElement = this;
			//insert fibObject instead of the actualUnderObject
			fibUnderObjects.front() = fibObject;
			
			//update the Fib-objectcounters
			cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( fibObject );
			const cFibObjectCounts fibObjectCountsOld =
				evalueCountersForObject( pFibElementPosition );
			fibObjectCountsDelta -= fibObjectCountsOld;
			updateAllCounters( fibObjectCountsDelta );
			
			if ( pFibElementPosition->pSuperiorElement == this ){
				pFibElementPosition->pSuperiorElement = NULL;
				if ( bDeleteOld ){
					pFibElementPosition->deleteObject();
				}//else don't delete
			}
#else //FEATURE_FAST_UPDATE
			fibObject->pSuperiorElement = this;
			fibObject->pPreviousFibElement =
				pFibElementPosition->pPreviousFibElement;
			
			//insert fibObject instead of the actualUnderObject
			fibUnderObjects.front() = fibObject;
			
			//remove connections of pOldFibObject to this Fib-object
			cFibElement * pLastFibElementInOld = pFibElementPosition->getFibElement(
					pFibElementPosition->getNumberOfElements() );
			if ( pLastFibElementInOld == NULL ){
				pLastFibElementInOld = pFibElementPosition;
			}
			if ( pFibElementPosition->pPreviousFibElement ){
				pFibElementPosition->pPreviousFibElement->pNextFibElement =
					fibObject;
			}
			if ( pLastFibElementInOld->pNextFibElement ){
				pLastFibElementInOld->pNextFibElement->pPreviousFibElement = NULL;
			}
			pFibElementPosition->cutConnections( ED_HIGHER );
			pLastFibElementInOld->cutConnections( ED_BELOW );
			if ( bDeleteOld ){
				cFibElement::deleteObject( pFibElementPosition );
			}//else don't delete
			updateAllValues();
#endif //FEATURE_FAST_UPDATE
					
			syncSubobjects();
			return true;
		}
	}
	
	bool bObjectChanged = cFibBranch::overwriteObjectWithObject( fibObject, cType,
		elementPoint, bDeleteOld );
	
	if ( bObjectChanged ){
		syncSubobjects();
	}
	return bObjectChanged;
}


/**
 * This method cuts the Fib element on the specified position.
 * This works like removeElement(), except that the removed element is 
 * returned.
 *
 * @see isDeletableElement()
 * @see removeElement()
 * @see getType()
 * @param cType the type of the Fib element to cut
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, to cut
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib-object
 * @param bCheckVariables if true (standardvalue) it will be checked if
 * 	the variables the Fib element defines are needed, else the 
 * 	Fib element will be removed even if its variables are needed elsewher
 * @return the pointer to the cuted Fib element or NULL, if the Fib
 * 	-element couldn't cut
 */
cFibElement * cRoot::cutElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute, bool bCheckVariables ){
	
	cFibElement * pCutedElement =
		cFibBranch::cutElement( cType, elementPoint, bAbsolute, bCheckVariables );
	
	if ( pCutedElement ){
		syncSubobjects();
	}
	return pCutedElement;
}


/**
 * This method moves a Fib-limb -element (cFibLimb) on the specified
 * position over iHowfar Fib elements.
 * Moving is stoped if an invalid Fib-object would result (e.g. no Fib
 * -element can be moved over an Fib elements that defines a variable
 * the moved Fib element uses).
 * Moving an Fib element into an listelement will result in an
 * listelement with the moved element in everyone of it's subobjects.
 *
 * @see isDeletableElement()
 * @see removeElement()
 * @see getType()
 * @param cType the type of the Fib element to move
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, to move
 * @param iHowfar the number of Fib elements over which the to move
 * 	Fib element should be moved; if this value is positiv the Fib
 * 	-element will be moved over Fib elements it contains else over
 * 	Fib elements it is contained in
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib-object
 * @return the number of Fib-Elements over which the to move Fib
 * 	-element was moved; if this value is positiv the Fib element
 * 	was moved over Fib elements it contains else over Fib elements
 * 	it is contained in
 */
intFib cRoot::moveLimbElement( const char cType, const
		unsignedIntFib elementPoint, const intFib iHowfar, bool bAbsolute ){
	
	intFib iElementsMoved = cFibBranch::moveLimbElement( cType, elementPoint,
		iHowfar, bAbsolute );
	
	if ( iElementsMoved ){
		syncSubobjects();
	}
	return iElementsMoved;
}


/**
 * @see szDatabasePath
 * @return a string to the actual set database path, the string is empty
 * 	if no database path is set
 */
std::string cRoot::getDatabasePath(){
	
	if ( pFibDatabase == NULL ){
		//no database instance -> create one
		pFibDatabase = cFibDatabase::getInstance();
	}
	return pFibDatabase->getDatabasePath();
}


/**
 * This function sets the Fib database path to the given path if possible.
 *
 * @see szDatabasePath
 * @param szInDatabasePath the path to the folder with the Fib database
 * 	objects
 * @return true if the given Fib database path exists and was set, else
 * 	false and the database path is not changed
 */
bool cRoot::setDatabasePath( const char * szInDatabasePath ){
	
	if ( pFibDatabase == NULL ){
		//no database instance -> create one
		pFibDatabase = cFibDatabase::getInstance();
	}
	return pFibDatabase->setDatabasePath( szInDatabasePath );
}


/**
 * This function sets the Fib database path to the given path if posible.
 *
 * @see szDatabasePath
 * @param szInDatabasePath the path to the folder with the Fib database
 * 	objects
 * @return true if the given Fib database path exists and was set, else
 * 	false and the database path is not changed
 */
bool cRoot::setDatabasePath( const string szInDatabasePath ){
	
	if ( pFibDatabase == NULL ){
		//no database instance -> create one
		pFibDatabase = cFibDatabase::getInstance();
	}
	return pFibDatabase->setDatabasePath( szInDatabasePath );
}


/**
 * This method returns the identifiers of all root-objects of this
 * object.
 *
 * @return the identifiers of all root-objects of this object
 */
list<longFib> cRoot::getAllRootObjectIdentifiers() const{
	/*go to the most top/ superior root-element and get all identifiers
	in the direction down*/
	cFibElement * pMasterElement = getMasterRoot();
	if ( pMasterElement->getType() != 'r' ){
		pMasterElement = pMasterElement->getNextFibElement( 'r' );
		if ( pMasterElement == NULL ){
			return list<longFib>();
		}
	}
	list<longFib> liIdentifiers = ((cRoot*)pMasterElement)->getAllDownRootObjectIdentifiers();
	
	//add database identifiers
	list<longFib> liDatabaseIdentifiers = getAllDatabaseObjectIdentifiers();
	liIdentifiers.insert( liIdentifiers.end(),
		liDatabaseIdentifiers.begin(), liDatabaseIdentifiers.end() );
	
	return liIdentifiers;
}


/**
 * This method returns the identifiers of all database -objects, in the
 * actual database.
 *
 * @return the identifiers of all database -objects
 */
list<longFib> cRoot::getAllDatabaseObjectIdentifiers() const{
	
	if ( pFibDatabase == NULL ){
		//no database instance -> create one
		pFibDatabase = cFibDatabase::getInstance();
	}
	//return database identifiers
	return pFibDatabase->getAllDatabaseObjectIdentifiers();
}


/**
 * This method returns the root-object for the given identifier.
 * If non such exists the Nullpoint NULL is returned.
 *
 * @param lIdentifier the identifier of the root-object to return
 * @return the root-object for the given identifier or NULL if non
 * 	such exists
 */
cRoot * cRoot::getRootObject( longFib lIdentifier ){
	//search the accessible root-objects
	cRoot * pAccessibleRootObject = getAccessibleRootObject( lIdentifier );
	if ( pAccessibleRootObject ){
		return pAccessibleRootObject;
	}
	
	//search all root-objects from the topmost down
	cFibElement * pMasterElement = getMasterRoot();
	if ( pMasterElement->getType() != 'r' ){
		pMasterElement = pMasterElement->getNextFibElement( 'r' );
		if ( pMasterElement == NULL ){
			return NULL;
		}
	}
	cRoot * pRootObject = ((cRoot*)pMasterElement)->getRootObjectDown( lIdentifier );
	if ( pRootObject ){
		return pRootObject;
	}
	if ( pFibDatabase == NULL ){
		//no database instance -> create one
		pFibDatabase = cFibDatabase::getInstance();
	}
	//search database root-objects
	return pFibDatabase->getFibObject( lIdentifier );
}


/**
 * This method returns the identifiers of all from this Fib element
 * accessible root-objects of this object.
 *
 * @return the identifiers of all accessible root-objects
 */
list<longFib> cRoot::getAllAccessibleRootObjectIdentifiers() const{
	//add the identifiers of this root-element
	return getAllAccessibleRootObjectIdentifiers( this );
}


/**
 * This method returns the from this Fib element accessible root
 * -object for the given identifier. If non such exists the Nullpoint 
 * NULL is returned.
 *
 * @param lIdentifier the identifier of the root-object to return
 * @return the accessible root-object for the given identifier or NULL
 * 	if non such exists
 */
cRoot * cRoot::getAccessibleRootObject( longFib lIdentifier ){
	//search the sub-root-objetcs in this root-element

	return getAccessibleRootObject( lIdentifier, this );
}


/**
 * This method returns the domains that are valid for this Fib element.
 *
 * @return the domains that are valid for this Fib element
 */
cDomains cRoot::getValidDomains() const{
	
	return getValidDomains( false );
}


/**
 * This method returns the domains that are valid for this Fib element.
 *
 * @param bInherit if true just inherited domains of this root element will
 * 	be returned else if false all domains will be returned
 * @return the domains that are valid for this Fib element
 */
cDomains cRoot::getValidDomains( const bool bInherit ) const{

	cDomains validDomains;
	//add the domains of super/ higher root-elements
	if ( (pSuperiorElement != NULL) && (pSuperiorElement->getType() == 'r') ){
		validDomains = ((cRoot*)pSuperiorElement)->getValidDomains( true );
	}
	
	/*add domains in this root-element and overwrite with them domains
	for the same type of higher root-elements*/
	const unsignedIntFib uiNumberOfDomains =
		domains.getNumberOfDomains();
	if ( bInherit ){
		//check inheritance
		for ( unsignedIntFib uiActualDomain = 1;
				uiActualDomain <= uiNumberOfDomains;
				uiActualDomain++ ){
			
			const cTypeElement * pTypeElement =
				domains.getType( uiActualDomain );
			
			if ( pTypeElement->isInherited() ){
				//domain is inherited -> add it
				validDomains.addDomain( *pTypeElement,
					domains.getDomain( uiActualDomain ) );
			}
		}
	}else{//don't check inheritance
		for ( unsigned int uiActualDomain = 1;
				uiActualDomain <= uiNumberOfDomains;
				uiActualDomain++ ){
			
			validDomains.addDomain( *(domains.getType( uiActualDomain )),
				domains.getDomain( uiActualDomain ) );
		}
	}
	
	return validDomains;
}


/**
 * This method returns the value domains that are valid for this
 * Fib element.
 * Just value domains are returned.
 *
 * @see getValidValueDomains()
 * @see getValidDomains()
 * @param bInherit if true just inherited domains of this root element will
 * 	be returned else if false all domains will be returned
 * @return the value domains that are valid for this Fib element
 */
cDomains cRoot::getValidPureValueDomains( const bool bInherit ) const{

	cDomains validValueDomains;
	//add the domains of super/ higher root-elements
	if ( (pSuperiorElement != NULL) && (pSuperiorElement->getType() == 'r') ){
		validValueDomains =
			((cRoot*)pSuperiorElement)->getValidPureValueDomains( true );
	}
	/*add value domains of this root-element and overwrite with them
	domains for the same type of higher root-elements*/
	const unsignedIntFib uiNumberOfDomains =
		valueDomains.getNumberOfDomains();
	if ( bInherit ){
		//check inheritance
		for ( unsigned int uiActualDomain = 1;
				uiActualDomain <= uiNumberOfDomains;
				uiActualDomain++ ){
			
			const cTypeElement * pTypeElement =
				valueDomains.getType( uiActualDomain );
			
			if ( pTypeElement->isInherited() ){
				//domain is inherited -> add it
				validValueDomains.addDomain( *(pTypeElement),
					valueDomains.getDomain( uiActualDomain ) );
			}
		}
	}else{//don't check inheritance
		for ( unsigned int uiActualDomain = 1;
				uiActualDomain <= uiNumberOfDomains;
				uiActualDomain++ ){
			
			validValueDomains.addDomain( *(valueDomains.getType( uiActualDomain )),
				valueDomains.getDomain( uiActualDomain ) );
		}
	}
	return validValueDomains;
}


/**
 * This method returns the domains for value that are valid for this
 * Fib element.
 * Missing value domains are added from the (non value) domains.
 *
 * @see getValidPureValueDomains()
 * @see getValidDomains()
 * @return the value domains that are valid for this Fib element
 */
cDomains cRoot::getValidValueDomains() const{

	cDomains validValueDomains = getValidPureValueDomains();
	
	//add the domains which are missing in the pure value domains
	cDomains allDomains = getValidDomains();
	for ( unsigned int uiActualDomain = 1;
			uiActualDomain <= allDomains.getNumberOfDomains();
			uiActualDomain++ ){
		
		if ( validValueDomains.getDomainForElement(
				*(allDomains.getType( uiActualDomain ) ) ) == NULL ){
			//this value domain is missing
			validValueDomains.addDomain( *(allDomains.getType( uiActualDomain ) ),
				allDomains.getDomain( uiActualDomain ) );
		}
	}
	return validValueDomains;
}


/**
 * This method returns the number of dimensions in this
 * Fib-Multimediaobject.
 *
 * @return the number of dimensions in
 */
unsignedIntFib cRoot::getNumberOfDimensions() const{

	for ( unsigned int uiActualDomain = 1;
			uiActualDomain <= domains.getNumberOfDomains(); uiActualDomain++ ){
		if ( domains.getType( uiActualDomain )->getType() == 1 ){
			//this is an dimension type
			cTypeDimension * dimensionType = (cTypeDimension*)(domains.
				getType( uiActualDomain ));
			return dimensionType->getNumberOfDimensions();
		}
	}
	//search for the number of dimensions in super/ higher root-elements
	if ( pSuperiorElement != NULL ){
		return pSuperiorElement->getNumberOfDimensions();
	}
	//return default number of dimensions
	cTypeDimension typeDimension;
	return typeDimension.getNumberOfDimensions();
}


/**
 * This method returns in which direction the iDimensionNumber dimension
 * is mapped.
 *
 * @param iDimensionNumber the number of the dimension for which the
 * 	mapping is to be returned
 * @return the direction in which the iDimensionNumber dimension is
 * 	mapped
 */
unsignedIntFib cRoot::getDimensionMapping( unsignedIntFib iDimensionNumber ) const{

	for ( unsigned int uiActualDomain = 1;
			uiActualDomain <= domains.getNumberOfDomains(); uiActualDomain++ ){
		if ( domains.getType( uiActualDomain )->getType() == 1 ){
			//this is an dimension type
			cTypeDimension * dimensionType = (cTypeDimension*)(domains.
				getType( uiActualDomain ));
			return dimensionType->getDimensionMapping( iDimensionNumber );
		}
	}
	//search for the number of dimensions in super/ higher root-elements
	if ( pSuperiorElement != NULL ){
		return pSuperiorElement->getDimensionMapping( iDimensionNumber );
	}
	//return default dimension mapping
	cTypeDimension typeDimension;
	return typeDimension.getDimensionMapping( iDimensionNumber );
}


/*
 * Root -element methods
 */

/**
 * This method sets the main -Fib-object to the given pInMainFibObject.
 *
 * @param pInMainFibObject a pointer to the main -Fib-object to set
 * @return true if the main -Fib-object is set to pInMainFibObject, else false
 */
bool cRoot::setMainFibObject( cFibElement * pInMainFibObject ){
	
	if ( pInMainFibObject == NULL ){
		return false;
	}
	if (  pInMainFibObject->getType() == 'r' ){
		//a root-element can't be the main fib object
		return false;
	}
#ifdef FEATURE_FAST_UPDATE
	if ( pInMainFibObject->pSuperiorElement != NULL ){
		pInMainFibObject->pSuperiorElement->cutConnectionsTo(
			pInMainFibObject );
	}
	pInMainFibObject->pSuperiorElement = this;
	
	cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( pInMainFibObject );
	if ( pMainFibObject == NULL ){
		fibObjectCountsDelta.uiNumberOfObjectpoints++;
	}
	const cFibObjectCounts fibObjectCountsOld =
		evalueCountersForObject( pMainFibObject );
	fibObjectCountsDelta -= fibObjectCountsOld;
#endif //FEATURE_FAST_UPDATE
	
	pMainFibObject = pInMainFibObject;
	if ( ! fibUnderObjects.empty() ){
		fibUnderObjects.front() = pInMainFibObject;
	}else{//fibUnderObjects is empty
		fibUnderObjects.push_back( pInMainFibObject );
	}
#ifdef FEATURE_FAST_UPDATE
	updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
	updateAllValues();
#endif //FEATURE_FAST_UPDATE
	return true;
}


/**
 * @return a pointer to the multimediainfo of this root-element
 */
cMultimediaInfo * cRoot::getMultimediaInfo(){
	return & multimediaInfo;
}


/**
 * @return a pointer to the optionalpart of this root-element or
 * 	NULL if non such exists.
 */
cOptionalPart * cRoot::getOptionalPart(){
	return & optionalPart;
}


/**
 * @return a pointer to the domains of this root-element
 */
cDomains * cRoot::getDomains(){
	return & domains;
}


/**
 * @return a pointer to the compressed/ value domains of this
 * 	root-element
 */
cDomains * cRoot::getValueDomains(){
	return & valueDomains;
}


/**
 * This method generates all domains, wich are needed to store this
 * Fib-object.
 * Most generated domains are added as value domains of this root-element.
 *
 * the generated domains are for the typs:
 * 	- cTypeArea
 * 	- cTypeUnderFunction
 * 	- cTypeExtObject
 * 	- cTypeExtSubobject (added as domains if wrong exists)
 * 	- cTypeFibSet
 * 	- cTypeFibMatrix
 * 
 * @param bAddAllValueDomains if true all domains, which are added as value
 * 	domains, are added without checking if they are needed
 */
void cRoot::generateNeededDomains( const bool bAddAllValueDomains ){
	
	DEBUG_OUT_L2(<<"cRoot("<<this<<")::generateNeededDomains() started"<<endl<<flush);
	
	if ( pMainFibObject == NULL ){
		DEBUG_OUT_L2(<<"cRoot("<<this<<")::generateNeededDomains() done no main Fib object -> no domains needed"<<endl<<flush);
		return;
	}
	
	list< doubleFib > liValuesInFunctions;
	//domain for area elements
		//counter subareas
	list< longFib > liValuesInCountSubareas;
		//domain subarea
	list< longFib > liValuesInAreasLower;
	list< longFib > liValuesInAreasUpper;
	
	//extern object element
	list< longFib > liValuesInExtObjIdentifier;
	list< longFib > liValuesInExtObjCountInVars;
	list< longFib > liValuesInExtObjCountSubobj;
	list< longFib > liValuesInExtObjCountOutVars;
		//external object input values
	map< longFib, list< cFibVector * > > mapExtObjectInputVectors;
	
	//extern subobject element
	list< longFib > liValuesInExtSubobjCountOutVars;
	/*evalue and correct output variable counts for the subobjects*/
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	map< unsignedLongFib, list< cFibVector * > > mapExtSubobjectOutputVectors;
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	vector< longFib > vecExtSubobjCountOutVars;
	unsignedLongFib ulMaxSubobjectNumber = 0;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	//cFibSet
	map< unsignedIntFib, list< longFib > > mapSetNumberOfDefVar;
	map< unsignedIntFib, list< longFib > > mapSetNumberOfSets;
	map< unsignedIntFib, list< cFibVector * > > mapSetExistingSets;
	
	//cFibMatrix
	map< unsignedIntFib, list< longFib > > mapMatrixNumberOfDefVar;
	map< unsignedIntFib, list< longFib > > mapMatrixNumberOfVectors;
	map< unsignedIntFib, list< longFib > > mapMatrixAreasLower;
	map< unsignedIntFib, list< longFib > > mapMatrixAreasUpper;
	map< unsignedIntFib, list< cFibVector * > > mapMatrixExistingVectors;
	
	
	//just check subobjects
	DEBUG_OUT_L2(<<"cRoot("<<this<<")::generateNeededDomains() searching the Fib elements"<<endl<<flush);
#ifdef FEATURE_GENERATE_NEEDED_DOMAINS
	unsignedLongFib uiElementsToCheck =
		pMainFibObject->getNumberOfElements();
	//for every Fib element in the Fib-object
	for ( cFibElement * pActualFibElement = pMainFibObject;
			( pActualFibElement != NULL ) && ( 0 < uiElementsToCheck );
			pActualFibElement = pActualFibElement->getNextFibElement(),
			uiElementsToCheck-- ){
#else //FEATURE_GENERATE_NEEDED_DOMAINS
	unsignedLongFib uiElementsToCheck = getNumberOfElements();
	//for every Fib element in the Fib-object
	for ( cFibElement * pActualFibElement = this;
			( pActualFibElement != NULL ) && ( 0 < uiElementsToCheck );
			pActualFibElement = pActualFibElement->getNextFibElement(),
			uiElementsToCheck-- ){
#endif //FEATURE_GENERATE_NEEDED_DOMAINS
	
		
		const char cActualType = pActualFibElement->getType();
		
		if ( ( cActualType == 'f' ) || ( cActualType == 'i' ) ){
			/*if the Fib element is an functionelement
			-> search for all values*/
			
			//the list with the underfunctions, wich whern't searched
			list<const cUnderFunction *> liOpenUnderFunctions;
			list<const cCondition *> liOpenSubConditions;
			if ( cActualType == 'f' ){
			
				const cUnderFunction * pUnderFunction =
					((cFunction*)pActualFibElement)->getUnderFunction();
				liOpenUnderFunctions.push_back( pUnderFunction );
			}else{// pActualFibElement->getType() == 'i' )
				const cCondition * pCondition =
					((cIf*)pActualFibElement)->getCondition();
				liOpenSubConditions.push_back( pCondition );
			}
			
			while ( ( ! liOpenUnderFunctions.empty() ) ||
					( ! liOpenSubConditions.empty() ) ){
				
				while ( ! liOpenUnderFunctions.empty() ){
					//search every underfunction
					const cUnderFunction * pUnderFunction =
						liOpenUnderFunctions.front();
					liOpenUnderFunctions.pop_front();
					
					if ( pUnderFunction->getNumberOfUnderFunctions() == 0 ){
						//this is a variable or value underfunction
						if ( pUnderFunction->getType() == cUnderFunction::FUNCTION_VALUE ){
							//evalue the minimal number of bits for the mantissa
							liValuesInFunctions.push_back( pUnderFunction->getValue() );
						}//else ignore variable underfunctions
						
					}else if ( pUnderFunction->getNumberOfUnderFunctions() == 1 ){
						/*this is a one value underfunction
						-> add the one underfunctions into the to search through underfunctions*/
						liOpenUnderFunctions.push_back(
							((cFunctionOneValue*)pUnderFunction)->getUnderFunction() );
						
					}else if ( pUnderFunction->getNumberOfUnderFunctions() == 2 ){
						/*this is a two value underfunction
						-> add the two underfunctions into the to search through underfunctions*/
					
						liOpenUnderFunctions.push_back(
							((cFunctionTwoValue*)pUnderFunction)->getFirstUnderFunction() );
						liOpenUnderFunctions.push_back(
							((cFunctionTwoValue*)pUnderFunction)->getSecondUnderFunction() );
						
						//check special cases
						if ( pUnderFunction->getType() == cUnderFunction::FUNCTION_IF ){
							//if subfunction add condition
							liOpenSubConditions.push_back(
								((cFunctionIf*)pUnderFunction)->getCondition() );
						}
					}
				}//end while open underfunctions exists
				while ( ! liOpenSubConditions.empty() ){
					//search every subcondition
					const cCondition * pSubCondition =
						liOpenSubConditions.front();
					liOpenSubConditions.pop_front();
					
					if ( pSubCondition->getNumberOfConditions() == 1 ){
						/*this is a one value subcondition
						-> add the one subcondition into the to search through subconditions*/
						liOpenSubConditions.push_back(
							((cConditionNot*)pSubCondition)->getSubCondition() );
						
					}else if ( pSubCondition->getNumberOfConditions() == 2 ){
						/*this is a two value subcondition
						-> add the two subconditions into the to search through subconditions*/
						liOpenSubConditions.push_back(
							((cConditionTwoValue*)pSubCondition)->getFirstSubCondition() );
						liOpenSubConditions.push_back(
							((cConditionTwoValue*)pSubCondition)->getSecondSubCondition() );
						
					}else if ( pSubCondition->getNumberOfUnderFunctions() == 2 ){
						/*this is a comparison condition with two underfunctions
						-> add the two underfunctions into the to search through underfunctions*/
					
						liOpenUnderFunctions.push_back(
							((cConditionComparison*)pSubCondition)->getFirstSubFunction() );
						liOpenUnderFunctions.push_back(
							((cConditionComparison*)pSubCondition)->getSecondSubFunction() );
					}
				}//end while open subconditions exists
				
			}//end while open subelements exists
		//end if function or if-element
		}else if ( cActualType == 'a' ){
			/*if the Fib element is an areaelement
			-> add all values in the subareas to the liValuesInAreas*/
			cArea * pArea = (cArea*)pActualFibElement;
			const unsignedIntFib uiNumberOfSubareas = pArea->getNumberOfSubareas();
			liValuesInCountSubareas.push_back( uiNumberOfSubareas );
			
			for ( unsignedIntFib uiActualSubarea = 1;
					uiActualSubarea <= uiNumberOfSubareas; uiActualSubarea++ ){
				
				const cVectorArea * pVectorArea =
					pArea->getSubarea( uiActualSubarea );
				
				if ( pVectorArea != NULL ){
					if ( ! pVectorArea->isVariable( 1 ) ){
						liValuesInAreasLower.push_back( pVectorArea->getValue( 1 ) );
					}
					if ( ! pVectorArea->isVariable( 2 ) ){
						liValuesInAreasUpper.push_back( pVectorArea->getValue( 2 ) );
					}
				}
			}
		}else if ( cActualType == 'o' ){
			//extern object element
			cExtObject * pExtObject = (cExtObject*)pActualFibElement;
			
			const longFib lIdentifierExtObject = pExtObject->getIdentifier();
			liValuesInExtObjIdentifier.push_back( lIdentifierExtObject );
			liValuesInExtObjCountInVars.push_back(
				pExtObject->getNumberOfInputValues() );
			
			const unsignedIntFib uiNumberOfSubobjects =
				pExtObject->getNumberOfSubobjects();
			liValuesInExtObjCountSubobj.push_back( uiNumberOfSubobjects );
			//get output variable counts
			for ( unsignedIntFib uiActualSubObject = 1;
					uiActualSubObject <= uiNumberOfSubobjects; uiActualSubObject++ ){
				
				liValuesInExtObjCountOutVars.push_back(
					pExtObject->getNumberOfOutputVariables( uiActualSubObject ) );
			}
			
			//add input vectors
			mapExtObjectInputVectors[ lIdentifierExtObject ].push_back(
				pExtObject->getInputVector() );
			
		}else if ( cActualType == 's' ){
			//extern subobject element
			DEBUG_OUT_L3(<<"cRoot("<<this<<")::generateNeededDomains() found extern subobject element"<<endl<<flush);
			cExtSubobject * pExtSubobject = (cExtSubobject*)pActualFibElement;
			
			const unsignedIntFib uiNumberSubobject =
				pExtSubobject->getNumberSubobject();
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
			mapExtSubobjectOutputVectors[ uiNumberSubobject ].push_back(
					pExtSubobject->getOutputVector() );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
			const unsignedIntFib uiNumberOfOutputVariables =
				pExtSubobject->getNumberOfOutputVariables();
			
			liValuesInExtSubobjCountOutVars.push_back(
				uiNumberOfOutputVariables );
			
			DEBUG_OUT_L3(<<"   number of subobject "<<uiNumberSubobject<<"; number of output variables "<<uiNumberOfOutputVariables<<endl<<flush);
			if ( ulMaxSubobjectNumber < uiNumberSubobject ){
				//new maximal / greatest subobject number
				DEBUG_OUT_L3(<<"   setting new maximal / greatest subobject number"<<endl<<flush);
				ulMaxSubobjectNumber = uiNumberSubobject;
			}
			if ( ( vecExtSubobjCountOutVars.size() < uiNumberSubobject ) &&
					( uiNumberSubobject < MAX_SUBOBJECTS ) ){
				
				vecExtSubobjCountOutVars.resize( uiNumberSubobject, 0 );
			}//else to much subobjects to set
			if ( ( 0 < uiNumberSubobject ) &&
					( uiNumberSubobject <= vecExtSubobjCountOutVars.size() ) ){
				if ( vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] < uiNumberOfOutputVariables ){
					//store number of maximal output variables for the subobject
					DEBUG_OUT_L4(<<"   setting number of output variables of the subobject "<<uiNumberSubobject<<" to the number "<<uiNumberOfOutputVariables<<endl<<flush);
					vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] =
						uiNumberOfOutputVariables;
				}//else number of output variables correct
			}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
		}else if ( cActualType == 'v' ){
			//set-element cFibSet
			DEBUG_OUT_L3(<<"cRoot("<<this<<")::generateNeededDomains() found set-element"<<endl<<flush);
			cFibSet * pFibSet = (cFibSet*)pActualFibElement;
			
			const unsignedIntFib uiDomainNumber = pFibSet->getDomainNr();
			
			mapSetNumberOfDefVar[ uiDomainNumber ].push_back(
				pFibSet->getNumberOfVariables() );
			
			const unsignedIntFib uiNumberOfVectors =
				pFibSet->getNumberOfVectors();
			
			mapSetNumberOfSets[ uiDomainNumber ].push_back( uiNumberOfVectors );
			//add set vectors of the set-element
			list< cFibVector * > & liSets =
				mapSetExistingSets[ uiDomainNumber ];
			for ( unsignedIntFib uiPosition = 1; uiPosition <= uiNumberOfVectors;
					uiPosition++ ){
				liSets.push_back( pFibSet->getVector( uiPosition ) );
			}
			
		}else if ( cActualType == 'm' ){
			//matrix element cFibMatrix
			DEBUG_OUT_L3(<<"cRoot("<<this<<")::generateNeededDomains() found matrix element"<<endl<<flush);
			cFibMatrix * pFibMatrix = (cFibMatrix*)pActualFibElement;
			
			const unsignedIntFib uiDomainNumber = pFibMatrix->getDomainNr();
			
			const unsignedIntFib uiNumberOfDimensions =
				pFibMatrix->getNumberOfMatrixDimensions();
			
			mapMatrixNumberOfDefVar[ uiDomainNumber ].push_back( uiNumberOfDimensions );
			//add matrix area vectors of the matrix element
			list< longFib > & liAreasLower = mapMatrixAreasLower[ uiDomainNumber ];
			list< longFib > & liAreasUpper = mapMatrixAreasUpper[ uiDomainNumber ];
			for ( unsignedIntFib uiActualArea = 1;
					uiActualArea <= uiNumberOfDimensions; uiActualArea++ ){
				
				const cVectorArea * pVectorArea =
					pFibMatrix->getArea( uiActualArea );
				
				if ( pVectorArea != NULL ){
					if ( ! pVectorArea->isVariable( 1 ) ){
						liAreasLower.push_back( pVectorArea->getValue( 1 ) );
					}
					if ( ! pVectorArea->isVariable( 2 ) ){
						liAreasUpper.push_back( pVectorArea->getValue( 2 ) );
					}
				}
			}//end add all area bounderies
			
			mapMatrixNumberOfDefVar[ uiDomainNumber ].push_back(
				pFibMatrix->getNumberOfVectorElements() );
			
			const unsignedIntFib uiNumberOfVectors =
				pFibMatrix->getNumberOfVectors();
			
			mapMatrixNumberOfVectors[ uiDomainNumber ].push_back( uiNumberOfVectors );
			//add matrix vectors of the matrix element
			list< cFibVector * > & liVectors =
				mapMatrixExistingVectors[ uiDomainNumber ];
			for ( unsignedIntFib uiPosition = 1; uiPosition <= uiNumberOfVectors;
					uiPosition++ ){
				liVectors.push_back( pFibMatrix->getVector( uiPosition ) );
			}
#ifdef FEATURE_GENERATE_NEEDED_DOMAINS
		}else if ( cActualType == 'r' ){
			//root-element -> stop
			break;
#endif //FEATURE_GENERATE_NEEDED_DOMAINS
		}
	}
	DEBUG_OUT_L2(<<"cRoot("<<this<<")::generateNeededDomains() generating needed domains"<<endl<<flush);
#ifdef FEATURE_GENERATE_NEEDED_DOMAINS
	//for checking if values in existing needed domains
	cDomains validDomains = getValidValueDomains();
	//generate needed domains for function elements
	if ( ! liValuesInFunctions.empty() ){
		//check if values are in existing needed domains
		const cTypeUnderFunction typeUnderFunction;
		cDomain * pDomainFunctionBase = 
			validDomains.getDomainForElement( typeUnderFunction );
		bool bAddNewDomain = bAddAllValueDomains;
		if ( ( pDomainFunctionBase == NULL ) ||
				( ! pDomainFunctionBase->isScalar() ) ){
			//no domain exists yet or not a number domain -> add one
			bAddNewDomain = true;
		}
		if ( ! bAddNewDomain ){
			cDomainSingle * pDomainFunction = (cDomainSingle*)
				(pDomainFunctionBase);
			//check if all function elements are element of the domain
			for ( list< doubleFib >::const_iterator
					itrValue = liValuesInFunctions.begin();
					itrValue != liValuesInFunctions.end(); itrValue++ ){
				
				if ( ! pDomainFunction->isElement( *itrValue ) ){
					//number not in existing valid domain -> create a new domain
					bAddNewDomain = true;
					break;
				}
			}//end for check if all values are in domain
		}

		if ( bAddNewDomain ){
			//create and add the function domain
			cDomainSingle * pDomainFunction =
				cDomainSingle::createGoodDomain( liValuesInFunctions );
			
			valueDomains.addDomain( typeUnderFunction, *pDomainFunction );
			delete pDomainFunction;
		}
	}
	//generate needed domains for area elements
	if ( ! liValuesInCountSubareas.empty() ){
		//check if values are in existing needed domains
		bool bAddNewDomain = bAddAllValueDomains;
		const cTypeArea typeArea;
		cDomain * pDomainAreaBase =
			validDomains.getDomainForElement( typeArea );
		if ( ( pDomainAreaBase == NULL ) ||
				( ! pDomainAreaBase->isVector() ) ){
			//no correct domain
			bAddNewDomain = true;
		}
		cDomainVector * pDomainArea = (cDomainVector*)pDomainAreaBase;

		if ( ( pDomainArea == NULL ) ||
				( pDomainArea->getNumberOfElements() != 2 ) ){
			//no correct domain exists yet -> add one
			bAddNewDomain = true;
		}
		if ( ! bAddNewDomain ){
			//check counts of subareas domain
			const cDomain * pSubdomainCountSubareas =
				pDomainArea->getElementDomain( 1 );
				
			if ( ( pSubdomainCountSubareas != NULL ) &&
					( pSubdomainCountSubareas->isScalar() ) ){
				cDomainSingle * pDomainLower =
					(cDomainSingle*)pSubdomainCountSubareas;
				for ( list< longFib >::const_iterator
						itrValue = liValuesInCountSubareas.begin();
						itrValue != liValuesInCountSubareas.end(); itrValue++ ){
					
					if ( ! pDomainLower->isElement( *itrValue ) ){
						//number not in existing valid domain -> create a new domain
						bAddNewDomain = true;
						break;
					}
				}
			}else{//no lower domain exists yet -> add one
				bAddNewDomain = true;
			}
		}
		if ( ( pDomainAreaBase != NULL ) && ( pDomainAreaBase->isVector() ) &&
				( pDomainArea->getNumberOfElements() == 2 ) ){
			//check subarea domain
			cDomain * pDomainSubareaBase =
				pDomainArea->getElementDomain( 2 );
			if ( ( pDomainSubareaBase == NULL ) ||
					( ! pDomainSubareaBase->isVector() ) ){
				//no correct domain
				bAddNewDomain = true;
			}
			cDomainVector * pDomainSubarea = (cDomainVector*)pDomainSubareaBase;
			if ( ( pDomainSubarea == NULL ) ||
					( pDomainSubarea->getNumberOfElements() != 2 ) ){
				//no correct domain exists yet -> add one
				bAddNewDomain = true;
			}

			if ( ! bAddNewDomain ){
				//check lower domain
				const cDomain * pDomainElementLower =
					pDomainSubarea->getElementDomain( 1 );
					
				if ( ( pDomainElementLower != NULL ) &&
						( pDomainElementLower->isScalar() ) ){
					cDomainSingle * pDomainLower =
						(cDomainSingle*)pDomainElementLower;
					for ( list< longFib >::const_iterator
							itrValue = liValuesInAreasLower.begin();
							itrValue != liValuesInAreasLower.end(); itrValue++ ){
						
						if ( ! pDomainLower->isElement( *itrValue ) ){
							//number not in existing valid domain -> create a new domain
							bAddNewDomain = true;
							break;
						}
					}
				}else{//no lower domain exists yet -> add one
					bAddNewDomain = true;
				}
			}
			if ( ! bAddNewDomain ){
				//check upper domain
				const cDomain * pDomainElementUpper =
					pDomainSubarea->getElementDomain( 2 );
					
				if ( ( pDomainElementUpper != NULL ) &&
						( pDomainElementUpper->isScalar() ) ){
					
					cDomainSingle * pDomainUpper =
						(cDomainSingle*)pDomainElementUpper;
					for ( list< longFib >::const_iterator
							itrValue = liValuesInAreasUpper.begin();
							itrValue != liValuesInAreasUpper.end(); itrValue++ ){
						
						if ( ! pDomainUpper->isElement( *itrValue ) ){
							//number not in existing valid domain -> create a new domain
							bAddNewDomain = true;
							break;
						}
					}
				}else{//no upper domain exists yet -> add one
					bAddNewDomain = true;
				}
			}
		}//end if check subarea domain
		if ( bAddNewDomain ){
			//create and add the area domain
			vector<cDomainSingle*> vecSubareaDomain( 2 );
			vecSubareaDomain[ 0 ] =
				cDomainIntegerBasis::createGoodDomain( liValuesInAreasLower );
			vecSubareaDomain[ 1 ] =
				cDomainIntegerBasis::createGoodDomain( liValuesInAreasUpper );
			cDomainVector * pVectorSubareaDomain = new cDomainVector( vecSubareaDomain );
			delete vecSubareaDomain[ 0 ];
			delete vecSubareaDomain[ 1 ];
			
			vector<cDomain*> vecAreaDomain( 2 );
			vecAreaDomain[ 0 ] =
				cDomainIntegerBasis::createGoodDomain( liValuesInCountSubareas );
			vecAreaDomain[ 1 ] = pVectorSubareaDomain;
			cDomainVector * pVectorAreaDomain = new cDomainVector( vecAreaDomain );
			delete vecAreaDomain[ 0 ];
			delete pVectorSubareaDomain;//=vecAreaDomain[ 1 ]
			
			valueDomains.addDomain( typeArea, *pVectorAreaDomain );
			delete pVectorAreaDomain;
		}
	}
	//extern object element
	if ( ! liValuesInExtObjIdentifier.empty() ){
		//check if values are in existing needed domains
		DEBUG_OUT_L2(<<"check if generating domain for extern object element"<<endl<<flush);
		const cTypeExtObject typeExtobject;
		cDomainVector * pDomainExtobject = (cDomainVector*)
			validDomains.getDomainForElement( typeExtobject );
		bool bAddNewDomain = false;
		if ( ( pDomainExtobject == NULL ) ||//no domain exists yet -> add one
				( pDomainExtobject->getNumberOfElements() != 4 ) ){
			//no correct domain exists yet -> add one
			bAddNewDomain = true;
		}
		if ( ! bAddNewDomain ){
			//check identifier domain
			const cDomain * pDomainElementIdentifier =
				pDomainExtobject->getElementDomain( 1 );
				
			if ( ( pDomainElementIdentifier != NULL ) &&
					( pDomainElementIdentifier->isScalar() ) ){
				cDomainSingle * pDomainIdentifier =
					(cDomainSingle*)pDomainElementIdentifier;
				
				for ( list< longFib >::const_iterator
						itrValue = liValuesInExtObjIdentifier.begin();
						itrValue != liValuesInExtObjIdentifier.end(); itrValue++ ){
					
					if ( ! pDomainIdentifier->isElement( *itrValue ) ){
						//number not in existing valid domain -> create a new domain
						bAddNewDomain = true;
						break;
					}
				}
			}else{//no identifier domain exists yet -> add one
				bAddNewDomain = true;
			}
		}
		if ( ! bAddNewDomain ){
			//check count input variables domain
			const cDomain * pDomainElementInVars =
				pDomainExtobject->getElementDomain( 2 );
				
			if ( ( pDomainElementInVars != NULL ) &&
					( pDomainElementInVars->isScalar() ) ){
				cDomainSingle * pDomainInVars =
					(cDomainSingle*)pDomainElementInVars;
				
				for ( list< longFib >::const_iterator
						itrValue = liValuesInExtObjCountInVars.begin();
						itrValue != liValuesInExtObjCountInVars.end(); itrValue++ ){
					
					if ( ! pDomainInVars->isElement( *itrValue ) ){
						//number not in existing valid domain -> create a new domain
						bAddNewDomain = true;
						break;
					}
				}
			}else{//no count input variables domain exists yet -> add one
				bAddNewDomain = true;
			}
		}
		if ( ! bAddNewDomain ){
			//check count subobjects domain
			const cDomain * pDomainElementSubobjects =
				pDomainExtobject->getElementDomain( 3 );
				
			if ( ( pDomainElementSubobjects != NULL ) &&
					( pDomainElementSubobjects->isScalar() ) ){
				cDomainSingle * pDomainSubobjects =
					(cDomainSingle*)pDomainElementSubobjects;
					
				for ( list< longFib >::const_iterator
						itrValue = liValuesInExtObjCountSubobj.begin();
						itrValue != liValuesInExtObjCountSubobj.end(); itrValue++ ){
					
					if ( ! pDomainSubobjects->isElement( *itrValue ) ){
						//number not in existing valid domain -> create a new domain
						bAddNewDomain = true;
						break;
					}
				}
			}else{//no count subobjects domain exists yet -> add one
				bAddNewDomain = true;
			}
		}
		if ( ! bAddNewDomain ){
			//check count output variables domain
			const cDomain * pDomainElementOutVar =
				pDomainExtobject->getElementDomain( 4 );
				
			if ( ( pDomainElementOutVar != NULL ) &&
					( pDomainElementOutVar->isScalar() ) ){
				cDomainSingle * pDomainOutVar =
					(cDomainSingle*)pDomainElementOutVar;
				
				for ( list< longFib >::const_iterator
						itrValue = liValuesInExtObjCountOutVars.begin();
						itrValue != liValuesInExtObjCountOutVars.end(); itrValue++ ){
					
					if ( ! pDomainOutVar->isElement( *itrValue ) ){
						//number not in existing valid domain -> create a new domain
						bAddNewDomain = true;
						break;
					}
				}
			}else{//no count output variables domain exists yet -> add one
				bAddNewDomain = true;
			}
		}
		if ( bAddNewDomain ){
			DEBUG_OUT_L2(<<"generating domain for extern object element"<<endl<<flush);
			//create vector domain
			vector<cDomainSingle*> vecExtObjectDomains( 4 );
			vecExtObjectDomains[ 0 ] =
				cDomainIntegerBasis::createGoodDomain( liValuesInExtObjIdentifier );
			vecExtObjectDomains[ 1 ] =
				cDomainIntegerBasis::createGoodDomain( liValuesInExtObjCountInVars );
			vecExtObjectDomains[ 2 ] =
				cDomainIntegerBasis::createGoodDomain( liValuesInExtObjCountSubobj );
			vecExtObjectDomains[ 3 ] =
				cDomainIntegerBasis::createGoodDomain( liValuesInExtObjCountOutVars );
			
			cDomainVector * pVectorExtObjectDomain = new cDomainVector( vecExtObjectDomains );
			delete vecExtObjectDomains[ 0 ];
			delete vecExtObjectDomains[ 1 ];
			delete vecExtObjectDomains[ 2 ];
			delete vecExtObjectDomains[ 3 ];
			
			valueDomains.addDomain( cTypeExtObject(), *pVectorExtObjectDomain );
			delete pVectorExtObjectDomain;
		}
		
		//create vectors for the input value vectors for each identifier
		DEBUG_OUT_L2(<<"create vectors for the input value vectors for each identifier"<<endl<<flush);
		for ( map< longFib, list< cFibVector * > >::iterator
				itrActualExtObjectId = mapExtObjectInputVectors.begin();
				itrActualExtObjectId != mapExtObjectInputVectors.end();
				itrActualExtObjectId++ ){
			
			const longFib lIdentifierExtObject = itrActualExtObjectId->first;
			list< cFibVector * > & liExtObjectInputVectors =
				itrActualExtObjectId->second;
			DEBUG_OUT_L2(<<"check domain for the input value vectors for identifier "<<lIdentifierExtObject<<endl<<flush);
			
			//check input value vector domain
			const cTypeExtObjectInput typeExtObjectInput( lIdentifierExtObject );
			cDomain * pDomainExtObjectInputBase = 
				validDomains.getDomainForElement( typeExtObjectInput );
			bool bAddNewDomain = bAddAllValueDomains;
			if ( ( pDomainExtObjectInputBase == NULL ) ||//no domain exists yet -> add one
					( ! pDomainExtObjectInputBase->isVector() ) ){
				//no correct domain exists yet -> add one
				bAddNewDomain = true;
			}
			if ( ! bAddNewDomain ){
				cDomainVectorBasis * pDomainExtObjectInput =
					(cDomainVectorBasis*)pDomainExtObjectInputBase;
				
				//check all input value vectors for the identifier
				for ( list< cFibVector * >::const_iterator
						itrVector = liExtObjectInputVectors.begin();
						itrVector != liExtObjectInputVectors.end(); itrVector++ ){
					
					if ( ! pDomainExtObjectInput->isElement( **itrVector ) ){
						//vector not in existing valid domain -> create a new domain
						bAddNewDomain = true;
						break;
					}
				}
			}
			//create a domain if needed
			if ( bAddNewDomain ){
				//delete existing domains from the value domains
				valueDomains.deleteDomain( typeExtObjectInput );
				
				DEBUG_OUT_L2(<<"create domain for the input value vectors for identifier "<<lIdentifierExtObject<<" with "<<liExtObjectInputVectors.size()<<" vectors"<<endl<<flush);
				//create vector domain
				cDomainVectorBasis * pDomainExtObjectInput =
					cDomainVectorBasis::createGoodDomain( liExtObjectInputVectors );
					
				DEBUG_OUT_L3(<<"   domain for the input value vectors for identifier "<<lIdentifierExtObject<<" created"<<endl<<flush);
				
				valueDomains.addDomain( typeExtObjectInput,
					*pDomainExtObjectInput );
				delete pDomainExtObjectInput;
			}
		}
		DEBUG_OUT_L2(<<"end check and create external object domains"<<endl<<flush);
	}//end check and create external object domains
	
#else //FEATURE_GENERATE_NEEDED_DOMAINS
	
	if ( ! liValuesInFunctions.empty() ){
		//create and add the functiondomain
		cDomainSingle * pDomainFunction =
			cDomainSingle::createGoodDomain( liValuesInFunctions );
		
		getDomains()->addDomain( cTypeUnderFunction(), *pDomainFunction );
		delete pDomainFunction;
	}
	
	if ( ! liValuesInAreasLower.empty() ){
		//create and add the areadomain
		vector<cDomainSingle*> vecAreaDomains( 2 );
		vecAreaDomains[ 0 ] =
			cDomainIntegerBasis::createGoodDomain( liValuesInAreasLower );
		vecAreaDomains[ 1 ] =
			cDomainIntegerBasis::createGoodDomain( liValuesInAreasUpper );
		cDomainVector * pVectorAreaDomain = new cDomainVector( vecAreaDomains );
		delete vecAreaDomains[ 0 ];
		delete vecAreaDomains[ 1 ];
		
		getDomains()->addDomain( cTypeArea(), *pVectorAreaDomain );
		delete pVectorAreaDomain;
	}
	//extern object element
	if ( ! liValuesInExtObjIdentifier.empty() ){
		//create vector domain
		vector<cDomainSingle*> vecExtObjectDomains( 4 );
		vecExtObjectDomains[ 0 ] =
			cDomainIntegerBasis::createGoodDomain( liValuesInExtObjIdentifier );
		vecExtObjectDomains[ 1 ] =
			cDomainIntegerBasis::createGoodDomain( liValuesInExtObjCountInVars );
		vecExtObjectDomains[ 2 ] =
			cDomainIntegerBasis::createGoodDomain( liValuesInExtObjCountSubobj );
		vecExtObjectDomains[ 3 ] =
			cDomainIntegerBasis::createGoodDomain( liValuesInExtObjCountOutVars );
		
		cDomainVector * pVectorExtObjectDomain = new cDomainVector( vecExtObjectDomains );
		delete vecExtObjectDomains[ 0 ];
		delete vecExtObjectDomains[ 1 ];
		delete vecExtObjectDomains[ 2 ];
		delete vecExtObjectDomains[ 3 ];
		
		getDomains()->addDomain( cTypeExtObject(), *pVectorExtObjectDomain );
		delete pVectorExtObjectDomain;
	}
#endif //FEATURE_GENERATE_NEEDED_DOMAINS

	//generate needed domains for external subobject elements
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	if ( ! mapExtSubobjectOutputVectors.empty() ){
		//check domains for all external subobject numbers
		for ( map< unsignedLongFib, list< cFibVector * > >::iterator
				itrActualSubobject = mapExtSubobjectOutputVectors.begin();
				itrActualSubobject != mapExtSubobjectOutputVectors.end();
				itrActualSubobject++ ){
			
			const unsignedIntFib uiNumberOfSubobject = 
				itrActualSubobject->first;
			list< cFibVector* > & liOutputVectors =
				itrActualSubobject->second;
			
			//get domain for actual external subobject
			const cTypeExtSubobject typeExtSubobject( uiNumberOfSubobject );
			const cDomain * pDomainExtSubobject =
				validDomains.getDomainForElement( typeExtSubobject );
			
			bool bAddNewDomain = bAddAllValueDomains;
			if ( pDomainExtSubobject == NULL ){
				//no domain -> add one
				bAddNewDomain = true;
			}else if ( ! pDomainExtSubobject->isVector() ){
				//the domain is not a vector domain
				bAddNewDomain = true;
			}else{//check all output value vectors
				const cDomainVectorBasis * pDomainVectorExtSubobject =
					(const cDomainVectorBasis*)pDomainExtSubobject;
				
				for ( list< cFibVector * >::const_iterator
						itrVector = liOutputVectors.begin();
						itrVector != liOutputVectors.end(); itrVector++ ){
					
					if ( ! pDomainVectorExtSubobject->isElement( **itrVector ) ){
						//vector not in existing valid domain -> create a new domain
						bAddNewDomain = true;
						break;
					}
				}
			}//end if check actual external subobject domain
			
			if ( bAddNewDomain ){
				//delete existing domains from the value domains
				valueDomains.deleteDomain( typeExtSubobject );
				//create new domain
				cDomainVectorBasis * pDomainExtSubobjectOutput =
					cDomainVectorBasis::createGoodDomain( liOutputVectors );
				
				//add new domain
				domains.addDomain( typeExtSubobject, *pDomainExtSubobjectOutput );
				delete pDomainExtSubobjectOutput;
			}
		}//end for all subobjects
	}
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	if ( ! liValuesInExtSubobjCountOutVars.empty() ){
		//external subobject elements exists
		//check if values are in existing needed domains
		DEBUG_OUT_L3(<<"generating domains for external subobject elements"<<endl<<flush);
		const cTypeExtSubobject typeExtSubobject;
		cDomainIntegerBasis * pDomainExtSubobject = (cDomainIntegerBasis*)
			validDomains.getDomainForElement( typeExtSubobject );
		bool bAddNewDomain = true;
		if ( pDomainExtSubobject != NULL ){
			bAddNewDomain = false;
			for ( list< longFib >::const_iterator
					itrValue = liValuesInExtSubobjCountOutVars.begin();
					itrValue != liValuesInExtSubobjCountOutVars.end(); itrValue++ ){
				
				if ( ! pDomainExtSubobject->isElement( *itrValue ) ){
					//number not in existing valid domain -> create a new domain
					bAddNewDomain = true;
					break;
				}
			}
		}//else no domain exists yet -> add one

		if ( bAddNewDomain ){
			//create and add the external subobject domain
			cDomainIntegerBasis * pDomainExtSubobjectNew =
				cDomainIntegerBasis::createGoodDomain( liValuesInExtSubobjCountOutVars );
			
			getDomains()->addDomain( typeExtSubobject, *pDomainExtSubobjectNew );
			delete pDomainExtSubobjectNew;
		}
		//check external subobject number
		const unsignedIntFib uiNumberSubobjectCounts =
			vecExtSubobjCountOutVars.size();
		if ( getNumberOfExternSubobjects() < uiNumberSubobjectCounts ){
			/*actual number of external subobjects to low
			-> set it to the maximal / greates external subobject number*/
			setNumberOfExternSubobjects( uiNumberSubobjectCounts );
		}
		//check number of output variables for the subobjects
		for ( unsignedIntFib uiNumberOfSubobject = 1;
				uiNumberOfSubobject <= uiNumberSubobjectCounts;
				uiNumberOfSubobject++ ){
			
			if ( vecExtSubobjCountOutVars[ uiNumberOfSubobject - 1 ] <
					getNumberOfOutputVariables( uiNumberOfSubobject ) ){
				/*correct the number of output variables of the subobject to
				the correct value*/
				setNumberOfOutputVariables( uiNumberOfSubobject,
					vecExtSubobjCountOutVars[ uiNumberOfSubobject - 1 ] );
			}//number of output variables for the subobject correct
		}
		DEBUG_OUT_L3(<<"domains for external subobject elements generated"<<endl<<flush);
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//set-element
	if ( ! mapSetNumberOfDefVar.empty() ){
		//check for all existing domain numbers
		for ( map< unsignedIntFib, list< longFib > >::const_iterator
				itrActualDomainNumber = mapSetNumberOfDefVar.begin();
				itrActualDomainNumber != mapSetNumberOfDefVar.end();
				itrActualDomainNumber++ ){
			const unsignedIntFib uiNumberOfDomain =
				itrActualDomainNumber->first;
			
			//check if values are in existing domains
			const cTypeFibSet typeFibSet( uiNumberOfDomain );
			cDomainVectorBasis * pDomainFibSet = (cDomainVectorBasis*)
				validDomains.getDomainForElement( typeFibSet );
			bool bAddNewDomain = bAddAllValueDomains;
			if ( ( pDomainFibSet == NULL ) ||//no domain exists yet -> add one
					( pDomainFibSet->getNumberOfElements() != 3 ) ){
				//no correct domain exists yet -> add one
				bAddNewDomain = true;
			}
			if ( ! bAddNewDomain ){
				//check number of defined variables
				const cDomain * pDomainElementNumberDefVar =
					pDomainFibSet->getElementDomain( 1 );
				
				if ( ( pDomainElementNumberDefVar != NULL ) &&
						( pDomainElementNumberDefVar->isScalar() ) ){
					cDomainSingle * pDomainNumberDefVar =
						(cDomainSingle*)pDomainElementNumberDefVar;
					
					list< longFib > & liNumberOfDefVar =
						mapSetNumberOfDefVar[ uiNumberOfDomain ];
					
					for ( list< longFib >::const_iterator
							itrValue = liNumberOfDefVar.begin();
							itrValue != liNumberOfDefVar.end(); itrValue++ ){
						
						if ( ! pDomainNumberDefVar->isElement( *itrValue ) ){
							//number not in existing valid domain -> create a new domain
							bAddNewDomain = true;
							break;
						}
					}
				}else{//no defined variables domain exists yet -> add one
					bAddNewDomain = true;
				}
			}
			if ( ! bAddNewDomain ){
				//check number of sets
				const cDomain * pDomainElementNumberSets =
					pDomainFibSet->getElementDomain( 2 );
				
				if ( ( pDomainElementNumberSets != NULL ) &&
						( pDomainElementNumberSets->isScalar() ) ){
					cDomainSingle * pDomainNumberSets =
						(cDomainSingle*)pDomainElementNumberSets;
					
					list< longFib > & liNumberOfSets =
						mapSetNumberOfSets[ uiNumberOfDomain ];
					
					for ( list< longFib >::const_iterator
							itrValue = liNumberOfSets.begin();
							itrValue != liNumberOfSets.end(); itrValue++ ){
						
						if ( ! pDomainNumberSets->isElement( *itrValue ) ){
							//number not in existing valid domain -> create a new domain
							bAddNewDomain = true;
							break;
						}
					}
				}else{//no number of sets domain exists yet -> add one
					bAddNewDomain = true;
				}
			}
			if ( ! bAddNewDomain ){
				//check number of sets
				const cDomain * pDomainElementVectors =
					pDomainFibSet->getElementDomain( 3 );
				
				if ( ( pDomainElementVectors != NULL ) &&
						( pDomainElementVectors->isVector() ) ){
					cDomainVectorBasis * pDomainSetVectors =
						(cDomainVectorBasis*)pDomainElementVectors;
					
					list< cFibVector * > & liSets =
						mapSetExistingSets[ uiNumberOfDomain ];
					
					for ( list< cFibVector * >::const_iterator
							itrVector = liSets.begin();
							itrVector != liSets.end(); itrVector++ ){
						
						if ( ! pDomainSetVectors->isElement( **itrVector ) ){
							//vector not in existing valid domain -> create a new domain
							bAddNewDomain = true;
							break;
						}
					}
				}else{//no sets domain exists yet -> add one
					bAddNewDomain = true;
				}
			}
			
			if ( bAddNewDomain ){
				//create vector domain
				vector<cDomain*> vecFibSetDomains( 3 );
				vecFibSetDomains[ 0 ] = cDomainIntegerBasis::createGoodDomain(
						mapSetNumberOfDefVar[ uiNumberOfDomain ] );
				vecFibSetDomains[ 1 ] = cDomainIntegerBasis::createGoodDomain(
					mapSetNumberOfSets[ uiNumberOfDomain ] );
				vecFibSetDomains[ 2 ] = cDomainVectorBasis::createGoodDomain(
					mapSetExistingSets[ uiNumberOfDomain ] );
				
				cDomainVector * pVectorFibSetDomain = new cDomainVector( vecFibSetDomains );
				delete vecFibSetDomains[ 0 ];
				delete vecFibSetDomains[ 1 ];
				delete vecFibSetDomains[ 2 ];
				
				valueDomains.addDomain( typeFibSet, *pVectorFibSetDomain );
				delete pVectorFibSetDomain;
			}
		}//end for all domain numbers
	}//end if create set-domain

	//matrix element
	if ( ! mapMatrixNumberOfDefVar.empty() ){
		//check for all existing domain numbers
		for ( map< unsignedIntFib, list< longFib > >::const_iterator
				itrActualDomainNumber = mapMatrixNumberOfDefVar.begin();
				itrActualDomainNumber != mapMatrixNumberOfDefVar.end();
				itrActualDomainNumber++ ){
			const unsignedIntFib uiNumberOfDomain =
				itrActualDomainNumber->first;
			
			//check if values are in existing domains
			const cTypeFibMatrix typeFibMatrix( uiNumberOfDomain );
			cDomainVectorBasis * pDomainFibMatrix = (cDomainVectorBasis*)
				validDomains.getDomainForElement( typeFibMatrix );
			bool bAddNewDomain = bAddAllValueDomains;
			
			if ( ( pDomainFibMatrix == NULL ) ||//no domain exists yet -> add one
					( pDomainFibMatrix->getNumberOfElements() != 4 ) ){
				//no correct domain exists yet -> add one
				bAddNewDomain = true;
			}
			if ( ! bAddNewDomain ){
				//check number of defined variables
				const cDomain * pDomainElementNumberDefVar =
					pDomainFibMatrix->getElementDomain( 1 );
				
				if ( ( pDomainElementNumberDefVar != NULL ) &&
						( pDomainElementNumberDefVar->isScalar() ) ){
					cDomainSingle * pDomainNumberDefVar =
						(cDomainSingle*)pDomainElementNumberDefVar;
					
					list< longFib > & liNumberOfDefVar =
						mapMatrixNumberOfDefVar[ uiNumberOfDomain ];
					
					for ( list< longFib >::const_iterator
							itrValue = liNumberOfDefVar.begin();
							itrValue != liNumberOfDefVar.end(); itrValue++ ){
						
						if ( ! pDomainNumberDefVar->isElement( *itrValue ) ){
							//number not in existing valid domain -> create a new domain
							bAddNewDomain = true;
							break;
						}
					}
				}else{//no defined variables domain exists yet -> add one
					bAddNewDomain = true;
				}
			}
			if ( ! bAddNewDomain ){
				//check number of vectors
				const cDomain * pDomainElementNumberVectors =
					pDomainFibMatrix->getElementDomain( 2 );
				
				if ( ( pDomainElementNumberVectors != NULL ) &&
						( pDomainElementNumberVectors->isScalar() ) ){
					cDomainSingle * pDomainNumberVectors =
						(cDomainSingle*)pDomainElementNumberVectors;
					
					list< longFib > & liNumberOfVectors =
						mapMatrixNumberOfVectors[ uiNumberOfDomain ];
					
					for ( list< longFib >::const_iterator
							itrValue = liNumberOfVectors.begin();
							itrValue != liNumberOfVectors.end(); itrValue++ ){
						
						if ( ! pDomainNumberVectors->isElement( *itrValue ) ){
							//number not in existing valid domain -> create a new domain
							bAddNewDomain = true;
							break;
						}
					}
				}else{//no number of vectors domain exists yet -> add one
					bAddNewDomain = true;
				}
			}
			
			if ( ! bAddNewDomain ){
				//check area domain
				cDomain * pDomainFibMatrixAreaBase =
					pDomainFibMatrix->getElementDomain( 3 );
				if ( ( pDomainFibMatrixAreaBase == NULL ) ||
						( ! pDomainFibMatrixAreaBase->isVector() ) ){
					//no correct domain
					bAddNewDomain = true;
				}
				cDomainVectorBasis * pDomainFibMatrixArea =
					(cDomainVectorBasis*)pDomainFibMatrixAreaBase;
				if ( ( pDomainFibMatrixArea == NULL ) ||
						( pDomainFibMatrixArea->getNumberOfElements() != 2 ) ){
					//no correct domain exists yet -> add one
					bAddNewDomain = true;
				}

				if ( ! bAddNewDomain ){
					//check lower domain
					const cDomain * pDomainElementLower =
						pDomainFibMatrixArea->getElementDomain( 1 );
						
					if ( ( pDomainElementLower != NULL ) &&
							( pDomainElementLower->isScalar() ) ){
						cDomainSingle * pDomainLower =
							(cDomainSingle*)pDomainElementLower;
							
						list< longFib > & liValuesInAreasLower =
							mapMatrixAreasLower[ uiNumberOfDomain ];
						
						for ( list< longFib >::const_iterator
								itrValue = liValuesInAreasLower.begin();
								itrValue != liValuesInAreasLower.end(); itrValue++ ){
							
							if ( ! pDomainLower->isElement( *itrValue ) ){
								//number not in existing valid domain -> create a new domain
								bAddNewDomain = true;
								break;
							}
						}
					}else{//no lower domain exists yet -> add one
						bAddNewDomain = true;
					}
				}
				if ( ! bAddNewDomain ){
					//check upper domain
					const cDomain * pDomainElementUpper =
						pDomainFibMatrixArea->getElementDomain( 2 );
						
					if ( ( pDomainElementUpper != NULL ) &&
							( pDomainElementUpper->isScalar() ) ){
						
						cDomainSingle * pDomainUpper =
							(cDomainSingle*)pDomainElementUpper;
							
						list< longFib > & liValuesInAreasUpper =
							mapMatrixAreasUpper[ uiNumberOfDomain ];
							
						for ( list< longFib >::const_iterator
								itrValue = liValuesInAreasUpper.begin();
								itrValue != liValuesInAreasUpper.end(); itrValue++ ){
							
							if ( ! pDomainUpper->isElement( *itrValue ) ){
								//number not in existing valid domain -> create a new domain
								bAddNewDomain = true;
								break;
							}
						}
					}else{//no upper domain exists yet -> add one
						bAddNewDomain = true;
					}
				}
			}//end if check area domain
			
			if ( ! bAddNewDomain ){
				//check number of sets
				const cDomain * pDomainElementVectors =
					pDomainFibMatrix->getElementDomain( 4 );
				
				if ( ( pDomainElementVectors != NULL ) &&
						( pDomainElementVectors->isVector() ) ){
					cDomainVectorBasis * pDomainMatrixVectors =
						(cDomainVectorBasis*)pDomainElementVectors;
					
					list< cFibVector * > & liVectors =
						mapMatrixExistingVectors[ uiNumberOfDomain ];
					
					for ( list< cFibVector * >::const_iterator
							itrVector = liVectors.begin();
							itrVector != liVectors.end(); itrVector++ ){
						
						if ( ! pDomainMatrixVectors->isElement( **itrVector ) ){
							//vector not in existing valid domain -> create a new domain
							bAddNewDomain = true;
							break;
						}
					}
				}else{//no sets domain exists yet -> add one
					bAddNewDomain = true;
				}
			}
			
			if ( bAddNewDomain ){
				//create vector domain
				vector<cDomain*> vecFibMatrixDomains( 4 );
				vecFibMatrixDomains[ 0 ] = cDomainIntegerBasis::createGoodDomain(
						mapMatrixNumberOfDefVar[ uiNumberOfDomain ] );
				vecFibMatrixDomains[ 1 ] = cDomainIntegerBasis::createGoodDomain(
					mapMatrixNumberOfVectors[ uiNumberOfDomain ] );
				//create matrix area domain
				vector<cDomainSingle*> vecAreaDomain( 2 );
				vecAreaDomain[ 0 ] = cDomainIntegerBasis::createGoodDomain(
					mapMatrixAreasLower[ uiNumberOfDomain ] );
				vecAreaDomain[ 1 ] = cDomainIntegerBasis::createGoodDomain(
					mapMatrixAreasUpper[ uiNumberOfDomain ] );
				vecFibMatrixDomains[ 2 ] = new cDomainVector( vecAreaDomain );
				delete vecAreaDomain[ 0 ];
				delete vecAreaDomain[ 1 ];
				//create matrix vector domain
				vecFibMatrixDomains[ 3 ] = cDomainVectorBasis::createGoodDomain(
					mapMatrixExistingVectors[ uiNumberOfDomain ] );
				
				cDomainVector * pVectorFibMatrixDomain = new cDomainVector(
					vecFibMatrixDomains );
				delete vecFibMatrixDomains[ 0 ];
				delete vecFibMatrixDomains[ 1 ];
				delete vecFibMatrixDomains[ 2 ];
				delete vecFibMatrixDomains[ 3 ];
				
				valueDomains.addDomain( typeFibMatrix, *pVectorFibMatrixDomain );
				delete pVectorFibMatrixDomain;
			}
		}//end for all domain numbers
	}//end if create matrix domain

#ifdef FEATURE_GENERATE_NEEDED_DOMAINS
	//generate needed domains for the sub-root-objects
	for ( list< pair< longFib, cRoot * > >::iterator
			itrActualRootElement = liSubRootObjects.begin();
			itrActualRootElement != liSubRootObjects.end();
			itrActualRootElement++ ){
		
		if ( itrActualRootElement->second ){
			itrActualRootElement->second->generateNeededDomains();
		}
	}
#endif//FEATURE_GENERATE_NEEDED_DOMAINS

	DEBUG_OUT_L2(<<"cRoot::generateNeededDomains() done"<<endl<<flush);
}


/**
 * @return the count of input variables for the main Fib-object of
 * 	this root-object
 */
unsignedIntFib cRoot::getNumberOfInputVariables() const{
	return liInputVariables.size();
}


/**
 * This method sets the number of input variables, the main Fib-object
 * of this root-object should have, to the given number. It will
 * create or delete variables as necessary.
 * Standardvalue of new varibles is the nullvalue of the standarddomain
 * for input variables. Variables which are still in use can't be 
 * deleted. The delete process will beginn on the end of the input 
 * variablen list and stop if enght variables are deleted or an
 * variable can't be deleted.
 * 
 * @param uiNumberOfInputVariables the number of input variables the main
 * 	Fib-object of this root-object should have
 * @return true if the number of input variables is set to the given
 * 	value, else false
 */
bool cRoot::setNumberOfInputVariables( unsignedIntFib uiNumberOfInputVariables ){
	
	if ( liInputVariables.size() < uiNumberOfInputVariables ){
		/*the number of input variables is to low
		-> create new input variables till ther count is
		uiNumberOfInputVariables*/
		
		//get the domain for the input variable
		cDomains valueDomains = getValidValueDomains();
		
		while ( liInputVariables.size() < uiNumberOfInputVariables ){
			cTypeInVar typeActualInVar( liInputVariables.size() );
			
			cDomainSingle * actualInVarDomain = (cDomainSingle*)(
				valueDomains.getDomainForElement( typeActualInVar ) );
			bool bStandardDomain = false;
			if ( actualInVarDomain == NULL ){
				actualInVarDomain = (cDomainSingle*)(
					typeActualInVar.getStandardDomain() );
				bStandardDomain = true;
			}
			
			liInputVariables.push_back( make_pair( new cFibVariable( this ),
				actualInVarDomain->getNull() ) );
			
			if ( bStandardDomain ){
				delete actualInVarDomain;
			}

		}
	}else if ( uiNumberOfInputVariables < liInputVariables.size() ){
		/* the number of input variables is to high
		-> delete input variables from the end of the input variables list
		till ther count is uiNumberOfInputVariables or an input variable
		can't deleted*/
		while ( uiNumberOfInputVariables < liInputVariables.size() ){
			if ( liInputVariables.back().first->getNumberOfUsingElements() == 0 ){
				//variable not used -> delete it
				delete (liInputVariables.back().first);
				liInputVariables.pop_back();
			}else{//variable is used -> can't delete it
				return false;
			}
		}
	}//else the number of input variables is correct
	
	return true;
}


/**
 * @return a list with the inputvariables of this root-object.
 */
list<cFibVariable*> cRoot::getInputVariables(){

	list<cFibVariable*> liVariables;
	for ( list< pair< cFibVariable *, doubleFib > >::iterator
			itrActualVariable = liInputVariables.begin();
			itrActualVariable != liInputVariables.end();
			itrActualVariable++ ){
		liVariables.push_back( itrActualVariable->first );
	}
	return liVariables;
}


/**
 * @param uiNumberOfInputVariable the number of the inputvariable to
 * 	return
 * @return the uiNumberOfInputVariable inputvariable of this root-object
 */
cFibVariable * cRoot::getInputVariable( unsignedIntFib uiNumberOfInputVariable ){
	
	if ( ( uiNumberOfInputVariable < 1 ) ||
			( getNumberOfInputVariables() < uiNumberOfInputVariable )){
		//no such input variable
		return NULL;
	}
	//find the correct variable
	list< pair< cFibVariable *, doubleFib > >::iterator itrActualVariable;
	for ( itrActualVariable = liInputVariables.begin();
			itrActualVariable != liInputVariables.end() &&
			uiNumberOfInputVariable != 1;
			itrActualVariable++, uiNumberOfInputVariable-- ){
		//nothing to do
	}
	if ( uiNumberOfInputVariable == 1 ){
		//return the actual variable
		return (itrActualVariable->first);
	}
	return NULL;
}


/**
 * @param uiNumberOfInputVariable the number of the inputvariable for
 * 	which the standardvalue is to be return
 * @return the standardvalue of the uiNumberOfInputVariable
 * 	inputvariable of this root-object
 */
doubleFib cRoot::getStandardValueOfInputVariable(
		unsignedIntFib uiNumberOfInputVariable ) const{
	
	if ( ( uiNumberOfInputVariable < 1 ) ||
			( getNumberOfInputVariables() < uiNumberOfInputVariable )){
		//no such input variable
		return (doubleFib)(0.0);
	}
	//find the correct variable
	list< pair< cFibVariable * , doubleFib > >::const_iterator itrActualVariable;
	for ( itrActualVariable = liInputVariables.begin();
			itrActualVariable != liInputVariables.end() &&
			uiNumberOfInputVariable != 1;
			itrActualVariable++, uiNumberOfInputVariable-- ){
		//nothing to do
	}
	if ( uiNumberOfInputVariable == 1 ){
		//return standardvalue of the actual variable
		return itrActualVariable->second;
	}
	return (doubleFib)(0.0);
}


/**
 * This Method sets the standardvalue of uiNumberOfInputVariable
 * inputvariable.
 *
 * @param uiNumberOfInputVariable the number of the inputvariable for
 * 	which the standardvalue is to be set
 * @param dValue the value to which the standardvalue is to be set
 * @return true if the standardvalue of the uiNumberOfInputVariable
 * 	inputvariable of this root-object is set do dValue,
 * 	else false
 */
bool cRoot::setStandardValueOfInputVariable(
		unsignedIntFib uiNumberOfInputVariable, doubleFib dValue ){
	
	if ( ( uiNumberOfInputVariable < 1 ) ||
			( getNumberOfInputVariables() < uiNumberOfInputVariable )){
		//no such input variable
		return false;
	}
	//find the correct variable
	list< pair< cFibVariable *, doubleFib > >::iterator itrActualVariable;
	unsignedIntFib uiDistanceToInputVariable = uiNumberOfInputVariable;
	for ( itrActualVariable = liInputVariables.begin();
			itrActualVariable != liInputVariables.end() &&
			uiDistanceToInputVariable != 1;
			itrActualVariable++, uiDistanceToInputVariable-- ){
		//nothing to do
	}
	bool bReturnValue = false;
	if ( uiDistanceToInputVariable == 1 ){
		//set standardvalue of the actual variable
		//check if the standardvalue is in the domain of the inputvariable
		cTypeInVar typeActualInVar( uiNumberOfInputVariable );
		
		cDomainSingle * actualInVarDomain = (cDomainSingle*)(
			domains.getDomainForElement( typeActualInVar ) );
		bool bStandardDomain = false;
		if ( actualInVarDomain == NULL ){
			actualInVarDomain = (cDomainSingle*)(
				valueDomains.getDomainForElement( typeActualInVar ) );
		}
		if ( actualInVarDomain == NULL ){
			actualInVarDomain = (cDomainSingle*)(
				typeActualInVar.getStandardDomain() );
			bStandardDomain = true;
		}
		if ( actualInVarDomain->isElement( dValue ) ){
			//set standardvalue
			itrActualVariable->second = dValue;
			itrActualVariable->first->setValue( dValue );

			bReturnValue = true;
		}
		
		if ( bStandardDomain ){
			delete actualInVarDomain;
		}
	}
	return bReturnValue;
}

#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR


/**
 * @return the count of extern subobjects this root-object has
 */
unsignedIntFib cRoot::getNumberOfExternSubobjects() const{
	
	//search in the valid domains for the greatest subobject number and return it
	const cDomains validDomains = getValidValueDomains();
	unsignedIntFib uiMaxNumberOfExtSubobject = 0;
	const unsignedIntFib uiNumberOfDomains = validDomains.getNumberOfDomains();
	for ( unsignedIntFib uiActualDomain = 1; uiActualDomain <= uiNumberOfDomains;
			uiActualDomain++ ){
		
		const cTypeElement * pTypeElement = validDomains.getType( uiActualDomain );
		if ( ( pTypeElement != NULL ) && ( pTypeElement->getType() == 13 ) ){
			//the type is a cTypeFibSet type
			const unsignedIntFib uiNumberOfExtSubobjectDomain =
				((cTypeExtSubobject*)(pTypeElement))->getNumberOfExtSubobject();
			if ( uiMaxNumberOfExtSubobject < uiNumberOfExtSubobjectDomain ){
				uiMaxNumberOfExtSubobject = uiNumberOfExtSubobjectDomain;
			}
		}
	}//end for search all domains for maximal external subobject domain
	
	return uiMaxNumberOfExtSubobject;
}


/**
 * This method returns the number of output variables of the
 * uiNumberOfExtSubobject'th extern subobject in this root-object, or
 * 0 if the subobject dosn't exists.
 *
 * @param uiNumberOfExtSubobject the number of the subobject for which
 * 	the number of output variables is to be returned
 * @return the count of output variables of the uiNumberOfExtSubobject'th
 * 	extern subobject in this root-object, or 0 if the
 * 	subobject dosn't exists
 */
unsignedIntFib cRoot::getNumberOfOutputVariables(
		unsignedIntFib uiNumberOfExtSubobject ) const{
	
	//get domain for actual external subobject
	const cDomains validDomains = getValidValueDomains();

	//get domain for actual external subobject
	const cTypeExtSubobject typeExtSubobject( uiNumberOfExtSubobject );
	const cDomain * pDomainExtSubobject =
		validDomains.getDomainForElement( typeExtSubobject );
	
	if ( pDomainExtSubobject == NULL ){
		//no domain -> return 0
		return 0;
	}
	if ( ! pDomainExtSubobject->isVector() ){
		//no domain -> return 0
		return 0;
	}
	const cDomainVectorBasis * pDomainVectorExtSubobject =
		(const cDomainVectorBasis*)pDomainExtSubobject;
	
	return pDomainVectorExtSubobject->getNumberOfElements();
}


/**
 * This method checks the extern subobject of this root-object.
 * It is checked if:
 * 	- every subobject in main -Fib-object of this root-object
 * 	is also defined in the root-object
 * 	- the number of output values in the definition and the
 * 	subobject Fib element(s) are the same
 * 	- ever subobject which is defined in this root-object is used
 * 	somewhere in the main -Fib-object
 *
 * @param iErrorNumber a pointer to an integerfild, wher an errornumber
 * 	can be stored; or NULL (standardvalue) if no errornumber should
 * 	be given back
 * 	possible errornumbers:
 * 		- 0 no error, everithing is OK
 * 		- -1 no main -Fib-object
 * 		- -10 an subobject definition is missing
 * 		- -11 different number of output values
 * 		- -12 not every defined subobject is used
 * 		- -13 the numbers of the subobjects dosn't go from 1 till n
 * @return the number of the first not correct extern subobject in
 * 	this root-object or 0 if every subobject is OK
 */
unsignedIntFib cRoot::checkExternSubobjects(
		intFib * iErrorNumber ){
	//implement when cExtSubobject is implemented
	DEBUG_OUT_L2(<<"cRoot("<<this<<")::checkExternUnderObjects() started"<<endl<<flush);
	
	if ( pMainFibObject == NULL ){
		DEBUG_OUT_L2(<<"cRoot("<<this<<")::checkExternUnderObjects() done no main Fib object -> no external subobjects"<<endl<<flush);
		if ( iErrorNumber != NULL ){
			(*iErrorNumber) = -1;
		}
		return 0;
	}
	
	/*evalue and correct output value counts for the subobjects*/
	vector< longFib > vecExtSubobjCountOutVars;
	unsignedLongFib ulMaxSubobjectNumber = 0;
	
	unsignedLongFib uiElementsToCheck = pMainFibObject->getNumberOfElements( 's' );
	//for every Fib element in the Fib-object
	for ( cExtSubobject * pActualSubobject = ((cExtSubobject*)(pMainFibObject->getNextFibElement( 's' )));
			( pActualSubobject != NULL ) && ( 0 < uiElementsToCheck );
			pActualSubobject = ((cExtSubobject*)(pActualSubobject->getNextFibElement( 's' ))),
			uiElementsToCheck-- ){
		
		//extern subobject element
		const unsignedIntFib uiNumberSubobject =
			pActualSubobject->getNumberSubobject();
		cFibVector * pExtSubobjectVector =
			pActualSubobject->getOutputVector();
		
		const unsignedIntFib uiNumberOfOutputVariables =
			pExtSubobjectVector->getNumberOfElements();
		
		DEBUG_OUT_L3(<<"   number of subobject "<<uiNumberSubobject<<"; number of output values "<<uiNumberOfOutputVariables<<endl<<flush);
		if ( ulMaxSubobjectNumber < uiNumberSubobject ){
			//new maximal / greatest subobject number
			DEBUG_OUT_L3(<<"   setting new maximal / greatest subobject number"<<endl<<flush);
			ulMaxSubobjectNumber = uiNumberSubobject;
		}
		if ( vecExtSubobjCountOutVars.size() < uiNumberSubobject ){
			if ( uiNumberSubobject < MAX_SUBOBJECTS ){
				
				vecExtSubobjCountOutVars.resize( uiNumberSubobject, -1 );
			}else{//MAX_SUBOBJECTS < uiNumberSubobject -> to much subobjects
				//the actual subobject is the first not correct subobject
				if ( iErrorNumber != NULL ){
					(*iErrorNumber) = -13;
				}
				return pActualSubobject->getNumberOfElement();
			}
		}//enought subobjects in root definition exists
		if ( uiNumberSubobject == 0 ){
			//wrong subobject number
			//the actual subobject is the first not correct subobject
			if ( iErrorNumber != NULL ){
				(*iErrorNumber) = -13;
			}
			return pActualSubobject->getNumberOfElement();
		}
		if ( ( 0 < uiNumberSubobject ) &&
				( uiNumberSubobject <= vecExtSubobjCountOutVars.size() ) ){
			
			if ( vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] != uiNumberOfOutputVariables ){
				if ( vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] != -1 ){
					//set different number of subobjects
					//the actual subobject is the first not correct subobject
					if ( iErrorNumber != NULL ){
						(*iErrorNumber) = -11;
					}
					return pActualSubobject->getNumberOfElement();
				}
				if ( vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] < uiNumberOfOutputVariables ){
					//store number of maximal output values for the subobject
					DEBUG_OUT_L4(<<"   setting number of output values of the subobject "<<uiNumberSubobject<<" to the number "<<uiNumberOfOutputVariables<<endl<<flush);
					vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] =
						uiNumberOfOutputVariables;
				}
			}//else number of output values correct
		}
	}
	
	DEBUG_OUT_L2(<<"cRoot::checkExternUnderObjects() done"<<endl<<flush);
	return 0;
}


/**
 * This method generates the extern subobject definitions for this
 * root-object.
 * possible errors which aborts the generation process:
 * 	- the number of output values in the the subobject
 *		Fib elements are not the same
 * 	-the numbers of the subobjects dosn't go from 1 till n
 *
 * @param iErrorNumber a pointer to an integerfild, wher an errornumber
 * 	can be stored; or NULL (standardvalue) if no errornumber should
 * 	be given back
 * 	possible errornumbers:
 * 		- 0 no error, everithing is OK
 * 		- -1 no main -Fib-object
 * 		- -11 different number of output values
 * 		- -13 the numbers of the subobjects dosn't go from 1 till n
 * @return the number of the first not correct extern subobject in
 * 	this root-object or 0 if every subobject is OK
 */
unsignedIntFib cRoot::generateExternSubobjectsDefinitions(
		intFib * iErrorNumber ){
	//implement when cExtSubobject is implemented
	DEBUG_OUT_L2(<<"cRoot("<<this<<")::generateExternSubobjectsDefinitions() started"<<endl<<flush);
	
	if ( pMainFibObject == NULL ){
		DEBUG_OUT_L2(<<"cRoot("<<this<<")::generateExternSubobjectsDefinitions() done no main Fib object -> no external subobjects"<<endl<<flush);
		if ( iErrorNumber != NULL ){
			(*iErrorNumber) = -1;
		}
		return 0;
	}
	unsignedIntFib uiFirstNotCorrectSubobject = 0;
	
	/*evalue and correct output value counts for the subobjects*/
	map< unsignedLongFib, longFib > mapExtSubobjCountOutVars;
	map< unsignedLongFib, list< cFibVector * > > mapExtSubobjectOutputVectors;
	unsignedLongFib ulMaxSubobjectNumber = 0;
	
	unsignedLongFib uiElementsToCheck = pMainFibObject->getNumberOfElements( 's' );
	//for every Fib element in the Fib-object
	for ( cExtSubobject * pActualSubobject = ((cExtSubobject*)(pMainFibObject->getNextFibElement( 's' )));
			( pActualSubobject != NULL ) && ( 0 < uiElementsToCheck );
			pActualSubobject = ((cExtSubobject*)(pActualSubobject->getNextFibElement( 's' ))),
			uiElementsToCheck-- ){
		
		//extern subobject element
		const unsignedIntFib uiNumberSubobject =
			pActualSubobject->getNumberSubobject();
		cFibVector * pExtSubobjectVector =
			pActualSubobject->getOutputVector();
		
		const unsignedIntFib uiNumberOfOutputVariables =
			pExtSubobjectVector->getNumberOfElements();
		
		mapExtSubobjectOutputVectors[ uiNumberSubobject ].push_back(
				pExtSubobjectVector );
		
		DEBUG_OUT_L3(<<"   number of subobject "<<uiNumberSubobject<<"; number of output values "<<uiNumberOfOutputVariables<<endl<<flush);
		if ( ulMaxSubobjectNumber < uiNumberSubobject ){
			//new maximal / greatest subobject number
			DEBUG_OUT_L3(<<"   setting new maximal / greatest subobject number"<<endl<<flush);
			ulMaxSubobjectNumber = uiNumberSubobject;
		}
		if ( uiNumberSubobject == 0 ){
			//wrong subobject number
			if ( uiFirstNotCorrectSubobject == 0 ){
				//the actual subobject is the first not correct subobject
				uiFirstNotCorrectSubobject = pActualSubobject->getNumberOfElement();
				if ( iErrorNumber != NULL ){
					(*iErrorNumber) = -13;
				}
			}
		}else{
			const map< unsignedLongFib, longFib >::iterator itrActualSubobject =
				mapExtSubobjCountOutVars.find( uiNumberSubobject );
				
			if ( itrActualSubobject != mapExtSubobjCountOutVars.end() ){
				//subobject allready found
				if ( mapExtSubobjCountOutVars[ uiNumberSubobject ] != uiNumberOfOutputVariables ){
					//different number of subobject output values
					if ( uiFirstNotCorrectSubobject == 0 ){
						//the actual subobject is the first not correct subobject
						uiFirstNotCorrectSubobject = pActualSubobject->getNumberOfElement();
						if ( iErrorNumber != NULL ){
							(*iErrorNumber) = -11;
						}
					}
				}//else correct number of output values
			}else{//subobject found the first time
				//store number of maximal output values for the subobject
				DEBUG_OUT_L4(<<"   setting number of output values of the subobject "<<uiNumberSubobject<<" to the number "<<uiNumberOfOutputVariables<<endl<<flush);
				mapExtSubobjCountOutVars[ uiNumberSubobject ] =
					uiNumberOfOutputVariables;
			}
		}
	}
	
	//generate needed definitions for external subobject elements
	if ( ! mapExtSubobjCountOutVars.empty() ){
		//external subobject elements exists
		
		const cDomains validDomains = getValidValueDomains();

		//check number of output values for the subobjects
		for ( map< unsignedLongFib, longFib >::iterator
				itrActualSubobject = mapExtSubobjCountOutVars.begin();
				itrActualSubobject != mapExtSubobjCountOutVars.end();
				itrActualSubobject++ ){
			
			const unsignedIntFib uiNumberOfSubobject = itrActualSubobject->first;
			
			//get domain for actual external subobject
			const cTypeExtSubobject typeExtSubobject( uiNumberOfSubobject );
			const cDomain * pDomainExtSubobject =
				validDomains.getDomainForElement( typeExtSubobject );
			
			bool bAddNewDomain = false;
			if ( pDomainExtSubobject == NULL ){
				//no domain -> add one
				bAddNewDomain = true;
			}else if ( ! pDomainExtSubobject->isVector() ){
				//the domain is not a vector domain
				bAddNewDomain = true;
			}else{
				const cDomainVectorBasis * pDomainVectorExtSubobject =
					(const cDomainVectorBasis*)pDomainExtSubobject;
				if ( pDomainVectorExtSubobject->getNumberOfElements() !=
						mapExtSubobjCountOutVars[ uiNumberOfSubobject ] ){
					//the number of output values is wrong
					bAddNewDomain = true;
				}
			}//end if check actual external subobject domain
			
			if ( bAddNewDomain ){
				//delete existing domains from the 
				valueDomains.deleteDomain( typeExtSubobject );
				
				cDomainVectorBasis * pDomainExtSubobjectOutput =
					cDomainVectorBasis::createGoodDomain(
						mapExtSubobjectOutputVectors[ uiNumberOfSubobject ] );
				
				//add new domain
				domains.addDomain( typeExtSubobject, *pDomainExtSubobjectOutput );
				delete pDomainExtSubobjectOutput;
			}
		}//end for all subobject numbers
		DEBUG_OUT_L3(<<"domains for external subobject elements generated"<<endl<<flush);
	}
	
	DEBUG_OUT_L2(<<"cRoot::generateExternSubobjectsDefinitions() done"<<endl<<flush);
	return uiFirstNotCorrectSubobject;
}


#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR


/**
 * @return the count of extern subobjects this root-object has
 */
unsignedIntFib cRoot::getNumberOfExternSubobjects() const{
	return (unsignedIntFib)( liExternSubobjects.size() );
}


/**
 * This method sets the number of the extern subobjects this 
 * root-object has to the given value uiNumberOfExternUnderObjects.
 * It automaticly creates or delets extern subobjects to or from the
 * end of the extern subobjectslist, till uiNumberOfExternUnderObjects
 * subobjects exsists or the operation is not possible.
 * Underobjects wich are still in use/ still exists in the main -fib
 * -object of this root-object can't be deleted.
 * The number of output variables of the created subobjects will be
 * set to 0.
 *
 * @param uiNumberOfExternUnderObjects the number of extern
 * 	subobjects this root-object should have
 * @return true if the number of extern subobjects is set to
 * 	uiNumberOfExternUnderObjects, else false
 */
bool cRoot::setNumberOfExternSubobjects(
		unsignedIntFib uiNumberOfExternUnderObjects ){
	
	bool bReturn = true;
	if ( liExternSubobjects.size() < uiNumberOfExternUnderObjects ){
		
		if ( MAX_SUBOBJECTS < uiNumberOfExternUnderObjects ){
			//to much subobjects to set
			bReturn = false;
			uiNumberOfExternUnderObjects = MAX_SUBOBJECTS;
		}
		while ( liExternSubobjects.size() < uiNumberOfExternUnderObjects ){
			liExternSubobjects.push_back( (unsignedIntFib)( 0 ) );
		}
	}else if ( uiNumberOfExternUnderObjects < liExternSubobjects.size() ){
		//get biggest subobject number of an used subobject
		unsignedIntFib uiBiggestSubobjectNumber = 0;
		if ( pMainFibObject != NULL ){
			//beware to yust search in the main -Fib-object of this root-object
			unsignedLongFib uiElementsToCheck =
				pMainFibObject->getNumberOfElements( 's' );
			for ( cExtSubobject * pActualSubobject =
						(cExtSubobject*)(pMainFibObject->getNextFibElement( 's' ));
					( pActualSubobject != NULL ) && ( 0 < uiElementsToCheck );
					pActualSubobject = (cExtSubobject*)(pActualSubobject->getNextFibElement( 's' )),
					uiElementsToCheck-- ){
				
				const unsignedIntFib uiActualSubObjectNumber =
					pActualSubobject->getNumberSubobject();
				if ( uiBiggestSubobjectNumber < uiActualSubObjectNumber ){
					uiBiggestSubobjectNumber = uiActualSubObjectNumber;
				}
			}
		}
		
		while ( uiNumberOfExternUnderObjects < liExternSubobjects.size() ){
			if ( liExternSubobjects.size() <= uiBiggestSubobjectNumber ){
				//this subobject is still in use -> can't delete anymore
				return false;
			}//else the subobject cn be deleted
			liExternSubobjects.pop_back();
		}
	}//else the count of extern subobjects is correct
	
	return bReturn;
}


/**
 * This method returns the number of output variables of the
 * uiNumberOfUnderObject extern subobject in this root-object, or
 * 0 if the subobject dosn't exists.
 *
 * @param uiNumberOfUnderObject the number of the subobject for which
 * 	the number of output variables is to be returned
 * @return the count of output variables of the uiNumberOfUnderObject
 * 	extern subobject in this root-object, or 0 if the
 * 	subobject dosn't exists
 */
unsignedIntFib cRoot::getNumberOfOutputVariables(
		unsignedIntFib uiNumberOfUnderObject ) const{
	
	if ( ( uiNumberOfUnderObject < 1 ) ||
			( getNumberOfExternSubobjects() < uiNumberOfUnderObject ) ){
		//no such extern object
		return (unsignedIntFib)(0);
	}
	//find the correct extern object
	list< unsignedIntFib >::const_iterator itrActualExternObject;
	for ( itrActualExternObject = liExternSubobjects.begin();
			itrActualExternObject != liExternSubobjects.end() &&
			uiNumberOfUnderObject != 1;
			itrActualExternObject++, uiNumberOfUnderObject-- ){
		//nothing to do
	}
	if ( uiNumberOfUnderObject == 1 ){
		//return the number of output variables of the extern object
		return (*itrActualExternObject);
	}
	return (unsignedIntFib)(0);
}


/**
 * This method sets the number of output variables of the
 * uiNumberOfUnderObject extern subobject in this root-object to
 * the given value uiNumberOfVariables.
 *
 * @param uiNumberOfUnderObject the number of the subobject for which
 * 	the number of output variables is to be set
 * @param uiNumberOfVariables the number of output variables the
 * 	uiNumberOfUnderObject subobject of this root-object should have
 * @return true if the number of output variables of the
 * 	uiNumberOfUnderObject subobject was set to uiNumberOfVariables,
 * 	else false
 */
bool cRoot::setNumberOfOutputVariables(
		unsignedIntFib uiNumberOfUnderObject,
		unsignedIntFib uiNumberOfVariables ){
	
	if ( ( uiNumberOfUnderObject < 1 ) ||
			( getNumberOfExternSubobjects() < uiNumberOfUnderObject ) ){
		//no such extern object
		return false;
	}
	//find the correct extern object
	list< unsignedIntFib >::iterator itrActualExternObject;
	for ( itrActualExternObject = liExternSubobjects.begin();
			itrActualExternObject != liExternSubobjects.end() &&
			uiNumberOfUnderObject != 1;
			itrActualExternObject++, uiNumberOfUnderObject-- ){
		//nothing to do
	}
	if ( uiNumberOfUnderObject == 1 ){
		//return the number of output variables of the extern object
		(*itrActualExternObject) = uiNumberOfVariables;
		return true;
	}
	return false;
}


/**
 * This method checks the extern subobject of this root-object.
 * It is checked if:
 * 	- every subobject in main -Fib-object of this root-object
 * 	is also defined in the root-object
 * 	- the number of output variables in the definition and the
 * 	subobject Fib element(s) are the same
 * 	- ever subobject which is defined in this root-object is used
 * 	somewhere in the main -Fib-object
 *
 * @param iErrorNumber a pointer to an integerfild, wher an errornumber
 * 	can be stored; or NULL (standardvalue) if no errornumber should
 * 	be given back
 * 	possible errornumbers:
 * 		- 0 no error, everithing is OK
 * 		- -1 no main -Fib-object
 * 		- -10 an subobject definition is missing
 * 		- -11 different number of output variables
 * 		- -12 not every defined subobject is used
 * 		- -13 the numbers of the subobjects dosn't go from 1 till n
 * @return the number of the first not correct extern subobject in
 * 	this root-object or 0 if every subobject is OK
 */
unsignedIntFib cRoot::checkExternSubobjects(
		intFib * iErrorNumber ){
	//implement when cExtSubobject is implemented
	DEBUG_OUT_L2(<<"cRoot("<<this<<")::checkExternUnderObjects() started"<<endl<<flush);
	
	if ( pMainFibObject == NULL ){
		DEBUG_OUT_L2(<<"cRoot("<<this<<")::checkExternUnderObjects() done no main Fib object -> no external subobjects"<<endl<<flush);
		if ( iErrorNumber != NULL ){
			(*iErrorNumber) = -1;
		}
		return 0;
	}
	
	/*evalue and correct output variable counts for the subobjects*/
	vector< longFib > vecExtSubobjCountOutVars;
	unsignedLongFib ulMaxSubobjectNumber = 0;
	
	unsignedLongFib uiElementsToCheck = pMainFibObject->getNumberOfElements( 's' );
	//for every Fib element in the Fib-object
	for ( cExtSubobject * pActualSubobject = ((cExtSubobject*)(pMainFibObject->getNextFibElement( 's' )));
			( pActualSubobject != NULL ) && ( 0 < uiElementsToCheck );
			pActualSubobject = ((cExtSubobject*)(pActualSubobject->getNextFibElement( 's' ))),
			uiElementsToCheck-- ){
		
		//extern subobject element
		const unsignedIntFib uiNumberOfOutputVariables =
			pActualSubobject->getNumberOfOutputVariables();
			
		const unsignedIntFib uiNumberSubobject =
			pActualSubobject->getNumberSubobject();
		DEBUG_OUT_L3(<<"   number of subobject "<<uiNumberSubobject<<"; number of output variables "<<uiNumberOfOutputVariables<<endl<<flush);
		if ( ulMaxSubobjectNumber < uiNumberSubobject ){
			//new maximal / greatest subobject number
			DEBUG_OUT_L3(<<"   setting new maximal / greatest subobject number"<<endl<<flush);
			ulMaxSubobjectNumber = uiNumberSubobject;
		}
		if ( vecExtSubobjCountOutVars.size() < uiNumberSubobject ){
			if ( uiNumberSubobject < MAX_SUBOBJECTS ){
				
				vecExtSubobjCountOutVars.resize( uiNumberSubobject, -1 );
			}else{//MAX_SUBOBJECTS < uiNumberSubobject -> to much subobjects
				//the actual subobject is the first not correct subobject
				if ( iErrorNumber != NULL ){
					(*iErrorNumber) = -13;
				}
				return pActualSubobject->getNumberOfElement();
			}
		}//enought subobjects in root definition exists
		if ( uiNumberSubobject == 0 ){
			//wrong subobject number
			//the actual subobject is the first not correct subobject
			if ( iErrorNumber != NULL ){
				(*iErrorNumber) = -13;
			}
			return pActualSubobject->getNumberOfElement();
		}
		if ( ( 0 < uiNumberSubobject ) &&
				( uiNumberSubobject <= vecExtSubobjCountOutVars.size() ) ){
			
			if ( vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] != uiNumberOfOutputVariables ){
				if ( vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] != -1 ){
					//set different number of subobjects
					//the actual subobject is the first not correct subobject
					if ( iErrorNumber != NULL ){
						(*iErrorNumber) = -11;
					}
					return pActualSubobject->getNumberOfElement();
				}
				if ( vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] < uiNumberOfOutputVariables ){
					//store number of maximal output variables for the subobject
					DEBUG_OUT_L4(<<"   setting number of output variables of the subobject "<<uiNumberSubobject<<" to the number "<<uiNumberOfOutputVariables<<endl<<flush);
					vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] =
						uiNumberOfOutputVariables;
				}
			}//else number of output variables correct
		}
	}
	
	DEBUG_OUT_L2(<<"cRoot::checkExternUnderObjects() done"<<endl<<flush);
	return 0;
}


/**
 * This method generates the extern subobject definitions for this
 * root-object.
 * possible errors which aborts the generation process:
 * 	- the number of output variables in the the subobject
 *		Fib elements are not the same
 * 	-the numbers of the subobjects dosn't go from 1 till n
 *
 * @param iErrorNumber a pointer to an integerfild, wher an errornumber
 * 	can be stored; or NULL (standardvalue) if no errornumber should
 * 	be given back
 * 	possible errornumbers:
 * 		- 0 no error, everithing is OK
 * 		- -1 no main -Fib-object
 * 		- -11 different number of output variables
 * 		- -13 the numbers of the subobjects dosn't go from 1 till n
 * @return the number of the first not correct extern subobject in
 * 	this root-object or 0 if every subobject is OK
 */
unsignedIntFib cRoot::generateExternSubobjectsDefinitions(
		intFib * iErrorNumber ){
	//implement when cExtSubobject is implemented
	DEBUG_OUT_L2(<<"cRoot("<<this<<")::checkExternUnderObjects() started"<<endl<<flush);
	
	if ( pMainFibObject == NULL ){
		DEBUG_OUT_L2(<<"cRoot("<<this<<")::checkExternUnderObjects() done no main Fib object -> no external subobjects"<<endl<<flush);
		if ( iErrorNumber != NULL ){
			(*iErrorNumber) = -1;
		}
		return 0;
	}
	unsignedIntFib uiFirstNotCorrectSubobject = 0;
	
	/*evalue and correct output variable counts for the subobjects*/
	vector< longFib > vecExtSubobjCountOutVars;
	unsignedLongFib ulMaxSubobjectNumber = 0;
	
	unsignedLongFib uiElementsToCheck = pMainFibObject->getNumberOfElements( 's' );
	//for every Fib element in the Fib-object
	for ( cExtSubobject * pActualSubobject = ((cExtSubobject*)(pMainFibObject->getNextFibElement( 's' )));
			( pActualSubobject != NULL ) && ( 0 < uiElementsToCheck );
			pActualSubobject = ((cExtSubobject*)(pActualSubobject->getNextFibElement( 's' ))),
			uiElementsToCheck-- ){
		
		//extern subobject element
		const unsignedIntFib uiNumberOfOutputVariables =
			pActualSubobject->getNumberOfOutputVariables();
			
		const unsignedIntFib uiNumberSubobject =
			pActualSubobject->getNumberSubobject();
		DEBUG_OUT_L3(<<"   number of subobject "<<uiNumberSubobject<<"; number of output variables "<<uiNumberOfOutputVariables<<endl<<flush);
		if ( ulMaxSubobjectNumber < uiNumberSubobject ){
			//new maximal / greatest subobject number
			DEBUG_OUT_L3(<<"   setting new maximal / greatest subobject number"<<endl<<flush);
			ulMaxSubobjectNumber = uiNumberSubobject;
		}
		if ( vecExtSubobjCountOutVars.size() < uiNumberSubobject ){
			if ( uiNumberSubobject < MAX_SUBOBJECTS ){
				
				vecExtSubobjCountOutVars.resize( uiNumberSubobject, -1 );
			}else{//MAX_SUBOBJECTS < uiNumberSubobject -> to much subobjects
				if ( uiFirstNotCorrectSubobject == 0 ){
					//the actual subobject is the first not correct subobject
					uiFirstNotCorrectSubobject = pActualSubobject->getNumberOfElement();
					if ( iErrorNumber != NULL ){
						(*iErrorNumber) = -13;
					}
				}
			}
		}//enought subobjects in root definition exists
		if ( uiNumberSubobject == 0 ){
			//wrong subobject number
			if ( uiFirstNotCorrectSubobject == 0 ){
				//the actual subobject is the first not correct subobject
				uiFirstNotCorrectSubobject = pActualSubobject->getNumberOfElement();
				if ( iErrorNumber != NULL ){
					(*iErrorNumber) = -13;
				}
			}
		}
		if ( ( 0 < uiNumberSubobject ) &&
				( uiNumberSubobject <= vecExtSubobjCountOutVars.size() ) ){
			
			if ( vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] != uiNumberOfOutputVariables ){
				if ( vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] != -1 ){
					//set different number of subobjects
					if ( uiFirstNotCorrectSubobject == 0 ){
						//the actual subobject is the first not correct subobject
						uiFirstNotCorrectSubobject = pActualSubobject->getNumberOfElement();
						if ( iErrorNumber != NULL ){
							(*iErrorNumber) = -11;
						}
					}
				}
				if ( vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] < uiNumberOfOutputVariables ){
					//store number of maximal output variables for the subobject
					DEBUG_OUT_L4(<<"   setting number of output variables of the subobject "<<uiNumberSubobject<<" to the number "<<uiNumberOfOutputVariables<<endl<<flush);
					vecExtSubobjCountOutVars[ uiNumberSubobject - 1 ] =
						uiNumberOfOutputVariables;
				}
			}//else number of output variables correct
		}
	}
	
	//generate needed definitions for external subobject elements
	if ( ! vecExtSubobjCountOutVars.empty() ){
		//external subobject elements exists

		//check external subobject number
		const unsignedIntFib uiNumberSubobjectCounts =
			vecExtSubobjCountOutVars.size();
		if ( getNumberOfExternSubobjects() < uiNumberSubobjectCounts ){
			/*actual number of external subobjects to low
			-> set it to the maximal / greates external subobject number*/
			setNumberOfExternSubobjects( uiNumberSubobjectCounts );
		}
		//check number of output variables for the subobjects
		for ( unsignedIntFib uiNumberOfSubobject = 1;
				uiNumberOfSubobject <= uiNumberSubobjectCounts;
				uiNumberOfSubobject++ ){
			
			if ( vecExtSubobjCountOutVars[ uiNumberOfSubobject - 1 ] == -1 ){
				//no such external subobject found
				continue;
			}
			if ( vecExtSubobjCountOutVars[ uiNumberOfSubobject - 1 ] <
					getNumberOfOutputVariables( uiNumberOfSubobject ) ){
				/*correct the number of output variables of the subobject to
				the correct value*/
				setNumberOfOutputVariables( uiNumberOfSubobject,
					vecExtSubobjCountOutVars[ uiNumberOfSubobject - 1 ] );
			}//number of output variables for the subobject correct
		}
		DEBUG_OUT_L3(<<"domains for external subobject elements generated"<<endl<<flush);
	}
	
	DEBUG_OUT_L2(<<"cRoot::checkExternUnderObjects() done"<<endl<<flush);
	return uiFirstNotCorrectSubobject;
}

#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR


/**
 * @return the count of sub-root-objects in this root-object
 */
unsignedIntFib cRoot::getNumberOfSubRootObjects() const{
	return (unsignedIntFib)( liSubRootObjects.size() );
}


/**
 * This method returns the uiNumberOfUnderObject sub-root-object
 * of this root-element or the pair <0,NULL>, if non such exists.
 * The returned pair first element is the identifier of the sub-root
 * -object and the second is a pointer to the sub-root-object.
 *
 * @param uiNumberOfUnderObject the number of the sub-root-object to
 * 	return
 * @return the uiNumberOfUnderObject't sub-root-objects of this
 * 	root-object as an (idenitifier, root-object -pointer) -pair or
 * 	the pair <0,NULL>, if non such exists
 */
pair<longFib, cRoot*> cRoot::getSubRootObject( unsignedIntFib uiNumberOfUnderObject ){

	if ( ( uiNumberOfUnderObject < 1 ) ||
			( getNumberOfSubRootObjects() < uiNumberOfUnderObject ) ){
		//no such sub-root-object
		return make_pair( 0, (cRoot*)(NULL) );
	}
	//find the correct sub-root-object
	list< pair< longFib, cRoot * > >::iterator itrActualSubRootObject;
	for ( itrActualSubRootObject = liSubRootObjects.begin();
			itrActualSubRootObject != liSubRootObjects.end() &&
			uiNumberOfUnderObject != 1;
			itrActualSubRootObject++, uiNumberOfUnderObject-- ){
		//nothing to do
	}
	if ( uiNumberOfUnderObject == 1 ){
		//return the sub-root-object
		return (*itrActualSubRootObject);
	}
	return make_pair( 0, (cRoot*)(NULL) );
}


/**
 * This method returns the number of the sub-root-object with the
 * identifier lIdentifier in this root-element or 0 if non such exists.
 *
 * @param lIdentifier identifier of the sub-root-object for which
 * 	the number should be returned return
 * @return the number of the sub-root-object with the identifier
 * 	lIdentifier in this root-element or 0 if non such exists
 */
unsignedIntFib cRoot::getSubRootObjectNumber( longFib lIdentifier ) const{

	//find the correct sub-root-object
	unsignedIntFib uiNumberOfUnderObject = 1;
	list< pair< longFib, cRoot * > >::const_iterator itrActualSubRootObject;
	for ( itrActualSubRootObject = liSubRootObjects.begin();
			itrActualSubRootObject != liSubRootObjects.end();
			itrActualSubRootObject++, uiNumberOfUnderObject++ ){
		
		if ( itrActualSubRootObject->first == lIdentifier ){
			//sub-root-object with the lIdentifier found
			return uiNumberOfUnderObject;
		}
	}//no sub-root-object with the given identifier lIdentifier
	return 0;
}


/**
 * This method returns the sub-root-object with the identifier
 * lIdentifier in this root-element or NULL if non such exists.
 *
 * @param lIdentifier identifier of the sub-root-object which
 * 	should be returned return
 * @return the sub-root-object with the identifier lIdentifier
 * 	in this root-element or NULL if non such exists
 */
cRoot * cRoot::getSubRootObjectForIdentifier( longFib lIdentifier ){
	//find the correct sub-root-object
	for ( list< pair< longFib, cRoot * > >::iterator
			itrActualSubRootObject = liSubRootObjects.begin();
			itrActualSubRootObject != liSubRootObjects.end();
			itrActualSubRootObject++ ){
		
		if ( itrActualSubRootObject->first == lIdentifier ){
			//sub-root-object with the lIdentifier found
			return itrActualSubRootObject->second;
		}
	}//no sub-root-object with the given identifier lIdentifier
	return NULL;
}


/**
 * This method adds the given root-object to the sub-root-object
 * -list of this root-element.
 * This will fail if:
 * 	- ther is no root-object (rootObject=NULL)
 * 	- the identifier lIdentifier is allready in use somewher in this
 * 	wool object
 *
 * @param lIdentifier the identifier the root-object should have
 * @param pRootObject a pointer to the root-object to add; the object
 * 	will not be copied, so don't delete it
 * @param uiPosition the position on which the root-object is to insert
 * 	in this root-element sub-object -list (counting begins with 1)
 * @return true if the root-object pRootObject was inserted, else false
 */
bool cRoot::addSubRootObject( longFib lIdentifier, cRoot * pRootObject,
		unsignedIntFib uiPosition ){

	if ( getSubRootObjectForIdentifier( lIdentifier ) != NULL ){
		//the lIdentifier allready exists
		return false;
	}
	if ( pRootObject == NULL ){
		//nothing to insert
		return false;
	}
#ifdef FEATURE_FAST_UPDATE
	if ( pRootObject->pSuperiorElement != NULL ){
		pRootObject->pSuperiorElement->cutConnectionsTo(
			pRootObject );
	}
#endif //FEATURE_FAST_UPDATE
	if ( uiPosition <= 1 ){
		//add the sub-root-object to the front of the sub-root-object list
		liSubRootObjects.push_front( make_pair( lIdentifier, pRootObject) );
		
		/*add the sub-root-object to the subobject -list an the second
		position (first is the main -Fib-object)*/
		list< cFibElement * >::iterator itrActualUnderObject =
			fibUnderObjects.begin();
		itrActualUnderObject++;
		fibUnderObjects.insert( itrActualUnderObject, pRootObject );
		
	}else if ( getNumberOfSubRootObjects() < uiPosition ){
		//add the sub-root-object to the end of the sub-root-object list
		liSubRootObjects.push_back( make_pair( lIdentifier, pRootObject ) );
		fibUnderObjects.push_back( pRootObject );
		
	}else{
		//insert the sub root object on the correct position
		list< pair< longFib, cRoot * > >::iterator itrActualSubRootObject;
		list< cFibElement * >::iterator itrActualUnderObject =
			fibUnderObjects.begin();
		itrActualUnderObject++;//first subobject is the main fib object
		for ( itrActualSubRootObject = liSubRootObjects.begin();
				itrActualSubRootObject != liSubRootObjects.end() &&
				itrActualUnderObject != fibUnderObjects.end() &&
				uiPosition != 1;
				itrActualSubRootObject++, itrActualUnderObject++ , uiPosition-- ){
			//nothing to do
		}
		liSubRootObjects.insert( itrActualSubRootObject,
			make_pair( lIdentifier, pRootObject ) );
		fibUnderObjects.insert( itrActualUnderObject, pRootObject );
	}
	//update the values
#ifdef FEATURE_FAST_UPDATE
	pRootObject->pSuperiorElement = this;
	
	cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( pRootObject );
	fibObjectCountsDelta.uiNumberOfObjectpoints++;
	updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
	pRootObject->pSuperiorElement = this;
	updateAllValues();
#endif //FEATURE_FAST_UPDATE
	return true;
}


/**
 * This method deletes the uiSubRootObjectNumber'th sub-root-object
 * in this root-element.
 *
 * @param uiSubRootObjectNumber the number of the sub-root-object in
 * 	the sub-root-object -list to delete
 * @param bDeleteOld if true the sub-root-object will be removed from
 * 	the memory, else yust the reference will be removed from this
 * 	root-element; default is true
 * @return true if the uiSubRootObjectNumber'th sub root-object was
 * 	deleted, else false
 */
bool cRoot::deleteSubRootObject( unsignedIntFib uiSubRootObjectNumber,
		bool bDeleteOld ){
	
	if ( ( uiSubRootObjectNumber < 1 ) ||
			( getNumberOfSubRootObjects() < uiSubRootObjectNumber ) ){
		//no such sub-root-object
		return false;
	}
	//find the correct sub-root-object
	list< pair< longFib, cRoot * > >::iterator itrActualSubRootObject;
	for ( itrActualSubRootObject = liSubRootObjects.begin();
			itrActualSubRootObject != liSubRootObjects.end() &&
			uiSubRootObjectNumber != 1;
			itrActualSubRootObject++, uiSubRootObjectNumber-- ){
		//nothing to do
	}
	if ( uiSubRootObjectNumber == 1 ){
		//delete the sub-root-object
		
		cRoot * pRootObjectToDelete = itrActualSubRootObject->second;
		
		//remove the sub-root-object from the sub-root-element -list
		liSubRootObjects.erase( itrActualSubRootObject );
		//remove the sub-root-object from the subobject -list
		for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			if ( (*actualUnderObject) == pRootObjectToDelete ){
				//correct sub-root-element/ subobject found
				fibUnderObjects.erase( actualUnderObject );
				break;
			}
		}
#ifdef FEATURE_FAST_UPDATE
		//update branch counts
		cFibObjectCounts fibObjectCountsDelta;
		fibObjectCountsDelta -= evalueCountersForObject( pRootObjectToDelete );
		fibObjectCountsDelta.uiNumberOfObjectpoints--;
		updateAllCounters( fibObjectCountsDelta );
		
		if ( pRootObjectToDelete->pSuperiorElement == this ){
			pRootObjectToDelete->pSuperiorElement = NULL;
			if ( bDeleteOld ){
				pRootObjectToDelete->deleteObject();
			}//else don't delete
		}
#else //FEATURE_FAST_UPDATE
		if ( bDeleteOld ){
			//remove connections of pOldFibObject to this Fib-object
			pRootObjectToDelete->pPreviousFibElement = NULL;
			pRootObjectToDelete->pSuperiorElement = NULL;
			
			cFibElement * pLastFibElementInOld =
				pRootObjectToDelete->getFibElement(
					pRootObjectToDelete->getNumberOfElements() - 1 );
			
			if ( pLastFibElementInOld ){
				pLastFibElementInOld->pNextFibElement = NULL;
			}
			
			deleteObject( pRootObjectToDelete );
		}//else don't delete
		updateAllValues();
#endif //FEATURE_FAST_UPDATE
		return true;
	}
	return false;
}


/**
 * This method returns all identifiers of all sub-root-objects in
 * this root-element.
 *
 * @return all identifiers of all sub-root-objects in this root-element
 */
list<longFib> cRoot::getAllSubRootObjectIdentifiers() const{

	list<longFib> liIdentifiers;
	for ( list< pair< longFib, cRoot * > >::const_iterator
			itrActualSubRootObject = liSubRootObjects.begin();
			itrActualSubRootObject != liSubRootObjects.end();
			itrActualSubRootObject++ ){
		
		liIdentifiers.push_back( itrActualSubRootObject->first );
	}
	return liIdentifiers;
}


/**
 * @return a set with all database identifiers that are given in this
 * 	root-element as used database objects 
 * 	@see setDatabaseIdentifiers
 */
set< longFib > cRoot::getUsedDatabaseIdentifiers() const{
	
	return setDatabaseIdentifiers;
}


/**
 * This method adds the given database identifier to the used database 
 * identifiers of this root-element.
 * @see setDatabaseIdentifiers
 * 
 * @param lIdentifier the identifer of a database object to add as used
 * 	by this root-element
 */
void cRoot::addUsedDatabaseIdentifier( const longFib lIdentifier ){
	
	setDatabaseIdentifiers.insert( lIdentifier );
}


/**
 * This method deletes the given database identifier from the used 
 * database identifiers of this root-element.
 * @see setDatabaseIdentifiers
 * 
 * @param lIdentifier the identifer of a database object to delete
 * @return true if the identifier was deleted, else false
 */
bool cRoot::deleteUsedDatabaseIdentifier( const longFib lIdentifier ){
	
	return (setDatabaseIdentifiers.erase( lIdentifier ) != 0);
}


/**
 * @return the checksumvektor of this root-element or NULL if no such
 * 	exists
 */
cVectorChecksum * cRoot::getChecksum(){
	return pChecksum;
}


/**
 * This method sets the checksumm for this root-element.
 * If no checksumvektor or a NULL -pointer is given, the checksum
 * property for this root-element is disabled.
 *
 * @param checksum the checksumvektor this root-element should have;
 * 	if NULL (standardvalue ) the checksum will be disabled for this
 * 	root-element
 */
void cRoot::setChecksum( const cVectorChecksum * pInChecksum ){
	if ( pChecksum != NULL ){
		delete pChecksum;
		pChecksum = NULL;
	}
	if ( pInChecksum ){
		//copy the checksum vector
		pChecksum = new cVectorChecksum( *pInChecksum, this );
	}
}


/**
 * This method stores this Fib-object in the compressed Fib-format
 * into the given stream.
 * It is needed becouse the stream can yust store byts but the size of
 * Fib elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the Fib elements.
 *
 * @see store
 * @param stream the stream where this Fib-object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if this Fib-object is stored, else false
 */
bool cRoot::storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	return storeBit( stream, cRestBits, uiRestBitPosition, true );
}


/**
 * This method stores this Fib-object in the compressed Fib-format
 * into the given stream.
 * It is needed becouse the stream can yust store byts but the size of
 * Fib elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the Fib elements.
 *
 * @see store
 * @param stream the stream where this Fib-object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @param bWriteOptionalPart if true the optionalpart is written
 * @return true if this Fib-object is stored, else false
 */
bool cRoot::storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition, bool bWriteOptionalPart ) const{

	//the value returned by the method
	bool bReturnValue = true;

#ifndef TEST
	//check if the Fib-object is correct
	if ( pMainFibObject == NULL ){
		//no main -Fib-object -> incorrect Fib-object
		return false;
	}
	if ( pSuperiorElement == NULL ){
		//check wool Fib-object
		if ( ! hasUnderAllObjects() ){
			return false;
		}
		//TODO: use isValidObject() when it is implemented
	}
#endif
	/*store the values of the variables, the variables will be used to
	store ther number*/
	(const_cast<cRoot*>(this))->backupVariablesValues( true );
	unsignedIntFib uiVariablenCount = 0;
	
	//set the variables values to ther number
	for ( list< pair< cFibVariable *, doubleFib > >::iterator
			itrActualVariable = (const_cast<cRoot*>(this))->liInputVariables.begin();
			itrActualVariable != (const_cast<cRoot*>(this))->liInputVariables.end();
			itrActualVariable++ ){
		
		uiVariablenCount++;
		itrActualVariable->first->setIntegerValue( (longFib)(uiVariablenCount) );
	}
	//counting variables in the main -Fib-object and creating a variables domain
	if ( pMainFibObject ){
		uiVariablenCount = const_cast<cFibElement*>(pMainFibObject)->
			enumerateVariablesForStoring( uiVariablenCount );
	}
	if ( uiVariablenCount > 0 ){//create the domain for the variables
		cTypeVariable typeVariable;
		unsigned int uiDigitsForVariables = getDigits( uiVariablenCount );
		cDomainNaturalNumberBit domainVariables( uiDigitsForVariables );
		
		const_cast<cDomains*>(&domains)->addDomain( typeVariable, domainVariables );
	}
	
	/*create the propertytypelist, with the propertytypes in the order
	they will be counted when stored*/
	const_cast<cRoot*>(this)->createStorePropertyOrder();
	
	
	//every root element begins with the full byte
	if ( uiRestBitPosition != 0 ){
		stream.write( &cRestBits, 1 );
		cRestBits = 0x00;
		uiRestBitPosition = 0;
	}
	
	//store the Fib-object
	
	//write the stream/file header
	if ( pSuperiorElement == NULL ){
		/*this is the topmost element in the stream
		-> write the header*/
		const char * cFileHeader = "fib";
		const bool bFileHeaderStored = nBitStream::store( stream, cRestBits,
			uiRestBitPosition, cFileHeader, 24 );
		if ( ! bFileHeaderStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			return false;
		}
	}
	
	unsignedLongFib ulBitsWriten = 0;

	//evalue the optional bitfild
	char cOptionalInformationBits[2];
	//empty the bits
	cOptionalInformationBits[0] = 0;
	cOptionalInformationBits[1] = 0;
	
	if ( pChecksum ){
		//set checksum bit
		cOptionalInformationBits[0] |= 0x80;
	}
	//check if the multimediainfo should be written
	if ( pSuperiorElement != NULL ){
		/*if the multimediainfo of this root-element differs to the
		multimediainfo of the supierior root-element the multimediainfo
		have to be be written*/
		if ( ! ( multimediaInfo ==
				(((const cRoot*)(pSuperiorElement))->multimediaInfo) ) ){
			//write the multimediainfo
			cOptionalInformationBits[0] |= 0x40;
		}
	}
	//check if the domains should be written
	if ( ( domains.getNumberOfDomains() != 0 ) ||
			( valueDomains.getNumberOfDomains() != 0 ) ){
		//write the domains
		cOptionalInformationBits[0] |= 0x20;
	}

	//check if the inputvariables should be written
	if ( getNumberOfInputVariables() > 0 ){
		//write the inputvariables
		cOptionalInformationBits[0] |= 0x10;
	}
	
#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//check if the output variables should be written
	if ( getNumberOfExternSubobjects() > 0 ){
		//write the output variables
		cOptionalInformationBits[0] |= 0x08;
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	//check if the sub-root-objects should be written
	if ( getNumberOfSubRootObjects() > 0 ){
		//write the output variables
		cOptionalInformationBits[0] |= 0x04;
	}
	//check if the database identifiers should be written
	if ( ! setDatabaseIdentifiers.empty() ){
		//write the output variables
		cOptionalInformationBits[0] |= 0x02;
	}
	
	//check if the optionalpart should be written
	cOptionalPart * optionalPartFull = NULL;
	if ( bWriteOptionalPart ){
		//extract text from the main-Fib-object into the optionalpart

		//enummerate comments and export ther strings to the optional part
		optionalPartFull = (const_cast<cRoot*>(this))->exportCommentsIntoOptionalPart();
		
		if ( ( optionalPartFull ) &&
				( optionalPartFull->getNumberOfEntries() != 0 ) ){
			//write optional part
			cOptionalInformationBits[0] |= 0x01;
		}
	}
	//write the optional information Bits
	const bool bOptionalInformationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, cOptionalInformationBits, 16 );
	if ( ! bOptionalInformationStored ){
		(const_cast<cRoot*>(this))->backupVariablesValues( false );
		if ( optionalPartFull ){
			delete optionalPartFull;
		}
		return false;
	}
	ulBitsWriten += 16;
	
	//write the elements
	
	//write the checksumfield
	if ( cOptionalInformationBits[0] & 0x80 ){
		
		unsignedLongFib ulTypOfChecksum = pChecksum->getValue( 1 );
		unsignedLongFib ulBitOfChecksumIntervall = pChecksum->getValue( 2 );
		unsignedLongFib ulBitForChecksum = pChecksum->getValue( 3 );
		
		const bool bTypOfChecksumStored = nBitStream::store( stream, cRestBits,
			uiRestBitPosition, ulTypOfChecksum, 16 );
		if ( ! bTypOfChecksumStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		const bool bBitOfChecksumIntervallStored = nBitStream::store( stream, cRestBits,
			uiRestBitPosition, ulBitOfChecksumIntervall, 64 );
		if ( ! bBitOfChecksumIntervallStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		const bool bBitForChecksumStored = nBitStream::store( stream, cRestBits,
			uiRestBitPosition, ulBitForChecksum, 64 );
		if ( ! bBitForChecksumStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}

		ulBitsWriten += 16 + 64 + 64;
	}

	//write the offsets
	unsignedLongFib ulOffset = ulBitsWriten / 8;
	
	//add the size of the offsetfileds
	/*for every Bit set in the cOptionalInformationBits after the second bit
	an 64 bit offset is written*/
	for ( unsigned char ucBit = 0x01; ucBit != 0x00; ucBit = ucBit << 1 ){
		if ( cOptionalInformationBits[0] & ucBit ){
			ulOffset += 8;
		}
	}
	//ulOffset + main -Fib-object offset - root end offset
	ulOffset += 8 + 8;
	
	if ( cOptionalInformationBits[0] & 0x40 ){
		//if the multimediainfo should be written -> add ther size to the offset
		ulOffset += 16;
	}
	
	//domains
	if ( cOptionalInformationBits[0] & 0x20 ){
		/*if the domains should be written
		-> write ther offset*/
		const bool bOffsetDomainsStored = nBitStream::store(
			stream, cRestBits, uiRestBitPosition, ulOffset, 64 );
		if ( ! bOffsetDomainsStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		
		//add ther size to the offset
		unsignedLongFib ulBitSizeDomains = domains.getCompressedSize();
		ulBitSizeDomains += valueDomains.getCompressedSize();
		//round up to a full byte
		ulOffset += roundUpToFullByte( ulBitSizeDomains ) / 8;
	}
	//input variables
	if ( cOptionalInformationBits[0] & 0x10 ){
		/*if the inputvariables should be written
		-> write ther offset*/
		const bool bOffsetInVarStored = nBitStream::store(
			stream, cRestBits, uiRestBitPosition, ulOffset, 64 );
		if ( ! bOffsetInVarStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		
		//add ther size to the offset
		ulOffset += 8;//input variables count

		//add bits for the standardvalues
		//get valid domains
		//for every input variable
		unsignedLongFib ulBitSizeOfStandardValues = 0;
		for ( unsignedIntFib iActualInVarNumber = 1;
				iActualInVarNumber <= liInputVariables.size();
				iActualInVarNumber++ ){
			//get the domain for the i'th input variable
			
			cTypeInVar typeInVar( iActualInVarNumber );
			cDomainSingle * domain = (cDomainSingle*)(
				domains.getDomainForElement( typeInVar ) );
			
			bool bStandartInVarDomain = false;
			if ( domain == NULL ){
				//use the standard domain
				domain = (cDomainSingle*)( typeInVar.getStandardDomain() );
				bStandartInVarDomain = true;
			}
			
			//add the bits vor the i'th input variable standardvalue
			ulBitSizeOfStandardValues +=
				domain->getCompressedSizeForValue();
			
			if ( bStandartInVarDomain ) {
				delete domain;
			}
		}
		//add byts to offset
		ulOffset += roundUpToFullByte( ulBitSizeOfStandardValues ) / 8;
	}
	
#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//output variables
	//bits per output variable
	unsigned int uiBitPerOutputVariable = 0;
	
	if ( cOptionalInformationBits[0] & 0x08 ){
		/*if the output variables should be written
		-> write ther offset*/
		const bool bOffsetExtObjectsStored = nBitStream::store(
			stream, cRestBits, uiRestBitPosition, ulOffset, 64 );
		if ( ! bOffsetExtObjectsStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}

		//add the bits for the output variables to the offset
		
		//ulOffset = output variables count + number of bits for output variable
		ulOffset += 8 + 1;

		//evalue the bits per output variable
		for ( list< unsignedIntFib >::const_iterator itrActualVariable =
					liExternSubobjects.begin();
				itrActualVariable != liExternSubobjects.end();
				itrActualVariable++ ){
				
			if ( uiBitPerOutputVariable <
					getDigits( *itrActualVariable ) ){
				
				uiBitPerOutputVariable =
					getDigits( *itrActualVariable );
			}
				
		}
		//add byts to offset for the outputvariable list
		ulOffset += roundUpToFullByte( uiBitPerOutputVariable *
			liExternSubobjects.size() ) / 8;
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//sum compressed size of main -Fib-object
	if ( pMainFibObject != NULL ){
		/*write the offset for the  main -Fib-object*/
		const bool bOffsetMainFibObjectStored = nBitStream::store(
			stream, cRestBits, uiRestBitPosition, ulOffset, 64 );
		if ( ! bOffsetMainFibObjectStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}

		//add byts to offset
		ulOffset += roundUpToFullByte( pMainFibObject->getCompressedSize() ) / 8;
	}
	//sum compressed size of sub-root-elements
	//bits per sub-root-element identifier
	unsigned int uiBitPerSubRootIdentifier = 0;
	
	if ( cOptionalInformationBits[0] & 0x04 ){
		/*if the sub-root-elements should be written
		-> write ther offset*/
		const bool bOffsetSubRootsStored = nBitStream::store(
			stream, cRestBits, uiRestBitPosition, ulOffset, 64 );
		if ( ! bOffsetSubRootsStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		//number of sub-roots + byts per identifier
		ulOffset += 8 + 1;
		
		//evalue the bits per sub-root-element identifier
		for ( list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement =
					liSubRootObjects.begin();
				itrActualRootElement != liSubRootObjects.end();
				itrActualRootElement++ ){
			
			if ( uiBitPerSubRootIdentifier <
					getDigits( itrActualRootElement->first ) ){
				
				uiBitPerSubRootIdentifier=
					getDigits( itrActualRootElement->first );
			}
		}
		//add one bit for the sign of the identifier
		uiBitPerSubRootIdentifier = roundUpToFullByte( uiBitPerSubRootIdentifier );
		
		for ( list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement =
					liSubRootObjects.begin();
				itrActualRootElement != liSubRootObjects.end();
				itrActualRootElement++ ){

			if ( itrActualRootElement->second != NULL ){
			
				unsignedLongFib ulBitsForSubRoot = uiBitPerSubRootIdentifier;
				
				ulBitsForSubRoot += itrActualRootElement->second->
					getCompressedSize( true );
				
				//round up to a full byte
				ulBitsForSubRoot = roundUpToFullByte( ulBitsForSubRoot );
				//add byts to offset
				ulOffset += ulBitsForSubRoot / 8;
			}
		}
	}
	//write offset wher the used database identifiers are written
	unsigned int uiMaxBitsForUsedDbIdentifier = 0;
	if ( cOptionalInformationBits[0] & 0x02 ){
		/*if the optional part should be written
		-> write ther offset*/
		const bool bOffsetOptionalPartStored = nBitStream::store(
			stream, cRestBits, uiRestBitPosition, ulOffset, 64 );
		if ( ! bOffsetOptionalPartStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		//add size of optional part
		for ( set< longFib >::const_iterator itrIdentifier = setDatabaseIdentifiers.begin();
				itrIdentifier != setDatabaseIdentifiers.end(); itrIdentifier++ ){
			
			const unsigned int uiBitsForIdentifier =
				getDigits( *itrIdentifier );
			if ( uiMaxBitsForUsedDbIdentifier < uiBitsForIdentifier ){
				uiMaxBitsForUsedDbIdentifier = uiBitsForIdentifier;
			}
		}
		//add sign bit
		//add byts of the used database identifiers
		ulOffset += 8 + 8 + 1 + roundUpToFullByte(
			uiMaxBitsForUsedDbIdentifier * setDatabaseIdentifiers.size() );
	}
	
	//check if the optionalpart should be written
	if ( cOptionalInformationBits[0] & 0x01 ){
		/*if the optional part should be written
		-> write ther offset*/
		const bool bOffsetOptionalPartStored = nBitStream::store(
			stream, cRestBits, uiRestBitPosition, ulOffset, 64 );
		if ( ! bOffsetOptionalPartStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		//add size of optional part
		ulOffset += optionalPartFull->getCompressedSize() / 8;
	}
	//bit wher the root element ends
	const bool bOffsetRootEndStored = nBitStream::store(
		stream, cRestBits, uiRestBitPosition, ulOffset, 64 );
	if ( ! bOffsetRootEndStored ){
		(const_cast<cRoot*>(this))->backupVariablesValues( false );
		if ( optionalPartFull ){
			delete optionalPartFull;
		}
		return false;
	}
	

	/*******************
	** write the data **
	********************/
	if ( cOptionalInformationBits[0] & 0x40 ){
		//write the multimediainfo
		unsignedLongFib ulFibVersion = multimediaInfo.getFibVersion();
		ulFibVersion = ulFibVersion << (sizeof( unsignedLongFib ) * 8 - 64);
		const bool bFibVersionStored = nBitStream::store(
			stream, cRestBits, uiRestBitPosition, ulFibVersion, 64 );
		if ( ! bFibVersionStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		unsignedLongFib ulDatabaseVersion = multimediaInfo.getDatabaseVersion();
		ulDatabaseVersion = ulDatabaseVersion << (sizeof( unsignedLongFib ) * 8 - 64);
		const bool bFibDbVersionStored = nBitStream::store(
			stream, cRestBits, uiRestBitPosition, ulDatabaseVersion, 64 );
		if ( ! bFibDbVersionStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
	}
	//domains
	if ( cOptionalInformationBits[0] & 0x20 ){
		
		//add ther size to the offset
		bool bDomainsStored = domains.store( stream, cRestBits, uiRestBitPosition);
		if ( ! bDomainsStored ){
			//restore the values of the variables
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		bool bValidDomainsStored = valueDomains.store( stream, cRestBits, uiRestBitPosition);
		if ( ! bValidDomainsStored ){
			//restore the values of the variables
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		
		//fill up to full byte
		if ( uiRestBitPosition != 0 ){
			stream.write( &cRestBits, 1 );
			cRestBits = 0x00;
			uiRestBitPosition = 0;
		}
	}

	//inputvariables
	if ( cOptionalInformationBits[0] & 0x10 ){
		
		//write the number of input variables
		unsignedLongFib ulNumberOfInputVariables = getNumberOfInputVariables();
		const bool bCountOfInVarStored = nBitStream::store(
			stream, cRestBits, uiRestBitPosition, ulNumberOfInputVariables, 64 );
		if ( ! bCountOfInVarStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		
		//write the standardvalues vor the input variables
		
		//get the domain for the input variable
		cDomains valueDomains = getValidValueDomains();
		
		for ( unsignedLongFib ulActualInputVariable = 1;
				ulActualInputVariable <= ulNumberOfInputVariables;
				ulActualInputVariable++ ){
			
			cTypeInVar typeActualInVar( ulActualInputVariable );
			
			cDomainSingle * actualInVarDomain = (cDomainSingle*)(
				valueDomains.getDomainForElement( typeActualInVar ) );
			bool bStandardDomain = false;
			if ( actualInVarDomain == NULL ){
				actualInVarDomain = (cDomainSingle*)(
					typeActualInVar.getStandardDomain() );
				bStandardDomain = true;
			}
			
			actualInVarDomain->storeValue(
				getStandardValueOfInputVariable( ulActualInputVariable ),
				stream, cRestBits, uiRestBitPosition );
			
			if ( bStandardDomain ){
				delete actualInVarDomain;
			}
		}
		//fill up to full byte
		if ( uiRestBitPosition != 0 ){
			stream.write( &cRestBits, 1 );
			cRestBits = 0x00;
			uiRestBitPosition = 0;
		}
	}
#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//outputvariable
	if ( cOptionalInformationBits[0] & 0x08 ){
		
		//write the number of extern subobjects with output variables
		unsignedLongFib ulNumberOfExternUnderObjects = getNumberOfExternSubobjects();
		const bool bCountOfExtObjectsStored = nBitStream::store(
			stream, cRestBits, uiRestBitPosition, ulNumberOfExternUnderObjects, 64 );
		if ( ! bCountOfExtObjectsStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		
		//evalue the bits per output variable
		unsigned int uiBitPerOutputVariable = 0;
		
		for ( list< unsignedIntFib >::const_iterator itrActualVariable =
					liExternSubobjects.begin();
				itrActualVariable != liExternSubobjects.end();
				itrActualVariable++ ){
				
			if ( uiBitPerOutputVariable <
					getDigits( *itrActualVariable ) ){
				
				uiBitPerOutputVariable =
					getDigits( *itrActualVariable );
			}
				
		}
		const bool bBitPerOutVarStored = nBitStream::store(
			stream, cRestBits, uiRestBitPosition, uiBitPerOutputVariable, 8 );
		if ( ! bBitPerOutVarStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}

		//store the counts of the output variables for the extern subobjects
		for ( list< unsignedIntFib >::const_iterator itrActualVariable =
					liExternSubobjects.begin();
				itrActualVariable != liExternSubobjects.end();
				itrActualVariable++ ){
			
			unsignedLongFib ulCountActualOutputVariables = (*itrActualVariable);
			
			bool bCountOfOutputVariablesStored = nBitStream::store( stream,
				cRestBits, uiRestBitPosition,
				ulCountActualOutputVariables, uiBitPerOutputVariable );
			if ( ! bCountOfOutputVariablesStored ){
				//restore the values of the variables
				(const_cast<cRoot*>(this))->backupVariablesValues( false );
				if ( optionalPartFull ){
					delete optionalPartFull;
				}
				return false;
			}
		}
		
		//fill up to full byte
		if ( uiRestBitPosition != 0 ){
			stream.write( &cRestBits, 1 );
			cRestBits = 0x00;
			uiRestBitPosition = 0;
		}
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	//store the main -Fib-object
	if ( pMainFibObject != NULL ){

		bool bMainFibObjectStored =  pMainFibObject->storeBit( stream,
			cRestBits, uiRestBitPosition );
		if ( ! bMainFibObjectStored ){
			//restore the values of the variables
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		
		//fill up to full byte
		if ( uiRestBitPosition != 0 ){
			stream.write( &cRestBits, 1 );
			cRestBits = 0x00;
			uiRestBitPosition = 0;
		}
	}else{//error no object -> write 8 0 byts for NULL = no object
		stream.write( 0, 8 );
		bReturnValue = false;
	}
	
	
	//sub-root-objects
	if ( cOptionalInformationBits[0] & 0x04 ){
		
		//write the number of sub-root-objects with output variables
		unsignedLongFib ulNumberOffSubRootObjects = getNumberOfSubRootObjects();
		const bool bCountOffSubRootsStored = nBitStream::store(
			stream, cRestBits, uiRestBitPosition, ulNumberOffSubRootObjects, 64 );
		if ( ! bCountOffSubRootsStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			if ( optionalPartFull ){
				delete optionalPartFull;
			}
			return false;
		}
		
		//evalue the bits per sub-root-element identifier
		unsigned int uiBitPerIdentifier = 0;
		for ( list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement =
					liSubRootObjects.begin();
				itrActualRootElement != liSubRootObjects.end();
				itrActualRootElement++ ){
			
			const unsigned int uiDigitsForActualIdentifier =
				getDigits( itrActualRootElement->first );
			if ( uiBitPerIdentifier < uiDigitsForActualIdentifier ){
				
				uiBitPerIdentifier = uiDigitsForActualIdentifier;
			}
		}
		
		uiBitPerIdentifier = roundUpToFullByte( uiBitPerIdentifier );
		const unsignedIntFib uiBytePerIdentifier = uiBitPerIdentifier / 8;
		const cDomainNaturalNumberBit domainNaturalNumberBit8( 8 );
		
		const bool bBytePerIdentifierStored = domainNaturalNumberBit8.storeUnscaledValue(
			uiBytePerIdentifier, stream, cRestBits, uiRestBitPosition );
		if ( ! bBytePerIdentifierStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			return false;
		}
		const cDomainIntegerBit domainIntegerIdentifier( uiBytePerIdentifier * 8 );
		for ( list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement =
					liSubRootObjects.begin();
				itrActualRootElement != liSubRootObjects.end();
				itrActualRootElement++ ){
			
			//write the identifier
			const long long lActualIdentifier = itrActualRootElement->first;
			const bool bIdentifierStored = domainIntegerIdentifier.storeUnscaledValue(
				lActualIdentifier, stream, cRestBits, uiRestBitPosition );
			if ( ! bIdentifierStored ){
				//restore the values of the variables
				(const_cast<cRoot*>(this))->backupVariablesValues( false );
				return false;
			}

			//write the sub root object
			if ( itrActualRootElement->second != NULL ){
				const bool bSubRootObjectStored = itrActualRootElement->second->
					storeBit( stream, cRestBits, uiRestBitPosition, bWriteOptionalPart );
				if ( ! bSubRootObjectStored ){
					//restore the values of the variables
					(const_cast<cRoot*>(this))->backupVariablesValues( false );
					return false;
				}
			}else{//error no object -> write 8 0 byts for NULL = no object
				stream.write( 0, 8 );
				bReturnValue = false;
			}
			//fill up to full byte
			if ( uiRestBitPosition != 0 ){
				stream.write( &cRestBits, 1 );
				cRestBits = 0x00;
				uiRestBitPosition = 0;
			}
		}
	}

	//write database identifiers
	if ( ! setDatabaseIdentifiers.empty() ){
		//store number of identifiers
		const cDomainNaturalNumberBit domainNaturalNumberBit64( 64 );
		unsigned long ulNumberOfUsedDbIdentifiers = setDatabaseIdentifiers.size();
		
		const bool bNumberOfUsedDbIdentifiersStored =
			domainNaturalNumberBit64.storeUnscaledValue(
				ulNumberOfUsedDbIdentifiers, stream, cRestBits, uiRestBitPosition );
		if ( ! bNumberOfUsedDbIdentifiersStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			return false;
		}
		//count bit for identifer
		const cDomainNaturalNumberBit domainNaturalNumberBit8( 8 );
		
		const bool bBitPerIdentifierStored = domainNaturalNumberBit8.storeUnscaledValue(
			uiMaxBitsForUsedDbIdentifier, stream, cRestBits, uiRestBitPosition );
		if ( ! bBitPerIdentifierStored ){
			(const_cast<cRoot*>(this))->backupVariablesValues( false );
			return false;
		}
		//store used database identifieres
		const cDomainIntegerBit domainIntegerIdentifier( uiMaxBitsForUsedDbIdentifier );
		for ( set< longFib >::const_iterator itrIdentifier = setDatabaseIdentifiers.begin();
				itrIdentifier != setDatabaseIdentifiers.end(); itrIdentifier++ ){
			
			//write the identifier
			const long long lActualIdentifier = (*itrIdentifier);
			const bool bIdentifierStored = domainIntegerIdentifier.storeUnscaledValue(
				lActualIdentifier, stream, cRestBits, uiRestBitPosition );
			if ( ! bIdentifierStored ){
				//restore the values of the variables
				(const_cast<cRoot*>(this))->backupVariablesValues( false );
				return false;
			}
		}//end for store identifier
		//fill up to full byte
		if ( uiRestBitPosition != 0 ){
			stream.write( &cRestBits, 1 );
			cRestBits = 0x00;
			uiRestBitPosition = 0;
		}
	}//end store used database identifier
	
	//optional part
	if ( ( cOptionalInformationBits[0] & 0x01 ) &&
			( optionalPartFull != NULL ) ){
		//write optional part
		optionalPartFull->store( stream );
	}
	if ( optionalPartFull ){
		delete optionalPartFull;
	}
	
	//restore old Fib-object
	(const_cast<cRoot*>(this))->backupVariablesValues( false );
	return bReturnValue;
}


#ifdef FEATURE_FAST_UPDATE

/**
 * This method cuts the connections of this Fib element to the
 * given Fib element.
 *
 * @param pFibElement the Fib element to which to cut the connection
 */
void cRoot::cutConnectionsTo( const cFibElement * pFibElement ){
	
	cFibElement::cutConnectionsTo( pFibElement );
	//check the subobjects
	list<cFibElement*>::iterator itrActualUnderObject = fibUnderObjects.begin();
	for ( ; itrActualUnderObject != fibUnderObjects.end(); itrActualUnderObject++ ){
		
		if ( (*itrActualUnderObject) == pFibElement ){
			/*cut connection to the actual subobject;
			it is (itrActualUnderObject != fibUnderObjects.end())*/
			break;
		}
	}
	if ( itrActualUnderObject != fibUnderObjects.end() ){
		//cut connection to the found subobject
		if ( itrActualUnderObject == fibUnderObjects.begin() ){
			//cut connection to the main fib object
			pMainFibObject = NULL;
			fibUnderObjects.front() = NULL;
		}else{//cut connection to a sub-root-object
			//search for the sub-root-object
			list< pair< longFib, cRoot * > >::iterator itrActualSubRootObject = liSubRootObjects.begin();
			for ( ; itrActualSubRootObject != liSubRootObjects.end() ; itrActualSubRootObject++ ){
				if ( itrActualSubRootObject->second == (*itrActualUnderObject) ){
					liSubRootObjects.erase( itrActualSubRootObject );
					break;
				}
			}
			fibUnderObjects.erase( itrActualUnderObject );
		}
		updateAllCounters();
	}
}


/**
 * This method updates the Fib element counters of all branchelements in
 * this branchelement.
 *
 * @return the numbers with which the Fib element counters wher updated
 */
cFibObjectCounts cRoot::updateCounters(){
	
	cFibObjectCounts newFibObjectCounts;
	
	//add number of Fib elements of the typs of all subobjects
	for ( list<cFibElement *>::const_iterator
			itrUnderobject = fibUnderObjects.begin();
			itrUnderobject != fibUnderObjects.end(); itrUnderobject++ ){
		
		if ( (*itrUnderobject) != NULL ){
			newFibObjectCounts +=
				evalueCountersForObject( *itrUnderobject );
			newFibObjectCounts.uiNumberOfObjectpoints++;
		}
	}
	newFibObjectCounts.vecNumberOfFibElements[
		cFibObjectCounts::elementTypeToIndex( getType() ) ]++;
	newFibObjectCounts.evalueAllFibElements();
	
	//evalue the delta
	cFibObjectCounts deltaFibObjectCounts;
	deltaFibObjectCounts = newFibObjectCounts;
	deltaFibObjectCounts -= fibObjectCounts;
	
	//set the counters of this branchelement toi the new values
	fibObjectCounts = newFibObjectCounts;
	
	return deltaFibObjectCounts;
}

#endif //FEATURE_FAST_UPDATE


/**
 * This method stores the actual variables of this root element, so
 * they can restored later.
 * This method also restores the variable values. Yust one set of values
 * can be stored.
 *
 * @param bStoreValues is true the variables values will be stored, else
 * 	the stored variables will be restored.
 */
void cRoot::backupVariablesValues( bool bStoreValues ){
	
	if ( bStoreValues ){
		//store the variables values
		//clear old stored backupvariablelist
		
		liLiStoredInputVariables.push_back( list< cFibVariable * >() );
		list< cFibVariable * > & liStoredInputVariables =
			liLiStoredInputVariables.back();
		
		for ( list< pair< cFibVariable *, doubleFib > >::iterator
				itrActualVariable = liInputVariables.begin();
				itrActualVariable != liInputVariables.end();
				itrActualVariable++ ){
			
			liStoredInputVariables.push_back( new cFibVariable( *(itrActualVariable->first) ) );
		}
		return;
	}else{// restore the variable values
		list< pair< cFibVariable *, doubleFib > >::iterator
				itrActualVariable = liInputVariables.begin();
		
		list< cFibVariable * > & liStoredInputVariables =
			liLiStoredInputVariables.back();
		
		for ( list< cFibVariable * >::iterator
				itrActualStoredVariable = liStoredInputVariables.begin();
				itrActualStoredVariable != liStoredInputVariables.end() &&
				itrActualVariable != liInputVariables.end();
				itrActualStoredVariable++, itrActualVariable++ ){
			
			*(itrActualVariable->first) = (**itrActualStoredVariable);
		}
		// remove restored input variables from stored input variables stack
		while ( ! liStoredInputVariables.empty() ){
			//the old values will be overwritten
			delete (liStoredInputVariables.back());
			liStoredInputVariables.pop_back();
		}
		liLiStoredInputVariables.pop_back();
	}
}


/**
 * This method syncronises the subobjects of this cRoot -class with
 * the subobjectslist fibUnderObjects of the cFibBranch class.
 */
void cRoot::syncSubobjects(){
	
	if ( fibUnderObjects.empty() ){
		//no subobjects
		pMainFibObject = NULL;
		liSubRootObjects.clear();
		return;
	}
	
	list<cFibElement*>::const_iterator itrActualUnderobject = fibUnderObjects.begin();
	if ( pMainFibObject != ( * itrActualUnderobject ) ){
		pMainFibObject = ( * itrActualUnderobject );
	}
	//syncronize the sub root objects
	itrActualUnderobject++;
	list< pair< longFib, cRoot * > >::iterator itrActualSubRootObject = liSubRootObjects.begin();
	for ( ; itrActualUnderobject != fibUnderObjects.end() ; itrActualUnderobject++ ){
		
		if ( itrActualSubRootObject == liSubRootObjects.end() ){
			//insert a new sub-root-object; the identifier is the actual position
			if ( ( *itrActualUnderobject)->getType() == 'r' ){
				liSubRootObjects.push_back( make_pair(
					liSubRootObjects.size() + 1 , (cRoot*)( * itrActualUnderobject ) ) );
			}//else error: the subobject is no root-object
			//insert the next sub-root-element at the end of the sub-root-element list
			itrActualSubRootObject = liSubRootObjects.end();
		}else{
			//overwrite sub-root-element
			if ( ( *itrActualUnderobject)->getType() == 'r' ){
				itrActualSubRootObject->second = (cRoot*)( * itrActualUnderobject );
			}//else error: the subobject is no root-object
			//check next sub-root-element
			itrActualSubRootObject++;
		}
	}
	//remove sub-root-objects that are to many
	if ( itrActualSubRootObject != liSubRootObjects.end() ){
		liSubRootObjects.erase ( itrActualSubRootObject, liSubRootObjects.end() );
	}
}


/**
 * This method returns the identifiers of all root-objects in the
 * direction down of this root-element.
 *
 * @see getAllRootObjectIdentifiers()
 * @return the identifiers of all root-objects in the direction down
 */
list<longFib> cRoot::getAllDownRootObjectIdentifiers() const{
	//the list with the founded identifiers
	list<longFib> liIdentifiers;
	
	for ( list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement =
				liSubRootObjects.begin();
			itrActualRootElement != liSubRootObjects.end();
			itrActualRootElement++ ){
		
		//add the actual identifier
		liIdentifiers.push_back( itrActualRootElement->first );
		
		//add the identifiers of the sub root object
		if ( itrActualRootElement->second != NULL ){
			list<longFib> liActualSubRootIdentifiers = itrActualRootElement->
				second->getAllDownRootObjectIdentifiers();
			
			liIdentifiers.insert( liIdentifiers.end(),
				liActualSubRootIdentifiers.begin(),
				liActualSubRootIdentifiers.end() );
		}//else error no sub-root-object
	}
	return liIdentifiers;
}


/**
 * This method returns the root-object in the direction down for the
 * given identifier.
 * If non such exists the Nullpoint NULL is returned.
 *
 * @param lIdentifier the identifier of the root-object to return
 * @return the root-object for the given identifier or NULL if non
 * 	such exists
 */
cRoot * cRoot::getRootObjectDown( longFib lIdentifier ){

	for ( list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement =
				liSubRootObjects.begin();
			itrActualRootElement != liSubRootObjects.end();
			itrActualRootElement++ ){
		
		if ( itrActualRootElement->second != NULL ){
			//check actual identifier
			if ( itrActualRootElement->first == lIdentifier ){
				//correct sub-root-object found -> return it
				return itrActualRootElement->second;
			}
			//search in sub-root-object
			cRoot * pRootObject = itrActualRootElement->second->
				getRootObjectDown( lIdentifier );
			if ( pRootObject ){
				//sub-root-object found -> return it
				return pRootObject;
			}
		}//else error no sub-root-object
	}
	//no correct sub-root-object found -> give back NULL
	return NULL;
}




/**
 * This method returns the identifiers of all from this Fib element
 * accessible root-objects of this object.
 *
 * @param pRoot a pointer to the root element, for which the
 * 	root-elements should be accessible
 * @return the identifiers of all accessible root-objects
 */
list<longFib> cRoot::getAllAccessibleRootObjectIdentifiers( const cRoot *pRoot ) const{
	//add the identifiers of this root-element

	list<longFib> liIdentifiers;
	if ( pRoot == this){
		liIdentifiers = getAllSubRootObjectIdentifiers();
	}else{
		//just give back the root elements after pRoot
		//find the sub-root-objects after pRoot
		list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement;
		for ( itrActualRootElement = liSubRootObjects.begin();
				itrActualRootElement != liSubRootObjects.end();
				itrActualRootElement++ ){
			
			if ( itrActualRootElement->second == pRoot ){
				itrActualRootElement++;
				break;
			}
		}
		//add the sub-root-objects after the founded sub-root-object
		for ( ; itrActualRootElement != liSubRootObjects.end();
				itrActualRootElement++ ){
			//add the actual identifier
			liIdentifiers.push_back( itrActualRootElement->first );
		}
	}
	
	//add the identifiers of super/ higher root-elements
	if ( pSuperiorElement != NULL ){
		list<longFib> liHigherIdentifiers =
			((cRoot*)pSuperiorElement)->getAllAccessibleRootObjectIdentifiers( this );
		
		liIdentifiers.insert( liIdentifiers.end(),
			liHigherIdentifiers.begin(), liHigherIdentifiers.end() );
	}else{//execute one time for the Fib-object
		//add database identifiers
		list<longFib> liDatabaseIdentifiers = getAllDatabaseObjectIdentifiers();
		liIdentifiers.insert( liIdentifiers.end(),
				liDatabaseIdentifiers.begin(), liDatabaseIdentifiers.end() );
	}
	return liIdentifiers;
}


/**
 * This method returns the from this Fib element accessible root
 * -object for the given identifier. If non such exists the Nullpoint 
 * NULL is returned.
 *
 * @param pRoot a pointer to the root element, for which the
 * 	root-elements should be accessible
 * @param lIdentifier the identifier of the root-object to return
 * @return the accessible root-object for the given identifier or NULL
 * 	if non such exists
 */
cRoot * cRoot::getAccessibleRootObject( longFib lIdentifier, const cRoot *pRoot  ){
	
	//just search the sub-root-elements after this
	if ( pRoot == this){
		//search the sub-root-objetcs in this root-element
		cRoot * pSubRootObject = getSubRootObjectForIdentifier( lIdentifier );
		if ( pSubRootObject ){
			return pSubRootObject;
		}
	}else{
		//just give back the root elements after pRoot
		//find the sub-root-objects after pRoot
		list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement;
		for ( itrActualRootElement = liSubRootObjects.begin();
				itrActualRootElement != liSubRootObjects.end();
				itrActualRootElement++ ){
			
			if ( itrActualRootElement->second == pRoot ){
				itrActualRootElement++;
				break;
			}
		}
		/*return the sub-root-object after the founded sub-root-object
		with the lIdentifier*/
		for ( ; itrActualRootElement != liSubRootObjects.end();
				itrActualRootElement++ ){
			if ( itrActualRootElement->first == lIdentifier ){
				//sub-root-object with the lIdentifier found
				return itrActualRootElement->second;
			}
		}
	}
	//search the identifiers of super/ higher root-elements
	if ( pSuperiorElement != NULL ){
		
		cRoot * pHigherSubRootObject =
			((cRoot*)pSuperiorElement)->getAccessibleRootObject( lIdentifier, this );
		if ( pHigherSubRootObject ){
			return pHigherSubRootObject;
		}
	}
	//search database Identifiers
	if ( pFibDatabase == NULL ){
		//no database instance -> create one
		pFibDatabase = cFibDatabase::getInstance();
	}
	return pFibDatabase->getFibObject( lIdentifier );
}


/**
 * This method creates the propertytypelist, with the propertytypes in the
 * order they will be counted when stored.
 *
 * @see storeBit()
 * @see liStorePropertyOrder
 */
bool cRoot::createStorePropertyOrder(){
	
	liStorePropertyOrder.clear();
	
	cDomains validDomains = getValidValueDomains();
	for( unsignedIntFib uiActualDomain = 1;
			uiActualDomain <= validDomains.getNumberOfDomains();
			uiActualDomain++ ){
		
		const cTypeElement * pTypeElement =
			validDomains.getType( uiActualDomain );
		
		if ( pTypeElement == NULL ){
			continue;
		}
		if ( pTypeElement->getType() != 6 ){
			//just add propertytyps
			continue;
		}
		//check if the propertype is allready added
		list<cTypeProperty>::const_iterator itrFoundType =
			find( liStorePropertyOrder.begin(), liStorePropertyOrder.end(),
			*((cTypeProperty*)pTypeElement) );
		
		if ( itrFoundType == liStorePropertyOrder.end() ){
			//just add missing propertytyps
			liStorePropertyOrder.push_back( *((cTypeProperty*)pTypeElement) );
		}
	}

	return true;
}


/**
 * This method evalues the bits needed to store a property type.
 *
 * @see storeBit()
 * @see createStorePropertyOrder()
 * @see liStorePropertyOrder
 * @see storePropertyType()
 */
unsignedIntFib cRoot::getBitsForStoredPropertyType() const{

	if ( liStorePropertyOrder.empty() ){
		const_cast<cRoot*>(this)->createStorePropertyOrder();
	}
	if ( liStorePropertyOrder.empty() ){
		return 0;
	}
	return getDigits( ((unsigned int)liStorePropertyOrder.size() - 1) );
}


/**
 * This method stores the given propertytype in the compressed file format.
 *
 * @see storeBit()
 * @see createStorePropertyOrder()
 * @see liStorePropertyOrder
 * @param stream the stream where this Fib-object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @param propertyType the propertytype to store
 * @return true if this Fib-object is stored, else false
 */
bool cRoot::storePropertyType( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition, const cTypeProperty & propertyType ) const{
	
	if ( liStorePropertyOrder.empty() ){
		const_cast<cRoot*>(this)->createStorePropertyOrder();
	}
	//find the correct propertytype in the liStorePropertyOrder
	unsigned long ulPropertyType = 0;
	for ( list< cTypeProperty >::const_iterator itrPropertyType =
			liStorePropertyOrder.begin();
			itrPropertyType != liStorePropertyOrder.end(); itrPropertyType++ ){
		
		if ( propertyType.equalElementType( *itrPropertyType ) ){
			//correct propertytype found
			break;
		}
		ulPropertyType++;
	}
	if ( ulPropertyType == liStorePropertyOrder.size() ){
		//no such propertytype found
		return false;
	}
	
	const unsigned char iBitsToStore = getBitsForStoredPropertyType();

	const bool bPropertyTypeStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, ulPropertyType, iBitsToStore );
	if ( ! bPropertyTypeStored ){
		return false;
	}
	
	return true;
}


/**
 * This method restores a propertytype from a stream in the compressed file format.
 *
 * @see storePropertyType()
 * @see storeBit()
 * @see createStorePropertyOrder()
 * @see liStorePropertyOrder
 * @param iBitStream the stream where this propertytype is stored to in,
 * 	because this stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @param outStatus An reference to an integervalue where the errorvalue
 * 	can be stored to. If the pointer is NULL no errorvalue will be
 * 	given back.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 * @return the restored property or the propertytype NONE if it couldn't be restored
 */
cTypeProperty cRoot::restorePropertyType( cReadBits & iBitStream, intFib & outStatus ) const{

	if ( ! iBitStream.getStream()->good() ){
		DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
		outStatus = -1;
		return cTypeProperty( cTypeProperty::NONE );
	}
	if ( liStorePropertyOrder.empty() ){
		const_cast<cRoot*>(this)->createStorePropertyOrder();
	}
	const unsigned int uiBitsToRestore = getBitsForStoredPropertyType();
	
	cDomainNaturalNumberBit domainNaturalNumberBit( uiBitsToRestore );
	
	long ulPropertyType = domainNaturalNumberBit.restoreIntegerValue(
		iBitStream, outStatus );
	if ( outStatus < 0 ){
		return cTypeProperty( cTypeProperty::NONE );
	}
	//find the correct propertytype in the liStorePropertyOrder
	list< cTypeProperty >::iterator itrPropertyType =
		const_cast<cRoot*>(this)->liStorePropertyOrder.begin();
	
	for ( long ulActalProperty = 0; (ulActalProperty < ulPropertyType) &&
			(itrPropertyType != liStorePropertyOrder.end());
			ulActalProperty++, itrPropertyType++ ){
	}
	if ( itrPropertyType == liStorePropertyOrder.end() ){
		//no such propertytype found
		outStatus = -2;
		return cTypeProperty( cTypeProperty::NONE );
	}
	return (*itrPropertyType);
}


/**
 * This method exports the comment values into a optional part.
 * It also enumerates the comments.
 * This functionality is for compressed storing of an Fib-object.
 * @see storeBit()
 * @see cRoot( cReadBits & iBitStream, intFib & outStatus, cRoot * pNextRoot )
 * @return a pointer to an optional part with the comments texts in it;
 * 	Beware: You have to delete it after usage
 */
cOptionalPart * cRoot::exportCommentsIntoOptionalPart(){
	
	if ( pMainFibObject == NULL ){
		//no main -Fib-object -> no comments in it
		return optionalPart.clone();
	}
	//extraxt all comments
	//for all commentelements under this root-element
	const unsignedIntFib uiNumberOfComments =
		pMainFibObject->getNumberOfElements( 'c' );
	if ( uiNumberOfComments == 0 ){
		//no comments in -> nothing to do
		return optionalPart.clone();
	}
	cOptionalPart * pFullOptionalPart = optionalPart.clone();
	
	cComment * pComment = ((cComment*)(getNextFibElement( 'c' )));
	
	//TODO: eleminate duplicate key, value pairs
	
	for ( unsigned int uiActualComment = 0;
			uiActualComment < uiNumberOfComments; uiActualComment++ ){
		
		if ( pComment == NULL ){
			//no next commentelement in it
			break;
		}
		pComment->ulCommentNumber = uiActualComment;
		
		//insert the comments into the optional part
		char szCommentNumber[ 64 ];
		sprintf( szCommentNumber, "@%u@", uiActualComment );
		string szKey( szCommentNumber );
		szKey.append( pComment->getKey() );
		
		pFullOptionalPart->addEntry( szKey, pComment->getValue() );
		
		if ( uiActualComment == (uiNumberOfComments - 1) ){
			break;
		}//else
		pComment = ((cComment*)(pComment->getNextFibElement( 'c' )));
	}
	//add comment domain to the domains
	cTypeComments typeComments;
	cDomainNaturalNumber domainComments( uiNumberOfComments - 1 );
	domains.addDomain( typeComments, domainComments );
	
	return pFullOptionalPart;
}


/**
 * This method removes all comment values from the optional part,
 * which wher stored ther for compressed storing.
 * It will also put the extracted comments into ther commentelements.
 * @see vecComments
 * @see getCommentValues()
 * @see storeBit()
 * @see cRoot( cReadBits & iBitStream, intFib & outStatus, cRoot * pNextRoot )
 */
void cRoot::extractCommentsFromOptionalPart(){
	
	if ( pMainFibObject == NULL ){
		//no main Fib object -> nothing to extract
		return;
	}
	//for all commentelements under this root-element
	const unsignedIntFib uiNumberOfComments =
		pMainFibObject->getNumberOfElements( 'c' );
	if ( uiNumberOfComments == 0 ){
		//no comments in Fib-object
		return;
	}
	
	const list< pair<string,string> > liComments =
		optionalPart.getEntries( "@", false );
	vector< pair<string,string> > vecComments( liComments.size() );
	
	for ( list< pair<string,string> >::const_iterator
			itrComment = liComments.begin(); itrComment != liComments.end();
			itrComment++ ){
		
		//extract the number and the key
		string szLoadedKey = itrComment->first;

		const unsigned int uiActualComment =
			atol( &(szLoadedKey.c_str()[ 1 ]) );
		//find second '@' character (first '@' and one character for the number can be skiped)
		const size_t uiKeyStart = szLoadedKey.find_first_of( '@', 2 ) + 1;
		szLoadedKey.erase( 0, uiKeyStart );
		
		//add to vecComments
		if ( vecComments.size() <= uiActualComment ){
			vecComments.resize( uiActualComment + 1 );
		}
		vecComments[ uiActualComment ] = pair<string,string>(
			szLoadedKey, itrComment->second );
	}
	//delete the extrcted comments from the optional part
	optionalPart.deleteEntries( "@", false );
	
	//put the extracted comments into ther comment elements
	cComment * pComment = ((cComment*)(getNextFibElement( 'c' )));

	for ( unsigned int uiActualComment = 0;
			uiActualComment < uiNumberOfComments; uiActualComment++ ){
		
		if ( pComment == NULL ){
			//no next commentelement in it
			break;
		}
		if ( pComment->ulCommentNumber < vecComments.size() ){
			pComment->setKey( vecComments[ pComment->ulCommentNumber ].first );
			pComment->setValue( vecComments[ pComment->ulCommentNumber ].second );
		}//else comment not found -> ignore it
		
		if ( uiActualComment == (uiNumberOfComments - 1) ){
			break;
		}//else
		pComment = ((cComment*)(pComment->getNextFibElement( 'c' )));
	}
}


/**
 * This method copies the connected object with the given number in the
 * order of connected objects.
 * For this every Fib element, beginning from this Fib element, that
 * is part of the connected object will be copied.
 * Variables which are not defined in the connected object but used
 * don't change ther reference.
 * It is an helpmethod for the copy method. It dosn't update the
 * structural information of the created Fib-object.
 *
 * @param iObjectPoint the number of the connected object to copy;
 * 	the standartvalue is 0 for coping the complet actual object
 * @return the copy of the connected object or NULL if non such exists
 */
cRoot * cRoot::copyInternal( const unsignedIntFib uiObjectPoint ) const{
	
	//copy this element
	cRoot * pFibObjectCopy = new cRoot( * this );
	//remove NULL main -Fib-object
	pFibObjectCopy->fibUnderObjects.clear();
	
	//copy and insert the subobjects which are part of the uiObjectPoint subobject
	if ( uiObjectPoint == 0 ){
		//copy all subobjects
		//copy main -Fib-object
		if ( pMainFibObject ){
			pFibObjectCopy->pMainFibObject = pMainFibObject->copyInternal();
			pFibObjectCopy->fibUnderObjects.push_back( pFibObjectCopy->pMainFibObject );
#ifdef FEATURE_FAST_UPDATE
			if ( pFibObjectCopy->pMainFibObject ){
				pFibObjectCopy->pMainFibObject->pSuperiorElement = pFibObjectCopy;
			}
#endif //FEATURE_FAST_UPDATE
		}else{
			pFibObjectCopy->fibUnderObjects.push_back( NULL );
		}
		//copy all existing sub-root-objects
		for ( list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement =
					liSubRootObjects.begin();
				itrActualRootElement != liSubRootObjects.end();
				itrActualRootElement++ ){

			if ( itrActualRootElement->second != NULL ){
				
				pair< longFib, cRoot * > pSubRootObject=
					make_pair( itrActualRootElement->first,
						itrActualRootElement->second->copyInternal() );
				
				if ( pSubRootObject.second ){
					//subobject could be copied
					pFibObjectCopy->liSubRootObjects.push_back( pSubRootObject );
					pFibObjectCopy->fibUnderObjects.push_back( pSubRootObject.second );
				
#ifdef FEATURE_FAST_UPDATE
					pSubRootObject.second->pSuperiorElement = pFibObjectCopy;
#endif //FEATURE_FAST_UPDATE
				}else{/*pSubRootObject->second==NULL
					-> sub-root-object couldn't be copied
					-> give back NULL*/
#ifdef FEATURE_FAST_UPDATE
					pFibObjectCopy->deleteObject();
#else //FEATURE_FAST_UPDATE
					pFibObjectCopy->updateAllValues();
					deleteObject( pFibObjectCopy );
#endif //FEATURE_FAST_UPDATE
					return NULL;
				}
			}
		}
	}else{
		//copy one subobject
		unsignedIntFib uiRemainingObjectpoints = uiObjectPoint;
		unsignedIntFib uiActualObjectpoints = 0;
		
		if ( pMainFibObject ){
			uiActualObjectpoints = pMainFibObject->getNumberOfObjectPoints() + 1;
		}
			
		if ( uiRemainingObjectpoints <= uiActualObjectpoints ){
			//an subobject in the main -Fib-object should be copied
			pFibObjectCopy->pMainFibObject = pMainFibObject->copyInternal( uiRemainingObjectpoints - 1 );
#ifdef FEATURE_FAST_UPDATE
			if ( pFibObjectCopy->pMainFibObject ){
				pFibObjectCopy->pMainFibObject->pSuperiorElement = pFibObjectCopy;
			}
#endif //FEATURE_FAST_UPDATE
			
			if ( pFibObjectCopy->pMainFibObject == NULL ){
				/*pSubRootObject->second==NULL
					-> sub-root-object couldn't be copied
					-> give back NULL*/
				delete pFibObjectCopy;
				return NULL;
			}
			pFibObjectCopy->fibUnderObjects.push_back( pFibObjectCopy->pMainFibObject );
			
			//copy all existing sub-root-objects
			for ( list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement=
						liSubRootObjects.begin();
					itrActualRootElement != liSubRootObjects.end();
					itrActualRootElement++ ){
	
				if ( itrActualRootElement->second != NULL ){
					
					pair< longFib, cRoot * > pSubRootObject =
						make_pair( itrActualRootElement->first,
							itrActualRootElement->second->copyInternal() );
					
					if ( pSubRootObject.second ){
						//subobject could be copied
						pFibObjectCopy->liSubRootObjects.push_back( pSubRootObject );
						pFibObjectCopy->fibUnderObjects.push_back( pSubRootObject.second );
					
#ifdef FEATURE_FAST_UPDATE
						pSubRootObject.second->pSuperiorElement = pFibObjectCopy;
#endif //FEATURE_FAST_UPDATE
					}else{/*pSubRootObject->second==NULL
						-> sub-root-object couldn't be copied
						-> give back NULL*/
#ifdef FEATURE_FAST_UPDATE
						pFibObjectCopy->deleteObject();
#else //FEATURE_FAST_UPDATE
						pFibObjectCopy->updateAllValues();
						deleteObject( pFibObjectCopy );
#endif //FEATURE_FAST_UPDATE
						return NULL;
					}
				}
			}
		}else{
			//add main -Fib-object in the subobjects
			if ( pMainFibObject ){
				pFibObjectCopy->pMainFibObject = pMainFibObject->copyInternal();
				pFibObjectCopy->fibUnderObjects.push_back( pFibObjectCopy->pMainFibObject );
#ifdef FEATURE_FAST_UPDATE
				if ( pFibObjectCopy->pMainFibObject ){
					pFibObjectCopy->pMainFibObject->pSuperiorElement = pFibObjectCopy;
				}
#endif //FEATURE_FAST_UPDATE
			}else{
				pFibObjectCopy->fibUnderObjects.push_back( NULL );
			}
			
			//copy an other subobject
			uiRemainingObjectpoints -= uiActualObjectpoints;
			
			for ( list< pair< longFib, cRoot * > >::const_iterator itrActualRootElement =
						liSubRootObjects.begin();
					itrActualRootElement != liSubRootObjects.end();
					itrActualRootElement++ ){
	
				if ( itrActualRootElement->second != NULL ){
					
					uiActualObjectpoints = itrActualRootElement->second->
						getNumberOfObjectPoints() + 1;
					
					if ( uiRemainingObjectpoints <= uiActualObjectpoints ){
						//subobject to copy found
						pair< longFib, cRoot * > pSubRootObject =
							make_pair( itrActualRootElement->first,
								itrActualRootElement->second->copyInternal( uiRemainingObjectpoints - 1 ) );
						
						if ( pSubRootObject.second ){
							//subobject could be copied
							pFibObjectCopy->liSubRootObjects.push_back( pSubRootObject );
							pFibObjectCopy->fibUnderObjects.push_back( pSubRootObject.second );
#ifdef FEATURE_FAST_UPDATE
							pSubRootObject.second->pSuperiorElement = pFibObjectCopy;
#endif //FEATURE_FAST_UPDATE
							break;
						
						}else{/*pSubRootObject->second==NULL
							-> sub-root-object couldn't be copied
							-> give back NULL*/
#ifdef FEATURE_FAST_UPDATE
							pFibObjectCopy->deleteObject();
#else //FEATURE_FAST_UPDATE
							pFibObjectCopy->updateAllValues();
							deleteObject( pFibObjectCopy );
#endif //FEATURE_FAST_UPDATE
							return NULL;
						}
					}
					uiRemainingObjectpoints -= uiActualObjectpoints;
				}
			}
			if ( pFibObjectCopy->liSubRootObjects.empty() ){
				/*no sub-root-object to copy found
				-> the objectpoint uiObjectPoint dosn't exists
				-> give back NULL*/
#ifdef FEATURE_FAST_UPDATE
				pFibObjectCopy->deleteObject();
#else //FEATURE_FAST_UPDATE
				pFibObjectCopy->updateAllValues();
				deleteObject( pFibObjectCopy );
#endif //FEATURE_FAST_UPDATE
				return NULL;
			}
		}
	}
	//replace the defined variables
	list<cFibVariable*> liDefinedOld  =
		(const_cast<cRoot*>(this))->getDefinedVariables( ED_POSITION );
	list<cFibVariable*> liDefinedCopy =
		pFibObjectCopy->getDefinedVariables( ED_POSITION );
	
	if ( liDefinedOld.size() != liDefinedCopy.size() ){
		//error
#ifdef FEATURE_FAST_UPDATE
		pFibObjectCopy->deleteObject();
#else //FEATURE_FAST_UPDATE
		pFibObjectCopy->updateAllValues();
		deleteObject( pFibObjectCopy );
#endif //FEATURE_FAST_UPDATE
		return NULL;
	}
	list<cFibVariable*>::iterator itrDefinedOld  = liDefinedOld.begin();
	list<cFibVariable*>::iterator itrDefinedCopy = liDefinedCopy.begin();
	for ( ; (itrDefinedOld != liDefinedOld.end()) &&
			(itrDefinedCopy != liDefinedCopy.end());
			itrDefinedOld++, itrDefinedCopy++ ){
		
		pFibObjectCopy->replaceVariable( (*itrDefinedOld), (*itrDefinedCopy) );
	}
	
#ifdef FEATURE_FAST_UPDATE
	pFibObjectCopy->updateAllCounters();
#endif //FEATURE_FAST_UPDATE
	return pFibObjectCopy;
}


/**
 * This method returns the extern object element which calls /uses this
 * root-object.
 *
 * @see liPExtObjectElm
 * @see setCallingFibElement()
 * @see unsetCallingFibElement()
 * @see cExtObject
 * @see evalueObject()
 * @return extern object element which calls /uses this root-object
 * 	(if NULL non exists)
 */
cExtObject * cRoot::getCallingExtObject(){
	
	if ( liPExtObjectElm.empty() ){
		//no external object element which calls this root element
		return NULL;
	}
	return liPExtObjectElm.back();
}


/**
 * This method sets the given extern object element as the element
 * which calls /uses this root-object.
 *
 * @see liPExtObjectElm
 * @see unsetCallingFibElement()
 * @see cExtObject
 * @see evalueObject()
 * @param pInExtObjectElm extern object element which calls /uses this
 * 	root-object
 */
void cRoot::setCallingFibElement( cExtObject * pInExtObjectElm ){
	
	if ( pInExtObjectElm == NULL ){
		//no new calling /using Fib element to set
		return;
	}
	backupVariablesValues( true );
	if ( ! liPExtObjectElm.empty() ){
		/*if this root element was called / used befor
		 -> store all variable values of variables below this root element*/
		liLiStoredBelowVariables.push_back( list< cFibVariable * >() );
		list< cFibVariable * > & liStoredBelowVariables =
			liLiStoredBelowVariables.back();
		
		//get variables used below
		const list< cFibVariable * > liVariablesDefinedBelow =
			getDefinedVariables( ED_BELOW );
		
#ifdef DEBUG_EVALUE
		const long lId = pInExtObjectElm->getIdentifier();
		const int iNumberExistingCalling = liPExtObjectElm.size();
		printf( "cRoot(=%p)::setCallingFibElement() store below defined variables (%i calling elements wher set before, the actual id is %li): ", this, iNumberExistingCalling, lId );
#endif //DEBUG_EVALUE
		
		for ( list< cFibVariable * >::const_iterator
				itrActualVariable = liVariablesDefinedBelow.begin();
				itrActualVariable != liVariablesDefinedBelow.end();
				itrActualVariable++ ){
			
#ifdef DEBUG_EVALUE
			printf( "%lf, ", (*itrActualVariable)->getValue() );
#endif //DEBUG_EVALUE
			liStoredBelowVariables.push_back( new cFibVariable( **itrActualVariable ) );
		}
#ifdef DEBUG_EVALUE
		printf( "\n " );
#endif //DEBUG_EVALUE
	}//end if store defined variables below
	liPExtObjectElm.push_back( pInExtObjectElm );
	
	//set the input variable values of the calling /using extern object element
	const cVectorExtObject * vecInputValuesGiven =
		pInExtObjectElm->getInputVector();
	const unsignedIntFib uiNumberOfInputValues =
		vecInputValuesGiven->getNumberOfElements();
	list< pair< cFibVariable *, doubleFib > >::iterator
			itrInputVariable = liInputVariables.begin();
	for ( unsignedIntFib uiActualInputValue = 1;
			( itrInputVariable != liInputVariables.end() ) &&
			( uiActualInputValue <= uiNumberOfInputValues ) ;
			uiActualInputValue++, itrInputVariable++ ){
		
		if ( itrInputVariable->first == NULL ){
			//no input variable to set
			continue;//can't transver value -> skip it
		}//else transfer value
		itrInputVariable->first->setValue(
			vecInputValuesGiven->getValue( uiActualInputValue ) );
	}
	//set missing input variables to ther default value
	for ( ; ( itrInputVariable != liInputVariables.end() ); itrInputVariable++ ){
		
		if ( itrInputVariable->first == NULL ){
			//no input variable to set
			continue;//can't transver value -> skip it
		}
		//set default value
		itrInputVariable->first->setValue(
			itrInputVariable->second );
	}
}


/**
 * This Method unsets the actual calling / using Fib element.
 * @see liPExtObjectElm
 * @see setCallingFibElement()
 * @see evalueObject()
 */
void cRoot::unsetCallingFibElement(){
	
	if ( ! liPExtObjectElm.empty() ){
		//an using Fib element exists -> unset it
		backupVariablesValues( false );
		if ( ! liLiStoredBelowVariables.empty() ){
			/*if this root element was called / used befor the actual calling element
			-> restore all variable values of variables above this root element*/
			
			//get variables used below
			list< cFibVariable * > liVariablesDefinedBelow =
				getDefinedVariables( ED_BELOW );
		
			list< cFibVariable * >::iterator
				itrActualVariable = liVariablesDefinedBelow.begin();
			
			list< cFibVariable * > & liStoredBelowVariables =
				liLiStoredBelowVariables.back();
			
#ifdef DEBUG_EVALUE
			const long lId = liPExtObjectElm.back()->getIdentifier();
			const int iNumberExistingCalling = liPExtObjectElm.size();
			printf( "cRoot(=%p)::unsetCallingFibElement() restore below defined variables (unset %i'th calling element with id %li): ", this, iNumberExistingCalling, lId );
#endif //DEBUG_EVALUE
			for ( list< cFibVariable * >::iterator
					itrActualStoredVariable = liStoredBelowVariables.begin();
					itrActualStoredVariable != liStoredBelowVariables.end() &&
					itrActualVariable != liVariablesDefinedBelow.end();
					itrActualStoredVariable++, itrActualVariable++ ){
				
				(**itrActualVariable) = (**itrActualStoredVariable);
#ifdef DEBUG_EVALUE
				printf( "%lf, ", (*itrActualVariable)->getValue() );
#endif //DEBUG_EVALUE
			}
#ifdef DEBUG_EVALUE
			printf( "\n " );
#endif //DEBUG_EVALUE
			// remove restored input variables from stored input variables stack
			while ( ! liStoredBelowVariables.empty() ){
				//the old values will be overwritten
				delete (liStoredBelowVariables.back());
				liStoredBelowVariables.pop_back();
			}
			liLiStoredBelowVariables.pop_back();
		}//end if ( ! liLiStoredBelowVariables.empty() ) restore below defined variables
		liPExtObjectElm.pop_back();
	}
}














