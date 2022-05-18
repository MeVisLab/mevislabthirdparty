add_pyd(_socket)
target_link_libraries(_socket PRIVATE Ws2_32.lib)

target_sources(_socket PRIVATE
    sources/Modules/socketmodule.c
)

if(CMAKE_PROJECT_VERSION VERSION_GREATER_EQUAL 3.9)
    target_link_libraries(_socket PRIVATE iphlpapi.lib)
endif()