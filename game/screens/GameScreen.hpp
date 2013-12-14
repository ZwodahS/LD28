#ifndef _GAME_SCREENS_GAMESCREEN_H_
#define _GAME_SCREENS_GAMESCREEN_H_
#include "Screen.hpp"
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
private:
};
#endif
