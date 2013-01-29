/**
 * @class cTypeProperty
 * file name: cTypeProperty.cpp
 * @author Betti Oesterholz
 * @date 19.07.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents Fib -propertytyps.
 * Copyright (C) @c LGPL3 2009 Betti Oesterholz
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
 * This file contains the basisclass of all Fib -propertytyps.
 * Fib -propertytyps are typs of the elements in an Fib 
 * -propertyvector.
 *
 */
/*
History:
19.07.2009  Oesterholz  created
13.05.2010  Oesterholz  the ordering of bits for the compressed storing corrected
05.07.2010  Oesterholz  lowerTypeProperty() moved her from cEvaluePositionList
	and operator<() added
17.12.2010  Oesterholz  isOverwritenTyp() method added
18.12.2010  Oesterholz  isOverwriting() and static isEvalued() methods added
12.02.2012  Oesterholz  restoreXml*() without restoring domain possible
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
28.01.2013  Oesterholz  colorSW changed to colorGrascale
*/



#include "cTypeProperty.h"

#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"

#include "nBitStream.h"

using namespace fib;

	

/**
 * The constructor for dimension typs.
 *
 * @param uiPropertyType the number of the property this type
 *		represents;
 */
cTypeProperty::cTypeProperty( unsignedIntFib uiPropertyType,
		unsignedIntFib uiNumberOfDimensions ):
		uiPropertyType( uiPropertyType ),
		uiNumberOfDimensions( uiNumberOfDimensions ){
//nothing to do
}

/**
 * The copyconstructor for property typs.
 *
 * @param typeProperty the type property to copy
 */
cTypeProperty::cTypeProperty( const cTypeProperty &typeProperty ):
		uiPropertyType( typeProperty.getNumberOfProperty() ),
		uiNumberOfDimensions( typeProperty.uiNumberOfDimensions ){
//nothing to do
}


/**
 * The constructor for property typs.
 * This constructor constructs a propertytype, which is of the same type
 * as the given propertytype typeProperty, but which is adapted to the
 * given domain if possible. For that the number of dimension is
 * set to a value that is compatible to the vectordomain if possible.
 * (If not possible number of dimension is set to the value as in
 * typeProperty.)
 *
 * @param typeProperty the type property to copy
 * @param domain the domain to which the propertytype is to be adapted
 */
cTypeProperty::cTypeProperty( const cTypeProperty &typeProperty, const cDomain & domain ):
		uiPropertyType( typeProperty.getNumberOfProperty() ),
		uiNumberOfDimensions( typeProperty.uiNumberOfDimensions ){
	//adapt the number of dimensions if possible
	string szDomainType = domain.getType();

	if ( szDomainType.compare( 0, 12, "DomainVector" ) == 0 ){
		/*if the domain is an vector domain
		-> check the number of vectorelements for the properties which depend
		on the number of dimensions*/
		const cDomainVectorBasis * vectorDomain =
			((cDomainVectorBasis*)(&domain));
		
		unsignedIntFib uiNumberOfDomainVectorElements=
			vectorDomain->getNumberOfElements();
		
		switch ( (int)(uiPropertyType) ){
			case SOUND_POLARIZED:
			case ELECTRO_MAGNETIC:
				if ( 3 < uiNumberOfDomainVectorElements ){
					uiNumberOfDimensions = uiNumberOfDomainVectorElements - 3;
				}else{
					uiNumberOfDimensions = 0;
				}
			break;
			//?? TODO case SOUND_AMPLITUDE:
		//TODO for more types
		
			//default every number of dimensions is OK
		}
	}
}


/**
 * This method checks, if this element type is compatible with the
 * given domain. Just domains which are compadible can be used for the
 * elements of this type.
 *
 * @param domain the domain, which should be compatible
 * @return true if the given domain is compatible, else false
 */
bool cTypeProperty::isCompatible( const cDomain &domain ) const{

	string szDomainType = domain.getType();
	
	if ( szDomainType.compare( 0, 12, "DomainVector" ) == 0 ){
		/*if the domain is an vector domain 
		-> check the number of vectorelements for the properties with 
		standard domains*/
		cDomainVectorBasis * vectorDomain =
			((cDomainVectorBasis*)(&domain));
		
		unsignedIntFib uiNumberOfDomainVectorElements=
			vectorDomain->getNumberOfElements();
		
		for ( unsignedIntFib uiActualSubdomain = 1;
				uiActualSubdomain <= uiNumberOfDomainVectorElements;
				uiActualSubdomain++ ){
			
			const cDomain * pActualDomainElement = vectorDomain->
				getElementDomain( uiActualSubdomain );
			if ( pActualDomainElement == NULL ){
				//subdomain missing
				return false;
			}
			if ( ! pActualDomainElement->isScalar() ){
				//subdomain is not a scalar
				return false;
			}
		}//else domain compatible

		switch ( (int)(uiPropertyType) ){
			case COLOR_GRAYSCALE:
			case TRANSPARENCY:
			case LAYER:
			case SOUND_BARRIER:
			case SOUND_REFLECTED:
			case SOUND_DAMPING:
			case KELVIN:
				return (uiNumberOfDomainVectorElements==1);
			break;
			case COLOR_RGB:
				return (uiNumberOfDomainVectorElements==3);
			break;
			case SOUND:
				return (uiNumberOfDomainVectorElements==4);
			break;
			case SOUND_POLARIZED:
			case ELECTRO_MAGNETIC:
				return (uiNumberOfDomainVectorElements==3 + uiNumberOfDimensions);
			break;
			case CHECKSUM:
				if ( uiNumberOfDomainVectorElements == 3 ){
					//the vector domain have to consist of tree natuaral number domains
					cDomain * domainElement1 = vectorDomain->getElementDomain( 1 );
					cDomain * domainElement2 = vectorDomain->getElementDomain( 2 );
					cDomain * domainElement3 = vectorDomain->getElementDomain( 3 );
					string szDomainElementType1 = domainElement1->getType();
					string szDomainElementType2 = domainElement2->getType();
					string szDomainElementType3 = domainElement3->getType();
					
					if ( ( szDomainElementType1.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) &&
							( szDomainElementType2.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) &&
							( szDomainElementType3.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ){
						return true;
					}
				}//else
				return false;
			break;
			//?? TODO case SOUND_AMPLITUDE:
	//TODO for more types

			default:{
				//default every number of elements is OK
				return true;
			}
		}

	}//else no compatible domain
	return false;
}


/**
 * This Method returns a pointer to a new instance of the standart
 * domain for elements of this type.
 * You have to delete the returned object after usage.
 *
 * @return the standart domain for elements of this type
 */
cDomain * cTypeProperty::getStandardDomain( ) const{
	
	//construct the vectordomain for the type
	cDomainVector * vectorDomain = NULL;
	switch ( (int)(uiPropertyType) ){
		case COLOR_RGB:{
			//vector( 3, IntegerB(8), IntegerB(8) , IntegerB(8) )
			vector<cDomainSingle*> vecDomains( 3 );
			vecDomains[ 0 ] = new cDomainNaturalNumberBit( 8 );
			vecDomains[ 1 ] = new cDomainNaturalNumberBit( 8 );
			vecDomains[ 2 ] = new cDomainNaturalNumberBit( 8 );
			vectorDomain = new cDomainVector( vecDomains );
			delete vecDomains[ 0 ];
			delete vecDomains[ 1 ];
			delete vecDomains[ 2 ];
		}break;
		case COLOR_GRAYSCALE:
		case TRANSPARENCY:{
			//vector( 1, IntegerB(8) )
			vector<cDomainSingle*> vecDomains( 1 );
			vecDomains[ 0 ] = new cDomainNaturalNumberBit( 8 );
			vectorDomain = new cDomainVector( vecDomains );
			delete vecDomains[ 0 ];
		}break;
		case LAYER:{
			//vector( 1, IntegerB(4) )
			vector<cDomainSingle*> vecDomains( 1 );
			vecDomains[ 0 ] = new cDomainNaturalNumberBit( 4 );
			vectorDomain = new cDomainVector( vecDomains );
			delete vecDomains[ 0 ];
		}break;
		case SOUND:{
			//vector( 4, IntegerB(16), IntegerB(32), IntegerB(16) * 2^{-16}, IntegerB(32) * 2^{-8} )
			vector<cDomainSingle*> vecDomains( 4 );
			vecDomains[ 0 ] = new cDomainNaturalNumberBit( 16 );
			vecDomains[ 1 ] = new cDomainNaturalNumberBit( 32 );
			vecDomains[ 2 ] = new cDomainNaturalNumberBit( 16, 1.0/65536.0 );
			vecDomains[ 3 ] = new cDomainNaturalNumberBit( 32, 1.0/256.0 );
			vectorDomain = new cDomainVector( vecDomains );
			delete vecDomains[ 0 ];
			delete vecDomains[ 1 ];
			delete vecDomains[ 2 ];
			delete vecDomains[ 3 ];
		}break;
		case SOUND_POLARIZED:{
			//vector( 3 + Dim, IntegerB(16), IntegerB(32), IntegerB(16) * 2^{-16}, IntegerB(32) * 2^{-8}, [IntegerB(16) * 2^{-16}]^{Dim-1}  )
			
			vector<cDomainSingle*> vecDomains( 3 + uiNumberOfDimensions);
			vecDomains[ 0 ] = new cDomainNaturalNumberBit( 16 );
			vecDomains[ 1 ] = new cDomainNaturalNumberBit( 32 );
			vecDomains[ 2 ] = new cDomainNaturalNumberBit( 16, 1.0/65536.0 );
			vecDomains[ 3 ] = new cDomainNaturalNumberBit( 32, 1.0/256.0 );
			for ( unsignedIntFib actualDimension=1; 
					actualDimension<uiNumberOfDimensions;
					actualDimension++ ){
				vecDomains[ 3+actualDimension ]=
					new cDomainNaturalNumberBit( 16, 1.0/65536.0 );
			}
			
			vectorDomain = new cDomainVector( vecDomains );
		
			delete vecDomains[ 0 ];
			delete vecDomains[ 1 ];
			delete vecDomains[ 2 ];
			delete vecDomains[ 3 ];
			for ( unsignedIntFib actualDimension=1;
					actualDimension<uiNumberOfDimensions;
					actualDimension++ ){
				delete vecDomains[ 3+actualDimension ];
			}

		}break;

		case SOUND_BARRIER:{
			//vector( 1, IntegerB(16) )
			vector<cDomainSingle*> vecDomains( 1 );
			vecDomains[ 0 ] = new cDomainNaturalNumberBit( 16 );
			vectorDomain = new cDomainVector( vecDomains );
			delete vecDomains[ 0 ];
		}break;
		case SOUND_REFLECTED:
		case SOUND_DAMPING:{
			//vector( 1, IntegerB(16) * 2^{-16} )
			vector<cDomainSingle*> vecDomains( 1 );
			vecDomains[ 0 ] = new cDomainNaturalNumberBit( 16, 1.0/65536.0 );
			vectorDomain = new cDomainVector( vecDomains );
			delete vecDomains[ 0 ];
		}break;
		case KELVIN:{
			//vector( 1, IntegerB(16) * 2^{-4} )
			vector<cDomainSingle*> vecDomains( 1 );
			vecDomains[ 0 ] = new cDomainNaturalNumberBit( 16, 1.0/16.0 );
			vectorDomain = new cDomainVector( vecDomains );
			delete vecDomains[ 0 ];
		}break;
		case ELECTRO_MAGNETIC:{
			//vector( 3 + Dim, IntegerB(64), IntegerB(64) * 2^{-16}, IntegerB(16) * 2^{-16}, IntegerB(32) * 2^{-8}, [IntegerB(16) * 2^{-16}]^{Dim-1}  )
			vector<cDomainSingle*> vecDomains( 3 + uiNumberOfDimensions);
			vecDomains[ 0 ] = new cDomainNaturalNumberBit( 64 );
			vecDomains[ 1 ] = new cDomainNaturalNumberBit( 64, 1.0/65536.0 );
			vecDomains[ 2 ] = new cDomainNaturalNumberBit( 16, 1.0/65536.0 );
			vecDomains[ 3 ] = new cDomainNaturalNumberBit( 32, 1.0/256.0 );
			for ( unsignedIntFib actualDimension=1;
					actualDimension<uiNumberOfDimensions;
					actualDimension++ ){
				vecDomains[ 3+actualDimension ]=
					new cDomainNaturalNumberBit( 16, 1.0/65536.0 );
			}
			
			vectorDomain = new cDomainVector( vecDomains );
			delete vecDomains[ 0 ];
			delete vecDomains[ 1 ];
			delete vecDomains[ 2 ];
			delete vecDomains[ 3 ];
			for ( unsignedIntFib actualDimension=1;
					actualDimension<uiNumberOfDimensions;
					actualDimension++ ){
				delete vecDomains[ 3+actualDimension ];
			}

		}break;
		case CHECKSUM:{
			//vector( 3 + Dim, IntegerB(4), IntegerB(8) , IntegerB(8) )
			vector<cDomainSingle*> vecDomains( 3 );
			vecDomains[ 0 ] = new cDomainNaturalNumberBit( 4 );
			vecDomains[ 1 ] = new cDomainNaturalNumberBit( 8 );
			vecDomains[ 2 ] = new cDomainNaturalNumberBit( 8 );
			
			vectorDomain = new cDomainVector( vecDomains );
			delete vecDomains[ 0 ];
			delete vecDomains[ 1 ];
			delete vecDomains[ 2 ];
		}break;

//?? TODO case SOUND_AMPLITUDE:
//TODO for more types

	
	
		default:{
			//default return standard domain
			vector<cDomainSingle*> vecDomains( 1 );
			vecDomains[ 0 ] = new cDomainNaturalNumberBit( 16 );
			vectorDomain = new cDomainVector( vecDomains );
			delete vecDomains[ 0 ];
		}
	}

	return vectorDomain;
}


/**
 * This Function returns for the type of the element an number.
 * The values, which are returned, mean:
 * 	- 1: cTypeDimension
 * 	- 2: cTypeUnderArea
 * 	- 3: cTypeUnderFunction
 * 	- 5: cTypeInVar
 * 	- 6: cTypeProperty
 * 	- 10: cTypeVariable
 * 	- 11: cTypeComments
 * 	- 12: cTypeExtObject
 * 	- 13: cTypeExtSubobject
 * 	- 14: cTypeFibSet
 * 	- 15: cTypeFibMatrix
 * 	- 16: cTypeExtObjectInput
 *
 * @return for the type of the element an number
 */
unsignedIntFib cTypeProperty::getType() const{
	return (unsignedIntFib)(6);
}


/**
 * @return the type of property this type represents;
 */
unsignedIntFib cTypeProperty::getNumberOfProperty() const{
	return uiPropertyType;
}


/**
 * @return the name of property this type represents
 */
string cTypeProperty::getNameOfProperty() const{

	switch ( (int)( getNumberOfProperty() ) ){
		case NONE:
			return "none";
		case COLOR_RGB:
			return "colorRGB";
		case COLOR_GRAYSCALE:
			return "colorGrayscale";
		case LAYER:
			return "layer";
		case TRANSPARENCY:
			return "transparency";
		case SOUND:
			return "sound";
		case SOUND_POLARIZED:
			return "soundPolarized";
		case SOUND_AMPLITUDE:
			return "soundAmplitude";
		case SOUND_BARRIER:
			return "soundBarrier";
		case SOUND_REFLECTED:
			return "soundReflected";
		case SOUND_DAMPING:
			return "soundDamping";
		case KELVIN:
			return "kelvin";
		case ELECTRO_MAGNETIC:
			return "electroMagnetic";
		case CHECKSUM:
			return "checksum";
//TODO for more typs

		default:{
			unsigned int uiMapping = getNumberOfProperty();
			char szDirectionBuffer[ 32 ];
			sprintf( szDirectionBuffer, "%u", uiMapping );
			return string( szDirectionBuffer );
		}
	}//never reached
	
	return "";
}


/**
 * @see getNameOfProperty()
 * @param szPropertyName a name for a property
 * @return the number the name szPropertyName represents
 */
unsignedIntFib cTypeProperty::getNumberForPropertyName( const string szPropertyName ){
	
	if ( szPropertyName == "none" ){
		return NONE;
	}
	if ( szPropertyName == "colorRGB" ){
		return COLOR_RGB;
	}
	if ( szPropertyName == "colorGrayscale" ){
		return COLOR_GRAYSCALE;
	}
	if ( szPropertyName == "layer" ){
		return LAYER;
	}
	if ( szPropertyName == "transparency" ){
		return TRANSPARENCY;
	}
	if ( szPropertyName == "sound" ){
		return SOUND;
	}
	if ( szPropertyName == "soundPolarized" ){
		return SOUND_POLARIZED;
	}
	if ( szPropertyName == "soundAmplitude" ){
		return SOUND_AMPLITUDE;
	}
	if ( szPropertyName == "soundBarrier" ){
		return SOUND_BARRIER;
	}
	if ( szPropertyName == "soundReflected" ){
		return SOUND_REFLECTED;
	}
	if ( szPropertyName == "soundDamping" ){
		return SOUND_DAMPING;
	}
	if ( szPropertyName == "kelvin" ){
		return KELVIN;
	}
	if ( szPropertyName == "electroMagnetic" ){
		return ELECTRO_MAGNETIC;
	}
	if ( szPropertyName == "checksum" ){
		return CHECKSUM;
	}

//TODO for more typs

	long lValue = 0;
	const int iReadValues = sscanf ( szPropertyName.c_str() , "%ld", & lValue );
	if ( iReadValues != 1){
		return 0;
	}
	return (unsignedIntFib)lValue;


}



/**
 * @return The SI unit for the dimension this type represents;
 * 	possible values are:
 * 		- "": for none
 * 		- "m": for meter
 * 		- "s": for secound
 * 		...
 *			TODO
 */
vector<string> cTypeProperty::getUnit() const{
	//construct the property vector units for the type
	
	vector<string> vecUnits;

	switch ( (int)(uiPropertyType) ){
		case COLOR_RGB:
			//vector( 3, IntegerB(8), IntegerB(8) ,$ $ IntegerB(8) )
			vecUnits.push_back( "red" );
			vecUnits.push_back( "green" );
			vecUnits.push_back( "blue" );
		break;
		case COLOR_GRAYSCALE:
			//vector( 1, IntegerB(8) )
			vecUnits.push_back( "white" );
		break;
		case TRANSPARENCY:
			//vector( 1, IntegerB(8) )
			vecUnits.push_back( "fraction" );
		break;
		case LAYER:
			//vector( 1, IntegerB(4) )
			vecUnits.push_back( "layer" );
		break;
		case SOUND:
			//vector( 4, IntegerB(16), IntegerB(32), IntegerB(16) * 2^{-16}, IntegerB(32) * 2^{-8} )
			vecUnits.push_back( "1/s" );
			vecUnits.push_back( "Pa" );
			vecUnits.push_back( "radian" );
			vecUnits.push_back( "s" );
		break;
		case SOUND_POLARIZED:
			//vector( 3 + Dim, IntegerB(16), IntegerB(32), IntegerB(16) * 2^{-16}, IntegerB(32) * 2^{-8}, [IntegerB(16) * 2^{-16}]^{Dim-1}  )
			vecUnits.push_back( "1/s" );
			vecUnits.push_back( "Pa" );
			vecUnits.push_back( "radian" );
			vecUnits.push_back( "s" );
			for ( unsignedIntFib actualDimension=1; 
					actualDimension<uiNumberOfDimensions;
					actualDimension++ ){
				vecUnits.push_back( "radian" );
			}
		break;
		case SOUND_BARRIER:
			//vector( 1, IntegerB(16) )
			vecUnits.push_back( "m/s" );
		break;
		case SOUND_REFLECTED:
		case SOUND_DAMPING:
			//vector( 1, IntegerB(16) * 2^{-16} )
			vecUnits.push_back( "fraction" );
		break;
		case KELVIN:
			//vector( 1, IntegerB(16) * 2^{-4} )
			vecUnits.push_back( "K" );

		break;
		case ELECTRO_MAGNETIC:
			//vector( 3 + Dim, IntegerB(64), IntegerB(64) * 2^{-16}, IntegerB(16) * 2^{-16}, IntegerB(32) * 2^{-8}, [IntegerB(16) * 2^{-16}]^{Dim-1}  )
			vecUnits.push_back( "1/s" );
			vecUnits.push_back( "cd" );
			vecUnits.push_back( "radian" );
			vecUnits.push_back( "s" );
			for ( unsignedIntFib actualDimension = 1;
					actualDimension < uiNumberOfDimensions;
					actualDimension++ ){
				vecUnits.push_back( "radian" );
			}
		break;
		case CHECKSUM:
			vecUnits.push_back( "type" );
			vecUnits.push_back( "bits" );
			vecUnits.push_back( "bits" );
		break;

	//?? TODO case SOUND_AMPLITUDE:
//TODO for more typs
	
	
		default:
			//default return standard empty unit
			vecUnits.push_back( "" );
	}

	return vecUnits;

}


/**
 * @return The typs of the properties the properties of this type overwrites
 */
list<cTypeProperty> cTypeProperty::getOverwritenTyps() const{

	//construct the typelist of types properties of this type oferwrites
	list<cTypeProperty> liPropertyTypes;

	switch ( (int)(uiPropertyType) ){
		case COLOR_RGB:
		case COLOR_GRAYSCALE:
			//overwrite colors
			liPropertyTypes.push_back( cTypeProperty( COLOR_RGB ) );
			liPropertyTypes.push_back( cTypeProperty( COLOR_GRAYSCALE ) );
		break;
		case TRANSPARENCY:
			liPropertyTypes.push_back( cTypeProperty( TRANSPARENCY ) );
		break;
		case LAYER:
			liPropertyTypes.push_back( cTypeProperty( LAYER ) );
		break;
		case SOUND_BARRIER:
			liPropertyTypes.push_back( cTypeProperty( SOUND_BARRIER ) );
		break;
		case SOUND_REFLECTED:
			liPropertyTypes.push_back( cTypeProperty( SOUND_REFLECTED ) );
		break;
		case SOUND_DAMPING:
			liPropertyTypes.push_back( cTypeProperty( SOUND_DAMPING ) );
		break;
		case KELVIN:
			liPropertyTypes.push_back( cTypeProperty( KELVIN ) );
		break;
		case SOUND:
		case SOUND_POLARIZED:
		case SOUND_AMPLITUDE:
		case ELECTRO_MAGNETIC:
		//overwrite nothing
		break;
		case CHECKSUM:
			liPropertyTypes.push_back( cTypeProperty( CHECKSUM ) );
		break;

//TODO for more typs
	
	
	}

	return liPropertyTypes;
}


/**
 * This method checks if the given type is overwritten by this type.
 *
 * @param typeToCheck the type to check, if it is overwritten
 * @return true if typeToCheck is overwritten by this type, else false
 */
bool cTypeProperty::isOverwritenTyp( const cTypeProperty & typeToCheck ) const{

	switch ( (int)(uiPropertyType) ){
		case COLOR_RGB:
		case COLOR_GRAYSCALE:
			//overwrite colors
			if ( ( typeToCheck.uiPropertyType == COLOR_RGB ) ||
					( typeToCheck.uiPropertyType ==  COLOR_GRAYSCALE ) ){
				return true;
			}
		break;
		//properties which just overwrites properties of the same type
		case TRANSPARENCY:
		case LAYER:
		case SOUND_BARRIER:
		case SOUND_REFLECTED:
		case SOUND_DAMPING:
		case KELVIN:
		case CHECKSUM:
			if ( typeToCheck.uiPropertyType == uiPropertyType ){
				return true;
			}
		break;
/*
		case SOUND:
		case SOUND_POLARIZED:
		case SOUND_AMPLITUDE:
		case ELECTRO_MAGNETIC:
		//overwrite nothing
*/
//TODO for more typs
	
	}
	//the given type is not overwritten
	return false;
}


/**
 * This method checks if the given type is overwritten by this type.
 *
 * @see uiPropertyType
 * @param uiTypeToCheck the number of the type to check, if it is overwritten
 * @return true if uiTypeToCheck is overwritten by this type, else false
 */
bool cTypeProperty::isOverwritenTyp( const unsignedIntFib & uiTypeToCheck ) const{

	switch ( (int)(uiPropertyType) ){
		case COLOR_RGB:
		case COLOR_GRAYSCALE:
			//overwrite colors
			if ( ( uiTypeToCheck == COLOR_RGB ) ||
					( uiTypeToCheck ==  COLOR_GRAYSCALE ) ){
				return true;
			}
		break;
		//properties which just overwrites properties of the same type
		case TRANSPARENCY:
		case LAYER:
		case SOUND_BARRIER:
		case SOUND_REFLECTED:
		case SOUND_DAMPING:
		case KELVIN:
		case CHECKSUM:
			if (uiTypeToCheck == uiPropertyType ){
				return true;
			}
		break;
/*
		case SOUND:
		case SOUND_POLARIZED:
		case SOUND_AMPLITUDE:
		case ELECTRO_MAGNETIC:
		//overwrite nothing
*/
//TODO for more typs
	
	}
	//the given type is not overwritten
	return false;
}


/**
 * @return if this type overwrites typs true, else false
 */
bool cTypeProperty::isOverwriting() const{

	return isOverwriting( uiPropertyType );
}


/**
 * This function checks if the given type overwrites some typs.
 *
 * @param uiTypeToCheck the number of the type to check, if it overwrittes
 * 	other typs
 * @return if the given type overwrites typs true, else false
 */
bool cTypeProperty::isOverwriting( const unsignedIntFib & uiTypeToCheck ){

	if ( (uiTypeToCheck == COLOR_RGB) ||
			(uiTypeToCheck == COLOR_GRAYSCALE) ||
			(uiTypeToCheck == TRANSPARENCY) ||
			(uiTypeToCheck == LAYER) ||
			(uiTypeToCheck == SOUND_BARRIER) ||
			(uiTypeToCheck == SOUND_REFLECTED) ||
			(uiTypeToCheck == SOUND_DAMPING) ||
			(uiTypeToCheck == KELVIN) ||
			(uiTypeToCheck == CHECKSUM) ){

		return true;
	}/*else SOUND, SOUND_POLARIZED, SOUND_AMPLITUDE, ELECTRO_MAGNETIC
		overwrite nothing
*/
//TODO for more typs

	//the given type is not overwriting
	return false;

}


/**
 * @return this method returnes true, if the property of this type is
 * 	for evaluating a fib -object, else false is returned 
 */
bool cTypeProperty::isEvalued() const{

	return isEvalued( uiPropertyType );
}


/**
 * This function checks if the given type is evalued.
 *
 * @param uiTypeToCheck the number of the type to check, if it is evalued
 * @return this method returnes true, if the property of the given type is
 * 	for evaluating a fib -object, else false is returned
 */
bool cTypeProperty::isEvalued( const unsignedIntFib & uiTypeToCheck ){

	if ( ( uiTypeToCheck == NONE) ||
			( uiTypeToCheck == CHECKSUM) ){
		return false;
	}//else the property is evalued
	return true;
}


/**
 * This Method checks if the given type is equal to this type.
 *
 * @return true if the given type is equal to this type, else false
 */
bool cTypeProperty::operator==( const cTypeElement &typeElement ) const{
	return (getType() == typeElement.getType()) &&
		(getNumberOfProperty() ==
			((cTypeProperty*)(&typeElement))->getNumberOfProperty());
}

/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cTypeProperty * cTypeProperty::clone() const{
	return new cTypeProperty( *this );
}


/**
 * This method evaluades the size of the typeelement in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the typeelement in bits in the compressed form
 */
unsignedLongFib cTypeProperty::getCompressedSize() const{
	if ( uiPropertyType < 256 ){
		//short property type / number -> 8 bit parameter is enought
		return 8 + 8;
	}//else
	return 8 + 64;
}


/**
 * This method stores this type in the XML -format into the
 * given stream.
 *
 * @param ostream the stream where domains should be stored to
 * @param domain the domain which should be stored to this type;
 * 	if a Nullpointer NULL (the standardvalue) is given, no domain
 * 	will be stored to this type
 * @return true if this type are stored, else false
 */
bool cTypeProperty::storeXml( ostream & ostream,
		const cDomain * domain ) const{
	
	ostream<<"<property name=\""<< getNameOfProperty()<<"\" ";
	
	//if given write the domain to the stream
	if ( domain != NULL ){
		
		ostream<<">"<<endl;

		bool bDomainStored = domain->storeXml( ostream );
		if ( ! bDomainStored ){
			return false;
		}
		ostream<<"</property>"<<endl;
	}else{
		ostream<<"/>"<<endl;
	}

	return true;
}


/**
 * This method restores a type with a domain in the XML -format from an
 * TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node wher the type is stored in
 * @param outStatus an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 * @param bRestoreDomain if true a domain is to be asumed in the type
 * 	element and it will be restored, else no domain will be restores
 * @return a pointer to the restored domain, or NULL if it couldn't be restored
 */
cDomain * cTypeProperty::restoreXmlWithDomain( const TiXmlElement * pXmlElement,
		intFib & outStatus, const bool bRestoreDomain ){
	
	//check the element type
	if ( pXmlElement == NULL ){
		//Error: noting to restore
		outStatus = -1;
		return NULL;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "property" ){
		//Error: wrong element type to restore
		outStatus = -2;
		return NULL;
	}
	
	uiPropertyType = 0;
	const char * szXmlName = pXmlElement->Attribute( "name");
	if ( szXmlName != NULL ){
		uiPropertyType = getNumberForPropertyName( string( szXmlName ) );
	}else{
		//Warning: count of dimensions missing
		outStatus = 2;
	}

	if ( bRestoreDomain ){
		//restore the domain
		const TiXmlElement * pXmlElementType = NULL;
		if ( pXmlElement->FirstChild() ){
			
			pXmlElementType = pXmlElement->FirstChildElement();
		}
		const TiXmlElement * pXmlElementDomain = NULL;
		for( ; pXmlElementType != NULL;
				pXmlElementType = pXmlElementType->NextSiblingElement() ){
			
			if ( pXmlElementDomain == NULL ){
				pXmlElementDomain = pXmlElementType;
			}else{//Warning: more than one domain to restore
				outStatus = 2;
				break;
			}
		}
		//restore the domain
		cDomain * pRestoredDomain = NULL;
		if ( pXmlElementDomain ){
			int iDomainRestoreReturn = 0;
			pRestoredDomain = cDomain::restoreXml( pXmlElementDomain, iDomainRestoreReturn );
			
			if ( iDomainRestoreReturn != 0 ){
				outStatus = iDomainRestoreReturn;
			}
			if ( pRestoredDomain != NULL ){
				//if needed evalue uiNumberOfDimensions
				uiNumberOfDimensions = 2;
				string szDomainType = pRestoredDomain->getType();
			
				if ( szDomainType.compare( 0, 12, "DomainVector" ) == 0 ){
					/*if the domain is an vector domain
					-> check the number of vectorelements for the properties which
					depend on the number of dimensions*/
					cDomainVectorBasis * vectorDomain =
						((cDomainVectorBasis*)(pRestoredDomain));
					
					unsignedIntFib uiNumberOfDomainVectorElements=
						vectorDomain->getNumberOfElements();
					
					switch ( (int)(uiPropertyType) ){
						case SOUND_POLARIZED:
						case ELECTRO_MAGNETIC:
							uiNumberOfDimensions = uiNumberOfDomainVectorElements - 3;
						break;
						//?? TODO case SOUND_AMPLITUDE:
					//TODO for more types
					
						//default every number of dimensions is OK
					}
				}
			}
		}else{
			outStatus = 2;
		}
		return pRestoredDomain;
	}//end if restore domain + else no domain to return
	return NULL;
}


/**
 * This method stores this typeelement in the compressed fib -format
 * into the given stream.
 * It is needed because the stream can yust store byts but the size of
 * fib -elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the fib -elements.
 *
 * @see cFibElement::store
 * @param stream the stream where this typeelement should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if the typeelement is stored, else false
 */
bool cTypeProperty::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	if ( uiRestBitPosition >= 8){
		//error in input
		return false;
	}

	char cPropertyName = 0x20; //the name "property"
	if ( uiPropertyType < 256 ){
		//short property type / number -> 8 bit parameter is enought
		cPropertyName = cPropertyName | 0x02;
		unsigned char cParameter = uiPropertyType;
		
		
		bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cPropertyName, 8 );
		if ( ! bNameStored ){
			return false;
		}
		bool bParameterStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			(unsigned long)(cParameter), 8 );
		if ( ! bParameterStored ){
			return false;
		}

	}else{
		//long property type / number -> 64 bit parameter
		cPropertyName = cPropertyName | 0x04;
		unsigned long long ulParameter = uiPropertyType;
		
		bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cPropertyName, 8 );
		if ( ! bNameStored ){
			return false;
		}
		bool bParameterStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			ulParameter, 64 );
		if ( ! bParameterStored ){
			return false;
		}
	}
	return true;
}


/**
 * This method restores a type from a bitstream, wher it is
 * stored in the compressed fib -format.
 *
 * @see store
 * @param iBitStream the stream where the type is stored in,
 * 	because the stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @return an integervalue with the errorvalue
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 */
intFib cTypeProperty::restore( cReadBits & iBitStream ){
	
	if ( ! iBitStream.getStream()->good() ){
		//Error: nothing to load
		return -1;
	}

	//read the typename
	char cTypeName = 0x00;
	unsigned int uiBitsRead = iBitStream.readBits( &cTypeName, 8 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 8 ){
		return -2;
	}
	if ( (cTypeName & 0xF8) != 0x20 ){
		//warning: wrong type
		return -2;
	}
	if ( (cTypeName & 0x06) == 0x02 ){
		//short property type / number -> 8 bit parameter is enought
		unsignedIntFib uiPropertyTypeRestored = 0x00;
		uiBitsRead = iBitStream.readBits( uiPropertyTypeRestored, 8 );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != 8 ){
			return -2;
		}
		uiPropertyType = uiPropertyTypeRestored;
	
	}else{
		//long property type / number -> 64 bit parameter
		unsignedLongFib ulPropertyTypeRestored = 0;
		uiBitsRead = iBitStream.readBits( ulPropertyTypeRestored, 64 );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != 64 ){
			return -2;
		}
		uiPropertyType = ulPropertyTypeRestored;
	}
	return 0;
}



/**
 * This function compares this property type with the given property type.
 * Propertytype is lower, if it's number is lower than the number of the 
 * other Propertytype.
 *
 * @param typeProperty a pointer to the second propertytype to compare
 * @return true if this propertytype is lower than that the given
 * 	of typeProperty, else false
 */
bool cTypeProperty::operator<( const cTypeProperty & typeProperty ) const{

	return lowerTypeProperty( *this, typeProperty );
}


/**
 * This function compares two cTypeProperty.
 * Propertytype is lower, if it's number is lower than the number of the 
 * other Propertytype.
 *
 * @param pTypeProperty1 a pointer to the first propertytype to compare
 * @param pTypeProperty2 a pointer to the second propertytype to compare
 * @return true if the propertytype pTypeProperty1 is lower than that
 * 	of pTypeProperty2, else false
 */
bool cTypeProperty::lowerTypeProperty( const cTypeProperty & pTypeProperty1,
		const cTypeProperty & pTypeProperty2 ){
	
	if ( pTypeProperty1.getNumberOfProperty() < pTypeProperty2.getNumberOfProperty() ){
		return true;
	}
	return false;
}


/**
 * This function compares two cTypeProperty.
 * Propertytype is lower, if it's number is lower than the number of the 
 * other Propertytype.
 *
 * @param pTypeProperty1 a pointer to the first propertytype to compare
 * @param pTypeProperty2 a pointer to the second propertytype to compare
 * @return true if the propertytype pTypeProperty1 is lower than that
 * 	of pTypeProperty2, else false
 */
bool cTypeProperty::lowerTypeProperty( const cTypeProperty * pTypeProperty1,
		const cTypeProperty * pTypeProperty2 ){

	return lowerTypeProperty( *pTypeProperty1, *pTypeProperty2 );
}






