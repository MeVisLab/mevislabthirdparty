#include <iostream>
#include <muParser.h>

int main(int argc, char* argv[])
{
    double fVal = 1;
    mu::Parser p;
    p.DefineVar("a", &fVal);
    p.DefineFun("MySqr", [](double v) { return v * v; });
    p.SetExpr("MySqr(a)*_pi+min(10,a)");

    for (std::size_t a=0; a<100; ++a) {
        fVal = a;
        std::cout << p.Eval() << std::endl;
    }

    return 0;
}
