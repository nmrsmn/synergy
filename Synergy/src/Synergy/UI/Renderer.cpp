// Created by Niels Marsman on 10-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

#include "Synergy/UI/Renderer.h"

#include "Synergy/Font.h"

#include "Synergy/Renderer/Shader.h"
#include "Synergy/Renderer/Shaders.h"
#include "Synergy/Renderer/Texture.h"
#include "Synergy/Renderer/VertexArray.h"
#include "Synergy/Renderer/VertexBuffer.h"
#include "Synergy/Renderer/IndexBuffer.h"

namespace Synergy::UI
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 uv;
        glm::vec2 size;
        float radius;
    };

    struct Data
    {
        Synergy::Ref<Synergy::Shader> shader;
        Synergy::Ref<Synergy::Shader> textShader;
        
        Synergy::Ref<Synergy::Texture> whiteTexture;
        
        uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        glm::vec4 positions[4];
        
        glm::vec3 screen;
        glm::mat4 ortho;
    };

    static Data data;

    void Synergy::UI::Renderer::Submit(Synergy::UI::Quad renderable)
    {
        Synergy::Renderer::RendererAPI* api = Instance().api;
        
        data.shader->Bind();
        data.shader->SetMat4("u_projection_view", data.ortho);
        
        Synergy::Ref<Synergy::Renderer::VertexArray> vertexArray = api->CreateVertexArray();
        Synergy::Ref<Synergy::Renderer::VertexBuffer> vertexBuffer = api->CreateVertexBuffer(4 * sizeof(Vertex));
        Synergy::Ref<Synergy::Renderer::IndexBuffer> indexBuffer = api->CreateIndexBuffer(data.indices, 6);
        vertexBuffer->SetLayout({
            { Synergy::Shader::DataType::VEC3, "a_position" },
            { Synergy::Shader::DataType::VEC4, "a_color" },
            { Synergy::Shader::DataType::VEC2, "a_uv" },
            { Synergy::Shader::DataType::VEC2, "a_size" },
            { Synergy::Shader::DataType::FLOAT, "a_radius" }
        });
        
        vertexArray->AddVertexBuffer(vertexBuffer);
        vertexArray->SetIndexBuffer(indexBuffer);
        
        Synergy::Ref<Synergy::Texture> texture = renderable.texture != nullptr ? renderable.texture : data.whiteTexture;
        
        texture->Activate(0);
        texture->Bind();
        
        const glm::vec2* uvs = texture->GetUVs();
        
        Vertex buffer[4];
        
        glm::vec3 position = renderable.position;// * data.screen;
        glm::vec2 size = renderable.size;// * glm::vec2 { data.screen.x, data.screen.y };
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
            glm::scale(glm::mat4(1.0f), { size, 1.0f });
        
        for (size_t offset = 0; offset < 4; offset++)
        {
            buffer[offset].position = transform * data.positions[offset];
            buffer[offset].color = renderable.color;
            buffer[offset].uv = uvs[offset];
            buffer[offset].size = renderable.size;
            buffer[offset].radius = (renderable.radius / data.screen.x);
        }
        
        vertexBuffer->SetData(buffer, 4 * sizeof(Vertex));
        api->DrawIndexed(vertexArray, 6);
    }

    void Synergy::UI::Renderer::Submit(Synergy::UI::Text renderable)
    {
        Synergy::Renderer::RendererAPI* api = Instance().api;
        
        data.textShader->Bind();
        data.textShader->SetMat4("u_projection_view", data.ortho);
        data.textShader->SetFloat4("u_text_color", renderable.color);
        
        Synergy::Ref<Synergy::Renderer::VertexArray> vertexArray = api->CreateVertexArray();
        Synergy::Ref<Synergy::Renderer::VertexBuffer> vertexBuffer = api->CreateVertexBuffer(6 * 4 * sizeof(float));
        vertexBuffer->SetLayout({
            { Shader::DataType::VEC4, "a_vertex" }
        });
        
        vertexArray->AddVertexBuffer(vertexBuffer);
        
        Synergy::Ref<Synergy::Texture> texture = data.whiteTexture;
        
        texture->Activate(0);
        texture->Bind();
        
        float scale = 1.0;
        
        float x = renderable.position.x;
        float y = renderable.position.y;
        
        std::string::const_iterator character;
        for (character = renderable.text.begin(); character != renderable.text.end(); character++)
        {
            Synergy::Font::Character current = renderable.font->GetCharacter(*character);
            
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

    Synergy::UI::Renderer& Synergy::UI::Renderer::Instance()
    {
        static Synergy::UI::Renderer instance;
        return instance;
    }

    void Synergy::UI::Renderer::Initialize(Synergy::Renderer::RendererAPI* api)
    {
        Instance().api = api;
        Instance().Initialize();
    }

    Synergy::UI::Renderer::Renderer() {}

    void Synergy::UI::Renderer::Initialize()
    {
        uint32_t textureData = 0xffffffff;
        data.whiteTexture = Synergy::Texture::Create(1, 1);
        data.whiteTexture->SetData(&textureData, sizeof(textureData));
        
        data.shader = Synergy::Shaders::Load("UIRenderer.shader");
        data.shader->Bind();
        
        data.textShader = Synergy::Shaders::Load("TextRenderer.shader");
        data.textShader->Bind();
        
        data.positions[0] = { 0.0f, 0.0f, -1.0f, 1.0f };
        data.positions[1] = { 1.0f, 0.0f, -1.0f, 1.0f };
        data.positions[2] = { 1.0f, 1.0f, -1.0f, 1.0f };
        data.positions[3] = { 0.0f, 1.0f, -1.0f, 1.0f };
        
        data.screen = glm::vec3 { 800, 600, 1 };
        data.ortho = glm::ortho(0.0f, data.screen.x, 0.0f, data.screen.y, 0.0f, data.screen.z);
    }
}

