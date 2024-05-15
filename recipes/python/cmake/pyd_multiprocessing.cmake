add_pyd(_multiprocessing)
target_include_directories(_multiprocessing PRIVATE ${SRC}/Modules/_multiprocessing)
target_link_libraries(_multiprocessing PRIVATE Ole32.lib Oleaut32.lib ws2_32.lib)

target_sources(_multiprocessing PRIVATE
    ${SRC}/Modules/_multiprocessing/multiprocessing.c
    ${SRC}/Modules/_multiprocessing/semaphore.c
)
