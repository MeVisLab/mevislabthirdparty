#include <stlab/version.hpp>
#include <stlab/concurrency/default_executor.hpp>
#include <stlab/concurrency/future.hpp>

#include <thread>
#include <chrono>
#include <cstdio>

int main()
{
    auto f = stlab::async(stlab::default_executor, [] { return 42; });
    while (!f.get_try()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::puts(STLAB_LIB_VERSION);
    return 0;
}
