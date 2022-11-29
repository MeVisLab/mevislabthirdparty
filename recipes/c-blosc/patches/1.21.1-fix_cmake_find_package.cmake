diff --git i/cmake/FindLZ4.cmake w/cmake/FindLZ4.cmake
index e581a80..acb5919 100644
--- i/cmake/FindLZ4.cmake
+++ w/cmake/FindLZ4.cmake
@@ -1,6 +1,6 @@
-find_path(LZ4_INCLUDE_DIR lz4.h)
+find_path(LZ4_INCLUDE_DIR NAMES lz4.h HINTS ${CONAN_INCLUDE_DIRS_LZ4})
 
-find_library(LZ4_LIBRARY NAMES lz4)
+find_library(LZ4_LIBRARY NAMES ${CONAN_LIBS_LZ4} HINTS ${CONAN_LIB_DIRS_LZ4})
 
 if (LZ4_INCLUDE_DIR AND LZ4_LIBRARY)
     set(LZ4_FOUND TRUE)
diff --git i/cmake/FindSnappy.cmake w/cmake/FindSnappy.cmake
index 688d4d5..720e8e1 100644
--- i/cmake/FindSnappy.cmake
+++ w/cmake/FindSnappy.cmake
@@ -1,6 +1,6 @@
-find_path(SNAPPY_INCLUDE_DIR snappy-c.h)
+find_path(SNAPPY_INCLUDE_DIR NAMES snappy-c.h HINTS ${CONAN_INCLUDE_DIRS_SNAPPY})
 
-find_library(SNAPPY_LIBRARY NAMES snappy)
+find_library(SNAPPY_LIBRARY NAMES ${CONAN_LIBS_SNAPPY} HINTS ${CONAN_LIB_DIRS_SNAPPY})
 
 if (SNAPPY_INCLUDE_DIR AND SNAPPY_LIBRARY)
     set(SNAPPY_FOUND TRUE)
diff --git i/cmake/FindZstd.cmake w/cmake/FindZstd.cmake
index 7db4bb9..4cdc1b2 100644
--- i/cmake/FindZstd.cmake
+++ w/cmake/FindZstd.cmake
@@ -1,6 +1,6 @@
-find_path(ZSTD_INCLUDE_DIR zstd.h)
+find_path(ZSTD_INCLUDE_DIR NAMES zstd.h HINTS ${CONAN_INCLUDE_DIRS_ZSTD})
 
-find_library(ZSTD_LIBRARY NAMES zstd)
+find_library(ZSTD_LIBRARY NAMES ${CONAN_LIBS_ZSTD} HINTS ${CONAN_LIB_DIRS_ZSTD})
 
 if (ZSTD_INCLUDE_DIR AND ZSTD_LIBRARY)
     set(ZSTD_FOUND TRUE)
