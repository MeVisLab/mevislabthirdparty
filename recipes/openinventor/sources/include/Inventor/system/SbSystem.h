/*
 *
 *  Copyright (C) 2006 MeVis Research GmbH  All Rights Reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: MeVis, Center for Medical Diagnostic Systems and
 *  Visualization GmbH, Universitätsallee 29, D-28359 Bremen, GERMANY, or:
 *
 *  http://www.mevis.de
 *
 */

/*
 * Copyright (C) 2006   MeVis Research GmbH
 *
 _______________________________________________________________________
 _______________  M E V I S   R E S E A R C H   G M B H  _______________
 |
 |   Description:
 |   The file defines some platform specific macros
 |
 |   Author(s)      : Felix Ritter
 |
 _______________  M E V I S   R E S E A R C H   G M B H  _______________
 _______________________________________________________________________
 */

#ifndef _SB_SYSTEM_
#define _SB_SYSTEM_

#include <Inventor/system/SbConfig.h>

#ifdef WIN32

#ifndef  __i386__
# define __i386__  1
#endif

//! Disable some annoying warnings on MSVC 6
#ifdef _MSC_VER
# pragma warning(disable:4244) // float, double
# pragma warning(disable:4305) // float, double
# pragma warning(disable:4309) // float, double
# pragma warning(disable:4251) // export
# pragma warning(disable:4291) // no delete destructor
#endif

#include <windows.h>
#include <winsock.h>    // declares many unix types
#include <math.h>

//! The following ifdef block is the standard way of creating macros which make exporting
//! from a DLL simpler. All files within this DLL are compiled with the INVENTOR_EXPORTS
//! symbol defined on the command line. this symbol should not be defined on any project
//! that uses this DLL. This way any other project whose source files include this file see
//! INVENTOR_API functions as being imported from a DLL, wheras this DLL sees symbols
//! defined with this macro as being exported.
#if defined(INVENTOR_EXPORTS) && !defined(INVENTOR_IMPORTS)
# define INVENTOR_API __declspec(dllexport)
#else
# define INVENTOR_API __declspec(dllimport)
#endif

#ifdef _DEBUG
# define SGIOIVDLL "Inventor_d.dll"
# define SGIOIVLIB "Inventor_d.lib"
#else
# define SGIOIVDLL "Inventor.dll"
# define SGIOIVLIB "Inventor.lib"
#endif

//! Tell MSVC which Open Inventor DLL to link against
#if defined(_MSC_VER) && !defined(__SGIOIV_BUILD_DLL)
# pragma comment(lib,SGIOIVLIB)
#endif

#else   // not WIN32

#define INVENTOR_API

#ifndef  CALLBACK
# define CALLBACK
#endif

#endif  // WIN32

//! OpenGL system settings

#ifdef __APPLE__

#include <AvailabilityMacros.h>

#if defined(__APPLE_CC__) && (__APPLE_CC__ < 5400)
# define OPENGL_CALLBACKFUNC GLvoid (CALLBACK *)(...)
#else
# define OPENGL_CALLBACKFUNC GLvoid (CALLBACK *)()
#endif

#else   // not __APPLE__

#define OPENGL_CALLBACKFUNC GLvoid (CALLBACK *)()

#endif  // __APPLE__

//! Font system settings

#if defined(WIN32)

#define IV_DEFAULT_FONTNAME "Times"

#elif defined(__APPLE__)

#define IV_DEFAULT_FONTNAME "Times-Roman"

#else

#define IV_DEFAULT_FONTNAME "Utopia-Regular"

#endif

#endif  // _SB_SYSTEM_
