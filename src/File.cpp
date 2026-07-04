#include <cstddef>
#include <string>
#include <vector>
#include <Windows.h>

#include "core/WindowsException.hpp"
#include "core/Path.hpp"
#include "core/Logger.hpp"
#include "core/File.hpp"


namespace Core
{
    File::File(const Path& path, Mode mode, const Logger& logger)
        :
        m_Path(path),
        m_Logger(logger)
    {
        DWORD desiredAccess = 0;
        DWORD creationDisposition = 0;

        switch (mode)
        {
        case Mode::Read:
            desiredAccess = GENERIC_READ;
            creationDisposition = OPEN_EXISTING;
            break;

        case Mode::Write:
            desiredAccess = GENERIC_WRITE;
            creationDisposition = CREATE_ALWAYS;
            break;
        }

        m_FileHandle = CreateFileA(m_Path.GetPath(), desiredAccess, FILE_SHARE_READ, nullptr, creationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);
        if (m_FileHandle == INVALID_HANDLE_VALUE)
        {
            throw WindowsException(
                HRESULT_FROM_WIN32(GetLastError()),
                "Failed to open file. path: '%s'", m_Path.GetPath()
            );
        }

        m_Logger.Info("Opened file. path: '%s'", m_Path.GetPath());
    }

    File::~File()
    {
        if (m_FileHandle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(m_FileHandle);

            m_Logger.Info("Closed file. path: '%s'", m_Path.GetPath());
        }
    }

    size_t File::GetSize() const
    {
        return GetFileSize(m_FileHandle, nullptr);
    }

    std::string File::ReadAsText() const
    {
        std::string content(GetSize(), '\0');
        Read(content.data(), content.size());

        return content;
    }

    std::vector<std::byte> File::ReadAsBinary() const
    {
        std::vector<std::byte> content(GetSize(), std::byte{ 0 });
        Read(content.data(), content.size());

        return content;
    }

    void File::WriteAsText(const std::string& content) const
    {
        Write(content.data(), content.size());
    }

    void File::WriteAsBinary(const std::vector<std::byte>& content) const
    {
        Write(content.data(), content.size());
    }

    void File::Read(void* data, size_t size) const
    {
        DWORD bytesToRead = static_cast<DWORD>(size);
        DWORD bytesRead = 0;

        if (ReadFile(m_FileHandle, data, bytesToRead, &bytesRead, nullptr) == FALSE)
        {
            throw WindowsException(
                HRESULT_FROM_WIN32(GetLastError()),
                "Failed to read from file. path: '%s', bytes to read: %lu", m_Path.GetPath(), bytesToRead
            );
        }

        m_Logger.Info("Read from file. path: '%s', bytes read: %lu", m_Path.GetPath(), bytesRead);
    }

    void File::Write(const void* data, size_t size) const
    {
        DWORD bytesToWrite = static_cast<DWORD>(size);
        DWORD bytesWritten = 0;

        if (WriteFile(m_FileHandle, data, bytesToWrite, &bytesWritten, nullptr) == FALSE)
        {
            throw WindowsException(
                HRESULT_FROM_WIN32(GetLastError()),
                "Failed to write to file. path: '%s', bytes to write: %lu", m_Path.GetPath(), bytesToWrite
            );
        }

        m_Logger.Info("Wrote to file. path: '%s', bytes written: %lu", m_Path.GetPath(), bytesWritten);
    }
}
