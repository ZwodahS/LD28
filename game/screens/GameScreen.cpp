#include "GameScreen.hpp"
#include "../Game.hpp"
GameScreen::GameScreen(Game& game)
    : Screen(game), _board(game), _inventory(game)
{
}

GameScreen::~GameScreen()
{
}

void GameScreen::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    _board.draw(window, delta);
    _inventory.draw(window, delta);
}

void GameScreen::update(sf::RenderWindow& window, const sf::Time& delta)
{
    _board.update(window, delta);
    _inventory.draw(window, delta);
}
void GameScreen::inputs(sf::RenderWindow& window, const sf::Time& delta)
{
    _inventory.inputs(window, delta);
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
