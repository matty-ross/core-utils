#pragma once


#include <cstddef>
#include <cstdint>


namespace Core
{
    class Pointer
    {
    public:
        __forceinline Pointer(void* pointer)
            :
            m_Pointer(pointer)
        {
        }

        __forceinline Pointer(uintptr_t pointer)
            :
            m_Pointer(reinterpret_cast<void*>(pointer))
        {
        }

    public:
        template <typename T = void*>
        __forceinline T GetPointer() const
        {
            return static_cast<T>(m_Pointer);
        }

        __forceinline Pointer deref() const
        {
            return *(static_cast<void**>(m_Pointer));
        }

        __forceinline Pointer at(ptrdiff_t offset) const
        {
            return reinterpret_cast<uintptr_t>(m_Pointer) + offset;
        }

        template <typename T>
        __forceinline T& as() const
        {
            return *(static_cast<T*>(m_Pointer));
        }

    private:
        void* m_Pointer = nullptr;
    };
}
