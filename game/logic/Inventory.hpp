#ifndef _GAME_LOGIC_INVENTORY_H_
#define _GAME_LOGIC_INVENTORY_H_
#include "../../z_framework/zf_common/InputState.hpp"
#include "../../z_framework/zf_sfml/VertexButton.hpp"
#include "Chip.hpp"
#include <SFML/Window.hpp>
class Game;
class Inventory
{
public:
    static const sf::Vector2f InventoryBegins;
    static const sf::Vector2f InternalOffset;
    static const sf::Vector2f Spacing;
    static const sf::FloatRect SellButton;
    Inventory(Game& game);
    ~Inventory();

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);
    void inputs(sf::RenderWindow& window, const sf::Time& delta);

    Chip* getSelectedChip();
    Chip* removeSelectedChip();
    void addChip(Chip* chip);

    bool isFull();
private:
    Game& _game;
    std::vector<Chip*> _chips;
    Chip* _currentSelectedChip;

    sf::VertexArray _selection;
    void updatePositions();
    sf::Vector2f chipPosition(int index);
    void setSelectionBound(sf::FloatRect bound);
    
    zf::VertexButton _destroyButton;

    zf::InputState _rotateKey;
    zf::InputState _rotateAntiKey;

    void destroyCurrentChip();
};
#endif
