#include <iostream>
#include <boost/asio.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <boost/filesystem.hpp>


int main(int argc, char *argv[])
{
    // boost thread
    boost::thread workerThread([]() { boost::this_thread::sleep(boost::posix_time::microseconds(3)); });

    // boost regex
    static const boost::regex date_regex("(199[0-9]|200[0-9])-([1-9]|0[1-9]|1[012])-([1-9]|[0-2][1-9]|3[01])");

    {
        const char *input_cstr = "2007-03-14";
        boost::cmatch char_matches;

        if(!boost::regex_match(input_cstr, char_matches, date_regex)) {
            std::cerr << "regex 2007-03-14 failed!" << std::endl;
            return 1;
        }
    }

    {
        std::string input_stlstr = "2007-03-34";
        boost::smatch str_matches;

        if (boost::regex_match(input_stlstr, str_matches, date_regex)) {
            std::cerr << "regex 2007-03-34 not failed!" << std::endl;
            return 1;
        }
    }

    if(!boost::regex_match("2019", boost::regex("(199[0-9]|20[0-2][0-9])"))) {
        std::cerr << "regex 2019 failed!" << std::endl;
        return 1;
    }

    // boost filesystem
    if(!boost::filesystem::is_regular_file(argv[0])) {
        std::cerr << "is_regular_file failed!" << std::endl;
        return 1;
    }

    // boost asio
    boost::asio::io_context ctx;

    workerThread.join();

    return 0;
}
