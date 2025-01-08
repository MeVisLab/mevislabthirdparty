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
 * Copyright (C) 1990-93   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.5 $
 |
 |   Classes:
 |      SoOutput
 |
 |   Notes: This file includes any machine-dependent `dgl' (data goo lib)
 |   code for each machine.  See dgl.h.
 |
 |   Author(s)          : Paul S. Strauss, Dave Immel (dgl/cray)
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <stdio.h>
#include <stdlib.h>
#include <Inventor/errors/SoDebugError.h>

#include <Inventor/SoMachine.h>

#include <Inventor/SoDB.h>
#include <Inventor/SoOutput.h>
#include "utf8_filesupport_win32.h"

#include <stdio.h>
#include <iomanip>
#include <sstream>
#include <string>

static const char *defaultASCIIHeader =  "#Inventor V2.1 ascii";
static const char *defaultBinaryHeader = "#Inventor V2.1 binary";
    
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Constructor - sets output to stdout by default.
//
// Use: public

SoOutput::SoOutput()
//
////////////////////////////////////////////////////////////////////////
{
    fp          = stdout;
    buffer      = NULL;
    toBuffer    = FALSE;
    openedHere  = FALSE;
    anyRef      = FALSE;
    binary      = FALSE;
    compact     = FALSE;
    wroteHeader = FALSE;
    tmpBuffer   = NULL;
    tmpBufSize  = 0;
    refDict     = new SbDict;
    borrowedDict= FALSE;
    annotation  = 0;
    headerString = SbString("");
    float_precision = 0;

    reset();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Constructor that gets reference dictionary from another SoOutput.
//
// Use: internal

SoOutput::SoOutput(SoOutput *dictOut)
//
////////////////////////////////////////////////////////////////////////
{
    fp          = stdout;
    buffer      = NULL;
    toBuffer    = FALSE;
    openedHere  = FALSE;
    anyRef      = FALSE;
    binary      = FALSE;
    compact     = FALSE;
    wroteHeader = FALSE;
    tmpBuffer   = NULL;
    tmpBufSize  = 0;
    annotation  = 0;
    float_precision = 0;

    if (dictOut == NULL) {
        borrowedDict = FALSE;
        refDict = new SbDict;
    }
    else {
        borrowedDict = TRUE;
        refDict = dictOut->refDict;
    }

    reset();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor - closes output file if it was opened by SoOutput.
//
// Use: public

SoOutput::~SoOutput()
//
////////////////////////////////////////////////////////////////////////
{
    closeFile();

    if (! borrowedDict)
        delete refDict;

    if (tmpBuffer != NULL)
        free((void *)tmpBuffer);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets file pointer to write to; resets indentation level.
//
// Use: public

void
SoOutput::setFilePointer(FILE *newFP)           // New file pointer
//
////////////////////////////////////////////////////////////////////////
{
#ifdef DEBUG
    if (newFP == NULL)
        SoDebugError::postWarning("SoOutput::setFilePointer",
                                  "Setting file pointer to NULL - "
                                  "may cause problems");
#endif /* DEBUG */

    // Close open file, if any
    closeFile();

    fp          = newFP;
    openedHere  = FALSE;
    wroteHeader = FALSE;
    toBuffer    = FALSE;

    if (isBinary() && (tmpBuffer == NULL)) {
        tmpBuffer = (char *)malloc(64);
        tmpBufSize = 64;
    }

    reset();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns file pointer writing to, or NULL if writing to buffer.
//
// Use: public

FILE *
SoOutput::getFilePointer() const
//
////////////////////////////////////////////////////////////////////////
{
    return isToBuffer() ? NULL : fp;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Opens named file, sets file pointer to result. If it can't open
//    the file, it prints an error message, leaves the file pointer
//    alone, and returns FALSE.
//
// Use: public

bool
SoOutput::openFile(const char *fileName)        // Name of file
//
////////////////////////////////////////////////////////////////////////
{
#ifdef WIN32
    FILE *newFP = fopen_utf8(fileName, "wb");
#else
    FILE *newFP = fopen(fileName, "w");
#endif

    // Close open file, if any
    closeFile();

    if (newFP == NULL) {
        SoDebugError::post("SoOutput::openFile",
                           "Can't open file \"%s\" for writing", fileName);
        return FALSE;
    }

    fp          = newFP;
    openedHere  = TRUE;
    wroteHeader = FALSE;
    toBuffer    = FALSE;

    reset();

    if (isBinary() && (tmpBuffer == NULL)) {
        tmpBuffer = (char *)malloc(64);
        tmpBufSize = 64;
    }

    return TRUE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Closes current file if it was opened with openFile(). If not,
//    this does nothing, so it's always safe to call.
//
// Use: public

void
SoOutput::closeFile()
//
////////////////////////////////////////////////////////////////////////
{
    if (openedHere) {
        fclose(fp);
        openedHere = FALSE;
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets up buffer to write to, initial size, reallocation function,
// and offset at which to start writing.
//
// Use: public

void
SoOutput::setBuffer(void *bufPointer, size_t initSize,
                    SoOutputReallocCB *f, int32_t offset)
//
////////////////////////////////////////////////////////////////////////
{
    buffer  = bufPointer;
    curBuf  = (char *) bufPointer;
    bufSize = initSize;
    reallocFunc = f;
    
    // make sure there are enough bytes in buffer to start writing at offset
    if (offset > 0) {
        makeRoomInBuf((int) (offset + 1));
        curBuf = (char *) buffer + (int) offset;
    }
    
    if (tmpBuffer != NULL) {
        free( (void *)tmpBuffer );
        tmpBuffer = NULL;
        tmpBufSize = 0;
    }

    wroteHeader = FALSE;

    toBuffer = TRUE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns pointer to buffer and the buffer's new size.
//    Returns FALSE if not writing into buffer.
//
// Use: public

bool
SoOutput::getBuffer(void *&bufPointer, size_t &nBytes) const
//
////////////////////////////////////////////////////////////////////////
{
    if (isToBuffer()) {
        bufPointer = buffer;
        nBytes     = bytesInBuf();

        return TRUE;
    }

    return FALSE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Resets buffer for output again; output starts over at beginning.
//
// Use: public

void
SoOutput::resetBuffer()
//
////////////////////////////////////////////////////////////////////////
{
    curBuf = (char *) buffer;

    wroteHeader = FALSE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Indicates whether output should be ASCII (default) or binary.
//
// Use: public

void
SoOutput::setBinary(bool flag)
//
////////////////////////////////////////////////////////////////////////
{
    binary = flag;

    // If writing to file, initialize the temporary output for buffering
    // data before writing.
    if (!isToBuffer())
    {
        tmpBuffer = (char *)malloc(64);
        tmpBufSize = 64;
    }

}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets the precision for outputing real numbers
//
// Use: public

void
SoOutput::setFloatPrecision(int precision)
//
////////////////////////////////////////////////////////////////////////
{
    char tmp[8];

    // Invalid precision specified; use default format string
    if (precision < 0 || precision > 8)
    {
#ifdef DEBUG
        SoDebugError::postWarning("SoOutput::setFloatPrecision",
                "Precision (significant digits) must be between 0 "
                "and 8 for %.xg format");
#endif /* DEBUG */
        float_precision = 0;
    }

    // Build the output format string from the input parameters
    else
    {
        float_precision = precision;
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets the header to be used for writing the file to be a 
//    user-specified string.
//
// Use: public

void
SoOutput::setHeaderString(const SbString &str)
//
////////////////////////////////////////////////////////////////////////
{
    headerString = str;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Reset the user-specified header string, so that the default headers
//    will be used
//
// Use: public

void
SoOutput::resetHeaderString()
//
////////////////////////////////////////////////////////////////////////
{
    headerString.makeEmpty();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Return the default ASCII header string (ie the latest version
//    of the standard Inventor ascii header)
//
// Use: public, static

SbString
SoOutput::getDefaultASCIIHeader()
//
////////////////////////////////////////////////////////////////////////
{
    return (SbString(defaultASCIIHeader));
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Return the default Binary header string (ie the latest version
//    of the standard Inventor binary header).  Note binary headers
//    must always be padded for correct alignment in binary files.
//
// Use: public, static

SbString
SoOutput::getDefaultBinaryHeader()
//
////////////////////////////////////////////////////////////////////////
{
    return (SoOutput::padHeader(SbString(defaultBinaryHeader)));
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Pad a string to a valid length for binary headers (ie one less
//    than a multiple of 4)
//
// Use: private, static

SbString
SoOutput::padHeader(const SbString &str)
//
////////////////////////////////////////////////////////////////////////
{
    SbString paddedStr(str);
    
    int pad = 3 - (str.getLength()%4);    
    for (int i = 0; i < pad; i++)
        paddedStr += " ";
        
    return (paddedStr);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes a character to current file/buffer.
//
// Use: public

void
SoOutput::write(char c)
//
////////////////////////////////////////////////////////////////////////
{
    if (! wroteHeader)
        writeHeader();

    if (isToBuffer() && ! makeRoomInBuf(4))
        return;

    if (isBinary()) {
        if (isToBuffer()) {
            *curBuf++ = c;
            *curBuf++ = 0;
            *curBuf++ = 0;
            *curBuf++ = 0;
        }
        else {
            *tmpBuffer = c;
            tmpBuffer[1] = 0;
            tmpBuffer[2] = 0;
            tmpBuffer[3] = 0;
            fwrite((void *)tmpBuffer, M_SIZEOF(char), 4, fp);
            fflush(fp);
        }
    }

    else if (! isToBuffer())
        putc(c, fp);

    else
        *curBuf++ = c;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes a NULL-terminated character string to current file/buffer.
//
// Use: public

void
SoOutput::write(const char *s)
//
////////////////////////////////////////////////////////////////////////
{
    int n = static_cast<int>(strlen(s));
    int nsize = (n + 3) & ~0003;

    if (! wroteHeader)
        writeHeader();


    if (isToBuffer() && ! makeRoomInBuf(nsize)) // Leave room for end NUL char
        return;

    if (isBinary())
    {
        //
        // Writing a binary string consists of writing a word representing
        // the string length without the NULL character, followed by the
        // string, followed by padding out to the word boundary.
        //
        if (isToBuffer()) {
            int m = n;
            DGL_HTON_INT32(m, n);
            *((int *)curBuf) = m;
            curBuf += 4;
            memcpy((void *)curBuf, (const void *)s, n);
            curBuf += n;
            for (int i=0; i<(nsize-n); i++) 
                *curBuf++ = 0;
        }
        else {
            if (!makeRoomInTmpBuf(nsize))
                return;
            int m = n;
            DGL_HTON_INT32(m, n);
            fwrite((void *)&m, sizeof(int), 1, fp);
            memcpy(tmpBuffer, (const void *)s, n);
            for (int i=0; i<(nsize-n); i++) 
                tmpBuffer[n+i] = 0;
            fwrite((void *)tmpBuffer, sizeof(char), nsize, fp);
            fflush(fp);
        }
    }

    else if (! isToBuffer())
        fputs(s, fp);

    else {
        strcpy(curBuf, s);
        curBuf += n;            // Don't increment over NUL char
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes an SbString to current file/buffer. This will always write out
//    double quotes around the string and will make sure that
//    backslashes are properly escaped.
//
// Use: public

void
SoOutput::write(const SbString &s)
//
////////////////////////////////////////////////////////////////////////
{
    if (isBinary())
        write(s.getString());

    else {
        const char *c;

        write('\"');

        for (c = s.getString(); *c != '\0'; c++) {
            if (*c == '\"')
                write('\\');
            write(*c);
        }

        write('\"');
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes an SbName to current file/buffer. This will always write out
//    double quotes around the string and will make sure that
//    backslashes are properly escaped.
//
// Use: public

void
SoOutput::write(const SbName &s)
//
////////////////////////////////////////////////////////////////////////
{
    if (isBinary())
        write(s.getString());

    else {
        const char *c;

        write('\"');

        for (c = s.getString(); *c != '\0'; c++) {
            if (*c == '\"')
                write('\\');
            write(*c);
        }

        write('\"');
    }
}

////////////////////////////////////////////////////////////////////////
//
// This macro is used by all the functions that write numbers.
//
////////////////////////////////////////////////////////////////////////

#define WRITE_NUM(num, precision, isHex, dglFunc, dglType)                    \
    if (! wroteHeader)                                                        \
        writeHeader();                                                        \
    if (isBinary()) {                                                         \
        if (isToBuffer() && ! makeRoomInBuf(M_SIZEOF(dglType)))               \
            return;                                                           \
        if (isToBuffer()) {                                                   \
            dglFunc(num, curBuf);                                             \
            curBuf += M_SIZEOF(dglType);                                      \
        }                                                                     \
        else {                                                                \
            if (!makeRoomInTmpBuf(M_SIZEOF(dglType)))                         \
                return;                                                       \
            dglFunc(num, tmpBuffer);                                          \
            fwrite((void *)tmpBuffer, M_SIZEOF(dglType), 1, fp);              \
            fflush(fp);                                                       \
        }                                                                     \
    }                                                                         \
    else {                                                                    \
        std::ostringstream ostr;                                              \
        if (precision > 0) {                                                  \
            ostr << std::setprecision(precision);                             \
        }                                                                     \
        if (isHex) {                                                          \
            ostr << std::setbase(16) << "0x";                                 \
        }                                                                     \
        ostr << num;                                                          \
        std::string s = ostr.str();                                           \
        if (! isToBuffer()) {                                                 \
            std::fwrite(s.c_str(), s.size(), 1, fp);                          \
        }                                                                     \
        else {                                                                \
            write(ostr.str().c_str());                                        \
        }                                                                     \
    }

#define WRITE_BIN_ARRAY(type, array, length, dglFunc)                         \
    if (! wroteHeader)                                                        \
        writeHeader();                                                        \
    if (isToBuffer() && ! makeRoomInBuf(length*M_SIZEOF(type)))               \
        return;                                                               \
    if (isToBuffer()) {                                                       \
        dglFunc(array, curBuf, length);                                       \
        curBuf += length * M_SIZEOF(type);                                    \
    }                                                                         \
    else {                                                                    \
        if (!makeRoomInTmpBuf(length*M_SIZEOF(type)))                         \
            return;                                                           \
        dglFunc(array, tmpBuffer, length);                                    \
        fwrite((void *)tmpBuffer, M_SIZEOF(type), length, fp);                \
        fflush(fp);                                                           \
    }                                                                         \


////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes an integer to current file/buffer.
//
// Use: public

void
SoOutput::write(int i)
//
////////////////////////////////////////////////////////////////////////
{
    WRITE_NUM(i, 0, false, convertInt32, int32_t);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes an unsigned integer to current file/buffer.
//
// Use: public

void
SoOutput::write(unsigned int i)
//
////////////////////////////////////////////////////////////////////////
{
    WRITE_NUM(i, 0, true, convertInt32, int32_t);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes a short integer to current file/buffer.
//
// Use: public

void
SoOutput::write(short s)
//
////////////////////////////////////////////////////////////////////////
{
    int32_t l = (int32_t)s;
    WRITE_NUM(l, 0, false, convertInt32, int32_t);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes an unsigned short integer to current file/buffer.
//
// Use: public

void
SoOutput::write(unsigned short s)
//
////////////////////////////////////////////////////////////////////////
{
    uint32_t l = (uint32_t)s;
    WRITE_NUM(l, 0, true, convertInt32, int32_t);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes a int32_t integer to current file/buffer.
//
// Use: public

//     made redundant by typedef of int32_t
//void
//SoOutput::write(int32_t l)
////
//////////////////////////////////////////////////////////////////////////
//{
//    WRITE_NUM(l, 0, false, convertInt32, int32_t);
//}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes an uint32_teger to current file/buffer.
//
// Use: public

//     made redundant by typedef of uint32_t
//void
//SoOutput::write(uint32_t l)
////
//////////////////////////////////////////////////////////////////////////
//{
//    WRITE_NUM(l, 0, true, convertInt32, int32_t);
//}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes a float to current file/buffer.
//
// Use: public

void
SoOutput::write(float f)
//
////////////////////////////////////////////////////////////////////////
{
    WRITE_NUM(f, float_precision, false, convertFloat, float);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes a double to current file/buffer.
//
// Use: public

void
SoOutput::write(double d)
//
////////////////////////////////////////////////////////////////////////
{
    WRITE_NUM(d, 16, false, convertDouble, double);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes an array of unsigned chars to current file/buffer.
//
// Use: public

void
SoOutput::writeBinaryArray(unsigned char *c, int length)
//
////////////////////////////////////////////////////////////////////////
{
    if (! wroteHeader)
        writeHeader();
    if (isToBuffer() && ! makeRoomInBuf(length*M_SIZEOF(unsigned char)))
        return;
    if (isToBuffer()) {
        memcpy(curBuf, c, length);
        curBuf += length * M_SIZEOF(unsigned char);
    }
    else {
        fwrite((void *)c, M_SIZEOF(unsigned char), length, fp);
        fflush(fp);
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes an array of int32_ts to current file/buffer.
//
// Use: public

void
SoOutput::writeBinaryArray(int32_t *l, int length)
//
////////////////////////////////////////////////////////////////////////
{
    WRITE_BIN_ARRAY(int32_t, l, length, convertInt32Array);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes an array of floats to current file/buffer.
//
// Use: public

void
SoOutput::writeBinaryArray(float *f, int length)
//
////////////////////////////////////////////////////////////////////////
{
    WRITE_BIN_ARRAY(float, f, length, convertFloatArray);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes an array of doubles to current file/buffer.
//
// Use: public

void
SoOutput::writeBinaryArray(double *d, int length)
//
////////////////////////////////////////////////////////////////////////
{
    WRITE_BIN_ARRAY(double, d, length, convertDoubleArray);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Converts short to network format and puts in buffer.
//
// Use: private

void
SoOutput::convertShort(short s, char *to)
//
////////////////////////////////////////////////////////////////////////
{
    int32_t l = (int32_t)s;
    char jjj[16];
    int i;

    DGL_HTON_INT32( INT32(jjj), l );
    for (i=0; i<M_SIZEOF(int32_t); i++)  to[i] = jjj[i];
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Converts long to network format and puts in buffer.
//
// Use: private

void
SoOutput::convertInt32(int32_t l, char *to)
//
////////////////////////////////////////////////////////////////////////
{
    char jjj[16];
    int i;

    DGL_HTON_INT32( INT32(jjj), l );

    for (i=0; i<M_SIZEOF(int32_t); i++)  to[i] = jjj[i];
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Converts float to network format and puts in buffer.
//
// Use: private

void
SoOutput::convertFloat(float f, char *to)
//
////////////////////////////////////////////////////////////////////////
{
    char jjj[64];
    int i;

    DGL_HTON_FLOAT( FLOAT(jjj), f );

    for (i=0; i<M_SIZEOF(float); i++)  to[i] = jjj[i];
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Converts double to network format and puts in buffer.
//
// Use: private

void
SoOutput::convertDouble(double d, char *to)
//
////////////////////////////////////////////////////////////////////////
{
    DGL_HTON_DOUBLE( DOUBLE(to), d );
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//    Converts array of shorts to network format and puts in buffer.
//
// Use: private

void
SoOutput::convertShortArray( short *from,
                             char *to,
                             int len)
//
////////////////////////////////////////////////////////////////////////
{
    char *b = to;

    while (len > 4) {           // unroll the loop a bit
        DGL_HTON_SHORT( SHORT(b), from[0]);
        DGL_HTON_SHORT( SHORT(b + M_SIZEOF(short)),   from[1]);
        DGL_HTON_SHORT( SHORT(b + M_SIZEOF(short)*2), from[2]);
        DGL_HTON_SHORT( SHORT(b + M_SIZEOF(short)*3), from[3]);
        b += M_SIZEOF(short)*4;
        from += 4;
        len -= 4;
    }
    while (len-- > 0) {
        DGL_HTON_SHORT( SHORT(b),*from);
        b += M_SIZEOF(short);
        from++;
    }
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//    Converts array of int32_ts to network format and puts in buffer.
//
// Use: private

void
SoOutput::convertInt32Array( int32_t *from,
                            char *to,
                            int len)
//
////////////////////////////////////////////////////////////////////////
{
    char  *b = to;
    int32_t  *f = from;

    while (len > 4) {           // unroll the loop a bit
        DGL_HTON_INT32( INT32(b), f[0]);
        DGL_HTON_INT32( INT32(b + M_SIZEOF(int32_t)),   f[1]);
        DGL_HTON_INT32( INT32(b + M_SIZEOF(int32_t)*2), f[2]);
        DGL_HTON_INT32( INT32(b + M_SIZEOF(int32_t)*3), f[3]);
        b += M_SIZEOF(int32_t)*4;
        f += 4;
        len -= 4;
    }
    while (len-- > 0) {
        DGL_HTON_INT32( INT32(b),*f);
        b += M_SIZEOF(int32_t);
        f++;
    }
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//    Converts array of floats to network format and puts in buffer.
//
// Use: private

void
SoOutput::convertFloatArray( float *from,
                             char *to,
                             int len)
//
////////////////////////////////////////////////////////////////////////
{
    char  *b = to;
    float *f = from;

    while (len > 4) {           // unroll the loop a bit
        DGL_HTON_FLOAT( FLOAT(b), f[0]);
        DGL_HTON_FLOAT( FLOAT(b + M_SIZEOF(float)),   f[1]);
        DGL_HTON_FLOAT( FLOAT(b + M_SIZEOF(float)*2), f[2]);
        DGL_HTON_FLOAT( FLOAT(b + M_SIZEOF(float)*3), f[3]);
        b += M_SIZEOF(float)*4;
        f += 4;
        len -= 4;
    }
    while (len-- > 0) {
        DGL_HTON_FLOAT( FLOAT(b),*f);
        b += M_SIZEOF(float);
        f++;
    }
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//    Converts array of doubles to network format and puts in buffer.
//
// Use: private

void
SoOutput::convertDoubleArray( double *from,
                              char *to,
                              int len )
//
////////////////////////////////////////////////////////////////////////
{
    char *b = to;

    while (len > 4) {           // unroll the loop a bit
        DGL_HTON_DOUBLE( DOUBLE(b), from[0]);
        DGL_HTON_DOUBLE( DOUBLE(b + M_SIZEOF(double)),   from[1]);
        DGL_HTON_DOUBLE( DOUBLE(b + M_SIZEOF(double)*2), from[2]);
        DGL_HTON_DOUBLE( DOUBLE(b + M_SIZEOF(double)*3), from[3]);
        b += M_SIZEOF(double)*4;
        from += 4;
        len -= 4;
    }
    while (len-- > 0) {
        DGL_HTON_DOUBLE( DOUBLE(b),*from);
        b += M_SIZEOF(double);
        from++;
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes indentation to file based on current indentation level.
//
// Use: public

void
SoOutput::indent()
//
////////////////////////////////////////////////////////////////////////
{
    int         i;

    for (i = indentLevel / 2; i > 0; --i)
        write('\t');

    if (indentLevel & 1) {
        write(' ');
        write(' ');
        write(' ');
        write(' ');
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Resets things for writing to a new file or changing files
//
// Use: internal

void
SoOutput::reset()
//
////////////////////////////////////////////////////////////////////////
{
    // If writing ASCII into buffer in memory, make sure it's
    // NULL-byte-terminated
    if (isToBuffer() && ! isBinary()) {
        write('\0');

        // However, subsequent writes (if any) should overwrite it
        curBuf--;
    }

    indentLevel  = 0;
    refIdCount = 0;

    if (anyRef) {

        // Clear dictionary
        refDict->clear();

        anyRef = FALSE;
        refIdCount = 0;
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes correct file header string to current file or buffer. The
//    header must be written in normal ASCII form since it is read in
//    ASCII to determine whether the data is ASCII or binary. So if we
//    are writing in binary, we have to stop temporarily.
//
// Use: private

void
SoOutput::writeHeader()
//
////////////////////////////////////////////////////////////////////////
{
    wroteHeader = TRUE;

    // Don't write header if writing in compact form
    if (compact)
        return;

    if (isBinary()) {
        binary = FALSE;
        if (headerString == "") {
            SbString defaultHeader = SoOutput::padHeader(defaultBinaryHeader);
            write(defaultHeader.getString());
        } else {
            // Make sure the string is padded for correct alignment, in case
            // it's used in a binary file
            SbString paddedString = SoOutput::padHeader(headerString);
            write(paddedString.getString());
        }  
        write('\n');
        binary = TRUE;
    }

    else {
        if (headerString == "")
            write(defaultASCIIHeader);
        else
            write(headerString.getString());
        write('\n');
        write('\n');
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Makes sure current buffer can contain nBytes more bytes. Returns
//    FALSE if this is not possible.
//
// Use: private

bool
SoOutput::makeRoomInBuf(size_t nBytes)
//
////////////////////////////////////////////////////////////////////////
{
    size_t      bytesUsed  = bytesInBuf();
    size_t      roomNeeded = bytesUsed + nBytes;

    // If already had problems with buffer, stop
    if (buffer == NULL)
        return FALSE;

    // If not enough room in buffer for nBytes more, realloc
    if (roomNeeded >= bufSize) {
        // While not enough room, double size of buffer
        while (roomNeeded >= bufSize)
            bufSize *= 2;
    
        // Now realloc a new buffer that is big enough
        buffer = (*reallocFunc)(buffer, bufSize);
    }
    
    // Test for bad reallocation
    if (buffer == NULL)
        return FALSE;
            
    // Readjust current buffer pointer
    curBuf = (char *) buffer + bytesUsed;

    return TRUE;
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//    Makes sure temporary buffer can contain nBytes more bytes. Returns
//    FALSE if this is not possible.
//
// Use: private

bool
SoOutput::makeRoomInTmpBuf(size_t nBytes)
//
////////////////////////////////////////////////////////////////////////
{
    if (tmpBuffer == NULL)
        return FALSE;
            
    // If not enough room in tmpBuffer for nBytes more, realloc
    if (nBytes >= tmpBufSize) {
        // While not enough room, double size of buffer
        while (nBytes >= tmpBufSize)
            tmpBufSize *= 2;
            
        // Now realloc a new buffer that is big enough
        tmpBuffer = (char *)::realloc((void *)tmpBuffer, tmpBufSize);
    }
    
    // Test for bad reallocation
    if (tmpBuffer == NULL)
        return FALSE;

    return TRUE;
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//    Adds a reference to dictionary, returning the name
//    created for the reference.  Called by SoBase::writeHeader.
//
// Use: private

int                                     // Returns reference id
SoOutput::addReference(const SoBase *base)      // Thing to enter
//
////////////////////////////////////////////////////////////////////////
{
    int referenceId = refIdCount++;

    refDict->enter(base, (void *) (size_t) referenceId);

    // Dictionary is now "dirty"
    anyRef = TRUE;

    return referenceId;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Finds a reference in dictionary, returning the name of the
//    reference. Returns NULL if not found.
//
// Use: private

int                                     // Returns reference ID
SoOutput::findReference(const SoBase *base      // Thing to look for
                        ) const
//
////////////////////////////////////////////////////////////////////////
{
    int referenceId = -1;
    void *ref;

    if (refDict->find(base, ref))
        referenceId = (int) ((size_t) ref);

    return referenceId;
}
