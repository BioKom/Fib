/**
 * @file cConvertFibDatabaseObject
 * file name: cConvertFibDatabaseObject.h
 * @author Betti Oesterholz
 * @date 29.01.2013
 * @mail Oesterholz@Fib-development.org
 *
 * System: C++
 *
 * This header specifies a class to convert Fib database objects.
 *
 * Copyright (C) @c GPL3 2012 Betti Oesterholz
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
 * This header specifies a class to convert Fib database objects.
 * For this the given external object elements will be changed, so
 * they match the requirements.
 * @pattern Strategy
 */
/*
History:
29.01.2013  Oesterholz  created
*/


#ifndef ___C_CONVERT_FIB_DATABASE_OBJECT_H__
#define ___C_CONVERT_FIB_DATABASE_OBJECT_H__

#include "version.h"

#include "cExtObject.h"
#include "cFibDatabase.h"


namespace fib{

namespace algorithms{

namespace nFibDatabase{


class cConvertFibDatabaseObject{
public:
	
	/**
	 * This function converts the given external object into the external
	 * object with a point subobject if possible.
	 * BEWARE: You have to add the color property directly below the created
	 * 	point.
	 * 	You have to care that the created (if converted) point element
	 * 	is deleted.
	 *
	 * @param pExternalObject a pointer to the external object to convert
	 * 	to it's version with a point subobject;
	 * 	BEWARE: this object will be changed to its version with point subobject
	 * @return a pointer to the version with a point subobject of the
	 * 	external object, or NULL if non exists
	 */
	cExtObject * convertToPointSubObject( cExtObject * pExternalObject );
	
	/**
	 * This function converts the given external object into an antialised
	 * external object if possible.
	 * BEWARE: You have to add the color property directly below the created
	 * 	point or above the created transparency property.
	 * 	You have to care that the created (if converted) point and property
	 * 	element are deleted.
	 *
	 * @param pExternalObject a pointer to the external object to convert
	 * 	to it's antialised version;
	 * 	BEWARE: this object will be changed to its antialised version
	 * @return a pointer to the antialised version of the external object,
	 * 	or NULL if non exists
	 */
	cExtObject * convertToAntialised( cExtObject * pExternalObject );
	
};//class cConvertFibDatabaseObject


};//end namespace nFibDatabase
};//end namespace algorithms
};//end namespace fib


#endif //___C_CONVERT_FIB_DATABASE_OBJECT_H__


