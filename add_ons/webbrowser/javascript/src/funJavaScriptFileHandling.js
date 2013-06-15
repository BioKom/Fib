
//TODO check

/**
 * file name: funJavaScriptFileHandling.js
 * @author Betti Oesterholz
 * @date 15.05.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements some functions to access the file javascript.
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
 * This file implements some functions to access the file javascript.
 *
 */
/*
History:
15.05.2013  Oesterholz  created
*/


/**
 * This function opens the file form the given path and retuns its data.
 *
 * @param zsPath the path of the file to open
 * @return the data of the file
 */
mergeInto( LibraryManager.library, {
		jsFunOpenFileStream: function( zsPath ) {
			var szJsPath = Pointer_stringify( zsPath );
			//alert( "jsFunOpenFileStream( " + szJsPath +" ) called");
			//console.log("jsFunOpenFileStream( " + szJsPath +" ) called");
			
			var bFileCouldBeRead = false;
			var bErrorOccurred = false;
			
			//console.log("   http = new XMLHttpRequest();");
			var http = new XMLHttpRequest();
			//console.log("   http.open('GET', szJsPath=" + szJsPath + ", false);");
			http.open('GET', szJsPath, false);
			try{
				http.send( null );
			}catch ( e ){
				//console.log("   Error was trown by http.send( null )" + e + ";");
				bErrorOccurred = true;
			}
			//console.log("   http.open(); returned readyState=" + http.readyState + " status : " + http.status );
			if ( ( http.readyState == 4 ) && ( http.status == 200 ) &&
					( ! bErrorOccurred ) ){
				console.log( "   the file " + szJsPath +" was read");
				//console.log( "   data:" + http.responseText );
				
				var pFileData =
						allocate( intArrayFromString( http.responseText ), 'i8', ALLOC_STACK );
				return pFileData;
			}//else{
			/*if ( ( http.readyState != 4 ) || ( http.status != 200 ) ){
				alert( "   the file " + szJsPath +" could not be read (state " +
				http.readyState + " status " + http.status +")");
				return "";
			}*/
			var bInternetExplorer = ( typeof window.ActiveXObject != 'undefined' );
			bErrorOccurred = false;

			if ( bInternetExplorer ) {
				var xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
				xmlDoc.async = false;
				while( xmlDoc.readyState != 4 ) {};
				try{
					xmlDoc.load( szJsPath );
				}catch ( e ){
					//console.log("   Error was trown by xmlDoc.load( szJsPath=" + szJsPath + " )" + e + ";");
					bErrorOccurred = true;
				}
				if ( ( ! bErrorOccurred ) && xmlDoc.text ){
					var pFileData =
						allocate( intArrayFromString( xmlDoc.text ), 'i8', ALLOC_STACK );
					//console.log( "   the file " + szJsPath +" was read");
					return pFileData;
				}//else error occurred
			}else{
				var xmlDoc = document.implementation.createDocument( "", "", null );
				
				//xmlDoc.onload = readXML;
				try{
					xmlDoc.load( szJsPath );
				}catch ( e ){
					//console.log("   Error was trown by xmlDoc.load( szJsPath=" + szJsPath + " )" + e + ";");
					bErrorOccurred = true;
				}
				//wait till document is loaded
				if ( ! bErrorOccurred ){
					//wait maximal 3 seconds
					var endTime = new Date().getTime() + 500;//milliseconds
					var actualTime = new Date().getTime();
					while ( xmlDoc.readyState != "complete" ){
						/*console.log("   waiting for xmlDoc.load(); returned readyState=" +
							xmlDoc.readyState + "; status : " + xmlDoc.status );*/
						actualTime = new Date().getTime();
						if ( endTime < actualTime ){
							//maximal wait time exceeded
							break;
						}
					}//complete ==? 4
					
					if ( ( xmlDoc.readyState == "complete" ) && xmlDoc.text ){
						var pFileData =
							allocate( intArrayFromString( xmlDoc.text ), 'i8', ALLOC_STACK );
						//console.log( "   the file " + szJsPath +" was read");
						return pFileData;
					}
				}//else error occurred
			}
			//TODO? use hidden iFrames
			
			
			var pEmptyData =
					allocate( intArrayFromString( "" ), 'i8', ALLOC_STACK );
			return pEmptyData;
		}
});


/**
 * This function checks if the given path is a existing folder.
 *
 * @param zsPath the path to check
 * @return 0 if the path is a existing folder, else 1
 */
mergeInto( LibraryManager.library, {
		jsFunCheckIfFolderExists: function( zsFolder ) {
			var zsJsFolder = Pointer_stringify( zsFolder );
			//TODO
			//alert( "jsFunCheckIfFolderExists( " + zsJsFolder +" ) called");
			console.log("jsFunCheckIfFolderExists( " + zsJsFolder +" ) called");
			//document.write( "jsFunCheckIfFolderExists( " + zsJsFolder +" ) called" );
			
			/*TODO dosn't work:
			var fileSystem;
			set fileSystem = Server.CreateObject("Scripting.FileSystemObject");
			if ( fs.FolderExists( zsJsFolder ) = true ) then
				alert( "   the folder exists");
			else
				alert( "   the folder do not exists");
			end if
			set fileSystem = nothing;
			*/
			return 1;
		}
});


/**
 * This function checks if the given path is a existing file.
 *
 * @param zsPath the path to check
 * @return 0 if the path is a existing file, else 1
 */
mergeInto( LibraryManager.library, {
		jsFunCheckIfFileExists: function( szPath ) {
			var szJsPath = Pointer_stringify( szPath );
			
			//console.log("jsFunCheckIfFileExists( " + szJsPath +" ) called");
			
			var bFileCouldBeRead = false;
			var bErrorOccurred = false;
			
			//console.log("   http = new XMLHttpRequest();");
			var http = new XMLHttpRequest();
			//console.log("   http.open('HEAD', szJsPath=" + szJsPath + ", false);");
			http.open('HEAD', szJsPath, false);
			try{
				http.send( null );
			}catch ( e ){
				//console.log("   Error was trown by http.send( null )=" + e + ";");
				bErrorOccurred = true;
			}
			//console.log("   http.open(); returned readyState=" + http.readyState + "; status : " + http.status );
			/*while ( http.readyState != 4 ){
				//TODO do nothing
			}*/
			if ( ( http.readyState == 4 ) && ( http.status == 200 ) &&
					( ! bErrorOccurred ) ){
				//console.log( "   the file " + szJsPath +" exists" );
				return 0;
			}//else{
			/*if ( ( http.readyState != 4 ) || ( http.status != 200 ) ){
				alert( "   the file " + szJsPath +" could not be read (state " +
				http.readyState + " status " + http.status +")");
				return "";
			}*/
			var bInternetExplorer = ( typeof window.ActiveXObject != 'undefined' );
			
			bErrorOccurred = false;
			if ( bInternetExplorer ) {
				var xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
				//console.log( "   xmlDoc = new ActiveXObject(\"Microsoft.XMLDOM\");" );
				xmlDoc.async = false;
				while( xmlDoc.readyState != 4 ) {};
				try{
					xmlDoc.load( szJsPath );
				}catch ( e ){
					//console.log("   Error was trown by xmlDoc.load( szJsPath=" + szJsPath + " )=" + e + ";");
					bErrorOccurred = true;
				}
				
				if ( xmlDoc.text && ( ! bErrorOccurred ) ){
					//console.log( "   the file " + szJsPath +" exists" );
					return 0;
				}
			}else{
				var xmlDoc = document.implementation.createDocument( "", "", null );
				//console.log( "   xmlDoc = document.implementation.createDocument(...);" );
				
				//xmlDoc.onload = readXML;
				try{
					//console.log( "   xmlDoc.load( szJsPath=" + szJsPath + " );" );
					xmlDoc.load( szJsPath );
				}catch ( e ){
					//console.log("   Error was trown by xmlDoc.load( szJsPath=" + szJsPath + " )=" + e + ";");
					bErrorOccurred = true;
				}
				if ( ! bErrorOccurred ){
					//wait till document is loaded
					//wait maximal 3 seconds
					var endTime = new Date().getTime() + 3000;//milliseconds
					var actualTime = new Date().getTime();
					while ( xmlDoc.readyState != "complete" ){
						/*console.log("   waiting for xmlDoc.load(); returned readyState=" +
							xmlDoc.readyState + "; status : " + xmlDoc.status );*/
						actualTime = new Date().getTime();
						if ( endTime < actualTime ){
							//maximal wait time exceeded
							break;
						}
					}//complete ==? 4
					
					if ( ( xmlDoc.readyState == "complete" ) && xmlDoc.text ){
						//console.log( "   the file " + szJsPath +" exists" );
						//console.log( "   text: \"" + xmlDoc.text + "\") );
						return 0;
					}
				}//else error occurred
			}
			
			//console.log( "   the file " + szJsPath +" dos not exists" );
			return 1;
		}
});









