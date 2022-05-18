cmake_minimum_required(VERSION 3.14)
project(conan-wrapper)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(_UNUSED
    ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY}
    ${CMAKE_INSTALL_BINDIR}
    ${CMAKE_INSTALL_DATAROOTDIR}
    ${CMAKE_INSTALL_INCLUDEDIR}
    ${CMAKE_INSTALL_LIBDIR}
    ${CMAKE_INSTALL_LIBEXECDIR}
    ${CMAKE_INSTALL_OLDINCLUDEDIR}
    ${CMAKE_INSTALL_SBINDIR}
)

add_library(newmat)
target_sources(newmat PRIVATE
    sources/bandmat.cpp
    sources/cholesky.cpp
    sources/controlw.h
    sources/evalue.cpp
    sources/fft.cpp
    sources/hholder.cpp
    sources/include.h
    sources/jacobi.cpp
    sources/myexcept.cpp
    sources/myexcept.h
    sources/newfft.cpp
    sources/newmat.h
    sources/newmat1.cpp
    sources/newmat2.cpp
    sources/newmat3.cpp
    sources/newmat4.cpp
    sources/newmat5.cpp
    sources/newmat6.cpp
    sources/newmat7.cpp
    sources/newmat8.cpp
    sources/newmat9.cpp
    sources/newmatap.h
    sources/newmatex.cpp
    sources/newmatio.h
    sources/newmatnl.cpp
    sources/newmatnl.h
    sources/newmatrc.h
    sources/newmatrm.cpp
    sources/newmatrm.h
    sources/nm_misc.cpp
    sources/precisio.h
    sources/solution.cpp
    sources/solution.h
    sources/sort.cpp
    sources/submat.cpp
    sources/svd.cpp
)

target_link_libraries(newmat ${CONAN_LIBS})
target_include_directories(newmat PRIVATE sources)

install(TARGETS newmat DESTINATION lib)
install(FILES
    sources/controlw.h
    sources/include.h
    sources/myexcept.h
    sources/newmat.h
    sources/newmatap.h
    sources/newmatio.h
    sources/newmatnl.h
    sources/newmatrc.h
    sources/newmatrm.h
    sources/precisio.h
    sources/solution.h
  DESTINATION
    include/newmat
)
