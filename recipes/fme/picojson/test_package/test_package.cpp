#include <cstdlib>
#include <iostream>
#include <string>

#include <picojson.h>

void parse()
{
    picojson::value v;
    std::string json = "{\"string\": \"it works\", \"number\": 3.14, \"integer\":5}";

    std::string err = picojson::parse(v, json);
    if(!err.empty()) {
        std::cerr << err << std::endl;
        std::exit(1);
    }

    std::cout << "  string...: " << v.get("string").get<std::string>() << std::endl;
    std::cout << "  number...: " << v.get("number").get<double>() << std::endl;
    std::cout << "  integer..: " << v.get("integer").get<double>() << std::endl;
}

void serialize()
{
    picojson::object v;
    picojson::object inner;
    std::string val = "tt";

    v["a"] = picojson::value(val);
    v["b"] = picojson::value(1.66);
    inner["test"] =  picojson::value(true);
    inner["integer"] =  picojson::value(1.0);
    v["inner"] =  picojson::value(inner);

    auto str = picojson::value(v).serialize();
    std::cout << "  " << str << std::endl;
}

void advanced()
{
    picojson::value v;
    std::string json =
        "{\"object\": {"
        "\"id\": \"f\","
        "\"subobject\": {"
        "  \"subsubarray\": ["
        "    {\"value\": \"0\"},"
        "    {\"value\": \"1\"},"
        "    {\"value\": \"2\"}"
        "   ]"
        "  }"
        "}"
        "}";

    std::string err = picojson::parse(v, json);
    if(!err.empty()) {
        std::cout << err << std::endl;
        std::exit(1);
    }

    std::cout << "  id...: " << v.get("object").get("id").get<std::string>() << std::endl;
    auto list = v.get("object").get("subobject").get("subsubarray").get<picojson::array>();
    for (auto it : list) {
        std::cout << "  value: " << it.get("value").get<std::string>() << std::endl;
    }
}

int main() {
    std::cout << ">>> parsing" << std::endl;
    parse();
    std::cout << ">>> serializing" << std::endl;
    serialize();
    std::cout << ">>> advanced parsing" << std::endl;
    advanced();

    std::cout << ">>> ok" << std::endl;
}
