#include <iostream>
#include <re2/re2.h>
#include <string>

int main()
{
    if (!RE2::FullMatch("hello", "h.*o"))
    {
        std::cerr << "expected 'hello' to match 'h.*o'" << std::endl;
        return 1;
    }
    if (RE2::FullMatch("hello", "e"))
    {
        std::cerr << "expected 'hello' not to match 'e'" << std::endl;
        return 1;
    }

    int number = 0;
    std::string word;
    if (!RE2::PartialMatch("ruby:1234", "(\\w+):(\\d+)", &word, &number) || word != "ruby" ||
        number != 1234)
    {
        std::cerr << "capture groups failed: " << word << " " << number << std::endl;
        return 1;
    }

    std::string text = "aaa bbb";
    RE2::GlobalReplace(&text, "b", "c");
    if (text != "aaa ccc")
    {
        std::cerr << "GlobalReplace failed: " << text << std::endl;
        return 1;
    }
    std::cout << "re2 works" << std::endl;
    return 0;
}
