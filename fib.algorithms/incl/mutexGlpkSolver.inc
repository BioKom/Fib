/**
 * @file mutexGlpkSolver
 * file name: mutexGlpkSolver.inc
 * @author Betti Oesterholz
 * @date 26.09.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file provides definitions for the glpk mutex handling.
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
 * This file provides definitions for the glpk mutex handling.
 * It is needed because with the FEATURE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING
 * feature the glp library (extern package) linear solver will be used with
 * a mutex switch, so it can run in treads.
 * If the glp libary is tread save and FEATURE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING
 * deactivated this file is obsolete.
 *
 */
/*
History:
26.09.2012  Oesterholz  created
*/

#ifdef FEATURE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING
	//just define mutex once
	#ifndef DEFINE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING
		
		#define DEFINE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING
		
		#include <pthread.h>
		
		#ifdef WINDOWS
			static HANDLE mutexGlpkSolver = CreateMutex(
				NULL,	// default security attributes
				FALSE,	// initially not owned
				NULL);	// unnamed mutex
			
			//TODO? for close handle CloseHandle( mutexGlpkSolver );
			
		#else //WINDOWS
			static pthread_mutex_t mutexGlpkSolver = PTHREAD_MUTEX_INITIALIZER;
		#endif //WINDOWS
			
	#endif// DEFINE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING

#endif //FEATURE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING
