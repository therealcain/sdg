#include "target.hpp"

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

#include <iostream>

static
bool start_trace()
{
    if(ptrace(PTRACE_TRACEME, 0, 0, 0) < 0)
    {
        std::cerr << "Tracing the program has failed.\n";
        return false;
    }

    return true;
}

static
bool start_program(char* const* argv)
{
    if(execvp(argv[1], &argv[2]) == -1)
    {
        std::cerr << "Failed to start program.\n";
        return false;
    }

    return true;
}

int start_target(char *const *argv)
{
    int child_pid = fork();

    if(child_pid == 0)
    {
        if(!start_trace())
            return -1;

        start_program(argv);
    }

    else if(child_pid > 0)
        return child_pid;

    else
    {
        std::cerr << "Failed to fork.\n";
        return -1;
    }

    return -1;
}
