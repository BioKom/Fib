/**
 * @file cInitFibEnviroment
 * file name: cInitFibEnviroment.h
 * @author Betti Oesterholz
 * @date 15.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for initialization of the enviroment.
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
 * This header specifies a abstract class for initialization of the enviroment.
 * the enviroment is intialisized for optimizing fib -individuals.
 * The intialization should:
 * 	- load the originalindividual
 * 	- insert a individual into the enviroment (cEnviroment)
 * 	- call the cInitOperator
 *
 */
/*
History:
15.03.2010  Oesterholz  created
*/

#ifndef ___C_INIT_FIB_ENVIROMENT_H__
#define ___C_INIT_FIB_ENVIROMENT_H__

#include "version.h"

#include "cInitEnviroment.h"

#include "cRoot.h"

using namespace fib;

namespace enviroment{
namespace fib{


class cInitFibEnviroment: public enviroment::cInitEnviroment{
protected:
	
	cRoot * pOriginalIndividual;

public:
	
	/**
	 * constructor of cInitFibEnviroment
	 *
	 * @param pFibOriginal the original individual, with which the enviroment
	 * 	should be initializised
	 */
	cInitFibEnviroment( const cRoot & pFibOriginal );

	/**
	 * copyconstructor of cInitFibEnviroment
	 *
	 * @param initFibEnviroment cInitFibEnviroment to copy
	 */
	cInitFibEnviroment( const cInitFibEnviroment & initFibEnviroment );


	/**
	 * destructor
	 */
	virtual ~cInitFibEnviroment();

	/**
	 * @return a pointer to the object which is represented by the individual
	 */
	virtual bool initEnviroment() const;

	/**
	 * This method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cInitFibEnviroment * clone() const;

	/**
	 * @return the name of this class
	 */
	virtual string getClassName() const;



};//end class cInitFibEnviroment


};//end namespace fib
};//end namespace enviroment

#endif //___C_INIT_FIB_ENVIROMENT_H__







