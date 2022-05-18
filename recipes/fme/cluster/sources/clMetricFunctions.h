/******************************************************************************/
/* The C Clustering Library for cDNA feature data.
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

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <float.h>

/******************************metric functions*****************************************/

double euclid (int n, double** data1, double** data2,
  double* weight, int index1, int index2, int transpose);

double cityblock (int n, double** data1, double** data2,
double* weight, int index1, int index2, int transpose);

double correlation (int n, double** data1, double** data2,  double* weight, int index1, int index2, int transpose);

double acorrelation (int n, double** data1, double** data2, double* weight, int index1, int index2, int transpose);

double ucorrelation (int n, double** data1, double** data2, double* weight, int index1, int index2, int transpose);

double uacorrelation (int n, double** data1, double** data2, double* weight, int index1, int index2, int transpose);

double spearman (int n, double** data1, double** data2, double* weight, int index1, int index2, int transpose);

double kendall (int n, double** data1, double** data2,
  double* weight, int index1, int index2, int transpose);

/***********end of metric functions**************************************/

void setmetric (char dist,double (**metric)(int,double**,double**,/*const*/ double*,int,int,int) );
//pointer to function!!!


//most important routine: calculates the distance matrix
double** distancematrix (int nrows, int ncolumns, double** data, double* weights, char dist, int transpose);


//*********supplementary routines***********************
void getrank (int n, double data[], double rank[]);

void sort(int n, double data[], int index[]);

int compare(const void* a, const void* b);

