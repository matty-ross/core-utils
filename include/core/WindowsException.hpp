#pragma once


#include <exception>
#include <Windows.h>


namespace Core
{
    class WindowsException : public std::exception
    {
    public:
        WindowsException(HRESULT hresult, const char* format, ...);

    public:
        const char* what() const override;

    private:
        char m_What[1024] = {};
    };
}
