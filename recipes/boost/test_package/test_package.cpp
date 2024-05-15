#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <boost/asio.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <boost/filesystem.hpp>


#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>

namespace io = boost::iostreams;


void zlib_iostream()
{
  // taken from https://theboostcpplibraries.com/boost.iostreams-filters, Example 34.8,
  // then modified
  std::vector<char> v;
  io::back_insert_device<std::vector<char>> snk{v};
  io::filtering_ostream os;
  os.push(io::zlib_compressor{});
  os.push(snk);
  os << "This is Boost (compressed/decompressed with zlib)" << std::flush;
  os.pop();

  io::array_source src{v.data(), v.size()};
  io::filtering_istream is;
  is.push(io::zlib_decompressor{});
  is.push(src);
  std::string s(std::istreambuf_iterator<char>(is), {});
  std::cout << s << '\n';
}


int main(int argc, char *argv[])
{
    zlib_iostream();

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
