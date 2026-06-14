#pragma once


#include <cstddef>
#include <string>
#include <vector>
#include <Windows.h>

#include "core/Path.hpp"
#include "core/Logger.hpp"


namespace Core
{
    class File
    {
    public:
        enum class Mode
        {
            Read,
            Write,
        };

    public:
        File(const Path& path, Mode mode, const Logger& logger);
        File(const File&) = delete;
        File(File&&) = delete;
        ~File();

        File& operator =(const File&) = delete;
        File& operator =(File&&) = delete;

    public:
        size_t GetSize() const;

        std::string ReadAsText() const;
        std::vector<std::byte> ReadAsBinary() const;
        void WriteAsText(const std::string& content) const;
        void WriteAsBinary(const std::vector<std::byte>& content) const;

    private:
        void Read(void* data, size_t size) const;
        void Write(const void* data, size_t size) const;

    private:
        Path m_Path;
        HANDLE m_FileHandle = INVALID_HANDLE_VALUE;

        const Logger& m_Logger;
    };
}
