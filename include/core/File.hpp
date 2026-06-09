#pragma once


#include <Windows.h>

#include "core/Path.hpp"


namespace Core
{
    class File
    {
    public:
        enum class Mode
        {
            Read,
            Write,
            ReadAndWrite,
        };

    public:
        File(const Core::Path& path, Mode mode);
        ~File();

        File(const File&) = delete;
        File(File&&) = delete;

        File& operator =(const File&) = delete;
        File& operator =(File&&) = delete;

    public:
        size_t GetSize() const;

        template <typename T>
        __forceinline T Read() const
        {
            T content(GetSize(), {});
            Read(content.data(), content.size());

            return content;
        }

        template <typename T>
        __forceinline void Write(const T& content) const
        {
            Write(content.data(), content.size());
        }

    private:
        void Read(void* buffer, size_t size) const;
        void Write(const void* buffer, size_t size) const;

    private:
        Core::Path m_Path;
        HANDLE m_FileHandle = INVALID_HANDLE_VALUE;
    };
}
