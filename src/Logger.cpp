#include "Core/Logger.hpp"


namespace Core
{
    Logger::Logger(const char* name)
        :
        m_Name(name)
    {
    }
    
    void Logger::Log(const char* level, const char* format, ...) const
    {
        // TODO: Log into the console.
    }
}
