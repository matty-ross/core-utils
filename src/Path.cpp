#pragma comment(lib, "Shlwapi.lib")


#include <Windows.h>
#include <Shlwapi.h>
#include <ShlObj.h>

#include "core/WindowsException.hpp"
#include "core/Path.hpp"


namespace Core
{
    Path::Path(const char* path)
    {
        ExpandEnvironmentStringsA(path, m_Path, MAX_PATH);
    }
    
    const char* Path::GetPath() const
    {
        return m_Path;
    }

    Path& Path::Append(const char* path)
    {
        PathAppendA(m_Path, path);

        return *this;
    }
    
    bool Path::Exists() const
    {
        return PathFileExistsA(m_Path) == TRUE;
    }
    
    void Path::CreateDirectoryTree() const
    {
        int result = SHCreateDirectoryExA(NULL, m_Path, nullptr);
        if (result != ERROR_SUCCESS)
        {
            throw WindowsException(
                HRESULT_FROM_WIN32(result),
                "Cannot create directory tree. Path: '%s'.", m_Path
            );
        }
    }
}
