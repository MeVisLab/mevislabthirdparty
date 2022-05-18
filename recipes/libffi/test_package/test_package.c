#if defined(_MSC_VER)
#pragma runtime_checks("s", off)
#endif

#include <ffi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

unsigned print_uint(unsigned arg)
{
    printf("print_int(%u)\n", arg);
    return 3 * arg;
}

typedef struct {
    FILE *stream;
} puts_binding_userdata;

void puts_binding(ffi_cif *cif, void *ret, void** args, void *userdata)
{
    fputs(*(char **)args[0], ((puts_binding_userdata *)userdata)->stream);
    *((unsigned*)ret) = 1337;
}

int main()
{
    ffi_type *argtypes[1] = {&ffi_type_uint32};
    ffi_cif cif;
    ffi_status status = FFI_BAD_ABI;
    status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1, &ffi_type_uint32, argtypes);
    if (status != FFI_OK)
    {
        puts("1 ffi_prep_cif FAILED.\n\n");
        return EXIT_FAILURE;
    }

    unsigned rvalue = 0;
    unsigned arg1 = 13;
    const unsigned expected_ret = 3 * arg1;
    void *args[] = {(void*)(&arg1)};
    ffi_call(&cif, FFI_FN(&print_uint), (void *) &rvalue, args);
    printf("ffi_call returns %d (should be %d)\n", rvalue, expected_ret);
    if (rvalue != expected_ret) {
        printf("ffi_call FAILED. Expected %d, but got %d.\n", expected_ret, rvalue);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#if defined(_MSC_VER)
#pragma runtime_checks("s", restore)
#endif
