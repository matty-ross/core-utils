#include "core/WindowsException.hpp"
#include "core/File.hpp"


namespace Core
{
    File::File(const Core::Path& path, Mode mode)
        :
        m_Path(path)
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

        case Mode::ReadAndWrite:
            desiredAccess = GENERIC_READ | GENERIC_WRITE;
            creationDisposition = OPEN_ALWAYS;
        }

        m_FileHandle = CreateFileA(m_Path.GetPath(), desiredAccess, FILE_SHARE_READ, nullptr, creationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);
        if (m_FileHandle == INVALID_HANDLE_VALUE)
        {
            throw new WindowsException(
                HRESULT_FROM_WIN32(GetLastError()),
                "Cannot open or create file. Path: '%s'.", m_Path.GetPath()
            );
        }
    }

    File::~File()
    {
        if (m_FileHandle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(m_FileHandle);
        }
    }

    size_t File::GetSize() const
    {
        return GetFileSize(m_FileHandle, nullptr);
    }

    void File::Read(void* buffer, size_t size) const
    {
        DWORD bytesRead = 0;
        if (ReadFile(m_FileHandle, buffer, size, &bytesRead, nullptr) == FALSE)
        {
            throw new WindowsException(
                HRESULT_FROM_WIN32(GetLastError()),
                "Cannot read from file. Path: '%s'.", m_Path.GetPath()
            );
        }
    }

    void File::Write(const void* buffer, size_t size) const
    {
        DWORD bytesWritten = 0;
        if (WriteFile(m_FileHandle, buffer, size, &bytesWritten, nullptr) == FALSE)
        {
            throw new WindowsException(
                HRESULT_FROM_WIN32(GetLastError()),
                "Cannot write to file. Path: '%s'.", m_Path.GetPath()
            );
        }
    }
}
