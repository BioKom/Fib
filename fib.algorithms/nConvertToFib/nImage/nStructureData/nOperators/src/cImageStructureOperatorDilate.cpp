
//TODO check

/**
 * @file cImageStructureOperatorDilate
 * file name: cImageStructureOperatorDilate.cpp
 * @author Betti Oesterholz
 * @date 07.05.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header implements a class for the dilate operators on a image structure.
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
 *
 * This header implements a class for the dilate operators on a image structure.
 * The operator will add all the neighbour points of the structure to the
 * structure and adds the new neighbours.
 * For this a method operator() is defined.
 * The operator will change an image structure and adapt the given search data.
 *
 * @pattern Strategy
 * @see cImageStructure
 * @see cConvertImageToFib
 */
/*
History:
07.05.2013  Oesterholz  created
*/


#include "cImageStructureOperatorDilate.h"


using namespace fib::algorithms::nConvertToFib::nImage::nStructureData::nOperators;
using std::string;


/**
 * destructor
 */
cImageStructureOperatorDilate::~cImageStructureOperatorDilate(){
	//nothing to do
};


/**
 * This method is for execute this operator on the given image structure.
 *
 * @param pImageStructure the image structure on which to execute this operator
 * 	(Beware it will be changed)
 * @param pSearchData the image search data to update;
 * 	Points of the given image structure should be marked as found.
 * 	This operator will add all points added to the image structure
 * 	as found in the image search data pSearchData and set all
 * 	points as not found, which it deletes from the image structure
 * 	(After the call all points in the image structure and just these
 * 	will be marked as found.)
 * @return true if the operator was successful, else false
 */
bool cImageStructureOperatorDilate::operator()( cImageStructure * pImageStructure,
		cImageSearchData * pSearchData ) const{
	
	if ( ( pImageStructure == NULL ) || ( pSearchData == NULL ) ){
		//can't call operation
		return false;
	}
	
	bool bBorderInStructure = true;
	const set<cVectorPosition> & setBorderPoints =
		pImageStructure->getStructureBorderPointsConst();
	
	if ( setBorderPoints.empty() ){
		bBorderInStructure =
			pImageStructure->isStructurePoint( *(setBorderPoints.begin()) );
	}
	const set<cVectorPosition> & setNeighbourPoints =
		pImageStructure->getStructureNeighbourPointsConst();
	
	pSearchData->registerFound( setNeighbourPoints );
	
	set<cVectorPosition> setNeighbourNeigPoints;
	for ( set<cVectorPosition>::const_iterator
			itrNeighbour = setNeighbourPoints.begin();
			itrNeighbour != setNeighbourPoints.end(); itrNeighbour++ ){
		
		const set<cVectorPosition> setPointNotFoundNotOverlappedNeighbours =
			pSearchData->getNotFoundNotOverlappedNeighbours( *itrNeighbour );
		
		setNeighbourNeigPoints.insert( setPointNotFoundNotOverlappedNeighbours.begin(),
			setPointNotFoundNotOverlappedNeighbours.end() );
	}
	if ( bBorderInStructure ){
		pImageStructure->addStructurePoints( setNeighbourPoints );
		pImageStructure->setStructureBorderPoints( setNeighbourPoints );
		pImageStructure->setStructureNeighbourPoints( setNeighbourNeigPoints );
	}else{
		pImageStructure->addStructurePoints( setBorderPoints );
		pImageStructure->setStructureBorderPoints( setNeighbourPoints );
		pImageStructure->setStructureNeighbourPoints( setNeighbourNeigPoints );
	}
	
	return true;
}


/**
 * @return the name of this class
 */
string cImageStructureOperatorDilate::getName() const{
	
	return "cImageStructureOperatorDilate";
}








