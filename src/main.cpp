#include <SFML/Graphics.hpp>
#include "JacksOrBetter.hpp"
#include "ResourceManager.hpp"

int main() {
    ResourceManager::getInstance().preloadTextures();
    JacksOrBetter jacksOrBetter;
    jacksOrBetter.run();
}