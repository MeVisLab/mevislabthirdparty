#include <iostream>
#include <nlohmann/json.hpp>

int main() {
    const nlohmann::json data = {
        {"pi", 3.141}
    };

    std::cout << data.dump(4) << std::endl;
    return 0;
}
