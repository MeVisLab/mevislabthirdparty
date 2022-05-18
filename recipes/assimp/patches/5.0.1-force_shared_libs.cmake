diff --git i/assimpTargets.cmake.in w/assimpTargets.cmake.in
index ab1a8d2..68e2c0d 100644
--- i/assimpTargets.cmake.in
+++ w/assimpTargets.cmake.in
@@ -51,11 +51,7 @@ if(_IMPORT_PREFIX STREQUAL "/")
 endif()
 
 # Create imported target assimp::assimp
-if(@BUILD_SHARED_LIBS@)
-  add_library(assimp::assimp SHARED IMPORTED)
-else()
-  add_library(assimp::assimp STATIC IMPORTED)
-endif()
+add_library(assimp::assimp SHARED IMPORTED)
 
 set_target_properties(assimp::assimp PROPERTIES
   COMPATIBLE_INTERFACE_STRING "assimp_MAJOR_VERSION"
