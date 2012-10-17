/**
 * @file cResourceCheck
 * file name: cResourceCheck.h
 * @author Betti Oesterholz
 * @date 19.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies the basisclass for checking if enougth resources
 * are exists to run more operations.
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
 * This header specifies the basisclass for checking if enougth resources
 * are exists to run more operations.
 * The test of this class (but not necessarily it's children) is true if:
 * 	- ther are betwean 2 and 32 operations running
 *
 * @see cEnviroment
 */
/*
History:
19.03.2010  Oesterholz  created
06.06.2010  Oesterholz  method getClassName() added
*/


#ifndef ___C_RESOURCE_CHECK_H__
#define ___C_RESOURCE_CHECK_H__

#include "version.h"

#include <string>


namespace enviroment{


class cResourceCheck{
protected:
	
	/**
	 * The maximal number of operations which should run in the enviroment.
	 */
	unsigned int uiMaxOperationsToRun;
	
public:

	/**
	 * constructor
	 *
	 * @param uiInMaxOperationsToRun the maximal number of operations which
	 * 	should run in the enviroment
	 */
	cResourceCheck( unsigned int uiInMaxOperationsToRun = 8 );
	
	/**
	 * Destructor of the class cResourceCheck.
	 */
	virtual ~cResourceCheck();

	/**
	 * @return true if enougth resources exists to start more operations
	 * 	(ther are under 32 operations running), else false
	 */
	virtual bool enoughResources() const;

	/**
	 * This method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cResourceCheck * clone() const;

	/**
	 * @return the name of this class
	 */
	virtual std::string getClassName() const;

};//end class cResourceCheck


};//end namespace enviroment

#endif //___C_RESOURCE_CHECK_H__







