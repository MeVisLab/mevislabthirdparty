find_package(Qt5 COMPONENTS Core Gui Sql REQUIRED)

add_library(QtSql "")
set_target_properties(QtSql PROPERTIES OUTPUT_NAME QtSql)

if(WIN32)
    set_target_properties(QtSql PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(QtSql PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(QtSql PRIVATE QtSql.cpp)
target_sources(QtSql PRIVATE
  ../generated_cpp/com_trolltech_qt_sql/com_trolltech_qt_sql0.h
  ../generated_cpp/com_trolltech_qt_sql/com_trolltech_qt_sql0.cpp
  ../generated_cpp/com_trolltech_qt_sql/com_trolltech_qt_sql_init.cpp
)

target_link_libraries(QtSql
  PRIVATE
    Qt5::Core 
    Qt5::Gui
    Qt5::Sql
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS QtSql
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
