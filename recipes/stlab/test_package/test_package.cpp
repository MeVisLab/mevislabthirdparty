#include <stdexcept>
#include <stlab/version.hpp>
#include <stlab/concurrency/await.hpp>
#include <stlab/concurrency/default_executor.hpp>
#include <stlab/concurrency/future.hpp>
#include <cstdio>

int main()
{
    printf("%d", stlab::await(stlab::async(stlab::default_executor, [] { return 42; })));

    std::puts(STLAB_LIB_VERSION);

    stlab::pre_exit();

    return 0;
}
