// Created by Niels Marsman on 19-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_VERTEXBUFFER_H
#define SYNERGY_RENDERER_VERTEXBUFFER_H

#include <vector>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Bindable.h"
#include "Synergy/Renderer/Shader.h"

namespace Synergy::Renderer
{
    class SYNERGY_API VertexBuffer: public Bindable
    {
    public:
        class SYNERGY_API Layout
        {
        public:
            struct SYNERGY_API Element
            {
                const char* name;
                Shader::DataType type;
                uint32_t size;
                uint64_t offset = 0;
                bool normalized = false;
                
            public:
                Element();
                Element(Shader::DataType type, const char* name, bool normalized = false);
            };
            
        public:
            Layout();
            Layout(const std::initializer_list<Element>& elements);
            
            uint64_t GetStride() const;
            const std::vector<Element>& GetElements() const;
            
            std::vector<Element>::const_iterator Begin() const;
            std::vector<Element>::const_iterator End() const;
            
        private:
            void Recalculate();
            
        private:
            std::vector<Element> elements;
            uint64_t stride = 0;
        };
        
    public:
        virtual ~VertexBuffer() = default;
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        
        virtual const Layout& GetLayout() const = 0;
        virtual void SetLayout(const Layout& layout) = 0;
        
        virtual void SetData(const void* data, uint32_t size) = 0;
    };
}

#endif
