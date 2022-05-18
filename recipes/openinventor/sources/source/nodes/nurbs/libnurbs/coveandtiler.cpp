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
 * coveandtiler.cpp - $Revision: 1.1.1.1 $
 *      Derrick Burns - 1991
 */

#include "glimports.h"
#include "myassert.h"
#include "mystdio.h"
#include "coveandtiler.h"
#include "gridvertex.h"
#include "gridtrimvertex.h"
#include "uarray.h"
#include "backend.h"


const int CoveAndTiler::MAXSTRIPSIZE = 1000;

CoveAndTiler::CoveAndTiler( Backend& b )
            : backend( b )
{ }

CoveAndTiler::~CoveAndTiler( void )
{ }

inline void
CoveAndTiler::output( GridVertex &gv )
{
    backend.tmeshvert( &gv );
}

inline void
CoveAndTiler::output( TrimVertex *tv )
{
    backend.tmeshvert( tv );
}

inline void
CoveAndTiler::output( GridTrimVertex& g )
{
    backend.tmeshvert( &g );
}

void 
CoveAndTiler::coveAndTile( void )
{
    long ustart = (top.ustart >= bot.ustart) ? top.ustart : bot.ustart;
    long uend   = (top.uend <= bot.uend)     ? top.uend   : bot.uend;
    if( ustart <= uend ) {
        tile( bot.vindex, ustart, uend );
        if( top.ustart >= bot.ustart )  
            coveUpperLeft();
        else 
            coveLowerLeft();
    
        if( top.uend <= bot.uend )  
            coveUpperRight();
        else
            coveLowerRight();
    } else {
        TrimVertex blv, tlv, *bl, *tl;
        GridTrimVertex bllv, tllv;
        TrimVertex *lf = left.first();
        TrimVertex *ll = left.last();
        if( lf->param[0] >= ll->param[0] ) {
            blv.param[0] = lf->param[0];
            blv.param[1] = ll->param[1];
            blv.nuid = 0; // XXX
            assert( blv.param[1] == bot.vval );
            bl = &blv;
            tl = lf;
            tllv.set( lf );
            if( ll->param[0] > uarray.uarray[top.ustart-1] ) {
                bllv.set( ll );
                assert( ll->param[0] <= uarray.uarray[bot.ustart] );
            } else {
                bllv.set( top.ustart-1, bot.vindex );
            }
            coveUpperLeftNoGrid( bl );
        } else {
            tlv.param[0] = ll->param[0];
            tlv.param[1] = lf->param[1];
            tlv.nuid = 0; // XXX
            assert( tlv.param[1] == top.vval );
            tl = &tlv;
            bl = ll;
            bllv.set( ll );
            if( lf->param[0] > uarray.uarray[bot.ustart-1] ) {
                assert( lf->param[0] <= uarray.uarray[bot.ustart] );
                tllv.set( lf );
            } else {
                tllv.set( bot.ustart-1, top.vindex );
            }
            coveLowerLeftNoGrid( tl );
        }

        TrimVertex brv, trv, *br, *tr;
        GridTrimVertex brrv, trrv;
        TrimVertex *rf = right.first();
        TrimVertex *rl = right.last();

        if( rf->param[0] <= rl->param[0] ) {
            brv.param[0] = rf->param[0];
            brv.param[1] = rl->param[1];
            brv.nuid = 0; // XXX
            assert( brv.param[1] == bot.vval );
            br = &brv;
            tr = rf;
            trrv.set( rf );
            if( rl->param[0] < uarray.uarray[top.uend+1] ) {
                assert( rl->param[0] >= uarray.uarray[top.uend] );
                brrv.set( rl );
            } else {
                brrv.set( top.uend+1, bot.vindex );
            }
            coveUpperRightNoGrid( br );
        } else {
            trv.param[0] = rl->param[0];
            trv.param[1] = rf->param[1];
            trv.nuid = 0; // XXX
            assert( trv.param[1] == top.vval );
            tr = &trv;
            br = rl;
            brrv.set( rl );
            if( rf->param[0] < uarray.uarray[bot.uend+1] ) {
                assert( rf->param[0] >= uarray.uarray[bot.uend] );
                trrv.set( rf );
            } else {
                trrv.set( bot.uend+1, top.vindex );
            }
            coveLowerRightNoGrid( tr );
        }

        backend.bgntmesh( "doit" );
        output(trrv);
        output(tllv);
        output( tr );
        output( tl );
        output( br );
        output( bl );
        output(brrv);
        output(bllv);
        backend.endtmesh();
    }
}

void 
CoveAndTiler::tile( long vindex, long ustart, long uend )
{
    long numsteps = uend - ustart;

    if( numsteps == 0 ) return;

    if( numsteps > MAXSTRIPSIZE ) {
        long umid = ustart + (uend - ustart) / 2;
        tile( vindex, ustart, umid );
        tile( vindex, umid, uend );
    } else {
        backend.surfmesh( ustart, vindex-1, numsteps, 1 );
    }
}

void 
CoveAndTiler::coveUpperRight( void )
{
    GridVertex tgv( top.uend, top.vindex );
    GridVertex gv( top.uend, bot.vindex );

    right.first();
    backend.bgntmesh( "coveUpperRight" );
    output( right.next() );
    output( tgv );
    backend.swaptmesh();
    output( gv );
        coveUR();
    backend.endtmesh();
}

void
CoveAndTiler::coveUpperRightNoGrid( TrimVertex* br )
{
    backend.bgntmesh( "coveUpperRight" );
    output( right.first() ); 
    output( right.next() );
    backend.swaptmesh();
    output( br );
        coveUR();
    backend.endtmesh();
}

void 
CoveAndTiler::coveUR( )
{
    GridVertex gv( top.uend, bot.vindex );
    TrimVertex *vert = right.next();
    if( vert == NULL ) return;

    assert( vert->param[0] >= uarray.uarray[gv.gparam[0]]  );

    if( gv.nextu() >= bot.uend ) {
        for( ; vert; vert = right.next() ) {
            output( vert );
            backend.swaptmesh();
        }
    } else while( 1 ) {
        if( vert->param[0] < uarray.uarray[gv.gparam[0]]  ) {
            output( vert );
            backend.swaptmesh();
            vert = right.next();
            if( vert == NULL ) break;
        } else {
            backend.swaptmesh();
            output( gv );
            if( gv.nextu() == bot.uend ) {
                for( ; vert; vert = right.next() ) {
                    output( vert );
                    backend.swaptmesh();
                }
                break;
            }
        }
    }
}

void
CoveAndTiler::coveUpperLeft( void )
{
    GridVertex tgv( top.ustart, top.vindex );
    GridVertex gv( top.ustart, bot.vindex );

    left.first();
    backend.bgntmesh( "coveUpperLeft" );
    output( tgv );
    output( left.next() );
    output( gv );
    backend.swaptmesh();
        coveUL();
    backend.endtmesh();
}

void
CoveAndTiler::coveUpperLeftNoGrid( TrimVertex* bl )
{
    backend.bgntmesh( "coveUpperLeftNoGrid" );
    output( left.first() ); 
    output( left.next() );
    output( bl );
    backend.swaptmesh();
        coveUL();
    backend.endtmesh();
}

void 
CoveAndTiler::coveUL()
{
    GridVertex gv( top.ustart, bot.vindex );
    TrimVertex *vert = left.next();
    if( vert == NULL ) return;
    assert( vert->param[0] <= uarray.uarray[gv.gparam[0]]  );

    if( gv.prevu() <= bot.ustart ) {
        for( ; vert; vert = left.next() ) {
            backend.swaptmesh();
            output( vert );
        }
    } else while( 1 ) {
        if( vert->param[0] > uarray.uarray[gv.gparam[0]]  ) {
            backend.swaptmesh();
            output( vert );
            vert = left.next();
            if( vert == NULL ) break;
        } else {
            output( gv );
            backend.swaptmesh();
            if( gv.prevu() == bot.ustart ) {
                for( ; vert; vert = left.next() ) {
                    backend.swaptmesh();
                    output( vert );
                }
                break;
            }
        }
    }
}

void 
CoveAndTiler::coveLowerLeft( void )
{
    GridVertex bgv( bot.ustart, bot.vindex );
    GridVertex gv( bot.ustart, top.vindex );

    left.last();
    backend.bgntmesh( "coveLowerLeft" );
    output( left.prev() );
    output( bgv );
    backend.swaptmesh();
    output( gv );
        coveLL();
    backend.endtmesh();
}

void
CoveAndTiler::coveLowerLeftNoGrid( TrimVertex* tl )
{
    backend.bgntmesh( "coveLowerLeft" );
    output( left.last() ); 
    output( left.prev() );
    backend.swaptmesh();
    output( tl );
        coveLL( );
    backend.endtmesh();
}

void 
CoveAndTiler::coveLL()
{
    GridVertex gv( bot.ustart, top.vindex );
    TrimVertex *vert = left.prev();
    if( vert == NULL ) return;
    assert( vert->param[0] <= uarray.uarray[gv.gparam[0]]  );

    if( gv.prevu() <= top.ustart ) {
        for( ; vert; vert = left.prev() ) {
            output( vert );
            backend.swaptmesh();
        }
    } else while( 1 ) {
        if( vert->param[0] > uarray.uarray[gv.gparam[0]] ){
            output( vert );
            backend.swaptmesh();
            vert = left.prev();
            if( vert == NULL ) break;
        } else {
            backend.swaptmesh();
            output( gv );
            if( gv.prevu() == top.ustart ) {
                for( ; vert; vert = left.prev() ) {
                    output( vert );
                    backend.swaptmesh();
                }
                break;
            }
        }
    }
}

void 
CoveAndTiler::coveLowerRight( void )
{
    GridVertex bgv( bot.uend, bot.vindex );
    GridVertex gv( bot.uend, top.vindex );

    right.last();
    backend.bgntmesh( "coveLowerRight" );       
    output( bgv );
    output( right.prev() );
    output( gv );
    backend.swaptmesh();
        coveLR();
    backend.endtmesh( );
}

void
CoveAndTiler::coveLowerRightNoGrid( TrimVertex* tr )
{
    backend.bgntmesh( "coveLowerRIght" );
    output( right.last() ); 
    output( right.prev() );
    output( tr );
    backend.swaptmesh();
        coveLR();
    backend.endtmesh();
}

void 
CoveAndTiler::coveLR( )
{
    GridVertex gv( bot.uend, top.vindex );
    TrimVertex *vert = right.prev();
    if( vert == NULL ) return;
    assert( vert->param[0] >= uarray.uarray[gv.gparam[0]]  );

    if( gv.nextu() >= top.uend ) {
        for( ; vert; vert = right.prev() ) {
            backend.swaptmesh();
            output( vert );
        }
    } else while( 1 ) {
        if( vert->param[0] < uarray.uarray[gv.gparam[0]]  ) {
            backend.swaptmesh();
            output( vert );
            vert = right.prev();
            if( vert == NULL ) break;
        } else {
            output( gv );
            backend.swaptmesh();
            if( gv.nextu() == top.uend ) {
                for( ; vert; vert = right.prev() ) {
                    backend.swaptmesh();
                    output( vert );
                }
                break;
            }
        }
    }
}

