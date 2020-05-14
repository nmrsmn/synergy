// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_MEMORY_ALLOCATOR_STACK_H
#define SYNERGY_MEMORY_ALLOCATOR_STACK_H

#include "Synergy/Core.h"
#include "Synergy/Memory/Allocator/Allocator.h"

namespace Synergy::Memory::Allocator
{
    class Stack : public Synergy::Memory::Allocator::Allocator
    {
    private:
        struct AllocMetaInfo
        {
            uint8_t adjustment;
        };
        
    public:
        Stack(const size_t size, const void* memory);
        virtual ~Stack();
        
        virtual void* Allocate(size_t size, uint8_t alignment) override;
        virtual void Free(void* memory) override;
        virtual void Clear() override;
    };
}

#endif
