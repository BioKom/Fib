/**
 * @file cFibIndividual
 * file name: cFibIndividual.h
 * @author Betti Oesterholz
 * @date 01.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a fib -individal.
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
 * This header specifies a class for a fib -individals.
 * An individal is an central object on which the genetic algorithm
 * (enviroment) works.
 * It contains a fib -object with it's information.
 *
 */
/*
History:
01.03.2010  Oesterholz  created
*/

#ifndef ___C_FIB_INDIVIDUAL_H__
#define ___C_FIB_INDIVIDUAL_H__

#include "version.h"

#include "cIndividual.h"

#include "cFibElement.h"

namespace enviroment{
namespace fib{


class cFibIndividual: public cIndividual{

protected:
	
	/**
	 * The fib -object which is represented by the individual.
	 */
	cFibElement * pFibObject;
	
public:

	/**
	 * constructor
	 *
	 * @param pInFibObject the fib -object which is represented by the individual;
	 * 	this fib -object won't be copied but destructed when the individual is
	 * 	destructed if bInDeleteObjectOnDestruction is true
	 * @param inIndividalInfo the information for the individual
	 * @param bInDeleteObjectOnDestruction if true delete the object
	 * 	(pInObject) when the individual is deleted
	 */
	cFibIndividual( cFibElement * pInFibObject, const cIndividualInfo & inIndividalInfo,
		bool bInDeleteObjectOnDestruction=true );
	
	/**
	 * constructor
	 * A copy of the contained fib individual is also done.
	 *
	 * @param fibIndividual the fib -individual to copy
	 */
	cFibIndividual( const cFibIndividual & fibIndividual );

	/**
	 * destructor
	 * It deletes the objekt to the individual.
	 */
	virtual ~cFibIndividual();
	
	/**
	 * @return a pointer to the object which is represented by the individual
	 */
	virtual cFibElement * getFibObject();
	
	/**
	 * @return a pointer to the object which is represented by the individual
	 */
	virtual const cFibElement * getFibObject() const;
	
	/**
	 * @return the name of this class
	 */
	virtual string getClassName() const;

	/**
	 * Comparisson on equal method for two cIndividual objects.
	 *
	 * @param individual the cIndividual to compare this
	 * 	idIndividualobject to
	 * @param checkIdentifiers if true (standradvalue) the identifiers will
	 * 	be checked allso, else not
	 * @return true if the cIndividual this object represents is
	 * 	equal to the cIndividual the given object individual
	 * 	represents
	 */
	virtual bool equal( const cIndividual &individual, bool checkIdentifiers=true ) const;

	/**
	 * This method clones this individual inclusive the containing object.
	 *
	 * @return a clone of this object
	 */
	virtual cFibIndividual * clone() const;

	/**
	 * This method clones this individual inclusive the containing object.
	 *
	 * @return a clone of this object
	 * @param bCloneObject if true the object will be cloned and
	 * 	@see bInDeleteObjectOnDestruction will be set to true, if false
	 * 	the object won't be cloned and @see bInDeleteObjectOnDestruction
	 * 	will be set to false
	 */
	virtual cFibIndividual * clone( bool bCloneObject ) const;


#ifdef TEST
protected:
#endif
	/**
	 * This method kills the individual, so it isn't living anymor.
	 *
	 * @see cIndividualInfo::isLiving()
	 * @see cIndividualInfo::bIsLiving
	 * @return true if the individal was killed, else false
	 */
	virtual bool kill();

};//end class cFibIndividual


};//end namespace fib
};//end namespace enviroment

#endif //___C_FIB_INDIVIDUAL_H__







