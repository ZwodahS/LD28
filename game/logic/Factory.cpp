/*
 *           DO WHAT THE **** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 * 
 * Copyright (C) 2013 ZwodahS(ericnjf@gmail.com) 
 * zwodahs.wordpress.com
 * 
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 * 
 *           DO WHAT THE **** YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 * 
 *  0. You just DO WHAT THE **** YOU WANT TO.
 * 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. 
 */
#include "Factory.hpp"
#include "Board.hpp"
const sf::Vector2f Factory::PowerOffset = sf::Vector2f(13, 29);
const sf::Vector2f Factory::ArrowOffset = sf::Vector2f(25, 29);
const sf::Vector2f Factory::OutputOffset = sf::Vector2f(40, 29);
Factory::Factory(Game& game, Board* board)
    : Chip(game, board, Chip::Factory)
{
    setFactoryOutputProduction(FactoryOutput::Pixel_Red);
    _powerIcon = _game.assets.power.createSprite();
    _arrowIcon = _game.assets.conversionArrow.createSprite();
    _outputIcon = _game.assets.shadedBox.createSprite();
}

Factory::~Factory()
{
}

void Factory::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::draw(window, delta);
    if(_board == 0 || _board->getChipDrawState() == Board::Draw_Icon)
    {
        window.draw(_powerIcon);
        window.draw(_arrowIcon);
        window.draw(_outputIcon);
    }
}

void Factory::update(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::update(window, delta);
}

void Factory::setPosition(const sf::Vector2f& position)
{
    Chip::setPosition(position);
    _powerIcon.setPosition(position + PowerOffset);
    _arrowIcon.setPosition(position + ArrowOffset);
    _outputIcon.setPosition(position + OutputOffset);
}

void Factory::setAlpha(float alpha)
{
    Chip::setAlpha(alpha);
    zf::setAlpha(_powerIcon, alpha);
    zf::setAlpha(_arrowIcon, alpha);
    zf::setAlpha(_outputIcon, alpha);
}

void Factory::setFactoryOutputProduction(FactoryOutput::Type type)
{ 
    _factoryType = type;
    _outputIcon.setColor(FactoryOutput::getColor(type));
}

void Factory::beginProcessing()
{
    FactoryOutput* output = 0;
    for(std::vector<FactoryOutput*>::iterator it = _inputs.begin() ; it != _inputs.end() ; ++it)
    {
        if((**it).getType() == FactoryOutput::Power)
        {
            FactoryOutput* o = *it;
            _inputs.erase(it);
            delete o;
            output = new FactoryOutput(_game, _factoryType);
            break;
        }
        else
        {
            delete *it;
        }
    }
    if(output != 0)
    {
        if(_arrows.hasOut(zf::North))
        {
            _outputs.push_back(std::pair<FactoryOutput*, zf::Grid>(output, zf::Grid(-1, 0)));
        }
        else if(_arrows.hasOut(zf::East))
        {
            _outputs.push_back(std::pair<FactoryOutput*, zf::Grid>(output, zf::Grid(0, 1)));
        }
        else if(_arrows.hasOut(zf::South))
        {
            _outputs.push_back(std::pair<FactoryOutput*, zf::Grid>(output, zf::Grid(1, 0)));
        }
        else if(_arrows.hasOut(zf::West))
        {
            _outputs.push_back(std::pair<FactoryOutput*, zf::Grid>(output, zf::Grid(0, -1)));
        }
    }
}

bool Factory::isProcessing()
{
    return false;
}

bool Factory::acceptInput(FactoryOutput* output)
{
    if(output == 0 || output->getType() != FactoryOutput::Power)
    {
        return false;
    }
    else
    {
        return true;
    }
}
