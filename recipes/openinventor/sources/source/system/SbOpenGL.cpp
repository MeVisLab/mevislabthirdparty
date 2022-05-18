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

#include <Inventor/system/SbOpenGL.h>
#include <Inventor/errors/SoError.h>

void SbOpenGL::init() {
  static bool initialized = false;
  if (!initialized) {
    GLenum err = glewInit();
    if (GLEW_OK != err) {
      // Problem: glewInit failed, something is seriously wrong.
      SoError::post("GLEW init failed: %s", glewGetErrorString(err));
    } else {
      initialized = true;
    }
  }
}

unsigned int SbGL::_uniqueId = 1;
GLenum SbGL::_matrixMode = 0; // matrix mode is calculated by mode - GL_MODELVIEW, so _matrixMode = 0 means GL_MODELVIEW.
unsigned int SbGL::_materialId = 0;
unsigned int SbGL::_lightId = 0;
unsigned int SbGL::_clipPlaneId = 0;

unsigned int SbGL::_matrixId[3] = {0,0,0};
std::vector<unsigned int> SbGL::_matrixIdStack[3];

void SbGL::glColor4ubv(const GLubyte *v)
{
  ::glColor4ubv(v);
}

void SbGL::glMaterialfv(GLenum face, GLenum pname, const GLfloat *params)
{
  if (pname != GL_DIFFUSE) {
    _materialId = _uniqueId++;
  }
  ::glMaterialfv(face,pname, params);
}

void SbGL::glMaterialf(GLenum face, GLenum pname, GLfloat param)
{
  if (pname != GL_DIFFUSE) {
    _materialId = _uniqueId++;
  }
  ::glMaterialf(face, pname, param);
}

void SbGL::glMatrixMode(GLenum mode)
{
  _matrixMode = mode - GL_MODELVIEW;
  ::glMatrixMode(mode);
}

void SbGL::glLoadIdentity(void)
{
  _matrixId[_matrixMode] = _uniqueId++;
  ::glLoadIdentity();
}

void SbGL::glLoadMatrixf(const GLfloat *m)
{
  _matrixId[_matrixMode] = _uniqueId++;
  ::glLoadMatrixf(m);
}

void SbGL::glMultMatrixf(const GLfloat *m)
{
  _matrixId[_matrixMode] = _uniqueId++;
  ::glMultMatrixf(m);
}

void SbGL::glScalef(GLfloat x, GLfloat y, GLfloat z)
{
  _matrixId[_matrixMode] = _uniqueId++;
  ::glScalef(x,y,z);
}

void SbGL::glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
  _matrixId[_matrixMode] = _uniqueId++;
  ::glRotatef(angle, x,y,z);
}

void SbGL::glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
  _matrixId[_matrixMode] = _uniqueId++;
  ::glTranslatef(x,y,z);
}

void SbGL::glPushMatrix(void)
{
  _matrixIdStack[_matrixMode].push_back(_matrixId[_matrixMode]);
  ::glPushMatrix();
}

void SbGL::glPopMatrix(void)
{
  if (!_matrixIdStack[_matrixMode].empty()) {
    _matrixId[_matrixMode] = _matrixIdStack[_matrixMode].back();
    _matrixIdStack[_matrixMode].pop_back();
  }
  else
  {
    SoError::post("pop matrix without matching push matrix: mode %d", _matrixMode);
  }
  ::glPopMatrix();
}

void SbGL::glLightf(GLenum light, GLenum pname, GLfloat param)
{
  _lightId = _uniqueId++;
  ::glLightf(light, pname, param);
}

void SbGL::glLightfv(GLenum light, GLenum pname, const GLfloat *params)
{
  _lightId = _uniqueId++;
  ::glLightfv(light, pname, params);
}

void SbGL::glClipPlane(GLenum plane, const GLdouble *equation)
{
  _clipPlaneId = _uniqueId++;
  ::glClipPlane(plane, equation);
}

unsigned int SbGL::projectionMatrixId()
{
  return _matrixId[GL_PROJECTION - GL_MODELVIEW];
}

unsigned int SbGL::modelViewMatrixId()
{
  return _matrixId[GL_MODELVIEW - GL_MODELVIEW];
}

unsigned int SbGL::textureMatrixId()
{
  return _matrixId[GL_TEXTURE - GL_MODELVIEW];
}

unsigned int SbGL::materialId()
{
  return _materialId;
}

unsigned int SbGL::lightId()
{
  return _lightId;
}

unsigned int SbGL::clipPlaneId()
{
  return _clipPlaneId;
}

