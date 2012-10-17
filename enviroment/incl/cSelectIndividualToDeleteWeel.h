/**
 * @file cSelectIndividualToDeleteWeel
 * file name: cSelectIndividualToDeleteWeel.h
 * @author Betti Oesterholz
 * @date 18.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for selecting a bad individual.
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This header specifies a class for selecting a bad individual from the
 * enviroment.
 * The selection method is weelselction.
 * Every individual has a propability of selection which is reversed proportional
 * to it's fitnessvalue or a minimum propability, if it's fitness is higher
 * the maximum/ best case fitness.
 * The minimum probability p_min is: p_min = 1 / (#individuals * 1024)
 * 	(#individuals = the count of individuals to select from)
 *
 * @see cSelectIndividualToDelete
 * @see cEnviroment
 */
/*
History:
18.03.2010  Oesterholz  created
06.06.2010  Oesterholz  method getClassName() added
*/


#ifndef ___C_SELECT_INDIVIDUAL_TO_DELETE_WEEL_H__
#define ___C_SELECT_INDIVIDUAL_TO_DELETE_WEEL_H__

#include "version.h"

#include "cSelectIndividualToDelete.h"


namespace enviroment{


class cSelectIndividualToDeleteWeel: public cSelectIndividualToDelete{

public:
	
	/**
	 * standardconstructor
	 */
	cSelectIndividualToDeleteWeel();
	
	/**
	 * Destructor of the class cSelectIndividualToDeleteWeel.
	 */
	virtual ~cSelectIndividualToDeleteWeel();

	/**
	 * @return a pointer to the selected individualdentifier, or the identifier
	 * 	for no individual (@see cIndividualIdentifier::getNoIndividualIdentifier())
	 */
	virtual cIndividualIdentifier getIndividualIdentifier() const;
	
	/**
	 * This method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cSelectIndividualToDeleteWeel * clone() const;

	/**
	 * @return the name of this class
	 */
	virtual string getClassName() const;

};//end class cSelectIndividualToDeleteWeel

};//end namespace enviroment

#endif //___C_SELECT_INDIVIDUAL_TO_DELETE_WEEL_H__







