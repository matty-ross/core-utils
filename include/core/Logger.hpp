#pragma once


namespace Core
{
    class Logger
    {
    public:
        Logger(const char* name);

    public:
        static void Initialize();

    public:
        template <typename... Args>
        __forceinline void Info(const char* format, Args... args) const
        {
            Log("\x1B[1;32mINFO\x1B[0m", format, args...);
        }

        template <typename... Args>
        __forceinline void Warning(const char* format, Args... args) const
        {
            Log("\x1B[1;33mWARNING\x1B[0m", format, args...);
        }

        template <typename... Args>
        __forceinline void Error(const char* format, Args... args) const
        {
            Log("\x1B[1;31mERROR\x1B[0m", format, args...);
        }

    private:
        void Log(const char* level, const char* format, ...) const;

    private:
        const char* m_Name = "";
    };
}
