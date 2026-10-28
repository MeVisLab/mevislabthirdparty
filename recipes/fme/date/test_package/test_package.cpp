#include <chrono>
#include <date/date.h>
#include <iostream>

int main()
{
    namespace ch = std::chrono;
    using namespace date;

    auto startDate = date::year{2020} / date::January / 1;
    std::cout << "Start date: " << startDate << '\n';

    auto endDate = date::year{2024} / date::January / 1;
    std::cout << "End date: " << endDate << '\n';

    auto start = date::sys_days(startDate);
    auto end = date::sys_days(endDate);
    date::days difference = end - start;

    std::cout << "Difference in days: " << difference.count() << " days\n";

    // Get the current date and time
    auto now = ch::system_clock::now();
    auto currentDate = floor<date::days>(now);
    date::year_month_day today = date::year_month_day{currentDate};

    // Output the current date
    std::cout << "Current date (UTC): " << today << '\n';

    return 0;
}
