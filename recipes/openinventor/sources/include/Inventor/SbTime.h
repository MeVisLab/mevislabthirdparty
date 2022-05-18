/*
 *
 *  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 *  Mountain View, CA  94043, or:
 *
 *  http://www.sgi.com
 *
 *  For further information regarding this notice, see:
 *
 *  http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */


/*
 * Copyright (C) 1990,91   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.3 $
 |
 |   Description:
 |      This file defines the SbTime class for manipulating times
 |
 |   Classes:
 |      SbTime
 |
 |   Author(s)          : Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_TIME_
#define _SB_TIME_

#include <Inventor/system/SbSystem.h>
#ifdef WIN32
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif
#include <math.h>
#include <limits.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbString.h>


////////////////////////////////////////////////////////////////////////////////
//! Class for representation of a time.
/*!
\class SbTime
\ingroup Basics
This class represents and performs operations on time. Operations may be
done in seconds, seconds and microseconds, or using a
<tt>struct timeval</tt>
(defined in <em>/usr/include/sys/time.h</em>).

\par See Also
\par
cftime
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbTime {
  public:

    //! Default constructor.
    SbTime()                                    {}

    //! Constructor taking seconds.
    SbTime(double sec);

    //! Constructor taking seconds + microseconds
    SbTime(time_t sec, long usec)               //!< System long from <sys/time.h>
        { t.tv_sec = static_cast<long>(sec); t.tv_usec = usec; }

  private:
    //! Constructor taking milliseconds
    //!
    //! NOTE! This constructor has been removed.  Change existing uses of
    //!          SbTime(msec)
    //! to
    //!          time_t secs = msec / 1000;
    //!          SbTime(secs, 1000 * (msec - 1000 * sec))
    //! The constructor was removed because it led to unexpected results --
    //! while SbTime(1.0) results in 1 second, SbTime(1) resulted in 1
    //! MILLIsecond).  Its declaration has been kept, as "private", so that
    //! existing code using it will get compilation errors; if it was removed
    //! completely, an existing use of SbTime(1) would silently cast to
    //! SbTime(1.0) resulting in hard-to-find bugs.  This declaration
    //! will be removed entirely in a future release, so that SbTime(1)
    //! will be equivalent to SbTime(1.0).
    SbTime(uint32_t msec);
  public:

    //! Constructors taking timeval.
    SbTime(const struct timeval *tv)
        { t.tv_sec = tv->tv_sec; t.tv_usec = tv->tv_usec; }

    //! Get the current time (seconds since Jan 1, 1970).
    static SbTime               getTimeOfDay();

    //! Set to the current time (seconds since Jan 1, 1970).
    void                        setToTimeOfDay();

    //! Get a zero time.
    static SbTime               zero()
        { return SbTime(0, 0); }

#ifndef INT32_MAX
#define INT32_MAX INT_MAX
#endif // !INT32_MAX

#ifdef WIN32
#undef max
#endif

    //! Get a time far, far into the future.
    static SbTime               max()
        { return SbTime(INT32_MAX, 999999); }

    //! Set time from a double (in seconds).
    void                setValue(double sec)
#ifdef __sgi
        { t.tv_sec = time_t(trunc(sec));
#else
        { t.tv_sec = time_t(int(sec));
#endif // __sgi
          t.tv_usec = long((sec - t.tv_sec) * 1000000.0); }

    //! Set time from seconds + microseconds
    void                setValue(time_t sec, long usec)         //!< System long
        { t.tv_sec = static_cast<long>(sec); t.tv_usec = usec; }

    //! Set time from a \p struct timeval.
    void                setValue(const struct timeval *tv)
        { t.tv_sec = tv->tv_sec; t.tv_usec = tv->tv_usec; }

    //! Set time from milliseconds.
    void                setMsecValue(unsigned long msec)        // System long
        { t.tv_sec = time_t(msec/1000);
          t.tv_usec = long(1000 * (msec % 1000)); }

    //! Get time in seconds as a double
    double              getValue() const
        { return (double) t.tv_sec + (double) t.tv_usec / 1000000.0; }

    //! Get time in seconds & microseconds
    void                getValue(time_t &sec, long &usec) const  //!< System long
        { sec = t.tv_sec; usec = t.tv_usec; }

    //! Get time in a struct timeval
    void                getValue(struct timeval *tv) const
        { tv->tv_sec = t.tv_sec; tv->tv_usec = t.tv_usec; }

    //! Get time in milliseconds (for Xt).
    unsigned long       getMsecValue() const                    // System long
        { return t.tv_sec * 1000 + t.tv_usec / 1000; }

    //! Convert to a string.  The default format is seconds with 3 digits of fraction
    //! precision.  \p fmt is a character string that consists of field descriptors and
    //! text characters, in a manner analogous to cftime (3C) and printf (3S).
    //! Each field descriptor consists of a % character followed by another character
    //! which specifies the replacement for the field descriptor.  All other characters
    //! are copied from \p fmt into the result.  The following field descriptors are
    //! supported:
    //! \code
    //! %   the `%' character
    //! D   total number of days
    //! H   total number of hours 
    //! M   total number of minutes
    //! S   total number of seconds
    //! I   total number of milliseconds
    //! U   total number of microseconds
    //! h   hours remaining after the days (00-23)
    //! m   minutes remaining after the hours (00-59)
    //! s   seconds remaining after the minutes (00-59)
    //! i   milliseconds remaining after the seconds (000-999)
    //! u   microseconds remaining after the seconds (000000-999999)
    //! \endcode
    //! The uppercase descriptors are formatted with a leading `em' for negative 
    //! times; the lowercase descriptors are formatted fixed width, with leading 
    //! zeros.  For example, a reasonable format string might be
    //! "elapsedtime:%Mminutes,%sseconds". The default value of \p fmt,
    //! "%S.%i", formats the time as seconds with 3 digits of fractional precision.
    SbString                    format(const char *fmt = "%S.%i") const;

    //! Convert to a date string, interpreting the time as seconds since
    //! Jan 1, 1970.  The default format gives "Tuesday, 01/26/93 11:23:41 AM".
    //! See the cftime() reference page for explanation of the format string.
    SbString                    formatDate(const char *fmt = "%A, %D %r") const;

    //! Addition
    friend INVENTOR_API SbTime          operator +(const SbTime &t0, const SbTime &t1);

    //! Subtraction
    friend INVENTOR_API SbTime          operator -(const SbTime &t0, const SbTime &t1);

    //! Addition and subtraction of two times which modifies the time structure.
    SbTime &                    operator +=(const SbTime &tm)
        { return (*this = *this + tm); }

    //! Addition and subtraction of two times which modifies the time structure.
    SbTime &                    operator -=(const SbTime &tm)
        { return (*this = *this - tm); }

    //! Unary negation
    SbTime                      operator -() const
        { return (t.tv_usec == 0) ? SbTime(- t.tv_sec, 0)
              : SbTime(- t.tv_sec - 1, 1000000 - t.tv_usec); }

    //! multiplication by scalar
    friend INVENTOR_API SbTime          operator *(const SbTime &tm, double s);

    friend INVENTOR_API SbTime          operator *(double s, const SbTime &tm);

    //! Destructive multiplication and division by scalar.
    SbTime &                    operator *=(double s)
        { *this = *this * s; return *this; }

    //! division by scalar
    friend INVENTOR_API SbTime          operator /(const SbTime &tm, double s);

    //! Destructive multiplication and division by scalar.
    SbTime &                    operator /=(double s)
        { return (*this = *this / s); }

    //! division by another time
    double                      operator /(const SbTime &tm) const
        { return getValue() / tm.getValue(); }

    //! Modulus for two times (remainder when time1 is divided by time2).
    SbTime                      operator %(const SbTime &tm) const
        { return *this - tm * floor(*this / tm); }

    //! Equality operators.
    bool                           operator ==(const SbTime &tm) const
        { return (t.tv_sec == tm.t.tv_sec) && (t.tv_usec == tm.t.tv_usec); }

    //! Equality operators.
    bool                           operator !=(const SbTime &tm) const
        { return ! (*this == tm); }

    //! Relational operators.
    inline bool                 operator <(const SbTime &tm) const;
    //! Relational operators.
    inline bool                 operator >(const SbTime &tm) const;
    //! Relational operators.
    inline bool                 operator <=(const SbTime &tm) const;
    //! Relational operators.
    inline bool                 operator >=(const SbTime &tm) const;

  private:
    struct timeval              t;
};

INVENTOR_API SbTime          operator +(const SbTime &t0, const SbTime &t1);
INVENTOR_API SbTime          operator -(const SbTime &t0, const SbTime &t1);
INVENTOR_API SbTime          operator *(const SbTime &tm, double s);
inline INVENTOR_API SbTime   operator *(double s, const SbTime &tm)
{ return tm * s; }
INVENTOR_API SbTime          operator /(const SbTime &tm, double s);


inline bool
SbTime::operator <(const SbTime &tm) const
{
    if ((t.tv_sec < tm.t.tv_sec) ||
        (t.tv_sec == tm.t.tv_sec && t.tv_usec < tm.t.tv_usec))
        return TRUE;
    else
        return FALSE;
}

inline bool
SbTime::operator >(const SbTime &tm) const
{
    if ((t.tv_sec > tm.t.tv_sec) ||
        (t.tv_sec == tm.t.tv_sec && t.tv_usec > tm.t.tv_usec))
        return TRUE;
    else
        return FALSE;
}

inline bool
SbTime::operator <=(const SbTime &tm) const
{
    if ((t.tv_sec < tm.t.tv_sec) ||
        (t.tv_sec == tm.t.tv_sec && t.tv_usec <= tm.t.tv_usec))
        return TRUE;
    else
        return FALSE;
}

inline bool
SbTime::operator >=(const SbTime &tm) const
{
    if ((t.tv_sec > tm.t.tv_sec) ||
        (t.tv_sec == tm.t.tv_sec && t.tv_usec >= tm.t.tv_usec))
        return TRUE;
    else
        return FALSE;
}


#endif /* _SB_TIME_ */
