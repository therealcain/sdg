#pragma once

#include <memory>

class Process
{
public:
    Process( const char* file );
    bool exec( const char* argv [] );

    ~Process();

private:
    struct ProcessData;
    std::unique_ptr<ProcessData> m_data;
};
