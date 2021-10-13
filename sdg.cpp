#include <iostream>

#include "interactive.hpp"

#include <unistd.h>

int main(int argc, char* const* argv)
{
    if(argc <= 1)
    {
        std::cerr << "Please specify an executable\n";
        return EXIT_FAILURE;
    }

    start_interactive(argv);

    return EXIT_SUCCESS;
}
