
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
 * This file specifies a class for handling the main windows for the
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
 * This file specifies a class for handling the main windows for the
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
*/


#ifndef ___FIB__NCREATOR__C_MAIN_WINDOW_HANDLER_H__
#define ___FIB__NCREATOR__C_MAIN_WINDOW_HANDLER_H__


#include "version.h"

#include <set>

#include <QObject>
#include <QMainWindow>
#include <QMutex>

#include "cFibObjectMainWindow.h"
#include "cFibNode.h"



namespace fib{

namespace nCreator{

//forward declarations
class cFibObjectInfo;

namespace nMainWindowHandler{
	//cyclic dependencies
	class cMainWindowHandlerDeleter;
};//end namespace nMainWindowHandler


class cMainWindowHandler: public QObject{
		Q_OBJECT

friend class nMainWindowHandler::cMainWindowHandlerDeleter;

protected:
	
	/**
	 * A pointer to the main window handler object.
	 */
	static cMainWindowHandler * pMainWindowHandler;
	
	/**
	 * A set with the existing main windows.
	 */
	std::set< QMainWindow * > setMainWindows;
	
	/**
	 * Mutex to lock access to the main windows data of this class.
	 * Lock the mutex if you use one of the following containers:
	 * @see setMainWindows
	 */
	QMutex mutexFibNodeHandler;
	
	
	/**
	 * constructor for the main window handler
	 */
	cMainWindowHandler();
	
public:
	
	/**
	 * destructor
	 */
	~cMainWindowHandler();
	
	/**
	 * @return a pointer to instance of the main window handler
	 */
	static cMainWindowHandler * getInstance();
	
	
	/**
	 * This function registers the given main window in this handler.
	 * This handler will than take care that the main window is deleted
	 * befor the application ends.
	 * @see setMainWindows
	 *
	 * @param pMainWindow a pointer to the main window to register
	 */
	void registerMainWindow( cFibObjectMainWindow * pMainWindow );
	
	/**
	 * This function unregisters the given main window from this handler.
	 * If you have unregister a main window, than you have the
	 * responsibility for the main window (e. g. you need to delete it).
	 * @see setMainWindows
	 *
	 * @param pMainWindow a pointer to the main window to unregister
	 * @return true if the given main window was unregister, else false
	 */
	bool unregisterMainWindow( cFibObjectMainWindow * pMainWindow );
	
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
	bool isRegisterMainWindow( const cFibObjectMainWindow * pMainWindow );
	
	
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
	 * @return a pointer to the a new main window for the given Fib object
	 */
	cFibObjectMainWindow * getNewMainWindowForFibObject(
			cFibElement * pFibObject, const bool bIsChangebel=true );
	
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
	cFibObjectMainWindow * getNewMainWindowForFibObjectInfo(
			cFibObjectInfo * pFibObjectInfo, const bool bIsChangebel=true );
	
	
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
	cFibObjectMainWindow * createNewMainWindowForEmptyFibObject();
	
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
	cFibElement * getEmptyFibObject();
	
	
	/**
	 * This method will restore a Fib object from a file and open a new
	 * main window, which will contain the loaded Fib object. The user can
	 * choose the file with a file dialog, which this method will open.
	 * The opened main window will allready be handeled by this hindler.
	 *
	 * @return a pointer the restored main window or the null pointer NULL,
	 * 	if non could be restored
	 */
	cFibObjectMainWindow * openMainWindowForFibObjectFromFile();
	
	/**
	 * This method will restore a Fib object from the file with the given path.
	 * Beware: You have to care that the retured Fib object will be deleted.
	 * 	(Use the Fib node handler.)
	 *
	 * @param szFibObjectPath the path to the Fib object file to restore
	 * @return a pointer the restored Fib object or the null pointer NULL,
	 * 	if non could be restored
	 */
	cFibElement * openFibObjectFromFile( const string & szFibObjectPath );
	
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
	cFibElement * openFibObjectFromFile( string * pOutStrFilePath = NULL );
	
	
	/**
	 * This method will close the given main window.
	 * This includes that the given main window will be deleted.
	 *
	 * @param pMainWindow a pointer to the main window to close
	 * @return true if the given main window was closed, else false
	 */
	bool closeMainWindow( cFibObjectMainWindow * pMainWindow );
	
	
//static versions of methods above
	
	/**
	 * This function registers the given main window in this handler.
	 * This handler will than take care that the main window is deleted
	 * befor the application ends.
	 * @see setMainWindows
	 *
	 * @param pMainWindow a pointer to the main window to register
	 */
	static void registerMainWindowStatic( cFibObjectMainWindow * pMainWindow );
	
	/**
	 * This function unregisters the given main window from this handler.
	 * If you have unregister a main window, than you have the
	 * responsibility for the main window (e. g. you need to delete it).
	 * @see setMainWindows
	 *
	 * @param pMainWindow a pointer to the main window to unregister
	 * @return true if the given main window was unregister, else false
	 */
	static bool unregisterMainWindowStatic( cFibObjectMainWindow * pMainWindow );
	
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
	static bool isRegisterMainWindowStatic( const cFibObjectMainWindow * pMainWindow );
	
	
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
	static cFibObjectMainWindow * getNewMainWindowForFibObjectStatic(
			cFibElement * pFibObject, const bool bIsChangebel=true );
	
	
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
	static cFibObjectMainWindow * createNewMainWindowForEmptyFibObjectStatic();
	
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
	static cFibElement * getEmptyFibObjectStatic();
	
	
	/**
	 * This method will restore a Fib object from a file and open a new
	 * main window, which will contain the loaded Fib object. The user can
	 * choose the file with a file dialog, which this method will open.
	 * The opened main window will allready be handeled by this hindler.
	 *
	 * @return a pointer the restored main window or the null pointer NULL,
	 * 	if non could be restored
	 */
	static cFibObjectMainWindow * openMainWindowForFibObjectFromFileStatic();
	
	/**
	 * This method will restore a Fib object from the file with the given path.
	 * Beware: You have to care that the retured Fib object will be deleted.
	 * 	(Use the Fib node handler.)
	 *
	 * @param szFibObjectPath the path to the Fib object file to restore
	 * @return a pointer the restored Fib object or the null pointer NULL,
	 * 	if non could be restored
	 */
	static cFibElement * openFibObjectFromFileStatic( const string & szFibObjectPath );
	
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
	static cFibElement * openFibObjectFromFileStatic( string * pOutStrFilePath = NULL );
	
	
	/**
	 * This method will close the given main window.
	 * This includes that the given main window will be deleted.
	 *
	 * @param pMainWindow a pointer to the main window to close
	 * @return true if the given main window was closed, else false
	 */
	static bool closeMainWindowStatic( cFibObjectMainWindow * pMainWindow );
	
	
};//end class cMainWindowHandler

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_MAIN_WINDOW_HANDLER_H__





