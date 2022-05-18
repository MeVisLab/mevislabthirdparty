/*
 *
 *  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved. 
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
 *  Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 *  Mountain View, CA  94043, or:
 * 
 *  http://www.sgi.com 
 * 
 *  For further information regarding this notice, see: 
 * 
 *  http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */

#ifndef __glucoveandtiler_h
#define __glucoveandtiler_h

#include "../SoAddPrefix.h"

/*
 * coveandtiler.h - $Revision: 1.1.1.1 $
 */

#include "trimregion.h"

class Backend;
#ifdef _MSC_VER
struct TrimVertex;
struct GridVertex;
#else
class TrimVertex;
class GridVertex;
#endif
class GridTrimVertex;

class CoveAndTiler : virtual public TrimRegion {
public:
                        CoveAndTiler( Backend& );
                        ~CoveAndTiler( void );
    void                coveAndTile( void );
private:
    Backend&            backend;
    static const int    MAXSTRIPSIZE;
    void                tile( long, long, long );
    void                coveLowerLeft( void );
    void                coveLowerRight( void );
    void                coveUpperLeft( void );
    void                coveUpperRight( void );
    void                coveUpperLeftNoGrid( TrimVertex * );
    void                coveUpperRightNoGrid( TrimVertex * );
    void                coveLowerLeftNoGrid( TrimVertex * );
    void                coveLowerRightNoGrid( TrimVertex * );
    void                coveLL( void );
    void                coveLR( void );
    void                coveUL( void );
    void                coveUR( void );
    inline void         output( GridTrimVertex& );
    inline void         output( GridVertex& );
    inline void         output( TrimVertex* );
};

#endif /* __glucoveandtiler_h */
