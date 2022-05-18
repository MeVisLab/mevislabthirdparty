/*
 *
 *  Copyright (C) 2010 MeVis Medical Solutions AG,  All Rights Reserved.
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
 *  Contact information: MeVis Medical Solutions AG
 *  Caroline-Herschel-Strasse 1, 28359 Bremen,  GERMANY, or:
 *
 *  http://www.mevis.de/
 *
 */

/*
 * Copyright (C) 2010 MeVis Medical Solutions AG
 *
 *   \file    SoQtSubDevice.h
 *   \author  Felix Ritter
 *   \date    12/2009
 */

#ifndef  _SO_QT_SUB_DEVICE_
#define  _SO_QT_SUB_DEVICE_

#include <Inventor/Qt/devices/SoQtDevice.h>


#define SO_QT_DEVICE_HEADER()                                       \
  public:                                                           \
    virtual SoType getTypeId() const override;                      \
    static SoType getClassTypeId() { return classTypeId; }          \
  private:                                                          \
    static SoType classTypeId;                                      \
    static void *createInstance()

#define SO_QT_DEVICE_SOURCE(className)                              \
  SoType className::classTypeId;                                    \
  SoType                                                            \
  className::getTypeId() const                                      \
  {                                                                 \
    return classTypeId;                                             \
  }                                                                 \
  void *                                                            \
  className::createInstance()                                       \
  {                                                                 \
    return (void *)(new className);                                 \
  }

#define SO_QT_DEVICE_INIT_CLASS(className,parentClass)              \
  classTypeId = SoType::createType(parentClass::getClassTypeId(),   \
                SO__QUOTE(className), &className::createInstance)


#endif /* _SO_QT_SUB_DEVICE_ */
