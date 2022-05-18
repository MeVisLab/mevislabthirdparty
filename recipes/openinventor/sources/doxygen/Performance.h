
/*! \page performance Performance Considerations
  This Open Inventor implementation supports rendering using vertex arrays.
  To really use vertex array rendering and VBOs, you have to make sure to only use
  special modes of the various possible material/normal/etc. binding modes.

  Vertex array rendering is typically activated if the rendering is done
  with a PER_VERTEX or OVERALL binding on non-indexed shapes and
  with a PER_VERTEX_INDEXED or OVERALL binding on indexed shapes.

  A good way to debug the vertex array rendering is to use the
  \c IV_DEBUG_VBO_RENDERING and \c IV_DEBUG_LEGACY_RENDERING environment variables
  in the debug version. This will print detailed info if vertex array rendering
  or legacy rendering is used on nodes that support both.

  Nodes that support vertex array rendering and VBOs:

  - SoIndexedTriangleSet
  - SoIndexedFaceSet (with triangles and quads)
  - SoIndexedLineSet (with 2 indices per line)
  - SoFaceSet (with triangles and quads)
  - SoPointSet
  - SoLineSet

  Nodes that do NOT (yet) support vertex array rendering:

  - SoIndexedTriangleStripSet, SoTriangleStripSet (triangle strips are out-of-date)
  - SoQuadMesh
  - SoNURBS*
  - SoCube, SoCylinder, SoCone, SoSphere
  - all other nodes not mentioned in the supported list above

*/
