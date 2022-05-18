/******************************************************************************/
/* The C Clustering Library for cDNA microarray data.
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

double find_closest_pair(int n, double** distmatrix, int* ip, int* jp);

void pslcluster (int nfibers, double** distmatrix, int** result, double *linkdist);
void pclcluster (int nrows, int ncolumns, double** data,
                 double* weight, double** distmatrix, char dist, int transpose,
                 int** result, double* linkdist);


void pmlcluster (int nfibers, double** distmatrix, int** result, double* linkdist);
void palcluster (int nfibers, double** distmatrix, int** result, double* linkdist);

//supplementary routines

//*********************aus dem Header****************************************
void cuttree (int nfibers, int** tree, int nclusters, int* clusterid);

/* ******************************************************************** */

}