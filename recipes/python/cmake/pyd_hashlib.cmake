find_package(OpenSSL REQUIRED)

add_pyd(_hashlib)
target_sources(_hashlib PRIVATE sources/Modules/_hashopenssl.c)
# DEFINES += OPENSSL_NO_SSL2 OPENSSL_NO_SSL3
target_link_libraries(_hashlib PRIVATE OpenSSL::SSL OpenSSL::Crypto)
