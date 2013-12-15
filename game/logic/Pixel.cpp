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
    _sprite.setColor(getColor(_type));
}
