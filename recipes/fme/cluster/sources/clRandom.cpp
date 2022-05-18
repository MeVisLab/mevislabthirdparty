// **InsertLicense** code
//----------------------------------------------------------------------------------
//! Implementation file for random generator functions
/*!
// \file    mlRanlib.cpp
// \author  Jan Klein
// \date    02/2006
*/


#ifdef WIN32

// Suppress useless warnings on windows.
//! Warning disabled: 'warning C4514': unreferenced inline/local function has been removed
#pragma warning(disable : 4514 )

#endif

#include "clRandom.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <chrono>
#include <random>

namespace cluster {

  typedef std::mt19937 DefaultRandomEngine;
  typedef DefaultRandomEngine::result_type Seed;


  DefaultRandomEngine getRandomEngine();

  void genprm(long *iarray, int larray)
  {
    static long i, itmp, iwhich, D1, D2;

    for (i = 1, D1 = 1, D2 = (larray - i + D1) / D1; D2 > 0; D2--, i += D1)
    {
      iwhich = ignuin(i, larray);
      itmp = *(iarray + iwhich - 1);
      *(iarray + iwhich - 1) = *(iarray + i - 1);
      *(iarray + i - 1) = itmp;
    }
  }

  float genunf(float low, float high)
  {
    static float genunf;

    if ((low > high))
    {
      fprintf(stderr, "LOW > HIGH in GENUNF: LOW %16.6E HIGH: %16.6E\n", low, high);
      fputs("Abort", stderr);
      exit(1);
    }
    else
    {
      genunf = low + (high - low)*ranf();
      return genunf;
    }
  }


  long ignuin(long low, long high)
  {
    std::uniform_int_distribution<long> distribution(low, high);
    DefaultRandomEngine engine = getRandomEngine();
    return distribution(engine);
  }


  long ignlgi(void)
  {
    const int min = 1;
    const int max = 2147483562;

    return ignuin(min, max);
  }


  float ranf(void)
  {
    std::uniform_real_distribution<float> distribution(0, 1);
    DefaultRandomEngine engine = getRandomEngine();

    return distribution(engine);
  }

  DefaultRandomEngine getRandomEngine()
  {
    Seed seed = static_cast<Seed>(std::chrono::system_clock::now().time_since_epoch().count());
    DefaultRandomEngine generator(seed);

    return generator;
  }
}
