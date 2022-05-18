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

#ifndef __gluimports_h_
#define __gluimports_h_

#include "../SoAddPrefix.h"
/*
 * glimports.h - $Revision: 1.1.1.1 $
 */

#include <stdio.h>
#include <stdlib.h>

#include "mystdlib.h"
#include "mystdio.h"

/*
//! The new/delete operators have been disabled, since they replace new/delete in the whole OIV library
//! which is undesired.

inline void *
operator new( size_t s )
{
    void *p = malloc( s );
    if( p ) {
        return p;
    } else {
#ifndef NDEBUG
        dprintf( "malloc failed\n" );
#endif
        return p;
    }
}

inline void
operator delete( void *p )
{
    if( p ) free( p );
}
*/

#endif /* __gluimports_h_ */
