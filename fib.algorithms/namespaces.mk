#
# @author Betti Oesterholz
# @date 15.06.2010
# @mail webmaster@BioKom.info
#
# System: make
#
# This is a makefile includefile for the namespace.
# It defines a variable NAMESPACES with the namespaces under
# fib.algorithms.
#
# Copyright (C) @c GPL3 2010 Betti Oesterholz
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#
##########################################################################
#
# History:
# 15.06.2010   Oesterholz   created
# 20.10.2010   Oesterholz   nCorrectFibObject added
# 08.12.2010   Oesterholz   nEvalueFibObject/nNeededUnderobjects added
# 07.01.2011   Oesterholz   nDn added
# 14.03.2011   Oesterholz   nAnalyse/nFibObject added
# 18.03.2011   Oesterholz   nCluster added
# 01.01.2013   Oesterholz   nConvertToFib* added
# 29.01.2013   Oesterholz   nFibDatabase added
# 14.04.2013   Oesterholz   nConvertToFib/nImage/nSearchForStructure and
#   nConvertToFib/nImage/nStructureData/nOperators added


#the sub -namespace variable
NAMESPACES:=./ nD1 nD2 nDn\
   nLinearEquation nLinearInequation\
   nReduceFibObject nTidyFibObjects nCorrectFibObject\
   nEvalueFibObject/nNeededUnderobjects nAnalyse/nFibObject\
   nCluster nFibDatabase\
   nConvertToFib nConvertToFib/nImage nConvertToFib/nImage/nStructureData\
   nConvertToFib/nImage/nStructureData/nConvertToFib\
   nConvertToFib/nImage/nSearchForStructure\
    nConvertToFib/nImage/nStructureData/nOperators

