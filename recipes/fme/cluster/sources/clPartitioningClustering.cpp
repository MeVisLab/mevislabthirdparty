// **InsertLicense** code
//----------------------------------------------------------------------------------
//! Implementation file for library PartitioningClustering
/*!
// \file    mlPartitioningClustering.cpp
// \author  Peter Ledochowitsch, Philip Bittihn, Jan Klein
// \date    02/2006
*/

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



#include "clPartitioningClustering.h"

#include "clRandom.h"

#include <algorithm> //std::min/std::max

namespace cluster {



/* ************************************************************************ */

double mean(int n, double x[])
{
  double result = 0.;
  int i;
  for (i = 0; i < n; i++)
  {
    result += x[i];
  }
  result /= n;
  return result;
}

/* ************************************************************************ */

double median (int n, double x[])
/*
Find the median of X(1), ... , X(N), using as much of the quicksort
algorithm as is needed to isolate it.
N.B. On exit, the array X is partially ordered.
Based on Alan J. Miller's median.f90 routine.
*/

{ int i, j;
  int nr = n / 2;
  int nl = nr - 1;
  int even = 0;
  /* hi & lo are position limits encompassing the median. */
  int lo = 0;
  int hi = n-1;

  if (n==2*nr) even = 1;
  if (n<3)
  {
    if (n<1)
    {
      return 0.;
    }
    if (n == 1)
    {
      return x[0];
    }
    return 0.5*(x[0]+x[1]);
  }

  /* Find median of 1st, middle & last values. */
  do
  { int loop;
    int mid = (lo + hi)/2;
    double result = x[mid];
    double xlo = x[lo];
    double xhi = x[hi];
    if (xhi<xlo)
    {
      double temp = xlo;
      xlo = xhi;
      xhi = temp;
    }
    if (result>xhi) {
      result = xhi;
    }
    else
    {
      if (result<xlo) {result = xlo;}
    }
    /* The basic quicksort algorithm to move all values <= the sort key (XMED)
     * to the left-hand end, and all higher values to the other end.
     */
    i = lo;
    j = hi;
    do
    {
      while (x[i]<result) i++;
      while (x[j]>result) j--;
      loop = 0;
      if (i<j)
      {
        double temp = x[i];
        x[i] = x[j];
        x[j] = temp;
        i++;
        j--;
        if (i<=j)
        {
          loop = 1;
        }
      }
    } while (loop); /* Decide which half the median is in. */

    if (even)
    {
      if (j==nl && i==nr)
      /* Special case, n even, j = n/2 & i = j + 1, so the median is
        * between the two halves of the series.   Find max. of the first
        * half & min. of the second half, then average.
        */
      {
        int k;
        double xmax = x[0];
        double xmin = x[n-1];
        for (k = lo; k <= j; k++) xmax = std::max(xmax, x[k]);
        for (k = i; k <= hi; k++) xmin = std::min(xmin,x[k]);
        return 0.5*(xmin + xmax);
      }
      if (j<nl)
      {
        lo = i;
      }
      if (i>nr)
      {
        hi = j;
      }
      if (i==j)
      {
        if (i==nl)
        {
          lo = nl;
        }
        if (j==nr)
        {
          hi = nr;
        }
      }
    }
    else
    {
      if (j<nr)
      {
        lo = i;
      }
      if (i>nr)
      {
        hi = j;
      }
      /* Test whether median has been isolated. */
      if (i==j && i==nr)
      {
        return result;
      }
    }
  }
  while (lo<hi-1);

  if (even)
  {
    return (0.5*(x[nl]+x[nr]));
  }
  if (x[lo]>x[hi])
  {
    double temp = x[lo];
    x[lo] = x[hi];
    x[hi] = temp;
  }
  return x[nr];
}

/* ********************************************************************** */
/* ---------------------------------------------------------------------- */

static
int equal_clusters(int n, int clusterids1[], int clusterids2[])
/*
This function checks if two k-means clustering solutions are equal to each
other. If equal, the function returns 1; otherwise, it returns 0.

n          (input) int
The size of the arrays clusterids1 and clusterids2, equal to the number of
items that were clustered.

clusterids1 (input) int[n]
An array containing n elements, indicating the number of the cluster to which
each of the items was assigned in the first clustering solution.

clusterids2 (input) int[n]
An array containing n elements, indicating the number of the cluster to which
each of the items was assigned in the second clustering solution.
*/
{
  int i;
  for (i = 0; i < n; i++)
  {
    if (clusterids1[i]!=clusterids2[i])
    {
      return 0;
    }
  }
  return 1;
}
/* ************************************************************************ */

void randomassign (int nclusters, int nelements, int* clusterid)
/*
Purpose
=======

The randomassign routine performs an initial random clustering, needed for
k-means or k-median clustering. Elements (fibers or features) are randomly
assigned to clusters. First, nclust elements are randomly chosen to be assigned
to the clusters 0..nclust-1 in order to guarantee that none of the clusters
are empty. The remaining elements are then randomly assigned to a cluster.

Arguments
=========

nclust  (input) int
The number of clusters.

nelements  (input) int
The number of elements to be clustered (i.e., the number of fibers or features
to be clustered).

clusterid  (output) int[nelements]
The cluster number to which an element was assigned.

External Functions:
ranlib: int genprm
============================================================================
*/

{
  int i;
  long* map = (long*) malloc(nelements*sizeof(long));
  /* Initialize mapping */
  for (i = 0; i < nelements; i++)
  {
    map[i] = i;
  }
  /* Create a random permutation of this mapping */
  genprm (map, nelements);

  /* Assign each of the first nclusters elements to a different cluster
   * to avoid empty clusters */
  for (i = 0; i < nclusters; i++)
  {
    clusterid[map[i]] = i;
  }

  /* Assign other elements randomly to a cluster */
  for (i = nclusters; i < nelements; i++)
  {
    clusterid[map[i]] = ignuin (0,nclusters-1);
  }
  free(map);
  return;
}

/* ********************************************************************* */
/* ********************************************************************* */

void getclustermean(int nclusters, int nrows, int ncolumns,
  double** data, int* clusterid, double** cdata, int transpose)
/*
Purpose
=======

The getclustermean routine calculates the cluster centroids, given to which
cluster each element belongs. The centroid is defined as the mean over all
elements for each dimension.

Arguments
=========

nclusters  (input) int
The number of clusters.

nrows     (input) int
The number of rows in the fiber  data matrix, equal to the number of
fibers.

ncolumns  (input) int
The number of columns in the fiber  data matrix, equal to the number of
features.

data       (input) double[nrows][ncolumns]
The array containing the fiber  data.

mask       (input) int[nrows][ncolumns]
This array shows which data values are missing. If mask[i][j]==0, then
data[i][j] is missing.

clusterid  (output) int[nrows] if transpose==0
                    int[ncolumns] if transpose==1
The cluster number to which each element belongs. If transpose==0, then the
dimension of clusterid is equal to nrows (the number of fibers). Otherwise, it
is equal to ncolumns (the number of features).

cdata      (output) double[nclusters][ncolumns] if transpose==0
                    double[nrows][nclusters] if transpose==1
On exit of getclustermean, this array contains the cluster centroids.

cmask      (output) int[nclusters][ncolumns] if transpose==0
                    int[nrows][nclusters] if transpose==1
This array shows which data values of are missing for each centroid. If
cmask[i][j]==0, then cdata[i][j] is missing. A data value is missing for
a centroid if all corresponding data values of the cluster members are missing.

transpose  (input) int
If transpose==0, clusters of rows (fibers) are specified. Otherwise, clusters of
columns (features) are specified.

========================================================================
*/
{
  int i, j, k;
  if (transpose==0)
  {
    for (i = 0; i < nclusters; i++)
    {
      for (j = 0; j < ncolumns; j++)
      {
        cdata[i][j] = 0.;
      }
    }
    for (k = 0; k < nrows; k++)
    {
      i = clusterid[k];
      for (j = 0; j < ncolumns; j++)
      {
          cdata[i][j]+=data[k][j];
      }
    }

  }
  else
  {
    for (i = 0; i < nrows; i++)
    {
      for (j = 0; j < nclusters; j++)
      {
        cdata[i][j] = 0.;
      }
    }
    for (k = 0; k < ncolumns; k++)
    {
      i = clusterid[k];
      for (j = 0; j < nrows; j++)
      {
         cdata[j][i]+=data[j][k];
      }
    }

  }
  return;
}

/* ********************************************************************* */

void getclustermedian(int nclusters, int nrows, int ncolumns,
  double** data,  int *clusterid, double** cdata,
  int transpose)
/*
Purpose
=======

The getclustermedian routine calculates the cluster centroids, given to which
cluster each element belongs. The centroid is defined as the median over all
elements for each dimension.

Arguments
=========

nclusters  (input) int
The number of clusters.

nrows     (input) int
The number of rows in the fiber  data matrix, equal to the number of
fibers.

ncolumns  (input) int
The number of columns in the fiber  data matrix, equal to the number of
features.

data       (input) double[nrows][ncolumns]
The array containing the fiber  data.

mask       (input) int[nrows][ncolumns]
This array shows which data values are missing. If mask[i][j]==0, then
data[i][j] is missing.

clusterid  (output) int[nrows] if transpose==0
                    int[ncolumns] if transpose==1
The cluster number to which each element belongs. If transpose==0, then the
dimension of clusterid is equal to nrows (the number of fibers). Otherwise, it
is equal to ncolumns (the number of features).

cdata      (output) double[nclusters][ncolumns] if transpose==0
                    double[nrows][nclusters] if transpose==1
On exit of getclustermedian, this array contains the cluster centroids.

cmask      (output) int[nclusters][ncolumns] if transpose==0
                    int[nrows][nclusters] if transpose==1
This array shows which data values of are missing for each centroid. If
cmask[i][j]==0, then cdata[i][j] is missing. A data value is missing for
a centroid if all corresponding data values of the cluster members are missing.

transpose  (input) int
If transpose==0, clusters of rows (fibers) are specified. Otherwise, clusters of
columns (features) are specified.

========================================================================
*/
{ int i, j, k;
  if (transpose==0)
  {
    double* temp = (double*) malloc(nrows*sizeof(double));
    for (i = 0; i < nclusters; i++)
    {
      for (j = 0; j < ncolumns; j++)
      {
        int count = 0;
        for (k = 0; k < nrows; k++)
        {
          if (i==clusterid[k])
          { temp[count] = data[k][j];
            count++;
          }
        }
        if (count>0)
        {
            cdata[i][j] = median (count,temp);
        }
        else
        {
            cdata[i][j] = 0.;
        }
      }
    }
    free (temp);
  }
  else
  { double* temp = (double*) malloc(ncolumns*sizeof(double));
    for (i = 0; i < nclusters; i++)
    {
      for (j = 0; j < nrows; j++)
      {
        int count = 0;
        for (k = 0; k < ncolumns; k++)
        {
          if (i==clusterid[k] )
          { temp[count] = data[j][k];
            count++;
          }
        }
        if (count>0)
        {
            cdata[j][i] = median (count,temp);
        }
        else
        {
            cdata[j][i] = 0.;
        }
      }
    }
    free (temp);
  }
  return;
}

/* ********************************************************************* */

void getclustermedoid(int nclusters, int nelements, double** distance,
  int *clusterid, int centroids[], double errors[])
/*
Purpose
=======

The getclustermedoid routine calculates the cluster centroids, given to which
cluster each element belongs. The centroid is defined as the element with the
smallest sum of distances to the other elements.

Arguments
=========

nclusters  (input) int
The number of clusters.

nelements  (input) int
The total number of elements.

distmatrix (input) double array, ragged
  (number of rows is nelements, number of columns is equal to the row number)
The distance matrix. To save space, the distance matrix is given in the
form of a ragged array. The distance matrix is symmetric and has zeros
on the diagonal. See distancematrix for a description of the content.

clusterid  (output) int[nelements]
The cluster number to which each element belongs.

rcentoid   (output) int[nclusters]
The index of the element that functions as the centroid for each cluster.

errors     (output) double[nclusters]
The within-cluster sum of distances between the items and the cluster
centroid.

========================================================================
*/
{ int i, j, k;
  for (j = 0; j < nclusters; j++) errors[j] = DBL_MAX;
  for (i = 0; i < nelements; i++)
  { double d = 0.0;
    j = clusterid[i];
    for (k = 0; k < nelements; k++)
    {
      if (i==k || clusterid[k]!=j)
      {
        continue;
      }
      d += (i < k ? distance[k][i] : distance[i][k]);
      if (d > errors[j])
      {
        break;
      }
    }
    if (d < errors[j])
    {
      errors[j] = d;
      centroids[j] = i;
    }
  }
}

/* ********************************************************************* */
static
void emalg (int nclusters, int nrows, int ncolumns,
  double** data, double *weight, int transpose,
  void getclustercenter(int, int, int, double**, int[],
                        double**, int),
  double metric (int,double**,double**,double*,int,int,int),
  int clusterid[], double** cdata)

{ const int nitems = (transpose==0) ? nrows : ncolumns;
  const int ndata = (transpose==0) ? ncolumns : nrows;

  int* cn = (int*) calloc(nclusters,sizeof(int));
  /* This will contain the number of elements in each cluster. This is needed
   * to check for empty clusters.
   */

  int* savedids = (int*) malloc(nitems*sizeof(int));
  /* needed to check for periodic behavior */

  int changed;
  int iteration = 0;
  int period = 10;
  int i, j;

  for (i = 0; i < nitems; i++)
  {
    cn[clusterid[i]]++;
  }

  /* Start the loop */
  do
  {
    if (iteration % period == 0)
    { /* save the current clustering solution */
      for (i = 0; i < nitems; i++)
      {
        savedids[i] = clusterid[i];
      }
      period *= 2;
    }
    iteration++;

    /* Find the center */
    getclustercenter(nclusters, nrows, ncolumns, data, clusterid,
                     cdata, transpose);

    changed = 0;

    for (i = 0; i < nitems; i++)
    /* Calculate the distances */
    {
      double distance;
      int jnow = clusterid[i];
      if (cn[jnow]==1)
      {
        continue;
      }
      /* No reassignment if that would lead to an empty cluster */
      /* Treat the present cluster as a special case */
      distance = metric(ndata,data,cdata,weight,i,jnow,transpose);
      for (j = 0; j < nclusters; j++)
      {
        double tdistance;
        if (j==jnow)
        {
          continue;
        }
        tdistance = metric(ndata,data,cdata,weight,i,j,transpose);
        if (tdistance < distance)
        {
          distance = tdistance;
          cn[clusterid[i]]--;
          clusterid[i] = j;
          cn[j]++;
          changed = 1;
        }
      }
    }
  } while (changed && !equal_clusters(nitems, savedids, clusterid));
  free (savedids);
  free (cn);
  return;
}

/* *********************************************************************** */


void kcluster (int nclusters,  unsigned int nrows, unsigned int ncolumns,
double** data, double* weight, int transpose,
int npass, char method, char dist,
int *clusterid, double* error, int* ifound)
/*

  example for a perfect comment
   - no "mask" anymore
   - "transpose" obsolete (because it makes no sense to cluster the features in respect to the fibers)

Purpose
=======

The kcluster routine performs k-means or k-median clustering on a given set of
elements, using the specified distance measure. The number of clusters is given
by the user. Multiple passes are being made to find the optimal clustering
solution, each time starting from a different initial clustering.


Arguments
=========

nclusters  (input) int
The number of clusters to be found.

data       (input) double[nrows][ncolumns]
The array containing the data of the elements to be clustered (i.e., the fiber
 data).


nrows     (input) int
The number of rows in the data matrix, equal to the number of fibers.

ncolumns  (input) int
The number of columns in the data matrix, equal to the number of features.

weight (input) double[n]
The weights that are used to calculate the distance.

[transpose  (input) int
If transpose==0, the rows of the matrix are clustered. Otherwise, columns
of the matrix are clustered.] Default: transpose == 0

npass      (input) int
The number of times clustering is performed. Clustering is performed npass
times, each time starting from a different (random) initial assignment of
fibers to clusters. The clustering solution with the lowest within-cluster sum
of distances is chosen.
If npass==0, then the clustering algorithm will be run once, where the initial
assignment of elements to clusters is taken from the clusterid array.

method     (input) char
Defines whether the arithmetic mean (method=='a') or the median
(method=='m') is used to calculate the cluster center.

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

clusterid  (output; input) int[nrows] if transpose==0
                           int[ncolumns] if transpose==1
The cluster number to which a fiber or feature was assigned. If npass==0,
then on input clusterid contains the initial clustering assignment from which
the clustering algorithm starts. On output, it contains the clustering solution
that was found.

error      (output) double
The sum of distances to the cluster center of each item in the optimal k-means
clustering solution that was found.

ifound     (output) int
The number of times the optimal clustering solution was
found. The value of ifound is at least 1; its maximum value is npass.

========================================================================
*/
{ const int nelements = (transpose==0) ? nrows : ncolumns;
  const int ndata = (transpose==0) ? ncolumns : nrows;
  void (*getclustercenter) (int, int, int, double**,  int[],
                            double**, int);

  double (*metric)
    (int,double**,double**,double*,int,int,int);

  int i;
  int ipass;
  int* tclusterid;
  int* mapping;
  double** cdata;
  float k = 0;

  if (nelements < nclusters)
  {
    *ifound = 0;
    return;
  }
  /* More clusters asked for than elements available */

  /* Set the function to find the centroid as indicated by method */
  if (method == 'm')
  {
    getclustercenter = &getclustermedian;
  }
  else
  {
    getclustercenter = &getclustermean;
  }

  /* Set the metric function as indicated by dist */
  setmetric (dist, &metric);

  /* Set the result of the first pass as the initial best clustering solution */
  *ifound = 1;

  /* Find out if the user specified an initial clustering */
  if (npass!=0)
  {
    randomassign (nclusters, nelements, clusterid);
  }

  /* Allocate space to store the centroid data */
  if (transpose==0)
  {
    cdata = (double**) malloc(nclusters*sizeof(double*));

    for (i = 0; i < nclusters; i++)
    {
      cdata[i] = (double*) malloc(ndata*sizeof(double));
    }
  }
  else
  {
    cdata = (double**) malloc(ndata*sizeof(double*));

    for (i = 0; i < ndata; i++)
    {
      cdata[i] = (double*) malloc(nclusters*sizeof(double));
    }
  }

  *error = 0.;
  emalg(nclusters, nrows, ncolumns, data, weight, transpose,
    getclustercenter, metric, clusterid, cdata);

  for (i = 0; i < nelements; i++)
  {
    int j = clusterid[i];
    *error += metric(ndata, data, cdata, weight, i, j, transpose);
  }

  if (npass==0)
  {
    if (transpose==0)
    {
      for (i = 0; i < nclusters; i++)
      {
        free(cdata[i]);
      }
    }
    else
    {
      for (i = 0; i < ndata; i++)
      {
        free(cdata[i]);
      }
    }
    free(cdata);
    return;
  }

  tclusterid = (int*) malloc(nelements*sizeof(int));
  mapping = (int*) malloc(nclusters*sizeof(int));

  for (ipass = 1; ipass < npass; ipass++)
  {
    if (k<ipass || ipass==(npass - 1))
    {
      k += static_cast<float>(((float)npass - 1.0) / 20.0);
    }
    double tssin = 0.;
    int same = 1;

    randomassign (nclusters, nelements, tclusterid);
    emalg(nclusters, nrows, ncolumns, data, weight, transpose,
      getclustercenter, metric, tclusterid, cdata);

    for (i = 0; i < nclusters; i++) mapping[i] = -1;
    for (i = 0; i < nelements; i++)
    {
      int j = tclusterid[i];
      if (mapping[j] == -1)
      {
        mapping[j] = clusterid[i];
      }
      else
      {
        if (mapping[j] != clusterid[i]) same = 0;
      }
      tssin +=
        metric(ndata, data, cdata, weight, i, j, transpose);
    }
    if (same)
    {
      (*ifound)++;
    }
    else
    {
      if (tssin < *error)
      { *ifound = 1;
        *error = tssin;
        for (i = 0; i < nelements; i++)
        {
          clusterid[i] = tclusterid[i];
        }
      }
    }
  }

  /* Deallocate temporarily used space */
  free(mapping);
  free(tclusterid);
  if (transpose==0)
  {
    for (i = 0; i < nclusters; i++)
    {
      free(cdata[i]);
    }
  }
  else
  {
    for (i = 0; i < ndata; i++)
    {
      free(cdata[i]);
    }
  }

  free(cdata);

  return;
}

/* *********************************************************************** */


void kmedoids (int nclusters, int nelements, double** distance,
  int npass, int* clusterid, double* error, int* ifound)
/*
Purpose
=======

The kmedoids routine performs k-medoids clustering on a given set of elements,
using the distance matrix and the number of clusters passed by the user.
Multiple passes are being made to find the optimal clustering solution, each
time starting from a different initial clustering.


Arguments
=========

nclusters  (input) int
The number of clusters to be found.

nelements  (input) int
The number of elements to be clustered.

distmatrix (input) double array, ragged
  (number of rows is nelements, number of columns is equal to the row number)
The distance matrix. To save space, the distance matrix is given in the
form of a ragged array. The distance matrix is symmetric and has zeros
on the diagonal. See distancematrix for a description of the content.

npass      (input) int
The number of times clustering is performed. Clustering is performed npass
times, each time starting from a different (random) initial assignment of fibers
to clusters. The clustering solution with the lowest within-cluster sum of
distances is chosen.
If npass==0, then the clustering algorithm will be run once, where the initial
assignment of elements to clusters is taken from the clusterid array.

clusterid  (output; input) int[nelements]
On input, if npass==0, then clusterid contains the initial clustering assignment
from which the clustering algorithm starts; all numbers in clusterid should be
between zero and nelements-1 inclusive. If npass!=0, clusterid is ignored on
input.
On output, clusterid contains the clustering solution that was found: clusterid
contains the number of the cluster to which each item was assigned. On output,
the number of a cluster is defined as the item number of the centroid of the
cluster.

error      (output) double
The sum of distances to the cluster center of each item in the optimal k-medoids
clustering solution that was found.

ifound     (output) int
The number of times the optimal clustering solution was
found. The value of ifound is at least 1; its maximum value is npass.

========================================================================
*/

{ int i, j, k, icluster, ipass;
  int* tclusterid;
  int* centroids;
  int* savedids;
  double* errors;
  int changed;
  int iteration = 0;
  int period = 10;
  float showprogress = 0;
  /* needed to check for periodic behavior */

  if (nelements < nclusters)
  {
    *ifound = 0;
    return;
  } /* More clusters asked for than elements available */

  centroids = (int*) malloc(nclusters*sizeof(int));
  savedids = (int*) malloc(nelements*sizeof(int));
  errors = (double*) malloc(nclusters*sizeof(double));

  /* Set the result of the first pass as the initial best clustering solution */
  *ifound = 1;

  /* Find out if the user specified an initial clustering */
  if (npass)
  {
    randomassign (nclusters, nelements, clusterid);
    /* Ready for the first run */
  }

  *error = 0.;
  do /* Start the loop */
  {
    if (iteration % period == 0)
    { /* save the current clustering solution */
      for (i = 0; i < nelements; i++)
      {
        savedids[i] = clusterid[i];
      }
      period *= 2;
    }
    iteration++;

    /* Find the center */
    getclustermedoid (nclusters, nelements, distance, clusterid, centroids, errors);

    changed = 0;
    for (i = 0; i < nelements; i++)
    /* Find the closest cluster */
    {
      double d = DBL_MAX;
      for (icluster = 0; icluster < nclusters; icluster++)
      {
        double td;
        j = centroids[icluster];
        if (i==j)
        {
          d = 0.0;
          clusterid[i] = icluster;
          changed = 1;
          break;
        }
        td = (i > j) ? distance[i][j] : distance[j][i];
        if (td < d)
        {
          d = td;
          clusterid[i] = icluster;
          changed = 1;
        }
      }
    }
  } while (changed && !equal_clusters(nelements, clusterid, savedids));

  for (i = 0; i < nelements; i++)
  {
    const int j = centroids[clusterid[i]];
    /* Set the cluster number to the item number of the cluster centroid */
    clusterid[i] = j;
    if (i==j) continue;
    *error += (i > j) ? distance[i][j] : distance[j][i];
  }
  if (npass==0)
  /* Deterministic result depending on the specified initial clustering */
  {
    free(savedids);
    free(centroids);
    free(errors);
    return; /* Done for today */
  }

  tclusterid = (int*) malloc(nelements*sizeof(int));
  for (ipass = 1; ipass < npass; ipass++)
  {
    if (showprogress<ipass || ipass==(npass - 1))
    {
      showprogress += static_cast<float>(((float)npass - 1.0) / 20.0);
    }

    double terror = 0.0;

    iteration = 0;
    period = 10;

    randomassign (nclusters, nelements, tclusterid);
    do /* Start the loop */
    {
      if (iteration % period == 0)
      { /* save the current clustering solution */
        for (i = 0; i < nelements; i++)
        {
          savedids[i] = tclusterid[i];
        }
        period = period * 2;
      }
      iteration++;

      /* Find the center */
      getclustermedoid (nclusters, nelements, distance, tclusterid, centroids, errors);

      changed = 0;
      for (i = 0; i < nelements; i++)
      /* Find the closest cluster */
      {
        double d = DBL_MAX;
        for (icluster = 0; icluster < nclusters; icluster++)
        {
          double td;
          j = centroids[icluster];
          if (i==j)
          {
            d = 0.0;
            tclusterid[i] = icluster;
            changed = 1;
            break;
          }
          td = (i > j) ? distance[i][j] : distance[j][i];
          if (td < d)
          {
            d = td;
            tclusterid[i] = icluster;
            changed = 1;
          }
        }
      }
      /* compare to the saved clustering solution */
    } while (changed && !equal_clusters(nelements, tclusterid, savedids));

    changed = 0;
    for (i = 0; i < nelements; i++)
    {
      k = tclusterid[i];
      j = centroids[k];
      if (j!=clusterid[i])
      {
        changed = 1;
      }
      if (i==j)
      { continue;
      }
      terror += (i > j) ? distance[i][j] : distance[j][i];
    }
    if (!changed)
    {
      (*ifound)++;
    }
    else
    {
      if (terror < *error)
      { *ifound = 1;
        *error = terror;
        /* The cluster number is set to the item number of the cluster centroid */
        for (i = 0; i < nelements; i++) clusterid[i] = centroids[tclusterid[i]];
      }
    }
  }

  /* Deallocate temporarily used space */
  free(savedids);
  free(centroids);
  free(tclusterid);
  free(errors);

  return;
}

/* ******************************************************************** */

}


