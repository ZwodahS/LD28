#include "ChipDetail.hpp"
#include "../Game.hpp"
const sf::Color ChipDetail::BorderColor = sf::Color(200, 200, 200);
const sf::Color ChipDetail::BackgroundColor = sf::Color(255, 255, 255, 50);
ChipDetail::ChipDetail(Game& game)
    : _game(game), _bound(0, 0, 300, 300), _border(sf::LinesStrip, 5), _background(sf::Quads, 4)
    , _currentShowingChip(0)
{
    _border[0].color = BorderColor;
    _border[1].color = BorderColor;
    _border[2].color = BorderColor;
    _border[3].color = BorderColor;
    _border[4].color = BorderColor;

    _background[0].color = BackgroundColor;
    _background[1].color = BackgroundColor;
    _background[2].color = BackgroundColor;
    _background[3].color = BackgroundColor;
}

void ChipDetail::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    if(_currentShowingChip != 0)
    {
        window.draw(_border);
        window.draw(_background);
    }
}

void ChipDetail::update(sf::RenderWindow& window, const sf::Time& delta)
{
}

void ChipDetail::setPosition(const sf::Vector2f& position)
{
    if(_currentShowingChip == 0)
    {
        // don't do anything, =/
    }
    else
    {
        _bound.left = position.x;
        _bound.top = position.y;
        updatePositions();
    }
}

void ChipDetail::updatePositions()
{
    _border[0].position = sf::Vector2f(_bound.left, _bound.top);
    _border[1].position = sf::Vector2f(_bound.left + _bound.width, _bound.top);
    _border[2].position = sf::Vector2f(_bound.left + _bound.width, _bound.top + _bound.height);
    _border[3].position = sf::Vector2f(_bound.left, _bound.top + _bound.height);
    _border[4].position = sf::Vector2f(_bound.left, _bound.top);

    _background[0].position = sf::Vector2f(_bound.left, _bound.top);
    _background[1].position = sf::Vector2f(_bound.left + _bound.width, _bound.top);
    _background[2].position = sf::Vector2f(_bound.left + _bound.width, _bound.top + _bound.height);
    _background[3].position = sf::Vector2f(_bound.left, _bound.top + _bound.height);
}

void ChipDetail::showChip(Chip* chip, Mode mode)
{
    _mode = mode;
    if(chip == 0)
    {
        _texts.clear();
        _sprites.clear();
        _currentShowingChip = 0;
    }
    else
    {
        if(mode == Board)
        {
        }
        else
        {
        }
    }
}
