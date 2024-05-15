find_package(OpenSSL REQUIRED)

add_pyd(_hashlib)
target_sources(_hashlib PRIVATE ${SRC}/Modules/_hashopenssl.c)
target_link_libraries(_hashlib PRIVATE OpenSSL::SSL OpenSSL::Crypto)
