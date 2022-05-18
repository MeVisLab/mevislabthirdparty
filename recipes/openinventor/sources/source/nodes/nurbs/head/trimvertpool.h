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

#ifndef __glutrimvertpool_h_
#define __glutrimvertpool_h_

#include "../SoAddPrefix.h"
/*
 * trimvertexpool.h - $Revision: 1.1.1.1 $
 */

#include "bufpool.h"

#ifdef _MSC_VER
struct TrimVertex;
#else
class TrimVertex;
#endif

#define INIT_VERTLISTSIZE  200

class INVENTOR_API TrimVertexPool {
public:
                        TrimVertexPool( void );
                        ~TrimVertexPool( void );
    void                clear( void );
    TrimVertex *        get( int );
private:
    Pool                pool;
    TrimVertex **       vlist;
    int                 nextvlistslot;
    int                 vlistsize;
};
#endif /* __glutrimvertpool_h_ */
