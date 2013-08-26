/**
 * @class cFibMatrix
 * file name: cFibMatrix.h
 * @author Betti Oesterholz
 * @date 02.01.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the Fib matrix element.
 * Copyright (C) @c LGPL3 2012 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This class represents the matrix element of the Fib multimedia language.
 * 
 * An matrix element represents a d dimensional matrix. For every dimension
 * ther is an area (Startvalue_h to Endvalue_h) for its possible index values.
 * Furthermore ther is a list ( (W_{1.1}, ..., W_{i.1}), ... ,
 * (W_{1.k}, ..., W_{i.k}) with vectors for the elements of the matrix.
 * 
 * In the evaluation of the matrix element each dimension/counter/index
 * variable (Variable_1, ..., Variable_d) goes through all integers of
 * the corresponding area (Startvalue_h to Endvalue_h). For each integer
 * value of the Variable_h all integer values of the variable Variable_{h-1}
 * will be set. For each value allocation of the dimension variables 
 * (Variable_1, ... , Variable_d) the value variables (Variable_{d+1}, ... ,
 * Variable_{d+i}) will be set to the next set of values (W_{1.b}, ... , W_{i.b}).
 * This continues until either the dimension variables (Variable_1, ... ,
 * Variable_d) have gone through all of their values or there is no next 
 * set of values (W_{1.k+1}, ... , W_{i.k+1}). If an element W_{a.b} is a 
 * variable, so the Variable_{d+a} will be assigned according to the value
 * of the variable W_{a.b}.
 * 
 * If there are no value variables (i=0), just all the values of the
 * dimension variables (Variable_1, ..., Variable_d) will be set and the
 * sets of values will be ignored.
 * 
 */
/*
History:
02.01.2012  Oesterholz  created
30.07.2013  Oesterholz  method assignValues() added
*/

#ifndef ___C_FIB_MATRIX_H__
#define ___C_FIB_MATRIX_H__


#include "version.h"

#include "fibDatatyps.h"

#include "cFibLimb.h"
#include "cRoot.h"
#include "cVectorFibMatrix.h"
#include "cVectorArea.h"
#include "cFibVariable.h"

namespace fib{


class cFibMatrix: public cFibLimb{

friend class cFibElement;

private:

	/**
	 * The variables, which this matrix element defines.
	 */
	vector< cFibVariable * > vecVariablesDefined;

	/**
	 * The vector with the area vectors for the dimensions of the matrix.
	 * The vector element i is for dimension i .
	 */
	vector< cVectorArea * > vecMatrixDimensionAreas;
	
	/**
	 * The list with the vectors of the matrix element.
	 */
	list< cVectorFibMatrix > liFibMatrix;
	
	/**
	 * The number of the matrix element domain for this matrix element.
	 */
	unsignedIntFib uiDomainNr;

public:

	/**
	 * parameter constructor
	 *
	 * @param iuNumberOfDimensions the number of dimension (variables)
	 * 	(minimum is 1)
	 * @param iuNumberOfVectorElements the number of elements in the vectors
	 * 	of the elements of the matrix of this matrix element should have
	 * @param pInSubobject the Fib element which is the subobject of
	 * 	this Fib element (it also stands next in the order of Fib elements)
	 * @param pInSuperiorElement the Fib element in which this
	 * 	matrix element is a subobject
	 */
	cFibMatrix( unsignedIntFib iuNumberOfDimensions,
		const unsignedIntFib iuNumberOfVectorElements,
		cFibElement * pInSubobject = NULL,
		cFibElement * pInSuperiorElement = NULL );
	
	/**
	 * copyconstructor
	 * This copyconstructor constructs a copy of the given matrix element.
	 * It dosn't copy other Fib elements than the given, even if ther are
	 * in the matrix element.
	 *
	 * @param matrixElement the matrix element to copy
	 */
	cFibMatrix( const cFibMatrix &matrixElement );

protected:

	/**
	 * The constructor for restoring a matrix object from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node wher the Fib object is stored in
	 * @param outStatus An reference to an integervalue where the errorvalue
	 * 	can be stored to.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore Fib element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 */
	cFibMatrix( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables );

	/**
	 * This constructor restores a matrix object from the stream where it is
	 * stored in the compressed Fib format.
	 * This method is for internal use only.
	 *
	 * @param iBitStream the stream wher the matrix object is stored in,
	 * 	because this stream is an cReadBits, any number of bits can be
	 * 	readed from it
	 * @param outStatus An reference to an integer value where the error value
	 * 	can be stored to. If the pointer is NULL no error value will be
	 * 	given back.
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore Fib element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param validDomains the domains valid for restoring the Fib elements
	 * @param pNextRoot the next higher root-element for the to restore
	 * 	Fib elements, or the last restored root-element
	 */
	cFibMatrix( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot );


public:

	/**
	 * destructor
	 */
	virtual ~cFibMatrix();

	/**
	 * @see getTypeName
	 * @return a character for the typ of the Fib element
	 * Types are:
	 *		- u: element of unknown typ
	 *		- p: point
	 * 	- l: list-element
	 *		- y: property
	 *		- c: comment
	 *		- a: area
	 *		- f: function
	 *		- i: if-condition
	 *		- o: extern object element
	 *		- s: extern subobject element
	 *		- v: set-element
	 *		- m: matrix element
	 *		- r: root-element
	 */
	virtual char getType() const;
	
	/**
	 * This method checks, if this Fib-element is an valid Fib-element.
	 *
	 * @return true if this Fib-element is an valid Fib-element, else false
	 */
	virtual bool isValidFibElement() const;

	/**
	 * This method evaluades the Fib object.
	 *
	 * @param evaluePosition a reference to the object with the
	 * 	evaluePosition() method to evalue /store the positions and ther
	 * 	properties; everytime a point (to evalue) is reached in the
	 * 	evaluation, this method is called with the position and the
	 * 	properties of the point; @see iEvaluePosition
	 * @param objectPoint the object point in the order of true part objects
	 * 	to evalue
	 * @param liVecProperties a list with the property vectors which should
	 * 	be global for the evalued object
	 * @return if the evaluation was successfull true, else false
	 */
	virtual bool evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const;

	/**
	 * This method evaluades the Fib object.
	 * Evertime a Fib elements, with a type of the given type chars in
	 * liCFibElementTyps, is reached while evaluation, it is given
	 * back with the properties which it has.
	 * Ever point element is given back. The type chars for point elements
	 * don't need to be in the list liCFibElementTyps.
	 *
	 * @param evalueFibElement a reference to the object with the
	 * 	evalueElement() method to evalue /store the Fib elements and ther
	 * 	properties; everytime a Fib element (with one of the type given
	 * 	in liCFibElementTyps) is reached in the evaluation, the method
	 * 	evalueElement() of this objects is called with the Fib element
	 * 	and the properties of the Fib element; @see iEvalueFibElement
	 * @param objectPoint the object point in the order of true part objects
	 * 	to evalue
	 * @param liVecProperties a list with the property vectors which should
	 * 	be global for the evalued object
	 * @param liCFibElementTyps a list with the type chars (@see getType)
	 * 	of the Fib elements to return
	 * @return if the evaluation was successfull true, else false
	 */
	virtual bool evalueObject( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties,
		const list<char> & liCFibElementTyps );

	/**
	 * This method evaluades a value for the time needed to evalue the
	 * object.
	 * This value should not exceed lMaxTime, if the value for the time
	 * is greater than lMaxTime the evaluation will be stopt and lMaxTime
	 * returned. If lMaxTime is 0 (for infinity) the evaluation won't be
	 * stoped, this is the standard case.
	 *
	 * @see evalueObject()
	 * @param lMaxTime the maximum time for the evaluation, the returned value
	 * 	will not be greater than this value; the value 0 stands for infinity,
	 * 	so the evaluation won't be stoped
	 * @return a value for the time needed to evalue the object
	 */
	virtual unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;

	/**
	 * This method evaluades the size of the Fib object in bits in the
	 * compressed file form.
	 *
	 * @see store()
	 * @return the size of the Fib object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;

	/**
	 * This method checks if the given variable is used in the given
	 * direction from this Fib element.
	 *
	 * @see cFibVariable
	 * @see isDefinedVariable()
	 * @param variable the variable to check if it is used
	 * @param direction the direction from this Fib element, in which the
	 * 	variable should be used; default value is ED_POSITION so yust
	 * 	this Fib element will be checked
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable *variable ,
		edDirection direction=ED_POSITION ) const;

	/**
	 * This method returns all variables used in the given direction from
	 * this Fib element.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @see isDefinedVariable()
	 * @param direction the direction from this Fib element, in which the
	 * 	variable should be used; default value is ED_POSITION so yust
	 * 	this Fib element will be checked
	 * @return the set with all variables used in the given direction from
	 * 	this Fib element
	 */
	virtual set<cFibVariable*> getUsedVariables( edDirection direction=ED_POSITION );

	/**
	 * This method replace the variable pVariableOld with the variable
	 * pVariableNew in the object.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @see isDefinedVariable()
	 * @param pVariableOld the variable to replace
	 * @param pVariableNew the variable with which the variable pVariableOld
	 * 	is to be replace
	 * @return true if the variable pVariableOld is replaced with pVariableNew,
	 * 	else false
	 */
	virtual bool replaceVariable( cFibVariable * pVariableOld,
		cFibVariable * pVariableNew );

	/**
	 * This method copies the Fib element on the specified position.
	 * Variables which are not defined in the Fib element but used
	 * don't change ther reference.
	 *
	 * @see getType()
	 * @param cType the type of the Fib element to copy
	 * @param elementPoint the number of the Fib element, in the order of
	 * 	Fib elements of the given type cType, to copy
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib object
	 * @return the copy of the Fib element
	 */
	virtual cFibElement *copyElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false ) const;

	/**
	 * This method asigns / copies the values from the given Fib element
	 * fibElement to this Fib element. This means, it will copy everything
	 * of the Fib element fibElement except pointers to other Fib elements
	 * (e. g. for subobjects), these will remain the same.
	 * For that both Fib elements have to be of the same type.
	 *
	 * @see getType()
	 * @param fibElement the Fib element, from which to assign / copy the values
	 * @return true if the values could be copied from the given Fib element
	 * 	fibElement, else false
	 */
	virtual bool assignValues( const cFibElement & fibElement );

	/**
	 * This method stores this Fib object in the XML format into the
	 * given stream.
	 *
	 * @param stream the stream where this Fib object should be stored to
	 * @return true if this Fib object is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const;


/*
 * matrix element methods
 */


	/**
	 * @return the number of dimensions (variables) the matrix of this
	 * 	matrix element has
	 * @see vecMatrixDimensionAreas
	 */
	unsignedIntFib getNumberOfMatrixDimensions() const;
	
	/**
	 * @return the number of elements of the matrix entry vectors of the
	 * 	matrix of this matrix element has
	 * @see liFibMatrix
	 */
	unsignedIntFib getNumberOfVectorElements() const;

	/**
	 * This method returns a pointer to the uiPosition'th from this
	 * matrix element defined variable.
	 *
	 * @param uiPosition the number of the from this matrix element defined
	 * 	variable to return (counting begins with 1)
	 * @return a pointer to the uiPosition'th from this matrix element defined
	 * 	variable, or NULL if non such exists
	 */
	cFibVariable * getDefinedVariable( const unsignedLongFib uiPosition );
	
	
	/**
	 * @see uiDomainNr
	 * @return the number of the matrix element domain for this matrix element
	 */
	unsignedIntFib getDomainNr() const;
	
	/**
	 * This method sets the number of the matrix element domain for this
	 * matrix element.
	 * 
	 * @see uiDomainNr
	 * @param uiInDomainNumber the number of the matrix element domain for
	 * 	this matrix element
	 */
	void setDomainNr( const unsignedLongFib uiInDomainNumber );
	
	/**
	 * This method returns the area for the uiDimension'th dimension.
	 * 
	 * @see vecMatrixDimensionAreas
	 * @param uiDimension the dimension for which the area is to be returned
	 * 	(counting begins with 1)
	 * @return the area for the uiDimension'th dimension
	 */
	cVectorArea * getArea( const unsignedIntFib uiDimension=1 );

	/**
	 * @see liFibMatrix
	 * @return the number of vectors or sets of values this matrix element contains
	 */
	unsignedLongFib getNumberOfVectors() const;
	
	/**
	 * @return a vector with all vectors / sets of values of this matrix element
	 * @see liFibMatrix
	 */
	const vector< cVectorFibMatrix > getVectors();
	
	/**
	 * This method sets all vectors / sets of values of this matrix element
	 * to the given vectors.
	 * 
	 * @see liFibMatrix
	 * @param vecMatrixVectors a vector with all vectors / sets of values this
	 * 	matrix element should contain
	 * @return true if the vectors wher set, else false and the vectors of
	 * 	this matrix element unchanged
	 */
	bool setVectors( const vector< cVectorFibMatrix > & vecMatrixVectors );
	
	/**
	 * This method returns a pointer to the uiPosition'th vector of this
	 * matrix element.
	 *
	 * @see liFibMatrix
	 * @param uiPosition the number of the vector to return (counting begins
	 * 	with 1)
	 * @return a pointer to the uiPosition'th vector, or NULL if non such exists
	 */
	cVectorFibMatrix * getVector( const unsignedLongFib uiPosition );
	
	/**
	 * This method sets the uiPosition'th vector of this matrix element to
	 * the given vector.
	 *
	 * @see liFibMatrix
	 * @param vecMatrixVector the vector to set
	 * @param uiPosition the position wher the to matrix vector should stand
	 * 	in this matrix element (counting begins with 1)
	 * @return true if the vector wher set, else false and the vectors of
	 * 	this matrix element unchanged
	 */
	bool setVector( const cVectorFibMatrix & vecMatrixVector,
		const unsignedLongFib uiPosition );
	
	/**
	 * This method adds the given vector to the existing vectors.
	 *
	 * @see liSubFibMatrixs
	 * @param vecMatrixVector a reference to the to add vector
	 * @param uiPosition the position wher the vecMatrix should be added
	 * 	(counting begins with 1); if 0 the vecMatrix or greater than the number
	 * 	of vectors the vector will be added to the end of the vector list
	 * @return true if the vecMatrix was added, else false
	 */
	bool addVector( const cVectorFibMatrix & vecMatrixVector,
		const unsignedLongFib uiPosition=0 );
	
	/**
	 * This method deletes the uiPosition'th vector from the existing vectors.
	 *
	 * @param uiPosition the position, wher the vector should be deleted from
	 * 	(counting begins with 1)
	 * @return true if the vector was deleted, else false
	 */
	bool deleteVector( const unsignedLongFib uiPosition );


protected:

	/**
	 * This method stores this Fib object in the compressed Fib-format
	 * into the given stream.
	 * It is needed because the stream can yust store byts but the size of
	 * Fib elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the Fib elements.
	 *
	 * @see store
	 * @param stream the stream where this Fib object should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @return true if this Fib object is stored, else false
	 */
	virtual bool storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const;

	/**
	 * This method sets the each variable, which is defined above a leaf,
	 * to an uniqe integer number greater than the given number
	 * uiLastVariableNumber. While storing this number can be stored to
	 * identify the variable.
	 *
	 * @param uiLastVariableNumber the number which was last use, this
	 * 	means also is the greatest used, in this limb.
	 * @return the number which was last use, this
	 * 	means also is the greatest used, in this limb
	 * 	from the method
	 */
	virtual unsignedIntFib enumerateVariablesForStoring(
		unsignedIntFib uiLastVariableNumber = 0 );
	
	/**
	 * This method copies the connected object with the given number in the
	 * order of connected objects.
	 * For this every Fib element, beginning from this Fib element, that
	 * is part of the connected object will be copied.
	 * Variables which are not defined in the connected object but used
	 * don't change ther reference.
	 * It is an help method for the copy method. It dosn't update the
	 * structural information of the created Fib object.
	 *
	 * @param iObjectPoint the number of the connected object to copy;
	 * 	the standartvalue is 0 for coping the complet actual object
	 * @return the copy of the connected object or NULL if non such exists
	 */
	virtual cFibElement *copyInternal( const unsignedIntFib iObjectPoint=0 ) const;

	/**
	 * This method checks if the given variable is defined in the given
	 * direction from this Fib element.
	 * This is for intern use to get the correct data from
	 * isDefinedVariable() without pCallingFibElement.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @param pVariable the variable to check if it is defined
	 * @param direction the direction from this Fib element, in which the
	 * 	variable should be defined; default value is ED_POSITION so yust
	 * 	this Fib element will be checked
	 * @param pCallingFibElement the Fib element which called this method
	 * @return true if the variable is used, else false
	 */
	virtual bool isDefinedVariableInternal( const cFibVariable * pVariable,
		edDirection direction = ED_POSITION,
		const cFibElement * pCallingFibElement = NULL ) const;
	
	/**
	 * This method returns all variables defined in the given direction from
	 * this Fib element.
	 * This is for intern use to get the correct data from
	 * getDefinedVariables() without pCallingFibElement.
	 *
	 * @see cFibVariable
	 * @see getUsedVariables()
	 * @see isDefinedVariable()
	 * @param direction the direction from this Fib element, in which the
	 * 	variable should be used; default value is ED_POSITION so yust
	 * 	this Fib element will be checked
	 * @param pCallingFibElement the Fib element which called this method
	 * @return the matrix with all variables used in the given direction from
	 * 	this Fib element
	 */
	virtual list< cFibVariable* > getDefinedVariablesInternal(
		edDirection direction = ED_HIGHER,
		const cFibElement * pCallingFibElement = NULL );


	/**
	 * This method checks if the given Fib object is equal to this Fib
	 * object.
	 * Variables can be others, but must be defined and used in equivalent
	 * Fib elements.
	 *
	 * @param fibObject the Fib object to which this Fib object should be
	 * 	equal
	 * @param mapEqualRootObjects the root objects of this object that wher
	 * 	already checked as equal
	 * 	map entries:
	 * 		key: the root-element of this Fib object that was checked
	 * 		value: the to the key correspondending root-element of the
	 * 			fibObject that was checked and which is equal to the key
	 * 			root-element
	 * 	(it is empty if bCheckExternalObjects == false)
	 * @param mapEqualDefinedVariables the Fib elements that defines
	 * 	variables and are equal;
	 * 	map entries:
	 * 		key: the Fib element of this Fib object that was checked
	 * 		value: the to the key correspondending Fib element of the
	 * 			fibObject that was checked and which sets its defined
	 * 			variables to the same values as the key Fib element
	 * @param bCheckExternalObjects if true the external objects of
	 * 	cExtObject will be compared
	 * @return true if this Fib object is equal to the given Fib object,
	 * 	else false
	 */
	virtual bool equalInternal( const cFibElement & fibObject,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;

	/**
	 * This method checks if the given Fib element is equal to this Fib
	 * element.
	 * The subobjects are not compared, not even ther count is compared.
	 * Used variables can be others.
	 *
	 * @param fibElement the Fib element to which this Fib element should be
	 * 	equal
	 * @param mapEqualRootObjects the root objects of this object that wher
	 * 	already checked as equal
	 * 	map entries:
	 * 		key: the root-element of this Fib object that was checked
	 * 		value: the to the key correspondending root-element of the
	 * 			fibObject that was checked and which is equal to the key
	 * 			root-element
	 * 	(it is empty if bCheckExternalObjects == false)
	 * @param mapEqualDefinedVariables the Fib elements that defines
	 * 	variables and are equal;
	 * 	map entries:
	 * 		key: the Fib element of this Fib object that was checked
	 * 		value: the to the key correspondending Fib element of the
	 * 			fibObject that was checked and which sets its defined
	 * 			variables to the same values as the key Fib element
	 * @param bCheckExternalObjects if true the external objects of
	 * 	cExtObject will be compared
	 * @return true if this Fib element is equal to the given Fib element,
	 * 	else false
	 */
	virtual bool equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & matrixEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;


	/**
	 * This method checks if the given Fib element sets the variable to
	 * the same values as this Fib element.
	 *
	 * @param pVariableOwn a pointer to a defined variable in this Fib element,
	 * 	it is compared to the equivalent variable pVariable in the given
	 * 	Fib element fibElement
	 * @param fibElement the Fib element, to which this Fib element should be
	 * 	compared
	 * @param pVariable a pointer to a defined variable in the other 
	 * 	Fib element fibElement
	 * @param mapEqualRootObjects the root objects of this object that wher
	 * 	already checked as equal
	 * 	map entries:
	 * 		key: the root-element of this Fib object that was checked
	 * 		value: the to the key correspondending root-element of the
	 * 			fibObject that was checked and which is equal to the key
	 * 			root-element
	 * 	(it is empty if bCheckExternalObjects == false)
	 * @param mapEqualDefinedVariables the Fib elements that defines
	 * 	variables and are equal;
	 * 	map entries:
	 * 		key: the Fib element of this Fib object that was checked
	 * 		value: the to the key correspondending Fib element of the
	 * 			fibObject that was checked and which sets its defined
	 * 			variables to the same values as the key Fib element
	 * @param bCheckExternalObjects if true the external objects of
	 * 	cExtObject will be compared
	 * @return true if this Fib element sets the variable to the same
	 * 	values as this Fib element
	 */
	virtual bool equalValuesSetInternal( const cFibVariable * pVariableOwn,
		const cFibElement & fibElement,
		const cFibVariable * pVariable,
		map< const cRoot *, const cRoot * > & matrixEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;


};
}//namespace fib

#endif //___C_FIB_MATRIX_H__






