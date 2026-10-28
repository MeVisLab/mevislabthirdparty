#ifndef TEST_PACKAGE_API_H
#define TEST_PACKAGE_API_H

#if defined(_WIN32)
#define TEST_PACKAGE_TEST_API
#else
#define TEST_PACKAGE_TEST_API __attribute__((visibility("default")))
#endif

namespace test_package_a
{
    TEST_PACKAGE_TEST_API const void *task_system_address();
    TEST_PACKAGE_TEST_API int nested_await(int value);
} // namespace test_package_a

namespace test_package_b
{
    TEST_PACKAGE_TEST_API const void *task_system_address();
    TEST_PACKAGE_TEST_API int nested_await(int value);
} // namespace test_package_b

#endif
