#include <hunspell.hxx>

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    using namespace std::string_literals;

    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " file.aff file.dic\n";
        return 1;
    }

    auto aff_file = argv[1];
    auto dic_file = argv[2];

    Hunspell hunspell(aff_file, dic_file);
    bool ok = hunspell.spell("MeVisLab"s);
    std::cout << (ok ? "correct\n" : "misspelled\n");

    return ok ? 0 : 1;
}
