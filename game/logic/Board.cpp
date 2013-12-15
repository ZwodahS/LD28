#include "Board.hpp"
#include "../Game.hpp"
#include "Chip.hpp"
Board::Board(Game& game)
    : _game(game), _chips(10, 10, 0)
{
    sf::Color lineColor = sf::Color(150,150,150);
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
}
