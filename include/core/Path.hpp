#pragma once


#include <Windows.h>


namespace Core
{
    class Path
    {
    public:
        Path(const char* path);

    public:
        Path& Append(const char* path);

        bool Exists() const;
        void CreateDirectoryTree() const;

    private:
        char m_Path[MAX_PATH] = {};
    };
}
