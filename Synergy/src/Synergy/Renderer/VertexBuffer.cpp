// Created by Niels Marsman on 19-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/VertexBuffer.h"

namespace Synergy::Renderer
{
    VertexBuffer::Layout::Element::Element(Shader::DataType type, const char* name, bool normalized)
        : name(name), type(type), size(Shader::DataTypeSize(type)), offset(0), normalized(normalized) {}

    VertexBuffer::Layout::Layout() {}

    VertexBuffer::Layout::Layout(const std::initializer_list<VertexBuffer::Layout::Element>& elements): elements(elements)
    {
        Recalculate();
    }

    uint64_t VertexBuffer::Layout::GetStride() const
    {
        return stride;
    }

    const std::vector<VertexBuffer::Layout::Element>& VertexBuffer::Layout::GetElements() const
    {
        return elements;
    }

    void VertexBuffer::Layout::Recalculate()
    {
        uint64_t offset = 0;
        stride = 0;
        for (VertexBuffer::Layout::Element& element : elements)
        {
            element.offset = offset;
            offset += element.size;
            stride += element.size;
        }
    }
}
