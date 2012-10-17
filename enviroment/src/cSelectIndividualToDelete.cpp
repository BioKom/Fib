/**
 * @file cSelectIndividualToDelete
 * file name: cSelectIndividualToDelete.cpp
 * @author Betti Oesterholz
 * @date 15.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements the abstract class for selecting a bad individual.
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
 * This file implements the abstract class for selecting a bad individual
 * from the enviroment.
 *
 * @see cEnviroment
 */
/*
History:
18.03.2010  Oesterholz  created
06.06.2010  Oesterholz  method getClassName() added
*/


#include "cSelectIndividualToDelete.h"

using namespace enviroment;



/**
 * Destructor of the class cSelectIndividualToDelete.
 */
cSelectIndividualToDelete::~cSelectIndividualToDelete(){
	//nothing to do
}


/**
 * @return the name of this class
 */
string cSelectIndividualToDelete::getClassName() const{
	return "cSelectIndividualToDelete";
}







