#include "Chip.hpp"
#include "Board.hpp"
#include "../Game.hpp"
#include "../../z_framework/zf_sfml/f_common.hpp"
#include "../../z_framework/zf_common/f_conversion.hpp"
const sf::Vector2f Chip::TimerOffset = sf::Vector2f(15, 28);
const sf::Vector2f Chip::TextBoundOffset = sf::Vector2f(33, 28);
Chip::Chip(Game& game, Board* board, ChipType t)
    : _game(game), _board(board), _timeText(" ", game.assets.font, 14)
    , _position(0, 0), _arrows(game), type(t), _runLeft(3)
{
    _background = _game.assets.chipOutline.createSprite();
    _timer = _game.assets.clock.createSprite();
    _textBound = sf::FloatRect(TextBoundOffset.x, TextBoundOffset.y, 18, 13);
    _bound = sf::FloatRect(0, 0, 64, 64);
    _timeText.setString(zf::toString(_runLeft));
}

Chip::~Chip()
{
}

void Chip::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    window.draw(_background);
    _arrows.draw(window, delta);
    if(_board != 0 && _board->chipDrawState == Board::Draw_Timer)
    {
        window.draw(_timer);
        window.draw(_timeText);
    }
}

void Chip::drawShadow(sf::RenderWindow& window, const sf::Time& delta, const sf::Vector2f& position)
{
    sf::Vector2f oldPos = _position;
    setPosition(position);
    setAlpha(100);
    draw(window, delta);
    setPosition(oldPos);
    setAlpha(255);
}

void Chip::update(sf::RenderWindow& window, const sf::Time& delta)
{
    _arrows.update(window, delta);
}

void Chip::setPosition(const sf::Vector2f& position)
{
    _position = position;
    _bound.left = position.x;
    _bound.top = position.y;
    _background.setPosition(position);
    _timer.setPosition(position + TimerOffset);
    _textBound.left = position.x + TextBoundOffset.x;
    _textBound.top = position.y + TextBoundOffset.y;
    zf::alignText(_timeText, _textBound, zf::AlignmentData());
    _arrows.setPosition(_position);
}

void Chip::rotate()
{
    _arrows.rotate();
}

const sf::FloatRect& Chip::getBound()
{
    return _bound;
}

void Chip::setAlpha(float alpha)
{
    zf::setAlpha(_background, alpha);
    zf::setAlpha(_timer, alpha);
    zf::setAlpha(_timeText, alpha);
    _arrows.setAlpha(alpha);
}

void Chip::setBoard(Board* board)
{
    _board = board;
}

void Chip::setArrow(ArrowControl::ArrowType north, ArrowControl::ArrowType east, ArrowControl::ArrowType south, ArrowControl::ArrowType west)
{
    _arrows.setArrow(zf::North, north);
    _arrows.setArrow(zf::East, east);
    _arrows.setArrow(zf::South, south);
    _arrows.setArrow(zf::West, west);
}

const std::vector<FactoryOutput*>& Chip::getInputs()
{
    return _inputs;
}

void Chip::put(FactoryOutput* input)
{
    _inputs.push_back(input);
}

bool Chip::clockDeplete()
{
    _runLeft--;
    _timeText.setString(zf::toString(_runLeft));
    setPosition(_position);
    if(_runLeft <= 0)
    {
        return true;
    }    
    return false;
}

void Chip::animateDestroy()
{
    // todo animate destroy if got time
}

bool Chip::isAnimating()
{
    //Todo animate destruction of chip if got chance
    return false;
}

bool Chip::markedForDestruction()
{
    return _runLeft <= 0;
}

bool Chip::acceptInputFrom(zf::Direction direction)
{
    return _arrows.hasIn(direction);
}
