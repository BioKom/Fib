/**
 * @file cMaximumReached
 * file name: cMaximumReached.h
 * @author Betti Oesterholz
 * @date 18.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for checking if enougth individuals are
 * in the enviroment.
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
 * This header specifies a class for checking if enougth individuals are
 * in the enviroment. If the test is true, no more individuals should be
 * added to the enviroment, befor deleting some old individuals from it.
 * The test of this class (but not necessarily it's children) is true if:
 * 	- ther are more than 65 536 individuals in the enviroment
 * 	- ther are more then 16 individuals in the envirmonet and less than
 * 		10 % of the main memory free
 *
 * @see cEnviroment
 */
/*
History:
18.03.2010  Oesterholz  created
06.06.2010  Oesterholz  method getClassName() added
*/


#ifndef ___C_MAXIMUM_REACHED_H__
#define ___C_MAXIMUM_REACHED_H__

#include "version.h"

#include <string>

namespace enviroment{


class cMaximumReached{
public:

	/**
	 * Destructor of the class cMaximumReached.
	 */
	virtual ~cMaximumReached();

	/**
	 * @return true if no more individuals should be added to the
	 * 	enviroment, else false
	 */
	virtual bool maximumReached() const;

	/**
	 * This method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cMaximumReached * clone() const;
	
	/**
	 * @return the name of this class
	 */
	virtual std::string getClassName() const;
	
};//end class cMaximumReached


};//end namespace enviroment

#endif //___C_MAXIMUM_REACHED_H__







