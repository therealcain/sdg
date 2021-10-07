#include <iostream>

#include "target.hpp"
#include "debugger.hpp"

#include <unistd.h>

int main(int argc, char* const* argv)
{
    if(argc <= 1)
    {
        std::cerr << "Please specify an executable\n";
        return EXIT_FAILURE;
    }

    if(auto child_pid = start_target(argv);
        child_pid != -1)
    {
        start_debugging(child_pid);
    }
    

    return EXIT_SUCCESS;
}
