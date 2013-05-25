#ifndef TEXTURE_HEADER_FILE
#define TEXTURE_HEADER_FILE

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <string>

namespace Graphics {
    inline const sf::Texture & getTexture(std::string textureString) {
        static std::unordered_map<std::string, sf::Texture> textures_;

        // If we don't have it
        if ( textures_.find(textureString) == textures_.end() ) {
            sf::Texture t;
            if ( ! t.loadFromFile(textureString) ) throw std::runtime_error("Failed to load the requested texture: "+textureString);
            
            textures_[textureString] = t;
        }

        return textures_[textureString];
    }
    
}

#endif
