// Created by Niels Marsman on 04-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RESOURCE_PACK_H
#define SYNERGY_RESOURCE_PACK_H

#include <fstream>
#include <optional>
#include <streambuf>
#include <unordered_map>

#include "Synergy/Core.h"

namespace Synergy
{
    class SYNERGY_API ResourcePack
    {
    public:
        enum class Mode
        {
            READ = 1,
            WRITE
        };
        
        struct Resource
        {
            uint32_t size;
            uint32_t offset;
        };
        
        struct Buffer: public std::streambuf
        {
        public:
            Buffer(std::ifstream& stream, uint32_t offset, uint32_t size);
            
        public:
            std::vector<char> memory;
        };
        
    public:
        static Synergy::Ref<Synergy::ResourcePack> Create();
        static Synergy::Ref<Synergy::ResourcePack> Load(const std::string& file, const std::optional<std::string> key = std::nullopt);
        
    public:
        ~ResourcePack();
        
        bool Add(const std::string& file);
        bool Add(const std::string& file, const std::string& content);
        bool Save(const std::string& pack, const std::optional<std::string> key = std::nullopt);
        
        bool Read(const std::string& file, auto (*read)(Synergy::ResourcePack::Buffer) -> bool);
        
        Synergy::Ref<Synergy::ResourcePack> Parse(const std::string& file, const std::optional<std::string> key = std::nullopt);
                
    private:
        ResourcePack();
        ResourcePack(const std::string& file, const std::optional<std::string> key = std::nullopt);
        ResourcePack(Synergy::ResourcePack::Buffer, const std::optional<std::string> key = std::nullopt);
        
        void Process(std::istream& stream, const std::optional<std::string> key = std::nullopt);
        
        std::vector<char> Scramble(const std::vector<char>& data, const std::string& key);
        std::string MakePosix(const std::string& file);
        
    private:
        Synergy::ResourcePack::Mode mode;
        
        std::ifstream stream;
        std::unordered_map<std::string, Synergy::ResourcePack::Resource> resources;
        std::unordered_map<std::string, const char*> sources;
    };
}

#endif
