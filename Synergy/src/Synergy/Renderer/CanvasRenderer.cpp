// Created by Niels Marsman on 01-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

#include "Synergy/Renderer/CanvasRenderer.h"

#include "Synergy/Font.h"

#include "Synergy/Renderer/Shader.h"
#include "Synergy/Renderer/Shaders.h"
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
        Ref<Shader> textShader;
        
        Ref<Texture> whiteTexture;
        
        uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        glm::vec4 positions[4];
        
        glm::vec3 screen;
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
        
        data.shader = Synergy::Shaders::Load("CanvasRenderer.shader");
        data.shader->Bind();
        
        data.textShader = Synergy::Shaders::Load("TextRenderer.shader");
        data.textShader->Bind();
        
        data.positions[0] = { -0.5f, -0.5f, -1.0f, 1.0f };
        data.positions[1] = {  0.5f, -0.5f, -1.0f, 1.0f };
        data.positions[2] = {  0.5f,  0.5f, -1.0f, 1.0f };
        data.positions[3] = { -0.5f,  0.5f, -1.0f, 1.0f };
        
        data.screen = glm::vec3 { 800, 600, 1 };
        data.ortho = glm::ortho(0.0f, data.screen.x, 0.0f, data.screen.y, 0.0f, data.screen.z);
    }

    void CanvasRenderer::Initialize(RendererAPI* api)
    {
        Instance().api = api;
        Instance().Initialize();
    }

    void CanvasRenderer::SubmitRenderable(Renderable2D renderable)
    {
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
        
        std::array<const glm::vec2, 4> uvs = texture->GetUVs();
        
        Vertex buffer[4];
        
        glm::vec3 position = renderable.position * data.screen;
        glm::vec2 size = renderable.size * glm::vec2 { data.screen.x, data.screen.y };
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
            glm::scale(glm::mat4(1.0f), { size, 1.0f });
        
        for (size_t offset = 0; offset < 4; offset++)
        {
            buffer[offset].position = transform * data.positions[offset];
            buffer[offset].color = renderable.color;
            buffer[offset].uv = uvs[offset];
        }
        
        vertexBuffer->SetData(buffer, 4 * sizeof(Vertex));
        api->DrawIndexed(vertexArray, 6);
    }

    void CanvasRenderer::SubmitText(Text text)
    {
        RendererAPI* api = Instance().api;
        
        data.textShader->Bind();
        data.textShader->SetMat4("u_projection_view", data.ortho);
        data.textShader->SetFloat4("u_text_color", text.color);
        
        Ref<VertexArray> vertexArray = api->CreateVertexArray();
        Ref<VertexBuffer> vertexBuffer = api->CreateVertexBuffer(6 * 4 * sizeof(float));
        vertexBuffer->SetLayout({
            { Shader::DataType::VEC4, "a_vertex" }
        });
        
        vertexArray->AddVertexBuffer(vertexBuffer);
        
        Ref<Texture> texture = data.whiteTexture;
        
        texture->Activate(0);
        texture->Bind();
        
        float scale = 1.0;
        
        float x = text.position.x;
        float y = text.position.y;
        
        std::string::const_iterator character;
        for (character = text.text.begin(); character != text.text.end(); character++)
        {
            Synergy::Font::Character current = text.font->GetCharacter(*character);
            
            float xpos = x + current.bearing.x * scale;
            float ypos = y - (current.size.y - current.bearing.y) * scale;
            
            float width = current.size.x * scale;
            float height = current.size.y * scale;
            
            float vertices[6][4] = {
                { xpos          , ypos + height , 0.0f, 0.0f },
                { xpos          , ypos          , 0.0f, 1.0f },
                { xpos + width  , ypos          , 1.0f, 1.0f },
                
                { xpos          , ypos + height , 0.0f, 0.0f },
                { xpos + width  , ypos          , 1.0f, 1.0f },
                { xpos + width  , ypos + height , 1.0f, 0.0f }
            };
            
            current.texture->Bind();
            
            vertexBuffer->SetData(vertices, sizeof(vertices));
            api->DrawArrays(6);
            
            x += (current.advance >> 6) * scale;
        }
    }
}

