#include <cstdint>
#include <Windows.h>

#include "core/WindowsException.hpp"
#include "core/Patch.hpp"


namespace Core
{
    Patch::Patch(const Core::Logger& logger, Core::Pointer address, size_t size)
        :
        m_Logger(logger),
        m_Address(address),
        m_Size(size)
    {
    }

    void Patch::WriteBytes(Core::Pointer bytes, size_t size)
    {
        Apply(bytes, size);
    }

    void Patch::WriteJump(Core::Pointer destination)
    {
        int32_t offset = static_cast<int32_t>(destination.GetAddress<uint8_t*>() - m_Address.GetAddress<uint8_t*>() - 0x5);
        
        uint8_t instruction[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
        Core::Pointer(instruction).at(0x1).as<int32_t>() = offset;

        Apply(instruction, sizeof(instruction));
    }
    
    void Patch::Apply(Core::Pointer bytes, size_t size)
    {
        DWORD oldProtection = 0;
        if (VirtualProtect(m_Address.GetAddress(), m_Size, PAGE_EXECUTE_READWRITE, &oldProtection) == FALSE)
        {
            throw WindowsException(
                HRESULT_FROM_WIN32(GetLastError()),
                "Cannot change memory page protection. Address: 0x%p, size: %zu.", m_Address.GetAddress(), m_Size
            );
        }

        for (size_t i = 0; i < m_Size; ++i)
        {
            m_Address.at(i).as<uint8_t>() = (i < size) ? bytes.at(i).as<uint8_t>() : 0x90;
        }

        if (VirtualProtect(m_Address.GetAddress(), m_Size, oldProtection, &oldProtection) == FALSE)
        {
            throw WindowsException(
                HRESULT_FROM_WIN32(GetLastError()),
                "Cannot restore memory page protection. Address: 0x%p, size: %zu.", m_Address.GetAddress(), m_Size
            );
        }

        m_Logger.Info("Applied patch. Address: 0x%p, size: %zu.", m_Address.GetAddress(), m_Size);
    }
}
