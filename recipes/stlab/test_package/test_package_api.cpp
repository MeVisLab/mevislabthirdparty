#include "test_package_api.h"

#include <stlab/concurrency/await.hpp>
#include <stlab/concurrency/default_executor.hpp>
#include <stlab/concurrency/future.hpp>

namespace TEST_PACKAGE_NAMESPACE
{
    const void *task_system_address()
    {
#if STLAB_TASK_SYSTEM(PORTABLE)
        return &stlab::detail::pts();
#elif STLAB_TASK_SYSTEM(WINDOWS)
        return &stlab::detail::single_task_system<stlab::detail::executor_priority::medium>();
#else
        return nullptr;
#endif
    }

    // Awaiting from within a pool task is what broke in gh issue 519
    int nested_await(int value)
    {
        return stlab::await(stlab::async(stlab::default_executor,
                                         [value]
                                         {
                                             return stlab::await(
                                                 stlab::async(stlab::default_executor,
                                                              [value] { return value * 2; }));
                                         }));
    }
} // namespace TEST_PACKAGE_NAMESPACE
