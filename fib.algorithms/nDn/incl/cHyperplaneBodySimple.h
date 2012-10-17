/**
 * @file cHyperplaneBodySimple
 * file name: cHyperplaneBodySimple.h
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
 * This implementation of the hyperplane body is simple with just points,
 * lines and hyperplanes of the maximal dimensionality. It is fast
 * but it dosn't work correct on big bodies.
 *
 * Beware of the curse of dimensions! The complexity of the body will
 * grow exponential with the number of dimensions. For example, just the
 * number of border points of a newly created body will be 2^uiDimensions .
 *
 * @see cHyperplaneBody
 * @see cHyperplane
 * @see cInequation
 */
/*
History:
28.01.2011  Oesterholz  created
27.02.2011  Oesterholz  method getNumberOfBorderPoints() added
03.04.2011  Oesterholz  reimplemented with optimized algorithm
*/

#ifndef ___C_HYPERPLANE_BODY_SIMPLE_H__
#define ___C_HYPERPLANE_BODY_SIMPLE_H__


#include "version.h"

#include "cHyperplaneBody.h"


#include <vector>
#include <set>
#include <list>
#include <ostream>



using namespace std;
using namespace fib::algorithms::nLinearInequation;


namespace fib{

namespace algorithms{

namespace nDn{

/**
 * Namespace for helperclasses for the cHyperplaneBodySimple class.
 */
namespace nHyperplaneBodySimple{
namespace nBorder{
	//classes for the hyperplane
	
	template < class tFactors > class cInequationData;
	template < class tFactors > class cLine;
	template < class tFactors > class cPoint;
	
	
	/**
	 * @class cHyperplaneData
	 * The data for a border hyperplane.
	 */
	template <class tFactors> class cHyperplaneData{
	public:
	
		/**
		 * The hyperplane, for which this data is.
		 * (It has d directions vectors.)
		 */
		cHyperplane< tFactors > hyperplane;

		/**
		 * A set with the pointers to the lines, which are contained
		 * in this hyperplane. (They have 1 direction vector.)
		 */
		set< nBorder::cLine< tFactors > * > setContainedLines;
		
		/**
		 * If existing, a pointer to the inequiation which created this
		 * hyperplane.
		 */
		cInequationData< tFactors > * pInequiation;
		
		/**
		 * If existing, a pointer to the inequiation which has as the
		 * hyperplane this hyperplane.
		 */
		cInequationData< tFactors > * pInequiationTwo;
		
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
		 * This method adds the given line (pointer) as a contained
		 * line. It will also add the pointer to this hyperplane as
		 * the containing hyperplane in the given line pContainedLine.
		 * @see setContainedLines
		 *
		 * @param pContainedLine a pointer to the line to add as
		 * 	the contained line
		 */
		void addContainedLine( nBorder::cLine< tFactors > * pContainedLine );
		
		
	};//cHyperplaneData
	
	/**
	 * @class cLine
	 * The data for a border line.
	 */
	template <class tFactors> class cLine{
	public:
	
		/**
		 * The hyperplane, for which this data is.
		 * (It has d directions vectors.)
		 */
		cHyperplane< tFactors > hyperplane;

		/**
		 * A set with the pointers to the points, which are contained
		 * in this line. (They have 0 direction vector.)
		 */
		set< nBorder::cPoint< tFactors > * > setContainedPoints;
		
		/**
		 * A set with the pointers to the hyperplanes, which contain
		 * in this line.
		 */
		set< nBorder::cHyperplaneData< tFactors > * > setContainingHyperplanes;
		
		
		/**
		 * standard constructor
		 */
		cLine();
		
		/**
		 * parameter constructor
		 *
		 * @param point1 a reference to the first point which creats this line
		 * @param point2 a reference to the second point which creats this line
		 */
		cLine( nBorder::cPoint< tFactors > & point1,
				nBorder::cPoint< tFactors > & point2 );
		
		/**
		 * destructor
		 */
		~cLine();
		
		/**
		 * This method adds the given point (pointer) as a contained
		 * point. It will also add the pointer to this line as
		 * the containing line in the given line pContainedPoint.
		 * @see setContainedPoints
		 *
		 * @param pContainedPoint a pointer to the point to add as
		 * 	the contained point
		 */
		void addContainedPoint( nBorder::cPoint< tFactors > * pContainedPoint );
		
	};//cLine

	/**
	 * @class cPoint
	 * The data for a border point.
	 */
	template <class tFactors> class cPoint{
	public:
	
		/**
		 * A vector for the position of this point.
		 */
		vector< tFactors > vecPointPosition;

		/**
		 * A set with the pointers to the hyperplanes, which contain
		 * in this line.
		 */
		set< nBorder::cLine< tFactors > * > setContainingLines;
		
		/**
		 * parameter constructor
		 *
		 * @param inVecPointPosition a vector for the position of this point
		 */
		cPoint( const vector< tFactors > & inVecPointPosition );
		
		/**
		 * destructor
		 */
		~cPoint();
		
	};//cPoint
	
	
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
	 * Class to compare two cPoint classes via pointers to them.
	 * Compared are just the position vectors of the two given points.
	 */
	template< class tFactors >
	class cPointPositionPointerCompare{
	public:
		bool operator() ( const cPoint< tFactors > * pPoint1,
				const cPoint< tFactors > * pPoint2 ) const{
			
			return ( pPoint1->vecPointPosition < pPoint2->vecPointPosition );
		}
	};
	
	
};//nBorder
};//nHyperplaneBodySimple


using namespace nHyperplaneBodySimple;

template <class tFactors>
class cHyperplaneBodySimple: public cHyperplaneBody< tFactors >{
protected:
	
	/**
	 * A set with the border hyperplanes of this body.
	 */
	set< nBorder::cHyperplaneData< tFactors > * > setBorders;
	
	/**
	 * A set with the border lines of this body.
	 */
	set< nBorder::cLine< tFactors > * > setBorderLines;
	
	/**
	 * A set with the border points of this body.
	 */
	typedef set< nBorder::cPoint< tFactors > *, nBorder::cPointPositionPointerCompare< tFactors > >
		typeSetOfPoints;
	typeSetOfPoints setBorderPoints;
	
	/**
	 * The list with the inequiations which constrain this body.
	 * (Ther are equivallent to the border hyperplanes, with the highest
	 * dimensionality.)
	 */
	list< nBorder::cInequationData< tFactors > * > liInequiations;
	
	
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
	cHyperplaneBodySimple( unsigned int uiInDimensions,
		const tFactors maxValue = 256 * 256 * 256 );
	
	
	/**
	 * copy constructor
	 *
	 * @param hyperplaneBody the body to copy
	 */
	cHyperplaneBodySimple( const cHyperplaneBodySimple< tFactors > & hyperplaneBody );
	
	/**
	 * standard destructor
	 */
	virtual ~cHyperplaneBodySimple();
	
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
	virtual cHyperplaneBodySimple<tFactors> * clone() const;

};


};//end namespace nDn
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../src/cHyperplaneBodySimple.cpp"


#endif //___C_HYPERPLANE_BODY_SIMPLE_H__
