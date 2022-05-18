// **InsertLicense** code
//----------------------------------------------------------------------------------
//! Implementation file for library Self-Organizing Maps
/*!
// \file    mlSOM.cpp
// \author  Peter Ledochowitsch, Philip Bittihn, Jan Klein
// \date    02/2006
*/


/******************************************************************************/
/* The C Clustering Library for cDNA fiber data.
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



#include "clSOM.h"

#include "clRandom.h"

namespace cluster {


/* ************************************************************************ */
/* ******************************************************************* */

static
void somworker (int nrows, int ncolumns, double** data, double* weights, int transpose, int nxgrid, int nygrid,
  double inittau, double*** celldata, int niter, char dist)

{ 
  const int nelements = (transpose==0) ? nrows : ncolumns;
  const int ndata = (transpose==0) ? ncolumns : nrows;
  double (*metric)
    (int,double**,double**,double*,int,int,int);
  int i, j;
  float k = 0;
  double* stddata = (double*) calloc(nelements,sizeof(double));
  int ix, iy;
  long* index;
  int iter;
  /* Maximum radius in which nodes are adjusted */
  double maxradius = sqrt(static_cast<double>(nxgrid)*nxgrid+static_cast<double>(nygrid)*nygrid);

  //cout << "maxradius successful!" << endl;

  //cout << "Random number generator initialized!" << endl;

  /* Set the metric function as indicated by dist */
  setmetric (dist, &metric);

  //cout << "Metric setted!" << endl;

  /* Calculate the standard deviation for each row or column */
  if (transpose==0)
  { 
    for (i = 0; i < nelements; i++)
    { 
      int n = 0;
      for (j = 0; j < ndata; j++)
      { 
         double term = data[i][j];
          term = term * term;
          stddata[i] += term;
          n++;
      }
      if (stddata[i] > 0) 
      {
        stddata[i] = sqrt(stddata[i]/n);
      }
      else 
      {
        stddata[i] = 1;
      }
    }
  }
  else
  { 
    for (i = 0; i < nelements; i++)
    { 
      int n = 0;
      for (j = 0; j < ndata; j++)
      { 
          double term = data[j][i];
          term = term * term;
          stddata[i] += term;
          n++;
      }
      if (stddata[i] > 0) 
      { 
        stddata[i] = sqrt(stddata[i]/n);
      }
      else 
      {
        stddata[i] = 1;
      }
    }
  }

  

  /* Randomly initialize the nodes */
  for (ix = 0; ix < nxgrid; ix++)
  { 
    for (iy = 0; iy < nygrid; iy++)
    { 
      double sum = 0.;
      for (i = 0; i < ndata; i++)
      { 
        double term = genunf(-1.,1.);
        celldata[ix][iy][i] = term;
        sum += term * term;
      }
      sum = sqrt(sum/ndata);
      for (i = 0; i < ndata; i++) 
      { 
        celldata[ix][iy][i] /= sum;
      }
    }
  }

  /* Randomize the order in which fibers or arrays will be used */
  index = (long*) malloc(nelements*sizeof(long));
  for (i = 0; i < nelements; i++) 
  { 
    index[i] = i;
  }
  genprm (index, nelements);

  
  /* Start the iteration */
  for (iter = 0; iter < niter; iter++)
  { 
    if (k<iter || iter==(niter - 1))
    {
      k += static_cast<float>(((float)niter - 1.0) / 20.0);
    }
      
    int ixbest = 0;
    int iybest = 0;
    long iobject = iter % nelements;
    iobject = index[iobject];
    if (transpose==0)
    { 
      double closest = metric(ndata,data,celldata[ixbest],weights,iobject,iybest,transpose);
      const double radius = maxradius * (1. - ((double)iter)/((double)niter));
      const double radius2 = radius * radius;
      const double tau = inittau * (1. - ((double)iter)/((double)niter));

      for (ix = 0; ix < nxgrid; ix++)
      { 
        for (iy = 0; iy < nygrid; iy++)
        { 
          double distance =
            metric (ndata,data,celldata[ix],weights,iobject,iy,transpose);
          if (distance < closest)
          { 
            ixbest = ix;
            iybest = iy;
            closest = distance;
          }
        }
      }
      for (ix = 0; ix < nxgrid; ix++)
      { 
        for (iy = 0; iy < nygrid; iy++)
        { 
          if (((ix-ixbest)*(ix-ixbest) + (iy-iybest)*(iy-iybest)) < radius2)
          { 
            double sum = 0.;
            for (i = 0; i < ndata; i++)
            {
              celldata[ix][iy][i] +=
                tau * (data[iobject][i]/stddata[iobject]-celldata[ix][iy][i]);
            }
            for (i = 0; i < ndata; i++)
            { 
              double term = celldata[ix][iy][i];
              term = term * term;
              sum += term;
            }
            if (sum>0)
            { 
              sum = sqrt(sum/ndata);
              for (i = 0; i < ndata; i++) celldata[ix][iy][i] /= sum;
            }
          }
        }
      }
    }
    else
    { double closest;
      double** celldatavector = (double**) malloc(ndata*sizeof(double*));
      const double radius = maxradius * (1. - ((double)iter)/((double)niter));
      const double radius2 = radius * radius;
      double tau = inittau * (1. - ((double)iter)/((double)niter));

      for (i = 0; i < ndata; i++)
      {
        celldatavector[i] = &(celldata[ixbest][iybest][i]);
      }
      closest = metric(ndata,data,celldatavector,weights,iobject,0,transpose);
      for (ix = 0; ix < nxgrid; ix++)
      { 
        for (iy = 0; iy < nygrid; iy++)
        { 
          double distance;
          for (i = 0; i < ndata; i++)
          {
            celldatavector[i] = &(celldata[ixbest][iybest][i]);
          }
          distance =
            metric (ndata,data,celldatavector,weights,iobject,0,transpose);
          if (distance < closest)
          { 
            ixbest = ix;
            iybest = iy;
            closest = distance;
          }
        }
      }
      free(celldatavector);
      for (ix = 0; ix < nxgrid; ix++)
      { 
        for (iy = 0; iy < nygrid; iy++)
        { 
          if (((ix-ixbest)*(ix-ixbest) + (iy-iybest)*(iy-iybest)) < radius2)
          { double sum = 0.;
            for (i = 0; i < ndata; i++)
            { 
              celldata[ix][iy][i] +=
                tau * (data[i][iobject]/stddata[iobject]-celldata[ix][iy][i]);
            }
            for (i = 0; i < ndata; i++)
            { 
              double term = celldata[ix][iy][i];
              term = term * term;
              sum += term;
            }
            if (sum>0)
            { 
              sum = sqrt(sum/ndata);
              for (i = 0; i < ndata; i++) celldata[ix][iy][i] /= sum;
            }
          }
        }
      }
    }
  }
  
  free(stddata);
  free(index);
  return;
}

/* ******************************************************************* */

static
void somassign (int nrows, int ncolumns, double** data,
  double *weights, int transpose, int nxgrid, int nygrid,
  double*** celldata, char dist, int **clusterid)
/* Collect clusterids */
{ double (*metric)
    (int,double**,double**, double*,int,int,int);
  const int ndata = (transpose==0) ? ncolumns : nrows;
  int i,j;

  setmetric (dist, &metric);

  if (transpose==0)
  { 
    for (i = 0; i < nrows; i++)
    { 
      int ixbest = 0;
      int iybest = 0;
      double closest = metric(ndata,data,celldata[ixbest],
        weights,i,iybest,transpose);
      int ix, iy;
      for (ix = 0; ix < nxgrid; ix++)
      { 
        for (iy = 0; iy < nygrid; iy++)
        { double distance =
            metric (ndata,data,celldata[ix],
              weights,i,iy,transpose);
          if (distance < closest)
          { 
            ixbest = ix;
            iybest = iy;
            closest = distance;
          }
        }
      }
      clusterid[i][0] = ixbest;
      clusterid[i][1] = iybest;
    }
    
  }
  else
  { 
    double** celldatavector = (double**) malloc(ndata*sizeof(double*));
    
    int ixbest = 0;
    int iybest = 0;
    
    for (i = 0; i < ncolumns; i++)
    { 
      double closest;
      int ix, iy;
      for (j = 0; j < ndata; j++)
      {
        celldatavector[j] = &(celldata[ixbest][iybest][j]);
      }
      closest = metric(ndata,data,celldatavector,
        weights,i,0,transpose);
      for (ix = 0; ix < nxgrid; ix++)
      { 
        for (iy = 0; iy < nygrid; iy++)
        { 
          double distance;
          for(j = 0; j < ndata; j++)
          {
            celldatavector[j] = &(celldata[ix][iy][j]);
          }
          distance = metric(ndata,data,celldatavector,
            weights,i,0,transpose);
          if (distance < closest)
          { 
            ixbest = ix;
            iybest = iy;
            closest = distance;
          }
        }
      }
      clusterid[i][0] = ixbest;
      clusterid[i][1] = iybest;
    }
    free(celldatavector);
    
  }
  return;
}

/* ******************************************************************* */

void somcluster (int nrows, int ncolumns, double** data, 
  double* weight, int transpose, int nxgrid, int nygrid,
  double inittau, int niter, char dist, double*** celldata, int **clusterid)
/*

Purpose
=======

The somcluster routine implements a self-organizing map (Kohonen) on a
rectangular grid, using a given set of vectors. The distance measure to be
used to find the similarity between fibers and nodes is given by dist.

Arguments
=========

nrows     (input) int
The number of rows in the data matrix, equal to the number of fibers.

ncolumns  (input) int
The number of columns in the data matrix, equal to the number of microarrays.

data       (input) double[nrows][ncolumns]
The array containing the fiber  data.

mask       (input) int[nrows][ncolumns]
This array shows which data values are missing. If
mask[i][j] == 0, then data[i][j] is missing.

weights    (input) double[ncolumns] if transpose==0;
                   double[nrows]    if transpose==1
The weights that are used to calculate the distance. The length of this vector
is ncolumns if fibers are being clustered, or nrows if microarrays are being
clustered.

transpose  (input) int
If transpose==0, the rows (fibers) of the matrix are clustered. Otherwise,
columns (microarrays) of the matrix are clustered.

nxgrid    (input) int
The number of grid cells horizontally in the rectangular topology of clusters.

nygrid    (input) int
The number of grid cells horizontally in the rectangular topology of clusters.

inittau    (input) double
The initial value of tau, representing the neighborhood function.

niter      (input) int
The number of iterations to be performed.

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

celldata (output) double[nxgrid][nygrid][ncolumns] if transpose==0;
                  double[nxgrid][nygrid][nrows]    if tranpose==1
The fiber  data for each node (cell) in the 2D grid. This can be
interpreted as the centroid for the cluster corresponding to that cell. If
celldata is NULL, then the centroids are not returned. If celldata is not
NULL, enough space should be allocated to store the centroid data before callingsomcluster.

clusterid (output), int[nrows][2]    if transpose==0;
                    int[ncolumns][2] if transpose==1
For each item (fiber or microarray) that is clustered, the coordinates of the
cell in the 2D grid to which the item was assigned. If clusterid is NULL, the
cluster assignments are not returned. If clusterid is not NULL, enough memory
should be allocated to store the clustering information before calling
somcluster.

========================================================================
*/
{//cout << "entered somcluster!" << endl;
    
  const int nobjects = (transpose==0) ? nrows : ncolumns;
  const int ndata = (transpose==0) ? ncolumns : nrows;
  int i,j;
  const int lcelldata = (celldata==NULL) ? 0 : 1;

  if (nobjects < 2) return;

  if (lcelldata==0)
  { 
    celldata = (double***) malloc(nxgrid*nygrid*ndata*sizeof(double**));
    for (i = 0; i < nxgrid; i++)
    { 
      celldata[i] = (double**) malloc(nygrid*ndata*sizeof(double*));
      for (j = 0; j < nygrid; j++)
      {
        celldata[i][j] = (double*) malloc(ndata*sizeof(double));
      }
    }
  }

  //cout << "successfully allocated space for celldata, entering somworker!" << endl;

  somworker (nrows, ncolumns, data, weight, transpose, nxgrid, nygrid,
    inittau, celldata, niter, dist);

  //cout << "somworker complete, entering somassign!" << endl;

  if (clusterid)
  {
    somassign (nrows, ncolumns, data, weight, transpose,
      nxgrid, nygrid, celldata, dist, clusterid);
  }

    //cout << "somassign completed!" << endl;

  if(lcelldata==0)
  { 
    for (i = 0; i < nxgrid; i++)
    {
      for (j = 0; j < nygrid; j++)
      {
        free(celldata[i][j]);
      }
    }
    for (i = 0; i < nxgrid; i++)
    {
      free(celldata[i]);
    }
    free(celldata);
  }
  return;
}

}
