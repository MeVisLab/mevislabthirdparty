#include <cstdio>
#include <stdexcept>
#include <utility>
#include <vector>

#include <stlab/concurrency/await.hpp>
#include <stlab/concurrency/default_executor.hpp>
#include <stlab/concurrency/future.hpp>
#include <stlab/concurrency/serial_queue.hpp>
#include <stlab/concurrency/task.hpp>
#include <stlab/pre_exit.hpp>
#include <stlab/version.hpp>

#include "test_package_api.h"

struct forwarding_executor
{
    using result_type = void;
    void operator()(stlab::task<void() noexcept> f) const
    {
        stlab::default_executor(std::move(f));
    }
};

int main()
{
    std::printf("%d\n", stlab::await(stlab::async(stlab::default_executor, [] { return 42; })));

    stlab::serial_queue_t queue{forwarding_executor{}};

    std::vector<stlab::future<int>> parts;
    for (int i = 0; i != 4; ++i)
    {
        parts.push_back(stlab::async(queue.executor(), [i] { return i; }));
    }

    const auto sum = stlab::await(stlab::when_all(
        forwarding_executor{},
        [](const std::vector<int> &values)
        {
            int total = 0;
            for (const auto value : values)
            {
                total += value;
            }
            return total;
        },
        std::make_pair(parts.begin(), parts.end())));

    if (sum != 6)
    {
        std::puts("unexpected result");
        return 1;
    }

    // gh issue 519: stlab used from several shared libraries must not instantiate
    // more than one task system
    const auto *task_system_a = test_package_a::task_system_address();
    const auto *task_system_b = test_package_b::task_system_address();
    std::printf("task system: test_package_a=%p test_package_b=%p\n", task_system_a, task_system_b);

    if (task_system_a == nullptr && task_system_b == nullptr)
    {
        std::puts("task system identity not observable for this configuration");
        return 1;
    }
    else if (task_system_a != task_system_b)
    {
        std::puts("each shared library got its own task system. see stlab issue 519");
        return 1;
    }

    if (test_package_a::nested_await(21) != 42 || test_package_b::nested_await(50) != 100)
    {
        std::puts("nested await returned an unexpected result");
        return 1;
    }

    std::puts(STLAB_LIB_VERSION);

    stlab::pre_exit();

    return 0;
}
