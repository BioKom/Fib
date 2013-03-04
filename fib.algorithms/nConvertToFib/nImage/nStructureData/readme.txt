nStructureData
==============

This folder contains the namespace for function and classes that are for
image structures (like same color circles or rectangles).


Workings
========

Convert to Fib object
---------------------

The interface iConvertImageStructureToFib (in incl/) is used by the
structure classed (which inherit cImageStructure) to define a method
(convertToFib()) to convert the structure data into a Fib (root) object.

For this often converting the basic area of the structure into external
objects (cExtObject) is needed. The interface iConvertAreaToExtObjects
(in nConvertToFib/incl/) defines a method for this. It is used for strategy
objects, which implement this method.
The class cUseConvertAreaToExtObjectsStrategy (in nConvertToFib/incl/)
defines the methods to switch betwean this strategies. So every class which
inherit cUseConvertAreaToExtObjectsStrategy can switch the strategy to
convert the basic area into Fib (external) objects.

