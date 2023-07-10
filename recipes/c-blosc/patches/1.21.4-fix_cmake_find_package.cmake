diff --git i/CMakeLists.txt w/CMakeLists.txt
index f726a0a..ce277e3 100644
--- i/CMakeLists.txt
+++ w/CMakeLists.txt
@@ -142,7 +142,7 @@ if(NOT DEACTIVATE_LZ4)
     if(PREFER_EXTERNAL_LZ4)
         find_package(LZ4)
     else()
-        message(STATUS "Using LZ4 internal sources.")
+        message(FATAL_ERROR "No LZ4 found.")
     endif()
     # HAVE_LZ4 will be set to true because even if the library is
     # not found, we will use the included sources for it
@@ -155,7 +155,7 @@ if(NOT DEACTIVATE_SNAPPY)
         message(STATUS "Activating support for SNAPPY.")
         set(HAVE_SNAPPY TRUE)
     else()
-        message(STATUS "SNAPPY *not* found.  De-activating support for it.")
+        message(FATAL_ERROR "SNAPPY not found.")
     endif()
 endif()
 
@@ -165,7 +165,7 @@ if(NOT DEACTIVATE_ZLIB)
         set(ZLIB_ROOT $ENV{ZLIB_ROOT})
         find_package(ZLIB)
         if(NOT ZLIB_FOUND )
-            message(STATUS "No zlib found.  Using internal sources.")
+            message(FATAL_ERROR "No zlib found.")
         endif()
     else()
         message(STATUS "Using zlib internal sources.")
@@ -179,7 +179,7 @@ if(NOT DEACTIVATE_ZSTD)
     if(PREFER_EXTERNAL_ZSTD)
         find_package(Zstd)
     else()
-        message(STATUS "Using ZSTD internal sources.")
+        message(FATAL_ERROR "No ZSTD found.")
     endif()
     # HAVE_ZSTD will be set to true because even if the library is
     # not found, we will use the included sources for it
diff --git i/cmake/FindLZ4.cmake w/cmake/FindLZ4.cmake
index 2ae6d5f..96ca8e2 100644
--- i/cmake/FindLZ4.cmake
+++ w/cmake/FindLZ4.cmake
@@ -1,12 +1,12 @@
-find_path(LZ4_INCLUDE_DIR lz4.h)
+find_path(LZ4_INCLUDE_DIR lz4.h HINTS ${CONAN_INCLUDE_DIRS_LZ4})
 
 # On Windows, the lz4 library is called liblz4.lib, which is not
 # found by using the lz4 name.
-find_library(LZ4_LIBRARY NAMES lz4 liblz4)
+find_library(LZ4_LIBRARY NAMES ${CONAN_LIBS_LZ4} HINTS ${CONAN_LIB_DIRS_LZ4})
 
 if (LZ4_INCLUDE_DIR AND LZ4_LIBRARY)
     set(LZ4_FOUND TRUE)
     message(STATUS "Found LZ4 library: ${LZ4_LIBRARY}")
 else ()
-    message(STATUS "No LZ4 library found.  Using internal sources.")
+    message(STATUS "No LZ4 library found.")
 endif ()
diff --git i/cmake/FindSnappy.cmake w/cmake/FindSnappy.cmake
index 688d4d5..3793875 100644
--- i/cmake/FindSnappy.cmake
+++ w/cmake/FindSnappy.cmake
@@ -1,10 +1,10 @@
-find_path(SNAPPY_INCLUDE_DIR snappy-c.h)
+find_path(SNAPPY_INCLUDE_DIR NAMES snappy-c.h HINTS ${CONAN_INCLUDE_DIRS_SNAPPY})
 
-find_library(SNAPPY_LIBRARY NAMES snappy)
+find_library(SNAPPY_LIBRARY NAMES ${CONAN_LIBS_SNAPPY} HINTS ${CONAN_LIB_DIRS_SNAPPY})
 
 if (SNAPPY_INCLUDE_DIR AND SNAPPY_LIBRARY)
     set(SNAPPY_FOUND TRUE)
     message(STATUS "Found SNAPPY library: ${SNAPPY_LIBRARY}")
 else ()
-    message(STATUS "No snappy found.  Using internal sources.")
+    message(STATUS "No snappy found.")
 endif ()
diff --git i/cmake/FindZstd.cmake w/cmake/FindZstd.cmake
index 7db4bb9..ded2dc7 100644
--- i/cmake/FindZstd.cmake
+++ w/cmake/FindZstd.cmake
@@ -1,10 +1,10 @@
-find_path(ZSTD_INCLUDE_DIR zstd.h)
+find_path(ZSTD_INCLUDE_DIR NAMES zstd.h HINTS ${CONAN_INCLUDE_DIRS_ZSTD})
 
-find_library(ZSTD_LIBRARY NAMES zstd)
+find_library(ZSTD_LIBRARY NAMES ${CONAN_LIBS_ZSTD} HINTS ${CONAN_LIB_DIRS_ZSTD})
 
 if (ZSTD_INCLUDE_DIR AND ZSTD_LIBRARY)
     set(ZSTD_FOUND TRUE)
     message(STATUS "Found Zstd library: ${ZSTD_LIBRARY}")
 else ()
-    message(STATUS "No Zstd library found.  Using internal sources.")
+    message(STATUS "No Zstd library found.")
 endif ()
