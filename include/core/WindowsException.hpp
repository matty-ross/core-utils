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
        HRESULT GetHresult() const;
        const char* what() const override;

    private:
        HRESULT m_Hresult = S_OK;
        char m_What[1024] = {};
    };
}
