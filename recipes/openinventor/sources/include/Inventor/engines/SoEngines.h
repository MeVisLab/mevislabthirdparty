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
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file #includes files that define ALL standard Inventor
 |      engine classes. It is provided as a convenience.
 |
 |   Author(s)          : Paul S. Strauss, Gavin Bell, Ronen Barzel
 |
 |   Notes:
 |      Try not to include this file; use only those specific ones
 |      that you actually need.
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ENGINES_
#define  _SO_ENGINES_

#include <Inventor/engines/SoBoolOperation.h>
#include <Inventor/engines/SoCalculator.h>
#include <Inventor/engines/SoCompose.h>
#include <Inventor/engines/SoComputeBoundingBox.h>
#include <Inventor/engines/SoConcatenate.h>
#include <Inventor/engines/SoCounter.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/engines/SoFieldConverter.h>
#include <Inventor/engines/SoGate.h>
#include <Inventor/engines/SoInterpolate.h>
#include <Inventor/engines/SoOnOff.h>
#include <Inventor/engines/SoOneShot.h>
#include <Inventor/engines/SoSelectOne.h>
#include <Inventor/engines/SoTimeCounter.h>
#include <Inventor/engines/SoTransformVec3f.h>
#include <Inventor/engines/SoTriggerAny.h>

#endif /* _SO_ENGINES_ */
