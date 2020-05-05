// Created by Niels Marsman on 04-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/ResourcePack.h"

namespace Synergy
{
    Synergy::ResourcePack::Buffer::Buffer(std::ifstream& stream, uint32_t offset, uint32_t size)
    {
        memory.resize(size);
        
        stream.seekg(offset);
        stream.read(memory.data(), memory.size());
        
        setg(memory.data(), memory.data(), memory.data() + size);
    }

    Synergy::Ref<Synergy::ResourcePack> ResourcePack::Create()
    {
        struct RefEnabler: public Synergy::ResourcePack
        {
            explicit RefEnabler(): Synergy::ResourcePack() {}
        };
        
        return Synergy::CreateRef<RefEnabler>();
    }

    Synergy::Ref<Synergy::ResourcePack> ResourcePack::Load(const std::string& file, const std::optional<std::string> key)
    {
        struct RefEnabler: public Synergy::ResourcePack
        {
            explicit RefEnabler(const std::string& file, const std::optional<std::string> key): Synergy::ResourcePack(file, key) {}
        };
        
        return Synergy::CreateRef<RefEnabler>(file, key);
    }

    ResourcePack::~ResourcePack()
    {
        stream.close();
    }
    
    bool ResourcePack::Add(const std::string& file)
    {
        if (mode != Synergy::ResourcePack::Mode::WRITE)
        {
            SYNERGY_ASSERT(false, "Adding file to READ ONLY ResourcePack failed.");
            return false;
        }
        
        const std::string path = this->MakePosix(file);
        
        if (std::filesystem::exists(path))
        {
            Synergy::ResourcePack::Resource resource;
            resource.size = (uint32_t) std::filesystem::file_size(path);
            resource.offset = 0;
            resources.insert({ path, resource });
            return true;
        }
        
        return false;
    }

    bool ResourcePack::Add(const std::string& file, const std::string& content)
    {
        if (mode != Synergy::ResourcePack::Mode::WRITE)
        {
            SYNERGY_ASSERT(false, "Adding file to READ ONLY ResourcePack failed.");
            return false;
        }
        
        const std::string path = this->MakePosix(file);
        
        Synergy::ResourcePack::Resource resource;
        resource.size = (uint32_t) content.size();
        resource.offset = 0;
        resources.insert({ path, resource });
        sources.insert({ path, content.c_str() });
        
        return true;
    }

    bool ResourcePack::Save(const std::string& pack, const std::optional<std::string> key)
    {
        if (mode != Synergy::ResourcePack::Mode::WRITE)
        {
            SYNERGY_ASSERT(false, "Saving a READ ONLY ResourcePack failed.");
            return false;
        }
        
        std::ofstream output(pack, std::ofstream::binary);
        if (!output.is_open())
        {
            SYNERGY_ASSERT(false, "Failed to open ResourcePack for writing.");
            return false;
        }
        
        uint32_t index = 0;
        output.write((char*) &index, sizeof(uint32_t));
        
        uint32_t entries = uint32_t(resources.size());
        output.write((char*) &entries, sizeof(uint32_t));
        
        for (auto& entry : resources)
        {
            size_t size = entry.first.size();
            output.write((char*) &size, sizeof(uint32_t));
            output.write(entry.first.c_str(), size);
            
            output.write((char*) &entry.second.size, sizeof(uint32_t));
            output.write((char*) &entry.second.offset, sizeof(uint32_t));
        }
        
        std::streampos offset = output.tellp();
        index = (uint32_t) offset;
        
        for (auto& entry : resources)
        {
            entry.second.offset = (uint32_t) offset;
            
            std::vector<uint8_t> buffer(entry.second.size);
            if (auto source { sources.find(entry.first) }; source != sources.end())
            {
                memcpy(buffer.data(), source->second, entry.second.size);
            }
            else
            {
                std::ifstream stream(entry.first, std::ifstream::binary);
                stream.read((char*) buffer.data(), entry.second.size);
                stream.close();
            }
            
            output.write((char*) buffer.data(), entry.second.size);
            offset += entry.second.size;
        }

        std::vector<char> stream;
        auto write = [&stream](const char* data, size_t size)
        {
            uint32_t current = stream.size();
            stream.resize(current + size);
            memcpy(stream.data() + current, data, size);
        };

        write((char*) &entries, sizeof(uint32_t));
        for (auto& entry : resources)
        {
            size_t size = entry.first.size();
            write((char*) &size, sizeof(uint32_t));
            write(entry.first.c_str(), size);

            write((char*) &entry.second.size, sizeof(uint32_t));
            write((char*) &entry.second.offset, sizeof(uint32_t));
        }

        std::vector<char> scrambled = key.has_value() ? this->Scramble(stream, key.value()) : stream;
        uint32_t length = uint32_t(scrambled.size());

        output.seekp(0, std::ios::beg);
        output.write((char*) &length, sizeof(uint32_t));
        output.write(scrambled.data(), length);
        output.close();
        
        return true;
    }

    bool ResourcePack::Read(const std::string& file, auto (*read)(Synergy::ResourcePack::Buffer) -> bool)
    {
        if (mode != Synergy::ResourcePack::Mode::READ)
        {
            SYNERGY_ASSERT(false, "Reading file from WRITE ONLY ResourcePack failed.");
            return false;
        }
        
        if (auto entry { resources.find(file) }; entry == resources.end())
        {
            return false;
        }
        else
        {
            Synergy::ResourcePack::Resource resource = entry->second;
            Synergy::ResourcePack::Buffer buffer(stream, resource.offset, resource.size);
            return read(buffer);
        }
    }

    Synergy::Ref<Synergy::ResourcePack> ResourcePack::Parse(const std::string& file, const std::optional<std::string> key)
    {
        if (mode != Synergy::ResourcePack::Mode::READ)
        {
            SYNERGY_ASSERT(false, "Reading file from WRITE ONLY ResourcePack failed.");
            return nullptr;
        }
        
        if (auto entry { resources.find(file) }; entry == resources.end())
        {
            return nullptr;
        }
        else
        {
            Synergy::ResourcePack::Resource resource = entry->second;
            Synergy::ResourcePack::Buffer buffer(stream, resource.offset, resource.size);
            
            struct RefEnabler: public Synergy::ResourcePack
            {
                explicit RefEnabler(Synergy::ResourcePack::Buffer buffer, const std::optional<std::string> key): Synergy::ResourcePack(buffer, key) {}
            };
            
            return Synergy::CreateRef<RefEnabler>(buffer, key);
        }
    }

    ResourcePack::ResourcePack(): mode(Synergy::ResourcePack::Mode::WRITE) { }

    ResourcePack::ResourcePack(const std::string& file, const std::optional<std::string> key): mode(Synergy::ResourcePack::Mode::READ)
    {
        stream.open(file, std::ifstream::binary);
        if (!stream.is_open())
        {
            SYNERGY_ASSERT(false, "Failed to open ResourcePack for reading.");
            return;
        }
        
        std::istream& stream = this->stream;
        Process(stream, key);
    }

    ResourcePack::ResourcePack(Synergy::ResourcePack::Buffer buffer, const std::optional<std::string> key): mode(Synergy::ResourcePack::Mode::READ)
    {
        std::istream stream = std::istream { &buffer };
        Process(stream, key);
    }

    void ResourcePack::Process(std::istream& stream, const std::optional<std::string> key)
    {
        uint32_t size;
        stream.read((char*) &size, sizeof(uint32_t));
        
        std::vector<char> buffer(size);
        for (uint32_t index = 0; index < size; index++)
        {
            buffer[index] = stream.get();
        }
        
        std::vector<char> decoded = key.has_value() ? this->Scramble(buffer, key.value()) : buffer;
        uint32_t position = 0;
        
        auto read = [&decoded, &position](char* destination, size_t size)
        {
            memcpy((void*) destination, (const void*) (decoded.data() + position), size);
            position += size;
        };
        
        auto get = [&read]() -> int {
            char character;
            read(&character, 1);
            return character;
        };
        
        uint32_t entries = 0;
        read((char*) &entries, sizeof(uint32_t));
        for (uint32_t index = 0; index < entries; index++)
        {
            uint32_t filePathSize = 0;
            read((char*) &filePathSize, sizeof(uint32_t));
            
            std::string file(filePathSize, ' ');
            for (uint32_t character = 0; character < filePathSize; character++)
            {
                file[character] = get();
            }
            
            Synergy::ResourcePack::Resource resource;
            read((char*) &resource.size, sizeof(uint32_t));
            read((char*) &resource.offset, sizeof(uint32_t));
            resources.insert({ file, resource });
        }
    }

    std::vector<char> ResourcePack::Scramble(const std::vector<char>& data, const std::string& key)
    {
        if (key.empty())
        {
            return data;
        }
        
        std::vector<char> output;
        uint32_t count = 0;
        
        for (char character : data)
        {
            output.push_back(character ^ key[(count++) % key.size()]);
        }
        
        return output;
    }
    
    std::string ResourcePack::MakePosix(const std::string& file)
    {
        std::string output;
        
        for (char character: file)
        {
            output += std::string(1, character == '\\' ? '/' : character);
        }
        
        return output;
    }
}
