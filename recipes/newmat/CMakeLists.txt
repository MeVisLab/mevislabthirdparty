cmake_minimum_required(VERSION 3.27)
project(newmat VERSION ${CONAN_NEWMAT_VERSION} LANGUAGES CXX)

add_library(newmat)
set_target_properties(newmat PROPERTIES VERSION "${PROJECT_VERSION}" SOVERSION "${PROJECT_VERSION_MAJOR}")

target_sources(newmat PRIVATE
    src/bandmat.cpp
    src/cholesky.cpp
    src/controlw.h
    src/evalue.cpp
    src/fft.cpp
    src/hholder.cpp
    src/include.h
    src/jacobi.cpp
    src/myexcept.cpp
    src/myexcept.h
    src/newfft.cpp
    src/newmat.h
    src/newmat1.cpp
    src/newmat2.cpp
    src/newmat3.cpp
    src/newmat4.cpp
    src/newmat5.cpp
    src/newmat6.cpp
    src/newmat7.cpp
    src/newmat8.cpp
    src/newmat9.cpp
    src/newmatap.h
    src/newmatex.cpp
    src/newmatio.h
    src/newmatnl.cpp
    src/newmatnl.h
    src/newmatrc.h
    src/newmatrm.cpp
    src/newmatrm.h
    src/nm_misc.cpp
    src/precisio.h
    src/solution.cpp
    src/solution.h
    src/sort.cpp
    src/submat.cpp
    src/svd.cpp
)

target_include_directories(newmat PRIVATE src)

install(TARGETS newmat DESTINATION lib)
install(FILES
    src/controlw.h
    src/include.h
    src/myexcept.h
    src/newmat.h
    src/newmatap.h
    src/newmatio.h
    src/newmatnl.h
    src/newmatrc.h
    src/newmatrm.h
    src/precisio.h
    src/solution.h
  DESTINATION
    include/newmat
)
