#include <hunspell.hxx>

#include <string>
#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
    using namespace std::string_literals;

    std::ofstream aff("test.aff");
    aff.close();

    std::ofstream dic("test.dic");
    dic.close();

    auto hunspell = new Hunspell("test.aff", "test.dic");
    hunspell->spell("MeVisLab"s);

    return 0;
}
