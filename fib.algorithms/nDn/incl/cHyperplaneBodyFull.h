/**
 * @file cHyperplaneBodyFull
 * file name: cHyperplaneBodyFull.h
 * @author Betti Oesterholz
 * @date 28.01.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a body with hyperplanes as its borders.
 * @pattern strategy
 *
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
 * This header specifies a class for a body with hyperplanes as its borders.
 * This body is defined by inequiations, all points wich fulfill the
 * inequiations are part of the body.
 * For the body all its hyperplane borders are stored and evalued.
 *
 * Beware of the curse of dimensions! The complexity of the body will
 * grow exponential with the number of dimensions. For example, just the
 * number of border points of a newly created body will be 2^uiDimensions .
 *
 * @see cHyperplaneBodyFull
 * @see cHyperplane
 * @see cInequation
 */
/*
History:
28.01.2011  Oesterholz  created
27.02.2011  Oesterholz  method getNumberOfBorderPoints() added
*/

#ifndef ___C_HYPERPLANE_BODY_FULL_H__
#define ___C_HYPERPLANE_BODY_FULL_H__


#include "version.h"

#include "cHyperplaneBody.h"

#include <vector>
#include <set>
#include <list>
#include <ostream>




namespace fib{

namespace algorithms{

namespace nDn{

/**
 * Namespace for helperclasses for the cHyperplaneBodyFull class.
 */
namespace nHyperplaneBodyFull{
	//classes for the hyperplane
	
	template < class tFactors > class cInequationData;
	
	
	/**
	 * @class cHyperplaneData
	 * The data for a hyperplane.
	 */
	template <class tFactors> class cHyperplaneData{
	public:
	friend class cHyperplaneBodyFull;
	
		/**
		 * The typs for the list with hyperplane references.
		 */
		typedef set< cHyperplaneData< tFactors > * > typeSetPHyperplanes;
		
		typedef typename typeSetPHyperplanes::iterator typeItrSetPHyperplanes;
		
		/**
		 * A list with the pointers to the point, which are contained
		 * directly or indirectly in this hyperplane. (They have 0 direction
		 * vectors.)
		 * This is for faster evaluation of @see isPart()
		 * @see bUpdateContainedPoints and @see setContainingBorders
		 */
		typeSetPHyperplanes setContainedPoints;

		/**
		 * A list with the pointers to the hyperplanes borders, which contain directly or
		 * indirectly in this hyperplane. (They are not contained in any
		 * other hyperplane.)
		 * This is for faster evaluation of @see isPart()
		 * @see bUpdateContainedPoints and @see setContainedPoints
		 */
		typeSetPHyperplanes setContainingBorders;
		
		/**
		 * This boolean indicates if the setContainedPoints should be updated.
		 * If false setContainedPoints contains all point hyperplanes, wich are
		 * directly or indirectly contained in this hyperplane.
		 * @see setContainedPoints and @see setContainingBorders
		 */
		bool bUpdateContainedPoints;
		
	public:
		
		/**
		 * The hyperplane, for which this data is.
		 * (It has d directions vectors.)
		 */
		cHyperplane< tFactors > hyperplane;
		
		/**
		 * A list with the pointers to the hyperplanes, which contain
		 * directly this hyperplane. (They have d + 1 direction vectors.)
		 */
		typeSetPHyperplanes setContainingHyperplanes;
		
		/**
		 * A list with the pointers to the hyperplanes, which are directly
		 * contained in this hyperplane. (They have d - 1 direction vectors.)
		 */
		typeSetPHyperplanes setContainedHyperplanes;
		
		/**
		 * If existing, a pointer to the inequiation which created this
		 * hyperplane.
		 */
		cInequationData< tFactors > * pInequiation;
		
		
		/**
		 * standard constructor
		 */
		cHyperplaneData();
		
		/**
		 * parameter constructor
		 *
		 * @param inInequiation the inequiation from which to create the hyperplane
		 * @param uiDimensions the number of dimensions of the space for the hyperplane
		 */
		cHyperplaneData( cInequationData< tFactors > & inInequiation,
			unsigned int uiDimensions );
		
		/**
		 * destructor
		 */
		~cHyperplaneData();
		
		/**
		 * This method adds the given hyperplane (pointer) as a contained
		 * hyperplane. It will also add the pointer to this hyperplane as
		 * the containing hyperplane in the given hyperplane
		 * pContainedHyperplane.
		 * @see setContainedHyperplanes and @see setContainingHyperplanes
		 *
		 * @param pContainedHyperplane a pointer to the hyperplane to add as
		 * 	the contained hyperplane
		 */
		void addContainedHyperplane( cHyperplaneData< tFactors > * pContainedHyperplane );
		
		/**
		 * @return if the given hyperplane is part of this hyperplane true,
		 * 	else false; @see setContainedHyperplanes
		 */
		bool isPart( const cHyperplaneData< tFactors > * pHyperplane );
		
	};//cHyperplaneData
	
	
	
	/**
	 * @class cInequationData
	 * The data for a inequiation.
	 */
	template <class tFactors> class cInequationData{
	public:
	
		/**
		 * The inequiation, for which this data is.
		 */
		cInequation< tFactors > inequiation;
		
		/**
		 * A pointer to the hyperplane which this inequiation has created.
		 */
		cHyperplaneData< tFactors > * pHyperplane;
		
		
		/**
		 * standardconstructor
		 */
		cInequationData();
		
		/**
		 * parameterconstructor
		 *
		 * @param inInequiation the inequiation for the inequiation data
		 * @param pInHyperplane the pointer to the hyperplane for the inequiation
		 */
		cInequationData( const cInequation< tFactors > & inInequiation,
				cHyperplaneData< tFactors > * pInHyperplane = NULL );
		
		/**
		 * destructor
		 */
		~cInequationData();
		
	};//cInequationData
	
	
	/**
	 * This function compares vectors correspondending to the number
	 * associated with them.
	 *
	 * @param paFirst the first pair to compare
	 * @param paSecond the second pair to compare
	 * @return true if the first element of the first pair is lower than
	 * 	the second, else false
	 */
	template <class tFactors>
	bool sortLowerFirst( const pair< unsigned int, vector< tFactors > > & paFirst,
			const pair< unsigned int, vector< tFactors > > & paSecond );
	
	
};//nHyperplaneBodyFull


using namespace nHyperplaneBodyFull;

template <class tFactors>
class cHyperplaneBodyFull: public cHyperplaneBody< tFactors >{
protected:
	
	/**
	 * A vector with the borders of this body.
	 * The index of the vector is the dimensionality of the borders of the
	 * list to the vectorelement. (e. g. vecBorders[0] contains the
	 * borderpoints of the body)
	 */
	vector< list< cHyperplaneData< tFactors > * > > vecBorders;
	
	/**
	 * The list with the inequiations which constrain this body.
	 * (Ther are equivallent to the border hyperplanes, with the highest
	 * dimensionality.)
	 */
	list< cInequationData< tFactors > * > liInequiations;
	
	
public:
	/**
	 * standard constructor
	 *
	 * @param uiInDimensions the dimensions of the space for the hyperbody;
	 * 	all added inequiations should have this much factors
	 * 	@see uiDimensions
	 * @param maxValue the maximum possible value in all directions
	 * 	the evalued hyperbody will allways inside a hypercubus of all
	 * 	vectors = (x_0,..., x_uiDimensions)^T, with
	 * 	-1 * maxValue <= x_i <= maxValue for 0 <= i <= uiDimensions
	 */
	cHyperplaneBodyFull( unsigned int uiInDimensions,
		const tFactors maxValue = 1E+36 );
	
	
	/**
	 * copy constructor
	 *
	 * @param hyperplaneBody the body to copy
	 */
	cHyperplaneBodyFull( const cHyperplaneBodyFull< tFactors > & hyperplaneBody );
	
	/**
	 * standard destructor
	 */
	virtual ~cHyperplaneBodyFull();
	
	/**
	 * With this method the hyperplane body can be restricted by the given
	 * inequiation, if the inequiation dosn't remove the body.
	 * If ther are points in this hyperplane body exists wich fulfill the
	 * inequiation, an hyperplane for the inequiation is created and added
	 * to this hyperplane body.
	 * 
	 * @see addInequiations()
	 * @see cInequation
	 * @see cInequation::cHyperplane( const cInequation & inequation )
	 *
	 * @return if true this body was restricted by the given inequiation,
	 * 	else the inequiation would remove this body
	 */
	virtual bool addInequiation( const cInequation< tFactors > & inequiation );
	
	/**
	 * @return the number of border points of the body
	 */
	virtual unsigned long getNumberOfBorderPoints() const;
	
	/**
	 * @return a vector with the border points of the body
	 */
	virtual vector< vector< tFactors > > getBorderPoints() const;
	
	/**
	 * This method checks if the given point is part of the hyperbody.
	 * If the point is on one of the borders of the hyperbody or inside it,
	 * it is part of the hyperbody.
	 *
	 * @param vecPoint the point to check
	 * @return true if the point vecPoint is part of the hyperbody, else false
	 */
	virtual bool isPart( const vector< tFactors > & vecPoint ) const;
	
	/**
	 * This method print the hyperplane in a readebel form to the given
	 * output stream outputSream.
	 *
	 * @param outputSream the stream wher to print this inequation to
	 */
	virtual void print( ostream & outputStream ) const;

	/**
	 * This method duplicates this whole hyperplane body.
	 *
	 * @return the cloned/ duplicates hyperplane body
	 */
	virtual cHyperplaneBodyFull<tFactors> * clone() const;

protected:

	/**
	 * This method evalues and inserts the intersections for the given
	 * hyperplanes liHyperplanes into this body.
	 * The hyperplanes of liHyperplanes should be allready in this body.
	 * The hyperplanes of liHyperplanes should also have the same
	 * dimensionality (number of directions) uiDimensionality.
	 * The containing hyperplanes of the hyperplanes in liHyperplanes, should
	 * be allready evalued.
	 *
	 * @param liHyperplanes the list with the hyperplanes, for which to evalue
	 * 	the intersections with this body
	 * @param uiDimensionality the dimensionality (number of directions) of
	 * 	the hyperplanes in liHyperplanes;
	 * 	because the containing hyperplanes of the liHyperplanes should be
	 * 	allready evalued, it should be uiDimensionality <= iDimensions - 2
	 * @return a list with the pointers of the new created intersection hyperplanes
	 */
	list< cHyperplaneData< tFactors > * > addIntersectionsFor(
		list< cHyperplaneData< tFactors > * > & liHyperplanes,
		const unsigned int uiDimensionality );
};


};//end namespace nDn
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../src/cHyperplaneBodyFull.cpp"


#endif //___C_HYPERPLANE_BODY_FULL_H__
