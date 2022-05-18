/* *****************************************************************************************
    Copyright 2021 MeVis Medical Solutions AG
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
***************************************************************************************** */

#ifndef FLENDIAN_H
#define FLENDIAN_H

#if defined (__GLIBC__)
# include <endian.h>
# if (__BYTE_ORDER == __LITTLE_ENDIAN)
#  define FL_LITTLE_ENDIAN
# elif (__BYTE_ORDER == __BIG_ENDIAN)
#  define FL_BIG_ENDIAN
# else
#  error Unknown machine endianness detected. The file FLEndian.h needs to be set up for your CPU type.
# endif
# define FL_BYTE_ORDER __BYTE_ORDER
#elif defined(__sparc) || defined(__sparc__) \
   || defined(_POWER) || defined(__powerpc__) \
   || defined(__ppc__) || defined(__ppc64__) \
   || defined(_MIPSEB) \
   || defined(__s390__) || defined(__hppa)
# define FL_BIG_ENDIAN
#elif defined(__i386__) || defined(__x86_64__) \
   || defined(__ia64) || defined(__ia64__) \
   || defined(_M_IX86) || defined(_M_IA64) \
   || defined(_M_ALPHA) || defined(_M_X64) \
   || defined(__alpha__) || defined(__aarch64__) \
   || defined(__arm__) || defined(__arm64__)
# define FL_LITTLE_ENDIAN
#else
# error The file FLEndian.h needs to be set up for your CPU type.
#endif


namespace FL
{
  constexpr auto correctEndianes(const GLubyte* value)
  {
#ifdef FL_LITTLE_ENDIAN
     return static_cast<GLuint>(value[1] << 8) | value[0];
#else
    return static_cast<GLuint>(value[0] << 8) | value[1]);
#endif
  }
}



#endif  /*FLENDIAN_H */
