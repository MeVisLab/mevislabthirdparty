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

/*
 * softcurveval.h
 *
 * $Revision: 1.1.1.1 $
 */

#ifndef SO_NURBS_SOFTCURVEVAL
#define SO_NURBS_SOFTCURVEVAL

#include <Inventor/SbTypeDefs.h>

#include "mystdio.h"
#include "isocurveeval.h"
#include "basiccrveval.h"
#include "softcurvmap.h"


class _SoNurbsCurveEvaluator : public _SoNurbsBasicCurveEvaluator  {  
public:
                        _SoNurbsCurveEvaluator( void );
                        ~_SoNurbsCurveEvaluator( void );
    void                range1f( long, REAL *, REAL * );
    void                domain1f( REAL, REAL );
    void                addMap( _SoNurbsCurveMap * );


    void                enable( long );
    void                disable( long );
    void                bgnmap1f( long );
    void                map1f( long, REAL, REAL, long, long, REAL * );
    void                mapgrid1f( long, REAL, REAL );
    void                mapmesh1f( long, long, long );
    void                evalpoint1i( long );
    void                evalcoord1f( long, REAL );
    void                endmap1f( void );

    void                bgnline( void );
    void                endline( void );

    int                 canRecord( void ) ;
    int                 canPlayAndRecord( void ) ;
    int                 createHandle( int handle );
    void                beginOutput( ServiceMode, int handle );
    void                endOutput( void ); 
    void                discardRecording( int handle );
    void                playRecording( int handle );

private:
    _SoNurbsCurveMap *  firstMap( void );
    _SoNurbsCurveMap *  nextMap( _SoNurbsCurveMap * );
    int                 isMap( _SoNurbsCurveMap * );

    _SoNurbsCurveMap *  maps;
    REAL                cus, cdus;
    
    _SoNurbsCurveMap *  typeToMap( long );
};

#endif /* SO_NURBS_SOFTCURVEVAL */
