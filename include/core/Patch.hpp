#pragma once


#include <cstddef>

#include "core/Pointer.hpp"
#include "core/Logger.hpp"


namespace Core
{
    class Patch
    {
    public:
        Patch(const Core::Logger& logger, Core::Pointer address, size_t size);

    public:
        void WriteBytes(Core::Pointer bytes, size_t size);
        void WriteJump(Core::Pointer destination);

    private:
        void Apply(Core::Pointer bytes, size_t size);

    private:
        const Core::Logger& m_Logger;

        Core::Pointer m_Address = nullptr;
        size_t m_Size = 0;
    };
}
