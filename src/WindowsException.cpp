#include <cstdarg>
#include <cstdio>
#include <Windows.h>

#include "core/WindowsException.hpp"


namespace Core
{
    WindowsException::WindowsException(HRESULT hresult, const char* format, ...)
        :
        m_Hresult(hresult)
    {
        char message[1024] = {};
        va_list args = {};
        va_start(args, format);
        vsprintf_s(message, format, args);
        va_end(args);

        sprintf_s(m_What, "%s | HRESULT: 0x%08X", message, m_Hresult);
    }

    HRESULT WindowsException::GetHresult() const
    {
        return m_Hresult;
    }

    const char* WindowsException::what() const
    {
        return m_What;
    }
}
