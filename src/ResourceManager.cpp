#include "ResourceManager.hpp"

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

void ResourceManager::preloadTextures() {
    fonts["toxi"] = sf::Font("res/toxigenesis bd.otf");
    //warning C4834: discarding return value of function with [[nodiscard]] attribute
    textures["cards"].loadFromFile("res/cards_sheet2.png");
    textures["background"].loadFromFile("res/background.jpg");
    textures["dealbtn_idle"].loadFromFile("res/Idle2x.png");
    textures["dealbtn_click"].loadFromFile("res/Click2x.png");
}

sf::Texture& ResourceManager::getTexture(const std::string& key) {
    return textures[key];
}

sf::Font& ResourceManager::getFont(const std::string& key) {
    return fonts[key];
}