
//TODO check

/**
 * @file tFibNodeHandler_integrateFibObjectIntoNode
 * file name: tFibNodeHandler_integrateFibObjectIntoNode.cpp
 * @author Betti Oesterholz
 * @date 17.02.2014
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for testing the integrateFibObjectIntoNode() method of
 * the cFibNodeHandler.
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
 * This test is for testing the integrateFibObjectIntoNode() method of
 * the cFibNodeHandler.
 *
 * The Fib test objects are loaded from the files in the folder pDirTestObjects.
 * It contains pairs of (Xml) Fib objects to test the
 * integrateFibObjectIntoNode() with.
 *
 * Every testcase is stored in two differnt files the DIR_TESTDATA
 * folder. (The standardfolder for DIR_TESTDATA is
 * "testObjects/integrateFibObjectIntoNode/".)
 * One file ends with "_org.xml". It stores the original Fib object.
 * The other file ends with "_change.xml". It contains the change Fib object
 * wich should be integrated into the original Fib object.
 * The test will create a containing node (pContainingNode) for the
 * original Fib object.
 * If there is a comment with the key "containing node", the contained
 * Fib element of the comment will be choosen as the containing node, else
 * the containing node will conatin the entire original Fib object (pOriginalFibObject).
 * Then the test will generate and set some random Fib nodes for the
 * original Fib object.
 * In the main step it will call integrateFibObjectIntoNode( pContainingNode,
 * pOriginalFibObject, pChangedFibObject, pChangedBy (random) ) .
 * After the call it will be checked:
 * 	- if pOriginalFibObject is equal to pChangedFibObject.
 * 	- the containing node and all nodes superior to it, send a node
 * 	  change event with pChangedBy as the changed by object
 *
 *
 * What's tested of class cFibNodeHandler class:
 * 	- bool integrateFibObjectIntoNode( cFibNode * pContainingNode, cFibElement * pOriginalFibObjectToReplace, cFibElement * pNewFibObject, const QObject * pChangedBy = NULL );
 *
 * @see cFibNodeHandler
 * @see cFibNode
 * @see cFibElement
 *
 * call: tFibNodeHandler_integrateFibObjectIntoNode [DIR_TESTDATA]
 *
 * parameters:
 * 	DIR_TESTDATA
 * 		The path wher the testdata could be found. The standardfolder is
 * 		"testObjects/integrateFibObjectIntoNode/".
 */
/*
History:
17.02.2014  Oesterholz  created
*/

#include "version.h"

#include "cFibNodeHandler.h"

#include <QObject>

#include "cFibElement.h"
#include "cComment.h"
#include "cFolder.h"

#include "cFibNode.h"
#include "lFibNodeChanged.h"
#include "eFibNodeChangedEvent.h"
#include "cFibScalar.h"


#include <string>
#include <utility>
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <ctime>


#ifndef DIR_TESTOBJECTS
	#define DIR_TESTOBJECTS "testObjects/integrateFibObjectIntoNode/"
#endif


using namespace fib::nCreator;
using namespace fib;
using namespace std;




const char * pDirTestObjects = DIR_TESTOBJECTS;


list< string > loadTestFileList( const string szTestFolderName );
map< string, string > loadTestCases( const string szTestFolderName );

/**
 * This class is a dummy listener for Fib node changes.
 */
class cFibNodeChangeListenerDummy: public lFibNodeChanged {
public:
	/**
	 * constructor
	 */
	cFibNodeChangeListenerDummy():
			pFibNode( NULL ), pFibObject( NULL ) {
		//nothing to do
	}
	
	/**
	 * destructor
	 */
	~cFibNodeChangeListenerDummy() {
		
		while ( ! liReceivedEvents.empty() ) {
			
			delete liReceivedEvents.back();
			liReceivedEvents.pop_back();
		}
	}
	
	/**
	 * Event method
	 * It will be called every time a Fib node (cFibNode), at which
	 * this object is registered, was changed.
	 *
	 * @param pFibNodeChanged a pointer to the event, with the information
	 * 	about the changed Fib node
	 */
	virtual void fibNodeChangedEvent(
			const eFibNodeChangedEvent * pFibNodeChanged ) {
		
		eFibNodeChangedEvent * pFibNodeChangedCopy =
			new eFibNodeChangedEvent( *pFibNodeChanged );
			
		if ( pFibNodeChangedCopy->getChangedNode() != NULL ) {
			//the copy event should not be changed by later events
			pFibNodeChangedCopy->getChangedNode()->
				unregisterNodeChangeListener( pFibNodeChangedCopy );
		}
		liReceivedEvents.push_back( pFibNodeChangedCopy );
	}
	
	
	/**
	 * @return the name of this class
	 */
	virtual std::string getName() const {
		
		return "cFibNodeChangeListenerDummy";
	}
	
	
//members:
	/**
	 * A pointer to the node for which changes this object listens.
	 */
	cFibNode * pFibNode;
	
	/**
	 * The original Fib object for the Fib node, for which changes this
	 * object listens.
	 */
	cFibElement * pFibObject;
	
	/**
	 * A copy of original Fib object for the Fib node, for which changes
	 * this object listens.
	 */
	cFibElement * pFibObjectCopy;
	
	/**
	 * The list with the by this class received node changed events.
	 */
	list< eFibNodeChangedEvent * > liReceivedEvents;
	
	
};//end class cFibNodeChangeListenerDummy




int main(int argc, char* argv[]) {

	unsigned long ulTestphase = 0;//actual phase of the test
	int iReturn = 0;//return value of the test; the number of occured errors
	int iFailedTestphases = 0;//return value of the test; the number of occured errors
	list< pair< string, string > > liErrorsInTestCase;
	
	srand( time(NULL) );
	
	if ( argc >= 2 ) {
		//one parameter given; get parameter test data path
		pDirTestObjects = argv[1];
	}
	
	cout<<endl<<"Running test for Fib object cFibNodeHandler integrateFibObjectIntoNode()"<<endl;
	cout<<      "========================================================================"<<endl;
	
	//load the testfolder list
	const string szFilePath = string( pDirTestObjects );
	
	map< string, string > mapTestCases = loadTestCases( szFilePath );
	
	if ( mapTestCases.empty() ) {
		cerr<<"Error: No testcases to test."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//for each test folder
	for ( map< string, string >::iterator itrTestCase = mapTestCases.begin();
			itrTestCase != mapTestCases.end(); itrTestCase++ ) {
		
		unsigned int uiErrorsInTestphase = 0;
		const string szOriginalTestFile = itrTestCase->first;
		const string szChangedTestFile  = itrTestCase->second;
		ulTestphase++;
		cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the Fib object in file \""<< szOriginalTestFile <<"\" (changed: \""<<szChangedTestFile<<"\")"<<endl;
		

		//load both Fib objects
		//load the original Fib object
		const string szPathFibObjectToTestOrg = szFilePath + szOriginalTestFile;
		ifstream inFileOrg( szPathFibObjectToTestOrg.c_str() );
		
		intFib outStatus = 0;
		cFibElement * pOriginalFibObject =
			cFibElement::restoreXml( inFileOrg , &outStatus );
		
		if ( ( outStatus == 0 ) && ( pOriginalFibObject != NULL ) ) {
			cout<<"Restoring original Fib object in the Xml format from the file "<<
				szPathFibObjectToTestOrg <<" successfull."<<endl;
		}else{
			cerr<<"Error: Restoring original Fib object in the Xml format from the file "<<
				szPathFibObjectToTestOrg <<" not successfull. (return status="<< outStatus <<")"<<endl;
			uiErrorsInTestphase++;
			iReturn += uiErrorsInTestphase;
			iFailedTestphases++;
			if ( pOriginalFibObject ) {
				pOriginalFibObject->deleteObject();
			}
			liErrorsInTestCase.push_back( *itrTestCase );
			continue;
		}//-> pOriginalFibObject != NULL
		//load the changed Fib object
		const string szPathFibObjectToTestChanged = szFilePath + szOriginalTestFile;
		ifstream inFileChanged( szPathFibObjectToTestChanged.c_str() );
		
		outStatus = 0;
		cFibElement * pChangedFibObject =
			cFibElement::restoreXml( inFileChanged , &outStatus );
		
		if ( ( outStatus == 0 ) && ( pChangedFibObject != NULL ) ) {
			cout<<"Restoring changed Fib object in the Xml format from the file "<<
				szPathFibObjectToTestChanged <<" successfull."<<endl;
		}else{
			cerr<<"Error: Restoring changed Fib object in the Xml format from the file "<<
				szPathFibObjectToTestChanged <<" not successfull. (return status="<< outStatus <<")"<<endl;
			uiErrorsInTestphase++;
			iReturn += uiErrorsInTestphase;
			iFailedTestphases++;
			if ( pChangedFibObject ) {
				pChangedFibObject->deleteObject();
			}
			pOriginalFibObject->deleteObject();
			liErrorsInTestCase.push_back( *itrTestCase );
			continue;
		}//-> pChangedFibObject != NULL
		//create a clone on the fib object to check to compare the result with
		cFibElement * pChangedFibObjectClone = pChangedFibObject->clone();
		if ( pChangedFibObjectClone == NULL ) {
			cerr<<"Error: No clone could be created from the changed Fib object."<<endl;
			uiErrorsInTestphase++;
			iReturn += uiErrorsInTestphase;
			iFailedTestphases++;
			pChangedFibObject->deleteObject();
			pOriginalFibObject->deleteObject();
			liErrorsInTestCase.push_back( *itrTestCase );
			continue;
		}
		cFibElement * pOriginalFibObjectClone = pOriginalFibObject->clone();
		if ( pOriginalFibObjectClone == NULL ) {
			cerr<<"Error: No clone could be created from the changed Fib object."<<endl;
			uiErrorsInTestphase++;
			iReturn += uiErrorsInTestphase;
			iFailedTestphases++;
			pChangedFibObject->deleteObject();
			pChangedFibObjectClone->deleteObject();
			pOriginalFibObject->deleteObject();
			liErrorsInTestCase.push_back( *itrTestCase );
			continue;
		}
		
	//create a containing node (pContainingNode) for the original Fib object
		//else the containing node will conatin the entire original Fib object (pOriginalFibObject)
		cFibElement * pFibObjectForContainingNode = pOriginalFibObject;
		//search for a comment with the key "containing node"
		for ( cFibElement * pActualComment =
				pOriginalFibObject->getNextFibElement( 'c' );
				pActualComment != NULL;
				pActualComment = pActualComment->getNextFibElement( 'c' ) ) {
			
			if ( (static_cast<cComment*>(
					pActualComment))->getKey() == "containing node" ) {
				//choose the contained Fib element of the comment for the containing node
				pFibObjectForContainingNode = pActualComment->getNextFibElement();
				break;
			}
		}
		cout<<"Fib element for containig node: "<<
			pFibObjectForContainingNode->getNumberOfElement()<<" of type "<<
			pFibObjectForContainingNode->getType()<<endl;
		//if the original Fib object where to integrate is equal the changed Fib object
		const bool bOriginalAndChangedEqual =
			pFibObjectForContainingNode->equal( *pChangedFibObject, false );
		
		//create containing node
		cFibNodeHandler * pNodeHandler = cFibNodeHandler::getInstance();
		
		//create a dummy Fib node change listener
		cFibNodeChangeListenerDummy * pFibNodeChangeListener =
			new cFibNodeChangeListenerDummy();
		//get a node for the Fib object
		cFibNode * pContainingNode = pNodeHandler->getNodeForFibObject(
			pFibObjectForContainingNode, pFibNodeChangeListener );
		//remember the Fib nade and Fib object for the change listener
		pFibNodeChangeListener->pFibNode   = pContainingNode;
		pFibNodeChangeListener->pFibObject = pFibObjectForContainingNode;
		pFibNodeChangeListener->pFibObjectCopy =
			pOriginalFibObjectClone->getFibElement(
				pFibObjectForContainingNode->getNumberOfElement() );
		/*a list with all dummy Fib node change listeners (which also store
		 *the Fib nodes and their Fib objects)*/
		list< cFibNodeChangeListenerDummy * > liFibNodeChangeListeners;
		liFibNodeChangeListeners.push_back( pFibNodeChangeListener );
		
		//generate some random nodes for some random choosen Fib elements
		const unsigned int uiGenerateNewNodeAllMaxElements =
			log( pOriginalFibObject->getNumberOfElements() ) + 8;
		
		cFibNode * pContainingNodeTmp;
		for ( cFibElement * pNodeFibElement = pOriginalFibObject;
				pNodeFibElement != NULL;
				pNodeFibElement = pNodeFibElement->getFibElement(
					rand() % uiGenerateNewNodeAllMaxElements + 1 ) ) {
			//get the Fib node for the random choosen Fib element
			pFibNodeChangeListener = new cFibNodeChangeListenerDummy();
			//get a node for the Fib object
			pContainingNodeTmp = pNodeHandler->getNodeForFibObject(
				pNodeFibElement, pFibNodeChangeListener );
			//remember the Fib nade and Fib object for the change listener
			pFibNodeChangeListener->pFibNode   = pContainingNodeTmp;
			pFibNodeChangeListener->pFibObject = pNodeFibElement;
			pFibNodeChangeListener->pFibObjectCopy =
				pOriginalFibObjectClone->getFibElement(
					pNodeFibElement->getNumberOfElement() );
			liFibNodeChangeListeners.push_back( pFibNodeChangeListener );
		}
		cout<<"Random generated Fib nodes: "<<liFibNodeChangeListeners.size()<<endl;
		
		//get all Fib nodes superior to the containig Fib node
		set< cFibNode* > setSuperiorNodes;
		for ( cFibElement * pActualFibElement = pFibObjectForContainingNode;
				pActualFibElement != NULL;
				pActualFibElement = pActualFibElement->getSuperiorFibElement() ) {
			
			cFibNode * pSuperiorNode = pNodeHandler->getContainingNodeForFibObject(
				pActualFibElement );
			setSuperiorNodes.insert( pSuperiorNode );
		}
		
		
		//generate random QObject as a chnger object
		cFibScalar * pChangedBy = new cFibScalar( 12.3, "changer" );
		
		//main part: call integrateFibObjectIntoNode()
		cout<<endl<<"pNodeHandler->integrateFibObjectIntoNode( pContainingNode="<<
			pContainingNode<<", pFibObjectForContainingNode="<<
			pFibObjectForContainingNode<<" (nr: "<<
			pFibObjectForContainingNode->getNumberOfElement()<<" type:"<<
			pFibObjectForContainingNode->getType()<<"), pChangedFibObject="<<
			pChangedFibObject<<" (nr: "<<
			pChangedFibObject->getNumberOfElement()<<" type:"<<
			pChangedFibObject->getType()<<"), pChangedBy="<<pChangedBy<<" );"<<endl;
		pNodeHandler->integrateFibObjectIntoNode( pContainingNode, pFibObjectForContainingNode,
			pChangedFibObject, pChangedBy );
		
		
		//check if pFibObjectForContainingNode is equal to pChangedFibObject
		if ( ! pFibObjectForContainingNode->equal( *pChangedFibObjectClone ) ) {
			cerr<<"Error: The original Fib object is not equal to the "<<
				"changed (clone) Fib object."<<endl;
			uiErrorsInTestphase++;
		}
		
		if ( bOriginalAndChangedEqual ) {
			//no events send
			for ( list< cFibNodeChangeListenerDummy * >::iterator
					itrChangeListener = liFibNodeChangeListeners.begin();
					itrChangeListener != liFibNodeChangeListeners.end();
					++itrChangeListener ) {
				
				if ( ! (*itrChangeListener)->liReceivedEvents.empty() ) {
					cerr<<"Error: The Fib node "<<(*itrChangeListener)->pFibNode<<
						" has send node change events, but nothing is changed."<<endl;
					uiErrorsInTestphase++;
					continue;
				}
			}
		}else{//check the nodes for the changed events
			/* the containing node and all nodes superior to it, have received
			 * a node change event with pChangedBy as the changed by object*/
			//get change listener for superior nodes
			list< cFibNodeChangeListenerDummy * > liSuperiorChangeListeners;
			for ( list< cFibNodeChangeListenerDummy * >::iterator
					itrChangeListener = liFibNodeChangeListeners.begin();
					itrChangeListener != liFibNodeChangeListeners.end();
					++itrChangeListener ) {
				if ( setSuperiorNodes.find( (*itrChangeListener)->pFibNode ) !=
						setSuperiorNodes.end() ){
					//Fib node for change listener is superior Fib node to containing node
					liSuperiorChangeListeners.push_back( *itrChangeListener );
				}
			}
			
			for ( list< cFibNodeChangeListenerDummy * >::iterator
					itrChangeListener = liSuperiorChangeListeners.begin();
					itrChangeListener != liSuperiorChangeListeners.end();
					++itrChangeListener ) {
				
				if ( (*itrChangeListener)->liReceivedEvents.empty() ) {
					cerr<<"Error: The superior Fib node "<<(*itrChangeListener)->pFibNode<<
						" has send no node change events, but somthing is changed."<<endl;
					uiErrorsInTestphase++;
					continue;
				}
			}
		}
		for ( list< cFibNodeChangeListenerDummy * >::iterator
				itrChangeListener = liFibNodeChangeListeners.begin();
				itrChangeListener != liFibNodeChangeListeners.end();
				++itrChangeListener ) {
			
			if ( pNodeHandler->isValidNode( (*itrChangeListener)->pFibNode ) ) {
				//the node of the Fib node change listeners is for the original Fib object
				if ( (*itrChangeListener)->pFibNode->getFibObject() == NULL ) {
					
					cerr<<"Error: The Fib node "<<(*itrChangeListener)->pFibObject<<
						" of the Fib change listener ("<<(*itrChangeListener)<<
						") has no Fib object."<<endl;
					uiErrorsInTestphase++;
				}else if ( (*itrChangeListener)->pFibNode->getFibObject()->getMasterRoot() !=
						pOriginalFibObject ) {
					cerr<<"Error: The Fib object "<<(*itrChangeListener)->pFibNode->getFibObject()<<
						" of the Fib node "<<(*itrChangeListener)->pFibNode<<
						" of the Fib change listener ("<<(*itrChangeListener)<<
						") has not the original Fib object as its master root element."<<endl;
					uiErrorsInTestphase++;
				}
				
				//the Fib element of the Fib node change listeners is in the original Fib object
				if ( (*itrChangeListener)->pFibObject->getMasterRoot() !=
						pOriginalFibObject ) {
					cerr<<"Error: The Fib element "<<(*itrChangeListener)->pFibObject<<
						" of the Fib change listener ("<<(*itrChangeListener)<<
						") has not the original Fib object as its master root element."<<endl;
					uiErrorsInTestphase++;
				}
			}else{//node was deleted
				if ( (*itrChangeListener)->liReceivedEvents.empty() ) {
					cerr<<"Error: The Fib node "<<(*itrChangeListener)->pFibNode<<
						" was deleted but did not send a node change event."<<endl;
					uiErrorsInTestphase++;
					continue;
				}
				if ( (*itrChangeListener)->liReceivedEvents.back()->isDeleted() ) {
					cerr<<"Error: The Fib node "<<(*itrChangeListener)->pFibNode<<
						" was deleted but did not has as last node change event"<<
						" a event for Fib node deleted."<<endl;
					uiErrorsInTestphase++;
				}
			}
		}
		
		/*check all Fib nodes, which have a changed Fib object, received one
		 * Fib node changed event and Fib nodes, which have not a changed
		 * Fib object, received no Fib node changed event */
		for ( list< cFibNodeChangeListenerDummy * >::iterator
				itrChangeListener = liFibNodeChangeListeners.begin();
				itrChangeListener != liFibNodeChangeListeners.end();
				++itrChangeListener ) {
			
			if ( (*itrChangeListener)->liReceivedEvents.empty() ) {
				//no change event received -> Fib object should not have changed
				if ( ! ( (*itrChangeListener)->pFibObjectCopy->equal(
						*((*itrChangeListener)->pFibObject ) ) ) ) {
					cerr<<"Error: The Fib node "<<(*itrChangeListener)->pFibNode<<
						" received no Fib node change event, but the Fib object was changed."<<endl;
					uiErrorsInTestphase++;
				}
			} else {//change event received -> Fib object should have changed
				if ( (*itrChangeListener)->liReceivedEvents.size() != 1 ) {
					cerr<<"Error: The Fib node "<<(*itrChangeListener)->pFibNode<<
						" received more than one Fib node change event."<<endl;
					uiErrorsInTestphase++;
				}
				if ( ! (*itrChangeListener)->liReceivedEvents.back()->
					isElementChanged( (*itrChangeListener)->pFibObject,
						eFibNodeChangedEvent::DELETED ) ) {
					//Fib element was not deleted
					if ( (*itrChangeListener)->pFibObjectCopy->equal(
							*((*itrChangeListener)->pFibObject) ) ) {
						cerr<<"Error: The Fib node "<<(*itrChangeListener)->pFibNode<<
							" received Fib node change events, but the Fib object was not changed."<<endl;
						uiErrorsInTestphase++;
					}
				}
			}
		}
		
		if ( uiErrorsInTestphase != 0 ) {
			iReturn += uiErrorsInTestphase;
			iFailedTestphases++;
			liErrorsInTestCase.push_back( *itrTestCase );
		}
		pOriginalFibObjectClone->deleteObject();
		pChangedFibObjectClone->deleteObject();
		/*the node handler will destroy the original Fib object
		+ the changed Fib object should be integrated into the original
		  Fib object and thus also be destroyed by the node handler*/
		delete pNodeHandler;
	}
	
	if ( iReturn == 0 ) {
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured in "<<iFailedTestphases<<" folders"<<endl;
		
		cerr<<"Errors wher in test cases: ";
		for ( list< pair< string, string > >::const_iterator
				itrTestCase = liErrorsInTestCase.begin();
				itrTestCase != liErrorsInTestCase.end(); itrTestCase++ ) {
			
			cout<<itrTestCase->first<<"("<<itrTestCase->second<<"); ";
		}
		cout<<endl;
	}

	return iReturn;
}


/**
 * This function loads the map with the testcases.
 * Each testcase consists of two files.
 * One file ends with "_org.xml". It stores the original Fib object.
 * The other file ends with "_change.xml". It contains the change Fib object.
 *
 * @param szTestFolderName the name of the folder, which contains the files
 * 	with the testdata
 * @return a map with the testcases
 * 	key: the filname of the file, which stores the original Fib object
 * 	value: the filname of the file, which stores the change Fib object
 * 		for the key original Fib object
 */
map< string, string > loadTestCases( const string szTestFolderName ) {
	//load all testfiles
	const list< string > liTestFiles = loadTestFileList( szTestFolderName );
	//find matching pairs in the testfiles list
	//sort testfiles by inserting them into a set
	set< string > setTestFiles;
	setTestFiles.insert( liTestFiles.begin(), liTestFiles.end() );
	
	map< string, string > mapTestcases;
	
	//as long as two files to match exists -> try to match them
	while ( 1 < setTestFiles.size() ) {
		
		const string strFirstTestFile = *(setTestFiles.begin());
		setTestFiles.erase( setTestFiles.begin() );
		const string strSecondTestFile = *(setTestFiles.begin());
		
		/*check if the first testfile ends with "_org.xml" and the second
		 *with "_change.xml"
		 *+ check if the remaining of the file name is equal*/
		if ( ( strFirstTestFile.compare(
					strFirstTestFile.size() - 8, 8, "_org.xml" ) == 0 ) &&
				( strSecondTestFile.compare(
					strSecondTestFile.size() - 11, 11, "_change.xml" ) == 0 ) &&
				( strFirstTestFile.compare( 0, strFirstTestFile.size() - 8,
					strSecondTestFile, 0, strSecondTestFile.size() - 11 ) == 0 ) ) {
			//files for next testcase found
			setTestFiles.erase( setTestFiles.begin() );
			mapTestcases.insert( pair< string, string >(
				strFirstTestFile, strSecondTestFile ) );
		}
		
		/*check if the first testfile ends with "_change.xml" and the second
		 *with "_org.xml"*/
		if ( ( strSecondTestFile.compare(
					strSecondTestFile.size() - 8, 8, "_org.xml" ) == 0 ) &&
				( strFirstTestFile.compare(
					strFirstTestFile.size() - 11, 11, "_change.xml" ) == 0 ) &&
				( strSecondTestFile.compare( 0, strSecondTestFile.size() - 8,
					strFirstTestFile, 0, strFirstTestFile.size() - 11 ) == 0 ) ) {
			//files for next testcase found
			setTestFiles.erase( setTestFiles.begin() );
			mapTestcases.insert( pair< string, string >(
				strSecondTestFile, strFirstTestFile ) );
		}
	}//end while there are minimum 2 test files
	
	return mapTestcases;
}



/**
 * This function reads the given directory and gives back all file names
 * of files it contains.
 * This files should be used as a testcases.
 *
 * @param szTestFolderName the name of the folder, which contains the files
 * 	with the testdata
 * @return the list of files in the given folder
 */
list< string > loadTestFileList( const string szTestFolderName ) {
	
	cFolder folder( szTestFolderName );
	
	return folder.getFiles();
}














