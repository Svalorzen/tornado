#ifndef TEXTURE_HEADER_FILE
#define TEXTURE_HEADER_FILE

#include <string>

namespace sf { class Texture; }

namespace Graphics {
    const sf::Texture & getTexture(std::string textureString);    
}

#endif
