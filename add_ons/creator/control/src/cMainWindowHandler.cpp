
//TODO check

/**
 * @file cMainWindowHandler
 * file name: cMainWindowHandler.h
 * @author Betti Oesterholz
 * @date 24.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for handling the main windows for the
 * Fib creator application.
 *
 *
 * Copyright (C) @c GPL3 2013 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
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
 * This file implements a class for handling the main windows for the
 * Fib creator application.
 * @see cFibObjectMainWindow
 * It should store all the main windows of the application. It will also
 * delete all windows it stores, when the application ends.
 *
 * @pattern singelton
 */
/*
History:
24.06.2013  Oesterholz  created
18.05.2014  Oesterholz  openFibObjectFromFile(): opens with last choosen file
*/


//TODO switches for test proposes
#define DEBUG


#include "cMainWindowHandler.h"

#include <iostream>
#include <fstream>

#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>

#include "cRoot.h"
#include "cPoint.h"
#include "cVectorPosition.h"
#include "cOptionalPart.h"
#include "cMultimediaInfo.h"
#include "cDomains.h"
#include "cDomainVector.h"
#include "cDomainNaturalNumber.h"
#include "cDomainNaturalNumberBit.h"
#include "cTypeDimension.h"
#include "cTypeProperty.h"

#include "cDialogNewFibObject.h"
#include "cFibObjectInfo.h"
#include "cFibObjectSource.h"
#include "cFibObjectSourcePath.h"


using namespace std;
using namespace fib::nCreator;





/**
 * A pointer to the main window handler object.
 */
cMainWindowHandler * cMainWindowHandler::pMainWindowHandler = NULL;



namespace fib{
namespace nCreator{
namespace nMainWindowHandler{

	/**
	 * This class is for deleting the Fib main window handler when the
	 * program ends.
	 * @see cMainWindowHandlerDeleter
	 */
	class cMainWindowHandlerDeleter{
	public:
		
		/**
		 * destructor which deletes the Fib node handler if not allready deleted
		 */
		~cMainWindowHandlerDeleter(){
			
			DEBUG_OUT_L2(<<"cMainWindowHandlerDeleter("<<this<<")::~cMainWindowHandlerDeleter() called"<<endl<<flush);
	
			if ( cMainWindowHandler::pMainWindowHandler != NULL ){
				//delete main window handler
				delete cMainWindowHandler::pMainWindowHandler;
				cMainWindowHandler::pMainWindowHandler = NULL;
			}
		}
		
	};//end class cMainWindowHandlerDeleter
	/**
	 * Object to delete the main window handler when the programm ends.
	 */
	cMainWindowHandlerDeleter fibNodeHandlerDeleter;
	
};//end namespace nMainWindowHandler
};//end namespace nCreator
};//end namespace fib



/**
 * constructor for the main window handler
 */
cMainWindowHandler::cMainWindowHandler(){
	
	DEBUG_OUT_L2(<<"cMainWindowHandler("<<this<<")::cMainWindowHandler() called"<<endl<<flush);
			
	if ( pMainWindowHandler != NULL ){
		//delete main window handler
		delete pMainWindowHandler;
		pMainWindowHandler = NULL;
	}
	pMainWindowHandler = this;
}


/**
 * destructor
 */
cMainWindowHandler::~cMainWindowHandler(){
	
	DEBUG_OUT_L2(<<"cMainWindowHandler("<<this<<")::~cMainWindowHandler() called"<<endl<<flush);
	
	for ( set< QMainWindow * >::iterator itrMainWindow = setMainWindows.begin();
			itrMainWindow != setMainWindows.end(); itrMainWindow++ ){
		delete (*itrMainWindow);
	}
	setMainWindows.clear();
	
	pMainWindowHandler = NULL;
	
	//end application
	QApplication::quit();
}


/**
 * @return a pointer to instance of the main window handler
 */
cMainWindowHandler * cMainWindowHandler::getInstance(){
	
	if ( pMainWindowHandler == NULL ){
		//create a new instance
		pMainWindowHandler = new cMainWindowHandler();
	}//else return existing instance
	return pMainWindowHandler;
}


/**
 * This function registers the given main window in this handler.
 * This handler will than take care that the main window is deleted
 * befor the application ends.
 * @see setMainWindows
 *
 * @param pMainWindow a pointer to the main window to register
 */
void cMainWindowHandler::registerMainWindow( cFibObjectMainWindow * pMainWindow ){
	
	DEBUG_OUT_L2(<<"cMainWindowHandler("<<this<<")::registerMainWindow( pMainWindow="<<pMainWindow<<") called"<<endl<<flush);
	if ( pMainWindow == NULL ){
		//no main window to register
		return;
	}
	mutexFibNodeHandler.lock();
	setMainWindows.insert( pMainWindow );
	mutexFibNodeHandler.unlock();
}


/**
 * This function unregisters the given main window from this handler.
 * If you have unregister a main window, than you have the
 * responsibility for the main window (e. g. you need to delete it).
 * @see setMainWindows
 *
 * @param pMainWindow a pointer to the main window to unregister
 * @return true if the given main window was unregister, else false
 */
bool cMainWindowHandler::unregisterMainWindow( cFibObjectMainWindow * pMainWindow ){
	
	DEBUG_OUT_L2(<<"cMainWindowHandler("<<this<<")::unregisterMainWindow( pMainWindow="<<pMainWindow<<") called"<<endl<<flush);
	if ( pMainWindow == NULL ){
		//no main window to unregister
		return false;
	}
	mutexFibNodeHandler.lock();
	const unsigned int bWindowErased = setMainWindows.erase( pMainWindow );
	mutexFibNodeHandler.unlock();
	
	DEBUG_OUT_L2(<<"cMainWindowHandler("<<this<<")::unregisterMainWindow( pMainWindow="<<pMainWindow<<") done window was "<<(bWindowErased ? "erased" : "not erased" )<<endl<<flush);
	return ( bWindowErased != 0 );
}


/**
 * This method checks if the given pointer points to a in this handler
 * existing main window.
 * A main window wich was registered in this handler could be missing,
 * if it was unregistered or deleted.
 * @see setMainWindows
 *
 * @param pMainWindow a pointer to the main window to check
 * @return true if the given main window points to an existing main
 * 	window in this handler, else false
 */
bool cMainWindowHandler::isRegisterMainWindow( const cFibObjectMainWindow * pMainWindow ){
	
	if ( pMainWindow == NULL ){
		//no main window to find
		return false;
	}
	mutexFibNodeHandler.lock();
	
	const bool bMainWindowFound =
		( setMainWindows.find( const_cast< cFibObjectMainWindow * >( pMainWindow ) ) !=
			setMainWindows.end() );
	mutexFibNodeHandler.unlock();
	
	return bMainWindowFound;
}


/**
 * This method returns a new main window for the given Fib object.
 *
 * @see setMainWindows
 * @param pFibObject the Fib object for the main window to return
 * 	The responsibility for the Fib object will go to the Fib object
 * 	node handler @see cFibNodeHandler
 * 	So don't delete it.
 * @param bIsChangebel true (standard value) if (the Fib element
 * 	 pFibObject of) the to create node is changebel, else false
 * @return the a new main window for the given Fib object
 */
cFibObjectMainWindow * cMainWindowHandler::getNewMainWindowForFibObject(
		cFibElement * pFibObject, const bool bIsChangebel ){
	
	DEBUG_OUT_L2(<<"cMainWindowHandler("<<this<<")::getNewMainWindowForFibObject( pFibObject="<<pFibObject<<", bIsChangebel="<<(bIsChangebel ? "true" : "false")<<") called"<<endl<<flush);
	if ( pFibObject == NULL ){
		//no Fib object for the new main window -> return NULL
		return NULL;
	}
	//create new main window
	cFibObjectMainWindow * pNewMainWindow =
		new cFibObjectMainWindow( pFibObject, bIsChangebel );
	//register new main window
	registerMainWindow( pNewMainWindow );
	//show the new window
	pNewMainWindow->show();
	
	return pNewMainWindow;
}


/**
 * This method returns a new main window for the given Fib object info
 * Fib object.
 *
 * @see setMainWindows
 * @see cFibObjectInfo
 * @param pFibObjectInfo the Fib object info of the Fib object for the
 * 	main window to return
 * 	The responsibility for the Fib object will go to the Fib object
 * 	node handler @see cFibNodeHandler
 * 	So don't delete it.
 * @param bIsChangebel true (standard value) if (the Fib element
 * 	 pFibObject of) the to create node is changebel, else false
 * @return a pointer to the a new main window for the given Fib object
 */
cFibObjectMainWindow * cMainWindowHandler::getNewMainWindowForFibObjectInfo(
		cFibObjectInfo * pFibObjectInfo, const bool bIsChangebel ){
	
	DEBUG_OUT_L2(<<"cMainWindowHandler("<<this<<")::getNewMainWindowForFibObjectInfo( pFibObjectInfo="<<pFibObjectInfo<<", bIsChangebel="<<(bIsChangebel ? "true" : "false")<<") called"<<endl<<flush);
	if ( pFibObjectInfo == NULL ){
		//no Fib object for the new main window -> return NULL
		return NULL;
	}
	int iOutStatus = 0;
	cFibElement * pLoadedFibObject =
		pFibObjectInfo->loadFibObjectFromSource( &iOutStatus );
	
	if ( pLoadedFibObject == NULL ){
		//no Fib object for Fib object info -> no main window can be created
		return NULL;
	}
	if ( iOutStatus < 0 ){
		/*error while loading Fib object for Fib object info
		 *-> no main window can be created*/
		return NULL;
	}
	//create main window for clone of Fib object info
	cFibObjectMainWindow * pNewFibObjectMainWindow =
		getNewMainWindowForFibObject( pLoadedFibObject->clone(), bIsChangebel );
	
	if ( ( pNewFibObjectMainWindow != NULL ) &&
			( pFibObjectInfo->getFibObjectSource() != NULL ) &&
			( pFibObjectInfo->getFibObjectSource()->getName() != "cFibObjectSourcePath" ) ){
		//set path of loaded Fib object as current path
		pNewFibObjectMainWindow->setCurrentFile( ((cFibObjectSourcePath*)(
			pFibObjectInfo->getFibObjectSource()))->getPath().c_str() );
		//TODO? better: set Fib object info for node (?and main window)
	}
	return pNewFibObjectMainWindow;
}


/**
 * This method creates and returns a new main window for an empty Fib object.
 * For that it will ask the user in a dialog for the parameter for the
 * to crate image Fib object. (e.g. size or transparency)
 * (The empty image Fib object will contain an empty point as the main
 * Fib object of the master root.)
 * @see getEmptyFibObject()
 *
 * @return a pointer to the a new main window
 */
cFibObjectMainWindow * cMainWindowHandler::createNewMainWindowForEmptyFibObject(){
	
	DEBUG_OUT_L2(<<"cMainWindowHandler("<<this<<")::createNewMainWindowForEmptyFibObject() called"<<endl<<flush);
	cFibElement * pEmptyFibObject = getEmptyFibObject();
	
	if ( pEmptyFibObject ){
		return getNewMainWindowForFibObject( pEmptyFibObject );
	}//else no empty Fib object created -> create no window
	return NULL;
}



/**
 * This method will create an empty image Fib object.
 * For that it will ask the user in a dialog for the parameter for the
 * to crate image Fib object. (e.g. size or transparency)
 * (The empty image Fib object will contain an empty point as the main
 * Fib object of the master root.)
 * Beware: You have to delete (deleteObject()) the returned Fib object
 * 	after usage.
 * @see createNewMainWindowForEmptyFibObject()
 * @see cDialogNewFibObject
 *
 * @return a pointer to an empty image Fib object
 */
cFibElement * cMainWindowHandler::getEmptyFibObject(){
	
	DEBUG_OUT_L2(<<"cMainWindowHandler("<<this<<")::getEmptyFibObject() called"<<endl<<flush);
	//call the new Fib object dialog
	cDialogNewFibObject dialogNewFibObject;
	
	if ( dialogNewFibObject.exec() ){
		//a new Fib object should be created -> get the Fib object
		return dialogNewFibObject.getFibObject();
	}//else
	//no Fib object should be created -> return NULL
	return NULL;
}


/**
 * This method will restore a Fib object from a file and open a new
 * main window, which will contain the loaded Fib object. The user can
 * choose the file with a file dialog, which this method will open.
 * The opened main window will allready be handeled by this hindler.
 *
 * @return a pointer the restored main window or the null pointer NULL,
 * 	if non could be restored
 */
cFibObjectMainWindow * cMainWindowHandler::openMainWindowForFibObjectFromFile(){
	
	DEBUG_OUT_L2(<<"cMainWindowHandler("<<this<<")::openMainWindowForFibObjectFromFile() called"<<endl<<flush);
	
	//read the Fib object
	string strFilePath( "" );
	
	cFibElement * pReadFibObject = openFibObjectFromFile( &strFilePath );
	if ( pReadFibObject == NULL ){
		//no Fib object read -> return NULL
		return NULL;
	}
	//create main windo for Fib object
	cFibObjectMainWindow * pNewFibObjectMainWindow =
		getNewMainWindowForFibObject( pReadFibObject );
	if ( pNewFibObjectMainWindow ){
		//set file name
		pNewFibObjectMainWindow->strCurFilePath =
			QString::fromStdString( strFilePath );
		return pNewFibObjectMainWindow;
	}
	return NULL;
}


/**
 * This method will restore a Fib object from the file with the given path.
 * Beware: You have to care that the retured Fib object will be deleted.
 * 	(Use the Fib node handler.)
 *
 * @param szFibObjectPath the path to the Fib object file to restore
 * @return a pointer the restored Fib object or the null pointer NULL,
 * 	if non could be restored
 */
cFibElement * cMainWindowHandler::openFibObjectFromFile(
		const string & szFibObjectPath ){
	
	DEBUG_OUT_L2(<<"cMainWindowHandler("<<this<<")::openFibObjectFromFile( szFibObjectPath="<<szFibObjectPath<<") called"<<endl<<flush);
	if ( szFibObjectPath == "" ){
		//no file to open -> return NULL
		return NULL;
	}
	cFibElement * pRestoredFibObject = NULL;
	
	if ( szFibObjectPath.compare( (szFibObjectPath.size() - 4), 4, ".xml" ) == 0 ){
		//restore to file in xml -format
		ifstream inFile( szFibObjectPath.c_str() );
		intFib outStatus = 0;
		
		if ( ! inFile.good() ){
			QMessageBox msgBox;
			msgBox.setWindowTitle("Fib creator open Fib object");
			msgBox.setText(tr( "Error: Can't open file \"%1\"." ).
				arg( QString::fromStdString( szFibObjectPath ) ) );
			msgBox.setIcon( QMessageBox::Critical );
			msgBox.exec();
			return NULL;
		}
		
		pRestoredFibObject = cFibElement::restoreXml( inFile , &outStatus );
		
		if ( 0 < outStatus ){
			QMessageBox msgBox;
			msgBox.setWindowTitle("Fib creator open Fib object");
			msgBox.setText(tr( "Warning: Restoring Fib object in the Xml format from the file \"%1\" not successfull. (return status=%2)." ).
				arg( QString::fromStdString( szFibObjectPath ) ).arg( outStatus ) );
			msgBox.setIcon( QMessageBox::Warning );
			msgBox.exec();
		}else if ( outStatus < 0 ){
			QMessageBox msgBox;
			msgBox.setWindowTitle("Fib creator open Fib object");
			msgBox.setText(tr( "Error: Restoring Fib object in the Xml format from the file \"%1\" not successfull. (return status=%2)." ).
				arg( QString::fromStdString( szFibObjectPath ) ).arg( outStatus ) );
			msgBox.setIcon( QMessageBox::Critical );
			msgBox.exec();
			return NULL;
		}
	}else{//restore to file in compressed format
		ifstream inFile( szFibObjectPath.c_str(), ios_base::in | ios_base::binary );
		intFib outStatus = 0;
		
		if ( ! inFile.good() ){
			QMessageBox msgBox;
			msgBox.setWindowTitle("Fib creator open Fib object");
			msgBox.setText( tr( "Error: Can't open file \"%1\"." ).
				arg( QString::fromStdString( szFibObjectPath ) ) );
			msgBox.setIcon( QMessageBox::Critical );
			msgBox.exec();
			return NULL;
		}
		
		pRestoredFibObject = cFibElement::restore( inFile , &outStatus );
		
		if ( 0 < outStatus ){
			QMessageBox msgBox;
			msgBox.setWindowTitle("Fib creator open Fib object");
			msgBox.setText(tr( "Warning: Restoring Fib object in the compressed format from the file \"%1\" not successfull. (return status=%2)." ).
				arg( QString::fromStdString( szFibObjectPath ) ).arg( outStatus ) );
			msgBox.setIcon( QMessageBox::Warning );
			msgBox.exec();
		}else if ( outStatus < 0 ){
			QMessageBox msgBox;
			msgBox.setWindowTitle("Fib creator open Fib object");
			msgBox.setText(tr( "Error: Restoring Fib object in the compressed format from the file \"%1\" not successfull. (return status=%2)." ).
				arg( QString::fromStdString( szFibObjectPath ) ).arg( outStatus ) );
			msgBox.setIcon( QMessageBox::Critical );
			msgBox.exec();
			return NULL;
		}
	}
	if ( pRestoredFibObject == NULL ){
		QMessageBox msgBox;
		msgBox.setWindowTitle("Fib creator open Fib object");
		msgBox.setText( tr( "Error: No Fib object restored from file \"%1\"." ).
				arg( QString::fromStdString( szFibObjectPath ) ) );
		msgBox.setIcon( QMessageBox::Critical );
		msgBox.exec();
		return NULL;
	}
	
	return pRestoredFibObject;
}


/**
 * This method will restore a Fib object from a file.
 * The user can choose the file with a file dialog, which this method
 * will open.
 * Beware: You have to care that the retured Fib object will be deleted.
 * 	(Use the Fib node handler.)
 *
 * @param pOutStrFilePath a pointer to the string, where to store the
 * 	file path, or NULL if the file name is not needed
 * @return a pointer the restored Fib object or the null pointer NULL,
 * 	if non could be restored
 */
cFibElement * cMainWindowHandler::openFibObjectFromFile( string * pOutStrFilePath ){
	
	DEBUG_OUT_L2(<<"cMainWindowHandler("<<this<<")::openFibObjectFromFile( pOutStrFilePath="<<pOutStrFilePath<<") called"<<endl<<flush);
	
	//to set start file
	QSettings settings("Fib development", "Fib creator");
	//open file dialog
	QFileDialog fileDialog( NULL, tr("Open Fib object"),  settings.value(
			"mainWindow/fileDialog/lastFile",
				QDir::homePath() + QDir::separator() + "*.xml" ).toString(),
		tr("Fib XML (*.xml);;Fib compressed (*.fib)" ) );
	
	fileDialog.setFileMode( QFileDialog::ExistingFile );
	
	if ( fileDialog.exec() ){
		//a file was choosen
		QStringList liFileNames = fileDialog.selectedFiles();
		if ( liFileNames.size() != 1 ){
			//not one file choosen -> return NULL
			return NULL;
		}
		//open Fib file
		if ( pOutStrFilePath ){
			//store the file path
			(*pOutStrFilePath) = liFileNames.size();
		}
		//store actual file as last used file
		settings.setValue("mainWindow/fileDialog/lastFile", liFileNames.front() );
		return openFibObjectFromFile( liFileNames.front().toStdString() );
	}//else
	//no file to open -> return NULL
	return NULL;
}


/**
 * This method will close the given main window.
 * This includes that the given main window will be deleted.
 *
 * @param pMainWindow a pointer to the main window to close
 * @return true if the given main window was closed, else false
 */
bool cMainWindowHandler::closeMainWindow( cFibObjectMainWindow * pMainWindow ){
	
	DEBUG_OUT_L2(<<"cMainWindowHandler("<<this<<")::closeMainWindow( pMainWindow="<<pMainWindow<<") called"<<endl<<flush);
	
	if ( pMainWindow == NULL ){
		//no main window to delete
		return false;
	}
	//TODO?
	unregisterMainWindow( pMainWindow );
	
	pMainWindow->deleteLater();
	
	//TODO? if all windows closed -> end application
	if ( setMainWindows.empty() ){
		delete this;
	}
	
	return true;
}


//static versions of methods above

/**
 * This function registers the given main window in this handler.
 * This handler will than take care that the main window is deleted
 * befor the application ends.
 * @see setMainWindows
 *
 * @param pMainWindow a pointer to the main window to register
 */
void cMainWindowHandler::registerMainWindowStatic(
		cFibObjectMainWindow * pMainWindow ){
	
	getInstance()->registerMainWindow( pMainWindow );
}


/**
 * This function unregisters the given main window from this handler.
 * If you have unregister a main window, than you have the
 * responsibility for the main window (e. g. you need to delete it).
 * @see setMainWindows
 *
 * @param pMainWindow a pointer to the main window to unregister
 * @return true if the given main window was unregister, else false
 */
bool cMainWindowHandler::unregisterMainWindowStatic(
		cFibObjectMainWindow * pMainWindow ){
	
	DEBUG_OUT_L2(<<"cMainWindowHandler::unregisterMainWindowStatic( pMainWindow="<<pMainWindow<<" ) called"<<endl<<flush);
	if ( pMainWindowHandler ){
		
		return pMainWindowHandler->unregisterMainWindow( pMainWindow );
	}//no main window handler -> no main window -> nothing to unregister
	DEBUG_OUT_L3(<<"cMainWindowHandler::unregisterMainWindowStatic( pMainWindow="<<pMainWindow<<" ) no main window handler -> no main window -> nothing to unregister"<<endl<<flush);
	return false;
}


/**
 * This method checks if the given pointer points to a in this handler
 * existing main window.
 * A main window wich was registered in this handler could be missing,
 * if it was unregistered or deleted.
 * @see setMainWindows
 *
 * @param pMainWindow a pointer to the main window to check
 * @return true if the given main window points to an existing main
 * 	window in this handler, else false
 */
bool cMainWindowHandler::isRegisterMainWindowStatic(
		const cFibObjectMainWindow * pMainWindow ){
	
	return getInstance()->isRegisterMainWindow( pMainWindow );
}


/**
 * This method returns a new main window for the given Fib object.
 *
 * @see setMainWindows
 * @param pFibObject the Fib object for the main window to return
 * 	The responsibility for the Fib object will go to the Fib object
 * 	node handler @see cFibNodeHandler
 * 	So don't delete it.
 * @param bIsChangebel true (standard value) if (the Fib element
 * 	 pFibObject of) the to create node is changebel, else false
 * @return the a new main window for the given Fib object
 */
cFibObjectMainWindow * cMainWindowHandler::getNewMainWindowForFibObjectStatic(
		cFibElement * pFibObject, const bool bIsChangebel ){
	
	return getInstance()->getNewMainWindowForFibObject( pFibObject, bIsChangebel );
}


/**
 * This method creates and returns a new main window for an empty Fib object.
 * For that it will ask the user in a dialog for the parameter for the
 * to crate image Fib object. (e.g. size or transparency)
 * (The empty image Fib object will contain an empty point as the main
 * Fib object of the master root.)
 * @see getEmptyFibObject()
 *
 * @return a pointer to the a new main window
 */
cFibObjectMainWindow * cMainWindowHandler::createNewMainWindowForEmptyFibObjectStatic(){
	
	return getInstance()->createNewMainWindowForEmptyFibObject();
}


/**
 * This method will create an empty image Fib object.
 * For that it will ask the user in a dialog for the parameter for the
 * to crate image Fib object. (e.g. size or transparency)
 * (The empty image Fib object will contain an empty point as the main
 * Fib object of the master root.)
 * Beware: You have to delete (deleteObject()) the returned Fib object
 * 	after usage.
 * @see createNewMainWindowForEmptyFibObject()
 *
 * @return a pointer to an empty image Fib object
 */
cFibElement * cMainWindowHandler::getEmptyFibObjectStatic(){
	
	return getInstance()->getEmptyFibObject();
}


/**
 * This method will restore a Fib object from a file and open a new
 * main window, which will contain the loaded Fib object. The user can
 * choose the file with a file dialog, which this method will open.
 * The opened main window will allready be handeled by this hindler.
 *
 * @return a pointer the restored main window or the null pointer NULL,
 * 	if non could be restored
 */
cFibObjectMainWindow * cMainWindowHandler::openMainWindowForFibObjectFromFileStatic(){
	
	return getInstance()->openMainWindowForFibObjectFromFile();
}


/**
 * This method will restore a Fib object from the file with the given path.
 * Beware: You have to care that the retured Fib object will be deleted.
 * 	(Use the Fib node handler.)
 *
 * @param szFibObjectPath the path to the Fib object file to restore
 * @return a pointer the restored Fib object or the null pointer NULL,
 * 	if non could be restored
 */
cFibElement * cMainWindowHandler::openFibObjectFromFileStatic(
		const string & szFibObjectPath ){
	
	return getInstance()->openFibObjectFromFile( szFibObjectPath );
}


/**
 * This method will restore a Fib object from a file.
 * The user can choose the file with a file dialog, which this method
 * will open.
 * Beware: You have to care that the retured Fib object will be deleted.
 * 	(Use the Fib node handler.)
 *
 * @param pOutStrFilePath a pointer to the string, where to store the
 * 	file path, or NULL if the file name is not needed
 * @return a pointer the restored Fib object or the null pointer NULL,
 * 	if non could be restored
 */
cFibElement * cMainWindowHandler::openFibObjectFromFileStatic(
		string * pOutStrFilePath ){
	
	return getInstance()->openFibObjectFromFile( pOutStrFilePath );
}


/**
 * This method will close the given main window.
 * This includes that the given main window will be deleted.
 *
 * @param pMainWindow a pointer to the main window to close
 * @return true if the given main window was closed, else false
 */
bool cMainWindowHandler::closeMainWindowStatic( cFibObjectMainWindow * pMainWindow ){
	
	return getInstance()->closeMainWindow( pMainWindow );
}





