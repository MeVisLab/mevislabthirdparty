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
 * isocurveeval.h
 *
 * $Revision: 1.1.1.1 $
 */

#ifndef SO_NURBS_ISOCURVEEVAL
#define SO_NURBS_ISOCURVEEVAL

#include <Inventor/SbTypeDefs.h>

#include "types.h"

class _SoNurbsIsocurveEvaluator {
private:
    static const        int Comb[157];
    int                 Evaluation_order;
    int                 Evaluation_stride;
    double              Evaluation_param;
    double              Evaluation_nparam;
    double              Evaluation_order1;
    double              Evaluation_order2;

protected:
    unsigned int        Ch( unsigned int, unsigned int );
    void                init( int, int, REAL, REAL, REAL );
    void                evaluate( REAL *, REAL *, REAL *, REAL * );
};

#endif /* SO_NURBS_ISOCURVEEVAL */
