#include "Pixel.hpp"
#include "../Game.hpp"
Pixel::Pixel(Game& game, Type type)
    : _game(game), _type(type), _sprite(game.assets.shadedBox.createSprite())
{
    updateColor();
}

Pixel::Type Pixel::getPixelType()
{
    return _type;
}

void Pixel::setType(const Type& type)
{
    _type = type;
    updateColor();
}

void Pixel::moveTo(sf::Vector2f start, sf::Vector2f end, float time)
{
    _sprite.animateMoveTo(start, end, time);
}

void Pixel::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    _sprite.draw(window, delta);
}

void Pixel::update(sf::RenderWindow& window, const sf::Time& delta)
{
    _sprite.update(window, delta);
}

void Pixel::updateColor()
{
    switch(_type)
    {
        case White : _sprite.setColor(sf::Color(255,255,255)); break;
        case Red : _sprite.setColor(sf::Color(255,0,0)); break;
        case Blue : _sprite.setColor(sf::Color(0,0,255)); break;
        case Green : _sprite.setColor(sf::Color(0,255,0)); break;
        case Yellow : _sprite.setColor(sf::Color(255,255,0)); break;
        case Teal : _sprite.setColor(sf::Color(0,255,255)); break;
        case Magenta : _sprite.setColor(sf::Color(255,0,255)); break;
    }
}
