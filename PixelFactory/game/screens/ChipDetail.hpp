#ifndef _GAME_SCREEN_CHIPDETAIL_H_
#define _GAME_SCREEN_CHIPDETAIL_H_
#include <SFML/Graphics.hpp>
class Game;
class Chip;
class ChipDetail
{
public:
    static const sf::Color BorderColor;
    static const sf::Color BackgroundColor;
    enum Mode
    {
        Board,
        Inventory,
    };
    ChipDetail(Game& game);

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);
    void setPosition(const sf::Vector2f& position);
    Chip* getCurrentChip();   
    // if chip is 0, then everything will cleared. 
    // if Mode == Board, it will display what it contains.
    void showChip(Chip* chip, Mode mode = Board);
private:
    Game& _game;
    Mode _mode;    
    Chip* _currentShowingChip;

    std::vector<sf::Text> _texts;
    std::vector<sf::Sprite> _sprites;
    sf::FloatRect _bound;

    sf::VertexArray _border;
    sf::VertexArray _background;

    void updatePositions();
};
#endif
