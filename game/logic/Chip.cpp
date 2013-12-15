#include "Chip.hpp"
#include "../Game.hpp"
#include "../../z_framework/zf_sfml/f_common.hpp"
const sf::Vector2f Chip::TimerOffset = sf::Vector2f(15, 28);
const sf::Vector2f Chip::TextBoundOffset = sf::Vector2f(33, 28);
const float Chip::BlinkInterval = 2;
Chip::Chip(Game& game, Board& board)
    : _game(game), _board(board), _timeText("9", game.assets.font, 14)
    , _position(0, 0), _arrows(game), _blink(BlinkInterval)
{
    _background = _game.assets.chipOutline.createSprite();
    _timer = _game.assets.clock.createSprite();
    _textBound = sf::FloatRect(TextBoundOffset.x, TextBoundOffset.y, 18, 13);
}

Chip::~Chip()
{
}

void Chip::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    window.draw(_background);
    _arrows.draw(window, delta);
    if(_state == Draw_Timer)
    {
        window.draw(_timer);
        window.draw(_timeText);
    }
}

void Chip::update(sf::RenderWindow& window, const sf::Time& delta)
{
    _arrows.update(window, delta);
    _blink -= delta.asSeconds();
    if(_blink < 0)
    {
        _blink += BlinkInterval;
        _state = _state == Draw_Icon ? Draw_Timer : Draw_Icon;
    }
}

void Chip::setPosition(const sf::Vector2f& position)
{
    _position = position;
    _background.setPosition(position);
    _timer.setPosition(position + TimerOffset);
    _textBound.left = position.x + TextBoundOffset.x;
    _textBound.top = position.y + TextBoundOffset.y;
    zf::alignText(_timeText, _textBound, zf::AlignmentData());
}

void Chip::rotate()
{
    _arrows.rotate();
}
