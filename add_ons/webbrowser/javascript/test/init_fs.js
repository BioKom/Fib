/**
 * file name: init_fs.js
 * @author Betti Oesterholz
 * @date 01.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains some basic emscripten functionality.
 *
 * Copyright (C) @c LGPL3 2013 Betti Oesterholz
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
 * This file contains some basic emscripten functionality.
 *
 */
/*
History:
01.06.2013  Oesterholz  created
*/



var Module = {
	/**
	 * Output the debugging information of C++ into an extra element with
	 * id "stdOutput" if existing.
	 */
	'print': function( textToOutput ){
		
		var outputElement = document.getElementById("stdOutput")
		
		if ( outputElement ){
			//output element with id "stdOutput" exists
			if ( "value" in outputElement ){
				outputElement.value = outputElement.value + textToOutput + "\n";
				return;
			}//else
			if ( "innerHTML" in outputElement ){
				outputElement.innerHTML = outputElement.innerHTML + textToOutput + "\n";
				return;
			}//else
		}//else
		console.log( "out>" + textToOutput );
	},
	/*'preRun' : function(){
		console.log('prerun');
		FS.createPath('/', 'home/user1', true, true);
	},*/
	'noInitialRun': true,
};//end var Module








