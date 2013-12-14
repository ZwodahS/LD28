#ifndef _GAME_ASSETS_
#define _GAME_ASSETS_
#include <SFML/Graphics.hpp>
#include "../z_framework/zf_sfml/SpriteSheet.hpp"
#include "../z_framework/zf_sfml/TextureRegion.hpp"


struct Assets
{
    zf::TextureRegion conversionArrow;
    zf::TextureRegion shadedBox;
    zf::TextureRegion chipOutline;
    zf::TextureRegion clock;
    zf::TextureRegion dollar;
    zf::TextureRegion power;
    zf::TextureRegion arrow_down;
    zf::TextureRegion arrow_left;
    zf::TextureRegion arrow_up;
    zf::TextureRegion arrow_right;

    sf::Font font;
    sf::Texture master1;
    zf::SpriteSheet masterS1;
};
#endif
