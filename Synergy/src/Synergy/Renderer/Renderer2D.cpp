// Created by Niels Marsman on 21-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <glm/gtc/matrix_transform.hpp>

#include "Synergy/Renderer/Renderer2D.h"

#include "Synergy/Renderer/Shader.h"
#include "Synergy/Renderer/VertexArray.h"
#include "Synergy/Renderer/VertexBuffer.h"
#include "Synergy/Renderer/IndexBuffer.h"

namespace Synergy::Renderer
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color;
    };

    struct Data
    {
        static const uint32_t quads = 20000;
        static const uint32_t vertices = quads * 4;
        static const uint32_t indices = quads * 6;
        
        Ref<Shader> shader;
        Ref<VertexArray> vertexArray;
        Ref<VertexBuffer> vertexBuffer;
        Ref<IndexBuffer> indexBuffer;
        
        uint32_t indexCount = 0;
        Vertex* vertexBufferStart = nullptr;
        Vertex* vertexBufferCurrent = nullptr;
        
        glm::vec4 positions[4];
    };

    static Data data;

    Renderer2D& Renderer2D::Instance()
    {
        static Renderer2D instance;
        return instance;
    }

    void Renderer2D::Initialize()
    {
        data.vertexArray = api->CreateVertexArray();
        data.vertexBuffer = api->CreateVertexBuffer(Data::vertices * sizeof(Vertex));
        data.vertexBuffer->SetLayout({
            { Shader::DataType::VEC3, "position" },
            { Shader::DataType::VEC4, "color" }
        });
        
        data.vertexArray->AddVertexBuffer(data.vertexBuffer);
        
        data.vertexBufferStart = new Vertex[Data::vertices];
        
        uint32_t* indices = new uint32_t[Data::indices];
        uint32_t offset = 0;
        
        for (uint32_t index = 0; index < Data::indices; index += 6)
        {
            indices[index + 0] = offset + 0;
            indices[index + 1] = offset + 1;
            indices[index + 2] = offset + 2;
            
            indices[index + 3] = offset + 2;
            indices[index + 4] = offset + 3;
            indices[index + 5] = offset + 0;
            
            offset += 4;
        }
        
        data.indexBuffer = api->CreateIndexBuffer(indices, Data::indices);
        
        data.vertexArray->SetIndexBuffer(data.indexBuffer);
        
        delete[] indices;
        
        std::map<Shader::Type, const std::string&> sources = {
            { Shader::Type::VERTEX, vertex_shader_source },
            { Shader::Type::FRAGMENT, fragment_shader_source }
        };
        
        data.shader = api->CreateShader("BatchRenderer2D", sources);
        
        data.positions[0] = { -0.5f, -0.5f, -1.0f, 1.0f };
        data.positions[1] = {  0.5f, -0.5f, -1.0f, 1.0f };
        data.positions[2] = {  0.5f,  0.5f, -1.0f, 1.0f };
        data.positions[3] = { -0.5f,  0.5f, -1.0f, 1.0f };
    }

    void Renderer2D::Initialize(RendererAPI* api)
    {
        Instance().api = api;
        Instance().Initialize();
    }

    void Renderer2D::BeginScene()
    {
        data.shader->Bind();
        
        data.indexCount = 0;
        data.vertexBufferCurrent = data.vertexBufferStart;
    }

    void Renderer2D::EndScene()
    {
        uint32_t size = (uint8_t*) data.vertexBufferCurrent - (uint8_t*) data.vertexBufferStart;
        data.vertexBuffer->SetData(data.vertexBufferStart, size);
        
        Flush();
    }

    void Renderer2D::Flush()
    {
        Instance().api->DrawIndexed(data.vertexArray, data.indexCount);
    }

    void Renderer2D::FlushAndReset()
    {
        Renderer2D::EndScene();
        
        data.indexCount = 0;
        data.vertexBufferCurrent = data.vertexBufferStart;
    }

    void Renderer2D::SubmitRenderable(Renderable2D renderable)
    {
        if (data.indexCount >= Data::indices)
            FlushAndReset();
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), renderable.position) *
            glm::scale(glm::mat4(1.0f), { renderable.size.x, renderable.size.y, 1.0f });
        
        for (size_t offset = 0; offset < 4; offset++)
        {
            data.vertexBufferCurrent->position = transform * data.positions[offset];
            data.vertexBufferCurrent->color = renderable.color;
            data.vertexBufferCurrent++;
        }
        
        data.indexCount += 6;
    }
}

