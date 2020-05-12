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
        
        struct Vertex
        {
            float x, y;
            float u, v;
        } vertices[6 * renderable.text.size()];
        
        data.textShader->Bind();
        data.textShader->SetMat4("u_projection_view", data.ortho);
        data.textShader->SetFloat4("u_text_color", renderable.color);
        
        Synergy::Ref<Synergy::Renderer::VertexArray> vertexArray = api->CreateVertexArray();
        Synergy::Ref<Synergy::Renderer::VertexBuffer> vertexBuffer = api->CreateVertexBuffer(sizeof(vertices));
        vertexBuffer->SetLayout({
            { Shader::DataType::VEC4, "a_vertex" }
        });
        
        vertexArray->AddVertexBuffer(vertexBuffer);
        
        Synergy::Ref<Synergy::Texture> texture = renderable.font->Texture();
        texture->Activate(0);
        texture->Bind();
        
        float scale = renderable.scale;
        
        const struct {
            float width;
            float height;
        } size = { (float) texture->GetWidth(), (float) texture->GetHeight() };
        
        float x = renderable.position.x;
        float y = renderable.position.y;
        
        uint32_t index = 0;
        
        std::string::const_iterator character;
        for (character = renderable.text.begin(); character != renderable.text.end(); character++)
        {
            Synergy::Font::Glyph glyph = renderable.font->GetCharacter(*character);
            
            float xpos = x + glyph.bearing.left * scale;
            float ypos = y - (glyph.size.height - glyph.bearing.top) * scale;
            
            float width = glyph.size.width * scale;
            float height = glyph.size.height * scale;
            
            x += (glyph.advance.x >> 6) * scale;
            y += (glyph.advance.y >> 6) * scale;
            
            if (!glyph.size.width || !glyph.size.height)
                continue;
            
/*
 data.positions[0] = { 0.0f, 0.0f, -1.0f, 1.0f };
 data.positions[1] = { 1.0f, 0.0f, -1.0f, 1.0f };
 data.positions[2] = { 1.0f, 1.0f, -1.0f, 1.0f };
 data.positions[3] = { 0.0f, 1.0f, -1.0f, 1.0f };
 */
            
            vertices[index++] = { xpos          , ypos + height , glyph.texture.x                                  , glyph.texture.y };
            vertices[index++] = { xpos          , ypos          , glyph.texture.x                                  , glyph.texture.y + (glyph.size.height / size.height) };
            vertices[index++] = { xpos + width  , ypos          , glyph.texture.x + (glyph.size.width / size.width), glyph.texture.y + (glyph.size.height / size.height) };

            vertices[index++] = { xpos + width  , ypos          , glyph.texture.x + (glyph.size.width / size.width), glyph.texture.y + (glyph.size.height / size.height) };
            vertices[index++] = { xpos + width  , ypos + height , glyph.texture.x + (glyph.size.width / size.width), glyph.texture.y };
            vertices[index++] = { xpos          , ypos + height , glyph.texture.x                                  , glyph.texture.y };
        }

        vertexBuffer->SetData(vertices, sizeof(vertices));
        api->DrawArrays(index);
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

