// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_MEMORY_ALLOCATOR_POOL_H
#define SYNERGY_MEMORY_ALLOCATOR_POOL_H

#include "Synergy/Core.h"
#include "Synergy/Memory/Allocator/Allocator.h"

namespace Synergy::Memory::Allocator
{
    class SYNERGY_API Pool : public Synergy::Memory::Allocator::Allocator
    {
    private:
        const size_t m_ObjectSize;
        const uint8_t m_ObjectAlignment;
        
        void** m_FreeList;
        
    public:
        Pool(const size_t size, const void* memory, size_t objectSize, uint8_t objectAlignment);
        virtual ~Pool();
        
        virtual void* Allocate(size_t size, uint8_t alignment) override;
        virtual void Free(void* memory) override;
        virtual void Clear() override;
    };
}

#endif
