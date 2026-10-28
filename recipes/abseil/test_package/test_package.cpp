#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <absl/base/internal/raw_logging.h>
#include <absl/base/throw_delegate.h>
#include <absl/container/flat_hash_map.h>
#include <absl/container/flat_hash_set.h>
#include <absl/log/log.h>
#include <absl/numeric/int128.h>
#include <absl/strings/str_cat.h>
#include <absl/strings/str_split.h>
#include <absl/time/time.h>
#include <absl/types/variant.h>

struct X
{
    int value;

    friend absl::weak_ordering operator<=>(const X &a, const X &b)
    {
        if (a.value < b.value)
            return absl::weak_ordering::less;
        if (a.value > b.value)
            return absl::weak_ordering::greater;
        return absl::weak_ordering::equivalent;
    }
};

int main()
{
    {
        absl::flat_hash_set<void *> ptrs;
        int x = 42;
        ptrs.insert(&x);
        ptrs.erase(&x);
    }

    {
        absl::flat_hash_map<int, std::string> map;
        map.emplace(1, "hello");
        map.emplace(2, "world");
    }

    absl::raw_log_internal::RawLog(absl::LogSeverity::kInfo, __FILE__, __LINE__, "RawLog: %d", 123);

    try
    {
        absl::ThrowStdOutOfRange("out of range test");
    }
    catch (const std::out_of_range &)
    {
        // Expected.
    }

    X a{3};
    X b{7};

    if ((a <=> b) < 0)
    {
        std::cout << "a < b\n";
    }

    if ((a <=> b) == 0)
    {
        std::cout << "a == b\n";
    }

    if ((a <=> b) > 0)
    {
        std::cout << "a > b\n";
    }

    absl::Time t1 = absl::Now();
    absl::Time t2 = absl::Time();
    absl::Time t3 = absl::UnixEpoch();

    absl::variant<int> v1;
    absl::bad_variant_access e1;

    const std::string year = absl::FormatTime("%Y", absl::Now(), absl::UTCTimeZone());

    std::cout << "year " << year << '\n';

    static_cast<void>(t1);
    static_cast<void>(t2);
    static_cast<void>(t3);
    static_cast<void>(v1);
    static_cast<void>(e1);

    return 0;
}
