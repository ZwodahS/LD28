#include "Board.hpp"
#include "../Game.hpp"
#include "Chip.hpp"
#include "FactoryOutput.hpp"
#include "../../z_framework/zf_common/f_inputs.hpp"
const float Board::BlinkInterval = 3;
const int Board::Max_Row = 10;
const int Board::Max_Col = 10;
const sf::Vector2f Board::BoardOffset = sf::Vector2f(170, 20);
Board::Board(Game& game)
    : _game(game), _chips(Max_Row, Max_Col, 0), _blink(BlinkInterval), _chipDrawState(Draw_Icon), boardState(State_Idle)
{
    sf::Color lineColor = sf::Color(50,50,50);
    for(int row = 0 ; row < 11 ; row ++)
    {
        sf::VertexArray line = sf::VertexArray(sf::Lines, 2);
        line[0].position = sf::Vector2f(0, row * (65)) + BoardOffset;
        line[1].position = sf::Vector2f(650, row * (65)) + BoardOffset;
        line[0].color = lineColor;
        line[1].color = lineColor;
        _lines.push_back(line);
    }
    for(int col = 0 ; col < 11 ; col ++)
    {
        sf::VertexArray line = sf::VertexArray(sf::Lines, 2);
        line[0].position = sf::Vector2f(col * (65), 0) + BoardOffset;
        line[1].position = sf::Vector2f(col * (65), 650) + BoardOffset;
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
    for(std::vector<FactoryOutput*>::iterator it = _factoryOutputs.begin() ; it != _factoryOutputs.end() ; ++it)
    {
        (**it).draw(window, delta);
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
        _chipDrawState = _chipDrawState == Draw_Icon ? Draw_Timer : Draw_Icon;
    }
    if(boardState == State_Idle)
    {
    }
    else if(boardState == State_Processing)
    {
        bool stillProcessing = false;
        for(zf::TwoDSpace<Chip*>::Iterator it = _chips.iteratesColRow(); !(it.end()) ; ++it)
        {
            if(it.get() != 0)
            {
                if((*it.get()).isProcessing())
                {
                    stillProcessing = true;
                    break;
                }
            }
        }
        if(stillProcessing)
        {
        }
        else
        {
            static const sf::Vector2f FactoryOutputOffset = sf::Vector2f(27, 27);
            for(zf::TwoDSpace<Chip*>::Iterator it = _chips.iteratesColRow(); !(it.end()) ; ++it)
            {
                if(it.get() != 0)
                {
                    std::vector<std::pair<FactoryOutput*, zf::Grid> > outputs = (*it.get()).getOutputs();
                    int i = 0;
                    for(std::vector<std::pair<FactoryOutput*, zf::Grid> >::iterator it2 = outputs.begin() ; it2 != outputs.end() ; ++it2)
                    {
                        zf::Grid directionGrid = (*it2).second;
                        zf::Grid destinationGrid = (*it2).second + it.current;
                        sf::Vector2f startingDestination = chipPosition(it.current.row, it.current.col);
                        sf::Vector2f endingDestination = chipPosition(destinationGrid.row, destinationGrid.col);
                        Chip* chip = _chips.get(destinationGrid);
                        zf::Direction inputDirection = directionGrid == zf::Grid(-1, 0) ? zf::South :
                                                       directionGrid == zf::Grid(1, 0)  ? zf::North :
                                                       directionGrid == zf::Grid(0, -1) ? zf::East  : zf::West;
                        if(!inRange(destinationGrid))
                        {
                            delete (*it2).first;
                        }
                        else if(chip != 0 && chip->acceptInputFrom(inputDirection) && chip->acceptInput((*it2).first))
                        {
                            (*(*it2).first).moveTo( FactoryOutputOffset + startingDestination
                                                 , FactoryOutputOffset + endingDestination
                                                 , i);
                            _factoryOutputs.push_back((*it2).first);
                            (*it2).first->targetGrid = destinationGrid;
                            i++;
                        }
                        else
                        {
                            delete (*it2).first;
                        }
                    }
                }
            }
            boardState = State_MovingObject;
        }
    }
    else if(boardState == State_MovingObject)
    {
        for(std::vector<FactoryOutput*>::iterator it = _factoryOutputs.begin() ; it != _factoryOutputs.end() ; ++it)
        {
            (**it).update(window, delta);
        }
        bool stillanimating = false;
        for(std::vector<FactoryOutput*>::iterator it = _factoryOutputs.begin() ; it != _factoryOutputs.end() ; ++it)
        {
            if((**it).isAnimating())
            {
                stillanimating = true;
                break;
            }
        }
        if(!stillanimating)
        {
            for(std::vector<FactoryOutput*>::iterator it = _factoryOutputs.begin() ; it != _factoryOutputs.end() ; ++it)
            {
                if((**it).markedForDestruction)
                {
                    delete *it;
                }
                else
                {
                    Chip* chip = _chips.get((**it).targetGrid);
                    if(chip == 0)
                    {
                        delete *it;
                    }
                    else
                    {
                        chip->put(*it);
                    }
                }
            }
            _factoryOutputs.clear();
            for(zf::TwoDSpace<Chip*>::Iterator it = _chips.iteratesColRow(); !(it.end()) ; ++it)
            {
                if(it.get() != 0)
                {
                    if((*(it.get())).clockDeplete())
                    {
                        (*(it.get())).animateDestroy();
                    }
                }
            }
            boardState = State_DestructionOfChip;
        }
    }
    else if(boardState == State_DestructionOfChip)
    {
        bool isAnimating = false;
        for(zf::TwoDSpace<Chip*>::Iterator it = _chips.iteratesColRow(); !(it.end()) ; ++it)
        {
            if(it.get() != 0)
            {
                Chip& chip = *(it.get());
                if(chip.isAnimating())
                {
                    isAnimating = true;
                    break;
                }
            }
        }
        if(!isAnimating)
        {
            for(zf::TwoDSpace<Chip*>::Iterator it = _chips.iteratesColRow(); !(it.end()) ; ++it)
            {
                if(it.get() != 0)
                {
                    Chip& chip = *(it.get());
                    if(chip.markedForDestruction())
                    {
                        delete &chip;
                        it.set(0);
                    }
                }
            }
            boardState = State_Idle;
        }
    }
}

void Board::inputs(sf::RenderWindow& window, const sf::Time& delta)
{
    zf::Input::processKey(_showTimer, sf::Keyboard::isKeyPressed(sf::Keyboard::LShift), delta.asSeconds());
    if(_showTimer.thisReleased)
    {
        _blink = 10;
        _chipDrawState = _chipDrawState == Draw_Icon ? Draw_Timer : Draw_Icon;
    }
}

Chip* Board::getChip(sf::Vector2f position)
{
    zf::Grid grid = toGrid(position);
    if(inRange(grid))
    {
        return _chips.get(grid);
    }
    else
    {
        return 0;
    }
}

sf::Vector2f Board::chipPosition(int row, int col)
{
    return sf::Vector2f(col * 65, row * 65) + BoardOffset + sf::Vector2f(1,1);
}

zf::Grid Board::toGrid(sf::Vector2f position)
{
    position -= BoardOffset - sf::Vector2f(1, 1);
    if(position.x < 0 || position.y < 0)
    {
        return zf::Grid(-1, -1);
    }
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
        if(inRange(grid) && canPlaceChip(grid))
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

void Board::runOnce()
{
    if(boardState != State_Idle)
    {
        return;
    }
    boardState = State_Processing;
    for(zf::TwoDSpace<Chip*>::Iterator it = _chips.iteratesColRow(); !(it.end()) ; ++it)
    {
        if(it.get() != 0)
        {
            (*(it.get())).beginProcessing();
        }
    }
}

std::vector<FactoryOutput*> Board::getCollectorGoods()
{
    std::vector<FactoryOutput*> goods = _collectorGoods;
    _collectorGoods.clear();
    return goods;
}


void Board::collect(FactoryOutput* goods)
{
    _collectorGoods.push_back(goods);
}

int Board::getChipCount()
{
    int count = 0;
    for(zf::TwoDSpace<Chip*>::Iterator it = _chips.iteratesColRow(); !(it.end()) ; ++it)
    {
        if(it.get() != 0)
        {
            count++;
        }
    }
    return count;
}

Board::ChipDrawState Board::getChipDrawState()
{
    return _chipDrawState;
}
