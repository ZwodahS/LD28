#ifndef _GAME_SCREENS_GAMESCREEN_H_
#define _GAME_SCREENS_GAMESCREEN_H_
#include "Screen.hpp"
#include "../logic/Board.hpp"
#include "../logic/Inventory.hpp"
#include "../logic/ChipFactory.hpp"
class GameScreen : public Screen
{
public:
    GameScreen(Game& game);
    ~GameScreen();

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);
    void inputs(sf::RenderWindow& window, const sf::Time& delta);
    void textInput(char c);
    void screenEnter();
    void screenExit();

    void placeChipOnGrid(zf::Grid grid);
private:
    Board _board;
    Inventory _inventory;
    ChipFactory _factory;
};
#endif
