#include "debugger.hpp"

#include <sys/ptrace.h>
#include <sys/wait.h>

#include <iostream>

void start_debugging(int pid)
{
    int wait_status;
    wait(&wait_status);

    while (WIFSTOPPED(wait_status)) 
    {
        if (ptrace(PTRACE_SINGLESTEP, pid, 0, 0) < 0) {
            std::cerr << "ptrace failed.\n";
            return;
        }

        wait(&wait_status);
    }
}
