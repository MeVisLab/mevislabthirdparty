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


#include "clHierarchicalClustering.h"

#include <algorithm> //std::min std::max

/* ---------------------------------------------------------------------- */

namespace cluster {

double find_closest_pair(int n, double** distmatrix, int* ip, int* jp)
/*
This function searches the distance matrix to find the pair with the shortest
distance between them. The indeces of the pair are returned in ip and jp; the
distance itself is returned by the function.

n          (input) int
The number of elements in the distance matrix.

distmatrix (input) double**
A ragged array containing the distance matrix. The number of columns in each
row is one less than the row index.

ip         (output) int*
A pointer to the integer that is to receive the first index of the pair with
the shortest distance.

jp         (output) int*
A pointer to the integer that is to receive the second index of the pair with
the shortest distance.
*/
{ int i, j;
  double distance = distmatrix[1][0];
  for (i = 0; i < n; i++)
  { 
    for (j = 0; j < i; j++)
    { 
      if (distmatrix[i][j]<distance)
      { 
        distance = distmatrix[i][j];
        *ip = i;
        *jp = j;
      }
    }
  }
  return distance;
}

/* ********************************************************************* */

/* ******************************************************************** */


void pclcluster (int nrows, int ncolumns, double** data,
double* weight, double** distmatrix, char dist, int transpose,
int** result, double* linkdist)
/*

Purpose
=======

The pclcluster routine performs clustering using pairwise centroid-linking
on a given set of fiber   data, using the distance metric given by dist.

Arguments
=========

nrows     (input) int
The number of rows in the fiber   data matrix, equal to the number of
fibers.

ncolumns  (input) int
The number of columns in the fiber   data matrix, equal to the number of
features.

data       (input) double[nrows][ncolumns]
The array containing the fiber  data.

mask       (input) int[nrows][ncolumns]
This array shows which data values are missing. If
mask[i][j] == 0, then data[i][j] is missing.

weight     (input) double[ncolumns] if transpose==0;
                   double[nrows]    if transpose==1
The weights that are used to calculate the distance. The length of this vector
is ncolumns if fibers are being clustered, and nrows if features are being
clustered.

transpose  (input) int
If transpose==0, the rows of the matrix are clustered. Otherwise, columns
of the matrix are clustered.

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

distmatrix (input) double**
The distance matrix. This matrix is precalculated by the calling routine
treecluster. The pclcluster routine modifies the contents of distmatrix, but
does not deallocate it.

result  (output) int[nelements-1][2]
The clustering solution. Each row in the matrix describes one linking event,
with the two columns containing the name of the nodes that were joined.
The original fibers are numbered 0..nfibers-1, nodes are numbered
-1..-(nelements-1), where nelements is nrows or ncolumns depending on whether
fibers (rows) or features (columns) are being clustered.

linkdist (output) double[nelements-1]
For each node, the distance between the two subnodes that were joined. The
number of nodes (nnodes) is equal to the number of fibers minus one if fibers are
clustered, or the number of features minus one if features are clustered.

========================================================================*/
{ double (*metric)
    (int,double**,double**, double*, int,int,int);
  int i;
  const int nelements = (transpose==0) ? nrows : ncolumns;
  int* distid = (int*) malloc(nelements*sizeof(int));
  int inode;
  const int ndata = transpose ? nrows : ncolumns;
  const int nnodes = nelements - 1;

  /* Set the metric function as indicated by dist */
  setmetric (dist, &metric);

  for (i = 0; i < nelements; i++) 
  {
    distid[i] = i;
  }
  /* To remember which row/column in the distance matrix contains what */

  /* Storage for node data */

    double** newdata = (double**) malloc(nelements*sizeof(double*));

    for (i = 0; i < nelements; i++)
    { 
      newdata[i] = (double*) malloc(ndata*sizeof(double));
      memcpy(newdata[i], data[i], ndata*sizeof(double));
    }
    data = newdata;



  for (inode = 0; inode < nnodes; inode++)
  { 
    /* Find the pair with the shortest distance */
    int isaved = 1;
    int jsaved = 0;
    linkdist[inode] = find_closest_pair(nelements-inode, distmatrix, &isaved, &jsaved);
    result[inode][0] = distid[jsaved];
    result[inode][1] = distid[isaved];

    /* Make node jsaved the new node */
    for (i = 0; i < ndata; i++)
    { 
      data[jsaved][i] = data[jsaved][i] + data[isaved][i];
    }
    free(data[isaved]);

    data[isaved] = data[nnodes-inode];


    /* Fix the distances */
    distid[isaved] = distid[nnodes-inode];
    for (i = 0; i < isaved; i++)
    {
      distmatrix[isaved][i] = distmatrix[nnodes-inode][i];
    }
    for (i = isaved + 1; i < nnodes-inode; i++)
    {
      distmatrix[i][isaved] = distmatrix[nnodes-inode][i];
    }

    distid[jsaved] = -inode-1;
    for (i = 0; i < jsaved; i++)
    { 
      distmatrix[jsaved][i] =
        metric(ndata,data,data,weight,jsaved,i,0);
    }
    for (i = jsaved + 1; i < nnodes-inode; i++)
    { 
      distmatrix[i][jsaved] =
        metric(ndata,data,data,weight,jsaved,i,0);
    }

  }

  /* Free temporarily allocated space */
  free(data[0]);
  free(data);
  free(distid);

  return;
}

/* ******************************************************************** */


/* ******************************************************************** */


void pslcluster (int nrows, double** distmatrix,
  int** result, double* linkdist)
/*

Purpose
=======

The pslcluster routine performs single-linkage hierarchical clustering, using
either the distance matrix directly, if available, or by calculating the
distances from the data array. This implementation is based on the SLINK
algorithm, described in:
Sibson, R. (1973). SLINK: An optimally efficient algorithm for the single-link
cluster method. The Computer Journal, 16(1): 30-34.
The output of this algorithm is identical to conventional single-linkage
hierarchical clustering, but is much more memory-efficient and faster. Hence,
it can be applied to large data sets, for which the conventional single-
linkage algorithm fails due to lack of memory.


Arguments
=========

nrows     (input) int
The number of rows in the fiber  data matrix, equal to the number of
fibers.

ncolumns  (input) int
The number of columns in the fiber  data matrix, equal to the number of
features.

data       (input) double[nrows][ncolumns]
The array containing the fiber  data.

mask       (input) int[nrows][ncolumns]
This array shows which data values are missing. If
mask[i][j] == 0, then data[i][j] is missing.

weight (input) double[n]
The weights that are used to calculate the distance. The length of this vector
is ncolumns if fibers are being clustered, and nrows if features are being
clustered.

transpose  (input) int
If transpose==0, the rows of the matrix are clustered. Otherwise, columns
of the matrix are clustered.

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

distmatrix (input) double**
The distance matrix. If the distance matrix is passed by the calling routine
treecluster, it is used by pslcluster to speed up the clustering calculation.
The pslcluster routine does not modify the contents of distmatrix, and does
not deallocate it. If distmatrix is NULL, the pairwise distances are calculated
by the pslcluster routine from the fiber  data (the data and mask
arrays) and stored in temporary arrays. If distmatrix is passed, the original
fiber  data (specified by the data and mask arguments) are not needed
and are therefore ignored.

result  (output) int[nelements-1][2]
The clustering solution. Each row in the matrix describes one linking event,
with the two columns containing the name of the nodes that were joined.
The original fibers are numbered 0..nfibers-1, nodes are numbered
-1..-(nelements-1), where nelements is nrows or ncolumns depending on whether
fibers (rows) or features (columns) are being clustered.

linkdist (output) double[nelements-1]
For each node, the distance between the two subnodes that were joined. The
number of nodes (nnodes) is equal to the number of fibers minus one if fibers are
clustered, or the number of features minus one if features are clustered.

========================================================================
*/
{ int i, j, k;
  const int nelements =  nrows;
  const int nnodes = nelements - 1;
  int* vector = (int*) malloc(nnodes*sizeof(int));
  double* temp = (double*) malloc(nnodes*sizeof(double));
  int* index;

  for (i = 0; i < nnodes; i++)
  { 
    vector[i] = i;
    linkdist[i] = DBL_MAX;
  }


  for (i = 0; i < nrows; i++)
  { 
    for (j = 0; j < i; j++) 
    {
      temp[j] = distmatrix[i][j];
    }
    for (j = 0; j < i; j++)
    { 
      k = vector[j];
      if (linkdist[j] >= temp[j])
      { 
        if (linkdist[j] < temp[k]) 
        {
          temp[k] = linkdist[j];
        }
        linkdist[j] = temp[j];
        vector[j] = i;
      }
      else if (temp[j] < temp[k]) {temp[k] = temp[j];}
    }
    for (j = 0; j < i; j++)
    {
      if (linkdist[j] >= linkdist[vector[j]]) 
      {
        vector[j] = i;
      }
    }
  }


  /* One of these days, I should write my own quicksort routine that takes
   * care of this reordering more efficiently. */
  index = (int*) malloc(nelements*sizeof(int));
  sort(nnodes, linkdist, index);
  for (i = 0; i < nnodes; i++) 
  {
    temp[i] = linkdist[i];
  }
  for (i = 0; i < nnodes; i++)
  { 
    j = index[i];
    result[i][0] = j;
    linkdist[i] = temp[j];
  }
  free(temp);

  for (i = 0; i < nelements; i++) 
  {
    index[i] = i;
  }
  for (i = 0; i < nnodes; i++)
  { 
    j = result[i][0];
    k = vector[j];
    result[i][0] = index[j];
    result[i][1] = index[k];
    index[k] = -i-1;

  }
  free(vector);
  free(index);

  return;
}
/* ******************************************************************** */



void pmlcluster (int nfibers, double** distmatrix, int** result,
  double* linkdist)
/*

Purpose
=======

The pmlcluster routine performs clustering using pairwise maximum- (complete-)
linking on the given distance matrix.

Arguments
=========

nfibers     (input) int
The number of elements to be clustered.

distmatrix (input) double**
The distance matrix, with nfibers rows, each row being filled up to the
diagonal. The elements on the diagonal are not used, as they are assumed to be
zero. The distance matrix will be modified by this routine.

result  (output) int[nfibers-1][2]
The clustering solution. Each row in the matrix describes one linking event,
with the two columns containing the name of the nodes that were joined.
The original elements are numbered 0..nfibers-1, nodes are numbered
-1..-(nfibers-1).

linkdist (output) double[nfibers-1]
For each node, the distance between the two subnodes that were joined. The
number of nodes (nnodes) is equal to the number of fibers minus one if fibers are
clustered, or the number of features minus one if features are clustered.

========================================================================
*/
{ int j;
  int nNodes;

  /* Setup a list specifying to which cluster a fiber belongs */
  int* clusterid = (int*) malloc(nfibers*sizeof(int));
  for (j = 0; j < nfibers; j++) 
  {
    clusterid[j] = j;
  }

  for (nNodes = nfibers; nNodes > 1; nNodes--)
  { 
    int isaved = 1;
    int jsaved = 0;
    linkdist[nfibers-nNodes] = find_closest_pair(nNodes, distmatrix, &isaved, &jsaved);

    /* Fix the distances */
    for (j = 0; j < jsaved; j++)
    {
      distmatrix[jsaved][j] = std::max(distmatrix[isaved][j],distmatrix[jsaved][j]);
    }
    for (j = jsaved+1; j < isaved; j++)
    {
      distmatrix[j][jsaved] = std::max(distmatrix[isaved][j], distmatrix[j][jsaved]);
    }
    for (j = isaved+1; j < nNodes; j++)
    {
      distmatrix[j][jsaved] = std::max(distmatrix[j][isaved], distmatrix[j][jsaved]);
    }

    for (j = 0; j < isaved; j++)
    {
      distmatrix[isaved][j] = distmatrix[nNodes-1][j];
    }
    for (j = isaved+1; j < nNodes-1; j++)
    {
      distmatrix[j][isaved] = distmatrix[nNodes-1][j];
    }

    /* Update clusterids */
    result[nfibers-nNodes][0] = clusterid[isaved];
    result[nfibers-nNodes][1] = clusterid[jsaved];
    clusterid[jsaved] = nNodes-nfibers-1;
    clusterid[isaved] = clusterid[nNodes-1];

  }
  free(clusterid);

  return;
}

//*************************************************************************


void palcluster (int nfibers, double** distmatrix, int** result,
  double* linkdist)
/*

Purpose
=======

The palcluster routine performs clustering using pairwise average
linking on the given distance matrix.

Arguments
=========

nfibers     (input) int
The number of elements to be clustered.

distmatrix (input) double**
The distance matrix, with nfibers rows, each row being filled up to the
diagonal. The elements on the diagonal are not used, as they are assumed to be
zero. The distance matrix will be modified by this routine.

result  (output) int[nfibers-1][2]
The clustering solution. Each row in the matrix describes one linking event,
with the two columns containing the name of the nodes that were joined.
The original elements are numbered 0..nfibers-1, nodes are numbered
-1..-(nfibers-1).

linkdist (output) double[nfibers-1]
For each node, the distance between the two subnodes that were joined. The
number of nodes (nnodes) is equal to the number of fibers minus one if fibers are
clustered, or the number of features minus one if features are clustered.

========================================================================
*/
{ int j;
  int nNodes;

  /* Keep track of the number of elements in each cluster
   * (needed to calculate the average) */
  int* number =  (int*) malloc(nfibers*sizeof(int));
  /* Setup a list specifying to which cluster a fiber belongs */
  int* clusterid = (int*) malloc(nfibers*sizeof(int));
  for (j = 0; j < nfibers; j++)
  { 
    number[j] = 1;
    clusterid[j] = j;
  }

  for (nNodes = nfibers; nNodes > 1; nNodes--)
  { 
    int sum;
    int isaved = 1;
    int jsaved = 0;
    linkdist[nfibers-nNodes] = find_closest_pair(nNodes, distmatrix, &isaved, &jsaved);

    /* Save result */
    result[nfibers-nNodes][0] = clusterid[isaved];
    result[nfibers-nNodes][1] = clusterid[jsaved];

    /* Fix the distances */
    sum = number[isaved] + number[jsaved];
    for (j = 0; j < jsaved; j++)
    { 
      distmatrix[jsaved][j] = distmatrix[isaved][j]*number[isaved]
                            + distmatrix[jsaved][j]*number[jsaved];
      distmatrix[jsaved][j] /= sum;
    }
    for (j = jsaved+1; j < isaved; j++)
    { 
      distmatrix[j][jsaved] = distmatrix[isaved][j]*number[isaved]
                            + distmatrix[j][jsaved]*number[jsaved];
      distmatrix[j][jsaved] /= sum;
    }
    for (j = isaved+1; j < nNodes; j++)
    { 
      distmatrix[j][jsaved] = distmatrix[j][isaved]*number[isaved]
                            + distmatrix[j][jsaved]*number[jsaved];
      distmatrix[j][jsaved] /= sum;
    }

    for (j = 0; j < isaved; j++)
    {
      distmatrix[isaved][j] = distmatrix[nNodes-1][j];
    }
    for (j = isaved+1; j < nNodes-1; j++)
    {
      distmatrix[j][isaved] = distmatrix[nNodes-1][j];
    }

    /* Update number of elements in the clusters */
    number[jsaved] = sum;
    number[isaved] = number[nNodes-1];

    /* Update clusterids */
    clusterid[jsaved] = nNodes-nfibers-1;
    clusterid[isaved] = clusterid[nNodes-1];

  }
  free(clusterid);
  free(number);

  return;
}





//***************************************************************************



void cuttree (int nfibers, int** tree, int nclusters, int* clusterid)
/*
Purpose
=======

The cuttree routine takes the output of a hierarchical clustering routine, and
divides the elements in the tree structure into clusters based on the
hierarchical clustering result. The number of clusters is specified by the user.

Arguments
=========

nfibers      (input) int
The number of elements that were clustered.

tree           (input) int[nfibers-1][2]
The clustering solution. Each row in the matrix describes one linking event,
with the two columns containing the name of the nodes that were joined.
The original elements are numbered 0..nfibers-1, nodes are numbered
-1..-(nfibers-1). The cuttree routine checks the tree array for errors to
avoid segmentation faults. Errors in the tree array that would not cause
segmentation faults may pass undetected. If an error is found, all elements
are assigned to cluster -1, and the routine returns.

nclusters      (input) int
The number of clusters to be formde.

clusterid      (output) int[nfibers]
The number of the cluster to which each element was assigned. Space for this
array should be allocated before calling the cuttree routine.

========================================================================
*/
{ int i, j, k;
  int icluster = 0;
  const int n = nfibers-nclusters; /* number of nodes to join */
  int* nodeid;
  /* Check the tree */
  int flag = 0;
  if (nclusters > nfibers || nclusters < 1) 
  {
    flag = 1;
  }
  for (i = 0; i < nfibers-1; i++)
  { 
    if (tree[i][0] >= nfibers || tree[i][0] < -i ||
        tree[i][1] >= nfibers || tree[i][1] < -i)
    { 
      flag = 1;
      break;
    }
  }
  /* Assign all elements to cluster -1 and return if an error is found. */
  if (flag)
  { 
    for (i = 0; i < nfibers; i++) 
    {
      clusterid[i] = -1;
    }
    return;
  }
  /* The tree array is safe to use. */
  for (i = nfibers-2; i >= n; i--)
  { k = tree[i][0];
    if (k>=0)
    { 
      clusterid[k] = icluster;
      icluster++;
    }
    k = tree[i][1];
    if (k>=0)
    { 
      clusterid[k] = icluster;
      icluster++;
    }
  }
  nodeid = (int*) malloc(n*sizeof(int));
  for (i = 0; i < n; i++) 
  {
    nodeid[i] = -1;
  }
  for (i = n-1; i >= 0; i--)
  { 
    if(nodeid[i]<0)
    { 
      j = icluster;
      nodeid[i] = j;
      icluster++;
    }
    else 
    {
      j = nodeid[i];
    }
    k = tree[i][0];
    if (k<0) 
    {
      nodeid[-k-1] = j;
    } 
    else 
    {
      clusterid[k] = j;
    }
    k = tree[i][1];
    if (k<0) 
    {
      nodeid[-k-1] = j;
    } 
    else 
    {
      clusterid[k] = j;
    }
  }
  free(nodeid);
  return;
}

/* ******************************************************************** */

}