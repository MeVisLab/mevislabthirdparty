add_pyd(_ssl)
#target_compile_definitions(_ssl PRIVATE OPENSSL_NO_SSL2 OPENSSL_NO_SSL3)
target_link_libraries(_ssl PRIVATE ws2_32.lib Crypt32.lib)
target_link_libraries(_ssl PRIVATE OpenSSL::SSL)

target_sources(_ssl PRIVATE
    sources/Modules/_ssl.c
)
