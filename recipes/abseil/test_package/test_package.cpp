#include <string>
#include <utility>
#include <iostream>
#include <vector>

#include <absl/strings/str_cat.h>
#include <absl/strings/str_split.h>
#include <absl/container/flat_hash_map.h>
#include <absl/container/flat_hash_set.h>
#include <absl/numeric/int128.h>
#include <absl/time/time.h>
#include <absl/types/variant.h>

int main()
{
    absl::Time t1 = absl::Now();
    absl::Time t2 = absl::Time();
    absl::Time t3 = absl::UnixEpoch();

    absl::variant<int> v1 = absl::variant<int>();
    absl::bad_variant_access e1;

    std::string const year = absl::FormatTime("%Y", absl::Now(), absl::UTCTimeZone());
    std::cout << "year " << year << std::endl;
}
