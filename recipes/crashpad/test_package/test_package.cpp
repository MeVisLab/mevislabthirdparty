#include <base/files/file_path.h>
#include <client/crashpad_client.h>

#include <cstdlib>
#include <iostream>

int main()
{
    const base::FilePath handler(FILE_PATH_LITERAL("crashpad_handler.exe"));
    if (handler.FinalExtension() != FILE_PATH_LITERAL(".exe") ||
        handler.RemoveFinalExtension().BaseName().value() != FILE_PATH_LITERAL("crashpad_handler"))
    {
        std::cerr << "unexpected base::FilePath behavior" << std::endl;
        return EXIT_FAILURE;
    }

    crashpad::CrashpadClient client;
    if (!client.GetHandlerIPCPipe().empty())
    {
        std::cerr << "unexpected handler IPC pipe without a started handler" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "crashpad client created" << std::endl;
    return EXIT_SUCCESS;
}
