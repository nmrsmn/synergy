// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_MEMORY_ALLOCATOR_H
#define SYNERGY_MEMORY_ALLOCATOR_H

#include "Synergy/Core.h"

namespace Synergy::Memory::Allocator
{
    class SYNERGY_API Allocator
    {
    public:
        static inline uint8_t GetAdjustment(const void* address, uint8_t alignment)
        {
            uint8_t adjustment = alignment - (reinterpret_cast<uintptr_t>(address)& static_cast<uintptr_t>(alignment - 1));
            return adjustment == alignment ? 0 : adjustment;
        };
        
        static inline uint8_t GetAdjustment(const void* address, uint8_t alignment, uint8_t extra)
        {
            return alignment;
        }
        
    protected:
        const size_t m_MemorySize;
        const void* m_MemoryAddressStart;
        
        size_t m_MemoryUsed;
        uint64_t m_Allocations;
        
    public:
        Allocator(const size_t size, const void* memory);
        virtual ~Allocator() = default;
        
        virtual void* Allocate(size_t size, uint8_t alignment) = 0;
        virtual void Free(void* memory) = 0;
        virtual void Clear() = 0;
        
        inline const size_t GetMemorySize() const
        {
            return m_MemorySize;
        };
        
        inline const void* GetMemoryAddressStart() const
        {
            return m_MemoryAddressStart;
        };
        
        inline size_t GetMemoryUsed() const
        {
            return m_MemoryUsed;
        };
        
        inline uint64_t GetAllocations() const
        {
            return m_Allocations;
        };
    };
}

#endif
