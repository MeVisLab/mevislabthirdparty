#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

#if defined(_MSC_VER) && !defined(GTEST_LINKED_AS_SHARED_LIBRARY)
  #define GTEST_LINKED_AS_SHARED_LIBRARY_NOTDEFINED
#endif

struct Salutation
{
    static std::string greet(const std::string& name);
};

std::string Salutation::greet(const std::string& name)
{
    std::ostringstream s;
    s << "Hello " << name << "!";
    return s.str();
}


TEST(SalutationTest, Static) {
    using namespace std::string_literals;
    EXPECT_EQ("Hello World!"s, Salutation::greet("World"s));
}

TEST(LinkedAsSharedLibraryDefineTest, Static) {
  #if defined(GTEST_LINKED_AS_SHARED_LIBRARY_NOTDEFINED)
    FAILED()
  #endif
}
