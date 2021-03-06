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
 * mapdescv.cpp - $Revision: 1.1.1.1 $
 *      Derrick Burns - 1991
 */

#include "glimports.h"
#include "mystdio.h"
#include "myassert.h"
#include "mystring.h"
#include "mymath.h"
#include "nurbsconsts.h"
#include "mapdesc.h"

/*--------------------------------------------------------------------------
 * calcPartialVelocity - calculate maximum magnitude of a given partial
 * derivative
 *--------------------------------------------------------------------------
 */
REAL
Mapdesc::calcPartialVelocity (
    REAL *p,
    int  stride,
    int  ncols,
    int  partial,
    REAL range )
{
    REAL tmp[MAXORDER][MAXCOORDS];
    REAL mag[MAXORDER];

    assert( ncols <= MAXORDER );

    int j, k, t;
    // copy inhomogeneous control points into temporary array
    for( j=0; j != ncols; j++ ) 
        for( k=0; k != inhcoords; k++ )
            tmp[j][k] = p[j*stride + k];

    for( t=0; t != partial; t++ ) 
        for( j=0; j != ncols-t-1; j++ ) 
            for( k=0; k != inhcoords; k++ ) 
                tmp[j][k] = tmp[j+1][k] - tmp[j][k];

    // compute magnitude and store in mag array
    for( j=0; j != ncols-partial; j++ ) {
        mag[j] = 0.0;
        for( k=0; k != inhcoords; k++ )
            mag[j] += tmp[j][k] * tmp[j][k];
    }

    // compute scale factor
    REAL fac = 1;
    REAL invt = 1.0 / range;
    for( t = ncols-1; t != ncols-1-partial; t-- ) 
        fac *= t * invt;

    // compute max magnitude of all entries in array
    REAL max = 0.0;
    for( j=0; j != ncols-partial; j++ )
        if( mag[j] > max ) max = mag[j];
    max = fac * ::sqrtf( (float) max );

    return max;
}

/*--------------------------------------------------------------------------
 * calcPartialVelocity - calculate maximum magnitude of a given partial
 * derivative
 *--------------------------------------------------------------------------
 */
REAL
Mapdesc::calcPartialVelocity (
    REAL *dist,
    REAL *p,
    int  rstride,
    int  cstride,
    int  nrows,
    int  ncols,
    int  spartial,
    int  tpartial,
    REAL srange, 
    REAL trange,
    int  side )
{
    REAL tmp[MAXORDER][MAXORDER][MAXCOORDS];
    REAL mag[MAXORDER][MAXORDER];

    assert( nrows <= MAXORDER );
    assert( ncols <= MAXORDER );

    REAL *tp = &tmp[0][0][0];
    REAL *mp = &mag[0][0];
    const int istride = sizeof( tmp[0]) / sizeof( tmp[0][0][0] );
    const int jstride = sizeof( tmp[0][0]) / sizeof( tmp[0][0][0] );
    const int mistride = sizeof( mag[0]) / sizeof( mag[0][0] );
    const int mjstride = sizeof( mag[0][0]) / sizeof( mag[0][0] );
    const int idist = nrows * istride;
    const int jdist = ncols * jstride;
    const int id = idist - spartial * istride;
    const int jd = jdist - tpartial * jstride;

    {
        // copy control points
        REAL *ti = tp;
        REAL *qi = p;
        REAL *til = tp + idist;
        for( ; ti != til; ) {
            REAL *tj = ti;
            REAL *qj = qi;
            REAL *tjl = ti + jdist;
            for( ; tj != tjl;  ) {
                for( int k=0; k != inhcoords; k++ ) {
                    tj[k] = qj[k];
                }
                tj += jstride;
                qj += cstride;
            }
            ti += istride;
            qi += rstride; 
        }
    }

    {
        // compute (s)-partial derivative control points
        REAL *til = tp + idist - istride;
        const REAL *till = til - ( spartial * istride );
        for( ; til != till; til -= istride )
            for( REAL *ti = tp; ti != til; ti += istride )
                for( REAL *tj = ti, *tjl = tj + jdist; tj != tjl; tj += jstride )
                    for( int k=0; k != inhcoords; k++ )
                        tj[k] = tj[k+istride] - tj[k];
    }

    {
        // compute (s,t)-partial derivative control points
        REAL *tjl = tp + jdist - jstride;
        const REAL *tjll = tjl - ( tpartial * jstride );
        for( ; tjl != tjll; tjl -= jstride )
            for( REAL *tj = tp; tj != tjl; tj += jstride )
                for( REAL *ti = tj, *til = ti + id; ti != til; ti += istride )
                    for( int k=0; k != inhcoords; k++ ) 
                        ti[k] = ti[k+jstride] - ti[k];

    }

    REAL max = 0.0;
    {
        // compute magnitude and store in mag array
        memset( (void *) mp, 0, sizeof( mag ) );
        for( REAL *ti = tp, *mi = mp, *til = tp + id; ti != til; ti += istride, mi += mistride )
            for( REAL *tj = ti, *mj = mi, *tjl = ti + jd; tj != tjl; tj += jstride, mj += mjstride ) {
                for( int k=0; k != inhcoords; k++ )
                   *mj += tj[k] * tj[k];
                if( *mj > max ) max = *mj;
            }

    }

    int i, j;

    // compute scale factor
    REAL fac = 1.0;
    {
        REAL invs = 1.0 / srange;
        REAL invt = 1.0 / trange;
        for( int s = nrows-1, slast = s-spartial; s != slast; s-- ) 
            fac *= s * invs;
        for( int t = ncols-1, tlast = t-tpartial; t != tlast; t-- ) 
            fac *= t * invt;
    }

    if( side == 0 ) {
        // compute max magnitude of first and last column
        dist[0] = 0.0;
        dist[1] = 0.0;
        for( i=0; i != nrows-spartial; i++ ) {
            j = 0;
            if( mag[i][j] > dist[0] ) dist[0] = mag[i][j];
    
            j = ncols-tpartial-1;
            if( mag[i][j] > dist[1] ) dist[1] = mag[i][j];
        }
        dist[0] = fac * ::sqrtf( dist[0] );
        dist[1] = fac * ::sqrtf( dist[1] );
    } else if( side == 1 ) {
        // compute max magnitude of first and last row
        dist[0] = 0.0;
        dist[1] = 0.0;
        for( j=0; j != ncols-tpartial; j++ ) {
            i = 0;
            if( mag[i][j] > dist[0] ) dist[0] = mag[i][j];
    
            i = nrows-spartial-1;
            if( mag[i][j] > dist[1] ) dist[1] = mag[i][j];
        }
        dist[0] = fac * ::sqrtf( dist[0] );
        dist[1] = fac * ::sqrtf( dist[1] );
    }

    max = fac * ::sqrtf( (float) max );

    return max;
}

