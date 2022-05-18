/*! \page releasenotes Release Notes

- \b Sept/22/2011:
  - Increased version to 2.5.0
  - Added pre/post vertex array rendering callbacks to SoVertexShape to allow external handling of e.g. vertex attributes
  - Added SoFaceSet::sendAdjacency, SoLineSet::sendAdjacency, SoIndexedLineSet::sendAdjacency and SoIndexedTriangleSet::sendAdjacency to allow the usage
of geometry shader adjacency on triangles and lines.
  - Removed OpenGL 1.0 support
  - Integrated GLEW to support OpenGL extensions in Open Inventor
  - Replaced tab with spaces and renamed *.c++ files to *.h
  - Integrated Vertex Array rendering and Vertex Buffer Objects (VBO) for common shape nodes, see \ref performance for details
  - Added SoShapeHints::useVBO to enable/disable VBO rendering
  - Added SoField::enableContainerNotify() to allow disabling container notifications on field
  - Added SoIndexedTriangleSet as a more efficient replacement for SoIndexedFaceSet with triangles. 
  - Converted documentation to doxygen, original *.ivm documentation files have been integrated into the Inventor header files
  - Removed complexity handling from SoPointSet (all points are rendered regardless of complexity)
  - Increased complexity dependend tesselation of SoSphere, SoCylinder and SoCone

- \b May/02/2007: Mac OS X port of SGI Open Inventor based on our Windows/Linux port.
             The new version number is 2.4.0.

- \b May/01/2007: The font handling has been rewritten (SoFont, SoFontStyle). The
             following OS-dependent methods for font lookup are used: On Mac OS X
             fonts are loaded using the Apple Type Services - a font name in
             SoFont* may be the Postscript font name (e.g. 'LucidaGrande-Bold')
             or the regular font name (e.g. 'Lucida Grande Bold')). On Windows
             the given font name is append by "", ".ttf", ".pfa", ".pfb", ".otf"
             and looked up as a font file in the windows font directory. On Linux
             the given font name is append by "", ".ttf", ".pfa", ".pfb", ".otf"
             and looked up as a font file in /usr/share/data/fonts or in the
             directory pointed to by the FL_FONT_PATH environment variable. 

- \b Nov/23/2005: There are two new elements, So(GL)StencilBitsElement to enable
             nodes the management of OpenGL stencil buffer use and
             So(GL)PolygonOffsetElement to control use of the OpenGL polygon
             offset feature. The latter element is used by the new node
             SoPolygonOffset. In addition there are the new fields, SoSFVec2s
             and SoSFVec3s with the corresponding new basic type SbVec3s. Also
             added the lexically less (<) operator to SbString which facilitates
             its use with the C++ STL.
             Before using any of these new additions SoMeVis::init() must be
             called to make those class-types known to the Open Inventor run-time
             type system (just like calling SoDB::init()). The new version number
             is 2.3.2.

- \b Jul/07/2005: Got rid of OpenGL 1.0 extensions use. OpenGL 1.1 must be
             supported to run the Windows release. This fixes problems with
             drivers that supported OpenGL 1.1 but did not provide the new
             OpenGL 1.1 functionality as OpenGL 1.0 extensions.

- \b Apr/20/2005: Doubled internal parser buffers in SoInput and added buffer
             overflow checks. Now the buffers are 64 characters in size.
             Functions that have been fixed are: SoInput::readHex(),
             SoInput::readInteger(), SoInput::readUnsignedInteger(),
             SoInput::readReal(), and SoInput::readDigits().

- \b Apr/11/2005: Fixed an inconsistent behavior of the SoSelection node. If
             pick matching is enabled, the SoButtonEvent::DOWN of the first
             mouse button will not be passed to nodes right to the SoSelection
             node anymore since SoButtonEvent::UP will handle the event in any
             case and both form an integrated whole.

- \b Mar/22/2005: Added more detailed version information to <Inventor/SbBasic.h>.
             The version has been increased to 2.2.0 to reflect the new
             functionality.
             \code
             #define SO_VERSION                 2
             #define SO_VERSION_REVISION        2
             #define SO_VERSION_PATCHLEVEL      0
             #define SGI_VERSION                20200
             \endcode

- \b Mar/18/2005: Fixed a nasty bug in SoVertexProperty that was causing a
             stack overflow when using packed colors in the orderedRGBA
             field. Only the WIN32 port was affected. Imported current
             CVS changes from oss.sgi.com.

- \b Nov/17/2004: The MeVis Open Inventor port is now able to catch, report,
             and suppress runtime crashes. A stack report of the recently
             called actions and traversed nodes can be generated to trace
             the cause of a crash. This feature is disabled by default
             and can be enabled at runtime using the
             SoCatch::enableExceptionHandling() function found in
             <Inventor/SoCatch.h>. To add finer tracing control to your
             own Open Inventor nodes you may use the macros provided in
             <Inventor/SoTrace.h>.

- \b Nov/04/2004: Added option to the Open Inventor installer to install
             API reference pages

- \b Oct/27/2004: UTF-8 support for path names in SoInput and SoOutput;
             Affected nodes: SoFile, SoTexture2

- \b Sep/01/2004: Check for valid (non-zero volume) bounding boxes of
             SoShape nodes when extending the scene bounding box
             in SoGetBoundingBoxAction. Added uint8_t, int8_t and
             uint16_t, int16_t types to inttypes.h

- \b May/25/2004: Set SoFocalDistanceElement in SoCamera during scene graph
             traversal

- \b Mar/30/2004: Interpret drive information in path correctly when using
             SoInput; Affected nodes: SoFile, SoTexture2

- \b Jul/23/2003: First release of the SGI Open Inventor Windows port

*/
