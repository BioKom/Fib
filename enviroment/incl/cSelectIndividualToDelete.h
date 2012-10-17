/**
 * @file cSelectIndividualToDelete
 * file name: cSelectIndividualToDelete.h
 * @author Betti Oesterholz
 * @date 18.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a abstract class for selecting a bad individual.
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
 * This header specifies a abstract class for selecting a bad individual
 * from the enviroment.
 *
 * @see cEnviroment
 */
/*
History:
18.03.2010  Oesterholz  created
06.06.2010  Oesterholz  method getClassName() added
*/


#ifndef ___C_SELECT_INDIVIDUAL_TO_DELETE_H__
#define ___C_SELECT_INDIVIDUAL_TO_DELETE_H__

#include "version.h"

#include "cIndividual.h"


namespace enviroment{


class cSelectIndividualToDelete{
public:

	/**
	 * Destructor of the class cSelectIndividualToDelete.
	 */
	virtual ~cSelectIndividualToDelete() = 0;

	/**
	 * @return a pointer to the selected individualdentifier, or the identifier
	 * 	for no individual (@see cIndividualIdentifier::getNoIndividualIdentifier())
	 */
	virtual cIndividualIdentifier getIndividualIdentifier() const = 0;

	/**
	 * This method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cSelectIndividualToDelete * clone() const = 0;

	/**
	 * @return the name of this class
	 */
	virtual string getClassName() const;
	
};//end class cSelectIndividualToDelete


};//end namespace enviroment

#endif //___C_SELECT_INDIVIDUAL_TO_DELETE_H__







