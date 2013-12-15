#include "Board.hpp"
#include "../Game.hpp"
#include "Chip.hpp"
#include "PowerStation.hpp"
const float Board::BlinkInterval = 2;
const int Board::Max_Row = 10;
const int Board::Max_Col = 10;
Board::Board(Game& game)
    : _game(game), _chips(Max_Row, Max_Col, 0), _blink(BlinkInterval), chipDrawState(Draw_Icon)
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

void Board::inputs(sf::RenderWindow& window, const sf::Time& delta)
{
}

sf::Vector2f Board::chipPosition(int row, int col)
{
    return sf::Vector2f(col * 65 + 21, row * 65 + 71);
}

zf::Grid Board::toGrid(sf::Vector2f position)
{
    position -= sf::Vector2f(21, 71);
    zf::Grid grid = zf::Grid::toGrid(position.x, position.y, 65, 0);
    if(!inRange(grid))
    {
        return zf::Grid(-1, -1);
    }
    return grid;
}

void Board::drawSelectedChip(sf::RenderWindow& window, const sf::Time& delta, Chip* chip)
{
    if(chip != 0)
    {
        zf::Grid grid = toGrid(_game.mouse.getWorldPosition(window));
        if(inRange(grid))
        {
            chip->drawShadow(window, delta, chipPosition(grid.row, grid.col));
        }
    }
}

bool Board::inRange(const zf::Grid& grid)
{
    if(grid.row < 0 || grid.col < 0 || grid.row >= Max_Row || grid.col >= Max_Col)
    {
        return false;
    }
    return true;
}

bool Board::canPlaceChip(const zf::Grid& grid)
{
    return inRange(grid) && _chips.get(grid) == 0;
}

void Board::placeChip(Chip* chip, const zf::Grid& grid)
{
    if(!canPlaceChip(grid))
    {
        return;
    }
    _chips.set(grid, chip);
    chip->setPosition(chipPosition(grid.row, grid.col));
    chip->setBoard(this);
}


