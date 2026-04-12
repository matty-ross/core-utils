#include <cstdarg>
#include <cstdio>
#include <Windows.h>

#include "core/Logger.hpp"


namespace Core
{
    Logger::Logger(const char* name)
        :
        m_Name(name)
    {
    }

    void Logger::Log(const char* level, const char* format, ...) const
    {
        SYSTEMTIME localTime = {};
        GetLocalTime(&localTime);

        char message[1024] = {};

        va_list args = {};
        va_start(args, format);
        vsprintf_s(message, format, args);
        va_end(args);

        printf_s(
            "[%04d-%02d-%02d %02d:%02d:%02d.%03d]  %-10s  %-20s  :  %s\n",
            localTime.wYear,
            localTime.wMonth,
            localTime.wDay,
            localTime.wHour,
            localTime.wMinute,
            localTime.wSecond,
            localTime.wMilliseconds,
            level,
            m_Name,
            message
        );
    }
}
