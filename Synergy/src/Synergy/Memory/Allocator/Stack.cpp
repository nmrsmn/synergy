// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Memory/Allocator/Stack.h"

namespace Synergy::Memory::Allocator
{
    Stack::Stack(const size_t size, const void* memory) :
        Synergy::Memory::Allocator::Allocator(size, memory)
    {}

    Stack::~Stack()
    {
        this->Clear();
    }

    void* Stack::Allocate(size_t size, uint8_t alignment)
    {
        SYNERGY_ASSERT(size > 0, "Allocated called with size of 0.");
        
        union
        {
            void* asVoidPtr;
            uintptr_t asUptr;
            AllocMetaInfo* asMetaInfo;
        };
        
        asVoidPtr = (void*) this->m_MemoryAddressStart;
        asUptr += this->m_MemoryUsed;
        
        uint8_t adjustment = Allocator::GetAdjustment(asVoidPtr, alignment, sizeof(AllocMetaInfo));
        
        if (this->m_MemoryUsed + size + adjustment > this->m_MemorySize)
        {
            return nullptr;
        }
        
        asMetaInfo->adjustment = adjustment;
        asUptr += adjustment;
        
        this->m_MemoryUsed += size + adjustment;
        this->m_Allocations++;
        
        return asVoidPtr;
    }

    void Stack::Free(void* memory)
    {
        union
        {
            void* asVoidPtr;
            uintptr_t asUptr;
            AllocMetaInfo* asMetaInfo;
        };
        
        asVoidPtr = memory;
        asUptr -= sizeof(AllocMetaInfo);
        
        this->m_MemoryUsed -= ((uintptr_t) this->m_MemoryAddressStart + this->m_MemoryUsed) - ((uintptr_t) memory + asMetaInfo->adjustment);
        this->m_Allocations--;
    }

    void Stack::Clear()
    {
        this->m_MemoryUsed = 0;
        this->m_Allocations = 0;
    }
}
