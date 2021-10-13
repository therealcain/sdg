#include "interactive.hpp"

#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <iostream>

#include "target.hpp"
#include "debugger.hpp"

static
void run(char* const* argv)
{
    auto child_pid = start_target(argv);

    if (child_pid != -1)
        start_debugging(child_pid);
}
// ---------------------------------------------------------------

static inline
bool is_command_run(const std::vector<std::string>& tokens)
{
    if(tokens[0] == "run")
        return tokens.size() == 1;

    return false;
}

static inline
bool is_command_exit(const std::vector<std::string>& tokens)
{
    if(tokens[0] == "exit")
        return tokens.size() == 1;

    return false;
}

// Returning true if loop breaking should happen.
static
bool do_command_and_check_exit(char* const* argv, std::vector<std::string>& tokens)
{
    if(tokens.size() <= 0)
        goto command_error;

    if (is_command_exit(tokens))
        return true;

    if (is_command_run(tokens))
    {
        run(argv);
        return true;
    }

command_error:
    std::cout << "Unrecognized command.";
    return false;
}
// ---------------------------------------------------------------

void start_interactive(char* const* argv)
{
    std::cout << "Welcome to sdg! Please type your commands:\n";
    while(true)
    {
        std::cout << "> ";
        std::flush(std::cout);

        // User input
        std::string input;
        std::getline(std::cin, input);

        // Split string to tokens
        std::istringstream iss(input);
        std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
                                        std::istream_iterator<std::string>{});

        if(do_command_and_check_exit(argv, tokens))
            break;

        std::cout << std::endl;
    }
}
