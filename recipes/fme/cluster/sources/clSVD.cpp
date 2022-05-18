// **InsertLicense** code
//----------------------------------------------------------------------------------
//! Implementation file for library SpectralClustering
/*!
// \file    mlSpectralClustering.cpp
// \author  Peter Ledochowitsch, Philip Bittihn, Jan Klein
// \date    02/2006
*/


// disclaimer only due to usage of SVD procedure

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


#include "clSVD.h"

#include "clHierarchicalClustering.h"

#include <algorithm> //std::min std::max
#include <cmath> //fabs sqrt

namespace cluster {
  /* ********************************************************************* */

  void svd(int m, int n, double** u, double w[], double** v, int* ierr)
    /*
     *   This subroutine is a translation of the Algol procedure svd,
     *   Num. Math. 14, 403-420(1970) by Golub and Reinsch.
     *   Handbook for Auto. Comp., Vol II-Linear Algebra, 134-151(1971).
     *
     *   This subroutine determines the singular value decomposition
     *        t
     *   A=usv  of a real m by n rectangular matrix, where m is greater
     *   then or equal to n.  Householder bidiagonalization and a variant
     *   of the QR algorithm are used.
     *
     *
     *   On input.
     *
     *      m is the number of rows of A (and u).
     *
     *      n is the number of columns of A (and u) and the order of v.
     *
     *      u contains the rectangular input matrix A to be decomposed.
     *
     *   On output.
     *
     *      w contains the n (non-negative) singular values of a (the
     *        diagonal elements of s).  they are unordered.  if an
     *        error exit is made, the singular values should be correct
     *        for indices ierr+1,ierr+2,...,n.
     *
     *      u contains the matrix u (orthogonal column vectors) of the
     *        decomposition.
     *        if an error exit is made, the columns of u corresponding
     *        to indices of correct singular values should be correct.
     *
     *      v contains the matrix v (orthogonal) of the decomposition.
     *        if an error exit is made, the columns of v corresponding
     *        to indices of correct singular values should be correct.
     *
     *      ierr is set to
     *        zero       for normal return,
     *        k          if the k-th singular value has not been
     *                   determined after 30 iterations.
     *
     *   Questions and comments should be directed to B. S. Garbow,
     *   Applied Mathematics division, Argonne National Laboratory
     *
     *   Modified to eliminate machep
     *
     *   Translated to C by Michiel de Hoon, Human Genome Center,
     *   University of Tokyo, for inclusion in the C Clustering Library.
     *   This routine is less general than the original svd routine, as
     *   it focuses on the singular value decomposition as needed for
     *   clustering. In particular,
     *     - We require m >= n
     *     - We calculate both u and v in all cases
     *     - We pass the input array A via u; this array is subsequently
     *       overwritten.
     *     - We allocate for the array rv1, used as a working space,
     *       internally in this routine, instead of passing it as an
     *       argument.
     *   2003.06.05
     */
  {
    int i, j, k, i1, k1, l1, its;
    double* rv1 = (double*)malloc(n*sizeof(double));
    double c, f, h, s, x, y, z;
    int l = 0;
    double g = 0.0;
    double scale = 0.0;
    double anorm = 0.0;
    *ierr = 0;
    /* Householder reduction to bidiagonal form */
    for (i = 0; i < n; i++)
    {
      l = i + 1;
      rv1[i] = scale * g;
      g = 0.0;
      s = 0.0;
      scale = 0.0;
      for (k = i; k < m; k++) scale += fabs(u[k][i]);
      if (scale != 0.0)
      {
        for (k = i; k < m; k++)
        {
          u[k][i] /= scale;
          s += u[k][i] * u[k][i];
        }
        f = u[i][i];
        g = (f >= 0) ? -sqrt(s) : sqrt(s);
        h = f * g - s;
        u[i][i] = f - g;
        if (i < n - 1)
        {
          for (j = l; j < n; j++)
          {
            s = 0.0;
            for (k = i; k < m; k++)
            {
              s += u[k][i] * u[k][j];
            }
            f = s / h;
            for (k = i; k < m; k++)
            {
              u[k][j] += f * u[k][i];
            }
          }
        }
        for (k = i; k < m; k++)
        {
          u[k][i] *= scale;
        }
      }
      w[i] = scale * g;
      g = 0.0;
      s = 0.0;
      scale = 0.0;
      if (i < n - 1)
      {
        for (k = l; k < n; k++)
        {
          scale += fabs(u[i][k]);
        }
        if (scale != 0.0)
        {
          for (k = l; k < n; k++)
          {
            u[i][k] /= scale;
            s += u[i][k] * u[i][k];
          }
          f = u[i][l];
          g = (f >= 0) ? -sqrt(s) : sqrt(s);
          h = f * g - s;
          u[i][l] = f - g;
          for (k = l; k < n; k++)
          {
            rv1[k] = u[i][k] / h;
          }
          for (j = l; j < m; j++)
          {
            s = 0.0;
            for (k = l; k < n; k++)
            {
              s += u[j][k] * u[i][k];
            }
            for (k = l; k < n; k++)
            {
              u[j][k] += s * rv1[k];
            }
          }
          for (k = l; k < n; k++)
          {
            u[i][k] *= scale;
          }
        }
      }
      anorm = std::max(anorm, fabs(w[i]) + fabs(rv1[i]));
    }
    /* accumulation of right-hand transformations */
    for (i = n - 1; i >= 0; i--)
    {
      if (i < n - 1)
      {
        if (g != 0.0)
        {
          for (j = l; j < n; j++)
          {
            v[j][i] = (u[i][j] / u[i][l]) / g;
          }

          /* double division avoids possible underflow */
          for (j = l; j < n; j++)
          {
            s = 0.0;
            for (k = l; k < n; k++)
            {
              s += u[i][k] * v[k][j];
            }
            for (k = l; k < n; k++)
            {
              v[k][j] += s * v[k][i];
            }
          }
        }
      }
      for (j = l; j < n; j++)
      {
        v[i][j] = 0.0;
        v[j][i] = 0.0;
      }
      v[i][i] = 1.0;
      g = rv1[i];
      l = i;
    }
    /* accumulation of left-hand transformations */
    for (i = n - 1; i >= 0; i--)
    {
      l = i + 1;
      g = w[i];
      if (i != n - 1)
      {
        for (j = l; j < n; j++)
        {
          u[i][j] = 0.0;
        }
      }
      if (g != 0.0)
      {
        if (i != n - 1)
        {
          for (j = l; j < n; j++)
          {
            s = 0.0;
            for (k = l; k < m; k++)
            {
              s += u[k][i] * u[k][j];
            }
            /* double division avoids possible underflow */
            f = (s / u[i][i]) / g;
            for (k = i; k < m; k++)
            {
              u[k][j] += f * u[k][i];
            }
          }
        }
        for (j = i; j < m; j++)
        {
          u[j][i] /= g;
        }
      }
      else
      {
        for (j = i; j < m; j++)
        {
          u[j][i] = 0.0;
        }
      }
      u[i][i] += 1.0;
    }
    /* diagonalization of the bidiagonal form */
    for (k = n - 1; k >= 0; k--)
    {
      k1 = k - 1;
      its = 0;
      while (1)
        /* test for splitting */
      {
        for (l = k; l >= 0; l--)
        {
          l1 = l - 1;
          if (fabs(rv1[l]) + anorm == anorm)
          {
            break;
          }
          /* rv1[0] is always zero, so there is no exit
           * through the bottom of the loop */
          if (fabs(w[l1]) + anorm == anorm)
            /* cancellation of rv1[l] if l greater than 0 */
          {
            c = 0.0;
            s = 1.0;
            for (i = l; i <= k; i++)
            {
              f = s * rv1[i];
              rv1[i] *= c;
              if (fabs(f) + anorm == anorm)
              {
                break;
              }
              g = w[i];
              h = sqrt(f*f + g*g);
              w[i] = h;
              c = g / h;
              s = -f / h;
              for (j = 0; j < m; j++)
              {
                y = u[j][l1];
                z = u[j][i];
                u[j][l1] = y * c + z * s;
                u[j][i] = -y * s + z * c;
              }
            }
            break;
          }
        }
        /* test for convergence */
        z = w[k];
        if (l == k) /* convergence */
        {
          if (z < 0.0)
            /*  w[k] is made non-negative */
          {
            w[k] = -z;
            for (j = 0; j < n; j++) v[j][k] = -v[j][k];
          }
          break;
        }
        else if (its == 30)
        {
          *ierr = k;
          break;
        }
        else
          /* shift from bottom 2 by 2 minor */
        {
          its++;
          x = w[l];
          y = w[k1];
          g = rv1[k1];
          h = rv1[k];
          f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2.0 * h * y);
          g = sqrt(f*f + 1.0);
          f = ((x - z) * (x + z) + h * (y / (f + (f >= 0 ? g : -g)) - h)) / x;
          /* next qr transformation */
          c = 1.0;
          s = 1.0;
          for (i1 = l; i1 <= k1; i1++)
          {
            i = i1 + 1;
            g = rv1[i];
            y = w[i];
            h = s * g;
            g = c * g;
            z = sqrt(f*f + h*h);
            rv1[i1] = z;
            c = f / z;
            s = h / z;
            f = x * c + g * s;
            g = -x * s + g * c;
            h = y * s;
            y = y * c;
            for (j = 0; j < n; j++)
            {
              x = v[j][i1];
              z = v[j][i];
              v[j][i1] = x * c + z * s;
              v[j][i] = -x * s + z * c;
            }
            z = sqrt(f*f + h*h);
            w[i1] = z;
            /* rotation can be arbitrary if z is zero */
            if (z != 0.0)
            {
              c = f / z;
              s = h / z;
            }
            f = c * g + s * y;
            x = -s * g + c * y;
            for (j = 0; j < m; j++)
            {
              y = u[j][i1];
              z = u[j][i];
              u[j][i1] = y * c + z * s;
              u[j][i] = -y * s + z * c;
            }
          }
          rv1[l] = 0.0;
          rv1[k] = f;
          w[k] = x;
        }
      }
    }
    free(rv1);
    return;
  }

}