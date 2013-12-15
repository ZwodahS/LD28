#include "GameScreen.hpp"
#include "../Game.hpp"
const sf::FloatRect GameScreen::RunFactoryButtonBound = sf::FloatRect(710, 900, 230, 40);
GameScreen::GameScreen(Game& game)
    : Screen(game), _board(game), _inventory(game), _factory(game), _detail(_game)
    , _player(game), _shop(game, _player)
{
    _inventory.addChip(_factory.createPowerStation(ChipFactory::Uncommon));
    _inventory.addChip(_factory.createCombiner(ChipFactory::Rare));
    _inventory.addChip(_factory.createMultiplier(ChipFactory::Uncommon));
    _inventory.addChip(_factory.createConnector(ChipFactory::Uncommon));
    _inventory.addChip(_factory.createFactory(ChipFactory::Common));
    _inventory.addChip(_factory.createCollector(ChipFactory::Uncommon));
    sf::Text text = sf::Text("Run Factory", _game.assets.font, 14);
    _runFactory = zf::VertexButton(sf::Color(0,255,0), sf::Color(0, 100, 0), RunFactoryButtonBound, text);
}

GameScreen::~GameScreen()
{
}

void GameScreen::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    _board.draw(window, delta);
    _inventory.draw(window, delta);
    _board.drawSelectedChip(window, delta, _inventory.getSelectedChip());
    _runFactory.draw(window, delta);
    _detail.draw(window, delta);
    _shop.draw(window, delta);
    _player.draw(window, delta);
}

void GameScreen::update(sf::RenderWindow& window, const sf::Time& delta)
{
    _board.update(window, delta);
    _inventory.draw(window, delta);
    _detail.setPosition(_game.mouse.getWorldPosition(window));
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
    if(_runFactory.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            _board.runOnce();
        }
    }
    _shop.inputs(window, delta);
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
