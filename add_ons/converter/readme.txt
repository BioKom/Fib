
Converter programs for Fib
===========================


convertFromFib
==============

This program is for converting multimedia objects in the Fib
multimedia formats into other multimedia formats.


call: convertFromFib FILE_MULTIMEDIADATA FILE_OUTPUT [MAX_EVALUE_TIME]

parameters:
	PATH_FIB_MULTIMEDIADATA
		the path to the to load Fib multimedia data
	FILE_OUTPUT
		The name of the file where the converted multimedia data would be
		stored to. The file ending will determine the output format.
	MAX_EVALUE_TIME
		if given and not 0, the maximal time in seconds for evaluing the
		Fib object;
		if not given or 0, no time limit for evaluing the Fib object is set

examples:
	> convertFromFib inputFib.xml output.png
	> convertFromFib inputFib.fib output.bmp


convertFibToFib
===============


This program is for converting Fib multimedia objects in one format
into a Fib object in another format.


call: convertFibToFib FILE_MULTIMEDIADATA [FILE_OUTPUT]

parameters:
	PATH_MULTIMEDIADATA
		The path to the to load Fib multimedia data.
	FILE_OUTPUT
		The name of the file where the Fib multimedia data would be
		stored to. If the file ending is ".xml" the data will be written
		in the Fib Xml format. If no parameter FILE_OUTPUT is given
		the Fib object will be stored in the Fib Xml format to the
		standard output.

examples:
	> convertFibToFib inputFib.xml outputFib.fib
	> convertFibToFib inputFib.fib outputFib.xml



convertToFib
============


This program is for converting multimedia objects in non Fib
multimedia formats into Fib objects.

Note: This program works at the time being just for RGB color pictures (without alpha).

call: convertToFib [PARAMETER] FILE_MULTIMEDIADATA [FILE_OUTPUT]
or call: convertToFib -h[elp]
	for help

parameters:
	PATH_MULTIMEDIADATA
		The path to the to load non Fib multimedia data
	FILE_OUTPUT
		The name of the file where the Fib multimedia data would be
		stored to. If the file ending is ".xml" the data will be written
		in the Fib Xml format. If no parameter FILE_OUTPUT is given
		the Fib object will be stored in the Fib Xml format to the
		standard output.
	PARAMETER
		Parameters for converting into the Fib multimedia format
	Possible parameters are:
		-mode=VALUE
			possible VALUE: simple, compress or reduce
			standard VALUE: compress
			(instead of the values, just the first letter of the values
			can be used)
			the compression mode
			if simple: the picture will be converted directly, without
				trying to reduce the data
			if compress: the multimedia data will be compressed, by
				building Fib under objects for areas with the same color
				and evaluating the background color (see option "-bg=")
			if reduce: the multimedia data will be compressed with
				reducing the data (higher compression rate as VALUE
				"compress"), by building Fib under objects for areas with
				similar color and evaluating the background color;
				some pixels won't have the correct color (see option "-bg="
				in combination with "-max_area_dif")
				possible options: 
					-max_area_diff=VALUE
						VALUE: a positive integer value
						the maximal difference of color values in an area (as
						the sum of the color vector element distances)
					-min_points=VALUE1 and -max_diff=VALUE2
						VALUE1 and VALUE2: positive integer value
						if an area with less than VALUE1 points exists and
						it layers beside an area with a color, wich has a less
						difference as VALUE2 to the color of the first area,
						both areas will be combined with the color of the
						second area (if the first area has more than one
						area as a neighbor, which fulfill VALUE2, the one with
						the minimum color distance is taken);
						the value of max_diff should be bigger than that of
						max_area_diff
					-addNeighbors or -addN
						add to the areas their neighbors and remove not needed areas;
						basicly this is an anti anti-aliasing
					-reduce_function_domains or -rfd
						reduce the bits to store the function (values)
					-replace_areas_with_points or -rpawp
						replace areas, which need more bits to store than
						there points, with there points
					-min_point_for_area=VALUE or -min_pfa=VALUE
						VALUE: the minimal number of points an area should
						have, to create an area object for it;
						if 0 the standard value will be taken
					-min_point_for_neighbor_area= or -min_pfna=
						all neighbor areas with less than this number of
						points, will be subsumed by the area
					-not_correct_missing_points or -ncmp
						don't correct points, which are missing in the created area Fib objects
					-max_error=VALUE
						VALUE: a positive integer value
						the maximal error for the area border polynomials to find
		-bg=VALUE
			possible VALUE: yes or no
			standard VALUE: yes
			if an background color should be set, if non exists;
			if no: no background color will be evaluated, if non exists;
		-correct-points or -cp
			if wrong points should be corrected, in the last compressing step
		-reduce_lists or -rl
			reduce the number of lists in the Fib object
		-minColDist=VALUE
			VALUE: a positive integer value
			The minimal color distance, to which reduce the original picture data.
		-expColDistFactor=VALUE
			VALUE: an floating point value, should be greater 1 (else: the
				functionality is not useful)
			The factor for reducing the color exponentially in the original picture data.
			(This is mainly for noise reduction.)
		-minFreeMemPc=VALUE (Unix only)
			VALUE: an floating point value, should be between (inclusive) 0
				(else: is set to 0) and 100 (else: is set to 100)
			The minimum per cent of free memory from all memory.
		-storeConvertedFibObjectTo=IMAGE_FILE_ENDING or -sFibTo=IMAGE_FILE_ENDING
			IMAGE_FILE_ENDING: the ending for the image file to store the
				created Fib object to (eg. bmp or png)
			If this parameter is given the created Fib object will be
			stored to an non fib image file. The type of the image file is
			given by the specified IMAGE_FILE_ENDING.

examples:
	> convertToFib input.png outputFib.xml
	> convertToFib input.bmp outputFib.fib
	> convertToFib -mode=r -rl -max_area_diff=4 -min_points=3 -max_diff=64 -rfd -rpawp input.jpg outputFib.fib

