#include "textures.hpp"

#include <unordered_map>

#include <SFML/Graphics.hpp>

namespace Graphics {
    const sf::Texture & getTexture(std::string textureString) {
        static std::unordered_map<std::string, sf::Texture> textures_;

        // If we don't have it
        if ( textures_.find(textureString) == textures_.end() ) {
            sf::Texture t;
            t.setSmooth(true); 
            if ( ! t.loadFromFile(textureString) ) throw std::runtime_error("Failed to load the requested texture: "+textureString);

            textures_[textureString] = t;
        }

        return textures_[textureString];
    }
}
