/*! \page environment Environment Variables
  The following environment variables can be set to influence the behaviour of Open Inventor:

  <table>
  <tr><td>IV_SEPARATOR_MAX_CACHES<td>Set the default number of render caches on SoSeparator
  <tr><td>IV_NO_VERTEX_ARRAY<td>if set, turns off vertex array rendering and uses deprecated immediate mode rendering
  <tr><td>IV_NO_VBO<td>if set, no VBOs are used (but vertex array rendering will still be used)
  <tr><td>IV_NO_NPOT<td>if set, no non-power-of-two textures are used by SoTexture2
  </table>

  These additional enviroment variables can be used in the debug version:

  <table>
  <tr><td>IV_DEBUG_CACHES<td>debug info on the cache usage
  <tr><td>IV_DEBUG_CACHELIST<td>debug info on the cache list 
  <tr><td>IV_DEBUG_MATRIX_CULL<td>debug info on matrix culling
  <tr><td>IV_DEBUG_RENDER_CULL<td>prints infos on culling while rendering 
  <tr><td>IV_DEBUG_PICK_CULL<td>prints infos on culling while picking 
  <tr><td>IV_DEBUG_SENSORS<td>prints infos on sensors
  <tr><td>IV_DEBUG_TRANSFORM_MANIP_FIELDS<td>prints infos on transform manipulator fields
  <tr><td>IV_DEBUG_WRITE_KIT_CHILDREN<td>prints infos when writing kit children
  <tr><td>IV_DEBUG_KIT_PARTS<td>prints infos on kit parts
  </table>

  These additional (MeVis only) enviroment variables can be used in the debug version:

  <table>
  <tr><td>IV_DEBUG_VBO_RENDERING<td>prints infos when VBO rendering is used 
  <tr><td>IV_DEBUG_LEGACY_RENDERING<td>prints when legacy immediate mode rendering is used instead of Vertex Array rendering
  </table>

*/
