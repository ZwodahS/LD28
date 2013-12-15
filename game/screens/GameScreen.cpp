#include "GameScreen.hpp"
#include "../Game.hpp"
GameScreen::GameScreen(Game& game)
    : Screen(game), _board(game), _inventory(game), _factory(game)
{
    _board.placeChip(_factory.createRandomPowerStation(ChipFactory::Common), zf::Grid(3, 3));
    _board.placeChip(_factory.createRandomPowerStation(ChipFactory::Uncommon), zf::Grid(4, 4));
    _board.placeChip(_factory.createRandomPowerStation(ChipFactory::Rare), zf::Grid(5, 5));
    
    _inventory.addChip(_factory.createFactory(ChipFactory::Common));
    _inventory.addChip(_factory.createFactory(ChipFactory::Uncommon));
    _inventory.addChip(_factory.createFactory(ChipFactory::Rare));
}

GameScreen::~GameScreen()
{
}

void GameScreen::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    _board.draw(window, delta);
    _inventory.draw(window, delta);
    _board.drawSelectedChip(window, delta, _inventory.getSelectedChip());
}

void GameScreen::update(sf::RenderWindow& window, const sf::Time& delta)
{
    _board.update(window, delta);
    _inventory.draw(window, delta);
}
void GameScreen::inputs(sf::RenderWindow& window, const sf::Time& delta)
{
    _board.inputs(window, delta);
    _inventory.inputs(window, delta);
    if(_game.mouse.left.thisReleased)
    {
        Chip* currentChip = _inventory.getSelectedChip();
        if(currentChip != 0)
        {
            zf::Grid grid = _board.toGrid(_game.mouse.getWorldPosition(window));
            if(grid != zf::Grid(-1, -1) && _board.canPlaceChip(grid))
            {
                placeChipOnGrid(grid);
            }
        }
    }
}
void GameScreen::textInput(char c)
{
}
void GameScreen::screenEnter()
{
}
void GameScreen::screenExit()
{
}

void GameScreen::placeChipOnGrid(zf::Grid grid)
{
    Chip* currentChip = _inventory.removeSelectedChip();
    if(currentChip != 0)
    {
        _board.placeChip(currentChip, grid);
    }
}
