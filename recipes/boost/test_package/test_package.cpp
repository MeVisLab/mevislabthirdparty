#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/date_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/json.hpp>
#include <boost/locale.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/regex.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/timer/timer.hpp>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>


#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_stream.hpp>

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


bool json_round_trip()
{
    boost::json::value parsed = boost::json::parse(R"({"name":"boost","values":[1,2,3]})");
    if (parsed.at("name").as_string() != "boost" || parsed.at("values").as_array().size() != 3)
    {
        return false;
    }
    return boost::json::parse(boost::json::serialize(parsed)) == parsed;
}


bool serialization_round_trip()
{
    std::stringstream stream;
    const std::vector<int> numbers{1, 2, 3};
    const std::string text = "serialized";
    {
        boost::archive::text_oarchive oa(stream);
        oa << numbers << text;
    }
    std::vector<int> restoredNumbers;
    std::string restoredText;
    boost::archive::text_iarchive ia(stream);
    ia >> restoredNumbers >> restoredText;
    return restoredNumbers == numbers && restoredText == text;
}


bool program_options_parse()
{
    namespace po = boost::program_options;
    po::options_description options;
    options.add_options()("count", po::value<int>())("name", po::value<std::string>());
    const char *fakeArgv[] = {"test_package", "--count", "7", "--name", "boost"};
    po::variables_map vm;
    po::store(po::parse_command_line(5, fakeArgv, options), vm);
    po::notify(vm);
    return vm["count"].as<int>() == 7 && vm["name"].as<std::string>() == "boost";
}


bool log_to_ostream()
{
    namespace sinks = boost::log::sinks;
    auto output = boost::make_shared<std::ostringstream>();
    auto sink = boost::make_shared<sinks::synchronous_sink<sinks::text_ostream_backend>>();
    sink->locked_backend()->add_stream(
        boost::shared_ptr<std::ostream>(output.get(), boost::null_deleter()));
    boost::log::core::get()->add_sink(sink);
    BOOST_LOG_TRIVIAL(info) << "boost log message";
    sink->flush();
    boost::log::core::get()->remove_sink(sink);
    return output->str().find("boost log message") != std::string::npos;
}


bool locale_to_upper()
{
    boost::locale::generator generator;
    std::locale locale = generator("en_US.UTF-8");
    return boost::locale::to_upper("boost", locale) == "BOOST";
}


bool random_sequence()
{
    boost::random::mt19937 generator;
    for (int i = 0; i < 9999; ++i)
    {
        generator();
    }
    return generator() == 4123659995u;
}


bool chrono_and_timer()
{
    boost::timer::cpu_timer timer;
    const auto start = boost::chrono::steady_clock::now();
    const auto elapsed = boost::chrono::steady_clock::now() - start;
    return elapsed.count() >= 0 && timer.elapsed().wall >= 0;
}


int main(int argc, char *argv[])
{
    zlib_iostream();

    struct
    {
        const char *name;
        bool (*check)();
    } checks[] = {{"json", json_round_trip},
                  {"serialization", serialization_round_trip},
                  {"program_options", program_options_parse},
                  {"log", log_to_ostream},
                  {"locale", locale_to_upper},
                  {"random", random_sequence},
                  {"chrono/timer", chrono_and_timer}};
    for (const auto &check : checks)
    {
        if (!check.check())
        {
            std::cerr << check.name << " failed!" << std::endl;
            return 1;
        }
    }

    // boost thread
    boost::thread workerThread([]()
                               { boost::this_thread::sleep(boost::posix_time::microseconds(3)); });

    // boost regex
    static const boost::regex date_regex(
        "(199[0-9]|200[0-9])-([1-9]|0[1-9]|1[012])-([1-9]|[0-2][1-9]|3[01])");

    {
        const char *input_cstr = "2007-03-14";
        boost::cmatch char_matches;

        if (!boost::regex_match(input_cstr, char_matches, date_regex))
        {
            std::cerr << "regex 2007-03-14 failed!" << std::endl;
            return 1;
        }
    }

    {
        std::string input_stlstr = "2007-03-34";
        boost::smatch str_matches;

        if (boost::regex_match(input_stlstr, str_matches, date_regex))
        {
            std::cerr << "regex 2007-03-34 not failed!" << std::endl;
            return 1;
        }
    }

    if (!boost::regex_match("2019", boost::regex("(199[0-9]|20[0-2][0-9])")))
    {
        std::cerr << "regex 2019 failed!" << std::endl;
        return 1;
    }

    // boost filesystem
    if (!boost::filesystem::is_regular_file(argv[0]))
    {
        std::cerr << "is_regular_file failed!" << std::endl;
        return 1;
    }

    // boost asio
    boost::asio::io_context ctx;

    workerThread.join();

    return 0;
}
