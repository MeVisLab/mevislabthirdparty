// **InsertLicense** code
//----------------------------------------------------------------------------------
//! metric functions used for fiber clustering
/*!
// \file    mlMetricFunctions.cpp
// \author  Peter Ledochowitsch, Philip Bittihn, Jan Klein
// \date    02/2006
*/


#include "clMetricFunctions.h"

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

/* ********************************begin metric function************************************* */


double euclid (int n, double** data1, double** data2,
  double* weight, int index1, int index2, int transpose)

/*
Purpose
=======

The euclid routine calculates the weighted Euclidean distance between two
rows or columns in a matrix.

Arguments
=========

n      (input) int
The number of elements in a row or column. If transpose==0, then n is the number
of columns; otherwise, n is the number of rows.

data1  (input) double array
The data array containing the first vector.

data2  (input) double array
The data array containing the second vector.

mask1  (input) int array
This array which elements in data1 are missing. If mask1[i][j]==0, then
data1[i][j] is missing.

mask2  (input) int array
This array which elements in data2 are missing. If mask2[i][j]==0, then
data2[i][j] is missing.

weight (input) double[n]
The weights that are used to calculate the distance.

index1     (input) int
Index of the first row or column.

index2     (input) int
Index of the second row or column.

transpose (input) int
If transpose==0, the distance between two rows in the matrix is calculated.
Otherwise, the distance between two columns in the matrix is calculated.

============================================================================
*/
{ 
  double result = 0.;
  double tweight = 0;
  int i;
  if (transpose==0) /* Calculate the distance between two rows */
  { 
    for (i = 0; i < n; i++)
    {
       double term = data1[index1][i] - data2[index2][i];
        result += weight[i]*term*term;
        tweight += weight[i];

    }
  }
  else
  { 
    for (i = 0; i < n; i++)
    {
       double term = data1[i][index1] - data2[i][index2];
        result += weight[i]*term*term;
        tweight += weight[i];

    }
  }
  if (!tweight) 
  {
    return 0; /* usually due to empty clusters */
  }
  result /= tweight;
  return result;
}

/* ********************************************************************* */


double cityblock (int n, double** data1, double** data2,
double* weight, int index1, int index2, int transpose)

/*
Purpose
=======

The cityblock routine calculates the weighted "City Block" distance between
two rows or columns in a matrix. City Block distance is defined as the
absolute value of X1-X2 plus the absolute value of Y1-Y2 plus..., which is
equivalent to taking an "up and over" path.

Arguments
=========

n      (input) int
The number of elements in a row or column. If transpose==0, then n is the number
of columns; otherwise, n is the number of rows.

data1  (input) double array
The data array containing the first vector.

data2  (input) double array
The data array containing the second vector.

mask1  (input) int array
This array which elements in data1 are missing. If mask1[i][j]==0, then
data1[i][j] is missing.

mask2  (input) int array
This array which elements in data2 are missing. If mask2[i][j]==0, then
data2[i][j] is missing.

weight (input) double[n]
The weights that are used to calculate the distance.

index1     (input) int
Index of the first row or column.

index2     (input) int
Index of the second row or column.

transpose (input) int
If transpose==0, the distance between two rows in the matrix is calculated.
Otherwise, the distance between two columns in the matrix is calculated.

============================================================================ */
{ 
  double result = 0.;
  double tweight = 0;
  int i;
  if (transpose==0) /* Calculate the distance between two rows */
  { 
    for (i = 0; i < n; i++)
    {
       double term = data1[index1][i] - data2[index2][i];
       result = result + weight[i]*fabs(term);
       tweight += weight[i];
    }
  }
  else
  { 
    for (i = 0; i < n; i++)
    {
       double term = data1[i][index1] - data2[i][index2];
       result = result + weight[i]*fabs(term);
       tweight += weight[i];
    }
  }
  if (!tweight) 
  {
    return 0; /* usually due to empty clusters */
  }
  result /= tweight;
  return result;
}

/* ********************************************************************* */


double correlation (int n, double** data1, double** data2,  double* weight, int index1, int index2, int transpose)
/*
Purpose
=======

The correlation routine calculates the weighted Pearson distance between two
rows or columns in a matrix. We define the Pearson distance as one minus the
Pearson correlation.
This definition yields a semi-metric: d(a,b) >= 0, and d(a,b) = 0 iff a = b.
but the triangular inequality d(a,b) + d(b,c) >= d(a,c) does not hold
(e.g., choose b = a + c).

Arguments
=========

n      (input) int
The number of elements in a row or column. If transpose==0, then n is the number
of columns; otherwise, n is the number of rows.

data1  (input) double array
The data array containing the first vector.

data2  (input) double array
The data array containing the second vector.

mask1  (input) int array
This array which elements in data1 are missing. If mask1[i][j]==0, then
data1[i][j] is missing.

mask2  (input) int array
This array which elements in data2 are missing. If mask2[i][j]==0, then
data2[i][j] is missing.

weight (input) double[n]
The weights that are used to calculate the distance.

index1     (input) int
Index of the first row or column.

index2     (input) int
Index of the second row or column.

transpose (input) int
If transpose==0, the distance between two rows in the matrix is calculated.
Otherwise, the distance between two columns in the matrix is calculated.
============================================================================
*/
{ 
  double result = 0.;
  double sum1 = 0.;
  double sum2 = 0.;
  double denom1 = 0.;
  double denom2 = 0.;
  double tweight = 0.;
  if (transpose==0) /* Calculate the distance between two rows */
  { 
    int i;
    for (i = 0; i < n; i++)
    {
       double term1 = data1[index1][i];
       double term2 = data2[index2][i];
       double w = weight[i];
       sum1 += w*term1;
       sum2 += w*term2;
       result += w*term1*term2;
       denom1 += w*term1*term1;
       denom2 += w*term2*term2;
       tweight += w;

    }
  }
  else
  { 
    int i;
    for (i = 0; i < n; i++)
    {
        double term1 = data1[i][index1];
        double term2 = data2[i][index2];
        double w = weight[i];
        sum1 += w*term1;
        sum2 += w*term2;
        result += w*term1*term2;
        denom1 += w*term1*term1;
        denom2 += w*term2*term2;
        tweight += w;

    }
  }
  if (!tweight) 
  {
    return 0; /* usually due to empty clusters */
  }
  result -= sum1 * sum2 / tweight;
  denom1 -= sum1 * sum1 / tweight;
  denom2 -= sum2 * sum2 / tweight;
  if (denom1 <= 0) 
  {
    return 1; /* include '<' to deal with roundoff errors */
  }
  if (denom2 <= 0) 
  {
    return 1; /* include '<' to deal with roundoff errors */
  }
  result = result / sqrt(denom1*denom2);
  result = 1. - result;
  return result;
}

/* ********************************************************************* */


double acorrelation (int n, double** data1, double** data2, double* weight, int index1, int index2, int transpose)
/*
Purpose
=======

The acorrelation routine calculates the weighted Pearson distance between two
rows or columns, using the absolute value of the correlation.
This definition yields a semi-metric: d(a,b) >= 0, and d(a,b) = 0 iff a = b.
but the triangular inequality d(a,b) + d(b,c) >= d(a,c) does not hold
(e.g., choose b = a + c).

Arguments
=========

n      (input) int
The number of elements in a row or column. If transpose==0, then n is the number
of columns; otherwise, n is the number of rows.

data1  (input) double array
The data array containing the first vector.

data2  (input) double array
The data array containing the second vector.

mask1  (input) int array
This array which elements in data1 are missing. If mask1[i][j]==0, then
data1[i][j] is missing.

mask2  (input) int array
This array which elements in data2 are missing. If mask2[i][j]==0, then
data2[i][j] is missing.

weight (input) double[n]
The weights that are used to calculate the distance.

index1     (input) int
Index of the first row or column.

index2     (input) int
Index of the second row or column.

transpose (input) int
If transpose==0, the distance between two rows in the matrix is calculated.
Otherwise, the distance between two columns in the matrix is calculated.
============================================================================
*/
{ double result = 0.;
  double sum1 = 0.;
  double sum2 = 0.;
  double denom1 = 0.;
  double denom2 = 0.;
  double tweight = 0.;
  if (transpose==0) /* Calculate the distance between two rows */
  { 
    int i;
    for (i = 0; i < n; i++)
    {
        double term1 = data1[index1][i];
        double term2 = data2[index2][i];
        double w = weight[i];
        sum1 += w*term1;
        sum2 += w*term2;
        result += w*term1*term2;
        denom1 += w*term1*term1;
        denom2 += w*term2*term2;
        tweight += w;
    }
  }
  else
  { 
    int i;
    for (i = 0; i < n; i++)
    {
        double term1 = data1[i][index1];
        double term2 = data2[i][index2];
        double w = weight[i];
        sum1 += w*term1;
        sum2 += w*term2;
        result += w*term1*term2;
        denom1 += w*term1*term1;
        denom2 += w*term2*term2;
        tweight += w;
    }
  }
  if (!tweight) 
  {
    return 0; /* usually due to empty clusters */
  }
  result -= sum1 * sum2 / tweight;
  denom1 -= sum1 * sum1 / tweight;
  denom2 -= sum2 * sum2 / tweight;
  if (denom1 <= 0) 
  {
    return 1; /* include '<' to deal with roundoff errors */
  }
  if (denom2 <= 0) 
  { 
    return 1; /* include '<' to deal with roundoff errors */
  }
  result = fabs(result) / sqrt(denom1*denom2);
  result = 1. - result;
  return result;
}

/* ********************************************************************* */


double ucorrelation (int n, double** data1, double** data2, double* weight, int index1, int index2, int transpose)
/*
Purpose
=======

The ucorrelation routine calculates the weighted Pearson distance between two
rows or columns, using the uncentered version of the Pearson correlation. In the
uncentered Pearson correlation, a zero mean is used for both vectors even if
the actual mean is nonzero.
This definition yields a semi-metric: d(a,b) >= 0, and d(a,b) = 0 iff a = b.
but the triangular inequality d(a,b) + d(b,c) >= d(a,c) does not hold
(e.g., choose b = a + c).

Arguments
=========

n      (input) int
The number of elements in a row or column. If transpose==0, then n is the number
of columns; otherwise, n is the number of rows.

data1  (input) double array
The data array containing the first vector.

data2  (input) double array
The data array containing the second vector.

mask1  (input) int array
This array which elements in data1 are missing. If mask1[i][j]==0, then
data1[i][j] is missing.

mask2  (input) int array
This array which elements in data2 are missing. If mask2[i][j]==0, then
data2[i][j] is missing.

weight (input) double[n]
The weights that are used to calculate the distance.

index1     (input) int
Index of the first row or column.

index2     (input) int
Index of the second row or column.

transpose (input) int
If transpose==0, the distance between two rows in the matrix is calculated.
Otherwise, the distance between two columns in the matrix is calculated.
============================================================================
*/
{ 
  double result = 0.;
  double denom1 = 0.;
  double denom2 = 0.;

  if (transpose==0) /* Calculate the distance between two rows */
  { int i;
    for (i = 0; i < n; i++)
    {
        double term1 = data1[index1][i];
        double term2 = data2[index2][i];
        double w = weight[i];
        result += w*term1*term2;
        denom1 += w*term1*term1;
        denom2 += w*term2*term2;
    }
  }
  else
  { int i;
    for (i = 0; i < n; i++)
    {
        double term1 = data1[i][index1];
        double term2 = data2[i][index2];
        double w = weight[i];
        result += w*term1*term2;
        denom1 += w*term1*term1;
        denom2 += w*term2*term2;
    }
  }

  if (denom1==0.) 
  {
    return 1.;
  }
  if (denom2==0.) 
  {
    return 1.;
  }
  result = result / sqrt(denom1*denom2);
  result = 1. - result;
  return result;
}

/* ********************************************************************* */


double uacorrelation (int n, double** data1, double** data2, double* weight, int index1, int index2, int transpose)
/*
Purpose
=======

The uacorrelation routine calculates the weighted Pearson distance between two
rows or columns, using the absolute value of the uncentered version of the
Pearson correlation. In the uncentered Pearson correlation, a zero mean is used
for both vectors even if the actual mean is nonzero.
This definition yields a semi-metric: d(a,b) >= 0, and d(a,b) = 0 iff a = b.
but the triangular inequality d(a,b) + d(b,c) >= d(a,c) does not hold
(e.g., choose b = a + c).

Arguments
=========

n      (input) int
The number of elements in a row or column. If transpose==0, then n is the number
of columns; otherwise, n is the number of rows.

data1  (input) double array
The data array containing the first vector.

data2  (input) double array
The data array containing the second vector.

mask1  (input) int array
This array which elements in data1 are missing. If mask1[i][j]==0, then
data1[i][j] is missing.

mask2  (input) int array
This array which elements in data2 are missing. If mask2[i][j]==0, then
data2[i][j] is missing.

weight (input) double[n]
The weights that are used to calculate the distance.

index1     (input) int
Index of the first row or column.

index2     (input) int
Index of the second row or column.

transpose (input) int
If transpose==0, the distance between two rows in the matrix is calculated.
Otherwise, the distance between two columns in the matrix is calculated.
============================================================================
*/
{ 
  double result = 0.;
  double denom1 = 0.;
  double denom2 = 0.;


  if (transpose==0) /* Calculate the distance between two rows */
  { 
    int i;
    for (i = 0; i < n; i++)
    {
        double term1 = data1[index1][i];
        double term2 = data2[index2][i];
        double w = weight[i];
        result += w*term1*term2;
        denom1 += w*term1*term1;
        denom2 += w*term2*term2;
    }
  }
  else
  { 
    int i;
    for (i = 0; i < n; i++)
    {
        double term1 = data1[i][index1];
        double term2 = data2[i][index2];
        double w = weight[i];
        result += w*term1*term2;
        denom1 += w*term1*term1;
        denom2 += w*term2*term2;
    }
  }
  if (denom1==0.)
  { 
    return 1.;
  }
  if (denom2==0.) 
  {
    return 1.;
  }
  result = fabs(result) / sqrt(denom1*denom2);
  result = 1. - result;
  return result;
}

/* **********************************************************************/


double spearman (int n, double** data1, double** data2, double* weight, int index1, int index2, int transpose)
/*
Purpose
=======

The spearman routine calculates the Spearman distance between two rows or
columns. The Spearman distance is defined as one minus the Spearman rank
correlation.

Arguments
=========

n      (input) int
The number of elements in a row or column. If transpose==0, then n is the number
of columns; otherwise, n is the number of rows.

data1  (input) double array
The data array containing the first vector.

data2  (input) double array
The data array containing the second vector.

mask1  (input) int array
This array which elements in data1 are missing. If mask1[i][j]==0, then
data1[i][j] is missing.

mask2  (input) int array
This array which elements in data2 are missing. If mask2[i][j]==0, then
data2[i][j] is missing.

weight (input) double[n]
These weights are ignored, but included for consistency with other distance
measures.

index1     (input) int
Index of the first row or column.

index2     (input) int
Index of the second row or column.

transpose (input) int
If transpose==0, the distance between two rows in the matrix is calculated.
Otherwise, the distance between two columns in the matrix is calculated.
============================================================================
*/
{ 
  weight=0; // These weights are ignored, but included for consistency with other distance measures.
  
  double* rank1;
  double* rank2;
  double result = 0.;
  double denom1 = 0.;
  double denom2 = 0.;
  double avgrank;
  double* tdata1 = (double*) malloc(n*sizeof(double));
  double* tdata2 = (double*) malloc(n*sizeof(double));
  int i;
  int m = 0;
  if (transpose==0)
  { 
    for (i = 0; i < n; i++)
    {
        tdata1[m] = data1[index1][i];
        tdata2[m] = data2[index2][i];
        m++;
    }
  }
  else
  { 
    for (i = 0; i < n; i++)
    {
        tdata1[m] = data1[i][index1];
        tdata2[m] = data2[i][index2];
        m++;
    }
  }
  if (m==0) 
  {
    return 0;
  }
  rank1 = (double*) malloc(m*sizeof(double));
  rank2 = (double*) malloc(m*sizeof(double));
  getrank(m, tdata1, rank1);
  free(tdata1);
  getrank(m, tdata2, rank2);
  free(tdata2);
  avgrank = 0.5*(m-1); /* Average rank */
  for (i = 0; i < m; i++)
  { 
    double value1 = rank1[i];
    double value2 = rank2[i];
    result += value1 * value2;
    denom1 += value1 * value1;
    denom2 += value2 * value2;
  }
  /* Note: denom1 and denom2 cannot be calculated directly from the number
   * of elements. If two elements have the same rank, the squared sum of
   * their ranks will change.
   */
  free(rank1);
  free(rank2);
  result /= m;
  denom1 /= m;
  denom2 /= m;
  result -= avgrank * avgrank;
  denom1 -= avgrank * avgrank;
  denom2 -= avgrank * avgrank;
  result = result / sqrt(denom1*denom2);
  result = 1. - result;
  return result;
}

/* *********************************************************************  */


double kendall (int n, double** data1, double** data2,
  double* weight, int index1, int index2, int transpose)
/*
Purpose
=======

The kendall routine calculates the Kendall distance between two
rows or columns. The Kendall distance is defined as one minus Kendall's tau.

Arguments
=========

n      (input) int
The number of elements in a row or column. If transpose==0, then n is the number
of columns; otherwise, n is the number of rows.

data1  (input) double array
The data array containing the first vector.

data2  (input) double array
The data array containing the second vector.

mask1  (input) int array
This array which elements in data1 are missing. If mask1[i][j]==0, then
data1[i][j] is missing.

mask2  (input) int array
This array which elements in data2 are missing. If mask2[i][j]==0, then
data2[i][j] is missing.

weight (input) double[n]
These weights are ignored, but included for consistency with other distance
measures.

index1     (input) int
Index of the first row or column.

index2     (input) int
Index of the second row or column.

transpose (input) int
If transpose==0, the distance between two rows in the matrix is calculated.
Otherwise, the distance between two columns in the matrix is calculated.
============================================================================
*/
{ 
  int con = 0;
  int dis = 0;
  int exx = 0;
  int exy = 0;

  weight=0; // These weights are ignored, but included for consistency with other distance measures.

  double denomx;
  double denomy;
  double tau;
  int i, j;
  if (transpose==0)
  { 
    for (i = 0; i < n; i++)
    {
       for (j = 0; j < i; j++)
        {
           double x1 = data1[index1][i];
            double x2 = data1[index1][j];
            double y1 = data2[index2][i];
            double y2 = data2[index2][j];
            if (x1 < x2 && y1 < y2) con++;
            if (x1 > x2 && y1 > y2) con++;
            if (x1 < x2 && y1 > y2) dis++;
            if (x1 > x2 && y1 < y2) dis++;
            if (x1 == x2 && y1 != y2) exx++;
            if (x1 != x2 && y1 == y2) exy++;
        }
    }
  }
  else
  { 
    for (i = 0; i < n; i++)
    {
       for (j = 0; j < i; j++)
        {
            double x1 = data1[i][index1];
            double x2 = data1[j][index1];
            double y1 = data2[i][index2];
            double y2 = data2[j][index2];
            if (x1 < x2 && y1 < y2) con++;
            if (x1 > x2 && y1 > y2) con++;
            if (x1 < x2 && y1 > y2) dis++;
            if (x1 > x2 && y1 < y2) dis++;
            if (x1 == x2 && y1 != y2) exx++;
            if (x1 != x2 && y1 == y2) exy++;
        }
    }
  }

  denomx = con + dis + exx;
  denomy = con + dis + exy;
  if (denomx==0) 
  {
    return 1;
  }
  if (denomy==0) 
  {
    return 1;
  }
  tau = (con-dis)/sqrt(denomx*denomy);
  return 1.-tau;
}




//***************************************************distance functions*********end




/* ****************************set metric (pointer to function!!!)************************  */


void setmetric (char dist,
  double (**metric)
    (int,double**,double**, double*,int,int,int) )
{ 
  switch(dist)
  { 
    case ('e'): *metric = &euclid; break;
    case ('b'): *metric = &cityblock; break;
    case ('c'): *metric = &correlation; break;
    case ('a'): *metric = &acorrelation; break;
    case ('u'): *metric = &ucorrelation; break;
    case ('x'): *metric = &uacorrelation; break;
    case ('s'): *metric = &spearman; break;
    case ('k'): *metric = &kendall; break;
    default: *metric = &euclid; break;
  }
  return;
}

/* *********************************************************************  */

//*****************distance matrix routine*********************************
double** distancematrix (int nrows, int ncolumns, double** data, double* weights, char dist, int transpose)

/*
Purpose
=======

The distancematrix routine calculates the distance matrix between genes or
microarrays using their measured gene expression data. Several distance measures
can be used. The routine returns a pointer to a ragged array containing the
distances between the genes. As the distance matrix is symmetric, with zeros on
the diagonal, only the lower triangular half of the distance matrix is saved.
The distancematrix routine allocates space for the distance matrix. If the
parameter transpose is set to a nonzero value, the distances between the columns
(microarrays) are calculated, otherwise distances between the rows (genes) are
calculated.
If sufficient space in memory cannot be allocated to store the distance matrix,
the routine returns a NULL pointer, and all memory allocated so far for the
distance matrix is freed.


Arguments
=========

nrows      (input) int
The number of rows in the gene expression data matrix (i.e., the number of
genes)

ncolumns   (input) int
The number of columns in the gene expression data matrix (i.e., the number of
microarrays)

data       (input) double[nrows][ncolumns]
The array containing the gene expression data.

mask       (input) int[nrows][ncolumns]
This array shows which data values are missing. If
mask(i,j) == 0, then data(i,j) is missing.

weight (input) double[n]
The weights that are used to calculate the distance. The length of this vector
is equal to the number of columns if the distances between genes are calculated,
or the number of rows if the distances between microarrays are calculated.

dist       (input) char
Defines which distance measure is used, as given by the table:
dist=='e': Euclidean distance
dist=='b': City-block distance
dist=='c': correlation
dist=='a': absolute value of the correlation
dist=='u': uncentered correlation
dist=='x': absolute uncentered correlation
dist=='s': Spearman's rank correlation
dist=='k': Kendall's tau
For other values of dist, the default (Euclidean distance) is used.

transpose  (input) int
If transpose is equal to zero, the distances between the rows is
calculated. Otherwise, the distances between the columns is calculated.
The former is needed when genes are being clustered; the latter is used
when microarrays are being clustered.

========================================================================
*/
{ 
  /* First determine the size of the distance matrix */
  const int n = (transpose==0) ? nrows : ncolumns;
  const int ndata = (transpose==0) ? ncolumns : nrows;
  int i,j;
  double** matrix;
  double (*metric)
    (int,double**,double**,double[],int,int,int);

  if (n < 2) 
  {
    return NULL;
  }

  /* Set up the ragged array */
  matrix = (double**) malloc(n*sizeof(double*));
  if(matrix==NULL) 
  {
    return NULL; /* Not enough memory available */
  }
  matrix[0] = NULL;
  /* The zeroth row has zero columns. We allocate it anyway for convenience.*/
  for (i = 1; i < n; i++)
  { 
    matrix[i] = (double*) malloc(i*sizeof(double));
    if (matrix[i]==NULL) 
    {
      break; /* Not enough memory available */
    }
  }
  if (i < n) /* break condition encountered */
  { 
    j = i;
    for (i = 1; i < j; i++) 
    {
      free(matrix[i]);
    }
    return NULL;
  }

  /* Set the metric function as indicated by dist */
  setmetric (dist, &metric);

  /* Calculate the distances and save them in the ragged array */
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < i; j++)
    {
      matrix[i][j]=metric(ndata,data,data,weights,i,j,transpose);
    }
  }

  return matrix;
}


/* ------------------calcilates rank----------------------------------- */


void getrank (int n, double data[], double rank[])
/* Calculates the ranks of the elements in the array data. Two elements with the
 * same value get the same rank, equal to the average of the ranks had the
 * elements different values.
 */
{ 
  int i;
  int* index = (int*) malloc(n*sizeof(int));
  /* Call sort to get an index table */
  sort (n, data, index);
  /* Build a rank table */
  for (i = 0; i < n; i++) 
  {
    rank[index[i]] = i;
  }
  /* Fix for equal ranks */
  i = 0;
  while (i < n)
  { 
    int m;
    double value = data[index[i]];
    int j = i + 1;
    while (j < n && data[index[j]] == value) 
    {
      j++;
    }
    m = j - i; /* number of equal ranks found */
    value = rank[index[i]] + (m-1)/2.;
    for (j = i; j < i + m; j++) 
    {
      rank[index[j]] = value;
    }
    i += m;
  }
  free (index);
  return;
}

/* ---------------------------------------------------------------------- */

/*----------------------sorts data--------------------------- */

void sort(int n, double data[], int index[])
/* Sets up an index table given the data, such that data[index[]] is in
 * increasing order. Sorting is done on the pointers, from which the indeces
 * are recalculated. The array data is unchanged.
 */
{ 
  if (n>0)
  {
      int i=0;
      double** p = (double**)malloc(n*sizeof(double*));
      double* start = data;
      for (i = 0; i < n; i++) 
      {
        p[i] = &(data[i]);
      }
      qsort(p, n, sizeof(double*), compare);
      for (i = 0; i < n; i++) 
      {
        index[i] = (int)(p[i]-start);
      }
      free(p);
  }
}

/* ---------------------------------------------------------------------- */

int compare(const void* a, const void* b)
/* Helper function for sort. Previously, this was a nested function under sort,
 * which is not allowed under ANSI C.
 */
{ 
  double term1 = *(*(double**)a);
  double term2 = *(*(double**)b);
  if (term1 < term2) 
  {
    return -1;
  }
  if (term1 > term2) 
  {
    return +1;
  }
  return 0;
}

