/**
 * @class cVectorChecksum
 * file name: cVectorChecksum.h
 * @author Betti Oesterholz
 * @date 06.10.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a checksumm -property -vector.
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
 * This class represents a checksum -property -vector of the
 * Fib -multimedialanguage.
 * It is a vector for checksum -properties.
 *
 */
/*
History:
06.10.2009  Oesterholz  created
16.03.2013  Oesterholz  clone() method added
*/

#ifndef ___C_VECTOR_CHECKSUM_H__
#define ___C_VECTOR_CHECKSUM_H__


#include "cVectorProperty.h"

namespace fib{


class cVectorChecksum: public cVectorProperty{

friend class cRoot;

public:


	/**
	 * The constructor of the checksum -property -vector.
	 *
	 * @param pDefiningElement the Fib -element which
	 * 	defines/ uses the checksum -property -vector
	 */
	cVectorChecksum( cFibElement * pDefiningElement = NULL );

	/**
	 * The copy constructor of the vector.
	 *
	 * @param vector the vector from which to copy the data
	 * @param definingFibElement the Fib -element which defines/ uses
	 * 	the new vector
	 */
	cVectorChecksum( const cVectorChecksum & vector,
		cFibElement *definingFibElement = NULL );

	/**
	 * The constructor for restoring a vector from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node the vector is stored in
	 * @param outStatus An reference to an integervalue where the errorvalue
	 * 	can be stored to.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore vector, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 */
	cVectorChecksum( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables );


	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	virtual cVectorChecksum * clone() const;

	/**
	 * This method creates an instance of this vector type.
	 *
	 * @param pDefiningElement the Fib -propertyelement which
	 * 	defines/ uses the propertyvector
	 */
	virtual cVectorChecksum * createInstance(
		cFibElement * pDefiningElement = NULL ) const;

	/**
	 * Sets the variable of the iNumberElement'te vectorelement.
	 *
	 * @param iNumberElement the number of the element, where the variable is
	 * 	to set
	 * @param pVariable the variable to set
	 * @return true if the iNumberElement'te vectorelement is set to the
	 * 	given variable pVariable, else false
	 */
	virtual bool setVariable( unsignedIntFib iNumberElement, cFibVariable *pVariable );

	/**
	 * This Method makes this vectorelements equal to the correspondending
	 * vectorelements of the given vector.
	 * The type of the vector and the number of elements won't be changed.
	 *
	 * @param vector the vector to copy
	 */
	virtual cVectorChecksum & operator=( const cFibVector &vector );

};//cVectorChecksum
}//namespace fib

#endif //___C_VECTOR_CHECKSUM_H__






