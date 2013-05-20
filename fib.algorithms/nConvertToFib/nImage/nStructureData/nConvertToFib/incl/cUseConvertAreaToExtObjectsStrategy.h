/**
 * @file cUseConvertAreaToExtObjectsStrategy
 * file name: cUseConvertAreaToExtObjectsStrategy.h
 * @author Betti Oesterholz
 * @date 26.01.2013
 * @mail Oesterholz@Fib-development.org
 *
 * System: C++
 *
 * This header specifies a class to manage the strategy to convert a area
 * of points to a list of external objects.
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
 * This header specifies a class to manage the strategy to convert a area
 * of points to a list of external objects.
 *
 * @patter strategy
 */
/*
History:
26.01.2013  Oesterholz  created
*/


#ifndef ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__N_CONVERT_TO_FIB__C_USE_CONVERT_AREA_TO_EXT_OBJECTS_STRATEGY_H__
#define ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__N_CONVERT_TO_FIB__C_USE_CONVERT_AREA_TO_EXT_OBJECTS_STRATEGY_H__

#include "version.h"

#include "iConvertAreaToExtObjects.h"

namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{

namespace nStructureData{

namespace nConvertToFib{


class cUseConvertAreaToExtObjectsStrategy{
protected:
	
	/**
	 * A pointer to the strategy to use.
	 * Allways existing (=not NULL).
	 *
	 * Should implement @see iConvertAreaToExtObjects
	 */
	iConvertAreaToExtObjects * pConvertStrategy;
	
public:
	
	/**
	 * Standard constructor
	 *
	 * @param pInConvertStrategy a pointer to the strategy to use;
	 * 	If NULL (standard value) the default strategy will be used.
	 * 	The given strategy will be cloned.
	 * 	@see pConvertStrategy
	 */
	cUseConvertAreaToExtObjectsStrategy(
			const iConvertAreaToExtObjects * pInConvertStrategy = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cUseConvertAreaToExtObjectsStrategy();
	
	/**
	 * @return the strategy to use to convert areas to a list of external objects
	 */
	const iConvertAreaToExtObjects * getStrategy() const;

	/**
	 * Sets the strategy to use to convert areas to a list of external objects.
	 *
	 * @param pInConvertStrategy a pointer to the strategy to use;
	 * 	If NULL (default value) the default strategy will be used.
	 * 	The given strategy will be cloned.
	 * 	@see pConvertStrategy
	 */
	void setStrategy( const iConvertAreaToExtObjects * pInConvertStrategy = NULL );
	
	
};//class cUseConvertAreaToExtObjectsStrategy


};//end namespace nConvertToFib
};//end namespace nStructureData
};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__N_CONVERT_TO_FIB__C_USE_CONVERT_AREA_TO_EXT_OBJECTS_STRATEGY_H__