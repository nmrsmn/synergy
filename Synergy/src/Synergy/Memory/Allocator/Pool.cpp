// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Memory/Allocator/Pool.h"

namespace Synergy::Memory::Allocator
{
    Pool::Pool(const size_t size, const void* memory, size_t objectSize, uint8_t objectAlignment) :
        Synergy::Memory::Allocator::Allocator(size, memory),
        m_ObjectSize(objectSize),
        m_ObjectAlignment(objectAlignment)
    {
        this->Clear();
    }

    Pool::~Pool()
    {
        this->m_FreeList = nullptr;
    }

    void* Pool::Allocate(size_t size, uint8_t alignment)
    {
        SYNERGY_ASSERT(size > 0, "Allocated called with size of 0.");
        SYNERGY_ASSERT(size == m_ObjectSize && alignment == m_ObjectAlignment, "Supplied size or alignment mismatch");
        
        if (this->m_FreeList == nullptr)
            return nullptr;
        
        void* memory = this->m_FreeList;
        
        this->m_FreeList = (void**) (*this->m_FreeList);
        
        this->m_MemoryUsed += this->m_ObjectSize;
        this->m_Allocations++;
        
        return memory;
    }

    void Pool::Free(void* memory)
    {
        *((void**) memory) = this->m_FreeList;
        this->m_FreeList = (void**) memory;
        
        this->m_MemoryUsed -= this->m_ObjectSize;
        this->m_Allocations--;
    }

    void Pool::Clear()
    {
        uint8_t adjustment = Allocator::GetAdjustment(this->m_MemoryAddressStart, this->m_ObjectAlignment);
        
        size_t objects = (size_t) floor((this->m_MemorySize - adjustment) / this->m_ObjectSize);
        
        union
        {
            void* asVoidPtr;
            uintptr_t asUptr;
        };
        
        asVoidPtr = (void*) this->m_MemoryAddressStart;
        asUptr += adjustment;
        
        this->m_FreeList = (void**) asVoidPtr;
        void** pointer = this->m_FreeList;
        
        for (int index = 0; index < (objects - 1); ++index)
        {
            *pointer = (void*) ((uintptr_t) pointer + this->m_ObjectSize);
            pointer = (void**) *pointer;
        }
        
        *pointer = nullptr;
    }
}
