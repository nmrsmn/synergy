// Created by Niels Marsman on 01-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

#include "Synergy/Renderer/CanvasRenderer.h"

#include "Synergy/Renderer/Shader.h"
#include "Synergy/Renderer/Texture.h"
#include "Synergy/Renderer/VertexArray.h"
#include "Synergy/Renderer/VertexBuffer.h"
#include "Synergy/Renderer/IndexBuffer.h"

namespace Synergy::Renderer
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 uv;
    };

    struct Data
    {
        Ref<Shader> shader;
        Ref<Texture> whiteTexture;
        
        uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        glm::vec4 positions[4];
        
        glm::mat4 ortho;
    };

    static Data data;

    CanvasRenderer& CanvasRenderer::Instance()
    {
        static CanvasRenderer instance;
        return instance;
    }

    void CanvasRenderer::Initialize()
    {
        uint32_t textureData = 0xffffffff;
        data.whiteTexture = api->CreateTexture(1, 1);
        data.whiteTexture->SetData(&textureData, sizeof(textureData));
        
        std::map<Shader::Type, const std::string&> sources = {
            { Shader::Type::VERTEX, vertex_shader_source },
            { Shader::Type::FRAGMENT, fragment_shader_source }
        };
        
        data.shader = api->CreateShader("CanvasRenderer", sources);
        data.shader->Bind();
        
        data.positions[0] = { -0.5f, -0.5f, -1.0f, 1.0f };
        data.positions[1] = {  0.5f, -0.5f, -1.0f, 1.0f };
        data.positions[2] = {  0.5f,  0.5f, -1.0f, 1.0f };
        data.positions[3] = { -0.5f,  0.5f, -1.0f, 1.0f };
        
        data.ortho = glm::ortho(-2.0, 2.0, -1.5, 1.5, -1.0, 1.0);
    }

    void CanvasRenderer::Initialize(RendererAPI* api)
    {
        Instance().api = api;
        Instance().Initialize();
    }

    void CanvasRenderer::SubmitRenderable(Renderable2D renderable)
    {
        static constexpr glm::vec2 uvs[] = {
            { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f }
        };
        
        RendererAPI* api = Instance().api;
        
        data.shader->Bind();
        data.shader->SetMat4("u_projection_view", data.ortho);
        
        Ref<VertexArray> vertexArray = api->CreateVertexArray();
        Ref<VertexBuffer> vertexBuffer = api->CreateVertexBuffer(4 * sizeof(Vertex));
        Ref<IndexBuffer> indexBuffer = api->CreateIndexBuffer(data.indices, 6);
        vertexBuffer->SetLayout({
            { Shader::DataType::VEC3, "a_position" },
            { Shader::DataType::VEC4, "a_color" },
            { Shader::DataType::VEC2, "a_uv" }
        });
        
        vertexArray->AddVertexBuffer(vertexBuffer);
        vertexArray->SetIndexBuffer(indexBuffer);
        
        Ref<Texture> texture = renderable.texture != nullptr ? renderable.texture : data.whiteTexture;
        
        texture->Activate(0);
        texture->Bind();
        
        Vertex buffer[4];
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), renderable.position) *
            glm::scale(glm::mat4(1.0f), { renderable.size.x, renderable.size.y, 1.0f });
        
        for (size_t offset = 0; offset < 4; offset++)
        {
            buffer[offset].position = transform * data.positions[offset];
            buffer[offset].color = renderable.color;
            buffer[offset].uv = uvs[offset];
        }
        
        vertexBuffer->SetData(buffer, 4 * sizeof(Vertex));
        api->DrawIndexed(vertexArray, 6);
    }
}

