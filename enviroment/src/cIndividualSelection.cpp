/**
 * @file cIndividualSelection
 * file name: cIndividualSelection.cpp
 * @author Betti Oesterholz
 * @date 15.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements the abstract class for selecting a good individual.
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
 * This file implements the abstract class for selecting a good individual
 * from the enviroment.
 *
 * @see cEnviroment
 */
/*
History:
17.03.2010  Oesterholz  created
06.06.2010  Oesterholz  method getClassName() added
*/


#include "cIndividualSelection.h"


using namespace enviroment;



/**
 * Destructor of the class cIndividualSelection.
 */
cIndividualSelection::~cIndividualSelection(){
	//nothing to do
}


/**
 * @return the name of this class
 */
string cIndividualSelection::getClassName() const{
	return "cIndividualSelection";
}





