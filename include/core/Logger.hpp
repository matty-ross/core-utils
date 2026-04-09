#pragma once


namespace Core
{
    class Logger
    {
    public:
        Logger(const char* name);

    public:
        template <typename... Args>
        void Info(const char* format, Args... args) const
        {
            Log("INFO", format, args...);
        }

        template <typename... Args>
        void Warning(const char* format, Args... args) const
        {
            Log("WARNING", format, args...);
        }

        template <typename... Args>
        void Error(const char* format, Args... args) const
        {
            Log("ERROR", format, args...);
        }

    private:
        void Log(const char* level, const char* format, ...) const;

    private:
        const char* m_Name = "";
    };
}
