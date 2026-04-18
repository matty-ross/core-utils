#include <cstdarg>
#include <cstdio>

#include "core/WindowsException.hpp"


namespace Core
{
    WindowsException::WindowsException(HRESULT hresult, const char* format, ...)
    {
        char message[1024] = {};

        va_list args = {};
        va_start(args, format);
        vsprintf_s(message, format, args);
        va_end(args);

        sprintf_s(m_What, "%s | HRESULT: 0x%08X", message, hresult);
    }

    const char* WindowsException::what() const
    {
        return m_What;
    }
}
