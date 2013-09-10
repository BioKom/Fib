
//TODO check

/**
 * @file cDialogNewFibObject
 * file name: cDialogNewFibObject.h
 * @author Betti Oesterholz
 * @date 01.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for the dialog to create a new Fib object.
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
 * This file specifies a class for the dialog to create a new Fib object.
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


#ifndef ___FIB__NCREATOR__C_DIALOG_NEW_FIB_OBJECT_H__
#define ___FIB__NCREATOR__C_DIALOG_NEW_FIB_OBJECT_H__


#include "version.h"

#include "cRoot.h"

#include <QDialog>

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


using namespace std;


namespace fib{

namespace nCreator{
class cDialogNewFibObject: public QDialog{
		Q_OBJECT
protected:
	
	/**
	 * Elements fo the image size.
	 */
	/// The label for the width (dimension 1) input field.
	QLabel * pLabelDimension1;
	/// The width (dimension 1) input field.
	QLineEdit * pLineEditDimension1;
	/// The label for the height (dimension 2) input field.
	QLabel * pLabelDimension2;
	/// The height (dimension 2) input field.
	QLineEdit * pLineEditDimension2;
	
	/**
	 * Element for the RGB color information.
	 */
	/// The check box to mark that RGB color should be used.
	QCheckBox * pCheckBoxColorRgb;
	/// The extension field for the RGB color max values.
	QWidget * pExtensionColorRgb;
	/// The label for the maximum value input field for the color red.
	QLabel * pLabelColorRed;
	/// The maximum value input field for the color red.
	QLineEdit * pLineEditMaxColorRed;
	/// The label for the maximum value input field for the color green.
	QLabel * pLabelColorGreen;
	/// The maximum value input field for the color green.
	QLineEdit * pLineEditMaxColorGreen;
	/// The label for the maximum value input field for the color blue.
	QLabel * pLabelColorBlue;
	/// The maximum value input field for the color blue.
	QLineEdit * pLineEditMaxColorBlue;
	
	/**
	 * Element for the grayscale color information.
	 */
	/// The check box to mark that grayscale color should be used.
	QCheckBox * pCheckBoxColorGrayscale;
	
	/// The extension field for the grayscale color max values.
	QWidget * pExtensionColorGrayscale;
	
	/// The label for the maximum value input field for the grayscale color.
	QLabel * pLabelColorGrayscale;
	/// The maximum value input field for the grayscale color.
	QLineEdit * pLineEditMaxColorGrayscale;
	
	
	/**
	 * Element for the transparency information.
	 */
	/// The check box to mark that transparency should be used.
	QCheckBox * pCheckBoxTransparency;
	
	/// The extension field for the transparency max values.
	QWidget * pExtensionTransparency;
	/// The label for the maximum value input field for the transparency.
	QLabel * pLabelTransparency;
	/// The maximum value input field for the transparency.
	QLineEdit * pLineEditMaxTransparency;
	
	/**
	 * Buttons for the dialog.
	 */
	/// box for the buttons
	QDialogButtonBox * pButtonBox;
	/// button to create the Fib object
	QPushButton * pButtonCreate;
	/// button to cancel the creation of the Fib object
	QPushButton * pButtonChancel;
	
	/**
	 * The variables to organize the layout of the dialog.
	 */
	QHBoxLayout * pLayoutDimension1;
	QHBoxLayout * pLayoutDimension2;
	QHBoxLayout * pLayoutColorRed;
	QHBoxLayout * pLayoutColorGreen;
	QHBoxLayout * pLayoutColorBlue;
	QVBoxLayout * pLayoutExtColorRgb;
	QHBoxLayout * pLayoutColorGrayscale;
	QHBoxLayout * pLayoutTransparency;
	QVBoxLayout * pLayoutMain;
	
	
public:
	
	/**
	 * standard constructor for a Fib object node
	 *
	 * @param pParent a pointer the parent of this new Fib object dialog window
	 */
	cDialogNewFibObject( QWidget * pParent = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cDialogNewFibObject();
	
	/**
	 * This method will create the Fib object and return a pointer to the
	 * Fib (root) object for the dialog.
	 * BEWARE: You have to care that the returned Fib object is deleted (deleteObject())
	 *
	 * @return a pointer to the Fib (root) object for the dialog
	 */
	cRoot * getFibObject();
	
	/**
	 * @return the name of this class "cDialogNewFibObject"
	 */
	virtual std::string getName() const;
	
protected:
	
	/**
	 * @return a hint for a good size of this window
	 */
	virtual QSize sizeHint() const;
	
};//end class cDialogNewFibObject

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_DIALOG_NEW_FIB_OBJECT_H__





