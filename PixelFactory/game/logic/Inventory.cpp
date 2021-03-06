#include "Inventory.hpp"
#include "PowerStation.hpp"
#include "../../z_framework/zf_common/f_inputs.hpp"
const sf::Vector2f Inventory::InventoryBegins = sf::Vector2f(5, 10);
const sf::Vector2f Inventory::InternalOffset = sf::Vector2f(5, 5);
const sf::Vector2f Inventory::Spacing = sf::Vector2f(80, 80);
const sf::FloatRect Inventory::SellButton = sf::FloatRect(10, 650, 150, 30);
Inventory::Inventory(Game& game)
    : _game(game), _selection(sf::Quads, 4), _currentSelectedChip(0)
    , _destroyButton(sf::Color(255,255,255,255), sf::Color(255,255,255,50), SellButton, sf::Text("Destroy Chip", _game.assets.font, 14))
{
    sf::Color selectionColor = sf::Color(100, 100, 0);
    _selection[0].color = selectionColor;
    _selection[1].color = selectionColor;
    _selection[2].color = selectionColor;
    _selection[3].color = selectionColor;
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
    _destroyButton.draw(window, delta);
}

void Inventory::update(sf::RenderWindow& window, const sf::Time& delta)
{
}

void Inventory::inputs(sf::RenderWindow& window, const sf::Time& delta)
{
    zf::Input::processKey(_rotateAntiKey, sf::Keyboard::isKeyPressed(sf::Keyboard::Q), delta.asSeconds());
    zf::Input::processKey(_rotateKey, sf::Keyboard::isKeyPressed(sf::Keyboard::E), delta.asSeconds());
    if(_destroyButton.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_currentSelectedChip != 0)
            {
                destroyCurrentChip();
            }
        }
    }
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
    else if(_rotateAntiKey.thisReleased)
    {
        if(_currentSelectedChip != 0)
        {
            _currentSelectedChip->rotateAnti();
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
    return InventoryBegins + InternalOffset + sf::Vector2f(index%2 * Spacing.x + 3, index/2 * Spacing.y + 3);
}

void Inventory::setSelectionBound(sf::FloatRect bound)
{
    _selection[0].position = sf::Vector2f(bound.left - 3, bound.top - 3);
    _selection[1].position = sf::Vector2f(bound.left + 3 + bound.width, bound.top - 3);
    _selection[2].position = sf::Vector2f(bound.left + 3 + bound.width, bound.top + 3 + bound.height);
    _selection[3].position = sf::Vector2f(bound.left - 3 , bound.top + 3 + bound.height);
}

Chip* Inventory::getSelectedChip()
{
    return _currentSelectedChip;
}

Chip* Inventory::removeSelectedChip()
{
    Chip* tmp = _currentSelectedChip;
    if(_currentSelectedChip != 0)
    {
        for(std::vector<Chip*>::iterator it = _chips.begin() ; it != _chips.end() ; )
        {    
            if(*it == _currentSelectedChip)
            {
                it = _chips.erase(it);
                continue;
            }
            ++it;
        }
        _currentSelectedChip = 0;
        updatePositions();
    }
    return tmp;
}

void Inventory::addChip(Chip* chip)
{
    _chips.push_back(chip);
    updatePositions();
}

bool Inventory::isFull()
{
    return _chips.size() >= 16;
}

void Inventory::destroyCurrentChip()
{
    Chip* chip = removeSelectedChip();
    delete chip;
}
