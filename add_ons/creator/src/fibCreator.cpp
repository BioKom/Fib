
//TODO check

/**
 * @file fibCreator
 * file name: fibCreator.cpp
 * @author Betti Oesterholz
 * @date 09.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file contains the main function for the Fib creator application.
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
 * This file contains the main function for the Fib creator application.
 * It is an application, with a grapical user interface, for creating and
 * changing Fib objects.
 */
/*
History:
09.06.2013  Oesterholz  created
*/


//TODO rework


#include <QtGui>
#include <QApplication>

#include "cFibNodeHandler.h"
#include "cFibObjectMainWindow.h"
#include "cMainWindowHandler.h"


using namespace fib::nCreator;


int main(int argc, char **argv){
	//the QApplication is the basis of the Qt application
	QApplication app(argc, argv);
	app.setOrganizationName("Fib development");
	app.setApplicationName("Fib creator");
	app.setOrganizationDomain("www.Fib-development.org");
	app.setApplicationVersion("V0.0.0");
	//init the translation/localization system
	QString locale = QLocale::system().name();

	QTranslator translator;
	const QString strTranslationFile = QString("fibCreator_") + locale;
	translator.load( strTranslationFile );
	app.installTranslator(&translator);
	
	//TODO
	

	//init the Fib object handler
	cFibNodeHandler::getInstance();
	//TODO init the window handler
	cMainWindowHandler * pMainWindowHandler = cMainWindowHandler::getInstance();
	
	
	//TODO if a Fib object file was given load the Fib object
		
		//TODO else load a default Fib object
		
		//else create empty main window
		if ( pMainWindowHandler->createNewMainWindowForEmptyFibObject() == NULL ){
			
			//no window created -> create empty main window
			cFibObjectMainWindow * pNewMainWindow =
				new cFibObjectMainWindow( NULL, true );
			//register new main window
			pMainWindowHandler->registerMainWindow( pNewMainWindow );
			//show the new window
			pNewMainWindow->show();
		}
		
		
	
	
	/*create a cMainWindowHandler:public QObject class which manages the
	 main windows, every new main window should be a child of it
	 (-> auto destruction; use deleteLater() because of pending signals )*/
	
	
	//create the main window
	
	
	
	
	/*TODO weg:
	// Ein Fenster mit einem Titel erzeugen
	QWidget window;
	window.setWindowTitle( QObject::tr("Fib creator") );

	// Ein Label mit einem Text erzeugen
	QLabel *label = new QLabel( QObject::tr("Hello World! ") + strTranslationFile );
	label->setAlignment(Qt::AlignCenter);

	// Eine Schaltfläche mit Tastenkürzel Alt-E erzeugen, welcher die Anwendung beendet
	QPushButton *button = new QPushButton( QObject::tr("&Exit") );
	QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));

	// Sowohl das Label als auch die Schaltfläche horizontal ausrichten
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(label);
	layout->addWidget(button);
	window.setLayout(layout);

	// Das Fenster anzeigen, die Anwendung starten und ihr Ergebnis (an das Betriebssystem) zurückliefern
	window.show();
	*/
	return app.exec();
}


