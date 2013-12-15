#include "Inventory.hpp"
#include "PowerStation.hpp"
#include "../../z_framework/zf_common/f_inputs.hpp"
const sf::Vector2f Inventory::InventoryBegins = sf::Vector2f(0, 740);
const sf::Vector2f Inventory::InternalOffset = sf::Vector2f(20, 30);
const sf::Vector2f Inventory::Spacing = sf::Vector2f(80, 80);
Inventory::Inventory(Game& game)
    : _game(game), _selection(sf::Quads, 4)
{
    sf::Color selectionColor = sf::Color(100, 100, 0);
    _selection[0].color = selectionColor;
    _selection[1].color = selectionColor;
    _selection[2].color = selectionColor;
    _selection[3].color = selectionColor;

    PowerStation* station = new PowerStation(game);
    _chips.push_back(station);
    station = new PowerStation(game);
    _chips.push_back(station);
    station = new PowerStation(game);
    _chips.push_back(station);
    updatePositions();
}

Inventory::~Inventory()
{
}

void Inventory::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    if(_currentSelectedChip != 0)
    {
        window.draw(_selection);
    }
    for(std::vector<Chip*>::iterator it = _chips.begin() ; it != _chips.end() ; ++it)
    {
        (**it).draw(window, delta);
    }
}

void Inventory::update(sf::RenderWindow& window, const sf::Time& delta)
{
}

void Inventory::inputs(sf::RenderWindow& window, const sf::Time& delta)
{
    zf::Input::processKey(_rotateKey, sf::Keyboard::isKeyPressed(sf::Keyboard::Space), delta.asSeconds());
    if(_game.mouse.left.thisReleased)
    {
        sf::Vector2f mousePos = _game.mouse.getWorldPosition(window);
        for(std::vector<Chip*>::iterator it = _chips.begin() ; it != _chips.end() ; ++it)
        {
            if((**it).getBound().contains(mousePos))
            {
                if(_currentSelectedChip == *it)
                {
                    _currentSelectedChip = 0;
                }
                else
                {
                    _currentSelectedChip = *it;
                }
                break;
            } 
        }
        if(_currentSelectedChip != 0)
        {
            sf::FloatRect bound = _currentSelectedChip->getBound();
            setSelectionBound(bound);
        }
    }
    if(_rotateKey.thisReleased)
    {
        if(_currentSelectedChip != 0)
        {
            _currentSelectedChip->rotate();
        }
    }
}

void Inventory::updatePositions()
{
    int i = 0;
    for(std::vector<Chip*>::iterator it = _chips.begin() ; it != _chips.end() ; ++it, i++)
    {
        (**it).setPosition(chipPosition(i));
    }    
}

sf::Vector2f Inventory::chipPosition(int index)
{
    return InventoryBegins + InternalOffset + sf::Vector2f(index/2 * Spacing.x + 3, index%2 * Spacing.y + 3);
}

void Inventory::setSelectionBound(sf::FloatRect bound)
{
    _selection[0].position = sf::Vector2f(bound.left - 3, bound.top - 3);
    _selection[1].position = sf::Vector2f(bound.left + 3 + bound.width, bound.top - 3);
    _selection[2].position = sf::Vector2f(bound.left + 3 + bound.width, bound.top + 3 + bound.height);
    _selection[3].position = sf::Vector2f(bound.left - 3 , bound.top + 3 + bound.height);
}
