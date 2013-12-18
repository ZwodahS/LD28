#ifndef _GAME_SCREENS_GAMESCREEN_H_
#define _GAME_SCREENS_GAMESCREEN_H_
#include "Screen.hpp"
#include "../logic/Board.hpp"
#include "../logic/Inventory.hpp"
#include "../logic/ChipFactory.hpp"
#include "../logic/Player.hpp"
#include "../logic/Shop.hpp"
#include "ChipDetail.hpp"
#include "../../z_framework/zf_sfml/VertexButton.hpp"
#include "../../z_framework/zf_common/InputState.hpp"
class GameScreen : public Screen
{
public:
    static const sf::FloatRect RunFactoryButtonBound;
    GameScreen(Game& game);
    ~GameScreen();

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);
    void inputs(sf::RenderWindow& window, const sf::Time& delta);
    void textInput(char c);
    void screenEnter();
    void screenExit();

    void placeChipOnGrid(zf::Grid grid);

    void chipsBought(ChipFactory::Rarity rarity, int amount);

private:
    Board _board;
    Inventory _inventory;
    ChipFactory _factory;
    ChipDetail _detail;
    Player _player;
    Shop _shop;

    zf::VertexButton _runFactory;
    zf::InputState _runFactoryButton;
};
#endif
