
//TODO check

/**
 * @file cDialogNewFibObject
 * file name: cDialogNewFibObject.cpp
 * @author Betti Oesterholz
 * @date 01.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for the dialog to create a new Fib object.
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
 * This file implements a class for the dialog to create a new Fib object.
 * The dialog will ask the user for the parameter for the to create Fib object.
 *
 * Supported options:
 * 	- images (2 dimensional: horizontal + verlical)
 * 	- RGB color
 * 	- grayscale color
 * 	- transparency
 *
 */
/*
History:
01.07.2013  Oesterholz  created
*/


//switches for test proposes
//#define DEBUG
//#define DEBUG_FIB_OBJECT


#include "cDialogNewFibObject.h"

#include <QIntValidator>

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



using namespace std;
using namespace fib::nCreator;
using namespace fib;


/**
 * standard constructor for a Fib object node
 *
 * @param pParent a pointer the parent of this new Fib object dialog window
 */
cDialogNewFibObject::cDialogNewFibObject( QWidget * pParent ):
		QDialog( pParent ){
	
	DEBUG_OUT_L2(<<"cDialogNewFibObject("<<this<<")::cDialogNewFibObject( pParent="<<pParent<<" ) called"<<endl<<flush);
	
	setWindowTitle(tr("Create new Fib object"));
	
	QValidator * pValidatorSize = new QIntValidator( 1, 99999, this );
	
	//create size input filds
	pLabelDimension1 = new QLabel( tr("width (px):"), this );
	pLineEditDimension1 = new QLineEdit( this );
	pLineEditDimension1->setText( "640" );
	pLineEditDimension1->setValidator( pValidatorSize );
	pLabelDimension1->setBuddy( pLineEditDimension1 );
	
	pLabelDimension2 = new QLabel( tr("height (px):"), this );
	pLineEditDimension2 = new QLineEdit( this );
	pLineEditDimension2->setText( "480" );
	pLineEditDimension2->setValidator( pValidatorSize );
	pLabelDimension2->setBuddy( pLineEditDimension2 );
	
	
	
	//create color RGB input field
	pCheckBoxColorRgb = new QCheckBox(tr("RGB color"), this);
	pCheckBoxColorRgb->setChecked( true );
	
	//if checked  display color RGB extension
	
	//create RGB color part
	pExtensionColorRgb = new QWidget( this );
	connect( pCheckBoxColorRgb, SIGNAL( toggled( bool ) ),
		pExtensionColorRgb, SLOT( setVisible( bool ) ) );
	
	pLabelColorRed = new QLabel( tr("max value red:"), this );
	pLineEditMaxColorRed = new QLineEdit( this );
	pLineEditMaxColorRed->setText( "255" );
	pLineEditMaxColorRed->setValidator( pValidatorSize );
	pLabelColorRed->setBuddy( pLineEditMaxColorRed );
	
	pLabelColorGreen = new QLabel( tr("max value green:"), this );
	pLineEditMaxColorGreen = new QLineEdit( this );
	pLineEditMaxColorGreen->setText( "255" );
	pLineEditMaxColorGreen->setValidator( pValidatorSize );
	pLabelColorGreen->setBuddy( pLineEditMaxColorGreen );
	
	pLabelColorBlue = new QLabel( tr("max value blue:"), this );
	pLineEditMaxColorBlue = new QLineEdit( this );
	pLineEditMaxColorBlue->setText( "255" );
	pLineEditMaxColorBlue->setValidator( pValidatorSize );
	pLabelColorBlue->setBuddy( pLineEditMaxColorBlue );
	
	
	//create grayscale color part
	pCheckBoxColorGrayscale = new QCheckBox(tr("grayscale color"), this );
	pCheckBoxColorGrayscale->setChecked( false );
	
	pExtensionColorGrayscale = new QWidget( this );
	pExtensionColorGrayscale->hide();
	connect( pCheckBoxColorGrayscale, SIGNAL( toggled( bool ) ),
		pExtensionColorGrayscale, SLOT( setVisible( bool ) ) );
	
	pLabelColorGrayscale = new QLabel( tr("max value grayscale:"), this );
	pLineEditMaxColorGrayscale = new QLineEdit( this );
	pLineEditMaxColorGrayscale->setText( "255" );
	pLineEditMaxColorGrayscale->setValidator( pValidatorSize );
	pLabelColorGrayscale->setBuddy( pLineEditMaxColorGrayscale );
	
	
	//create transparency part
	pCheckBoxTransparency = new QCheckBox(tr("transparency"), this );
	pCheckBoxTransparency->setChecked( true );
	
	pExtensionTransparency = new QWidget( this );
	connect( pCheckBoxTransparency, SIGNAL( toggled( bool ) ),
		pExtensionTransparency, SLOT( setVisible( bool ) ) );
	
	pLabelTransparency = new QLabel( tr("max value transparency:"), this );
	pLineEditMaxTransparency = new QLineEdit( this );
	pLineEditMaxTransparency->setText( "255" );
	pLineEditMaxTransparency->setValidator( pValidatorSize );
	pLabelTransparency->setBuddy( pLineEditMaxTransparency );
	
	
	//create buttons
	pButtonBox = new QDialogButtonBox( this );
	pButtonCreate = new QPushButton(tr("C&reate"), this );
	pButtonCreate->setDefault( true );
	connect( pButtonCreate, SIGNAL( pressed() ), this, SLOT( accept() ) );
	
	pButtonChancel = new QPushButton(tr("&Chancel"), this );
	pButtonChancel->setCheckable( true );
	pButtonChancel->setAutoDefault( false );
	connect( pButtonChancel, SIGNAL( pressed() ), this, SLOT( reject() ) );
	
	
//create the layout
	//create size layouts
	pLayoutDimension1 = new QHBoxLayout();
	pLayoutDimension1->addWidget( pLabelDimension1 );
	pLayoutDimension1->addWidget( pLineEditDimension1 );
	
	pLayoutDimension2 = new QHBoxLayout();
	pLayoutDimension2->addWidget( pLabelDimension2 );
	pLayoutDimension2->addWidget( pLineEditDimension2 );
	
	//create color RGB layout
	pLayoutColorRed = new QHBoxLayout();
	pLayoutColorRed->addWidget( pLabelColorRed );
	pLayoutColorRed->addWidget( pLineEditMaxColorRed );
	
	pLayoutColorGreen = new QHBoxLayout();
	pLayoutColorGreen->addWidget( pLabelColorGreen );
	pLayoutColorGreen->addWidget( pLineEditMaxColorGreen );
	
	pLayoutColorBlue = new QHBoxLayout();
	pLayoutColorBlue->addWidget( pLabelColorBlue );
	pLayoutColorBlue->addWidget( pLineEditMaxColorBlue );
	
	
	pLayoutExtColorRgb = new QVBoxLayout();
	pLayoutExtColorRgb->setMargin( 1 );
	pLayoutExtColorRgb->addLayout( pLayoutColorRed );
	pLayoutExtColorRgb->addLayout( pLayoutColorGreen );
	pLayoutExtColorRgb->addLayout( pLayoutColorBlue );
	pExtensionColorRgb->setLayout( pLayoutExtColorRgb );
	
	//create color grayscale layout
	pLayoutColorGrayscale = new QHBoxLayout();
	pLayoutColorGrayscale->setMargin( 1 );
	pLayoutColorGrayscale->addWidget( pLabelColorGrayscale );
	pLayoutColorGrayscale->addWidget( pLineEditMaxColorGrayscale );
	pExtensionColorGrayscale->setLayout( pLayoutColorGrayscale );
	
	//create color transparency layout
	pLayoutTransparency = new QHBoxLayout();
	pLayoutTransparency->setMargin( 1 );
	pLayoutTransparency->addWidget( pLabelTransparency );
	pLayoutTransparency->addWidget( pLineEditMaxTransparency );
	pExtensionTransparency->setLayout( pLayoutTransparency );
	
	//create button layout
	pButtonBox = new QDialogButtonBox( Qt::Horizontal, this );
	pButtonBox->addButton( pButtonCreate, QDialogButtonBox::ActionRole );
	pButtonBox->addButton( pButtonChancel, QDialogButtonBox::ActionRole );
	pButtonBox->setCenterButtons( true );
	
	
	//create main layout
	pLayoutMain = new QVBoxLayout( this );
	pLayoutMain->addLayout( pLayoutDimension1 );
	pLayoutMain->addLayout( pLayoutDimension2 );
	pLayoutMain->addWidget( pCheckBoxColorRgb );
	pLayoutMain->addWidget( pExtensionColorRgb );
	pLayoutMain->addWidget( pCheckBoxColorGrayscale );
	pLayoutMain->addWidget( pExtensionColorGrayscale );
	pLayoutMain->addWidget( pCheckBoxTransparency );
	pLayoutMain->addWidget( pExtensionTransparency );
	pLayoutMain->addWidget( pButtonBox );
	
	setLayout( pLayoutMain );
	//set resizing possible
	setSizeGripEnabled( true );
}


/**
 * destructor
 */
cDialogNewFibObject::~cDialogNewFibObject(){
	//nothing to do
	DEBUG_OUT_L2(<<"cDialogNewFibObject("<<this<<")::~cDialogNewFibObject() called"<<endl<<flush);
}


/**
 * This method will create the Fib object and return a pointer to the
 * Fib (root) object for the dialog.
 * BEWARE: You have to care that the returned Fib object is deleted (deleteObject())
 *
 * @return a pointer to the Fib (root) object for the dialog
 */
cRoot * cDialogNewFibObject::getFibObject(){
	
	DEBUG_OUT_L2(<<"cDialogNewFibObject("<<this<<")::getFibObject() called"<<endl<<flush);
	
	bool bConvertOk = true;
	
	//get the size for the image
	const int uiMaxX = pLineEditDimension1->text().toInt( &bConvertOk ) - 1;
	if ( ( ! bConvertOk ) || ( uiMaxX < 0 ) ){
		//Error: could not convert to number
		return NULL;
	}
	const int uiMaxY = pLineEditDimension2->text().toInt( &bConvertOk ) - 1;
	if ( ( ! bConvertOk ) || ( uiMaxY < 0 ) ){
		//Error: could not convert to number
		return NULL;
	}
	DEBUG_OUT_L2(<<"cDialogNewFibObject("<<this<<")::getFibObject() dimensions max X="<<uiMaxX<<"   max Y="<<uiMaxY<<"  "<<endl<<flush);
	
	//create the empty Fib object
	//main Fib object is an empty point
	cPoint * pMainFibObjectPoint = new cPoint();
	
	cRoot * pRootObject = new cRoot( pMainFibObjectPoint );
	cOptionalPart * pOptionalPart = pRootObject->getOptionalPart();
	pOptionalPart->addEntry( "application:created", "Fib creator V0.0.0" );
	//set dimension domain
	cDomains * pDomains = pRootObject->getDomains();
	
	vector<cDomainSingle*> vecSubDomDimension( 2 );
	vecSubDomDimension[ 0 ] = new cDomainNaturalNumber( uiMaxX );
	vecSubDomDimension[ 1 ] = new cDomainNaturalNumber( uiMaxY );
	cDomainVector * pDomDimension = new cDomainVector( vecSubDomDimension );
	delete vecSubDomDimension[ 0 ];
	delete vecSubDomDimension[ 1 ];
	
	pDomains->addDomain( cTypeDimension( 2 ), pDomDimension );
	
	if ( pCheckBoxColorRgb->isChecked() ){
		//set color RGB domain
		const int uiMaxRed   = pLineEditMaxColorRed->text().toInt( &bConvertOk );
		const int uiMaxGreen = pLineEditMaxColorGreen->text().toInt( &bConvertOk );
		const int uiMaxBlue  = pLineEditMaxColorBlue->text().toInt( &bConvertOk );
		
		vector<cDomainSingle*> vecSubDomColor( 3 );
		vecSubDomColor[ 0 ] = new cDomainNaturalNumber(
			( 0 < uiMaxRed ) ? uiMaxRed : 0 );
		vecSubDomColor[ 1 ] = new cDomainNaturalNumber(
			( 0 < uiMaxGreen ) ? uiMaxGreen : 0 );
		vecSubDomColor[ 2 ] = new cDomainNaturalNumber(
			( 0 < uiMaxBlue ) ? uiMaxBlue : 0 );
		cDomainVector * pDomColor = new cDomainVector( vecSubDomColor );
		delete vecSubDomColor[ 0 ];
		delete vecSubDomColor[ 1 ];
		delete vecSubDomColor[ 2 ];
		
		pDomains->addDomain( cTypeProperty( cTypeProperty::COLOR_RGB ), pDomColor );
	}
	if ( pCheckBoxColorGrayscale->isChecked() ){
		//set color grayscale domain
		const int uiMaxGrayscale = pLineEditMaxColorGrayscale->text().toInt( &bConvertOk );
		
		vector<cDomainSingle*> vecSubDomColor( 1 );
		vecSubDomColor[ 0 ] = new cDomainNaturalNumber(
			( 0 < uiMaxGrayscale ) ? uiMaxGrayscale : 0 );
		
		cDomainVector * pDomColor = new cDomainVector( vecSubDomColor );
		delete vecSubDomColor[ 0 ];
		
		pDomains->addDomain( cTypeProperty( cTypeProperty::COLOR_GRAYSCALE ), pDomColor );
	}
	if ( pCheckBoxTransparency->isChecked() ){
		//set transparency domain
		const int uiMaxGrayscale = pLineEditMaxTransparency->text().toInt( &bConvertOk );
		
		vector<cDomainSingle*> vecSubDomColor( 1 );
		vecSubDomColor[ 0 ] = new cDomainNaturalNumber(
			( 0 < uiMaxGrayscale ) ? uiMaxGrayscale : 0 );
		
		cDomainVector * pDomColor = new cDomainVector( vecSubDomColor );
		delete vecSubDomColor[ 0 ];
		
		pDomains->addDomain( cTypeProperty( cTypeProperty::TRANSPARENCY ), pDomColor );
	}
	//TODO? include dummy domains for functions, areas external subobjects ...
	
#ifdef DEBUG_FIB_OBJECT
	cout<<"cDialogNewFibObject("<<this<<")::getFibObject() created Fib object:"<<endl;
	if ( pRootObject ){
		pRootObject->storeXml( cout );
	}else{
		cout<<"NULL";
	}
	cout<<endl;
#endif //DEBUG_FIB_OBJECT
	
	return pRootObject;
}




/**
 * @return the name of this class "cDialogNewFibObject"
 */
std::string cDialogNewFibObject::getName() const{
	
	return "cDialogNewFibObject";
}


/**
 * @return a hint for a good size of this window
 */
QSize cDialogNewFibObject::sizeHint() const{
	
	return QSize( 300, 300 );
}






