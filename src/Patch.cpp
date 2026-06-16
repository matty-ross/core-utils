#include <cstddef>
#include <cstdint>
#include <Windows.h>

#include "core/Pointer.hpp"
#include "core/WindowsException.hpp"
#include "core/Logger.hpp"
#include "core/Patch.hpp"


namespace Core
{
    Patch::Patch(Pointer address, size_t size, const Logger& logger)
        :
        m_Address(address),
        m_Size(size),
        m_Logger(logger)
    {
    }

    void Patch::WriteBytes(Pointer bytes, size_t size) const
    {
        Apply(bytes, size);
    }

    void Patch::WriteNOPs() const
    {
        Apply(nullptr, 0);
    }

    void Patch::WriteJMP(Pointer destination) const
    {
        // JMP rel32
        std::byte instruction[5] = { std::byte{ 0xE9 } };
        int32_t offset = static_cast<int32_t>(destination.GetPointer<std::byte*>() - m_Address.GetPointer<std::byte*>() - 0x5);
        Pointer(instruction).at(0x1).as<int32_t>() = offset;

        Apply(instruction, sizeof(instruction));
    }

    void Patch::Apply(Pointer bytes, size_t size) const
    {
        DWORD oldProtection = 0;

        if (VirtualProtect(m_Address.GetPointer(), m_Size, PAGE_EXECUTE_READWRITE, &oldProtection) == FALSE)
        {
            throw WindowsException(
                HRESULT_FROM_WIN32(GetLastError()),
                "Cannot change memory page protection. address: 0x%p, size: %zu", m_Address.GetPointer(), m_Size
            );
        }

        for (size_t i = 0; i < m_Size; ++i)
        {
            m_Address.at(i).as<std::byte>() = (i < size) ? bytes.at(i).as<std::byte>() : std::byte{ 0x90 };
        }

        if (VirtualProtect(m_Address.GetPointer(), m_Size, oldProtection, &oldProtection) == FALSE)
        {
            throw WindowsException(
                HRESULT_FROM_WIN32(GetLastError()),
                "Cannot restore memory page protection. address: 0x%p, size: %zu", m_Address.GetPointer(), m_Size
            );
        }

        m_Logger.Info("Applied patch. address: 0x%p, size: %zu", m_Address.GetPointer(), m_Size);
    }
}
