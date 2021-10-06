#include <iostream>

#include "process.hpp"

int main( int argc, const char* argv [] )
{
    if( argc <= 1 )
    {
        std::cerr << "Please specify an executable\n";
        return EXIT_FAILURE;
    }

    Process process( argv[ 1 ] );

    if( process.exec( &argv[ 1 ] ) )
    {
        std::cout << "Executed!\n";
    }
    else
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
