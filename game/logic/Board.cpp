#include "Board.hpp"
#include "../Game.hpp"
#include "Chip.hpp"
#include "PowerStation.hpp"
const float Board::BlinkInterval = 2;
Board::Board(Game& game)
    : _game(game), _chips(10, 10, 0), _blink(BlinkInterval), chipDrawState(Draw_Icon)
{
    sf::Color lineColor = sf::Color(50,50,50);
    for(int row = 0 ; row < 11 ; row ++)
    {
        sf::VertexArray line = sf::VertexArray(sf::Lines, 2);
        line[0].position = sf::Vector2f(20, 70 + row * (65));
        line[1].position = sf::Vector2f(670, 70 + row * (65));
        line[0].color = lineColor;
        line[1].color = lineColor;
        _lines.push_back(line);
    }
    for(int col = 0 ; col < 11 ; col ++)
    {
        sf::VertexArray line = sf::VertexArray(sf::Lines, 2);
        line[0].position = sf::Vector2f(20 + col * (65), 70);
        line[1].position = sf::Vector2f(20 + col * (65), 720);
        line[0].color = lineColor;
        line[1].color = lineColor;
        _lines.push_back(line);
    }

    PowerStation* station = new PowerStation(game, this);
    _chips.set(4,4,station);
    (*station).setPosition(chipPosition(4,4));

    station = new PowerStation(game, this);
    _chips.set(5,5,station);
    (*station).setPosition(chipPosition(5,5));
}


void Board::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    for(zf::TwoDSpace<Chip*>::Iterator it = _chips.iteratesColRow(); !(it.end()) ; ++it)
    {
        if(it.get() != 0)
        {
            (*(it.get())).draw(window, delta);
        }
    }
    for(std::vector<sf::VertexArray>::iterator it = _lines.begin() ; it != _lines.end() ; ++it)
    {
        window.draw(*it);
    }
}

void Board::update(sf::RenderWindow& window, const sf::Time& delta)
{
    for(zf::TwoDSpace<Chip*>::Iterator it = _chips.iteratesColRow(); !(it.end()) ; ++it)
    {
        if(it.get() != 0)
        {
            (*(it.get())).update(window, delta);
        }
    }
    _blink -= delta.asSeconds();
    if(_blink < 0)
    {
        _blink += BlinkInterval;
        chipDrawState = chipDrawState == Draw_Icon ? Draw_Timer : Draw_Icon;
    }
}

sf::Vector2f Board::chipPosition(int row, int col)
{
    return sf::Vector2f(col * 65 + 21, row * 65 + 71);
}
