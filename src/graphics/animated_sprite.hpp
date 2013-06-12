#ifndef ANIMATED_SPRITE_HEADER_FILE
#define ANIMATED_SPRITE_HEADER_FILE

#include <SFML/Graphics.hpp>

class AnimatedSprite : public sf::Sprite {
    public:
        AnimatedSprite();
        AnimatedSprite(const sf::Texture &);
        AnimatedSprite(const sf::Texture &, const sf::IntRect & );

        void resize(int width, int height);

        bool getToRender();
        void setToRender(bool);

    private:
        bool toRender_;
};

#endif
