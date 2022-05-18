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

#include <stdlib.h>
#include <stdio.h>
#include <Inventor/SoDB.h>
#include <Inventor/Xt/SoXt.h>
#include <Inventor/nodes/SoSeparator.h>
#include "SceneTumble.h"

int
main(int argc, char *argv[])
{
   if (argc != 2) {
      fprintf(stderr, "Usage: %s <filename.iv>\n", argv[0]);
      exit(1);
   }
   
   Widget window = SoXt::init(argv[0]);

   SoInput in;
   SoSeparator *scene = NULL;
   if (in.openFile(argv[1])) {
      scene = SoDB::readAll(&in);
      in.closeFile();
   }
   
   if (scene == NULL) {
      fprintf(stderr, "Sorry, could not read %s\n", argv[1]);;
      exit(1);
   }
   
   SceneTumble *tumbler = new SceneTumble(window);
   tumbler->setSceneGraph(scene);
   tumbler->show();
   SoXt::show(window); // do this AFTER showing the GLX widget
   SoXt::mainLoop();
}
