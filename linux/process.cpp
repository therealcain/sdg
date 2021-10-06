#include "../process.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>

#include <string>
#include <iostream>

// ------------------------------------------------------------------

struct Process::ProcessData
{
    pid_t id;
    std::string file;
};
// ------------------------------------------------------------------

Process::Process( const char* file )
    : m_data( std::make_unique<ProcessData>() )
{
    m_data->file = file;
}

// For Pimpl.
Process::~Process() = default;
// ------------------------------------------------------------------

bool Process::exec( const char* argv [] )
{
    pid_t pid = fork();

    if( pid == 0 )
    {
        if( ptrace( PTRACE_TRACEME, 0, 0, 0 ) < 0 )
        {
            std::cerr << "Failed to ptrace.\n";
            return false;
        }

        // execvp is an old C interface, so we must cast it.
        execvp( m_data->file.c_str(), const_cast<char* const*>(argv) );
    }

    else if( pid > 0 )
    {
        m_data->id = pid;
        return true;
    }

    else
    {
        std::cerr << "Failed to fork.\n";
        return false;
    }

    return true;
}
