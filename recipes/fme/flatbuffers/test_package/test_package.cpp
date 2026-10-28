#include <cstdlib>
#include <iostream>

#include <flatbuffers/flatbuffers.h>

#include "monster_generated.h"

int main(int /*argc*/, const char * /*argv*/[])
{
    flatbuffers::FlatBufferBuilder builder;

    auto name = builder.CreateString("FlatBuffers Example");
    auto message = CreateMonster(builder, nullptr, 150, 80, name, 0, MyGame::Sample::Color_Blue, 0,
                                 MyGame::Sample::Equipment_Weapon, 0, 0);

    builder.Finish(message);

    uint8_t *buf = builder.GetBufferPointer();
    size_t size = builder.GetSize();

    auto received_message = flatbuffers::GetRoot<MyGame::Sample::Monster>(buf);

    if (received_message->mana() != 150)
    {
        std::cerr << "Error: mana != 150" << std::endl;
        return EXIT_FAILURE;
    }

    if (received_message->hp() != 80)
    {
        std::cerr << "Error: hp != 80" << std::endl;
        return EXIT_FAILURE;
    }

    if (received_message->color() != MyGame::Sample::Color_Blue)
    {
        std::cerr << "Error: color != Blue" << std::endl;
        return EXIT_FAILURE;
    }

    if (received_message->name()->str() != "FlatBuffers Example")
    {
        std::cerr << "Error: name != FlatBuffers Example" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
