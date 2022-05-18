// **InsertLicense** code
//----------------------------------------------------------------------------------
/*!
// \file    mlRandomNumbers.h
// \author  Jan Klein
// \date    02/2006
*/

#pragma once

namespace cluster {

  //  generate random permutation of iarray
  extern void genprm(long *iarray, int larray);

  // generate uniform real between low and high
  extern float genunf(float low, float high);

  // Returns a random integer following a uniform distribution over
  // (1, 2147483562) using the current generator.
  extern long ignlgi(void);

  // Generates an integer uniformly distributed between LOW and HIGH.  
  extern long ignuin(long low, long high);

  // Returns a random floating point number from a uniform distribution over 0 - 1 
  extern float ranf(void);
}