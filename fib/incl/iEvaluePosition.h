/**
 * @class iEvaluePosition
 * file name: iEvaluePosition.h
 * @author Betti Oesterholz
 * @date 18.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the interface for evaluing Fib-objects.
 *
 * Copyright (C) @c LGPL3 2010 Betti Oesterholz
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
 * @pattern strategy
 * This file contains the interface for evaluing Fib-objects.
 * Every class which implements this interface have to implement the method
 * evaluePosition.
 * When the Fib-object is evalued this method is called every time a
 * pointelement is reached. The parameter for the method are the
 * positionsvector of the point and properties of the point.
 */
/*
History:
18.04.2010  Oesterholz  created
*/

#ifndef ___I_EVALUE_POSITION__
#define ___I_EVALUE_POSITION__

#include "version.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"


#include <list>


using std::list;

namespace fib{

class iEvaluePosition{
public:
	
	/**
	 * destructor
	 */
	virtual ~iEvaluePosition(){};

	/**
	 * The method with wich the evalued points with ther properties are
	 * inserted /evalued. Everytime a point (to evalue) is reached in the
	 * evaluation, this method is called with the position and the
	 * properties of the point.
	 *
	 * @param vPosition the position of the point, which is evalued
	 * @param vProperties a list of the properties of the point
	 */
	virtual bool evaluePosition( const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties ) = 0;

};//class iEvaluePosition

};

#endif


