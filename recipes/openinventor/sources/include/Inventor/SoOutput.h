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
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file contains the definition of the SoOutput class.
 |
 |   Classes:
 |      SoOutput
 |
 |   Author(s)          : Paul S. Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_OUTPUT_
#define  _SO_OUTPUT_

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbDict.h>
#include <Inventor/SbString.h>

class SoBase;

typedef void *SoOutputReallocCB(void *ptr, size_t newSize);


////////////////////////////////////////////////////////////////////////////////
//! Used to write Inventor data files.
/*!
\class SoOutput
\ingroup General
This class is used for writing Inventor data files.  It supports both
ASCII (default) and binary formats and provides some convenience
functions for handling files.  It can also write to a buffer in memory
as well as to a file pointer.  
A user-defined header can be specified for the output file.
An instance of SoOutput is
contained in an SoWriteAction; this is typically the only instance
needed.

\par See Also
\par
SoInput, SoWriteAction, SoTranSender
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoOutput {
 public:

    //! Constructor and destructor. The default SoOutput writes to stdout.
    //! The destructor closes any files opened by the SoOutput.
    SoOutput();

    //! Constructor and destructor. The default SoOutput writes to stdout.
    //! The destructor closes any files opened by the SoOutput.
    ~SoOutput();

    //! Sets file pointer to write to.
    void                setFilePointer(FILE *newFP);

    //! Returns the file pointer in use, or NULL if using a buffer.
    FILE *              getFilePointer() const;

    //! Opens named file, sets file pointer to result. This returns FALSE on error.
    bool                openFile(const char *fileName);

    //! Closes current file if opened with
    //! openFile().
    void                closeFile();

    //! Sets up memory buffer to write to, initial size, reallocation function
    //! (which is called if there is not enough room in the buffer), and
    //! offset in the buffer at which to begin writing.  If the reallocation
    //! function returns NULL, writing will be disabled.
    void                setBuffer(void *bufPointer, size_t initSize,
                                  SoOutputReallocCB *reallocFunc, 
                                  int32_t offset = 0);

    //! Returns pointer to memory buffer being written to and the new size of
    //! the buffer. Returns FALSE if not writing into a buffer.
    bool                getBuffer(void *&bufPointer, size_t &nBytes) const;

    //! The total number of bytes allocated to a memory buffer may be larger
    //! than the number of bytes written. This returns that total number.
    size_t              getBufferSize() const { return bufSize; }

    //! Resets buffer for output again. Output starts over at beginning of buffer.
    void                resetBuffer();

    //! Sets whether output should be ASCII (default) or binary.
    void                setBinary(bool flag);

    //! Returns current state of binary flag.
    bool                isBinary() const                { return binary; }

    //! Sets the header for output files.
    //! This is useful, for example, if you have a file format that is
    //! a superset of the Inventor file format and you want Inventor
    //! to read the files.  It is highly recommend that in your new
    //! header you simply append to the header of the Inventor
    //! file format you are extending.
    //! For example, if a new file format is based on the Inventor 2.1 
    //! file format, register a header similar to:
    //! <tt>"#Inventor V2.1 ascii MY FILE FORMAT EXTENSION"</tt>
    //! Then all Inventor 2.1 applications (and later) can read the file.
    void                setHeaderString(const SbString &str);

    //! Resets the header for output files to be the default header.
    void                resetHeaderString();
    
    //! Returns the string representing the default ASCII header.
    static SbString     getDefaultASCIIHeader();
    //! Returns the string representing the default binary header.
    static SbString     getDefaultBinaryHeader();

    //! Sets the precision for writing floating point numbers, i.e.
    //! the number of significant digits. Floating point numbers
    //! are written using %.xg format, where 'x' is the value of
    //! the precision argument.
    void                setFloatPrecision(int precision);
                                                        
  SoEXTENDER public:

    //! Enum that determines stage of operation of writing
    enum Stage {
        COUNT_REFS,             //!< Count write references
        WRITE                   //!< Actually write to file
    };

    //! Sets/returns current stage of operation of action
    void                setStage(Stage stage)           { curStage = stage; }
    Stage               getStage() const                { return curStage; }

    //! Increments/decrements indentation level by amount (default 1).
    //! Each indentation level is 4 spaces.
    void                incrementIndent(int amount = 1)
        { indentLevel += amount; }
    void                decrementIndent(int amount = 1)
        { indentLevel -= amount; }

    //! Writes item of particular type to current file pointer/buffer
    void                write(char           c);
    void                write(const char    *s);
    void                write(const SbString &s);
    void                write(const SbName   &n);
    void                write(int            i);
    void                write(unsigned int   i);
    void                write(short          s);
    void                write(unsigned short s);
    //! was ... C-api: name=writeInt32
    //!     but typedef makes this redundant
    //!void              write(int32_t        l);
    //! was ... C-api: name=writeUInt32
    //!     but typedef makes this redundant
    //!void              write(uint32_t       l);
    void                write(float          f);
    void                write(double         d);
    void                writeBinaryArray(unsigned char *c, int length);
    void                writeBinaryArray(int32_t *l, int length);
    void                writeBinaryArray(float *f, int length);
    void                writeBinaryArray(double *d, int length);

    //! Writes indentation to file/buffer based on current indentation level
    void                indent();

  SoINTERNAL public:

    //! Constructor and destructor. The default SoOutput writes to stdout.
    //! The destructor closes any files opened by the SoOutput.
    SoOutput(SoOutput *dictOut);

    //! Resets things for writing to a new file or changing files
    void                reset();

    //! Prevents header and extra white space from being written.
    //! Useful for producing compact strings of data.
    void                setCompact(bool flag)         { compact = flag; }
    bool                isCompact() const               { return compact; }

    //! Bit mask for various output annotations.  Note that annotation is
    //! automatically disabled for non-compact or binary format.
    enum Annotations {
        ADDRESSES  = (1<<0),    //!< pointer values
        REF_COUNTS = (1<<1)     //!< node reference counts
    };
    void                setAnnotation(uint32_t bits)
        { annotation = bits; }
    uint32_t            getAnnotation()
        { return (isCompact() || isBinary()) ? 0 : annotation; }

  private:
    FILE                *fp;            //!< File writing to
    bool                toBuffer;       //!< TRUE if writing to buffer
    char                *tmpBuffer;     //!< For binary write to file
    void                *buffer;        //!< Buffer writing to
    char                *curBuf;        //!< Current pointer in buffer
    size_t              bufSize;        //!< Maximum buffer size
    size_t              tmpBufSize;     //!< Maximum temporary buffer size
    SoOutputReallocCB   *reallocFunc;   //!< Reallocation function for buffer
    bool                openedHere;     //!< TRUE if SoOutput opened file
    bool                binary;         //!< TRUE if writing binary data
    bool                compact;        //!< TRUE if writing in compact form
    bool                wroteHeader;    //!< TRUE if header was written
    int                 indentLevel;    //!< Current indentation level
    SbDict              *refDict;       //!< SoBase pointer -> reference ID
    bool                borrowedDict;   //!< TRUE if dict from another SoOutput
    int                 refIdCount;     //!< Counter for generating ref IDs
    bool                anyRef;         //!< TRUE if any reference in dictionary
    uint32_t            annotation;     //!< annotation bit mask
    Stage               curStage;       //!< Stage of operation
    SbString            headerString;   //!< The header 
    SbString            fmtString;      //!< Output format

    //! Writes correct file header string to current file/buffer
    void                writeHeader();
    
    //! Pad a header so that it is correctly aligned for reading from
    //! binary files into memory
    static SbString     padHeader(const SbString &inString);

    //! Returns TRUE if writing into memory buffer rather than file
    bool                isToBuffer() const
        { return toBuffer; }

    //! Returns number of bytes in current buffer
    size_t              bytesInBuf() const
        { return (curBuf - (char *) buffer); }

    //! Makes sure current buffer can contain nBytes more bytes
    bool                makeRoomInBuf(size_t nBytes);

    //! Makes sure temporary buffer can contain nBytes more bytes
    bool                makeRoomInTmpBuf(size_t nBytes);

    //! Adds a reference to dictionary, returning the reference id
    //! created for it.
    int                 addReference(const SoBase *base);

    //! Looks up a reference, returning the reference id or -1 if it
    //! hasn't been added yet.
    int                 findReference(const SoBase *base) const;

    //! Convert datatypes to network format during writing
    void                convertShort(short s, char *to);
    void                convertInt32(int32_t l, char *to);
    void                convertFloat(float f, char *to);
    void                convertDouble(double d, char *to);
    void                convertShortArray( short *from, char *to, int len);
    void                convertInt32Array( int32_t *from, char *to, int len);
    void                convertFloatArray( float *from, char *to, int len);
    void                convertDoubleArray( double *from, char *to, int len);

friend class SoBase;
friend class SoDB;
};

#endif /* _SO_OUTPUT_ */

