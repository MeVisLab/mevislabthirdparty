// **InsertLicense** code
//----------------------------------------------------------------------------------
//! Header file for library Self-Organizing Maps
/*!
// \file    mlSOM.h
// \author  Peter Ledochowitsch, Philip Bittihn, Jan Klein
// \date    02/2006
*/


//SOM := Self-Organizing Maps


/******************************************************************************/
/* The C Clustering Library for cDNA gene data.
 * Copyright (C) 2002 Michiel Jan Laurens de Hoon.
 *
 * This library was written at the Laboratory of DNA Information Analysis,
 * Human Genome Center, Institute of Medical Science, University of Tokyo,
 * 4-6-1 Shirokanedai, Minato-ku, Tokyo 108-8639, Japan.
 * Contact: mdehoon@c2b2.columbia.edu
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation with or without modifications and for any purpose and
 * without fee is hereby granted, provided that any copyright notices
 * appear in all copies and that both those copyright notices and this
 * permission notice appear in supporting documentation, and that the
 * names of the contributors or copyright holders not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific prior permission.
 * 
 * THE CONTRIBUTORS AND COPYRIGHT HOLDERS OF THIS SOFTWARE DISCLAIM ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL THE
 * CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT
 * OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOFTWARE.
 * 
 */

#pragma once

#include "clMetricFunctions.h"

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <iostream>

namespace cluster {

#ifndef min
#define min(x, y)   ((x) < (y) ? (x) : (y))
#endif
#ifndef max
#define max(x, y)   ((x) > (y) ? (x) : (y))
#endif


#ifndef CALL
# define CALL
#endif


void somcluster (int nrows, int ncolumns, double** data, 
double* weight, int transpose, int nxgrid, int nygrid,
double inittau, int niter, char dist, double*** celldata, int **clusterid);

}
