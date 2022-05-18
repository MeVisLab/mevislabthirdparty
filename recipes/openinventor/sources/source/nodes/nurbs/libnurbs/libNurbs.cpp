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
 * Copyright (C) 1990,91   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.2 $
 |
 |   Classes:
 |      Bunches of nurbs code
 |
 |   Author(s)          : Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include "../SoAddPrefix.h"
#include "arc.cpp"
#include "arcsorter.cpp"
#include "arctess.cpp"
#include "backend.cpp"
#include "basiccrveval.cpp"
#include "basicsurfeval.cpp"
#include "bin.cpp"
#include "bufpool.cpp"
#include "cachingeval.cpp"
#include "ccw.cpp"
#include "coveandtiler.cpp"
#include "curve.cpp"
#include "curvelist.cpp"
#include "curvesub.cpp"
#include "displaylist.cpp"
#include "flist.cpp"
#include "flistsorter.cpp"
#include "hull.cpp"
#include "intersect.cpp"
#include "knotvector.cpp"
#include "mapdesc.cpp"
#include "mapdescv.cpp"
#include "maplist.cpp"
#include "mesher.cpp"
#include "monotonizer.cpp"
#include "mycode.cpp"
#include "nurbsinterfac.cpp"
#include "nurbstess.cpp"
#include "patch.cpp"
#include "patchlist.cpp"
#include "quilt.cpp"
#include "reader.cpp"
#include "renderhints.cpp"
#include "slicer.cpp"
#include "sorter.cpp"
#include "splitarcs.cpp"
#include "subdivider.cpp"
#include "tobezier.cpp"
#include "trimline.cpp"
#include "trimregion.cpp"
#include "trimvertpool.cpp"
#include "uarray.cpp"
#include "varray.cpp"
#include "qsort.cpp"
