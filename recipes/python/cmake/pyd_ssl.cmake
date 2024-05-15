add_pyd(_ssl)

find_package(OpenSSL REQUIRED)

target_link_libraries(_ssl PRIVATE ws2_32.lib Crypt32.lib)
target_link_libraries(_ssl PRIVATE OpenSSL::SSL)

target_sources(_ssl PRIVATE
    ${SRC}/Modules/_ssl.c
)
