#include <cstdio>

#include "core/WindowsException.hpp"


namespace Core
{
    WindowsException::WindowsException(const char* message, HRESULT hresult)
    {
        sprintf_s(m_What, "%s | HRESULT: 0x%08X", message, hresult);
    }

    const char* WindowsException::what() const
    {
        return m_What;
    }
}
