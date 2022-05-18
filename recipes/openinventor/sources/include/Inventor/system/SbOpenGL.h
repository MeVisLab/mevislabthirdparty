/*
 *
 *  Copyright (C) 2011 MeVis Medical Solutions AG  All Rights Reserved.
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
 *  Contact information: MeVis, Center for Medical Diagnostic Systems and
 *  Visualization GmbH, Universitätsallee 29, D-28359 Bremen, GERMANY, or:
 *
 *  http://www.mevis.de
 *
 */

/*
 Author: Florian Link
 Date:   09-2011
*/

#ifndef _SB_OPENGL_
#define _SB_OPENGL_

#include <Inventor/system/SbSystem.h>

//! include the glew header, which allows to access the whole OpenGL and extensions API
//! without using native windows or unix headers
#include <GL/glew.h>

#include <vector>

class INVENTOR_API SbOpenGL
{
public:
  static void init();
};

//! a class that offers static wrappers around OpenGL functions
class INVENTOR_API SbGL
{
public:
  static void glColor4ubv (const GLubyte *v);

  static void glMaterialfv (GLenum face, GLenum pname, const GLfloat *params);
  static void glMaterialf (GLenum face, GLenum pname, GLfloat param);

  static void glLoadIdentity (void);
  static void glLoadMatrixf (const GLfloat *m);
  static void glMultMatrixf (const GLfloat *m);
  static void glMatrixMode (GLenum mode);
  static void glScalef (GLfloat x, GLfloat y, GLfloat z);
  static void glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
  static void glTranslatef (GLfloat x, GLfloat y, GLfloat z);
  static void glPushMatrix (void);
  static void glPopMatrix (void);

  static void glLightf (GLenum light, GLenum pname, GLfloat param);
  static void glLightfv (GLenum light, GLenum pname, const GLfloat *params);

  static void glClipPlane (GLenum plane, const GLdouble *equation);

  static unsigned int projectionMatrixId();
  static unsigned int modelViewMatrixId();
  static unsigned int textureMatrixId();
  static unsigned int materialId();
  static unsigned int lightId();
  static unsigned int clipPlaneId();

private:
  static unsigned int _uniqueId;

  static GLenum _matrixMode;

  static std::vector<unsigned int> _matrixIdStack[3];
  static unsigned int _matrixId[3];

  static unsigned int _materialId;
  static unsigned int _lightId;
  static unsigned int _clipPlaneId;

};

#endif
