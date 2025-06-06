#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    static ResourceManager& getInstance();

    void preloadTextures();
    
    sf::Texture& getTexture(const std::string& key);
    sf::Font &getFont(const std::string &key);

private:
    ResourceManager() = default;
    ~ResourceManager() = default;
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
};