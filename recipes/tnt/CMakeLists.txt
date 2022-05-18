cmake_minimum_required(VERSION 3.14)
project(conan-wrapper)

set(_unused
    ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY}
    ${CMAKE_INSTALL_BINDIR}
    ${CMAKE_INSTALL_DATAROOTDIR}
    ${CMAKE_INSTALL_INCLUDEDIR}
    ${CMAKE_INSTALL_LIBDIR}
    ${CMAKE_INSTALL_LIBEXECDIR}
    ${CMAKE_INSTALL_OLDINCLUDEDIR}
    ${CMAKE_INSTALL_SBINDIR}
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

install(FILES
    sources/tnt.h
    sources/tnt_array1d.h
    sources/tnt_array1d_utils.h
    sources/tnt_array2d.h
    sources/tnt_array2d_utils.h
    sources/tnt_array3d.h
    sources/tnt_array3d_utils.h
    sources/tnt_cmat.h
    sources/tnt_fortran_array1d.h
    sources/tnt_fortran_array1d_utils.h
    sources/tnt_fortran_array2d.h
    sources/tnt_fortran_array2d_utils.h
    sources/tnt_fortran_array3d.h
    sources/tnt_fortran_array3d_utils.h
    sources/tnt_i_refvec.h
    sources/tnt_math_utils.h
    sources/tnt_sparse_matrix_csr.h
    sources/tnt_stopwatch.h
    sources/tnt_subscript.h
    sources/tnt_vec.h
    sources/tnt_version.h
  DESTINATION
    include
)
