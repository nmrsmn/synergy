// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Memory/Allocator/Allocator.h"

namespace Synergy::Memory::Allocator
{
    Allocator::Allocator(const size_t size, const void* memory) :
        m_MemorySize(size),
        m_MemoryAddressStart(memory),
        m_MemoryUsed(0),
        m_Allocations(0)
    {}
}
