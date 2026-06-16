#pragma once


#include <cstddef>

#include "core/Pointer.hpp"
#include "core/Logger.hpp"


namespace Core
{
    class Patch
    {
    public:
        Patch(Pointer address, size_t size, const Logger& logger);

    public:
        void WriteBytes(Pointer bytes, size_t size) const;
        void WriteNOPs() const;
        void WriteJMP(Pointer destination) const;

    private:
        void Apply(Pointer bytes, size_t size) const;

    private:
        Pointer m_Address = nullptr;
        size_t m_Size = 0;

        const Logger& m_Logger;
    };
}
