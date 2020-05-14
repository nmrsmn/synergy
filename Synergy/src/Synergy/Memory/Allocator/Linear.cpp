// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Memory/Allocator/Linear.h"

namespace Synergy::Memory::Allocator
{
    Linear::Linear(const size_t size, const void* memory) :
        Synergy::Memory::Allocator::Allocator(size, memory)
    {}

    Linear::~Linear()
    {
        this->Clear();
    }

    void* Linear::Allocate(size_t size, uint8_t alignment)
    {
        SYNERGY_ASSERT(size > 0, "Allocated called with size of 0.");
        
        union
        {
            void* asVoidPtr;
            uintptr_t asUptr;
        };
        
        asVoidPtr = (void*) this->m_MemoryAddressStart;
        asUptr += this->m_MemoryUsed;
        
        uint8_t adjustment = Allocator::GetAdjustment(asVoidPtr, alignment);
        
        if (this->m_MemoryUsed + size + adjustment > this->m_MemorySize)
        {
            return nullptr;
        }
        
        asUptr += adjustment;
        
        this->m_MemoryUsed += size + adjustment;
        this->m_Allocations++;
        
        return asVoidPtr;
    }

    void Linear::Free(void* memory)
    {
        SYNERGY_ASSERT(false, "Linear allocators don't support free operations. Use clear instead.");
    }

    void Linear::Clear()
    {
        this->m_MemoryUsed = 0;
        this->m_Allocations = 0;
    }
}
