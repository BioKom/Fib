/**
 * @file cUseConvertAreaToExtObjectsStrategy
 * file name: cUseConvertAreaToExtObjectsStrategy.h
 * @author Betti Oesterholz
 * @date 26.01.2013
 * @mail Oesterholz@Fib-development.org
 *
 * System: C++
 *
 * This file implements a class to manage the strategy to convert a area
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


#include "version.h"

#include "cUseConvertAreaToExtObjectsStrategy.h"

#include "cImageStructureConvertToTiles.h"


using namespace fib::algorithms::nConvertToFib::nImage::nStructureData::nConvertToFib;


/**
 * standard constructor
 *
 * @param pInConvertStrategy a pointer to the strategy to use;
 * 	If NULL the default strategy will be used.
 * 	The given strategy will be cloned.
 * 	@see pConvertStrategy
 */
cUseConvertAreaToExtObjectsStrategy::cUseConvertAreaToExtObjectsStrategy(
		const iConvertAreaToExtObjects * pInConvertStrategy ):
		pConvertStrategy( NULL ){
	
	setStrategy( pInConvertStrategy );
}


/**
 * destructor
 */
cUseConvertAreaToExtObjectsStrategy::~cUseConvertAreaToExtObjectsStrategy(){
	
	if ( pConvertStrategy ){
		delete pConvertStrategy;
	}
}


/**
 * @return the strategy to use to convert areas to a list of external objects
 */
const iConvertAreaToExtObjects * cUseConvertAreaToExtObjectsStrategy::
		getStrategy() const{
	
	return pConvertStrategy;
}


/**
 * Sets the strategy to use to convert areas to a list of external objects.
 *
 * @param pInConvertStrategy a pointer to the strategy to use;
 * 	If NULL the default strategy will be used.
 * 	The given strategy will be cloned.
 * 	@see pConvertStrategy
 */
void cUseConvertAreaToExtObjectsStrategy::setStrategy(
		const iConvertAreaToExtObjects * pInConvertStrategy ){
	
	if ( pConvertStrategy ){
		//delete old strategy
		delete pConvertStrategy;
	}
	//set new strategy
	if ( pInConvertStrategy ){
		pConvertStrategy = pInConvertStrategy->clone();
	}else{//no strategy given -> use default strategy
		pConvertStrategy = new cImageStructureConvertToTiles();
	}
}







