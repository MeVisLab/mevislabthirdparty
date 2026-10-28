#include <cstring>
#include <double-conversion/double-conversion.h>
#include <iostream>

int main()
{
    using double_conversion::DoubleToStringConverter;
    using double_conversion::StringBuilder;
    using double_conversion::StringToDoubleConverter;

    char buffer[64];
    StringBuilder builder(buffer, sizeof(buffer));
    if (!DoubleToStringConverter::EcmaScriptConverter().ToShortest(0.1 + 0.2, &builder))
    {
        std::cerr << "ToShortest failed" << std::endl;
        return 1;
    }
    const char *text = builder.Finalize();
    if (std::strcmp(text, "0.30000000000000004") != 0)
    {
        std::cerr << "unexpected ToShortest result: " << text << std::endl;
        return 1;
    }

    StringToDoubleConverter converter(StringToDoubleConverter::NO_FLAGS, 0.0, 1.0, "inf", "nan");
    int processed = 0;
    const char *input = "3.25e2";
    double value =
        converter.StringToDouble(input, static_cast<int>(std::strlen(input)), &processed);
    if (value != 325.0 || processed != 6)
    {
        std::cerr << "unexpected StringToDouble result: " << value << " (" << processed << ")"
                  << std::endl;
        return 1;
    }
    std::cout << text << " " << value << std::endl;
    return 0;
}
