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
 * patch.cpp - $Revision: 1.1.1.1 $
 *      Derrick Burns - 1992
 */

#include "glimports.h"
#include "mystdio.h"
#include "myassert.h"
#include "mymath.h"
#include "mystring.h"
#include "patch.h"
#include "mapdesc.h"
#include "quilt.h"
#include "nurbsconsts.h"
#include "simplemath.h" //for abs function in ::singleStep();


/*--------------------------------------------------------------------------
 * Patch - copy patch from quilt and transform control points
 *--------------------------------------------------------------------------
 */

Patch::Patch( Quilt_ptr geo, REAL *pta, REAL *ptb, Patch *n )
{
/* pspec[i].range is uninit here */
    mapdesc = geo->mapdesc;
    cullval = mapdesc->isCulling() ? CULL_ACCEPT : CULL_TRIVIAL_ACCEPT;
    notInBbox = mapdesc->isBboxSubdividing() ? 1 : 0;
    needsSampling = mapdesc->isRangeSampling() ? 1 : 0;
    pspec[0].order = geo->qspec[0].order;
    pspec[1].order = geo->qspec[1].order;
    pspec[0].stride = pspec[1].order * MAXCOORDS;
    pspec[1].stride = MAXCOORDS;

    /* transform control points to sampling and culling spaces */
    REAL *ps  = geo->cpts;
    geo->select( pta, ptb );
    ps += geo->qspec[0].offset;
    ps += geo->qspec[1].offset;
    ps += geo->qspec[0].index * geo->qspec[0].order * geo->qspec[0].stride;
    ps += geo->qspec[1].index * geo->qspec[1].order * geo->qspec[1].stride;

    if( needsSampling ) {
        mapdesc->xformSampling( ps, geo->qspec[0].order, geo->qspec[0].stride, 
                                geo->qspec[1].order, geo->qspec[1].stride,
                                spts, pspec[0].stride, pspec[1].stride );
    }

    if( cullval == CULL_ACCEPT  ) {
        mapdesc->xformCulling( ps, geo->qspec[0].order, geo->qspec[0].stride, 
                               geo->qspec[1].order, geo->qspec[1].stride,
                               cpts, pspec[0].stride, pspec[1].stride ); 
    }
    
    if( notInBbox ) {
        mapdesc->xformBounding( ps, geo->qspec[0].order, geo->qspec[0].stride, 
                               geo->qspec[1].order, geo->qspec[1].stride,
                               bpts, pspec[0].stride, pspec[1].stride ); 
    }
    
    /* set scale range */
    pspec[0].range[0] = geo->qspec[0].breakpoints[geo->qspec[0].index];
    pspec[0].range[1] = geo->qspec[0].breakpoints[geo->qspec[0].index+1];
    pspec[0].range[2] = pspec[0].range[1] - pspec[0].range[0];

    pspec[1].range[0] = geo->qspec[1].breakpoints[geo->qspec[1].index];
    pspec[1].range[1] = geo->qspec[1].breakpoints[geo->qspec[1].index+1];
    pspec[1].range[2] = pspec[1].range[1] - pspec[1].range[0];

    // may need to subdivide to match range of sub-patch
    if( pspec[0].range[0] != pta[0] ) {
        assert( pspec[0].range[0] < pta[0] );
        Patch lower( *this, 0, pta[0], 0 );
        *this = lower;
    }

    if( pspec[0].range[1] != ptb[0] ) {
        assert( pspec[0].range[1] > ptb[0] );
        Patch upper( *this, 0, ptb[0], 0 );
    }

    if( pspec[1].range[0] != pta[1] ) {
        assert( pspec[1].range[0] < pta[1] );
        Patch lower( *this, 1, pta[1], 0 );
        *this = lower;
    }

    if( pspec[1].range[1] != ptb[1] ) {
        assert( pspec[1].range[1] > ptb[1] );
        Patch upper( *this, 1, ptb[1], 0 );
    }
    checkBboxConstraint();
    next = n;
}

/*--------------------------------------------------------------------------
 * Patch - subdivide a patch along an isoparametric line
 *--------------------------------------------------------------------------
 */

Patch::Patch( Patch& upper, int param, REAL value, Patch *n )
{
    Patch& lower = *this;

    lower.cullval = upper.cullval;
    lower.mapdesc = upper.mapdesc;
    lower.notInBbox = upper.notInBbox;
    lower.needsSampling = upper.needsSampling;
    lower.pspec[0].order = upper.pspec[0].order;
    lower.pspec[1].order = upper.pspec[1].order;
    lower.pspec[0].stride = upper.pspec[0].stride;
    lower.pspec[1].stride = upper.pspec[1].stride;
    lower.next = n;

    /* reset scale range */
    switch( param ) {
        case 0: {
            REAL d = (value-upper.pspec[0].range[0]) / upper.pspec[0].range[2];
            if( needsSampling )
                mapdesc->subdivide( upper.spts, lower.spts, d, pspec[1].order,
                        pspec[1].stride, pspec[0].order, pspec[0].stride );

            if( cullval == CULL_ACCEPT ) 
                mapdesc->subdivide( upper.cpts, lower.cpts, d, pspec[1].order,
                        pspec[1].stride, pspec[0].order, pspec[0].stride );

            if( notInBbox ) 
                mapdesc->subdivide( upper.bpts, lower.bpts, d, pspec[1].order,
                        pspec[1].stride, pspec[0].order, pspec[0].stride );
            
            lower.pspec[0].range[0] = upper.pspec[0].range[0];
            lower.pspec[0].range[1] = value;
            lower.pspec[0].range[2] = value - upper.pspec[0].range[0];
            upper.pspec[0].range[0] = value;
            upper.pspec[0].range[2] = upper.pspec[0].range[1] - value;

            lower.pspec[1].range[0] = upper.pspec[1].range[0];
            lower.pspec[1].range[1] = upper.pspec[1].range[1];
            lower.pspec[1].range[2] = upper.pspec[1].range[2];
            break;
        }
        case 1: {
            REAL d = (value-upper.pspec[1].range[0]) / upper.pspec[1].range[2];
            if( needsSampling )
                mapdesc->subdivide( upper.spts, lower.spts, d, pspec[0].order,
                        pspec[0].stride, pspec[1].order, pspec[1].stride );
            if( cullval == CULL_ACCEPT ) 
                mapdesc->subdivide( upper.cpts, lower.cpts, d, pspec[0].order,
                        pspec[0].stride, pspec[1].order, pspec[1].stride );
            if( notInBbox ) 
                mapdesc->subdivide( upper.bpts, lower.bpts, d, pspec[0].order,
                        pspec[0].stride, pspec[1].order, pspec[1].stride );
            lower.pspec[0].range[0] = upper.pspec[0].range[0];
            lower.pspec[0].range[1] = upper.pspec[0].range[1];
            lower.pspec[0].range[2] = upper.pspec[0].range[2];

            lower.pspec[1].range[0] = upper.pspec[1].range[0];
            lower.pspec[1].range[1] = value;
            lower.pspec[1].range[2] = value - upper.pspec[1].range[0];
            upper.pspec[1].range[0] = value;
            upper.pspec[1].range[2] = upper.pspec[1].range[1] - value;
            break;
        }
    }

    // inherit bounding box
    if( mapdesc->isBboxSubdividing() && ! notInBbox )
        memcpy( lower.bb, upper.bb, sizeof( bb ) );
            
    lower.checkBboxConstraint();
    upper.checkBboxConstraint();
}

/*--------------------------------------------------------------------------
 * clamp - clamp the sampling rate to a given maximum
 *--------------------------------------------------------------------------
 */

void
Patch::clamp( void )
{
    if( mapdesc->clampfactor != N_NOCLAMPING ) {
        pspec[0].clamp( mapdesc->clampfactor );
        pspec[1].clamp( mapdesc->clampfactor );
    }
}

void 
Patchspec::clamp( REAL clampfactor )
{
    if( sidestep[0] < minstepsize )
        sidestep[0] = clampfactor * minstepsize;
    if( sidestep[1] < minstepsize )
        sidestep[1] = clampfactor * minstepsize;
    if( stepsize < minstepsize )
        stepsize = clampfactor * minstepsize;
}

void 
Patch::checkBboxConstraint( void )
{
    if( notInBbox && 
        mapdesc->bboxTooBig( bpts, pspec[0].stride, pspec[1].stride,
                                   pspec[0].order, pspec[1].order, bb ) != 1 ) {
        notInBbox = 0;
    }
}

void
Patch::bbox( void )
{
    if( mapdesc->isBboxSubdividing() )
        mapdesc->surfbbox( bb );
}

/*--------------------------------------------------------------------------
 * getstepsize - compute the sampling density across the patch
 *              and determine if patch needs to be subdivided
 *--------------------------------------------------------------------------
 */

void
Patch::getstepsize( void )
{
    pspec[0].minstepsize = pspec[1].minstepsize = 0;
    pspec[0].needsSubdivision = pspec[1].needsSubdivision = 0;

    if( mapdesc->isConstantSampling() ) {
        // fixed number of samples per patch in each direction
        // maxsrate is number of s samples per patch
        // maxtrate is number of t samples per patch
        pspec[0].getstepsize( mapdesc->maxsrate );
        pspec[1].getstepsize( mapdesc->maxtrate );

    } else if( mapdesc->isDomainSampling() ) {
        // maxsrate is number of s samples per unit s length of domain
        // maxtrate is number of t samples per unit t length of domain
        pspec[0].getstepsize( mapdesc->maxsrate * pspec[0].range[2] );
        pspec[1].getstepsize( mapdesc->maxtrate * pspec[1].range[2] );

    } else if( ! needsSampling ) {
        pspec[0].singleStep();
        pspec[1].singleStep();
    } else {
        // upper bound on path length between sample points
        REAL tmp[MAXORDER][MAXORDER][MAXCOORDS];
        const int trstride = sizeof(tmp[0]) / sizeof(REAL);
        const int tcstride = sizeof(tmp[0][0]) / sizeof(REAL); 

        assert( pspec[0].order <= MAXORDER );
    
        /* points have been transformed, therefore they are homogeneous */

        int val = mapdesc->project( spts, pspec[0].stride, pspec[1].stride, 
                 &tmp[0][0][0], trstride, tcstride, 
                 pspec[0].order, pspec[1].order ); 
        if( val == 0 ) {
            // control points cross infinity, therefore partials are undefined
            pspec[0].getstepsize( mapdesc->maxsrate );
            pspec[1].getstepsize( mapdesc->maxtrate );
        } else {
            REAL t1 = mapdesc->getProperty( N_PIXEL_TOLERANCE );
            REAL t2 = mapdesc->getProperty( N_ERROR_TOLERANCE );
            pspec[0].minstepsize = ( mapdesc->maxsrate > 0.0 ) ? 
                        (pspec[0].range[2] / mapdesc->maxsrate) : 0.0;
            pspec[1].minstepsize = ( mapdesc->maxtrate > 0.0 ) ? 
                        (pspec[1].range[2] / mapdesc->maxtrate) : 0.0;
            if( mapdesc->isParametricDistanceSampling() ) {
                // t2 is upper bound on the distance between surface and tessellant 
                REAL ssv[2], ttv[2];
                REAL ss = mapdesc->calcPartialVelocity( ssv, &tmp[0][0][0], trstride, tcstride, pspec[0].order, pspec[1].order, 2, 0, pspec[0].range[2], pspec[1].range[2], 0 );
                REAL st = mapdesc->calcPartialVelocity(   0, &tmp[0][0][0], trstride, tcstride, pspec[0].order, pspec[1].order, 1, 1, pspec[0].range[2], pspec[1].range[2], -1 );
                REAL tt = mapdesc->calcPartialVelocity( ttv, &tmp[0][0][0], trstride, tcstride, pspec[0].order, pspec[1].order, 0, 2, pspec[0].range[2], pspec[1].range[2], 1 );
                //make sure that ss st and tt are nonnegative:
                if(ss <0) ss = -ss;
                if(st <0) st = -st;
                if(tt <0) tt = -tt;

                if( ss != 0.0 && tt != 0.0 ) {
                    /* printf( "ssv[0] %g ssv[1] %g ttv[0] %g ttv[1] %g\n", 
                        ssv[0], ssv[1], ttv[0], ttv[1] ); */
                    REAL ttq = ::sqrtf( (float) ss );
                    REAL ssq = ::sqrtf( (float) tt );
                    REAL ds = ::sqrtf( 4 * t2 * ttq / ( ss * ttq + st * ssq ) );
                    REAL dt = ::sqrtf( 4 * t2 * ssq / ( tt * ssq + st * ttq ) );
                    pspec[0].stepsize = ( ds < pspec[0].range[2] ) ? ds : pspec[0].range[2];
                    REAL scutoff = 2.0 * t2 / ( pspec[0].range[2] * pspec[0].range[2]);
                    pspec[0].sidestep[0] = (ssv[0] > scutoff) ? ::sqrtf( 2.0 * t2 / ssv[0] ) : pspec[0].range[2];
                    pspec[0].sidestep[1] = (ssv[1] > scutoff) ? ::sqrtf( 2.0 * t2 / ssv[1] ) : pspec[0].range[2];
    
                    pspec[1].stepsize = ( dt < pspec[1].range[2] ) ? dt : pspec[1].range[2];
                    REAL tcutoff = 2.0 * t2 / ( pspec[1].range[2] * pspec[1].range[2]);
                    pspec[1].sidestep[0] = (ttv[0] > tcutoff) ? ::sqrtf( 2.0 * t2 / ttv[0] ) : pspec[1].range[2];
                    pspec[1].sidestep[1] = (ttv[1] > tcutoff) ? ::sqrtf( 2.0 * t2 / ttv[1] ) : pspec[1].range[2];
                } else if( ss != 0.0 ) {
                    REAL x = pspec[1].range[2] * st;
                    REAL ds = ( ::sqrtf( x * x + 8.0 * t2 * ss ) - x ) / ss;
                    pspec[0].stepsize = ( ds < pspec[0].range[2] ) ? ds : pspec[0].range[2];
                    REAL scutoff = 2.0 * t2 / ( pspec[0].range[2] * pspec[0].range[2]);
                    pspec[0].sidestep[0] = (ssv[0] > scutoff) ? ::sqrtf( 2.0 * t2 / ssv[0] ) : pspec[0].range[2];
                    pspec[0].sidestep[1] = (ssv[1] > scutoff) ? ::sqrtf( 2.0 * t2 / ssv[1] ) : pspec[0].range[2];
                    pspec[1].singleStep();
                } else if( tt != 0.0 ) {
                    REAL x = pspec[0].range[2] * st;
                    REAL dt = ( ::sqrtf( x * x + 8.0 * t2 * tt ) - x )  / tt;
                    pspec[0].singleStep();
                    REAL tcutoff = 2.0 * t2 / ( pspec[1].range[2] * pspec[1].range[2]);
                    pspec[1].stepsize = ( dt < pspec[1].range[2] ) ? dt : pspec[1].range[2];
                    pspec[1].sidestep[0] = (ttv[0] > tcutoff) ? ::sqrtf( 2.0 * t2 / ttv[0] ) : pspec[1].range[2];
                    pspec[1].sidestep[1] = (ttv[1] > tcutoff) ? ::sqrtf( 2.0 * t2 / ttv[1] ) : pspec[1].range[2];
                } else {
                    if( 4.0 * t2  > st * pspec[0].range[2] * pspec[1].range[2] ) {
                        pspec[0].singleStep();
                        pspec[1].singleStep();
                    } else {
                        REAL area = 4.0 * t2 / st;
                        REAL ds = ::sqrtf( area * pspec[0].range[2] / pspec[1].range[2] );
                        REAL dt = ::sqrtf( area * pspec[1].range[2] / pspec[0].range[2] );
                        pspec[0].stepsize = ( ds < pspec[0].range[2] ) ? ds : pspec[0].range[2];
                        pspec[0].sidestep[0] = pspec[0].range[2];
                        pspec[0].sidestep[1] = pspec[0].range[2];
        
                        pspec[1].stepsize = ( dt < pspec[1].range[2] ) ? dt : pspec[1].range[2];
                        pspec[1].sidestep[0] = pspec[1].range[2];
                        pspec[1].sidestep[1] = pspec[1].range[2];
                    }
                }
            } else if( mapdesc->isPathLengthSampling() ) {
                // t1 is upper bound on path length
                REAL msv[2], mtv[2];
                REAL ms = mapdesc->calcPartialVelocity( msv, &tmp[0][0][0], trstride, tcstride, pspec[0].order, pspec[1].order, 1, 0, pspec[0].range[2], pspec[1].range[2], 0 );
                REAL mt = mapdesc->calcPartialVelocity( mtv, &tmp[0][0][0], trstride, tcstride, pspec[0].order, pspec[1].order, 0, 1, pspec[0].range[2], pspec[1].range[2], 1 );
                REAL side_scale = 1.0;

                if( ms != 0.0 ) {
                    if( mt != 0.0 ) {
/*                  REAL d = t1 / ( ms * ms + mt * mt );*/
/*                  REAL ds = mt * d;*/
                    REAL ds = t1 / (2.0*ms);
/*                  REAL dt = ms * d;*/
                    REAL dt = t1 / (2.0*mt); 
                        pspec[0].stepsize = ( ds < pspec[0].range[2] ) ? ds : pspec[0].range[2];
                        pspec[0].sidestep[0] = ( msv[0] * pspec[0].range[2] > t1 ) ? (side_scale* t1 / msv[0]) : pspec[0].range[2];
                        pspec[0].sidestep[1] = ( msv[1] * pspec[0].range[2] > t1 ) ? (side_scale* t1 / msv[1]) : pspec[0].range[2];
        
                        pspec[1].stepsize = ( dt < pspec[1].range[2] ) ? dt : pspec[1].range[2];
                        pspec[1].sidestep[0] = ( mtv[0] * pspec[1].range[2] > t1 ) ? (side_scale*t1 / mtv[0]) : pspec[1].range[2];
                        pspec[1].sidestep[1] = ( mtv[1] * pspec[1].range[2] > t1 ) ? (side_scale*t1 / mtv[1]) : pspec[1].range[2];
                    } else {
                        pspec[0].stepsize = ( t1 < ms * pspec[0].range[2] ) ? (t1 / ms) : pspec[0].range[2];
                        pspec[0].sidestep[0] = ( msv[0] * pspec[0].range[2] > t1 ) ? (t1 / msv[0]) : pspec[0].range[2];
                        pspec[0].sidestep[1] = ( msv[1] * pspec[0].range[2] > t1 ) ? (t1 / msv[1]) : pspec[0].range[2];
        
                        pspec[1].singleStep();
                    }
                } else {
                    if( mt != 0.0 ) {
                        pspec[0].singleStep();
    
                        pspec[1].stepsize = ( t1 < mt * pspec[1].range[2] ) ? (t1 / mt) : pspec[1].range[2];
                        pspec[1].sidestep[0] = ( mtv[0] * pspec[1].range[2] > t1 ) ? (t1 / mtv[0]) : pspec[1].range[2];
                        pspec[1].sidestep[1] = ( mtv[1] * pspec[1].range[2] > t1 ) ? (t1 / mtv[1]) : pspec[1].range[2];
                    } else {
                        pspec[0].singleStep();
                        pspec[1].singleStep();
                    }
                }
            } else if( mapdesc->isSurfaceAreaSampling() ) {
                // t is the square root of area
/*
                REAL msv[2], mtv[2];
                REAL ms = mapdesc->calcPartialVelocity( msv, &tmp[0][0][0], trstride, tcstride, pspec[0].order, pspec[1].order, 1, 0, pspec[0].range[2], pspec[1].range[2], 0 );
                REAL mt = mapdesc->calcPartialVelocity( mtv, &tmp[0][0][0], trstride, tcstride, pspec[0].order, pspec[1].order, 0, 1, pspec[0].range[2], pspec[1].range[2], 1 );
                if( ms != 0.0 &&  mt != 0.0 ) {
                        REAL d = 1.0 / (ms * mt);
                        t *= M_SQRT2;
                        REAL ds = t * ::sqrtf( d * pspec[0].range[2] / pspec[1].range[2] );
                        REAL dt = t * ::sqrtf( d * pspec[1].range[2] / pspec[0].range[2] );
                        pspec[0].stepsize = ( ds < pspec[0].range[2] ) ? ds : pspec[0].range[2];
                        pspec[0].sidestep[0] = ( msv[0] * pspec[0].range[2] > t ) ? (t / msv[0]) : pspec[0].range[2];
                        pspec[0].sidestep[1] = ( msv[1] * pspec[0].range[2] > t ) ? (t / msv[1]) : pspec[0].range[2];
        
                        pspec[1].stepsize = ( dt < pspec[1].range[2] ) ? dt : pspec[1].range[2];
                        pspec[1].sidestep[0] = ( mtv[0] * pspec[1].range[2] > t ) ? (t / mtv[0]) : pspec[1].range[2];
                        pspec[1].sidestep[1] = ( mtv[1] * pspec[1].range[2] > t ) ? (t / mtv[1]) : pspec[1].range[2];
                } else {
                    pspec[0].singleStep();
                    pspec[1].singleStep();
                }
*/
            } else {
                pspec[0].singleStep();
                pspec[1].singleStep();
            }
        }
    }

    dprintf( "sidesteps %g %g %g %g, stepsize %g %g\n",
        pspec[0].sidestep[0], pspec[0].sidestep[1],
        pspec[1].sidestep[0], pspec[1].sidestep[1],
        pspec[0].stepsize, pspec[1].stepsize );

    if( mapdesc->minsavings != N_NOSAVINGSSUBDIVISION ) {
        REAL savings = 1./(pspec[0].stepsize * pspec[1].stepsize) ;
        savings-= (2./( pspec[0].sidestep[0] + pspec[0].sidestep[1] )) * 
                  (2./( pspec[1].sidestep[0] + pspec[1].sidestep[1] ));
    
        savings *= pspec[0].range[2] * pspec[1].range[2];
        if( savings > mapdesc->minsavings ) {
            pspec[0].needsSubdivision = pspec[1].needsSubdivision = 1;
        }
    }

    if( pspec[0].stepsize < pspec[0].minstepsize )  pspec[0].needsSubdivision =  1;
    if( pspec[1].stepsize < pspec[1].minstepsize )  pspec[1].needsSubdivision =  1;
    needsSampling = (needsSampling ? needsSamplingSubdivision() : 0);
}

void
Patchspec::singleStep()
{
    stepsize =  sidestep[0] =  sidestep[1] = fabs(range[2]);
}

void 
Patchspec::getstepsize( REAL max ) // max is number of samples for entire patch
{
    stepsize = ( max >= 1.0 ) ? range[2] / max : range[2];
    if (stepsize < 0.0) {
       stepsize = -stepsize;
    }
    sidestep[0] =  sidestep[1] = minstepsize = stepsize;
}

int
Patch::needsSamplingSubdivision( void )
{
    return (pspec[0].needsSubdivision || pspec[1].needsSubdivision) ? 1 : 0;
}

int
Patch::needsNonSamplingSubdivision( void )
{
    return notInBbox;
}

int
Patch::needsSubdivision( int param )
{
    return pspec[param].needsSubdivision;
}

int
Patch::cullCheck( void )
{
    if( cullval == CULL_ACCEPT ) 
        cullval = mapdesc->cullCheck( cpts, pspec[0].order,  pspec[0].stride,
                                            pspec[1].order,  pspec[1].stride );
    return cullval;
}

